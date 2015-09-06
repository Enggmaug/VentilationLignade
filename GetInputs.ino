
/*********************************************************************************/
/*                   RECCUPERATION DES INPUTS                                    */
/*********************************************************************************/
bool GetInputs() {
  bool InputsChanged;
  byte SerialRx[80];
  int rd;

  rd = Serial.available();
  if (rd > 0)
  {
    rd = Serial.readBytes((char *)SerialRx, rd);
    Serial.print(">>");
    Serial.print((char *)SerialRx);
    Serial.println("");

    if (Mode == MAINTENANCE)
    {
      if (strncmp((char *)SerialRx, "T_EXT_15 ON", 11) == 0)
      {
        NewInputs.InputTempOut15 = true;
        if (NewInputs.InputTempOut24)
          Serial.println("Temp. exterieure > 24Deg");
        else
          Serial.println("Temp. exterieure entre 15 et 24Deg");
      }
      else if (strncmp((char *)SerialRx, "T_EXT_15 OFF", 12) == 0)
      {
        NewInputs.InputTempOut15 = false;
        NewInputs.InputTempOut24 = false;
        Serial.println("Temp. exterieure < 15Deg");
      }
      else if (strncmp((char *)SerialRx, "T_EXT_24 ON", 11) == 0)
      {
        NewInputs.InputTempOut24 = true;
        NewInputs.InputTempOut15 = true;
        Serial.println("Temp. exterieure > 24Deg");
      }
      else if (strncmp((char *)SerialRx, "T_EXT_24 OFF", 12) == 0)
      {
        NewInputs.InputTempOut24 = false;
        if (NewInputs.InputTempOut15)
          Serial.println("Temp. exterieure entre 15 et 24Deg");
        else
          Serial.println("Temp. exterieure < 15Deg");

      }
      else if (strncmp((char *)SerialRx, "T_INT_22 ON", 11) == 0)
      {
        NewInputs.InputTempInt22 = true;
        Serial.println("Temp. interieure > 22Deg");
      }
      else if (strncmp((char *)SerialRx, "T_INT_22 OFF", 12) == 0)
      {
        NewInputs.InputTempInt22 = false;
        Serial.println("Temp. interieure < 22Deg");
      }
      else if (strncmp((char *)SerialRx, "T_CHEMINEE ON", 13) == 0)
      {
        NewInputs.InputTempCheminee = true;
        Serial.println("Feu Cheminee allume");
      }
      else if (strncmp((char *)SerialRx, "T_CHEMINEE OFF", 14) == 0)
      {
        NewInputs.InputTempCheminee = false;
        Serial.println("Feu Cheminee eteint");
      }
      else
      {
        Serial.println("Commande non reconnue");
        Serial.println("Utiliser : THERMOSTAT ETAT");
        Serial.println("    Avec : THERMOSTAT = T_EXT_15 / T_EXT_24 / T_INT_22 / T_CHEMINEE");
        Serial.println("           ETAT       = ON / OFF");
      }

    }

    if (strncmp((char *)SerialRx, "MAINT", 5) == 0)
    {
      Mode = MAINTENANCE;
      Serial.println("Entree Mode Maintenance");
      DisplayScreen();
    }
    else if (strncmp((char *)SerialRx, "NORM", 4) == 0)
    {
      Mode = NORMAL;
      Serial.println("Sortie Mode Maintenance");
      DisplayScreen();
    }
    else if (Mode == NORMAL)
    {
      Serial.println("Mode Normal : Pas de commande recue");
    }
  }

  if (Mode == NORMAL)
  {
    NewInputs.InputTempOut15 = TempOver(T_EXT_15);
    NewInputs.InputTempOut24 = TempOver(T_EXT_24);
    NewInputs.InputTempInt22 = TempOver(T_INT_22);
    NewInputs.InputTempCheminee = TempOver(T_CHEMINEE);
  }

  InputsChanged = (NewInputs.InputTempOut15 ^ OldInputs.InputTempOut15);
  InputsChanged = InputsChanged | (NewInputs.InputTempOut24 ^ OldInputs.InputTempOut24);
  InputsChanged = InputsChanged | (NewInputs.InputTempInt22 ^ OldInputs.InputTempInt22);
  InputsChanged = InputsChanged | (NewInputs.InputTempCheminee ^ OldInputs.InputTempCheminee);
  OldInputs = NewInputs;

  return InputsChanged;

}
