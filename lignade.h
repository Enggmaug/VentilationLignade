/*----- Definition des constantes de base               -----*/
#define TEMPS_BYPASS 30000//Temps de fermeture/ouverture d'un Bypass

/*----- Utilisation des Pins IO                         -----*/
//#define SPARE          0
//#define SPARE          1
//#define SPARE          2
#define BYPASS_1_1     3
#define BYPASS_1_2     4
#define BYPASS_2_1     5
#define BYPASS_2_2     6
//#define SPARE          7
//#define SPARE          8
#define TFT_DC        9
#define TFT_CS        10
#define TFT_RST       -1
#define SPI_MOSI      11
#define SPI_MISO      12
#define SPI_SCK       13
//#define SPARE          14
#define SDCARD_CS     15
#define ENDSTOP2_2    16
#define ENDSTOP2_1    17
#define ENDSTOP1_2    18
#define ENDSTOP1_1    19
#define T_EXT_15      20 // changé pour etre sur une pin CS pour thermocouple SPI => Futur SPARE
#define T_EXT_24      21 // changé pour etre sur une pin CS pour thermocouple SPI
#define T_INT_22      22 // changé pour etre sur une pin CS pour thermocouple SPI
#define T_CHEMINEE    23 // changé pour etre sur une pin CS pour thermocouple SPI


#define VENT_CHEMINEE 24 //   -- Penser à changer les branchements
#define VENT_CAVE     25 //   -- Penser à changer les branchements
#define SELECT_VMC    26 //   -- Penser à changer les branchements
#define V12_1         27 //   -- Penser à changer les branchements
#define V12_2         28 //   -- Penser à changer les branchements
#define V12_SEL       29 //   -- Penser à changer les branchements
#define V12_IN        30 //   -- Penser à changer les branchements
#define SWITCH_MENU   31
#define MENU_A        32
#define MENU_B        33

/*----- Autorise/Inhibe l'utilisation des blocs         -----*/
#define ENDSTOPS 0                     //Facultatif
#define MONITORING_12V 0               //Facultatif

/*----- Methode alternative aux blocs inhibés           -----*/
//Thermostats
#define TempOver(Thermostat) not(digitalRead(Thermostat))

//EndStops
#define ENDSTOP_OPEN HIGH
#define ENDSTOP_CLOSED LOW

#define EndStopIsClosed(EndStop) digitalRead(EndStop)


//ByPass
#define BYPASS_ACT LOW
#define BYPASS_DESACT HIGH
//!!Ajouter Timeout
#if ENDSTOPS
//A Ecrire
#else
#define BYPASS_2Ouvrir() {Display_Wait();Alim_On();digitalWrite(BYPASS_2_1,BYPASS_ACT);delay(TEMPS_BYPASS);digitalWrite(BYPASS_2_1,BYPASS_DESACT);Alim_Off();}
#define BYPASS_2Fermer() {Display_Wait();Alim_On();digitalWrite(BYPASS_2_2,BYPASS_ACT);delay(TEMPS_BYPASS);digitalWrite(BYPASS_2_2,BYPASS_DESACT);Alim_Off();}
#endif

#if ENDSTOPS
//A Ecrire
#else
#define BYPASS_1Ouvrir() {Display_Wait();Alim_On();digitalWrite(BYPASS_1_1,BYPASS_ACT);delay(TEMPS_BYPASS/2);VMC_Simple();delay(TEMPS_BYPASS/2);digitalWrite(BYPASS_1_1,BYPASS_DESACT);Alim_Off();}
#define BYPASS_1Fermer() {Display_Wait();Alim_On();digitalWrite(BYPASS_1_2,BYPASS_ACT);delay(TEMPS_BYPASS/2);VMC_Double();delay(TEMPS_BYPASS/2);digitalWrite(BYPASS_1_2,BYPASS_DESACT);Alim_Off();}
#endif

//Ventilos
#define VENT_ON LOW
#define VENT_OFF HIGH
#define VentiloMarche(Ventilo) {digitalWrite(Ventilo,VENT_ON);}
#define VentiloArret(Ventilo) {digitalWrite(Ventilo,VENT_OFF);}
#define VMC_Double() {digitalWrite(SELECT_VMC,VENT_OFF);}
#define VMC_Simple() {digitalWrite(SELECT_VMC,VENT_ON);}

//Monitoring 12V
#define ALIM_ON LOW
#define ALIM_OFF HIGH
#if MONITORING_12V
#define Alim_Off() { }// A ecrire
#else
#define Alim_Off() {digitalWrite(V12_1,ALIM_OFF);}
#endif

signed char AlimToUse = V12_1;
#if MONITORING_12V
#define Alim_On() { }// A ecrire
#else
#define Alim_On() {digitalWrite(V12_1,ALIM_ON);delay(1000);}
#endif


