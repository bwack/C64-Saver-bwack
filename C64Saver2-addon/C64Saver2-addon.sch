EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:ina219
LIBS:promicro
LIBS:C64Saver2-addon-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L INA219 U1
U 1 1 5B218B38
P 2100 4200
F 0 "U1" H 2100 5150 60  0000 C CNN
F 1 "INA219" H 1750 4250 60  0000 C CNN
F 2 "ina219:ina219" H 2200 3150 60  0001 C CNN
F 3 "" H 2200 3150 60  0000 C CNN
	1    2100 4200
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x12_Female J1
U 1 1 5B218CEF
P 2000 2550
F 0 "J1" H 2000 3150 50  0000 C CNN
F 1 "Conn_01x12_Female" H 2000 1850 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x12_Pitch2.54mm" H 2000 2550 50  0001 C CNN
F 3 "" H 2000 2550 50  0001 C CNN
	1    2000 2550
	0    -1   -1   0   
$EndComp
Text GLabel 3950 5050 1    49   Input ~ 0
9VAC1
Text GLabel 4050 5050 1    49   Input ~ 0
9VAC2
Text GLabel 4150 5050 1    49   Input ~ 0
OVERVOLTAGE
Text GLabel 4250 5050 1    49   Input ~ 0
PGATE
Text GLabel 3750 4900 1    49   Input ~ 0
GND2
$Comp
L D D1
U 1 1 5B21A217
P 7750 2250
F 0 "D1" H 7750 2350 50  0000 C CNN
F 1 "D" H 7750 2150 50  0000 C CNN
F 2 "Diodes_SMD:D_1206" H 7750 2250 50  0001 C CNN
F 3 "" H 7750 2250 50  0001 C CNN
	1    7750 2250
	-1   0    0    1   
$EndComp
Text GLabel 7400 2250 0    49   Input ~ 0
9VAC1
Text GLabel 7400 2750 0    49   Input ~ 0
9VAC2
$Comp
L CP1_Small C1
U 1 1 5B21A63F
P 8050 2500
F 0 "C1" H 8060 2570 50  0000 L CNN
F 1 "CP1_Small" H 8060 2420 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 8050 2500 50  0001 C CNN
F 3 "" H 8050 2500 50  0001 C CNN
	1    8050 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5B21A814
P 7750 2750
F 0 "#PWR01" H 7750 2500 50  0001 C CNN
F 1 "GND" H 7750 2600 50  0000 C CNN
F 2 "" H 7750 2750 50  0001 C CNN
F 3 "" H 7750 2750 50  0001 C CNN
	1    7750 2750
	1    0    0    -1  
$EndComp
Text Label 2050 2950 0    49   ~ 0
VIN-
Text Label 2050 3100 0    49   ~ 0
VIN+
$Comp
L 4N25 U5
U 1 1 5B21C898
P 8600 1700
F 0 "U5" H 8400 1900 50  0000 L CNN
F 1 "4N25" H 8600 1900 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6" H 8400 1500 50  0001 L CIN
F 3 "" H 8600 1700 50  0001 L CNN
	1    8600 1700
	1    0    0    -1  
$EndComp
$Comp
L 4N25 U6
U 1 1 5B21CB3E
P 9300 4350
F 0 "U6" H 9100 4550 50  0000 L CNN
F 1 "4N25" H 9300 4550 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6" H 9100 4150 50  0001 L CIN
F 3 "" H 9300 4350 50  0001 L CNN
	1    9300 4350
	1    0    0    -1  
$EndComp
Text GLabel 9600 4450 2    49   Input ~ 0
PGATE
Text GLabel 9600 4350 2    49   Input ~ 0
VIN-
$Comp
L ADuM1200BR U2
U 1 1 5B21CDC6
P 4850 3750
F 0 "U2" H 4500 4150 50  0000 L CNN
F 1 "ADuM1200BR" H 4800 4150 50  0000 L CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 4850 3750 50  0001 C CIN
F 3 "" H 4850 3750 50  0001 C CNN
	1    4850 3750
	1    0    0    -1  
$EndComp
$Comp
L VO615A-5 U4
U 1 1 5B21CE49
P 7600 1450
F 0 "U4" H 7600 1750 50  0000 C CNN
F 1 "VO615A-5" H 7600 1650 50  0000 C CNN
F 2 "" H 7600 1450 50  0001 C CNN
F 3 "" H 7600 1450 50  0001 C CNN
	1    7600 1450
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x07_Female J2
U 1 1 5B22BF3B
P 3950 5250
F 0 "J2" H 3950 5650 50  0000 C CNN
F 1 "Conn_01x07_Female" H 3950 4850 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x07_Pitch2.54mm" H 3950 5250 50  0001 C CNN
F 3 "" H 3950 5250 50  0001 C CNN
	1    3950 5250
	0    -1   1    0   
$EndComp
$Comp
L SW_Push SW2
U 1 1 5B22D489
P 6350 4100
F 0 "SW2" H 6400 4200 50  0000 L CNN
F 1 "SW_Push" H 6350 4040 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm_h13mm" H 6350 4300 50  0001 C CNN
F 3 "" H 6350 4300 50  0001 C CNN
	1    6350 4100
	1    0    0    -1  
$EndComp
$Comp
L SW_Push SW1
U 1 1 5B22D5E5
P 6350 3850
F 0 "SW1" H 6400 3950 50  0000 L CNN
F 1 "SW_Push" H 6350 3790 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm_h13mm" H 6350 4050 50  0001 C CNN
F 3 "" H 6350 4050 50  0001 C CNN
	1    6350 3850
	1    0    0    -1  
$EndComp
Text Label 4000 3500 0    60   ~ 0
Vin-
$Comp
L +5V #PWR02
U 1 1 5B230438
P 5500 3350
F 0 "#PWR02" H 5500 3200 50  0001 C CNN
F 1 "+5V" H 5500 3490 50  0000 C CNN
F 2 "" H 5500 3350 50  0001 C CNN
F 3 "" H 5500 3350 50  0001 C CNN
	1    5500 3350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 5B23073D
P 5450 4100
F 0 "#PWR03" H 5450 3850 50  0001 C CNN
F 1 "GND" H 5450 3950 50  0000 C CNN
F 2 "" H 5450 4100 50  0001 C CNN
F 3 "" H 5450 4100 50  0001 C CNN
	1    5450 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 5050 3850 5050
Connection ~ 3750 5050
Wire Wire Line
	1900 3300 1900 2950
Wire Wire Line
	1900 2950 2300 2950
Wire Wire Line
	2300 2950 2300 2750
Wire Wire Line
	2100 2750 2600 2750
Connection ~ 2200 2750
Connection ~ 2300 2750
Connection ~ 2400 2750
Connection ~ 2500 2750
Wire Wire Line
	2300 3300 2300 3100
Wire Wire Line
	2300 3100 1700 3100
Wire Wire Line
	1700 3100 1700 2750
Wire Wire Line
	1500 2750 2000 2750
Connection ~ 1600 2750
Connection ~ 1700 2750
Connection ~ 1800 2750
Connection ~ 1900 2750
Connection ~ 3750 4900
Wire Wire Line
	3750 4900 3750 5050
Wire Wire Line
	8050 2750 8050 2600
Wire Wire Line
	8050 2400 8050 2250
Wire Wire Line
	7900 2250 8350 2250
Wire Wire Line
	7600 2250 7400 2250
Connection ~ 8050 2250
Connection ~ 8050 2750
Wire Wire Line
	4400 3500 3800 3500
Wire Wire Line
	4400 4000 3800 4000
Wire Wire Line
	3800 4000 3800 3950
Wire Wire Line
	2800 3650 4400 3650
Wire Wire Line
	2950 3850 4400 3850
Wire Wire Line
	2950 3850 2950 3750
Wire Wire Line
	2950 3750 2800 3750
Wire Wire Line
	6850 3450 6850 3350
Wire Wire Line
	5300 4050 5300 4000
Wire Wire Line
	8550 3450 8250 3450
Wire Wire Line
	5500 3350 5500 3500
Wire Wire Line
	5500 3500 5300 3500
Wire Wire Line
	5450 4050 5450 4100
Wire Wire Line
	5300 4050 5450 4050
$Comp
L GND #PWR04
U 1 1 5B230A84
P 6550 3350
F 0 "#PWR04" H 6550 3100 50  0001 C CNN
F 1 "GND" H 6550 3200 50  0000 C CNN
F 2 "" H 6550 3350 50  0001 C CNN
F 3 "" H 6550 3350 50  0001 C CNN
	1    6550 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 3350 6550 3350
Wire Wire Line
	7400 2750 8500 2750
Wire Wire Line
	8350 2250 8350 3150
Wire Wire Line
	8350 3150 8250 3150
Wire Wire Line
	8250 3250 8500 3250
Wire Wire Line
	8500 3250 8500 2750
$Comp
L +5V #PWR05
U 1 1 5B2319FA
P 8550 3450
F 0 "#PWR05" H 8550 3300 50  0001 C CNN
F 1 "+5V" H 8550 3590 50  0000 C CNN
F 2 "" H 8550 3450 50  0001 C CNN
F 3 "" H 8550 3450 50  0001 C CNN
	1    8550 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 3550 6850 3550
Wire Wire Line
	5650 3550 5650 3650
Wire Wire Line
	5650 3650 5300 3650
Wire Wire Line
	5700 3650 6850 3650
Wire Wire Line
	5700 3650 5700 3850
Wire Wire Line
	5700 3850 5300 3850
$Comp
L Conn_01x04_Male J3
U 1 1 5B231FDF
P 6300 2700
F 0 "J3" H 6300 2900 50  0000 C CNN
F 1 "Conn_01x04_Male" H 6300 2400 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 6300 2700 50  0001 C CNN
F 3 "" H 6300 2700 50  0001 C CNN
	1    6300 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	5850 2600 5850 3650
Connection ~ 5850 3650
Wire Wire Line
	6100 2500 5750 2500
Wire Wire Line
	5750 2500 5750 3550
Connection ~ 5750 3550
$Comp
L +5V #PWR06
U 1 1 5B232213
P 6100 2700
F 0 "#PWR06" H 6100 2550 50  0001 C CNN
F 1 "+5V" H 6100 2840 50  0000 C CNN
F 2 "" H 6100 2700 50  0001 C CNN
F 3 "" H 6100 2700 50  0001 C CNN
	1    6100 2700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6100 2800 6100 2900
$Comp
L GND #PWR07
U 1 1 5B232316
P 6100 2850
F 0 "#PWR07" H 6100 2600 50  0001 C CNN
F 1 "GND" H 6100 2700 50  0000 C CNN
F 2 "" H 6100 2850 50  0001 C CNN
F 3 "" H 6100 2850 50  0001 C CNN
	1    6100 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 2600 5850 2600
Text Label 4000 4000 0    60   ~ 0
GND2
Wire Wire Line
	6550 3850 6600 3850
Wire Wire Line
	6600 3850 6600 3750
Wire Wire Line
	6600 3750 6850 3750
Wire Wire Line
	6850 3850 6650 3850
Wire Wire Line
	6650 3850 6650 4100
Wire Wire Line
	6650 4100 6550 4100
Wire Wire Line
	6150 3850 6150 4250
Connection ~ 6150 4100
$Comp
L GND #PWR08
U 1 1 5B233217
P 6150 4250
F 0 "#PWR08" H 6150 4000 50  0001 C CNN
F 1 "GND" H 6150 4100 50  0000 C CNN
F 2 "" H 6150 4250 50  0001 C CNN
F 3 "" H 6150 4250 50  0001 C CNN
	1    6150 4250
	1    0    0    -1  
$EndComp
$Comp
L R_Small R1
U 1 1 5B233376
P 8700 4250
F 0 "R1" H 8730 4270 50  0000 L CNN
F 1 "R_Small" H 8730 4210 50  0000 L CNN
F 2 "" H 8700 4250 50  0001 C CNN
F 3 "" H 8700 4250 50  0001 C CNN
	1    8700 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	9000 4250 8800 4250
Wire Wire Line
	8600 4250 8250 4250
Wire Wire Line
	9000 4450 9000 4600
$Comp
L GND #PWR09
U 1 1 5B233866
P 9000 4600
F 0 "#PWR09" H 9000 4350 50  0001 C CNN
F 1 "GND" H 9000 4450 50  0000 C CNN
F 2 "" H 9000 4600 50  0001 C CNN
F 3 "" H 9000 4600 50  0001 C CNN
	1    9000 4600
	1    0    0    -1  
$EndComp
$Comp
L ProMicro U3
U 1 1 5B263A73
P 7550 3900
F 0 "U3" H 7550 4850 60  0000 C CNN
F 1 "ProMicro" H 7550 3350 60  0000 C CNN
F 2 "promicro:ProMicro" H 7650 2850 60  0001 C CNN
F 3 "" H 7650 2850 60  0000 C CNN
	1    7550 3900
	1    0    0    -1  
$EndComp
$EndSCHEMATC
