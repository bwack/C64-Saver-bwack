C64 Saver v1 and v2
- Overvoltage protection for the C64 and its power brick.

Designed by BWACK 2018
CERN OPEN HARDWARE LICENSE v1.2
http://www.ohwr.org/

The KiCad and other design files are available on GitHub:
https://github.com/bwack/

All text above must be included in any redistribution

# Warning: latest version of the savers are not tested.

# Bwack's C64 saver designs.

The C64 Saver 2 is an open-source project intended to make overvoltage protection available and easy to make for anyone interested in using the old Commodore power brick together with the C64. The power brick is 30-40 years old, and it is known for failure with overvoltage. This is caused sometimes because of broken solder joints on the regulator or the regulator itself failing.

## What has changed in v2 ?
- The design is modular.
- Spike protection. Handles hotswapping and switch bouncing better.
- It is much much easier and faster to make. Most people can make it!

## The base board (C64 Saver 2 SMD or Throughhole)
The base board is all you need for overvoltage protection. Through hole parts except for the mosfet, but it is large and easy to solder, no special tools needed other than your solder iron. The board shape fits the Hammond 1551g project case.
* Note: You need to bridge pin 4 and 5 in J2 and pin 4 and 5 in J4 if you are not using the base board in combination with the addon board or the relay board. The reason for this is that, with the addon board, we need to route the current through a sensing circuit. When the addon board is not used, we need to route it directly to the mosfet and terminals.

 ![C64 Saver 2 3D](C64%20Saver%20Throughhole%202.6/C64Saver2_3D.png)
 ![C64 Saver 2 3D_bottom](C64%20Saver%20Throughhole%202.6/C64Saver2_3D_bottom.png)
 
There is also a SMD version for those who like to reflow soldering.

## The addon board
The C64 saver addon board is a hat for the base board, and adds software control, instrumentation on both ac and dc side, and an optional 128x32 OLED display. The aim for this project is to make a tool for C64 repairers. The 9VAC and 5VDC are fully isolated. Software control and instrumentation is useful if you are repairing C64s. You can set the output to shut down in case of an overcurrent condition. If an overvoltage happens you can configure the saver to auto reset or keep the power from comming back on again. There are several reasons why you might want this. C64 PSUs that need service, the capacitors are dry and the 5VDC has an AC component on it. The saver would normally just go on and off at 100Hz. The software control can detect this. The other problem is if the computer has a faulty chip that cause massive current draw on the 5V. The fuse might not blow because it is not enough, then you can configure the saver cut if you desire. I'm not gonna lie. This is my pet project, and the cost has not been a topic on my mind.

The C64 Saver Addon Board 1.4:

![C64 saver addon_board](addon%20board%201.4/C64Saver2-addon-1.4_3Dfront.png)

Youtube video of me testing the addon board installed on the C64 Saver 2.

[![YouTube: Testing_the_addon_board ](http://img.youtube.com/vi/oYrapS5jUx8/0.jpg)](http://www.youtube.com/watch?v=oYrapS5jUx8)

The relay and hold board is archived in the oldfiles folder.

## C64 Saver OCP

OCP, not robocop, but overcurrent protection. Is a new circuit that I'm working on. It has three LEDs and a button. The overvoltage protection circuit is the same as before. The overcurrent will light the yellow led and keep it lit and keep the output OFF after an overcurrent event.

## The old design
I have decided to release my older C64 Saver v1. The board that fits inside a connector. Time and skill is super high on this product so be warned ! (SMD 0603, solder blob connections, tight spaces and short circuit hazards).

## Gerbers
If you are looking for gerbers, click the releases tab. There you will find a zip file of gerber for each release.

# BOM
All bill of materials (BOM) are moved into the respective project folders. I have added digikey etc order no. in the parts in the schematics such that they will show up in the interactive boms.

Here are the interactive BOMs:

[ibom for C64 Saver Throughole 2.6](https://htmlpreview.github.io/?https://github.com/bwack/C64-Saver-bwack/blob/master/C64%20Saver%20Throughhole%202.6/bom/ibom.html)

[ibom for C64 Saver SMD 2.6](https://htmlpreview.github.io/?https://github.com/bwack/C64-Saver-bwack/blob/master/C64%20Saver%20SMD%202.6/bom/ibom.html)

[ibom for C64 Addon Board 1.4](https://htmlpreview.github.io/?https://github.com/bwack/C64-Saver-bwack/blob/master/addon%20board%201.4/bom/ibom.html)

[ibom for C64 Saver OCP 0.1](https://htmlpreview.github.io/?https://github.com/bwack/C64-Saver-bwack/blob/master/C64%20Saver%20OCP%200.1/bom/ibom.html)



# Changelog:

- C64 Saver 2.6 (THT+SMD) and Addon Board 1.4 (2023-04-02)
  - Replaced 7n2002 with BC547/BC847 to fix the tolerance issues.
  - Throughhole and SMD: same version numbers, same circuits, same reference numbers.
  - Red LED is switched by TL431 and Green by BC547/BC847.
  - Added LEDs to the Throughhole version. It was a challenge.
  - Fix: The Addon Board 1.3 had incorrect pinout for the 5V reg.
  - I never tested the Addon Board 1.3, but thanks to Retroisten who sent.
  me images and advicing me about he pinout, I'm very happy about it. He also
  showed me that it does work, with the regulator hacked in.  In this version 1.4
  it is working.

- C64 Saver 2.5 (SMD) (2020-09-13)
  - Added fault LED and power LED
  - 0805 SMD resistors
  - SOT23-5 TL431 and NMOS

- RelayHold 0.2 (2019-08-25)
  - Initial release
  - All through-hole parts.

- Addon Board 1.3 (2019-05-24)
  - Changed optocoupler footprint to more common SOIC-4_4.55x2.6mm_P1.27mm
  - Larger 5V regulator on 9vac side for less heat
  - replaced 100uF tantalum with 3x 47uF 1206 MLCC
  - kicad 5.1.0 project

- Addon Board 1.2 (2018-11-11)
  - Swapped HOLD_ with SENSE_VAC on the MCU. SENSE_VAC needs ADC.
  - Correct the mixed up SDA and SCL.
  - 5V supply to the 5V section is moved to VIN+ (before the shunt).
    To not pull power through the sensing resistor.
  - 4k7 I2C pullups.https://htmlpreview.github.io/?https://github.com/bwack/C64-Saver-bwack/blob/develop/C64%20Saver%20Throughhole%202.6/bom/ibom.html

- C64 Saver 2.4 (2018-09-23)
  - Support lower Vth on Q1. Resistor divider R7 and R8.
  - Remove C2 to make room for resistor divider.
  - Changed R5 to 3k3 to reduce BOM size.
  - New layout and routing.

- Addon Board 1.1 (2018-09-23)
  - ATtiny85 is a 8S2 package and two mm wider than SOIC8.
  - Read overvoltage signal on reset pin using ADC. Added voltage divider.
  - Replace MCP1700 with MCP1703. Supporting higher Vin_max

- C64 Saver 2.3 (2018-08-18)
  - Q1 2N7002 pin 1 and 2 rotated
  - Q2 Reversed drain and source
  - Increased pullup on Q1 drain.
  - Repurposed R5 as pullup for Q1 drain.
  - tested bodged v2.2 prototype, wohttps://htmlpreview.github.io/?https://github.com/bwack/C64-Saver-bwack/blob/develop/C64%20Saver%20Throughhole%202.6/bom/ibom.htmlrking!

- C64 Saver 2.2 (2018-08-16)
  - R1 was rotated.

- C64 Saver 2.1 & Addon 1.0 (2018-07-23)
  - 5x 9VAC pins. 9VAC1 current (4x) + 9VAC2.
  - Moved GND pin.
  - Changed board size to fit Hammond1551g
  - C64 Saver board:
    - Smaller throughole resistors
    - Moved C1 closer to input circuits.
  - Addon board:
    - VAC sense circuit with voltage divider.
    - 5V regulator on VCC pin. RAW pin disconnected.
    - Pullups on I2C busses.
    - SSOP-4 optocoupler packages
    - Another regulator on the 5V side to protect the iso1541 and ina219.

- C64 Saver 2.0beta & Addon 1.0beta (2018-07-02)
  - New design.
  - Protected sensitive parts.
  - baseboard: throughhole parts.
  - C64 saver 2 addon board.
  - problem: has conflicting pinouts.
