# buttonbox

Easily configurable HID button box

Supports 32 buttons, 2 sliders and 4 axes

## Usage

- Install Platform.IO plugin to VSCode
- Open folder in VSCode as a Platform.IO project
- In `src/main.cpp` fill in the pin numbers for joystick buttons, axes and sliders. Digital pins for buttons, analog for axes and sliders. If you need a new board, check the Platform.io board identifier and add a new build option to platformio.ini file
- Upload to board
- On Windows you can best see the output by writing "gamepad" into Win search > "Set up USB game controllers" > your controller > properties
