EESchema Schematic File Version 4
LIBS:C64Saver2-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "C64 Saver"
Date "2020-09-13"
Rev "2.5"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L C64Saver2-rescue:CP C1
U 1 1 5AFB3C02
P 2350 3600
F 0 "C1" H 2375 3700 50  0000 L CNN
F 1 "47uF" H 2375 3500 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.4" H 2388 3450 50  0001 C CNN
F 3 "" H 2350 3600 50  0001 C CNN
	1    2350 3600
	1    0    0    -1  
$EndComp
$Comp
L C64Saver2-rescue:R R1
U 1 1 5AFB3CB5
P 3650 3150
F 0 "R1" V 3730 3150 50  0000 C CNN
F 1 "3k9" V 3650 3150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3580 3150 50  0001 C CNN
F 3 "" H 3650 3150 50  0001 C CNN
	1    3650 3150
	1    0    0    -1  
$EndComp
$Comp
L C64Saver2-rescue:Conn_01x04 J6
U 1 1 5B1D42F2
P 8400 3750
F 0 "J6" H 8400 3950 50  0000 C CNN
F 1 "Conn_01x04" H 8400 3450 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_bornier-4_P5.08mm" H 8400 3750 50  0001 C CNN
F 3 "" H 8400 3750 50  0001 C CNN
	1    8400 3750
	1    0    0    -1  
$EndComp
$Comp
L C64Saver2-rescue:Conn_01x04 J1
U 1 1 5B1D4425
P 1500 3850
F 0 "J1" H 1500 4050 50  0000 C CNN
F 1 "Conn_01x04" H 1500 3550 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_bornier-4_P5.08mm" H 1500 3850 50  0001 C CNN
F 3 "" H 1500 3850 50  0001 C CNN
	1    1500 3850
	-1   0    0    1   
$EndComp
$Comp
L C64Saver2-rescue:R R2
U 1 1 5B1D6BF3
P 3650 4300
F 0 "R2" V 3730 4300 50  0000 C CNN
F 1 "3k3" V 3650 4300 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3580 4300 50  0001 C CNN
F 3 "" H 3650 4300 50  0001 C CNN
	1    3650 4300
	1    0    0    -1  
$EndComp
$Comp
L C64Saver2-rescue:R R3
U 1 1 5B1D6DA9
P 4050 3150
F 0 "R3" V 4130 3150 50  0000 C CNN
F 1 "3k3" V 4050 3150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3980 3150 50  0001 C CNN
F 3 "" H 4050 3150 50  0001 C CNN
	1    4050 3150
	1    0    0    -1  
$EndComp
$Comp
L C64Saver2-rescue:R R6
U 1 1 5B1D73D7
P 5700 3350
F 0 "R6" V 5780 3350 50  0000 C CNN
F 1 "3k9" V 5700 3350 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5630 3350 50  0001 C CNN
F 3 "" H 5700 3350 50  0001 C CNN
	1    5700 3350
	1    0    0    -1  
$EndComp
$Comp
L C64Saver2-rescue:R R5
U 1 1 5B1D747E
P 4950 2950
F 0 "R5" V 5030 2950 50  0000 C CNN
F 1 "3k3" V 4950 2950 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4880 2950 50  0001 C CNN
F 3 "" H 4950 2950 50  0001 C CNN
	1    4950 2950
	1    0    0    -1  
$EndComp
$Comp
L C64Saver2-rescue:R R4
U 1 1 5B1D9590
P 4300 3650
F 0 "R4" V 4380 3650 50  0000 C CNN
F 1 "330k" V 4300 3650 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4230 3650 50  0001 C CNN
F 3 "" H 4300 3650 50  0001 C CNN
	1    4300 3650
	0    -1   -1   0   
$EndComp
Text GLabel 5800 3100 2    49   Input ~ 0
PGATE
Text Label 3800 4900 0    49   ~ 0
9VAC1'
Text Label 3100 4800 0    49   ~ 0
9VAC2
Text Label 6850 2700 0    49   ~ 0
5V_SAFE
Text Label 2000 2700 0    49   ~ 0
VCC1+
Text Label 3350 2700 0    49   ~ 0
VCC1-
$Comp
L power:GND #PWR01
U 1 1 5B1E4ECB
P 2550 4600
F 0 "#PWR01" H 2550 4350 50  0001 C CNN
F 1 "GND" H 2550 4450 50  0000 C CNN
F 2 "" H 2550 4600 50  0001 C CNN
F 3 "" H 2550 4600 50  0001 C CNN
	1    2550 4600
	1    0    0    -1  
$EndComp
Text GLabel 4450 5700 1    49   Input ~ 0
PGATE
Text GLabel 5800 3650 2    49   Input ~ 0
OVERVOLTAGE
Text GLabel 4350 5700 1    49   Input ~ 0
OVERVOLTAGE
Text Label 3700 4100 0    49   ~ 0
SENSE
Text Label 5250 3900 0    49   ~ 0
NGATE
$Comp
L C64Saver2-rescue:Mounting_Hole MK1
U 1 1 5B1F2FB5
P 1100 6700
F 0 "MK1" H 1100 6900 50  0000 C CNN
F 1 "Mounting_Hole" H 1100 6825 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_2.5mm" H 1100 6700 50  0001 C CNN
F 3 "" H 1100 6700 50  0001 C CNN
	1    1100 6700
	1    0    0    -1  
$EndComp
$Comp
L C64Saver2-rescue:Mounting_Hole MK2
U 1 1 5B1F307E
P 1100 7050
F 0 "MK2" H 1100 7250 50  0000 C CNN
F 1 "Mounting_Hole" H 1100 7175 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_2.5mm" H 1100 7050 50  0001 C CNN
F 3 "" H 1100 7050 50  0001 C CNN
	1    1100 7050
	1    0    0    -1  
$EndComp
$Comp
L C64Saver2-rescue:Q_PMOS_GDS Q2
U 1 1 5B217093
P 5700 2800
F 0 "Q2" V 5900 2850 50  0000 L CNN
F 1 "IRFR5305" V 6000 2850 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:ATPAK-2" H 5900 2900 50  0001 C CNN
F 3 "" H 5700 2800 50  0001 C CNN
	1    5700 2800
	0    1    -1   0   
$EndComp
Text Label 3050 4900 0    49   ~ 0
9VAC1
Wire Wire Line
	3650 4100 3950 4100
Wire Wire Line
	3650 3300 3650 3650
Connection ~ 3650 4100
Wire Wire Line
	4050 4500 4050 4200
Wire Wire Line
	3650 4500 3650 4450
Wire Wire Line
	4050 2700 4050 3000
Wire Wire Line
	3650 2700 3650 3000
Connection ~ 3650 2700
Connection ~ 4050 4500
Wire Wire Line
	5700 4500 5700 4100
Wire Wire Line
	5700 3500 5700 3650
Connection ~ 4050 2700
Wire Wire Line
	4950 2700 4950 2800
Connection ~ 4950 2700
Wire Wire Line
	4950 3100 4950 3650
Connection ~ 5700 3100
Wire Wire Line
	4450 3650 4950 3650
Connection ~ 5700 3650
Wire Wire Line
	4150 3650 3650 3650
Connection ~ 3650 3650
Connection ~ 3650 4500
Wire Wire Line
	2050 3750 2050 4500
Wire Wire Line
	1700 3750 2050 3750
Connection ~ 5700 4500
Wire Wire Line
	1700 3950 1800 3950
Wire Wire Line
	1800 3950 1800 4900
Wire Wire Line
	1900 4800 1900 3850
Wire Wire Line
	1900 3850 1700 3850
Wire Wire Line
	1800 3650 1800 2700
Wire Wire Line
	1700 3650 1800 3650
Wire Wire Line
	1800 2700 2350 2700
Wire Wire Line
	2550 4600 2550 4500
Connection ~ 2550 4500
Wire Wire Line
	5700 3000 5700 3100
Wire Wire Line
	2350 3450 2350 2700
Wire Wire Line
	2350 3750 2350 4500
Wire Wire Line
	8200 3650 7800 3650
Wire Wire Line
	7800 3650 7800 2700
Wire Wire Line
	7950 4800 7950 3850
Wire Wire Line
	7950 3850 8200 3850
Wire Wire Line
	8050 4900 8050 3950
Wire Wire Line
	8050 3950 8200 3950
Wire Wire Line
	7800 4500 7800 3750
Wire Wire Line
	7800 3750 8200 3750
$Comp
L C64Saver2-rescue:Conn_01x08 J2
U 1 1 5B493748
P 2800 1650
F 0 "J2" H 2800 2050 50  0000 C CNN
F 1 "Conn_01x08" H 2800 1150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08_Pitch2.54mm" H 2800 1650 50  0001 C CNN
F 3 "" H 2800 1650 50  0001 C CNN
	1    2800 1650
	0    1    -1   0   
$EndComp
Wire Wire Line
	2500 2700 2500 1950
Wire Wire Line
	3000 1850 3000 1950
Wire Wire Line
	2400 1850 2400 1950
Wire Wire Line
	2400 1950 2500 1950
Connection ~ 2500 1950
Wire Wire Line
	2600 1950 2600 1850
Wire Wire Line
	2700 1950 2700 1850
Connection ~ 2600 1950
Wire Wire Line
	2900 1850 2900 1950
Wire Wire Line
	2800 1950 2900 1950
Connection ~ 3000 1950
Wire Wire Line
	2800 1850 2800 1950
Connection ~ 2900 1950
Wire Wire Line
	3100 1950 3100 1850
$Comp
L C64Saver2-rescue:Conn_01x08 J4
U 1 1 5B4955D0
P 3600 5700
F 0 "J4" H 3600 6100 50  0000 C CNN
F 1 "Conn_01x08" H 3600 5200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08_Pitch2.54mm" H 3600 5700 50  0001 C CNN
F 3 "" H 3600 5700 50  0001 C CNN
	1    3600 5700
	0    1    1    0   
$EndComp
$Comp
L C64Saver2-rescue:Conn_01x04 J5
U 1 1 5B495741
P 4350 5900
F 0 "J5" H 4350 6100 50  0000 C CNN
F 1 "Conn_01x04" H 4350 5600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 4350 5900 50  0001 C CNN
F 3 "" H 4350 5900 50  0001 C CNN
	1    4350 5900
	0    -1   1    0   
$EndComp
Wire Wire Line
	3500 5400 3500 5500
Wire Wire Line
	3200 5400 3300 5400
Connection ~ 3400 5400
Wire Wire Line
	3300 5500 3300 5400
Wire Wire Line
	3200 5500 3200 5400
Connection ~ 3300 5400
Wire Wire Line
	3700 5500 3700 5400
Wire Wire Line
	3600 5400 3700 5400
Connection ~ 3600 5400
Wire Wire Line
	3800 5400 3800 5500
Connection ~ 3700 5400
Wire Wire Line
	3900 5400 3900 5500
Connection ~ 3800 5400
$Comp
L power:GND #PWR02
U 1 1 5B497536
P 4800 5800
F 0 "#PWR02" H 4800 5550 50  0001 C CNN
F 1 "GND" H 4800 5650 50  0000 C CNN
F 2 "" H 4800 5800 50  0001 C CNN
F 3 "" H 4800 5800 50  0001 C CNN
	1    4800 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 5800 4800 5600
Wire Wire Line
	4800 5600 4550 5600
Wire Wire Line
	4550 5600 4550 5700
Wire Wire Line
	4250 4800 4250 5700
Text Label 4250 5650 1    49   ~ 0
9VAC2
Wire Wire Line
	1800 4900 3400 4900
Wire Wire Line
	3600 4900 8050 4900
Wire Wire Line
	1900 4800 4250 4800
Wire Wire Line
	3400 4900 3400 5400
Wire Wire Line
	3600 4900 3600 5400
Connection ~ 4250 4800
Wire Wire Line
	5250 3100 5700 3100
Connection ~ 4950 3650
Wire Wire Line
	2050 4500 2350 4500
$Comp
L C64Saver2-rescue:R R7
U 1 1 5BA6F720
P 4500 3900
F 0 "R7" V 4580 3900 50  0000 C CNN
F 1 "33k" V 4500 3900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4430 3900 50  0001 C CNN
F 3 "" H 4500 3900 50  0001 C CNN
	1    4500 3900
	0    -1   -1   0   
$EndComp
$Comp
L C64Saver2-rescue:R R8
U 1 1 5BA6F7A6
P 4700 4200
F 0 "R8" V 4780 4200 50  0000 C CNN
F 1 "82k" V 4700 4200 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4630 4200 50  0001 C CNN
F 3 "" H 4700 4200 50  0001 C CNN
	1    4700 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 3300 4050 3900
Wire Wire Line
	4350 3900 4050 3900
Connection ~ 4050 3900
Wire Wire Line
	4650 3900 4700 3900
Wire Wire Line
	4700 4050 4700 3900
Connection ~ 4700 3900
Wire Wire Line
	4700 4350 4700 4500
Connection ~ 4700 4500
Wire Wire Line
	7800 2700 6750 2700
Wire Wire Line
	3650 4100 3650 4150
Wire Wire Line
	3650 2700 4050 2700
Wire Wire Line
	4050 4500 4700 4500
Wire Wire Line
	4050 2700 4950 2700
Wire Wire Line
	5700 3100 5700 3200
Wire Wire Line
	5700 3100 5800 3100
Wire Wire Line
	5700 3650 5700 3700
Wire Wire Line
	5700 3650 5800 3650
Wire Wire Line
	3650 3650 3650 4100
Wire Wire Line
	3650 4500 4050 4500
Wire Wire Line
	5700 4500 7800 4500
Wire Wire Line
	2500 1950 2500 1850
Wire Wire Line
	2500 1950 2600 1950
Wire Wire Line
	2600 1950 2700 1950
Wire Wire Line
	3000 1950 3000 2700
Wire Wire Line
	3000 1950 3100 1950
Wire Wire Line
	2900 1950 3000 1950
Wire Wire Line
	3400 5400 3500 5400
Wire Wire Line
	3400 5400 3400 5500
Wire Wire Line
	3300 5400 3400 5400
Wire Wire Line
	3600 5400 3600 5500
Wire Wire Line
	3700 5400 3800 5400
Wire Wire Line
	3800 5400 3900 5400
Wire Wire Line
	4250 4800 7950 4800
Wire Wire Line
	4950 3650 5700 3650
$Comp
L C64Saver2-rescue:R R9
U 1 1 5F597072
P 6100 1900
F 0 "R9" V 6000 1900 50  0000 C CNN
F 1 "3k3" V 6100 1900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6030 1900 50  0001 C CNN
F 3 "" H 6100 1900 50  0001 C CNN
	1    6100 1900
	0    1    1    0   
$EndComp
Wire Wire Line
	6350 2750 6350 2700
Wire Wire Line
	6350 1900 6250 1900
Wire Wire Line
	5450 1900 5200 1900
Wire Wire Line
	5900 2700 6350 2700
Connection ~ 6350 2700
$Comp
L C64Saver2-rescue:R R10
U 1 1 5F59760D
P 6350 2900
F 0 "R10" H 6250 2850 50  0000 C CNN
F 1 "3k3" V 6350 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6280 2900 50  0001 C CNN
F 3 "" H 6350 2900 50  0001 C CNN
	1    6350 2900
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5F5D4509
P 6350 3050
F 0 "#PWR03" H 6350 2800 50  0001 C CNN
F 1 "GND" H 6350 2900 50  0000 C CNN
F 2 "" H 6350 3050 50  0001 C CNN
F 3 "" H 6350 3050 50  0001 C CNN
	1    6350 3050
	1    0    0    -1  
$EndComp
$Comp
L Reference_Voltage:TL431DBZ U1
U 1 1 5F5C6CCE
P 4050 4100
F 0 "U1" V 4096 4030 50  0000 R CNN
F 1 "TL431DBZ" V 4005 4030 50  0000 R CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4050 3950 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/tl431.pdf" H 4050 4100 50  0001 C CIN
	1    4050 4100
	0    -1   -1   0   
$EndComp
$Comp
L Transistor_FET:2N7002 Q1
U 1 1 5F5CC067
P 5600 3900
F 0 "Q1" H 5806 3946 50  0000 L CNN
F 1 "2N7002" H 5806 3855 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5800 3825 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7002.pdf" H 5600 3900 50  0001 L CNN
	1    5600 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 3900 5250 3900
Wire Wire Line
	4700 4500 5250 4500
Wire Wire Line
	4050 3900 4050 4000
Wire Wire Line
	5250 3050 5250 3100
Wire Wire Line
	5250 4100 5250 3900
Connection ~ 5250 3900
Wire Wire Line
	5250 3900 5400 3900
Wire Wire Line
	5250 4400 5250 4500
Connection ~ 5250 4500
Wire Wire Line
	5250 4500 5700 4500
Wire Wire Line
	5250 2750 5250 2700
Connection ~ 5250 2700
Wire Wire Line
	5250 2700 5500 2700
$Comp
L Device:D_Zener_ALT D2
U 1 1 5F5D6945
P 5250 2900
F 0 "D2" V 5204 2979 50  0000 L CNN
F 1 "BZY55B6V8" V 5295 2979 50  0000 L CNN
F 2 "Diode_SMD:D_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5250 2900 50  0001 C CNN
F 3 "~" H 5250 2900 50  0001 C CNN
	1    5250 2900
	0    1    1    0   
$EndComp
Wire Wire Line
	4950 2700 5200 2700
Wire Wire Line
	6350 1900 6350 2700
Connection ~ 5200 2700
Wire Wire Line
	5200 2700 5250 2700
$Comp
L Device:LED_ALT LED1
U 1 1 5F60FA71
P 5600 1900
F 0 "LED1" H 5750 1850 50  0000 C CNN
F 1 "LED_RED_3mm" H 5600 2000 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm" H 5600 1900 50  0001 C CNN
F 3 "~" H 5600 1900 50  0001 C CNN
	1    5600 1900
	-1   0    0    1   
$EndComp
Wire Wire Line
	5750 1900 5950 1900
Wire Wire Line
	5200 1900 5200 2700
$Comp
L Device:LED_ALT LED2
U 1 1 5F5E4F21
P 6750 3100
F 0 "LED2" H 6900 3050 50  0000 C CNN
F 1 "LED_GREEN_3mm" H 6750 3200 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm" H 6750 3100 50  0001 C CNN
F 3 "~" H 6750 3100 50  0001 C CNN
	1    6750 3100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6750 2950 6750 2700
Connection ~ 6750 2700
Wire Wire Line
	6750 2700 6350 2700
$Comp
L C64Saver2-rescue:R R11
U 1 1 5F5E915D
P 6750 3400
F 0 "R11" H 6650 3350 50  0000 C CNN
F 1 "3k3" V 6750 3400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6680 3400 50  0001 C CNN
F 3 "" H 6750 3400 50  0001 C CNN
	1    6750 3400
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5F5E95C1
P 6750 3550
F 0 "#PWR0101" H 6750 3300 50  0001 C CNN
F 1 "GND" H 6750 3400 50  0000 C CNN
F 2 "" H 6750 3550 50  0001 C CNN
F 3 "" H 6750 3550 50  0001 C CNN
	1    6750 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Zener_ALT D1
U 1 1 5F5E7C0C
P 5250 4250
F 0 "D1" V 5204 4329 50  0000 L CNN
F 1 "BZY55B6V8" V 5295 4329 50  0000 L CNN
F 2 "Diode_SMD:D_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5250 4250 50  0001 C CNN
F 3 "~" H 5250 4250 50  0001 C CNN
	1    5250 4250
	0    1    1    0   
$EndComp
Connection ~ 2350 2700
Wire Wire Line
	2350 2700 2500 2700
Connection ~ 2350 4500
Wire Wire Line
	2350 4500 2550 4500
Wire Wire Line
	3000 2700 3650 2700
Wire Wire Line
	2550 4500 3650 4500
$EndSCHEMATC