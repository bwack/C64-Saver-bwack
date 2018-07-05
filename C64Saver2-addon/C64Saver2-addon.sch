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
LIBS:iso1541d
LIBS:acs712
LIBS:mechanical
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
L Conn_01x12_Female J1
U 1 1 5B218CEF
P 1900 2600
F 0 "J1" H 1900 3200 50  0000 C CNN
F 1 "Conn_01x12_Female" H 1900 1900 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x12_Pitch2.54mm" H 1900 2600 50  0001 C CNN
F 3 "" H 1900 2600 50  0001 C CNN
	1    1900 2600
	0    -1   -1   0   
$EndComp
Text GLabel 2750 6700 1    49   Input ~ 0
OVERVOLTAGE
Text GLabel 2850 6700 1    49   Input ~ 0
PGATE
Text GLabel 1400 2800 3    49   Input ~ 0
GND2
$Comp
L D D1
U 1 1 5B21A217
P 4450 1950
F 0 "D1" H 4450 2050 50  0000 C CNN
F 1 "D" H 4450 1850 50  0000 C CNN
F 2 "Diodes_SMD:D_SOD-123" H 4450 1950 50  0001 C CNN
F 3 "" H 4450 1950 50  0001 C CNN
	1    4450 1950
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5B21A814
P 8750 3750
F 0 "#PWR01" H 8750 3500 50  0001 C CNN
F 1 "GND" H 8750 3600 50  0000 C CNN
F 2 "" H 8750 3750 50  0001 C CNN
F 3 "" H 8750 3750 50  0001 C CNN
	1    8750 3750
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x07_Female J2
U 1 1 5B22BF3B
P 2550 6900
F 0 "J2" H 2550 7300 50  0000 C CNN
F 1 "Conn_01x07_Female" H 2550 6500 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x07_Pitch2.54mm" H 2550 6900 50  0001 C CNN
F 3 "" H 2550 6900 50  0001 C CNN
	1    2550 6900
	0    -1   1    0   
$EndComp
$Comp
L SW_Push SW2
U 1 1 5B22D489
P 6350 4550
F 0 "SW2" H 6400 4650 50  0000 L CNN
F 1 "SW_Push" H 6350 4490 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm_h13mm" H 6350 4750 50  0001 C CNN
F 3 "" H 6350 4750 50  0001 C CNN
	1    6350 4550
	1    0    0    -1  
$EndComp
$Comp
L SW_Push SW1
U 1 1 5B22D5E5
P 6350 4300
F 0 "SW1" H 6400 4400 50  0000 L CNN
F 1 "SW_Push" H 6350 4240 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm_h13mm" H 6350 4500 50  0001 C CNN
F 3 "" H 6350 4500 50  0001 C CNN
	1    6350 4300
	1    0    0    -1  
$EndComp
Text Label 4000 3950 0    60   ~ 0
Vin-
$Comp
L +5V #PWR02
U 1 1 5B230438
P 5500 3800
F 0 "#PWR02" H 5500 3650 50  0001 C CNN
F 1 "+5V" H 5500 3940 50  0000 C CNN
F 2 "" H 5500 3800 50  0001 C CNN
F 3 "" H 5500 3800 50  0001 C CNN
	1    5500 3800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 5B23073D
P 5450 4550
F 0 "#PWR03" H 5450 4300 50  0001 C CNN
F 1 "GND" H 5450 4400 50  0000 C CNN
F 2 "" H 5450 4550 50  0001 C CNN
F 3 "" H 5450 4550 50  0001 C CNN
	1    5450 4550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5B230A84
P 6550 3800
F 0 "#PWR04" H 6550 3550 50  0001 C CNN
F 1 "GND" H 6550 3650 50  0000 C CNN
F 2 "" H 6550 3800 50  0001 C CNN
F 3 "" H 6550 3800 50  0001 C CNN
	1    6550 3800
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR05
U 1 1 5B2319FA
P 8550 3900
F 0 "#PWR05" H 8550 3750 50  0001 C CNN
F 1 "+5V" H 8550 4040 50  0000 C CNN
F 2 "" H 8550 3900 50  0001 C CNN
F 3 "" H 8550 3900 50  0001 C CNN
	1    8550 3900
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x04_Male J3
U 1 1 5B231FDF
P 6350 3300
F 0 "J3" H 6350 3500 50  0000 C CNN
F 1 "OLED_128x32_Conn_01x04_Male" H 6350 3000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 6350 3300 50  0001 C CNN
F 3 "" H 6350 3300 50  0001 C CNN
	1    6350 3300
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR06
U 1 1 5B232213
P 6150 3300
F 0 "#PWR06" H 6150 3150 50  0001 C CNN
F 1 "+5V" H 6150 3440 50  0000 C CNN
F 2 "" H 6150 3300 50  0001 C CNN
F 3 "" H 6150 3300 50  0001 C CNN
	1    6150 3300
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR07
U 1 1 5B232316
P 6150 3450
F 0 "#PWR07" H 6150 3200 50  0001 C CNN
F 1 "GND" H 6150 3300 50  0000 C CNN
F 2 "" H 6150 3450 50  0001 C CNN
F 3 "" H 6150 3450 50  0001 C CNN
	1    6150 3450
	1    0    0    -1  
$EndComp
Text Label 4000 4450 0    60   ~ 0
GND2
$Comp
L GND #PWR08
U 1 1 5B233217
P 6150 4700
F 0 "#PWR08" H 6150 4450 50  0001 C CNN
F 1 "GND" H 6150 4550 50  0000 C CNN
F 2 "" H 6150 4700 50  0001 C CNN
F 3 "" H 6150 4700 50  0001 C CNN
	1    6150 4700
	1    0    0    -1  
$EndComp
$Comp
L R_Small R1
U 1 1 5B233376
P 8700 4700
F 0 "R1" V 8650 4500 50  0000 L CNN
F 1 "560" V 8700 4650 39  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 8700 4700 50  0001 C CNN
F 3 "" H 8700 4700 50  0001 C CNN
	1    8700 4700
	0    1    1    0   
$EndComp
$Comp
L ProMicro U3
U 1 1 5B263A73
P 7550 4350
F 0 "U3" H 7550 5300 60  0000 C CNN
F 1 "ProMicro" H 7550 3800 60  0000 C CNN
F 2 "promicro:ProMicro" H 7650 3300 60  0001 C CNN
F 3 "" H 7650 3300 60  0000 C CNN
	1    7550 4350
	1    0    0    -1  
$EndComp
$Comp
L INA219xIDR-SOIC U1
U 1 1 5B268A1F
P 1900 4450
F 0 "U1" H 1650 4950 50  0000 L CNN
F 1 "INA219xIDR-SOIC" H 2150 4950 50  0000 L CNN
F 2 "SMD_Packages:SOIC-8-N" H 2850 3900 50  0001 C CNN
F 3 "" H 2000 4100 50  0000 C CNN
	1    1900 4450
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5B26A16A
P 1900 3200
F 0 "R2" V 1980 3200 50  0000 C CNN
F 1 "0R1" V 1900 3200 50  0000 C CNN
F 2 "Resistors_SMD:R_2010_HandSoldering" V 1830 3200 50  0001 C CNN
F 3 "" H 1900 3200 50  0001 C CNN
	1    1900 3200
	0    1    1    0   
$EndComp
$Comp
L C C2
U 1 1 5B26A790
P 1350 4700
F 0 "C2" H 1375 4800 50  0000 L CNN
F 1 "100n" H 1375 4600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1388 4550 50  0001 C CNN
F 3 "" H 1350 4700 50  0001 C CNN
	1    1350 4700
	1    0    0    -1  
$EndComp
Text GLabel 1150 4900 0    49   Input ~ 0
GND2
$Comp
L GND #PWR09
U 1 1 5B26DFD3
P 5250 5300
F 0 "#PWR09" H 5250 5050 50  0001 C CNN
F 1 "GND" H 5250 5150 50  0000 C CNN
F 2 "" H 5250 5300 50  0001 C CNN
F 3 "" H 5250 5300 50  0001 C CNN
	1    5250 5300
	1    0    0    -1  
$EndComp
Text GLabel 4500 5050 0    49   Input ~ 0
VIN-
Text GLabel 4550 5250 0    49   Input ~ 0
PGATE
Text Label 5300 5050 0    60   ~ 0
HOLD
$Comp
L R_Small R3
U 1 1 5B26FC73
P 4400 5800
F 0 "R3" V 4300 5700 50  0000 L CNN
F 1 "560" V 4400 5750 39  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 4400 5800 50  0001 C CNN
F 3 "" H 4400 5800 50  0001 C CNN
	1    4400 5800
	0    1    1    0   
$EndComp
$Comp
L GND #PWR010
U 1 1 5B270566
P 5200 6000
F 0 "#PWR010" H 5200 5750 50  0001 C CNN
F 1 "GND" H 5200 5850 50  0000 C CNN
F 2 "" H 5200 6000 50  0001 C CNN
F 3 "" H 5200 6000 50  0001 C CNN
	1    5200 6000
	1    0    0    -1  
$EndComp
Text Label 5300 5800 0    60   ~ 0
#OVERVOLTAGE
$Comp
L ISO1541D U2
U 1 1 5B26AA8D
P 4850 4200
F 0 "U2" H 4500 4600 50  0000 L CNN
F 1 "ISO1541D" H 4750 4600 50  0000 L CNN
F 2 "SMD_Packages:SOIC-8-N" H 4950 3800 50  0001 C CIN
F 3 "" H 4850 4200 50  0001 C CNN
	1    4850 4200
	-1   0    0    -1  
$EndComp
Text Label 4000 4100 0    60   ~ 0
SDA2
Text Label 4000 4300 0    60   ~ 0
SCL2
Text Label 5350 4100 0    60   ~ 0
SDA1
Text Label 5350 4300 0    60   ~ 0
SCL1
Text GLabel 4500 6000 0    49   Input ~ 0
OVERVOLTAGE
Text GLabel 4200 5800 0    49   Input ~ 0
VIN-
$Comp
L R_Small R4
U 1 1 5B26E78A
P 2950 5200
F 0 "R4" V 3000 5000 50  0000 L CNN
F 1 "10K" V 2950 5150 39  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 2950 5200 50  0001 C CNN
F 3 "" H 2950 5200 50  0001 C CNN
	1    2950 5200
	-1   0    0    1   
$EndComp
Text Label 1700 3050 1    60   ~ 0
VIN+
Text Label 2100 3050 1    60   ~ 0
VIN-
$Comp
L R_Small R5
U 1 1 5B296F2B
P 9950 4150
F 0 "R5" V 9850 4050 50  0000 L CNN
F 1 "560" V 9950 4100 39  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 9950 4150 50  0001 C CNN
F 3 "" H 9950 4150 50  0001 C CNN
	1    9950 4150
	-1   0    0    1   
$EndComp
$Comp
L R_Small R6
U 1 1 5B2970CF
P 9950 4450
F 0 "R6" V 9850 4350 50  0000 L CNN
F 1 "560" V 9950 4400 39  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 9950 4450 50  0001 C CNN
F 3 "" H 9950 4450 50  0001 C CNN
	1    9950 4450
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR011
U 1 1 5B297124
P 9950 3850
F 0 "#PWR011" H 9950 3700 50  0001 C CNN
F 1 "+5V" H 9950 3990 50  0000 C CNN
F 2 "" H 9950 3850 50  0001 C CNN
F 3 "" H 9950 3850 50  0001 C CNN
	1    9950 3850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 5B297405
P 9950 4750
F 0 "#PWR012" H 9950 4500 50  0001 C CNN
F 1 "GND" H 9950 4600 50  0000 C CNN
F 2 "" H 9950 4750 50  0001 C CNN
F 3 "" H 9950 4750 50  0001 C CNN
	1    9950 4750
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 5B297EAD
P 10550 4300
F 0 "C5" H 10575 4400 50  0000 L CNN
F 1 "1u" H 10575 4200 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 10588 4150 50  0001 C CNN
F 3 "" H 10550 4300 50  0001 C CNN
	1    10550 4300
	0    1    1    0   
$EndComp
$Comp
L R_Small R8
U 1 1 5B29A6ED
P 10200 4300
F 0 "R8" V 10100 4200 50  0000 L CNN
F 1 "560" V 10200 4250 39  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 10200 4300 50  0001 C CNN
F 3 "" H 10200 4300 50  0001 C CNN
	1    10200 4300
	0    -1   -1   0   
$EndComp
$Comp
L ACS712 U6
U 1 1 5B2AC0F1
P 7550 1050
F 0 "U6" H 7550 1350 60  0000 C CNN
F 1 "ACS712" H 7550 700 60  0000 C CNN
F 2 "SMD_Packages:SOIC-8-N" H 7550 1050 60  0001 C CNN
F 3 "" H 7550 1050 60  0001 C CNN
	1    7550 1050
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR013
U 1 1 5B2ADC33
P 8200 900
F 0 "#PWR013" H 8200 750 50  0001 C CNN
F 1 "+5V" H 8200 1040 50  0000 C CNN
F 2 "" H 8200 900 50  0001 C CNN
F 3 "" H 8200 900 50  0001 C CNN
	1    8200 900 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 5B2ADC86
P 8200 1450
F 0 "#PWR014" H 8200 1200 50  0001 C CNN
F 1 "GND" H 8200 1300 50  0000 C CNN
F 2 "" H 8200 1450 50  0001 C CNN
F 3 "" H 8200 1450 50  0001 C CNN
	1    8200 1450
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5B2ADCD9
P 8400 1300
F 0 "C3" H 8425 1400 50  0000 L CNN
F 1 "1u" H 8425 1200 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 8438 1150 50  0001 C CNN
F 3 "" H 8400 1300 50  0001 C CNN
	1    8400 1300
	-1   0    0    1   
$EndComp
$Comp
L C C4
U 1 1 5B2AE259
P 9100 1050
F 0 "C4" H 8900 1000 50  0000 L CNN
F 1 "100nF" H 8750 1100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9138 900 50  0001 C CNN
F 3 "" H 9100 1050 50  0001 C CNN
	1    9100 1050
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR015
U 1 1 5B2AE521
P 9100 1200
F 0 "#PWR015" H 9100 950 50  0001 C CNN
F 1 "GND" H 9100 1050 50  0000 C CNN
F 2 "" H 9100 1200 50  0001 C CNN
F 3 "" H 9100 1200 50  0001 C CNN
	1    9100 1200
	1    0    0    -1  
$EndComp
Text Label 9300 4300 0    60   ~ 0
SENSE_VAC
Text Label 8350 4200 0    60   ~ 0
SENSE_ACCUR
Text Label 6250 900  0    60   ~ 0
9VAC1+
Text Label 6250 1150 0    60   ~ 0
9VAC1-
$Comp
L C C1
U 1 1 5B2D5A0C
P 4900 2250
F 0 "C1" H 4925 2350 50  0000 L CNN
F 1 "220u" H 4925 2150 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210_HandSoldering" H 4938 2100 50  0001 C CNN
F 3 "" H 4900 2250 50  0001 C CNN
	1    4900 2250
	-1   0    0    1   
$EndComp
Text Notes 10650 7650 0    60   ~ 0
1.0
$Comp
L GND #PWR016
U 1 1 5B3BF5F2
P 6250 2600
F 0 "#PWR016" H 6250 2350 50  0001 C CNN
F 1 "GND" H 6250 2450 50  0000 C CNN
F 2 "" H 6250 2600 50  0001 C CNN
F 3 "" H 6250 2600 50  0001 C CNN
	1    6250 2600
	1    0    0    -1  
$EndComp
Text Label 3650 2600 0    60   ~ 0
9VAC2
$Comp
L AP1117-50 U7
U 1 1 5B3C1493
P 5650 1950
F 0 "U7" H 5500 2075 50  0000 C CNN
F 1 "AP1117-50" H 5650 2075 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-223-3_TabPin2" H 5650 2150 50  0001 C CNN
F 3 "" H 5750 1700 50  0001 C CNN
	1    5650 1950
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR017
U 1 1 5B3B9E81
P 6250 1950
F 0 "#PWR017" H 6250 1800 50  0001 C CNN
F 1 "+5V" H 6250 2090 50  0000 C CNN
F 2 "" H 6250 1950 50  0001 C CNN
F 3 "" H 6250 1950 50  0001 C CNN
	1    6250 1950
	1    0    0    -1  
$EndComp
$Comp
L R_Small R10
U 1 1 5B3BED52
P 5450 3200
F 0 "R10" V 5350 3100 50  0000 L CNN
F 1 "560" V 5450 3150 39  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 5450 3200 50  0001 C CNN
F 3 "" H 5450 3200 50  0001 C CNN
	1    5450 3200
	-1   0    0    1   
$EndComp
$Comp
L R_Small R11
U 1 1 5B3BF114
P 5650 3200
F 0 "R11" V 5550 3100 50  0000 L CNN
F 1 "560" V 5650 3150 39  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 5650 3200 50  0001 C CNN
F 3 "" H 5650 3200 50  0001 C CNN
	1    5650 3200
	-1   0    0    1   
$EndComp
$Comp
L +5V #PWR018
U 1 1 5B3BF6CD
P 5550 3050
F 0 "#PWR018" H 5550 2900 50  0001 C CNN
F 1 "+5V" H 5550 3190 50  0000 C CNN
F 2 "" H 5550 3050 50  0001 C CNN
F 3 "" H 5550 3050 50  0001 C CNN
	1    5550 3050
	1    0    0    -1  
$EndComp
$Comp
L R_Small R7
U 1 1 5B3C0614
P 2900 3900
F 0 "R7" V 2800 3800 50  0000 L CNN
F 1 "560" V 2900 3850 39  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 2900 3900 50  0001 C CNN
F 3 "" H 2900 3900 50  0001 C CNN
	1    2900 3900
	-1   0    0    1   
$EndComp
$Comp
L R_Small R9
U 1 1 5B3C06EC
P 3100 3900
F 0 "R9" V 3000 3800 50  0000 L CNN
F 1 "560" V 3100 3850 39  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 3100 3900 50  0001 C CNN
F 3 "" H 3100 3900 50  0001 C CNN
	1    3100 3900
	-1   0    0    1   
$EndComp
Wire Wire Line
	2000 2800 2500 2800
Connection ~ 2100 2800
Connection ~ 2200 2800
Connection ~ 2300 2800
Connection ~ 2400 2800
Connection ~ 1600 2800
Connection ~ 1700 2800
Connection ~ 1800 2800
Wire Wire Line
	4400 3950 3950 3950
Wire Wire Line
	4400 4450 3950 4450
Wire Wire Line
	6850 3900 6850 3800
Wire Wire Line
	8550 3900 8250 3900
Wire Wire Line
	5500 3800 5500 3950
Wire Wire Line
	5500 3950 5300 3950
Wire Wire Line
	5450 4450 5450 4550
Wire Wire Line
	6850 3800 6550 3800
Wire Wire Line
	5650 4000 6850 4000
Wire Wire Line
	5650 4000 5650 4100
Wire Wire Line
	5650 4100 5300 4100
Wire Wire Line
	5700 4100 6850 4100
Wire Wire Line
	5700 4100 5700 4300
Wire Wire Line
	5700 4300 5300 4300
Wire Wire Line
	5900 3200 5900 4100
Wire Wire Line
	6150 3100 5800 3100
Wire Wire Line
	5800 3100 5800 4000
Wire Wire Line
	6150 3200 5900 3200
Wire Wire Line
	6550 4300 6600 4300
Wire Wire Line
	6600 4300 6600 4200
Wire Wire Line
	6600 4200 6850 4200
Wire Wire Line
	6850 4300 6650 4300
Wire Wire Line
	6650 4300 6650 4550
Wire Wire Line
	6650 4550 6550 4550
Wire Wire Line
	6150 4300 6150 4700
Connection ~ 6150 4550
Wire Wire Line
	8600 4700 8250 4700
Wire Wire Line
	1700 2800 1700 3200
Wire Wire Line
	2100 3200 2100 2800
Wire Wire Line
	2000 3350 2000 3850
Wire Wire Line
	1850 3350 1850 3850
Wire Wire Line
	1750 3350 1850 3350
Wire Wire Line
	2000 3350 2050 3350
Wire Wire Line
	2050 3350 2050 3200
Wire Wire Line
	2050 3200 2100 3200
Wire Wire Line
	1700 3200 1750 3200
Wire Wire Line
	1750 3200 1750 3350
Connection ~ 2050 3200
Connection ~ 1750 3200
Wire Wire Line
	1500 4550 1350 4550
Wire Wire Line
	1150 4900 1500 4900
Wire Wire Line
	1350 4900 1350 4850
Connection ~ 1350 4900
Wire Wire Line
	1500 2800 1500 3950
Wire Wire Line
	1500 3950 1350 3950
Wire Wire Line
	1350 3950 1350 4550
Connection ~ 1350 4550
Wire Wire Line
	2800 4100 4400 4100
Wire Wire Line
	2800 4200 3200 4200
Wire Wire Line
	2950 4800 2950 5100
Wire Wire Line
	2950 4900 2800 4900
Wire Wire Line
	1450 5400 1450 4900
Connection ~ 1450 4900
Wire Notes Line
	4800 2850 4800 6200
Wire Wire Line
	8850 4700 8850 5050
Wire Wire Line
	8850 5050 5150 5050
Wire Wire Line
	5150 5250 5250 5250
Wire Wire Line
	5250 5250 5250 5300
Wire Wire Line
	4550 6000 4500 6000
Wire Wire Line
	4550 5800 4500 5800
Wire Wire Line
	4200 5800 4300 5800
Wire Wire Line
	5150 6000 5200 6000
Wire Wire Line
	5150 5800 8950 5800
Wire Wire Line
	8950 5800 8950 4600
Wire Wire Line
	8950 4600 8250 4600
Wire Wire Line
	8850 4700 8800 4700
Wire Wire Line
	2950 5300 2950 5400
Connection ~ 2950 4900
Wire Wire Line
	2950 4800 2800 4800
Wire Wire Line
	2950 5400 1450 5400
Wire Wire Line
	5450 4450 5300 4450
Wire Wire Line
	10900 1650 10900 4300
Wire Wire Line
	3300 900  7000 900 
Wire Wire Line
	7000 1000 6950 1000
Wire Wire Line
	6950 1000 6950 900 
Connection ~ 6950 900 
Wire Wire Line
	3400 1150 7000 1150
Wire Wire Line
	8100 1450 8400 1450
Wire Wire Line
	8100 1450 8100 1250
Wire Wire Line
	8400 1150 8100 1150
Connection ~ 8200 1450
Wire Wire Line
	8250 4200 8900 4200
Wire Wire Line
	3300 900  3300 5750
Wire Wire Line
	3400 1150 3400 5850
Wire Wire Line
	6150 3450 6150 3400
Wire Wire Line
	2250 5750 2250 6700
Wire Wire Line
	3300 5750 2250 5750
Wire Wire Line
	2450 5850 2450 6700
Wire Wire Line
	3400 5850 2450 5850
Wire Wire Line
	2350 6700 2350 6600
Wire Wire Line
	2350 6600 2250 6600
Connection ~ 2250 6600
Wire Wire Line
	2550 6700 2550 6600
Wire Wire Line
	2550 6600 2450 6600
Connection ~ 2450 6600
Wire Wire Line
	3200 4300 4400 4300
Wire Wire Line
	9100 900  8100 900 
Wire Wire Line
	8900 4200 8900 1000
Wire Wire Line
	8900 1000 8100 1000
Connection ~ 6950 1150
Wire Wire Line
	7000 1250 6950 1250
Wire Wire Line
	6950 1250 6950 1150
Wire Wire Line
	1500 2800 1900 2800
Connection ~ 1500 2800
Wire Wire Line
	2650 6700 2650 5950
Wire Wire Line
	2650 5950 3500 5950
Wire Wire Line
	3500 5950 3500 2600
Wire Wire Line
	3500 2600 6250 2600
Wire Wire Line
	4100 1950 4300 1950
Wire Wire Line
	4100 900  4100 1950
Connection ~ 4100 900 
Wire Wire Line
	4600 1950 5350 1950
Wire Wire Line
	4900 1950 4900 2100
Wire Wire Line
	4900 2400 4900 2600
Connection ~ 4900 2600
Connection ~ 4900 1950
Wire Wire Line
	5650 2250 5650 2600
Connection ~ 5650 2600
Wire Wire Line
	6250 1950 5950 1950
Wire Wire Line
	10900 1650 4100 1650
Connection ~ 4100 1650
Connection ~ 5800 4000
Connection ~ 5900 4100
Wire Wire Line
	10900 4300 10700 4300
Wire Wire Line
	10400 4300 10300 4300
Wire Wire Line
	8250 4300 10100 4300
Wire Wire Line
	9950 4250 9950 4350
Connection ~ 9950 4300
Wire Wire Line
	9950 4050 9950 3850
Wire Wire Line
	9950 4550 9950 4750
Wire Wire Line
	8250 3700 8750 3700
Wire Wire Line
	8750 3700 8750 3750
Wire Wire Line
	5650 3300 5800 3300
Connection ~ 5800 3300
Wire Wire Line
	5450 3300 5450 3350
Wire Wire Line
	5450 3350 5900 3350
Connection ~ 5900 3350
Wire Wire Line
	5650 3100 5650 3050
Wire Wire Line
	5650 3050 5450 3050
Wire Wire Line
	5450 3050 5450 3100
Wire Wire Line
	3200 4200 3200 4300
Wire Wire Line
	2900 4000 2900 4100
Connection ~ 2900 4100
Wire Wire Line
	3100 4000 3100 4200
Connection ~ 3100 4200
Wire Wire Line
	2900 3800 2900 3750
Wire Wire Line
	2900 3750 3100 3750
Wire Wire Line
	3100 3750 3100 3800
$Comp
L +5V #PWR019
U 1 1 5B3C0B11
P 3000 3750
F 0 "#PWR019" H 3000 3600 50  0001 C CNN
F 1 "+5V" H 3000 3890 50  0000 C CNN
F 2 "" H 3000 3750 50  0001 C CNN
F 3 "" H 3000 3750 50  0001 C CNN
	1    3000 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 5050 4550 5050
$Comp
L TLP291 U4
U 1 1 5B3D5BA2
P 4850 5150
F 0 "U4" H 4650 5350 50  0000 L CNN
F 1 "TLP291" H 4850 5350 50  0000 L CNN
F 2 "Housings_SOIC:SO-4_7.6x3.6mm_Pitch2.54mm" H 4650 4950 50  0001 L CIN
F 3 "" H 4850 5150 50  0001 L CNN
	1    4850 5150
	1    0    0    -1  
$EndComp
$Comp
L TLP291 U5
U 1 1 5B3D5E18
P 4850 5900
F 0 "U5" H 4650 6100 50  0000 L CNN
F 1 "TLP291" H 4850 6100 50  0000 L CNN
F 2 "Housings_SOIC:SO-4_7.6x3.6mm_Pitch2.54mm" H 4650 5700 50  0001 L CIN
F 3 "" H 4850 5900 50  0001 L CNN
	1    4850 5900
	1    0    0    -1  
$EndComp
$EndSCHEMATC
