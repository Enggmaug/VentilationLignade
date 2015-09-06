
void loop() {
  bool InputsChanged;
  bool RefreshScreen = false;
  InputsChanged = GetInputs();

  if ((FirstLoop == true) or (InputsChanged == true))
  {
    RefreshScreen = true;

    char InputsCalc;
    //Construction de la valeur de switch
    InputsCalc = 0;
    InputsCalc = (char) NewInputs.InputTempOut15;
    InputsCalc = InputsCalc << 1;
    InputsCalc = InputsCalc + (char) NewInputs.InputTempOut24;
    InputsCalc = InputsCalc << 1;
    InputsCalc = InputsCalc + (char) NewInputs.InputTempInt22;
    InputsCalc = InputsCalc << 1;
    InputsCalc = InputsCalc + (char) NewInputs.InputTempCheminee;

    //Gestion des états
    switch (InputsCalc) {
      /* ETAT 1*/
      case 0x00 : // TExt Froide - TInt < 22°C - Cheminee Eteinte
      case 0x02 : // TExt Froide - TInt > 22°C - Cheminee Eteinte
      case 0x0C : // TExt Chaude - TInt < 22°C - Cheminee Eteinte
      case 0x0D : // TExt Chaude - TInt < 22°C - Cheminee Allumée
      case 0x04 : // TExt Error  - TInt < 22°C - Cheminee Eteinte
        Serial.println("ETAT 1");
        NewOutputs.OutputVentiloCheminee = false;
        NewOutputs.SortieAirDirect = false;
        NewOutputs.EntreeAirPuit = true;
        break;
      /*ETAT 2*/
      case 0x01 : // TExt Froide - TInt < 22°C - Cheminee Allumée
      case 0x03 : // TExt Froide - TInt > 22°C - Cheminee Allumée
      case 0x05 : // TExt Error  - TInt < 22°C - Cheminee Allumée
        Serial.println("ETAT 2");
        NewOutputs.OutputVentiloCheminee = true;
        NewOutputs.SortieAirDirect = false;
        NewOutputs.EntreeAirPuit = true;
        break;
      /*ETAT 3*/
      case 0x08 : // TExt Douce  - TInt < 22°C - Cheminee Eteinte
      case 0x0A : // TExt Douce  - TInt > 22°C - Cheminee Eteinte
        Serial.println("ETAT 3");
        NewOutputs.OutputVentiloCheminee = false;
        NewOutputs.SortieAirDirect = false;
        NewOutputs.EntreeAirPuit = false;
        break;
      /*ETAT 4*/
      case 0x09 : // TExt Douce  - TInt < 22°C - Cheminee Allumée
      case 0x0B : // TExt Douce  - TInt > 22°C - Cheminee Allumée
        Serial.println("ETAT 4");
        NewOutputs.OutputVentiloCheminee = true;
        NewOutputs.SortieAirDirect = false;
        NewOutputs.EntreeAirPuit = false;
        break;
      /*ETAT 5*/
      case 0x0E : // TExt Chaude - TInt > 22°C - Cheminee Eteinte
      case 0x0F : // TExt Chaude - TInt > 22°C - Cheminee Allumée
      case 0x06 : // TExt Error  - TInt > 22°C - Cheminee Eteinte
      case 0x07 : // TExt Error  - TInt > 22°C - Cheminee Allumée
        Serial.println("ETAT 5");
        NewOutputs.OutputVentiloCheminee = false;
        NewOutputs.SortieAirDirect = true;
        NewOutputs.EntreeAirPuit = true;
        break;
      default :
        break;
    }

    //Gestion des sorties
    if (FirstLoop == true) //Premier Passage : Toutes sorties réinitialisées.
    {
      Serial.println("FirstLoop ! ");
      OldOutputs.OutputVentiloCheminee = ! NewOutputs.OutputVentiloCheminee;
      OldOutputs.SortieAirDirect = ! NewOutputs.SortieAirDirect;
      OldOutputs.EntreeAirPuit = ! NewOutputs.EntreeAirPuit;
    }
    FirstLoop = false;
    //Cheminée
    if (NewOutputs.OutputVentiloCheminee != OldOutputs.OutputVentiloCheminee)
    {
      if (NewOutputs.OutputVentiloCheminee == false)
      {
        VentiloArret(VENT_CHEMINEE);
      }
      else
      {
        VentiloMarche(VENT_CHEMINEE);
      }
    }
    //Bypass1
    if (NewOutputs.SortieAirDirect != OldOutputs.SortieAirDirect)
    {
      if (NewOutputs.SortieAirDirect == false)
      {
        BYPASS_1Fermer();
      }
      else
      {
        BYPASS_1Ouvrir();
      }
    }
    //Bypass2
    if (NewOutputs.EntreeAirPuit != OldOutputs.EntreeAirPuit)
    {
      if (NewOutputs.EntreeAirPuit == false)
      {
        VentiloMarche(VENT_CAVE);
        BYPASS_2Fermer();
      }
      else
      {
        BYPASS_2Ouvrir();
        VentiloArret(VENT_CAVE);
      }
    }
    OldOutputs = NewOutputs;
  }

  // Affichage de l'écran
  if (RefreshScreen == true)
  {
    DisplayScreen();
    RefreshScreen = false;
  }
}
