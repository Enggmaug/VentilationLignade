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
LIBS:special
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
LIBS:VentilationLignade-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title ""
Date "9 sep 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 1600 1600 0    60   Input ~ 0
END_1_1
Text HLabel 1600 1950 0    60   Input ~ 0
END_1_2
Text HLabel 1600 2500 0    60   Input ~ 0
END_2_2
Text HLabel 1600 2250 0    60   Input ~ 0
END_2_1
Text HLabel 1550 3100 0    60   Input ~ 0
12V_IN
Text HLabel 1550 3500 0    60   Input ~ 0
GND_12V
Text GLabel 7300 1450 2    60   Output ~ 0
ENDSTOP_1_1
Text GLabel 7300 1700 2    60   Output ~ 0
ENDSTOP_1_2
Text GLabel 7350 1950 2    60   Output ~ 0
ENDSTOP_2_1
Text GLabel 7350 2250 2    60   Output ~ 0
ENDSTOP_2_2
Text GLabel 7300 3150 2    60   Output ~ 0
12V_CHECK
$Comp
L GNDPWR #PWR046
U 1 1 55ECC2EB
P 2050 3650
F 0 "#PWR046" H 2050 3700 40  0001 C CNN
F 1 "GNDPWR" H 2050 3570 40  0000 C CNN
F 2 "" H 2050 3650 60  0000 C CNN
F 3 "" H 2050 3650 60  0000 C CNN
	1    2050 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 3500 2050 3500
Wire Wire Line
	2050 3500 2050 3650
Wire Wire Line
	1550 3100 4700 3100
Wire Wire Line
	4700 3100 4700 3150
Wire Wire Line
	4700 3150 7300 3150
Wire Wire Line
	7350 2250 4150 2250
Wire Wire Line
	4150 2250 4150 2500
Wire Wire Line
	4150 2500 1600 2500
Wire Wire Line
	1600 2250 3600 2250
Wire Wire Line
	3600 2250 3600 1950
Wire Wire Line
	3600 1950 7350 1950
Wire Wire Line
	7300 1700 3250 1700
Wire Wire Line
	3250 1700 3250 1950
Wire Wire Line
	3250 1950 1600 1950
Wire Wire Line
	1600 1600 4150 1600
Wire Wire Line
	4150 1600 4150 1450
Wire Wire Line
	4150 1450 7300 1450
$EndSCHEMATC
