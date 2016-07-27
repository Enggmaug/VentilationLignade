/*---------------------------------------------------------------------------------------------*/
/*                               RESET DES HISTORIQUES SUR RAM                                 */
/*---------------------------------------------------------------------------------------------*/
void Reset(void)
{
  int idx,idy,idz;

  for (idx = 0;idx <NB_TYP_HISTO; idx ++)
    IndexHistoriques[idx] = 0;
  for (idx = 0;idx < (SCREEN_WIDTH); idx ++)
    {for (idy= 0;idy < (NB_TYP_HISTO); idy ++)
    {for (idz = 0;idz < (NB_TEMP - 1); idz ++)
    {Historiques[idz][idy][idx] = 0.0;}}}
}


/*---------------------------------------------------------------------------------------------*/
/*                                         No Action                                           */
/*---------------------------------------------------------------------------------------------*/
void None(void)
{
}

/*---------------------------------------------------------------------------------------------*/
/*                      Affectation des sorties à atteindre pour une date donnée               */
/*---------------------------------------------------------------------------------------------*/
unsigned int ManageOutputGoal(unsigned int counter)
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

  digitalWrite(VENT_CAVE ,OutputTable[Reglage][IndexOut].VentiloCave);
  digitalWrite(VENT_CHEM ,OutputTable[Reglage][IndexOut].VentiloCheminee);
  digitalWrite(SELECT_VMC,OutputTable[Reglage][IndexOut].DoubleFlux);
  //MoveBypass(ByPass_Cave,      OutputTable[Reglage][IndexOut].BypassCave);
  //MoveBypass(ByPass_DoubleFlux,OutputTable[Reglage][IndexOut].BypassVMC );
}


