EESchema Schematic File Version 2  date 06/04/2017 11:38:52
LIBS:VentilationLignade-rescue
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
LIBS:VentilationLignade-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 2 2
Title ""
Date "6 apr 2017"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 1400 1350 0    60   Input ~ 0
END_1_1
Text HLabel 1400 2750 0    60   Input ~ 0
END_1_2
Text HLabel 1400 5500 0    60   Input ~ 0
END_2_2
Text HLabel 1400 4100 0    60   Input ~ 0
END_2_1
Text HLabel 1400 6900 0    60   Input ~ 0
12V_IN
Text HLabel 1400 7600 0    60   Input ~ 0
GND_12V
Text GLabel 7300 1450 2    60   Output ~ 0
ENDSTOP_1_1
Text GLabel 7300 2850 2    60   Output ~ 0
ENDSTOP_1_2
Text GLabel 7300 4200 2    60   Output ~ 0
ENDSTOP_2_1
Text GLabel 7300 5600 2    60   Output ~ 0
ENDSTOP_2_2
Text GLabel 7300 7000 2    60   Output ~ 0
12V_CHECK
$Comp
L OPTO-TRANSISTOR-RESCUE-VentilationLignade U2
U 1 1 55F3F4FD
P 3200 1550
AR Path="/55F3F4FD" Ref="U2"  Part="1" 
AR Path="/55ECC0F8/55F3F4FD" Ref="U2"  Part="1" 
F 0 "U2" H 3400 1850 60  0000 C CNN
F 1 "OPTO-TRANSISTOR" H 3300 1250 60  0000 C CNN
F 2 "SMD_Packages:SOIC-8-N" H 3200 1550 60  0001 C CNN
F 3 "~" H 3200 1550 60  0000 C CNN
	1    3200 1550
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-VentilationLignade R4
U 1 1 55F3F577
P 2050 1350
AR Path="/55F3F577" Ref="R4"  Part="1" 
AR Path="/55ECC0F8/55F3F577" Ref="R4"  Part="1" 
F 0 "R4" V 2130 1350 40  0000 C CNN
F 1 "10K" V 2057 1351 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 1980 1350 30  0001 C CNN
F 3 "~" H 2050 1350 30  0000 C CNN
	1    2050 1350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1400 1350 1800 1350
Wire Wire Line
	2300 1350 2550 1350
$Comp
L DIODE D1
U 1 1 55F3F589
P 2350 1650
F 0 "D1" H 2350 1750 40  0000 C CNN
F 1 "DIODE" H 2350 1550 40  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 2350 1650 60  0001 C CNN
F 3 "~" H 2350 1650 60  0000 C CNN
	1    2350 1650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2350 1450 2350 1350
Connection ~ 2350 1350
Wire Wire Line
	2550 1650 2550 1950
Wire Wire Line
	2550 1950 2350 1950
Wire Wire Line
	2350 1950 2350 1850
$Comp
L R-RESCUE-VentilationLignade R9
U 1 1 55F3F5A2
P 4250 1350
AR Path="/55F3F5A2" Ref="R9"  Part="1" 
AR Path="/55ECC0F8/55F3F5A2" Ref="R9"  Part="1" 
F 0 "R9" V 4330 1350 40  0000 C CNN
F 1 "511K" V 4257 1351 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 4180 1350 30  0001 C CNN
F 3 "~" H 4250 1350 30  0000 C CNN
	1    4250 1350
	0    -1   -1   0   
$EndComp
$Comp
L C-RESCUE-VentilationLignade C9
U 1 1 55F3F5B1
P 4200 1150
AR Path="/55F3F5B1" Ref="C9"  Part="1" 
AR Path="/55ECC0F8/55F3F5B1" Ref="C9"  Part="1" 
F 0 "C9" H 4200 1250 40  0000 L CNN
F 1 "100nF" H 4206 1065 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4238 1000 30  0001 C CNN
F 3 "~" H 4200 1150 60  0000 C CNN
	1    4200 1150
	0    -1   -1   0   
$EndComp
$Comp
L GND-RESCUE-VentilationLignade #PWR043
U 1 1 55F3F5C0
P 4650 2050
AR Path="/55F3F5C0" Ref="#PWR043"  Part="1" 
AR Path="/55ECC0F8/55F3F5C0" Ref="#PWR043"  Part="1" 
F 0 "#PWR043" H 4650 2050 30  0001 C CNN
F 1 "GND" H 4650 1980 30  0001 C CNN
	1    4650 2050
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-VentilationLignade #PWR044
U 1 1 55F3F5CF
P 4950 1250
AR Path="/55F3F5CF" Ref="#PWR044"  Part="1" 
AR Path="/55ECC0F8/55F3F5CF" Ref="#PWR044"  Part="1" 
F 0 "#PWR044" H 4950 1250 30  0001 C CNN
F 1 "GND" H 4950 1180 30  0001 C CNN
	1    4950 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 1350 4000 1350
Wire Wire Line
	3900 1350 3900 1150
Wire Wire Line
	3900 1150 4000 1150
Connection ~ 3900 1350
Wire Wire Line
	4400 1150 4950 1150
Wire Wire Line
	4950 1150 4950 1250
Wire Wire Line
	4500 1350 4700 1350
Wire Wire Line
	4700 1350 4700 1150
Connection ~ 4700 1150
Wire Wire Line
	4650 2050 4650 1750
$Comp
L R-RESCUE-VentilationLignade R14
U 1 1 55F3F61B
P 5200 1050
AR Path="/55F3F61B" Ref="R14"  Part="1" 
AR Path="/55ECC0F8/55F3F61B" Ref="R14"  Part="1" 
F 0 "R14" V 5280 1050 40  0000 C CNN
F 1 "1K" V 5207 1051 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 5130 1050 30  0001 C CNN
F 3 "~" H 5200 1050 30  0000 C CNN
	1    5200 1050
	1    0    0    -1  
$EndComp
$Comp
L +3.3V-RESCUE-VentilationLignade #PWR045
U 1 1 55F3F634
P 5200 700
AR Path="/55F3F634" Ref="#PWR045"  Part="1" 
AR Path="/55ECC0F8/55F3F634" Ref="#PWR045"  Part="1" 
F 0 "#PWR045" H 5200 660 30  0001 C CNN
F 1 "+3.3V" H 5200 810 30  0000 C CNN
	1    5200 700 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 1450 7300 1450
Wire Wire Line
	5200 1450 5200 1300
Connection ~ 5200 1450
$Comp
L OPTO-TRANSISTOR-RESCUE-VentilationLignade U3
U 1 1 55F3F66D
P 3200 2950
AR Path="/55F3F66D" Ref="U3"  Part="1" 
AR Path="/55ECC0F8/55F3F66D" Ref="U3"  Part="1" 
F 0 "U3" H 3400 3250 60  0000 C CNN
F 1 "OPTO-TRANSISTOR" H 3300 2650 60  0000 C CNN
F 2 "SMD_Packages:SOIC-8-N" H 3200 2950 60  0001 C CNN
F 3 "~" H 3200 2950 60  0000 C CNN
	1    3200 2950
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-VentilationLignade R5
U 1 1 55F3F673
P 2050 2750
AR Path="/55F3F673" Ref="R5"  Part="1" 
AR Path="/55ECC0F8/55F3F673" Ref="R5"  Part="1" 
F 0 "R5" V 2130 2750 40  0000 C CNN
F 1 "R" V 2057 2751 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 1980 2750 30  0001 C CNN
F 3 "~" H 2050 2750 30  0000 C CNN
	1    2050 2750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1400 2750 1800 2750
Wire Wire Line
	2300 2750 2550 2750
$Comp
L DIODE D2
U 1 1 55F3F67B
P 2350 3050
F 0 "D2" H 2350 3150 40  0000 C CNN
F 1 "DIODE" H 2350 2950 40  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 2350 3050 60  0001 C CNN
F 3 "~" H 2350 3050 60  0000 C CNN
	1    2350 3050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2350 2850 2350 2750
Connection ~ 2350 2750
Wire Wire Line
	2550 3050 2550 3350
Wire Wire Line
	2550 3350 2350 3350
Wire Wire Line
	2350 3350 2350 3250
$Comp
L R-RESCUE-VentilationLignade R10
U 1 1 55F3F686
P 4250 2750
AR Path="/55F3F686" Ref="R10"  Part="1" 
AR Path="/55ECC0F8/55F3F686" Ref="R10"  Part="1" 
F 0 "R10" V 4330 2750 40  0000 C CNN
F 1 "511K" V 4257 2751 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 4180 2750 30  0001 C CNN
F 3 "~" H 4250 2750 30  0000 C CNN
	1    4250 2750
	0    -1   -1   0   
$EndComp
$Comp
L C-RESCUE-VentilationLignade C10
U 1 1 55F3F68C
P 4200 2550
AR Path="/55F3F68C" Ref="C10"  Part="1" 
AR Path="/55ECC0F8/55F3F68C" Ref="C10"  Part="1" 
F 0 "C10" H 4200 2650 40  0000 L CNN
F 1 "100nF" H 4206 2465 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4238 2400 30  0001 C CNN
F 3 "~" H 4200 2550 60  0000 C CNN
	1    4200 2550
	0    -1   -1   0   
$EndComp
$Comp
L GND-RESCUE-VentilationLignade #PWR046
U 1 1 55F3F692
P 4650 3450
AR Path="/55F3F692" Ref="#PWR046"  Part="1" 
AR Path="/55ECC0F8/55F3F692" Ref="#PWR046"  Part="1" 
F 0 "#PWR046" H 4650 3450 30  0001 C CNN
F 1 "GND" H 4650 3380 30  0001 C CNN
	1    4650 3450
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-VentilationLignade #PWR047
U 1 1 55F3F698
P 4950 2650
AR Path="/55F3F698" Ref="#PWR047"  Part="1" 
AR Path="/55ECC0F8/55F3F698" Ref="#PWR047"  Part="1" 
F 0 "#PWR047" H 4950 2650 30  0001 C CNN
F 1 "GND" H 4950 2580 30  0001 C CNN
	1    4950 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 2750 4000 2750
Wire Wire Line
	3900 2750 3900 2550
Wire Wire Line
	3900 2550 4000 2550
Connection ~ 3900 2750
Wire Wire Line
	4400 2550 4950 2550
Wire Wire Line
	4950 2550 4950 2650
Wire Wire Line
	4500 2750 4700 2750
Wire Wire Line
	4700 2750 4700 2550
Connection ~ 4700 2550
Wire Wire Line
	4650 3450 4650 3150
$Comp
L R-RESCUE-VentilationLignade R15
U 1 1 55F3F6A9
P 5200 2450
AR Path="/55F3F6A9" Ref="R15"  Part="1" 
AR Path="/55ECC0F8/55F3F6A9" Ref="R15"  Part="1" 
F 0 "R15" V 5280 2450 40  0000 C CNN
F 1 "R" V 5207 2451 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 5130 2450 30  0001 C CNN
F 3 "~" H 5200 2450 30  0000 C CNN
	1    5200 2450
	1    0    0    -1  
$EndComp
$Comp
L +3.3V-RESCUE-VentilationLignade #PWR048
U 1 1 55F3F6AF
P 5200 2100
AR Path="/55F3F6AF" Ref="#PWR048"  Part="1" 
AR Path="/55ECC0F8/55F3F6AF" Ref="#PWR048"  Part="1" 
F 0 "#PWR048" H 5200 2060 30  0001 C CNN
F 1 "+3.3V" H 5200 2210 30  0000 C CNN
	1    5200 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 2850 7300 2850
Wire Wire Line
	5200 2850 5200 2700
Connection ~ 5200 2850
$Comp
L OPTO-TRANSISTOR-RESCUE-VentilationLignade U4
U 1 1 55F3F6BA
P 3200 4300
AR Path="/55F3F6BA" Ref="U4"  Part="1" 
AR Path="/55ECC0F8/55F3F6BA" Ref="U4"  Part="1" 
F 0 "U4" H 3400 4600 60  0000 C CNN
F 1 "OPTO-TRANSISTOR" H 3300 4000 60  0000 C CNN
F 2 "SMD_Packages:SOIC-8-N" H 3200 4300 60  0001 C CNN
F 3 "~" H 3200 4300 60  0000 C CNN
	1    3200 4300
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-VentilationLignade R6
U 1 1 55F3F6C0
P 2050 4100
AR Path="/55F3F6C0" Ref="R6"  Part="1" 
AR Path="/55ECC0F8/55F3F6C0" Ref="R6"  Part="1" 
F 0 "R6" V 2130 4100 40  0000 C CNN
F 1 "R" V 2057 4101 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 1980 4100 30  0001 C CNN
F 3 "~" H 2050 4100 30  0000 C CNN
	1    2050 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1400 4100 1800 4100
Wire Wire Line
	2300 4100 2550 4100
$Comp
L DIODE D3
U 1 1 55F3F6C8
P 2350 4400
F 0 "D3" H 2350 4500 40  0000 C CNN
F 1 "DIODE" H 2350 4300 40  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 2350 4400 60  0001 C CNN
F 3 "~" H 2350 4400 60  0000 C CNN
	1    2350 4400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2350 4200 2350 4100
Connection ~ 2350 4100
Wire Wire Line
	2550 4400 2550 4700
Wire Wire Line
	2550 4700 2350 4700
Wire Wire Line
	2350 4700 2350 4600
$Comp
L R-RESCUE-VentilationLignade R11
U 1 1 55F3F6D3
P 4250 4100
AR Path="/55F3F6D3" Ref="R11"  Part="1" 
AR Path="/55ECC0F8/55F3F6D3" Ref="R11"  Part="1" 
F 0 "R11" V 4330 4100 40  0000 C CNN
F 1 "511K" V 4257 4101 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 4180 4100 30  0001 C CNN
F 3 "~" H 4250 4100 30  0000 C CNN
	1    4250 4100
	0    -1   -1   0   
$EndComp
$Comp
L C-RESCUE-VentilationLignade C11
U 1 1 55F3F6D9
P 4200 3900
AR Path="/55F3F6D9" Ref="C11"  Part="1" 
AR Path="/55ECC0F8/55F3F6D9" Ref="C11"  Part="1" 
F 0 "C11" H 4200 4000 40  0000 L CNN
F 1 "100nF" H 4206 3815 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4238 3750 30  0001 C CNN
F 3 "~" H 4200 3900 60  0000 C CNN
	1    4200 3900
	0    -1   -1   0   
$EndComp
$Comp
L GND-RESCUE-VentilationLignade #PWR049
U 1 1 55F3F6DF
P 4650 4800
AR Path="/55F3F6DF" Ref="#PWR049"  Part="1" 
AR Path="/55ECC0F8/55F3F6DF" Ref="#PWR049"  Part="1" 
F 0 "#PWR049" H 4650 4800 30  0001 C CNN
F 1 "GND" H 4650 4730 30  0001 C CNN
	1    4650 4800
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-VentilationLignade #PWR050
U 1 1 55F3F6E5
P 4950 4000
AR Path="/55F3F6E5" Ref="#PWR050"  Part="1" 
AR Path="/55ECC0F8/55F3F6E5" Ref="#PWR050"  Part="1" 
F 0 "#PWR050" H 4950 4000 30  0001 C CNN
F 1 "GND" H 4950 3930 30  0001 C CNN
	1    4950 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 4100 4000 4100
Wire Wire Line
	3900 4100 3900 3900
Wire Wire Line
	3900 3900 4000 3900
Connection ~ 3900 4100
Wire Wire Line
	4400 3900 4950 3900
Wire Wire Line
	4950 3900 4950 4000
Wire Wire Line
	4500 4100 4700 4100
Wire Wire Line
	4700 4100 4700 3900
Connection ~ 4700 3900
Wire Wire Line
	4650 4800 4650 4500
$Comp
L R-RESCUE-VentilationLignade R16
U 1 1 55F3F6F6
P 5200 3800
AR Path="/55F3F6F6" Ref="R16"  Part="1" 
AR Path="/55ECC0F8/55F3F6F6" Ref="R16"  Part="1" 
F 0 "R16" V 5280 3800 40  0000 C CNN
F 1 "R" V 5207 3801 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 5130 3800 30  0001 C CNN
F 3 "~" H 5200 3800 30  0000 C CNN
	1    5200 3800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V-RESCUE-VentilationLignade #PWR051
U 1 1 55F3F6FC
P 5200 3450
AR Path="/55F3F6FC" Ref="#PWR051"  Part="1" 
AR Path="/55ECC0F8/55F3F6FC" Ref="#PWR051"  Part="1" 
F 0 "#PWR051" H 5200 3410 30  0001 C CNN
F 1 "+3.3V" H 5200 3560 30  0000 C CNN
	1    5200 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 4200 7300 4200
Wire Wire Line
	5200 4200 5200 4050
Connection ~ 5200 4200
$Comp
L OPTO-TRANSISTOR-RESCUE-VentilationLignade U5
U 1 1 55F3F707
P 3200 5700
AR Path="/55F3F707" Ref="U5"  Part="1" 
AR Path="/55ECC0F8/55F3F707" Ref="U5"  Part="1" 
F 0 "U5" H 3400 6000 60  0000 C CNN
F 1 "OPTO-TRANSISTOR" H 3300 5400 60  0000 C CNN
F 2 "SMD_Packages:SOIC-8-N" H 3200 5700 60  0001 C CNN
F 3 "~" H 3200 5700 60  0000 C CNN
	1    3200 5700
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-VentilationLignade R7
U 1 1 55F3F70D
P 2050 5500
AR Path="/55F3F70D" Ref="R7"  Part="1" 
AR Path="/55ECC0F8/55F3F70D" Ref="R7"  Part="1" 
F 0 "R7" V 2130 5500 40  0000 C CNN
F 1 "R" V 2057 5501 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 1980 5500 30  0001 C CNN
F 3 "~" H 2050 5500 30  0000 C CNN
	1    2050 5500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1400 5500 1800 5500
Wire Wire Line
	2300 5500 2550 5500
$Comp
L DIODE D4
U 1 1 55F3F715
P 2350 5800
F 0 "D4" H 2350 5900 40  0000 C CNN
F 1 "DIODE" H 2350 5700 40  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 2350 5800 60  0001 C CNN
F 3 "~" H 2350 5800 60  0000 C CNN
	1    2350 5800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2350 5600 2350 5500
Connection ~ 2350 5500
Wire Wire Line
	2550 5800 2550 6100
Wire Wire Line
	2550 6100 2350 6100
Wire Wire Line
	2350 6100 2350 6000
$Comp
L R-RESCUE-VentilationLignade R12
U 1 1 55F3F720
P 4250 5500
AR Path="/55F3F720" Ref="R12"  Part="1" 
AR Path="/55ECC0F8/55F3F720" Ref="R12"  Part="1" 
F 0 "R12" V 4330 5500 40  0000 C CNN
F 1 "511K" V 4257 5501 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 4180 5500 30  0001 C CNN
F 3 "~" H 4250 5500 30  0000 C CNN
	1    4250 5500
	0    -1   -1   0   
$EndComp
$Comp
L C-RESCUE-VentilationLignade C12
U 1 1 55F3F726
P 4200 5300
AR Path="/55F3F726" Ref="C12"  Part="1" 
AR Path="/55ECC0F8/55F3F726" Ref="C12"  Part="1" 
F 0 "C12" H 4200 5400 40  0000 L CNN
F 1 "100nF" H 4206 5215 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4238 5150 30  0001 C CNN
F 3 "~" H 4200 5300 60  0000 C CNN
	1    4200 5300
	0    -1   -1   0   
$EndComp
$Comp
L GND-RESCUE-VentilationLignade #PWR052
U 1 1 55F3F72C
P 4650 6200
AR Path="/55F3F72C" Ref="#PWR052"  Part="1" 
AR Path="/55ECC0F8/55F3F72C" Ref="#PWR052"  Part="1" 
F 0 "#PWR052" H 4650 6200 30  0001 C CNN
F 1 "GND" H 4650 6130 30  0001 C CNN
	1    4650 6200
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-VentilationLignade #PWR053
U 1 1 55F3F732
P 4950 5400
AR Path="/55F3F732" Ref="#PWR053"  Part="1" 
AR Path="/55ECC0F8/55F3F732" Ref="#PWR053"  Part="1" 
F 0 "#PWR053" H 4950 5400 30  0001 C CNN
F 1 "GND" H 4950 5330 30  0001 C CNN
	1    4950 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 5500 4000 5500
Wire Wire Line
	3900 5500 3900 5300
Wire Wire Line
	3900 5300 4000 5300
Connection ~ 3900 5500
Wire Wire Line
	4400 5300 4950 5300
Wire Wire Line
	4950 5300 4950 5400
Wire Wire Line
	4500 5500 4700 5500
Wire Wire Line
	4700 5500 4700 5300
Connection ~ 4700 5300
$Comp
L R-RESCUE-VentilationLignade R17
U 1 1 55F3F743
P 5200 5200
AR Path="/55F3F743" Ref="R17"  Part="1" 
AR Path="/55ECC0F8/55F3F743" Ref="R17"  Part="1" 
F 0 "R17" V 5280 5200 40  0000 C CNN
F 1 "R" V 5207 5201 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 5130 5200 30  0001 C CNN
F 3 "~" H 5200 5200 30  0000 C CNN
	1    5200 5200
	1    0    0    -1  
$EndComp
$Comp
L +3.3V-RESCUE-VentilationLignade #PWR054
U 1 1 55F3F749
P 5200 4850
AR Path="/55F3F749" Ref="#PWR054"  Part="1" 
AR Path="/55ECC0F8/55F3F749" Ref="#PWR054"  Part="1" 
F 0 "#PWR054" H 5200 4810 30  0001 C CNN
F 1 "+3.3V" H 5200 4960 30  0000 C CNN
	1    5200 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 5600 7300 5600
Wire Wire Line
	5200 5600 5200 5450
Connection ~ 5200 5600
Wire Wire Line
	4650 6200 4650 5900
$Comp
L OPTO-TRANSISTOR-RESCUE-VentilationLignade U6
U 1 1 55F3F75B
P 3200 7100
AR Path="/55F3F75B" Ref="U6"  Part="1" 
AR Path="/55ECC0F8/55F3F75B" Ref="U6"  Part="1" 
F 0 "U6" H 3400 7400 60  0000 C CNN
F 1 "OPTO-TRANSISTOR" H 3300 6800 60  0000 C CNN
F 2 "SMD_Packages:SOIC-8-N" H 3200 7100 60  0001 C CNN
F 3 "~" H 3200 7100 60  0000 C CNN
	1    3200 7100
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-VentilationLignade R8
U 1 1 55F3F761
P 2050 6900
AR Path="/55F3F761" Ref="R8"  Part="1" 
AR Path="/55ECC0F8/55F3F761" Ref="R8"  Part="1" 
F 0 "R8" V 2130 6900 40  0000 C CNN
F 1 "R" V 2057 6901 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 1980 6900 30  0001 C CNN
F 3 "~" H 2050 6900 30  0000 C CNN
	1    2050 6900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1400 6900 1800 6900
Wire Wire Line
	2300 6900 2550 6900
$Comp
L DIODE D5
U 1 1 55F3F769
P 2350 7200
F 0 "D5" H 2350 7300 40  0000 C CNN
F 1 "DIODE" H 2350 7100 40  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 2350 7200 60  0001 C CNN
F 3 "~" H 2350 7200 60  0000 C CNN
	1    2350 7200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2350 7000 2350 6900
Connection ~ 2350 6900
Wire Wire Line
	2550 7200 2550 7500
Wire Wire Line
	2550 7500 2350 7500
Wire Wire Line
	2350 7500 2350 7400
$Comp
L R-RESCUE-VentilationLignade R13
U 1 1 55F3F774
P 4250 6900
AR Path="/55F3F774" Ref="R13"  Part="1" 
AR Path="/55ECC0F8/55F3F774" Ref="R13"  Part="1" 
F 0 "R13" V 4330 6900 40  0000 C CNN
F 1 "511K" V 4257 6901 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 4180 6900 30  0001 C CNN
F 3 "~" H 4250 6900 30  0000 C CNN
	1    4250 6900
	0    -1   -1   0   
$EndComp
$Comp
L C-RESCUE-VentilationLignade C13
U 1 1 55F3F77A
P 4200 6700
AR Path="/55F3F77A" Ref="C13"  Part="1" 
AR Path="/55ECC0F8/55F3F77A" Ref="C13"  Part="1" 
F 0 "C13" H 4200 6800 40  0000 L CNN
F 1 "100nF" H 4206 6615 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4238 6550 30  0001 C CNN
F 3 "~" H 4200 6700 60  0000 C CNN
	1    4200 6700
	0    -1   -1   0   
$EndComp
$Comp
L GND-RESCUE-VentilationLignade #PWR055
U 1 1 55F3F780
P 4650 7600
AR Path="/55F3F780" Ref="#PWR055"  Part="1" 
AR Path="/55ECC0F8/55F3F780" Ref="#PWR055"  Part="1" 
F 0 "#PWR055" H 4650 7600 30  0001 C CNN
F 1 "GND" H 4650 7530 30  0001 C CNN
	1    4650 7600
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-VentilationLignade #PWR056
U 1 1 55F3F786
P 4950 6800
AR Path="/55F3F786" Ref="#PWR056"  Part="1" 
AR Path="/55ECC0F8/55F3F786" Ref="#PWR056"  Part="1" 
F 0 "#PWR056" H 4950 6800 30  0001 C CNN
F 1 "GND" H 4950 6730 30  0001 C CNN
	1    4950 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 6900 4000 6900
Wire Wire Line
	3900 6900 3900 6700
Wire Wire Line
	3900 6700 4000 6700
Connection ~ 3900 6900
Wire Wire Line
	4400 6700 4950 6700
Wire Wire Line
	4950 6700 4950 6800
Wire Wire Line
	4500 6900 4700 6900
Wire Wire Line
	4700 6900 4700 6700
Connection ~ 4700 6700
Wire Wire Line
	4650 7600 4650 7300
$Comp
L R-RESCUE-VentilationLignade R18
U 1 1 55F3F797
P 5200 6600
AR Path="/55F3F797" Ref="R18"  Part="1" 
AR Path="/55ECC0F8/55F3F797" Ref="R18"  Part="1" 
F 0 "R18" V 5280 6600 40  0000 C CNN
F 1 "R" V 5207 6601 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 5130 6600 30  0001 C CNN
F 3 "~" H 5200 6600 30  0000 C CNN
	1    5200 6600
	1    0    0    -1  
$EndComp
$Comp
L +3.3V-RESCUE-VentilationLignade #PWR057
U 1 1 55F3F79D
P 5200 6250
AR Path="/55F3F79D" Ref="#PWR057"  Part="1" 
AR Path="/55ECC0F8/55F3F79D" Ref="#PWR057"  Part="1" 
F 0 "#PWR057" H 5200 6210 30  0001 C CNN
F 1 "+3.3V" H 5200 6360 30  0000 C CNN
	1    5200 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 7000 7300 7000
Wire Wire Line
	5200 7000 5200 6850
Connection ~ 5200 7000
Wire Wire Line
	5200 3450 5200 3550
Wire Wire Line
	5200 2100 5200 2200
Wire Wire Line
	5200 700  5200 800 
Wire Wire Line
	5200 4850 5200 4950
Wire Wire Line
	5200 6250 5200 6350
Wire Wire Line
	2500 1950 2500 7650
Connection ~ 2500 3350
Connection ~ 2500 1950
Connection ~ 2500 4700
Connection ~ 2500 6100
Connection ~ 2500 7500
$Comp
L GNDPWR #PWR058
U 1 1 55F3FD73
P 2500 7650
F 0 "#PWR058" H 2500 7700 40  0001 C CNN
F 1 "GNDPWR" H 2500 7570 40  0000 C CNN
	1    2500 7650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 7600 2500 7600
Connection ~ 2500 7600
$Comp
L R-RESCUE-VentilationLignade R19
U 1 1 55F403F8
P 4200 1750
AR Path="/55F403F8" Ref="R19"  Part="1" 
AR Path="/55ECC0F8/55F403F8" Ref="R19"  Part="1" 
F 0 "R19" V 4280 1750 40  0000 C CNN
F 1 "0Ohms" V 4207 1751 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 4130 1750 30  0001 C CNN
F 3 "~" H 4200 1750 30  0000 C CNN
	1    4200 1750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3800 1750 3950 1750
Wire Wire Line
	4650 1750 4450 1750
$Comp
L R-RESCUE-VentilationLignade R20
U 1 1 55F404EA
P 4200 3150
AR Path="/55F404EA" Ref="R20"  Part="1" 
AR Path="/55ECC0F8/55F404EA" Ref="R20"  Part="1" 
F 0 "R20" V 4280 3150 40  0000 C CNN
F 1 "R" V 4207 3151 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 4130 3150 30  0001 C CNN
F 3 "~" H 4200 3150 30  0000 C CNN
	1    4200 3150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3800 3150 3950 3150
Wire Wire Line
	4650 3150 4450 3150
$Comp
L R-RESCUE-VentilationLignade R21
U 1 1 55F404F2
P 4200 4500
AR Path="/55F404F2" Ref="R21"  Part="1" 
AR Path="/55ECC0F8/55F404F2" Ref="R21"  Part="1" 
F 0 "R21" V 4280 4500 40  0000 C CNN
F 1 "R" V 4207 4501 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 4130 4500 30  0001 C CNN
F 3 "~" H 4200 4500 30  0000 C CNN
	1    4200 4500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4650 4500 4450 4500
$Comp
L R-RESCUE-VentilationLignade R22
U 1 1 55F404F9
P 4200 5900
AR Path="/55F404F9" Ref="R22"  Part="1" 
AR Path="/55ECC0F8/55F404F9" Ref="R22"  Part="1" 
F 0 "R22" V 4280 5900 40  0000 C CNN
F 1 "R" V 4207 5901 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 4130 5900 30  0001 C CNN
F 3 "~" H 4200 5900 30  0000 C CNN
	1    4200 5900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3800 5900 3950 5900
Wire Wire Line
	4650 5900 4450 5900
$Comp
L R-RESCUE-VentilationLignade R23
U 1 1 55F40501
P 4200 7300
AR Path="/55F40501" Ref="R23"  Part="1" 
AR Path="/55ECC0F8/55F40501" Ref="R23"  Part="1" 
F 0 "R23" V 4280 7300 40  0000 C CNN
F 1 "R" V 4207 7301 40  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 4130 7300 30  0001 C CNN
F 3 "~" H 4200 7300 30  0000 C CNN
	1    4200 7300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4650 7300 4450 7300
Wire Wire Line
	3800 4500 3950 4500
Wire Wire Line
	3950 7300 3800 7300
NoConn ~ 2850 5900
NoConn ~ 2850 7300
NoConn ~ 2850 4500
NoConn ~ 2850 1750
NoConn ~ 2850 3150
NoConn ~ 9100 2000
$EndSCHEMATC
