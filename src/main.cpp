#include <Arduino.h>
#include "Joystick.h"

// Button pins, up to 32. Number of the button is place in array, 0 => 1
const int BUTTONS[] = {PD2, PD3, PD6};

// Pins for switches which will work like buttons, pressing the button for SWITCH_BUTTON_DELAY after being flipped
// Swiotch buttons will get numbers after normal buttons, so BUTTONS.length + switch button index
const int SWITCH_BUTTON_DELAY = 500;
const int SWITCH_BUTTONS[] = {PD4, PD5};

// Joystick sliders, up to 2
const int SLIDERS[] = {};

// Joystick axes analog pins in order: X, Y, Z, Z rotate
const int AXES[] = {};

Joystick_ Joystick(0x06,
                   JOYSTICK_TYPE_JOYSTICK, 32, 0,
                   true, true, true, true, false, false,
                   true, true, false, false, false);

int *switch_button_delays;
bool *switch_button_states;

void update_buttons()
{
  for (size_t i = 0; i < sizeof(BUTTONS) / sizeof(BUTTONS[0]); i++)
  {
    boolean pressed = !digitalRead(BUTTONS[i]); // Digital inputs have a pullup resistor => pressed = 0
    Joystick.setButton(i, pressed);
  }
}

void update_sliders()
{
  for (size_t i = 0; i < sizeof(SLIDERS) / sizeof(SLIDERS[0]); i++)
  {
    int value = analogRead(SLIDERS[i]);
    // Serial.println("Slider " + String(i + 1) + " " + String(value));
    i == 0 ? Joystick.setThrottle(value) : Joystick.setRudder(value);
  }
}

void update_axes()
{
  for (size_t i = 0; i < sizeof(AXES) / sizeof(AXES[0]); i++)
  {
    int value = analogRead(AXES[i]);
    // Serial.println("Axis " + String(i + 1) + " " + String(value));
    switch (i)
    {
    case 0:
      Joystick.setXAxis(value);
      break;
    case 1:
      Joystick.setYAxis(value);
      break;
    case 2:
      Joystick.setZAxis(value);
      break;
    case 3:
      Joystick.setRxAxis(value);
      break;

    default:
      break;
    }
  }
}

void update_switch_buttons()
{
  const int BUTTONS_LENGTH = sizeof(BUTTONS) / sizeof(BUTTONS[0]);

  for (size_t i = 0; i < sizeof(SWITCH_BUTTONS) / sizeof(SWITCH_BUTTONS[0]); i++)
  {
    bool pressed = digitalRead(SWITCH_BUTTONS[i]);
    if (switch_button_delays[i] != 0)
    {
      if (millis() >= switch_button_delays[i])
      {
        switch_button_delays[i] = 0;
        Joystick.setButton(BUTTONS_LENGTH + i, false);
      }
    }
    if (pressed != switch_button_states[i])
    {
      switch_button_states[i] = pressed;
      switch_button_delays[i] = millis() + SWITCH_BUTTON_DELAY;
      Joystick.setButton(BUTTONS_LENGTH + i, true);
    }
  }
}

void setup()
{
  Joystick.setXAxisRange(-127, 127);
  Joystick.setYAxisRange(-127, 127);
  Joystick.setZAxisRange(-127, 127);
  Joystick.setRxAxisRange(-127, 127);
  Joystick.setThrottleRange(0, 255);
  Joystick.setRudderRange(0, 255);

  Joystick.begin();

  for (size_t i = 0; i < sizeof(BUTTONS) / sizeof(BUTTONS[0]); i++)
  {
    pinMode(BUTTONS[i], INPUT_PULLUP);
  }

  for (size_t i = 0; i < sizeof(SWITCH_BUTTONS) / sizeof(SWITCH_BUTTONS[0]); i++)
  {
    pinMode(SWITCH_BUTTONS[i], INPUT_PULLUP);
  }

  switch_button_delays = new int[sizeof(SWITCH_BUTTONS) / sizeof(SWITCH_BUTTONS[0])];
  switch_button_states = new bool[sizeof(SWITCH_BUTTONS) / sizeof(SWITCH_BUTTONS[0])];

  for (size_t i = 0; i < sizeof(switch_button_delays) / sizeof(switch_button_delays[0]); i++)
  {
    switch_button_delays[i] = 0;
  }

  for (size_t i = 0; i < sizeof(switch_button_states) / sizeof(switch_button_states[0]); i++)
  {
    switch_button_states[i] = false;
  }
}

void loop()
{
  update_buttons();
  update_switch_buttons();
  update_sliders();
  update_axes();
}
