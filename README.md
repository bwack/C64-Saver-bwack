C64 Saver v1 and v2
- Overvoltage protection for the C64 and its power brick.

Designed by BWACK 2018
CERN OPEN HARDWARE LICENSE v1.2
http://www.ohwr.org/

The KiCad and other design files are available on GitHub:
https://github.com/bwack/

All text above must be included in any redistribution

# Bwack's C64 saver designs.

The C64 Saver 2 is an open-source project intended to make overvoltage protection available and easy to make for anyone interested in using the old Commodore power brick together with the C64. The power brick is 20-30 years old and it is known for failure with overvoltage. This is caused sometimes because of broken solder joints on the regulator or the regulator itself failing.

## What has changed in v2 ?
- The design is modular.
- Spike protection. Handles hotswapping and switch bouncing better.
- It is much much easier and faster to make. Most people can make it, and not just me who don't want to do the v1 anymore anyway. Insane how much time that took god damnit.

## The C64 Saver 2 (base board)
The base board is all you need for overvoltage protection. Through hole parts except for the mosfet, but it is large and easy to solder. The board shape fits the Hammond 1551g project case.
* Note: For the C64 Saver 2 work standalone (without addon board), J2 needs to be bridged and so does J4. This is done by a solder blob or a link where you see the power path is "broken" in the middle of the pinheaders. This is intended to allow sensing on the addon board. The three pinheaders are not needed on the standalone version.

 ![C64 Saver 2 3D](C64%20Saver%202/C64Saver2_3D.png)
 ![C64 Saver 2 3D_bottom](C64%20Saver%202/C64Saver2_3D_bottom.png)

## The C64 Saver 2 addon board
The C64 saver addon board is a hat for the base board and adds software control, instrumentation on both ac and dc side, and an optional 128x32 OLED display. The aim for this project is to make a tool for C64 repairers. The 9VAC and 5VDC are fully isolated. Software control and instrumentation is useful if you are repairing C64s. You can set the output to shut down in case of an overcurrent condition. If an overvoltage happens you can configure the saver to auto reset or keep the power from comming back on again. There are several reasons why you might want this. C64 PSUs that need service, the capacitors are dry and the 5VDC has an AC component on it. The saver would normally just go on and off at 100Hz. The software control can detect this. The other problem is if the computer has a faulty chip that cause massive current draw on the 5V. The fuse might not blow because it is not enough, then you can configure the saver cut if you desire. I'm not gonna lie. This is my pet project, and the cost has not been a topic on my mind.

![C64 saver addon_board](addon%20board/C64Saver2-addon.kicad_pcb_1_3.png)

Youtube video of me testing the addon board installed on the C64 Saver 2. Note that it is not necessary to have an addon board for the C64 Saver 2 to work, however some pins need to be shorted for the C64 Saver 2 to work standalone.

[![Testing_the_addon_board ](http://img.youtube.com/vi/oYrapS5jUx8/0.jpg)](http://www.youtube.com/watch?v=oYrapS5jUx8)

## The C64 Saver 2 relay hold board

The addon board above are for many hard to make. I was thinking, what about making a board that doesn't need to be programmed, that can cut 9VAC, and optionally keep the outputs disabled even if the fault goes away. This circuit is it.

![C64 saver relay hold](relayhold%20board/relayhold%20board%203D.png)


## The old design
I have decided to release my older C64 Saver v1. The board that fits inside a connector. Time and skill is super high on this product so be warned ! (SMD 0603, solder blob connections, tight spaces and short circuit hazards).

## Gerbers
If you are looking for gerbers, click the releases tab. There you will find a zip file of gerber for each release.

# BOM

## C64 Saver 2.5 SMD

| pcs | ref                 | value         | descr                                          | mouser part no     | comment  |
| --- | ------------------- | ------------- | ---------------------------------------------- | ------------------ | -------- |
| 1   | C1                  | 47uF/16V      | Electrolytic Cap SMD 6.3 x 5.4 mm              | 647-UWJ1C470MCL1   |          |
| 2   | D1,D2               | BZY55B6V8     | Zener SMD 0805                                 | 821-BZY55B6V8RBG   |          |
| 2   | J2,J4               | Conn 1x8      | Multicontact Female Straight 1x8 way P2.54mm   |                    | optional |
| 1   | J5                  | Conn 1x4      | Multicontact Female Straight 1x4 way P2.54mm   |                    | optional |
| 1   | LED1                | LED_RED_3mm   | LED 3mm RED Diffused Throughole                | 859-LTL-4211N      |          |
| 1   | LED2                | LED_GREEN_3mm | LED 3mm RED Diffused Throughole                | 859-LTL-4231N      |          |
| 1   | Q1                  | 2n7002        | Small signal transistor SOT-23 N 60V           | 771-2N7002NXAKR    |          |
| 1   | Q2                  | IRFR5305P     | MOSFET P-Channel SMD DPAK                      | 942-IRFR5305TRLPBF |          |
| 2   | R1,R6               | 3k9           | Resistor SMD 0805                              | 667-ERJ-6ENF3901V  |          |
| 6   | R2,R3,R5,R9,R10,R11 | 3k3           | Resistor SMD 0805                              | 667-ERJ-6GEYJ332V  |          |
| 1   | R4                  | 330k          | Resistor SMD 0805                              | 667-ERJ-6GEYJ334V  |          |
| 1   | R7                  | 33k           | Resistor SMD 0805                              | 652-CR0805JW-333ELF |          |
| 1   | R8                  | 82k           | Resistor SMD 0805                              | 667-ERJ-6ENF8202V  |          |
| 1   | U1                  | TL431DBZ      | Regulator with voltage reference SOT-23        | 595-TL431QDBZR     |          |

## C64 Saver 2.4 Throughhole

| pcs | ref      | value     | descr                                          | elfa#      |
| --- | -------- | --------- | ---------------------------------------------- | ---------- |
| 3   | R2,R3,R5 | 3k3       | Resistor Axial DIN0204 L3.6mm x D1.6mm         | 160-05-557 |
| 2   | R1,R6    | 3k9       | Resistor Axial DIN0204 L3.6mm x D1.6mm         | 160-05-565 |
| 1   | R4       | 330k      | Resistor Axial DIN0204 L3.6mm x D1.6mm         | 160-95-608 |
| 1   | R7       | 33k       | Resistor Axial DIN0204 L3.6mm x D1.6mm         |            |
| 1   | R8       | 82k       | Resistor Axial DIN0204 L3.6mm x D1.6mm         |            |
| 1   | C1       | 47uF/16V  | Cap THT CP_Radial_D6.3mm_P2.50mm               | 167-19-512 |
| 1   | D1       | TL431     | Regulator with voltage reference TO-92 package | 173-13-703 |
| 2   | D2,D3    | 6V8       | Zener diode DO-35 SOD27 P7.62mm Horizontal     | 300-30-855 |
| 1   | Q1       | 2n7000    | Small signal transistor TO-92 N 60V            | 171-03-018 |
| 1   | Q2       | IRFR5305P | MOSFET P SMD DPAK                              | 171-17-294 |
| 2   | J2,J4    | Conn 1x8  | Multicontact Female Straight 1x8 way P2.54mm   | 300-93-668 |
| 1   | J5       | Conn 1x4  | Multicontact Female Straight 1x4 way P2.54mm   | 300-93-664 |

# Changelog:

- C64 Saver 2.5 (SMD) ()
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
  - 4k7 I2C pullups.

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
  - tested bodged v2.2 prototype, working!

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
