# C64 Saver v1 and v2
- Overvoltage protection for the C64 and its power brick.

Designed by BWACK 2018
CERN OPEN HARDWARE LICENSE v1.2
http://www.ohwr.org/

The KiCad and other design files are available on GitHub:
https://github.com/bwack/

All text above must be included in any redistribution

Welcome to Bwack's C64 saver designs.

The C64 Saver 2 is an open-source project intended to make overvoltage protection available and easy to make for anyone interested in using the old Commodore power brick together with the C64. The power brick is 20-30 years old and it is known for failure with overvoltage. This is caused sometimes because of broken solder joints on the regulator or the regulator itself failing.

## What has changed in v2 ?
- The design is modular.
- Spike protection. Handles hotswapping and switch bouncing better.
- It is much much easier and faster to make. Most people can make it, and not just me who don't want to do the v1 anymore anyway. Insane how much time that took god damnit.

## The C64 Saver 2 (base board)
The base board is all you need for overvoltage protection. Through hole parts except for the mosfet, but it is large and easy to solder.

## The C64 Saver 2 addon board
The C64 saver addon board is a hat for the base board and adds software control, instrumentation on both ac and dc side, and an optional 128x32 OLED display. The 9VAC and 5VDC are fully isolated. Software control and instrumentation is useful if you are repairing C64s. You can set the output to shut down in case of an overcurrent condition. If an overvoltage happens you can configure the saver to auto reset or keep the power from comming back on again. There are several reasons why you might want this. C64 PSUs that need service, the capacitors are dry and the 5VDC has an AC component on it. The saver would normally just go on and off at 100Hz. The software control can detect this. The other problem is if the computer has a faulty chip that cause massive current draw on the 5V. The fuse might not blow because it is not enough, then you can configure the saver cut if you desire.

## The old design
I have decided to release my older C64 Saver v1. The board that fits inside a connector. Time and skill is super high on this product so be warned ! (SMD 0603, solder blob connections, tight spaces and short circuit hazards).

## Changelog:
- Rev 2.0 (in development)
  - New design.
  - Protected sensitive parts
  - C64 saver 2 addon board
