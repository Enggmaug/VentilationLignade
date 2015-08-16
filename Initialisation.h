
/*-----------------------------------------------------------*/
/*----- Fonction d'initialisation                       -----*/
/*-----------------------------------------------------------*/
void PinsSetup() {
// Pins EndStops
#if ENDSTOPS
  #if BYPASS1
    pinMode(ENDSTOP1_1, INPUT);
    pinMode(ENDSTOP1_2, INPUT);
  #endif
  #if BYPASS2
    pinMode(ENDSTOP2_1, INPUT);
    pinMode(ENDSTOP2_2, INPUT);
  #endif
#endif

// Pins Thermostats
#if THERMOSTATS
    pinMode(THERM_1, INPUT);
    pinMode(THERM_2, INPUT);
    pinMode(THERM_3, INPUT);
    pinMode(THERM_4, INPUT);
#endif

//Pins Bypass
#if BYPASS1
    pinMode(BYPASS1_1, OUTPUT);
    pinMode(BYPASS1_2, OUTPUT);
#endif
#if BYPASS2
    pinMode(BYPASS2_1, OUTPUT);
    pinMode(BYPASS2_2, OUTPUT);
#endif

//Pins Ventilos
#if VENTILOS
    pinMode(VENT_1, OUTPUT);
    pinMode(VENT_2, OUTPUT);
    pinMode(VENT_3, OUTPUT);
    pinMode(VENT_4, OUTPUT);        
#endif

//Pins Monitoring 12V

    pinMode(V12_1, OUTPUT);
#if MONITORING_12V
    pinMode(V12_ON, OUTPUT);
    pinMode(V12_2, OUTPUT);
    pinMode(V12_IN, INPUT);
#endif

}
