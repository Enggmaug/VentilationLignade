/*---------------------------------------------------------------------------------------------*/
/*                      Affectation des sorties à atteindre                                    */
/*---------------------------------------------------------------------------------------------*/
void ManageOutputGoal(void)
{
  int IndexOut = 0;

#define EXTERIEUR_L 0
#define EXTERIEUR_H 1
#define INTERIEUR   2
#define CHEMINEE    4
#define PUIT_CANAD  3
  if (TemperatureDepasseSeuil[EXTERIEUR_H])
  {
    IndexOut = 2;
  }
  else if (TemperatureDepasseSeuil[EXTERIEUR_L])
  {
    IndexOut = 1;
  }

  IndexOut = IndexOut << 1;
  if (TemperatureDepasseSeuil[INTERIEUR])
  {
    IndexOut += 1;
  }
  
  IndexOut = IndexOut << 1;
    if (TemperatureDepasseSeuil[CHEMINEE])
  {
    IndexOut += 1;
  }
  
  g_OutputGoal = OutputTable[Reglage][IndexOut];
  
  digitalWrite(VENT_CAVE ,OutputTable[Reglage][IndexOut].VentiloCave);
  digitalWrite(VENT_CHEM ,OutputTable[Reglage][IndexOut].VentiloCheminee);
  digitalWrite(SELECT_VMC,OutputTable[Reglage][IndexOut].DoubleFlux);
  MoveBypass(&ByPass_Cave,      OutputTable[Reglage][IndexOut].BypassCave);
  MoveBypass(&ByPass_DoubleFlux,OutputTable[Reglage][IndexOut].BypassVMC );

}


void MoveBypass(Bypass *BypassRef,bool goal)
{
  BypassRef->isOpen   = digitalRead(BypassRef->SwitchOpen);
  BypassRef->isClosed = digitalRead(BypassRef->SwitchClosed);
  if (goal == OPEN && BypassRef->isOpen ==false)
  {
    AlimOn();
    digitalWrite(BypassRef->PinOpen,true);
    digitalWrite(BypassRef->PinClose,false);
    BypassRef->isOpening = true;
    BypassRef->isClosing = false;
    BypassRef->TimeoutCounter = 0;
    delay(500); // Pour ne pas avoir les pics de courant des 2 Bypass en même temps
  }
  else if (goal == CLOSE && BypassRef->isClosed ==false)
  {
    AlimOn();
    digitalWrite(BypassRef->PinOpen,false);
    digitalWrite(BypassRef->PinClose,true);
    BypassRef->isClosing = true;
    BypassRef->isOpening = false;
    BypassRef->TimeoutCounter = 0;
    delay(500); // Pour ne pas avoir les pics de courant des 2 Bypass en même temps
  }
  else
  {
    digitalWrite(BypassRef->PinOpen,false);
    digitalWrite(BypassRef->PinClose,false);
    AlimOff();
  }
}


void AlimOn(void){
  // A améliorer avec Gestion de 2 alims
  digitalWrite(V12_1_ON,true);
}
void AlimOff(void){
  // A améliorer avec Gestion de 2 alims
  if((ByPass_DoubleFlux.isClosing == false) && (ByPass_Cave.isClosing == false) && (ByPass_DoubleFlux.isOpening == false) && (ByPass_Cave.isOpening == false))
  {
    digitalWrite(V12_1_ON,false);  
  }
}

void CheckMovement(Bypass* BP)
{
  BP->TimeoutCounter ++;

  if (BP->TimeoutCounter >= TIMEOUT_BYPASS)
  {
    BP->isClosing = false;
    BP->isOpening = false;
    digitalWrite(BP->PinOpen,false);
    digitalWrite(BP->PinClose,false);
    AlimOff();
  }
  
  if (BP->isClosing)
  {
    if(digitalRead(BP->SwitchClosed))
    {
      BP->isClosing = false;
      BP->isClosed = true;
      digitalWrite(BP->PinOpen,false);
      digitalWrite(BP->PinClose,false);
      AlimOff();
    }
  }
  else if (BP->isOpening)
  {
    if(digitalRead(BP->SwitchOpen))
    {
      BP->isOpening = false;
      BP->isOpen = true;
      digitalWrite(BP->PinOpen,false);
      digitalWrite(BP->PinClose,false);      
      AlimOff();
    }
  }
}

