#include "lignade.h"

/*----- Autorise/Inhibe les messages sur le serial port -----*/
#define DEBUG 1

#if DEBUG
#define DebugMessage(str) {Serial.println(str);}
#else
#define DebugMessage(str) {}
#endif

/*-----------------------------------------------------------*/
/*----- Definition Machine d'Etats                      -----*/
/*-----------------------------------------------------------*/
enum StateMachine {
  STATE_1,
  STATE_2,
  STATE_3,
  STATE_4,
  STATE_T,
  STATE_5,
  STATE_6
} MachineEtat;

bool StateChanged = true;

enum Modes {
  MAINTENANCE,
  NORMAL
} Mode;

bool Text15 = THERM_OFF, Text24 = THERM_OFF, Tin22 = THERM_OFF, TChem = THERM_OFF;
/*-----------------------------------------------------------*/
/*----- Fonction d'initialisation                       -----*/
/*-----------------------------------------------------------*/
void setup() {
  // si Debug autorisé, alors démarrage de la liaison serie
#if DEBUG
  Serial.begin(38400);
#endif

  // Pins EndStops
#if ENDSTOPS
  pinMode(ENDSTOP1_1, INPUT);
  pinMode(ENDSTOP1_2, INPUT);
#if BYPASS2
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
  pinMode(BYPASS1_1, OUTPUT);
  digitalWrite(BYPASS1_1, BYPASS_DESACT);
  pinMode(BYPASS1_2, OUTPUT);
  digitalWrite(BYPASS1_2, BYPASS_DESACT);
#if BYPASS2
  pinMode(BYPASS2_1, OUTPUT);
   digitalWrite(BYPASS2_1, BYPASS_DESACT);
  pinMode(BYPASS2_2, OUTPUT);
   digitalWrite(BYPASS2_2, BYPASS_DESACT);
#endif

  //Pins Ventilos
  pinMode(VENT_CHEMINEE, OUTPUT);
  pinMode(VENT_CAVE, OUTPUT);
  pinMode(VENT_4, OUTPUT);

  //Pin VMC
  pinMode(SELECT_VMC, OUTPUT);

  //Pins Monitoring 12V
  pinMode(V12_1, OUTPUT);
#if MONITORING_12V
  pinMode(V12_ON, OUTPUT);
  pinMode(V12_2, OUTPUT);
  pinMode(V12_IN, INPUT);
#endif


  Mode = NORMAL;

  if (TempOver(T_EXT_15))
  {
    MachineEtat = STATE_T;
  }
  else
  {
    if (TempOver(T_CHEMINEE))
    {
      MachineEtat = STATE_1;
    }
    else
    {
      MachineEtat = STATE_2;
    }
  }
  DebugMessage("Etat à l'initialisation : ");
  DebugMessage(MachineEtat);
}
/*-----------------------------------------------------------*/
/*----- Machine d'états                                 -----*/
/*-----------------------------------------------------------*/
void loop() {
  byte SerialRx[80];
  int rd;
  rd = Serial.available();
  if (rd > 0)
  {
    rd = Serial.readBytes((char *)SerialRx, rd);
    if (Mode == MAINTENANCE)
    {
      if (strcmp((char *)SerialRx, "T_EXT_15 ON") == 0)
      {
        Text15 = true;
        if (Text24)
          Serial.println("Temp. exterieure > 24Deg");
        else
          Serial.println("Temp. exterieure entre 15 et 24Deg");
      }
      else if (strcmp((char *)SerialRx, "T_EXT_15 OFF") == 0)
      {
        Text15 = false;
        Text24 = false;
        Serial.println("Temp. exterieure < 15Deg");
      }
      else if (strcmp((char *)SerialRx, "T_EXT_24 ON") == 0)
      {
        Text24 = true;
        Text15 = true;
        Serial.println("Temp. exterieure > 24Deg");
      }
      else if (strcmp((char *)SerialRx, "T_EXT_24 OFF") == 0)
      {
        Text24 = false;
        if (Text15)
          Serial.println("Temp. exterieure entre 15 et 24Deg");
        else
          Serial.println("Temp. exterieure < 15Deg");

      }
      else if (strcmp((char *)SerialRx, "T_INT_22 ON") == 0)
      {
        Tin22 = true;
        Serial.println("Temp. interieure > 22Deg");
      }
      else if (strcmp((char *)SerialRx, "T_INT_22 OFF") == 0)
      {
        Tin22 = false;
        Serial.println("Temp. interieure < 22Deg");
      }
      else if (strcmp((char *)SerialRx, "T_CHEMINEE ON") == 0)
      {
        TChem = true;
        Serial.println("Feu Cheminee allumee");
      }
      else if (strcmp((char *)SerialRx, "T_CHEMINEE OFF") == 0)
      {
        TChem = false;
        Serial.println("Feu Cheminee eteint");
      }
      else
      {
        Serial.println("Commande non reconnue");
        Serial.println("Utiliser : THERMOSTAT ETAT");
        Serial.println("    Avec : THERMOSTAT = T_EXT_15 / T_EXT_24 / T_INT_22 / T_CHEMINEE");
        Serial.println("           ETAT       = ON / OFF");
        Serial.println("");
        Serial.println("Etat courant : ");
        switch (MachineEtat)
        {
          case STATE_1 :
            Serial.println("               Etat 1");
            break;
          case STATE_2 :
            Serial.println("               Etat 2");
            break;
          case STATE_3 :
            Serial.println("               Etat 3");
            break;
          case STATE_4 :
            Serial.println("               Etat 4");
            break;
          case STATE_T :
            Serial.println("               Etat Transition");
            break;
          case STATE_5 :
            Serial.println("               Etat 5");
            break;
          case STATE_6 :
            Serial.println("               Etat 6");
            break;
          default : Serial.println("Erreur - Etat inconnu");
            break;
        }
      }

    }
    if (strcmp((char *)SerialRx, "MAINT") == 0)
    {
      Mode = MAINTENANCE;
      Serial.println("Entree Mode Maintenance");
    }
    else if (strcmp((char *)SerialRx, "NORM") == 0)
    {
      Mode = NORMAL;
      Serial.println("Sortie Mode Maintenance");
    }
    else if (Mode == NORMAL)
    {
      Serial.println("Mode Normal : Pas de commande recue");
    }
  }

  if (Mode == NORMAL)
  {
    Text15 = TempOver(T_EXT_15);
    Text24 = TempOver(T_EXT_24);
    Tin22 = TempOver(T_INT_22);
    TChem = TempOver(T_CHEMINEE);
  }

  switch (MachineEtat) {
    case STATE_1 :
      if (TChem)
      {
        MachineEtat = STATE_2;
        StateChanged = true;
      }
      else if (Text15)
      {
        MachineEtat = STATE_3;
        StateChanged = true;
      }
      break;
    case STATE_2 :
      if (!TChem)
      {
        MachineEtat = STATE_1;
        StateChanged = true;
      }
      else if (Text15)
      {
        MachineEtat = STATE_4;
        StateChanged = true;
      }
      break;
    case STATE_3 :
      if (Text24)
      {
        MachineEtat = STATE_T;
        StateChanged = true;
      }
      else if (TChem)
      {
        MachineEtat = STATE_4;
        StateChanged = true;
      }
      else if (!Text15)
      {
        MachineEtat = STATE_1;
        StateChanged = true;
      }
      break;
    case STATE_4 :
      if (Text24)
      {
        MachineEtat = STATE_T;
        StateChanged = true;
      }
      else if (!TChem)
      {
        MachineEtat = STATE_3;
        StateChanged = true;
      }
      else if (!Text15)
      {
        MachineEtat = STATE_2;
        StateChanged = true;
      }
      break;
    case STATE_5 :
      if (Tin22)
      {
        MachineEtat = STATE_6;
        StateChanged = true;
      }
      else if (!Text24)
      {
        MachineEtat = STATE_T;
        StateChanged = true;
      }
      break;
    case STATE_6 :
      if (!Tin22)
      {
        MachineEtat = STATE_5;
        StateChanged = true;
      }
      else if (!Text24)
      {
        MachineEtat = STATE_T;
        StateChanged = true;
      }
      break;
    case STATE_T :
      if (Text24)
      {
        if (Tin22)
        {
          MachineEtat = STATE_6;
          StateChanged = true;
        }
        else
        {
          MachineEtat = STATE_5;
          StateChanged = true;
        }
      }
      else
      {
        if (TChem)
        {
          MachineEtat = STATE_4;
          StateChanged = true;
        }
        else
        {
          MachineEtat = STATE_3;
          StateChanged = true;
        }
      }
      break;
    default :
      if (Text15)
      {
        MachineEtat = STATE_T;
        StateChanged = true;
      }
      else
      {
        if (TChem)
        {
          MachineEtat = STATE_1;
          StateChanged = true;
        }
        else
        {
          MachineEtat = STATE_2;
          StateChanged = true;
        }
      }
      break;
  }

  if (StateChanged == true)
  {
    StateChanged = false;
    // Arret des Ventilos
    VentiloArret(VENT_CHEMINEE);
    VentiloArret(VENT_CAVE);
    VentiloArret(VENT_4);

    switch (MachineEtat) {
      case STATE_1 :
        DebugMessage("Etat 1");
        Bypass1Ouvrir();

        break;
      case STATE_2 :
        DebugMessage("Etat 2");
        Bypass1Fermer();
        break;
      case STATE_3 :
        DebugMessage("Etat 3");


        break;
      case STATE_4 :
        DebugMessage("Etat 4");


        break;
      case STATE_T :
        DebugMessage("Etat Transition");

        break;
      case STATE_5 :
        DebugMessage("Etat 5");

        break;
      case STATE_6 :
        DebugMessage("Etat 6");

        break;

      default :
        MachineEtat = STATE_1;
        StateChanged = true;
        break;
    }
  }
}
