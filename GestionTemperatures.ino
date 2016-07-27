
/*---------------------------------------------------------------------------------------------*/
/*                     Reccuperation/Verification des Températures                             */
/*---------------------------------------------------------------------------------------------*/
void GetTemperatures(void)
{
  int idx;
  const int PinNumber[NB_TEMP] = {T_EXT, T_EXT, T_INT, T_CHEMINEE, T_PUIT};

  static unsigned int IndexMoyenne = TEMP_SAMPLES_NB;
  static float Releves[NB_TEMP-1][TEMP_SAMPLES_NB] = {0.0};

  for (idx = 0; idx < NB_TEMP-1 ; idx ++)
  {
    Releves[idx][IndexMoyenne] = ReadTemperature(PinNumber[idx+1]);
  }
  
  if (IndexMoyenne >= TEMP_SAMPLES_NB)
  {
     for (idx = 1; idx < NB_TEMP ; idx ++)
    {
      Temperatures[idx] = Moyenne( &Releves[idx][0], TEMP_SAMPLES_NB -1, TEMP_SAMPLES_NB);
      
    }
      Temperatures[0] = Temperatures[1];  // Les Deux premieres températures sont la même, car on a 2 seuils pour l'exterieur
  }
}

float ReadTemperature(int AnalogPinNumber)
{
  float value;
  if (AnalogPinNumber > 0)
  {
    int reading;
    reading = analogRead(AnalogPinNumber);

    value = ConvertThermistorValue(reading);
  }
  else
    value= 0.0;

   return (value);
}


void CheckTemperatures (void)
{
  int idx;
  for (idx = 0; idx < NB_TEMP; idx++)
  {
    if (TemperatureDepasseSeuil[idx] == true)
    {
      if (Temperatures[idx] < ( Seuils[Reglage][idx] - Hysteresis[Reglage][idx]))
      {
        TemperatureDepasseSeuil[idx] = false;
      }
    }
    else
    {
      if (Temperatures[idx] > ( Seuils[Reglage][idx] + Hysteresis[Reglage][idx]))
      {
        TemperatureDepasseSeuil[idx] = true;
      }
    }

    if (Temperatures[idx] < MinMax[MIN][idx])
    {
      MinMax[MIN][idx] = Temperatures[idx];
    }
    else if (Temperatures[idx] > MinMax[MAX][idx])
    {
      MinMax[MAX][idx] = Temperatures[idx];
    }
  }
}

/*---------------------------------------------------------------------------------------------*/
/*        Convertion d'une température de float vers int pour affichage dans thermomètre       */
/*---------------------------------------------------------------------------------------------*/
int ConvertTemperature(float InputTemp, float Min, float Max, int HauteurMax)
{
  float RegleDeTroyes;

  RegleDeTroyes = (((InputTemp - Min) / (Max - Min)) * (float) HauteurMax);

  return ((int) RegleDeTroyes);
}


float Moyenne (float *pt_tab, unsigned int EndIndex, unsigned int NbOfElements)
{
  unsigned int idx;
  double value = 0.0;
  unsigned int StartIndex;
  
  if (EndIndex >= (NbOfElements - 1)) // Ex. : EndIndex = 10 NbE = 7  => 10 9 8 7 6 5 4  => EndIndex - NbE = 3
    {
      StartIndex = EndIndex - (NbOfElements - 1); // => = 4
    }

  else // Ex. : EndIndex = 5 NbE = 7  => 5 4 3 2 1 0 379  => NbE - EndIndex = 2 
    {
      StartIndex = SCREEN_WIDTH - (NbOfElements - 1) + EndIndex; // => = 379
    }
    
  for (idx = 0; idx < NbOfElements; idx ++)
  {
    if ((StartIndex + idx) == SCREEN_WIDTH)
      StartIndex = 0; 
    value = value + (double)pt_tab[StartIndex + idx];
  }
  
  value = value / NbOfElements;
  return (float) value;
}

/*---------------------------------------------------------------------------------------------*/
/*        Convertion d'une lecture de thermistance vers une température                        */
/*---------------------------------------------------------------------------------------------*/
float ConvertThermistorValue(int input)
{
  int index = 64;
  int Dichotomie;

  for (Dichotomie = 64; Dichotomie > 0; Dichotomie >> 1)
  {
    if (input == ThermistorTable[index].Reading) return(ThermistorTable[index].Temperature);
    else if (input > ThermistorTable[index].Reading) index -= Dichotomie;
    else if (input < ThermistorTable[index].Reading) index += Dichotomie;
  }
  
  if (input > ThermistorTable[index].Reading) index = index-1;
    
  if (input > ThermistorTable[index].Reading) Serial.println(index);
  if (input < ThermistorTable[index+1].Reading) Serial.println(index);
}


