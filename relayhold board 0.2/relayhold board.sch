EESchema Schematic File Version 4
LIBS:relayhold board-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "relay hold"
Date "2019-08-25"
Rev "0.2"
Comp ""
Comment1 "an addon board for the C64 Saver 2"
Comment2 "adds 9VAC shutdown on powerfault and fault-hold mechanism"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Relay:SANYOU_SRD_Form_C K1
U 1 1 5D4738B9
P 7900 3850
F 0 "K1" V 8450 3750 50  0000 C CNN
F 1 "SANYOU_SRD_Form_C" V 8350 3850 50  0000 C CNN
F 2 "Relay_THT:Relay_SPDT_SANYOU_SRD_Series_Form_C" H 8350 3800 50  0001 L CNN
F 3 "http://www.sanyourelay.ca/public/products/pdf/SRD.pdf" H 7900 3850 50  0001 C CNN
	1    7900 3850
	1    0    0    1   
$EndComp
$Comp
L Device:Q_NPN_CBE Q3
U 1 1 5D4744D9
P 5850 5000
F 0 "Q3" H 6041 5046 50  0000 L CNN
F 1 "BC337" H 6041 4955 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline_Wide" H 6050 5100 50  0001 C CNN
F 3 "~" H 5850 5000 50  0001 C CNN
	1    5850 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_PNP_CBE Q2
U 1 1 5D47588C
P 5150 4000
F 0 "Q2" H 5341 3954 50  0000 L CNN
F 1 "Q_PNP_BCE" H 5341 4045 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline_Wide" H 5350 4100 50  0001 C CNN
F 3 "~" H 5150 4000 50  0001 C CNN
	1    5150 4000
	-1   0    0    1   
$EndComp
$Comp
L Device:C C1
U 1 1 5D478324
P 5050 5350
F 0 "C1" H 5165 5396 50  0000 L CNN
F 1 "1u" H 5165 5305 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W2.5mm_P5.00mm" H 5088 5200 50  0001 C CNN
F 3 "~" H 5050 5350 50  0001 C CNN
	1    5050 5350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5D47926D
P 4350 5000
F 0 "R2" V 4143 5000 50  0000 C CNN
F 1 "100K" V 4234 5000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 4280 5000 50  0001 C CNN
F 3 "~" H 4350 5000 50  0001 C CNN
	1    4350 5000
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 5D47994D
P 5050 4450
F 0 "R3" H 4980 4404 50  0000 R CNN
F 1 "1K" H 4980 4495 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 4980 4450 50  0001 C CNN
F 3 "~" H 5050 4450 50  0001 C CNN
	1    5050 4450
	-1   0    0    1   
$EndComp
$Comp
L Device:R R4
U 1 1 5D479DCD
P 5500 4000
F 0 "R4" V 5707 4000 50  0000 C CNN
F 1 "100K" V 5616 4000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 5430 4000 50  0001 C CNN
F 3 "~" H 5500 4000 50  0001 C CNN
	1    5500 4000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5D499005
P 4050 6050
F 0 "#PWR0101" H 4050 5800 50  0001 C CNN
F 1 "GND" H 4055 5877 50  0000 C CNN
F 2 "" H 4050 6050 50  0001 C CNN
F 3 "" H 4050 6050 50  0001 C CNN
	1    4050 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 5200 5950 5700
Wire Wire Line
	5050 5000 5050 4600
Wire Wire Line
	5050 5200 5050 5000
Connection ~ 5050 5000
Wire Wire Line
	5050 5500 5050 5700
Wire Wire Line
	5050 5000 4650 5000
Wire Wire Line
	4050 5700 4050 6050
Wire Wire Line
	4050 5700 4650 5700
Wire Wire Line
	5950 5700 7700 5700
$Comp
L Transistor_FET:2N7000 Q4
U 1 1 5D4D6DDF
P 7600 4650
F 0 "Q4" H 7806 4696 50  0000 L CNN
F 1 "2N7000" H 7806 4605 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline_Wide" H 7800 4575 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7000.pdf" H 7600 4650 50  0001 L CNN
	1    7600 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 4650 5950 4800
Wire Wire Line
	7700 3200 7700 3550
Wire Wire Line
	7700 4150 7700 4450
Wire Wire Line
	7700 4850 7700 5700
$Comp
L Connector_Generic:Conn_01x08 J1
U 1 1 5D4F707D
P 2500 3300
F 0 "J1" H 2418 2675 50  0000 C CNN
F 1 "Conn_01x08" H 2418 2766 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 2500 3300 50  0001 C CNN
F 3 "~" H 2500 3300 50  0001 C CNN
	1    2500 3300
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J3
U 1 1 5D4F776C
P 9200 3850
F 0 "J3" H 9200 3250 50  0000 C CNN
F 1 "Conn_01x08" H 9350 3350 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 9200 3850 50  0001 C CNN
F 3 "~" H 9200 3850 50  0001 C CNN
	1    9200 3850
	1    0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 5D4F8170
P 2500 4550
F 0 "J2" H 2418 4867 50  0000 C CNN
F 1 "Conn_01x04" H 2418 4776 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 2500 4550 50  0001 C CNN
F 3 "~" H 2500 4550 50  0001 C CNN
	1    2500 4550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4050 5700 2700 5700
Wire Wire Line
	2700 5700 2700 4750
Connection ~ 4050 5700
Wire Wire Line
	2700 4650 3350 4650
Wire Wire Line
	3400 5000 3400 4550
Wire Wire Line
	3400 4550 2700 4550
Wire Wire Line
	3400 5000 4200 5000
Text Label 3100 4650 2    50   ~ 0
PGATE
Text Label 3600 5000 0    50   ~ 0
OVERVOLTAGE
NoConn ~ 2700 4450
Wire Wire Line
	9000 3750 9000 3650
Connection ~ 9000 3550
Wire Wire Line
	9000 3550 9000 3450
Connection ~ 9000 3650
Wire Wire Line
	9000 3650 9000 3550
Wire Wire Line
	9000 3850 9000 3950
Wire Wire Line
	9000 4300 8200 4300
Wire Wire Line
	8200 4300 8200 4150
Connection ~ 9000 3950
Wire Wire Line
	9000 3950 9000 4050
Connection ~ 9000 4050
Wire Wire Line
	9000 4050 9000 4150
Connection ~ 9000 4150
Wire Wire Line
	9000 4150 9000 4300
Wire Wire Line
	9000 3450 9000 3300
Wire Wire Line
	9000 3300 8100 3300
Wire Wire Line
	8100 3300 8100 3550
Connection ~ 9000 3450
Text Label 8550 3300 0    50   ~ 0
9VAC1
Text Label 8550 4300 0    50   ~ 0
9VAC1'
Wire Wire Line
	2700 2900 2700 3000
Connection ~ 2700 3000
Wire Wire Line
	2700 3000 2700 3100
Connection ~ 2700 3100
Wire Wire Line
	2700 3100 2700 3200
Connection ~ 2700 3200
Wire Wire Line
	2700 3200 2700 3300
Connection ~ 2700 3300
Wire Wire Line
	2700 3300 2700 3400
Connection ~ 2700 3400
Wire Wire Line
	2700 3400 2700 3500
Connection ~ 2700 3500
Wire Wire Line
	2700 3500 2700 3600
Wire Wire Line
	2700 3200 3350 3200
Text Label 3600 3200 0    50   ~ 0
V_IN
Wire Wire Line
	5050 4200 5050 4300
$Comp
L Device:Q_PNP_CBE Q1
U 1 1 5D55EF5D
P 3450 3600
F 0 "Q1" H 3641 3554 50  0000 L CNN
F 1 "Q_PNP_BCE" H 3641 3645 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline_Wide" H 3650 3700 50  0001 C CNN
F 3 "~" H 3450 3600 50  0001 C CNN
	1    3450 3600
	-1   0    0    1   
$EndComp
Wire Wire Line
	3350 3400 3350 3200
Connection ~ 3350 3200
Wire Wire Line
	3350 3800 3350 4650
$Comp
L Device:R R1
U 1 1 5D564462
P 3800 3600
F 0 "R1" V 4007 3600 50  0000 C CNN
F 1 "100K" V 3916 3600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 3730 3600 50  0001 C CNN
F 3 "~" H 3800 3600 50  0001 C CNN
	1    3800 3600
	0    -1   -1   0   
$EndComp
Connection ~ 5950 5700
$Comp
L Device:R R5
U 1 1 5D57432A
P 6650 4000
F 0 "R5" H 6580 3954 50  0000 R CNN
F 1 "33K" H 6580 4045 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 6580 4000 50  0001 C CNN
F 3 "~" H 6650 4000 50  0001 C CNN
	1    6650 4000
	-1   0    0    1   
$EndComp
Wire Wire Line
	3950 3600 5700 3600
Wire Wire Line
	5700 3600 5700 4000
Wire Wire Line
	5650 4000 5700 4000
Wire Wire Line
	5050 3200 5050 3800
$Comp
L Jumper:Jumper_3_Open JP1
U 1 1 5D5B7B1A
P 5950 4000
F 0 "JP1" V 5650 4050 50  0000 L CNN
F 1 "Jumper_3_Open" V 5995 4087 50  0001 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 5950 4000 50  0001 C CNN
F 3 "~" H 5950 4000 50  0001 C CNN
	1    5950 4000
	0    1    1    0   
$EndComp
Wire Wire Line
	5950 3750 5950 3200
Connection ~ 5950 3200
Wire Wire Line
	5950 3200 6650 3200
Wire Wire Line
	5950 4250 5950 4650
Connection ~ 5950 4650
Wire Wire Line
	5950 4650 6650 4650
Wire Wire Line
	6650 3200 6650 3850
Connection ~ 6650 3200
Wire Wire Line
	6650 4150 6650 4650
Connection ~ 6650 4650
Connection ~ 5050 3200
Wire Wire Line
	5050 3200 5950 3200
Wire Wire Line
	3350 3200 5050 3200
Wire Wire Line
	6650 3200 7050 3200
Wire Wire Line
	6650 4650 7050 4650
Wire Wire Line
	5800 4000 5700 4000
Connection ~ 5700 4000
Connection ~ 5050 5700
Text Notes 6050 4100 0    50   ~ 0
HOLD
Text Notes 6050 3950 0    50   ~ 0
RECOVER
$Comp
L Device:LED D1
U 1 1 5D60F16E
P 7050 4050
F 0 "D1" V 7089 3932 50  0000 R CNN
F 1 "RED_LED" V 6998 3932 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm" H 7050 4050 50  0001 C CNN
F 3 "~" H 7050 4050 50  0001 C CNN
	1    7050 4050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7050 4200 7050 4650
Connection ~ 7050 4650
Wire Wire Line
	7050 4650 7400 4650
$Comp
L Device:R R6
U 1 1 5D616A97
P 7050 3550
F 0 "R6" H 6980 3504 50  0000 R CNN
F 1 "560" H 6980 3595 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 6980 3550 50  0001 C CNN
F 3 "~" H 7050 3550 50  0001 C CNN
	1    7050 3550
	-1   0    0    1   
$EndComp
Wire Wire Line
	7050 3400 7050 3200
Connection ~ 7050 3200
Wire Wire Line
	7050 3200 7700 3200
Wire Wire Line
	7050 3700 7050 3900
$Comp
L Device:R R7
U 1 1 5D63FF47
P 4650 5350
F 0 "R7" H 4580 5304 50  0000 R CNN
F 1 "33K" H 4580 5395 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 4580 5350 50  0001 C CNN
F 3 "~" H 4650 5350 50  0001 C CNN
	1    4650 5350
	-1   0    0    1   
$EndComp
Wire Wire Line
	4650 5200 4650 5000
Connection ~ 4650 5000
Wire Wire Line
	4650 5000 4500 5000
Wire Wire Line
	4650 5500 4650 5700
Connection ~ 4650 5700
Wire Wire Line
	4650 5700 5050 5700
Wire Wire Line
	5050 5700 5950 5700
Wire Wire Line
	5050 5000 5650 5000
Text Label 5600 5000 0    10   ~ 0
OV_GATE
Text Label 7300 4650 0    10   ~ 0
MOSFET_GATE
$EndSCHEMATC
