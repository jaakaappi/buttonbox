# joystick

Easily configurable Teensy HID joystick

Supports 32 buttons, 2 sliders and 4 axes

## Usage

- Install Platform.IO plugin to VSCode
- Open folder in VSCode as a Platform.IO project
- In `src/main.cpp` fill in the pin numbers for [HID joystick](https://www.pjrc.com/teensy/td_joystick.html) buttons, axes and sliders. Digital pins for buttons, analog for axes and sliders. See [Teensy pinout](https://www.pjrc.com/teensy/pinout.html) for available pin numbers
- Upload to board
- Linked HID joystick page has instructions for seeing joystick output
