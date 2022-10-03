#include <Arduino.h>

// Button pins, up to 32. Number of the button is place in array + 1
const int BUTTONS[] = {0};
// Joystick sliders, up to 2
const int SLIDERS[] = {};
// Joystick axes analog pins in order: X, Y, Z, Z rotate
const int AXES[] = {A9};

void setup()
{
  Serial.begin(9600);

  for (size_t i = 0; i < sizeof(BUTTONS) / sizeof(BUTTONS[0]); i++)
  {
    pinMode(BUTTONS[i], INPUT_PULLUP);
  }
}

void update_buttons()
{
  for (size_t i = 0; i < sizeof(BUTTONS) / sizeof(BUTTONS[0]); i++)
  {
    boolean pressed = !digitalRead(BUTTONS[i]); // Digital inputs have a pullup resistor => pressed = 0

    Serial.println("Button " + String(i + 1) + " " + String(pressed));

    Joystick.button(i + 1, pressed);
  }
}

void update_sliders()
{
  for (size_t i = 0; i < sizeof(SLIDERS) / sizeof(SLIDERS[0]); i++)
  {
    int value = analogRead(SLIDERS[i]);
    Serial.println("Slider " + String(i + 1) + " " + String(value));
    i == 0 ? Joystick.sliderLeft(value) : Joystick.sliderRight(value);
  }
}

void update_axes()
{
  for (size_t i = 0; i < sizeof(AXES) / sizeof(AXES[0]); i++)
  {
    int value = analogRead(AXES[i]);
    Serial.println("Axis " + String(i + 1) + " " + String(value));
    switch (i)
    {
    case 0:
      Joystick.X(value);
      break;
    case 1:
      Joystick.Y(value);
      break;
    case 2:
      Joystick.Z(value);
      break;
    case 3:
      Joystick.Zrotate(value);
      break;

    default:
      break;
    }
  }
}

void loop()
{
  update_buttons();
  update_sliders();
  update_axes();
  // delay(1000);
}