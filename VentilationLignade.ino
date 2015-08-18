#include "lignade.h"

/*----- Autorise/Inhibe les messages sur le serial port -----*/
#define DEBUG 0

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
  pinMode(BYPASS1_2, OUTPUT);
#if BYPASS2
  pinMode(BYPASS2_1, OUTPUT);
  pinMode(BYPASS2_2, OUTPUT);
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
}
/*-----------------------------------------------------------*/
/*----- Machine d'états                                 -----*/
/*-----------------------------------------------------------*/
void loop() {

  switch (MachineEtat) {
    case STATE_1 :
      if (TempOver(T_CHEMINEE))
      {
        MachineEtat = STATE_2;
        StateChanged = true;
      }
      else if (TempOver(T_EXT_15))
      {
        MachineEtat = STATE_3;
        StateChanged = true;
      }
      break;
    case STATE_2 :
      if (!TempOver(T_CHEMINEE))
      {
        MachineEtat = STATE_1;
        StateChanged = true;
      }
      else if (TempOver(T_EXT_15))
      {
        MachineEtat = STATE_4;
        StateChanged = true;
      }
      break;
    case STATE_3 :
      if (TempOver(T_EXT_24))
      {
        MachineEtat = STATE_T;
        StateChanged = true;
      }
      else if (TempOver(T_CHEMINEE))
      {
        MachineEtat = STATE_4;
        StateChanged = true;
      }
      else if (!TempOver(T_EXT_15))
      {
        MachineEtat = STATE_1;
        StateChanged = true;
      }
      break;
    case STATE_4 :
      if (TempOver(T_EXT_24))
      {
        MachineEtat = STATE_T;
        StateChanged = true;
      }
      else if (!TempOver(T_CHEMINEE))
      {
        MachineEtat = STATE_3;
        StateChanged = true;
      }
      else if (!TempOver(T_EXT_15))
      {
        MachineEtat = STATE_2;
        StateChanged = true;
      }
      break;
    case STATE_5 :
      if (TempOver(T_INT_22))
      {
        MachineEtat = STATE_6;
        StateChanged = true;
      }
      else if (!TempOver(T_EXT_24))
      {
        MachineEtat = STATE_T;
        StateChanged = true;
      }
      break;
    case STATE_6 :
      if (!TempOver(T_INT_22))
      {
        MachineEtat = STATE_5;
        StateChanged = true;
      }
      else if (!TempOver(T_EXT_24))
      {
        MachineEtat = STATE_T;
        StateChanged = true;
      }
      break;
    case STATE_T :
      if (TempOver(T_EXT_24))
      {
        if (TempOver(T_INT_22))
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
        if (TempOver(T_CHEMINEE))
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
      if (TempOver(T_EXT_15))
      {
        MachineEtat = STATE_T;
        StateChanged = true;
      }
      else
      {
        if (TempOver(T_CHEMINEE))
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
    //Selection Double Flux
    

        break;
      case STATE_2 :

        break;
      case STATE_3 :


        break;
      case STATE_4 :


        break;
      case STATE_T :

        break;
      case STATE_5 :
      
        break;
      case STATE_6 :

        break;

    default :
    StateChanged = false;
        break;
    }
  }
}
