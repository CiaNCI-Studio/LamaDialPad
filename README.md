# Lama Dial Pad

Lama Dial Pad - Open Source Gamepad

Desenvolvido para ser usado com o console fantasia Lama16 e com o Lama Engine
mas e um controle multi propósito  com botões que podem ser mapeados como um controle de SNES.
Funciona elegantemente com o Godot ;)

(
Designed for use with Lama16 Fantasy Console, and Lama Engine, 
but it's a multi purpose gamepad with buttons that can be maped to snes controller. 
Works elegantly with Godot ;)
)

[Color Roll Test Game](https://github.com/Kelvysb/ColorRoll)

V3 3d: models (printables)

https://www.thingiverse.com/thing:6273114

https://skfb.ly/oMzWV

Ingredientes (Ingredients):
1 - Arduino Pro micro (Atmel Mega32U4)
6 - Push buttons 1.5mm (1.5mm push buttons)
1 - Push button 4.5mm (4.5mm push button)
2 - Rotary encoders 12.5mm
2 - Leds 5mm
1 - Resistor de 1k
1 - Cabo USB (USB cable)
Muitos - Fios (Wires)

Circuito (Circuit):

![circuit](./docs/Circuit%20Schema.png)

Esquema de montagem (Assembly Scheme):


if(up)
  {
    Keyboard.press(KEY_W);
  }
  else
  {
    Keyboard.release(KEY_W);
  }

  if(down)
  {
    Keyboard.press(KEY_S);
  }
  else
  {
    Keyboard.release(KEY_S);
  }

  if(left)
  {
    Keyboard.press(KEY_A);
  }
  else
  {
    Keyboard.release(KEY_A);
  }

  if(right)
  {
    Keyboard.press(KEY_D);
  }
  else
  {
    Keyboard.release(KEY_D);
  }

  if(select)
  {
    Keyboard.press(KEY_ESC);
  }
  else
  {
    Keyboard.release(KEY_ESC );
  }

  if(start)
  {
    Keyboard.press(KEY_ENTER);
  }
  else
  {
    Keyboard.release(KEY_ENTER);
  }

  if(a)
  {
    Keyboard.press(KEY_SPACE);
  }
  else
  {
    Keyboard.release(KEY_SPACE);
  }

  if(b)
  {
    Keyboard.press(KEY_RIGHT_SHIFT);
  }
  else
  {
    Keyboard.release(KEY_RIGHT_SHIFT);
  }

  if(button_x && !button_x_state)
  {
    Keyboard.press(KEY_DOWN); 
    button_x_state = true;
  }
  else
  {
    Keyboard.release(KEY_DOWN);
    button_x_state = false;
  }

  if(button_y && !button_y_state)
  {
    Keyboard.press(KEY_UP);    
    button_y_state = true;
  }
  else
  {
    Keyboard.release(KEY_UP);
    button_y_state = false;
  }

  if(button_l && !button_l_state)
  {
    Keyboard.press(KEY_LEFT);
    button_l_state = true;
  }
  else
  {
    Keyboard.release(KEY_LEFT);
    button_l_state = false;
  }

  if(button_r && !button_r_state)
  {
    Keyboard.press(KEY_RIGHT);
    button_r_state = true;
  }
  else
  {
    Keyboard.release(KEY_RIGHT);
    button_r_state = false;
  }