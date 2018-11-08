SSD1306xLED - Library/Driver for the SSD1306 based OLED/PLED 128x64 displays

This is a testing project.

This program demonstrates the use of the SSD1306xLED library.

To build the project, type:
	$ make

To program the binary into the microcontroller, type:
   $ make program

Alternatively, to program the binary, type:
	$ avrdude -c usbasp -p t85 -U flash:w:"main.hex":a

To clean up files left out from previous builds, type:
   $ make clean


