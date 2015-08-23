/*----- Definition des constantes de base               -----*/
#define TEMPS_BYPASS 30000//Temps de fermeture/ouverture d'un Bypass

/*----- Utilisation des Pins IO                         -----*/
#define ENDSTOP1_1    22
#define ENDSTOP1_2    21
#define ENDSTOP2_1    20
#define ENDSTOP2_2    19
#define T_EXT_15      18
#define T_EXT_24      17
#define T_INT_22      16
#define T_CHEMINEE    14
#define BYPASS_1_1     3
#define BYPASS_1_2     4
#define BYPASS_2_1     5
#define BYPASS_2_2     6
#define VENT_CHEMINEE 7
#define VENT_CAVE     8
#define VENT_4        23
#define SELECT_VMC    9
#define V12_1         0
#define V12_2         2
#define V12_SEL       1    // a interchanger avec V12_IN (pour LED)
#define V12_IN        13   // a interchanger avec V12_SEL


/*----- Autorise/Inhibe l'utilisation des blocs         -----*/
#define ENDSTOPS 0                     //Facultatif
#define MONITORING_12V 0               //Facultatif

/*----- Methode alternative aux blocs inhibés           -----*/
//Thermostats
#define THERM_ON HIGH
#define THERM_OFF LOW

#define TempOver(Thermostat) digitalRead(Thermostat)

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
#define BYPASS_2Ouvrir() {Alim_On();digitalWrite(BYPASS_2_1,BYPASS_ACT);delay(TEMPS_BYPASS);digitalWrite(BYPASS_2_1,BYPASS_DESACT);Alim_Off();}
#define BYPASS_2Fermer() {Alim_On();digitalWrite(BYPASS_2_2,BYPASS_ACT);delay(TEMPS_BYPASS);digitalWrite(BYPASS_2_2,BYPASS_DESACT);Alim_Off();}
#endif

#if ENDSTOPS
//A Ecrire
#else
#define BYPASS_1Ouvrir() {Alim_On();digitalWrite(BYPASS_1_1,BYPASS_ACT);delay(TEMPS_BYPASS/2);VMC_Double();delay(TEMPS_BYPASS/2);digitalWrite(BYPASS_1_1,BYPASS_DESACT);Alim_Off();}
#define BYPASS_1Fermer() {Alim_On();digitalWrite(BYPASS_1_2,BYPASS_ACT);delay(TEMPS_BYPASS/2);VMC_Simple();delay(TEMPS_BYPASS/2);digitalWrite(BYPASS_1_2,BYPASS_DESACT);Alim_Off();}
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


