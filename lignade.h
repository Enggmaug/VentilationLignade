/*----- Definition des constantes de base               -----*/
#define TEMPS_BYPASS 5000//Temps de fermeture/ouverture d'un Bypass

/*----- Utilisation des Pins IO                         -----*/
#define ENDSTOP1_1 22
#define ENDSTOP1_2 21
#define ENDSTOP2_1 20
#define ENDSTOP2_2 19
#define THERM_1    18
#define THERM_2    17
#define THERM_3    16
#define THERM_4    14
#define BYPASS1_1  3
#define BYPASS1_2  4
#define BYPASS2_1  5
#define BYPASS2_2  6
#define VENT_1     7
#define VENT_2     8
#define VENT_3     9
#define VENT_4     16
#define V12_1      0
#define V12_2      1
#define V12_ON     2    // a interchanger avec V12_IN (pour LED)
#define V12_IN     13   // a interchanger avec V12_ON


/*----- Autorise/Inhibe l'utilisation des blocs         -----*/
#define THERMOSTATS 0                  //obligatoire
#define ENDSTOPS 0                     //Facultatif
#define BYPASS1 0                      //obligatoire
#define BYPASS2 0                      //Facultatif
#define VENTILOS 0                     //obligatoire
#define MONITORING_12V 0               //Facultatif

/*----- Methode alternative aux blocs inhibés           -----*/
//Thermostats
#define THERM_ON HIGH
#define THERM_OFF LOW
#if THERMOSTATS
    #define TempOver(Thermostat) {digitalRead(Thermostat)}
#else
    #define TempOver(Thermostat){return(THERM_OFF);}
#endif

//EndStops
#define ENDSTOP_OPEN HIGH
#define ENDSTOP_CLOSED LOW
#if ENDSTOPS
    #define EndStopIsClosed(EndStop) {digitalRead(EndStop)}
#else
    #define EndStopIsClosed(EndStop){delay(TEMPS_BYPASS);return ENDSTOP_CLOSED}
#endif

//ByPass
#define BYPASS_ACT HIGH
#define BYPASS_DESACT LOW
#if BYPASS1                           //!!Ajouter Timeout
    #define Bypass1Ouvrir() {\
    digitalWrite(BYPASS1_1;BYPASS_ACT);\
    while(EndStopIsClosed(ENDSTOP1_1)!= ENDSTOP_CLOSED);\
    digitalWrite(BYPASS1_1;BYPASS_DESACT)}
    
    #define Bypass1Fermer() {\
    digitalWrite(BYPASS1_2;BYPASS_ACT);\
    while(EndStopIsClosed(ENDSTOP1_2)!= ENDSTOP_CLOSED);\
    digitalWrite(BYPASS1_2;BYPASS_DESACT)}
#else
     #define Bypass1Ouvrir() {}
     #define Bypass1Fermer() {}
#endif
#if BYPASS2                           //!!Ajouter Timeout
    #define Bypass1Ouvrir() {\
    digitalWrite(BYPASS2_1;BYPASS_ACT);\
    while(EndStopIsClosed(ENDSTOP2_1)!= ENDSTOP_CLOSED);\
    digitalWrite(BYPASS2_1;BYPASS_DESACT)}
    
    #define Bypass1Fermer() {\
    digitalWrite(BYPASS2_2;BYPASS_ACT);\
    while(EndStopIsClosed(ENDSTOP2_2)!= ENDSTOP_CLOSED);\
    digitalWrite(BYPASS2_2;BYPASS_DESACT)}
#else
     #define Bypass2Ouvrir() {}
     #define Bypass2Fermer() {}
#endif

//Ventilos
#define VENT_ON HIGH
#define VENT_OFF LOW
#if VENTILOS
    #define VentiloMarche(Ventilo) {digitalWrite(Ventilo;VENT_ON)}
    #define VentiloArret(Ventilo) {digitalWrite(Ventilo;VENT_OFF)}    
#else
    #define VentiloMarche(Ventilo) {}
    #define VentiloArret(Ventilo) {}    
#endif

//Monitoring 12V
#define ALIM_ON HIGH
#define ALIM_OFF LOW
#if MONITORING_12V
#define Alim_Off() {digitalWrite(V12_ON;ALIM_OFF);\
    delay(200);\
    digitalWrite(V12_1;ALIM_OFF);\
    delay(200);\
    digitalWrite(V12_2;ALIM_OFF)}
#else
#define Alim_Off() {digitalWrite(V12_1;ALIM_OFF);
#endif

signed char AlimToUse = V12_1;
#if MONITORING_12V
#define Alim_On() {\
    digitalWrite(V12_ON;ALIM_ON);\
    delay(200);\
    if (AlimToUse != -1){digitalWrite((unsigned int)AlimToUse;ALIM_ON)}\
    delay(300);\
    if(digitalRead(V12_IN)==ALIM_OFF) {\
        AlimToUse?V12_1=V12_2:-1;\
        digitalWrite(V12_1;ALIM_OFF);\
        delay(200);\
        digitalWrite(V12_2;ALIM_OFF);\
        delay(200);\
        Alim_On()}}
#else
    #define Alim_On() {digitalWrite(V12_1;ALIM_ON);}
#endif
