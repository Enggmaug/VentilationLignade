
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
      if (strncmp((char *)SerialRx, "T_EXT_LOW ON", 11) == 0)
      {
        NewInputs.InputTempOutLow = true;
        if (NewInputs.InputTempOutHigh)
          Serial.println("Temp. exterieure Chaude");
        else
          Serial.println("Temp. exterieure Moyenne");
      }
      else if (strncmp((char *)SerialRx, "T_EXT_LOW OFF", 12) == 0)
      {
        NewInputs.InputTempOutLow = false;
        NewInputs.InputTempOutHigh = false;
        Serial.println("Temp. exterieure Froide");
      }
      else if (strncmp((char *)SerialRx, "T_EXT_HIGH ON", 11) == 0)
      {
        NewInputs.InputTempOutHigh = true;
        NewInputs.InputTempOutLow = true;
        Serial.println("Temp. exterieure Chaude");
      }
      else if (strncmp((char *)SerialRx, "T_EXT_HIGH OFF", 12) == 0)
      {
        NewInputs.InputTempOutHigh = false;
        if (NewInputs.InputTempOutLow)
          Serial.println("Temp. exterieure Moyenne");
        else
          Serial.println("Temp. exterieure Froide");

      }
      else if (strncmp((char *)SerialRx, "T_INT ON", 11) == 0)
      {
        NewInputs.InputTempInt = true;
        Serial.println("Temp. interieure Chaude");
      }
      else if (strncmp((char *)SerialRx, "T_INT OFF", 12) == 0)
      {
        NewInputs.InputTempInt = false;
        Serial.println("Temp. interieure Froide");
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
        Serial.println("    Avec : THERMOSTAT = T_EXT_LOW / T_EXT_HIGH / T_INT / T_CHEMINEE");
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
    NewInputs.InputTempOutLow = TempOver(T_EXT_LOW);
    NewInputs.InputTempOutHigh = TempOver(T_EXT_HIGH);
    NewInputs.InputTempInt = TempOver(T_INT);
    NewInputs.InputTempCheminee = TempOver(T_CHEMINEE);
  }

  InputsChanged = (NewInputs.InputTempOutLow ^ OldInputs.InputTempOutLow);
  InputsChanged = InputsChanged | (NewInputs.InputTempOutHigh ^ OldInputs.InputTempOutHigh);
  InputsChanged = InputsChanged | (NewInputs.InputTempInt ^ OldInputs.InputTempInt);
  InputsChanged = InputsChanged | (NewInputs.InputTempCheminee ^ OldInputs.InputTempCheminee);
  OldInputs = NewInputs;

  return InputsChanged;

}



bool GetTemp(int Thermostat)
{
 // Fonction à écrire : on retourne vrai si la température est au dessus du seuil défini pour cette temp.
return (false);

}

