/*
Lama Dial Pad Gamepad - V3.0
(Former Open Dials)
USB version
Arduino pro micro pinout.
*/

#include "NewEncoder.h"
#include "HID-Project.h"
#include <EEPROM.h>

NewEncoder firstEncoder;
NewEncoder secondEncoder;

/*Altere os valores abaixo para remapear os botões do controle*/
/*Change the values below to remap controller buttons*/
/*-------------------------------------------*/
const int GamePad_Up = 12;
const int GamePad_Down = 13;
const int GamePad_Left = 14;
const int GamePad_Right = 15;
const int GamePad_A = 1;
const int GamePad_B = 2;
const int GamePad_DialUp = 3;
const int GamePad_DialDown = 4;
const int GamePad_DialLeft = 10;
const int GamePad_DialRight = 11;
const int GamePad_Start = 7;
const int GamePad_Select = 5;

const KeyboardKeycode Keyboard_Up = KEY_W;
const KeyboardKeycode Keyboard_Down = KEY_S;
const KeyboardKeycode Keyboard_Left = KEY_A;
const KeyboardKeycode Keyboard_Right = KEY_D;
const KeyboardKeycode Keyboard_A = KEY_SPACE;
const KeyboardKeycode Keyboard_B = KEY_RIGHT_SHIFT;
const KeyboardKeycode Keyboard_DialUp = KEY_UP;
const KeyboardKeycode Keyboard_DialDown = KEY_DOWN;
const KeyboardKeycode Keyboard_DialLeft = KEY_LEFT;
const KeyboardKeycode Keyboard_DialRight = KEY_RIGHT;
const KeyboardKeycode Keyboard_Start = KEY_ENTER;
const KeyboardKeycode Keyboard_Select = KEY_ESC;
/*-------------------------------------------*/


/*Altere os pinos abaixo para remapear as ligações do Arduino*/
/*Change the pin values below to remap arduino connections*/
/*-------------------------------------------*/
const int button_up_pin = 2;
const int button_down_pin = 3;
const int button_left_pin = 4;
const int button_right_pin = 5;

const int button_a_pin = 15;
const int button_b_pin = A0;

const int button_start_pin = 6;
const int encoder1_a_pin = 7;
const int encoder1_b_pin = 8;

const int button_select_pin = 10;
const int encoder2_a_pin = 14;
const int encoder2_b_pin = 16;

const int led_mode_joypad_pin = A1;
const int led_mode_keyboard_pin = A2;
const int button_mode_pin = A3;
/*-------------------------------------------*/

int encoder1_last = 0;
int encoder2_last = 0;
bool button_up_last = false;
bool button_down_last = false;
bool button_left_last = false;
bool button_right_last = false;
bool button_a_last = false;
bool button_b_last = false;
bool button_start_last = false;
bool button_select_last = false;
bool button_mode_last = false;

bool button_l = false;
bool button_r = false;
bool button_x = false;
bool button_y = false;

bool button_l_state = false;
bool button_r_state = false;
bool button_x_state = false;
bool button_y_state = false;

int mode = 0;
int mode_address = 0;

unsigned long delayTime = 0;

void setup()
{
    pinMode(button_up_pin, INPUT_PULLUP);
    pinMode(button_down_pin, INPUT_PULLUP);
    pinMode(button_left_pin, INPUT_PULLUP);
    pinMode(button_right_pin, INPUT_PULLUP);

    pinMode(button_a_pin, INPUT_PULLUP);
    pinMode(button_b_pin, INPUT_PULLUP);

    pinMode(button_start_pin, INPUT_PULLUP);
    pinMode(button_select_pin, INPUT_PULLUP);

    pinMode(button_mode_pin, INPUT_PULLUP);
    pinMode(led_mode_joypad_pin, OUTPUT);
    pinMode(led_mode_keyboard_pin, OUTPUT);

    firstEncoder.begin(encoder1_a_pin, encoder1_b_pin);
    secondEncoder.begin(encoder2_a_pin, encoder2_b_pin);    
    mode = EEPROM.read(mode_address);
    if(mode != 0 && mode != 1)
    {
      mode = 0;
    } 
    SetMode();
}

void loop()
{      
    firstEncoder.Update();
    secondEncoder.Update();
    
    if (millis() - delayTime < 100)
        return;

    delayTime = millis();      
      
    SetEncoder();
    SelectMode();
      
    if(mode == 0){
      digitalWrite(led_mode_joypad_pin, HIGH);
      digitalWrite(led_mode_keyboard_pin, LOW);
      JoypadMode();
    }
    else
    {
      digitalWrite(led_mode_keyboard_pin, HIGH);
      digitalWrite(led_mode_joypad_pin, LOW);
      KeyboardMode();
    }    
}

void JoypadMode()
{
  bool up = digitalRead(button_up_pin) == LOW;
  bool down = digitalRead(button_down_pin) == LOW;
  bool left = digitalRead(button_left_pin) == LOW;
  bool right = digitalRead(button_right_pin) == LOW;

  bool a = digitalRead(button_a_pin) == LOW;
  bool b = digitalRead(button_b_pin) == LOW;

  bool start = digitalRead(button_start_pin) == LOW;
  bool select = digitalRead(button_select_pin) == LOW;
  
  if(up)
  {
    Gamepad.press(GamePad_Up);
  }
  else
  {
    Gamepad.release(GamePad_Up);
  }

  if(down)
  {
    Gamepad.press(GamePad_Down);
  }
  else
  {
    Gamepad.release(GamePad_Down);
  }

  if(left)
  {
    Gamepad.press(GamePad_Left);
  }
  else
  {
    Gamepad.release(GamePad_Left);
  }

  if(right)
  {
    Gamepad.press(GamePad_Right);
  }
  else
  {
    Gamepad.release(GamePad_Right);
  }

  if(select)
  {
    Gamepad.press(GamePad_Select);
  }
  else
  {
    Gamepad.release(GamePad_Select);
  }

  if(start)
  {
    Gamepad.press(GamePad_Start);
  }
  else
  {
    Gamepad.release(GamePad_Start);
  }

  if(a)
  {
    Gamepad.press(GamePad_A);
  }
  else
  {
    Gamepad.release(GamePad_A);
  }

  if(b)
  {
    Gamepad.press(GamePad_B);
  }
  else
  {
    Gamepad.release(GamePad_B);
  }

  if(button_x && !button_x_state)
  {
    Gamepad.press(GamePad_DialUp);    
    button_x_state = true;
  }
  else
  {
    Gamepad.release(GamePad_DialUp);
    button_x_state = false;
  }

  if(button_y && !button_y_state)
  {
    Gamepad.press(GamePad_DialDown);    
    button_y_state = true;
  }
  else
  {
    Gamepad.release(GamePad_DialDown);
    button_y_state = false;
  }

  if(button_l && !button_l_state)
  {
    Gamepad.press(GamePad_DialLeft);
    button_l_state = true;
  }
  else
  {
    Gamepad.release(GamePad_DialLeft);
    button_l_state = false;
  }

  if(button_r && !button_r_state)
  {
    Gamepad.press(GamePad_DialRight);
    button_r_state = true;
  }
  else
  {
    Gamepad.release(GamePad_DialRight);
    button_r_state = false;
  }

  Gamepad.write();
}

void KeyboardMode()
{
  bool up = digitalRead(button_up_pin) == LOW;
  bool down = digitalRead(button_down_pin) == LOW;
  bool left = digitalRead(button_left_pin) == LOW;
  bool right = digitalRead(button_right_pin) == LOW;

  bool a = digitalRead(button_a_pin) == LOW;
  bool b = digitalRead(button_b_pin) == LOW;

  bool start = digitalRead(button_start_pin) == LOW;
  bool select = digitalRead(button_select_pin) == LOW;

  if(up)
  {
    Keyboard.press(Keyboard_Up);
  }
  else
  {
    Keyboard.release(Keyboard_Up);
  }

  if(down)
  {
    Keyboard.press(Keyboard_Down);
  }
  else
  {
    Keyboard.release(Keyboard_Down);
  }

  if(left)
  {
    Keyboard.press(Keyboard_Left);
  }
  else
  {
    Keyboard.release(Keyboard_Left);
  }

  if(right)
  {
    Keyboard.press(Keyboard_Right);
  }
  else
  {
    Keyboard.release(Keyboard_Right);
  }

  if(select)
  {
    Keyboard.press(Keyboard_Select);
  }
  else
  {
    Keyboard.release(Keyboard_Select);
  }

  if(start)
  {
    Keyboard.press(Keyboard_Start);
  }
  else
  {
    Keyboard.release(Keyboard_Start);
  }

  if(a)
  {
    Keyboard.press(Keyboard_A);
  }
  else
  {
    Keyboard.release(Keyboard_A);
  }

  if(b)
  {
    Keyboard.press(Keyboard_B);
  }
  else
  {
    Keyboard.release(Keyboard_B);
  }

  if(button_x && !button_x_state)
  {
    Keyboard.press(Keyboard_DialDown); 
    button_x_state = true;
  }
  else
  {
    Keyboard.release(Keyboard_DialDown);
    button_x_state = false;
  }

  if(button_y && !button_y_state)
  {
    Keyboard.press(Keyboard_DialUp);    
    button_y_state = true;
  }
  else
  {
    Keyboard.release(Keyboard_DialUp);
    button_y_state = false;
  }

  if(button_l && !button_l_state)
  {
    Keyboard.press(Keyboard_DialLeft);
    button_l_state = true;
  }
  else
  {
    Keyboard.release(Keyboard_DialLeft);
    button_l_state = false;
  }

  if(button_r && !button_r_state)
  {
    Keyboard.press(Keyboard_DialRight);
    button_r_state = true;
  }
  else
  {
    Keyboard.release(Keyboard_DialRight);
    button_r_state = false;
  }

  Keyboard.send();
}

void SetEncoder()
{  
  int encoder1_value = firstEncoder.GetSteps();
  int encoder2_value = secondEncoder.GetSteps();
  if(encoder1_value != encoder1_last) 
    {
      if(encoder1_value > encoder1_last)
      {
        button_r = true;
      }else 
      {
        button_l = true;
      }
      encoder1_last = encoder1_value;
    }
    else
    {
      button_r = false;
      button_l = false;
    }

    if(encoder2_value != encoder2_last) 
    {
      if(encoder2_value > encoder2_last)
      {
        button_x = true;
      }else 
      {
        button_y = true;
      }
      encoder2_last = encoder2_value;
    }
    else
    {
      button_x = false;
      button_y = false;
    }  
}

void SelectMode()
{
  if(GetButtonState(button_mode_pin) != button_mode_last)
  {
    if(GetButtonState(button_mode_pin))
    {      
      if(mode == 0)
      {
        mode = 1;        
      }else
      {
        mode = 0;        
      }    
      EEPROM.write(mode_address, mode);
      SetMode();
    }
    button_mode_last = GetButtonState(button_mode_pin);
  }
}

void SetMode()
{
  if(mode == 0)
  {
    Keyboard.end();
    Gamepad.begin();
  }else
  {
    Gamepad.end();
    Keyboard.begin();
  }      
}

bool GetButtonState(int button){
  if(digitalRead(button) == HIGH) 
  {
    return false;
  }else
  {
    return true;
  }
}