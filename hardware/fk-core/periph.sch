EESchema Schematic File Version 2
LIBS:power
LIBS:device
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
LIBS:atsamd21g-m
LIBS:ina219
LIBS:mcp73871
LIBS:microsd
LIBS:pcf8523t
LIBS:tps63060
LIBS:max1704xx
LIBS:gp-635tsmd
LIBS:fgpmmopa6h
LIBS:sk6812
LIBS:dcbarrelsmt
LIBS:xtal-3.2x1
LIBS:rfm9xw
LIBS:rf-sma-edge
LIBS:fk-core-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
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
L MICROSD M1
U 1 1 587FB272
P 3300 2200
F 0 "M1" H 3300 2200 45  0001 C CNN
F 1 "MICROSD" H 3300 2200 45  0001 C CNN
F 2 "microsd:MICROSD" H 3330 2350 20  0001 C CNN
F 3 "" H 3300 2200 60  0001 C CNN
F 4 "101-00581-59-1-ND" H 3300 2200 60  0001 C CNN "SPN"
	1    3300 2200
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR054
U 1 1 587FB329
P 2050 2500
F 0 "#PWR054" H 2050 2350 50  0001 C CNN
F 1 "+3V3" H 2050 2640 50  0000 C CNN
F 2 "" H 2050 2500 50  0000 C CNN
F 3 "" H 2050 2500 50  0000 C CNN
	1    2050 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR055
U 1 1 587FB33D
P 2050 3150
F 0 "#PWR055" H 2050 2900 50  0001 C CNN
F 1 "GND" H 2050 3000 50  0000 C CNN
F 2 "" H 2050 3150 50  0000 C CNN
F 3 "" H 2050 3150 50  0000 C CNN
	1    2050 3150
	1    0    0    -1  
$EndComp
NoConn ~ 2600 2400
NoConn ~ 2600 2300
NoConn ~ 1900 1600
Text GLabel 1900 1900 0    60   Input ~ 0
MISO
Text GLabel 1900 2000 0    60   Input ~ 0
MOSI
Text GLabel 1900 2100 0    60   Input ~ 0
SCK
Text GLabel 1900 2200 0    60   Input ~ 0
SD_CS
$Comp
L PCF8523T U5
U 1 1 587FB83A
P 6700 1750
F 0 "U5" H 6700 2050 50  0000 C CNN
F 1 "PCF8523T" H 6700 1950 50  0000 C CNN
F 2 "SMD_Packages:SOIC-8-N" H 6700 850 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/PCF8523.pdf" H 6700 750 50  0001 C CNN
F 4 "568-5306-1-ND" H 6700 1750 60  0001 C CNN "SPN"
	1    6700 1750
	1    0    0    -1  
$EndComp
Text GLabel 5800 2050 0    60   Input ~ 0
SDA1
Text GLabel 5800 2150 0    60   Input ~ 0
SCL1
$Comp
L Battery_Cell BT1
U 1 1 587FBB09
P 4800 2150
F 0 "BT1" H 4900 2250 50  0000 L CNN
F 1 "Battery_Cell" H 4900 2150 50  0000 L CNN
F 2 "Connectors:CR1220" V 4800 2210 50  0001 C CNN
F 3 "" V 4800 2210 50  0000 C CNN
F 4 "BC501SM-ND" H 4800 2150 60  0001 C CNN "SPN"
	1    4800 2150
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR056
U 1 1 587FBC3F
P 4800 1600
F 0 "#PWR056" H 4800 1450 50  0001 C CNN
F 1 "+3V3" H 4800 1740 50  0000 C CNN
F 2 "" H 4800 1600 50  0000 C CNN
F 3 "" H 4800 1600 50  0000 C CNN
	1    4800 1600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR057
U 1 1 587FBD33
P 4800 2550
F 0 "#PWR057" H 4800 2300 50  0001 C CNN
F 1 "GND" H 4800 2400 50  0000 C CNN
F 2 "" H 4800 2550 50  0000 C CNN
F 3 "" H 4800 2550 50  0000 C CNN
	1    4800 2550
	1    0    0    -1  
$EndComp
$Comp
L Crystal CRYSTAL8X3.8SMT1
U 1 1 587FBE50
P 7750 1950
F 0 "CRYSTAL8X3.8SMT1" H 7750 2100 50  0000 C CNN
F 1 "Crystal" H 7750 1800 50  0000 C CNN
F 2 "SOJ-4:SOJ-4" H 7750 1950 50  0001 C CNN
F 3 "" H 7750 1950 50  0000 C CNN
F 4 "XC1912CT-ND" H 7750 1950 60  0001 C CNN "SPN"
	1    7750 1950
	0    1    1    0   
$EndComp
NoConn ~ 7300 2350
$Comp
L PWR_FLAG #FLG058
U 1 1 58811532
P 4500 1850
F 0 "#FLG058" H 4500 1945 50  0001 C CNN
F 1 "PWR_FLAG" H 4500 2030 50  0000 C CNN
F 2 "" H 4500 1850 50  0000 C CNN
F 3 "" H 4500 1850 50  0000 C CNN
	1    4500 1850
	1    0    0    -1  
$EndComp
NoConn ~ 1900 1500
Text GLabel 5900 4950 0    60   Input ~ 0
GPS_RX
$Comp
L CONN_01X04 P5
U 1 1 58806947
P 3450 6550
F 0 "P5" H 3450 6800 50  0000 C CNN
F 1 "CONN_01X04" V 3550 6550 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x04" H 3450 6550 50  0001 C CNN
F 3 "" H 3450 6550 50  0000 C CNN
	1    3450 6550
	-1   0    0    1   
$EndComp
Text GLabel 4150 6500 2    60   Input ~ 0
SDA1
Text GLabel 4150 6600 2    60   Input ~ 0
SCL1
$Comp
L +3V3 #PWR059
U 1 1 58806AD4
P 4000 6300
F 0 "#PWR059" H 4000 6150 50  0001 C CNN
F 1 "+3V3" H 4000 6440 50  0000 C CNN
F 2 "" H 4000 6300 50  0000 C CNN
F 3 "" H 4000 6300 50  0000 C CNN
	1    4000 6300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR060
U 1 1 58806B22
P 4000 6800
F 0 "#PWR060" H 4000 6550 50  0001 C CNN
F 1 "GND" H 4000 6650 50  0000 C CNN
F 2 "" H 4000 6800 50  0000 C CNN
F 3 "" H 4000 6800 50  0000 C CNN
	1    4000 6800
	1    0    0    -1  
$EndComp
$Comp
L FGPMMOPA6H U8
U 1 1 5880828D
P 7000 4500
F 0 "U8" H 7000 4350 60  0000 C CNN
F 1 "FGPMMOPA6H" H 7000 4500 60  0000 C CNN
F 2 "FGPMMOPA6H:FGPMMOPA6H" H 7000 4500 60  0001 C CNN
F 3 "https://cdn-shop.adafruit.com/datasheets/GlobalTop-FGPMMOPA6H-Datasheet-V0A.pdf" H 7000 4500 60  0001 C CNN
F 4 "1530-1011-1-ND" H 7000 4500 60  0001 C CNN "SPN"
	1    7000 4500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR061
U 1 1 5880889C
P 5100 4950
F 0 "#PWR061" H 5100 4700 50  0001 C CNN
F 1 "GND" H 5100 4800 50  0000 C CNN
F 2 "" H 5100 4950 50  0000 C CNN
F 3 "" H 5100 4950 50  0000 C CNN
	1    5100 4950
	1    0    0    -1  
$EndComp
NoConn ~ 6000 4350
NoConn ~ 7850 4750
NoConn ~ 7850 4650
$Comp
L GND #PWR062
U 1 1 588089E8
P 8700 4950
F 0 "#PWR062" H 8700 4700 50  0001 C CNN
F 1 "GND" H 8700 4800 50  0000 C CNN
F 2 "" H 8700 4950 50  0000 C CNN
F 3 "" H 8700 4950 50  0000 C CNN
	1    8700 4950
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR063
U 1 1 58809394
P 5100 3900
F 0 "#PWR063" H 5100 3750 50  0001 C CNN
F 1 "+3V3" H 5100 4040 50  0000 C CNN
F 2 "" H 5100 3900 50  0000 C CNN
F 3 "" H 5100 3900 50  0000 C CNN
	1    5100 3900
	1    0    0    -1  
$EndComp
Text GLabel 5900 4850 0    60   Input ~ 0
GPS_TX
$Comp
L R R18
U 1 1 58809D8B
P 5350 4450
F 0 "R18" V 5430 4450 50  0000 C CNN
F 1 "470" V 5350 4450 50  0000 C CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" V 5280 4450 50  0001 C CNN
F 3 "" H 5350 4450 50  0000 C CNN
F 4 "541-470CCT-ND" H 5350 4450 60  0001 C CNN "SPN"
	1    5350 4450
	0    -1   -1   0   
$EndComp
$Comp
L LED D1
U 1 1 58809DE8
P 5750 4450
F 0 "D1" H 5750 4550 50  0000 C CNN
F 1 "RED" H 5750 4350 50  0000 C CNN
F 2 "LEDs:LED_0805" H 5750 4450 50  0001 C CNN
F 3 "" H 5750 4450 50  0000 C CNN
F 4 "475-1415-1-ND" H 5750 4450 60  0001 C CNN "SPN"
	1    5750 4450
	1    0    0    -1  
$EndComp
Text Label 5200 4700 0    60   ~ 0
GPS_FIX
Text Label 5100 4150 0    60   ~ 0
GPS_RESET
$Comp
L RFM9xW U10
U 1 1 588132A6
P 3100 4500
F 0 "U10" H 2750 5000 60  0000 C CNN
F 1 "RFM9xW" H 3100 4550 60  0000 C CNN
F 2 "RFM95W:RFM9xW" H 3100 4000 60  0001 C CNN
F 3 "" H 3100 4800 60  0000 C CNN
	1    3100 4500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR064
U 1 1 588134FA
P 3900 4950
F 0 "#PWR064" H 3900 4700 50  0001 C CNN
F 1 "GND" H 3900 4800 50  0000 C CNN
F 2 "" H 3900 4950 50  0000 C CNN
F 3 "" H 3900 4950 50  0000 C CNN
	1    3900 4950
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR065
U 1 1 588135AD
P 3900 4050
F 0 "#PWR065" H 3900 3900 50  0001 C CNN
F 1 "+3V3" H 3900 4190 50  0000 C CNN
F 2 "" H 3900 4050 50  0000 C CNN
F 3 "" H 3900 4050 50  0000 C CNN
	1    3900 4050
	1    0    0    -1  
$EndComp
Text GLabel 3900 4450 2    60   Input ~ 0
SCK
Text GLabel 3900 4550 2    60   Input ~ 0
MOSI
Text GLabel 3900 4650 2    60   Input ~ 0
MISO
Text Label 3700 4250 0    60   ~ 0
RFM_RESET
$Comp
L RF-SMA-EDGE J1
U 1 1 58813E67
P 1600 4150
F 0 "J1" H 1600 4400 60  0000 C CNN
F 1 "RF-SMA-EDGE" H 1600 3700 60  0000 C CNN
F 2 "RF-SMA-EDGE:RF-SMA-EDGE" H 1600 3600 60  0001 C CNN
F 3 "" H 1550 4100 60  0000 C CNN
	1    1600 4150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2600 2700 2050 2700
Wire Wire Line
	2050 2700 2050 3150
Wire Wire Line
	2600 2600 2050 2600
Wire Wire Line
	2050 2600 2050 2500
Wire Wire Line
	2600 2900 2050 2900
Connection ~ 2050 2900
Wire Wire Line
	2600 3000 2050 3000
Connection ~ 2050 3000
Wire Wire Line
	2600 2200 1900 2200
Wire Wire Line
	1900 2100 2600 2100
Wire Wire Line
	1900 2000 2600 2000
Wire Wire Line
	1900 1900 2600 1900
Wire Wire Line
	1900 1500 2600 1500
Wire Wire Line
	2600 1600 1900 1600
Wire Wire Line
	6100 2150 5800 2150
Wire Wire Line
	5800 2050 6100 2050
Wire Wire Line
	4800 2250 4800 2550
Wire Wire Line
	4800 2350 6100 2350
Wire Wire Line
	4500 1850 6100 1850
Wire Wire Line
	4800 1850 4800 1950
Wire Wire Line
	4800 1600 4800 1750
Wire Wire Line
	4800 1750 6100 1750
Connection ~ 4800 2350
Wire Wire Line
	7750 2100 7750 2150
Wire Wire Line
	7750 2150 7300 2150
Wire Wire Line
	7750 1800 7750 1750
Wire Wire Line
	7750 1750 7300 1750
Connection ~ 4800 1850
Wire Wire Line
	4000 6300 4000 6400
Wire Wire Line
	4000 6400 3650 6400
Wire Wire Line
	4000 6800 4000 6700
Wire Wire Line
	4000 6700 3650 6700
Wire Wire Line
	4150 6600 3650 6600
Wire Wire Line
	3650 6500 4150 6500
Wire Wire Line
	5100 4750 6000 4750
Wire Wire Line
	5100 4250 5100 4950
Wire Wire Line
	5100 4250 6000 4250
Connection ~ 5100 4750
Wire Wire Line
	8700 4150 8700 4950
Wire Wire Line
	7850 4850 8700 4850
Wire Wire Line
	7850 4150 8700 4150
Connection ~ 8700 4850
Wire Wire Line
	6000 4050 5100 4050
Wire Wire Line
	5100 4050 5100 3900
Wire Wire Line
	6000 4950 5900 4950
Wire Wire Line
	5900 4850 6000 4850
Wire Wire Line
	5900 4450 6000 4450
Wire Wire Line
	5600 4450 5500 4450
Wire Wire Line
	5200 4450 5100 4450
Connection ~ 5100 4450
Wire Wire Line
	8000 4950 8000 5500
Wire Wire Line
	8000 4950 7850 4950
Wire Wire Line
	6000 4150 5100 4150
Wire Wire Line
	5950 4450 5950 4700
Wire Wire Line
	5950 4700 5200 4700
Connection ~ 5950 4450
Wire Wire Line
	3900 4750 3900 4950
Wire Wire Line
	3900 4850 3600 4850
Wire Wire Line
	3600 4750 3900 4750
Connection ~ 3900 4850
Wire Wire Line
	3900 4050 3900 4150
Wire Wire Line
	3900 4150 3600 4150
Wire Wire Line
	3600 4250 4200 4250
Wire Wire Line
	3600 4450 3900 4450
Wire Wire Line
	3900 4550 3600 4550
Wire Wire Line
	3600 4650 3900 4650
Wire Wire Line
	1650 4550 1650 4500
Wire Wire Line
	1450 4550 1750 4550
Wire Wire Line
	1750 4550 1750 4500
Wire Wire Line
	1450 4550 1450 4500
Connection ~ 1650 4550
Wire Wire Line
	1550 4500 1550 4550
Connection ~ 1550 4550
Wire Wire Line
	1600 4550 1600 4950
Connection ~ 1600 4550
$Comp
L GND #PWR066
U 1 1 5881447B
P 1600 4950
F 0 "#PWR066" H 1600 4700 50  0001 C CNN
F 1 "GND" H 1600 4800 50  0000 C CNN
F 2 "" H 1600 4950 50  0000 C CNN
F 3 "" H 1600 4950 50  0000 C CNN
	1    1600 4950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR067
U 1 1 5881451F
P 2300 4950
F 0 "#PWR067" H 2300 4700 50  0001 C CNN
F 1 "GND" H 2300 4800 50  0000 C CNN
F 2 "" H 2300 4950 50  0000 C CNN
F 3 "" H 2300 4950 50  0000 C CNN
	1    2300 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 4850 2300 4850
Wire Wire Line
	2300 4850 2300 4950
NoConn ~ 2550 4350
NoConn ~ 2550 4450
NoConn ~ 2550 4550
NoConn ~ 2550 4650
NoConn ~ 2550 4750
Text GLabel 3900 4350 2    60   Input ~ 0
RFM_CS
Wire Wire Line
	3900 4350 3600 4350
Text GLabel 2450 4250 0    60   Input ~ 0
RFM_INT
Wire Wire Line
	2450 4250 2550 4250
Wire Wire Line
	2000 4150 2550 4150
$Comp
L RF-SMA-EDGE J2
U 1 1 58814EB3
P 8450 5500
F 0 "J2" H 8450 5750 60  0000 C CNN
F 1 "RF-SMA-EDGE" H 8450 5050 60  0000 C CNN
F 2 "RF-SMA-EDGE:RF-SMA-EDGE" H 8450 4950 60  0001 C CNN
F 3 "" H 8400 5450 60  0000 C CNN
	1    8450 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 5500 8050 5500
$Comp
L GND #PWR068
U 1 1 5881536E
P 9000 5900
F 0 "#PWR068" H 9000 5650 50  0001 C CNN
F 1 "GND" H 9000 5750 50  0000 C CNN
F 2 "" H 9000 5900 50  0000 C CNN
F 3 "" H 9000 5900 50  0000 C CNN
	1    9000 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 5850 9000 5850
Connection ~ 8400 5850
Connection ~ 8500 5850
Wire Wire Line
	9000 5850 9000 5900
Connection ~ 8600 5850
$EndSCHEMATC
