void setup(void)
{
  int idx;
  
  pinMode(RTCLK_CS, OUTPUT);       // chip select pin
  pinMode(COD_CLK, INPUT);
  pinMode(COD_DT, INPUT);
  pinMode(COD_SW, INPUT);
  pinMode(RTCLK_INT, INPUT);

 pinMode( BYPASS_1_F, OUTPUT);
 pinMode( BYPASS_1_O, OUTPUT);
 pinMode( BYPASS_2_F, OUTPUT);
 pinMode( BYPASS_2_O, OUTPUT);
 pinMode( VENT_CAVE, OUTPUT);
 pinMode( VENT_CHEM, OUTPUT);
 pinMode( V12_1_ON, OUTPUT);
 pinMode( SELECT_VMC, OUTPUT);
 pinMode( V12_2_ON, OUTPUT);
 pinMode( SELECT_12V, OUTPUT);

 digitalWrite(BYPASS_1_F ,true);
 digitalWrite(BYPASS_1_O ,true);
 digitalWrite(BYPASS_2_F ,true);
 digitalWrite(BYPASS_2_O ,true);
 digitalWrite(VENT_CAVE ,true);
 digitalWrite(VENT_CHEM ,true);
 digitalWrite(V12_1_ON ,true);
 digitalWrite(SELECT_VMC ,true);
 digitalWrite(V12_2_ON ,true);
 digitalWrite(SELECT_12V ,true);

  tft.begin();
  delay(2000);
  DS3234_init(RTCLK_CS, DS3234_INTCN);

  MenuChanged = true;
  RotDetect = false;
  delay(1000);

  /*Mise en place des interruptions pour les mouvements du codeur*/
  attachInterrupt(digitalPinToInterrupt(COD_DT),    RotationDetectDT,  CHANGE  );
  attachInterrupt(digitalPinToInterrupt(COD_CLK),   RotationDetectCLK, CHANGE  );
  attachInterrupt(digitalPinToInterrupt(COD_SW),    Selection,         RISING  );
  attachInterrupt(digitalPinToInterrupt(RTCLK_INT), RTClockInterrupt,  FALLING );

  /*Start des services*/
  Serial.begin(9600);
  SdCardPresent = SD.begin(SDCARD_CS);

  tft.setRotation(1);

  MenuChanged = true;
  Reglage = MI_SAISON;

  if (SdCardPresent)
  {
    ReadSeuilsFromFile();
  }
  else
  {
    DisableSD();
  }

  //DisableRTC(); // a implémenter si pas de RTC trouvé
  ReadTime();

  GotoStartMenu();
  DisplayMenuScreen();
  delay(1000);     // à remplacer par fin de phase d'init
  GotoDisplayTemp();
  RotDetect = false;

  SetAlarmMinutes();

  Reglage = ETE;

for (idx = 1; idx < NB_TEMP ; idx ++)
  {
    Temperatures[idx] = ReadTemperature(PinNumber[idx]);
  }
      Temperatures[0] = Temperatures[1];  // Les Deux premieres températures sont la même, car on a 2 seuils pour l'exterieur
}

