#include "lignade.h"

/*----- Autorise/Inhibe les messages sur le serial port -----*/
#define DEBUG 1

#if DEBUG
#define DebugMessage(str) {Serial.println(str);}
#else
#define DebugMessage(str) {}
#endif

enum Modes {
  MAINTENANCE,
  NORMAL
} Mode;

typedef struct Inputs {
  bool InputTempOut15;
  bool InputTempOut24;
  bool InputTempInt22;
  bool InputTempCheminee;
} Inputs;

typedef struct Outputs {
  bool OutputVentiloCheminee;
  bool EntreeAirPuit;
  bool SortieAirDirect;
} Outputs;

struct Outputs OldOutputs;
struct Outputs NewOutputs;
struct Inputs OldInputs;
struct Inputs NewInputs;

bool FirstLoop;

void setup() {
  // si Debug autorisé, alors démarrage de la liaison serie
#if DEBUG
  Serial.begin(38400);
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

  NewInputs.InputTempOut15 = true;
  NewInputs.InputTempOut24 = true;
  NewInputs.InputTempInt22 = true;
  NewInputs.InputTempCheminee = true;
  OldInputs = NewInputs;

  FirstLoop = true;
  delay(2000);
}

void loop() {
  bool InputsChanged;
  InputsChanged = GetInputs();

  if ((FirstLoop == true) or (InputsChanged == true))
  {
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
      /* ETATS 1 et 5 */
      case 0x00 : // TExt Froide - TInt < 22°C - Cheminee Eteinte
      case 0x02 : // TExt Froide - TInt > 22°C - Cheminee Eteinte
      case 0x0C : // TExt Chaude - TInt < 22°C - Cheminee Eteinte
      case 0x0D : // TExt Chaude - TInt < 22°C - Cheminee Allumée
      case 0x04 : // TExt Error  - TInt < 22°C - Cheminee Eteinte
      case 0x06 : // TExt Error  - TInt > 22°C - Cheminee Eteinte
        Serial.println("ETATS 1");
        NewOutputs.OutputVentiloCheminee = false;
        NewOutputs.SortieAirDirect = false;
        NewOutputs.EntreeAirPuit = true;
        break;
      /*ETAT 2*/
      case 0x01 : // TExt Froide - TInt < 22°C - Cheminee Allumée
      case 0x03 : // TExt Froide - TInt > 22°C - Cheminee Allumée
      case 0x05 : // TExt Error  - TInt < 22°C - Cheminee Allumée
      case 0x07 : // TExt Error  - TInt > 22°C - Cheminee Allumée
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
      /*ETAT 6*/
      case 0x0E : // TExt Chaude - TInt > 22°C - Cheminee Eteinte
      case 0x0F : // TExt Chaude - TInt > 22°C - Cheminee Allumée
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
}


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
    else
    {
      NewInputs.InputTempOut15 = TempOver(T_EXT_15);
      NewInputs.InputTempOut24 = TempOver(T_EXT_24);
      NewInputs.InputTempInt22 = TempOver(T_INT_22);
      NewInputs.InputTempCheminee = TempOver(T_CHEMINEE);
    }
    if (strncmp((char *)SerialRx, "MAINT", 5) == 0)
    {
      Mode = MAINTENANCE;
      Serial.println("Entree Mode Maintenance");
    }
    else if (strncmp((char *)SerialRx, "NORM", 4) == 0)
    {
      Mode = NORMAL;
      Serial.println("Sortie Mode Maintenance");
    }
    else if (Mode == NORMAL)
    {
      Serial.println("Mode Normal : Pas de commande recue");
    }
  }

  InputsChanged = (NewInputs.InputTempOut15 ^ OldInputs.InputTempOut15);
  InputsChanged = InputsChanged | (NewInputs.InputTempOut24 ^ OldInputs.InputTempOut24);
  InputsChanged = InputsChanged | (NewInputs.InputTempInt22 ^ OldInputs.InputTempInt22);
  InputsChanged = InputsChanged | (NewInputs.InputTempCheminee ^ OldInputs.InputTempCheminee);
  OldInputs = NewInputs;

  return InputsChanged;

}

