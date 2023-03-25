# Firmware for the addon board

Build source code with avr-gcc.
This section is under construction.

## Programming
Program the addon board using USBasp or other AVR programming ISP device.
Arduino as ISP does also work. The ISP header has 2mm pitch, and the pinout is standard 2x3 way ISP pinout. You program the board with the main.hex file. It is found under the releases tab.

## Developing
To build the project you need to download the C64-saver-bwack repository from github.
From there you will get the sources for the addon board.
Download the WinAVR (windows), or avr-gcc (linux, mac). The avrdude version might not be
compatible with your USBasp. Download arduino also, and copy avrdude from it and into your WinAVR bin folder.

In the src folder you can clean, build and program.
- make clean
- make
- make install

## contributing to the Github repository
Fork the project and make your changes. Make sure you "make clean" before push to the repo. We only want source code in the repo. Have fun!
