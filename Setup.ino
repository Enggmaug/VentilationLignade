
void setup() {
  // si Debug autorisé, alors démarrage de la liaison serie
#if DEBUG
  Serial.begin(9600);
#endif
  // Pins EndStops
#if ENDSTOPS
  pinMode(ENDSTOP1_1, INPUT);
  pinMode(ENDSTOP1_2, INPUT);
#if BYPASS_1
  pinMode(ENDSTOP2_1, INPUT);
  pinMode(ENDSTOP2_2, INPUT);
#endif
#endif

  // Pins Thermostats
  pinMode(T_EXT_15, INPUT);
  pinMode(T_EXT_24, INPUT);
  pinMode(T_INT_22, INPUT);
  pinMode(T_CHEMINEE, INPUT);

  //Pins Bypass
  pinMode(BYPASS_2_1, OUTPUT);
  digitalWrite(BYPASS_2_1, BYPASS_DESACT);
  pinMode(BYPASS_2_2, OUTPUT);
  digitalWrite(BYPASS_2_2, BYPASS_DESACT);
  pinMode(BYPASS_1_1, OUTPUT);
  digitalWrite(BYPASS_1_1, BYPASS_DESACT);
  pinMode(BYPASS_1_2, OUTPUT);
  digitalWrite(BYPASS_1_2, BYPASS_DESACT);

  //Pins Ventilos
  pinMode(VENT_CHEMINEE, OUTPUT);
  VentiloArret(VENT_CHEMINEE);
  pinMode(VENT_CAVE, OUTPUT);
  VentiloArret(VENT_CAVE);

  //Pin VMC
  pinMode(SELECT_VMC, OUTPUT);
  VMC_Double();

  //Pins Monitoring 12V
  pinMode(V12_1, OUTPUT);
#if MONITORING_12V
  pinMode(V12_SEL, OUTPUT);
  pinMode(V12_2, OUTPUT);
  pinMode(V12_IN, INPUT);
#endif

  Alim_Off();

  Mode = NORMAL;

  NewInputs.InputTempOut15 = TempOver(T_EXT_15);
  NewInputs.InputTempOut24 = TempOver(T_EXT_24);
  NewInputs.InputTempInt22 = TempOver(T_INT_22);
  NewInputs.InputTempCheminee = TempOver(T_CHEMINEE);
  OldInputs = NewInputs;

  FirstLoop = true;

  SdCardPresent = SD.begin(SDCARD_CS);

  // Mise en route de l'affichage
  tft.begin();

  tft.setRotation(3);
  tft.fillScreen(ILI9340_BLACK);
}

