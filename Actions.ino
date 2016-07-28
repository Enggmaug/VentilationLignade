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
void DebugOnOff(void)
{
   DebugActivated = not(DebugActivated);
   if (DebugActivated == false)
   {
		GetTemperatures();
   }
   MenuChanged = true;
}


/*---------------------------------------------------------------------------------------------*/
/*                                         No Action                                           */
/*---------------------------------------------------------------------------------------------*/
void None(void)
{
}

