
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

  IndexMoyenne = IndexMoyenne +1;
  
  if (IndexMoyenne >= TEMP_SAMPLES_NB)
  {
     for (idx = 1; idx < NB_TEMP ; idx ++)
    {
      Temperatures[idx] = Moyenne( &Releves[idx][0], TEMP_SAMPLES_NB -1, TEMP_SAMPLES_NB);
    }
      Temperatures[0] = Temperatures[1];  // Les Deux premieres températures sont la même, car on a 2 seuils pour l'exterieur
      IndexMoyenne = 0;
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
  SeuilTriggered = false;

//Le seuil de température extérieure basse n'est pas réglable : c'est la température du puit Canadien
  Seuils[Reglage][EXTERIEUR_L] = Temperatures[PUIT_CANAD];
    
  for (idx = 0; idx < NB_TEMP-1; idx++)
  {    
    if (TemperatureDepasseSeuil[idx] == true)
    {
      if (Temperatures[idx] < ( Seuils[Reglage][idx] - Hysteresis[Reglage][idx]))
      {
        TemperatureDepasseSeuil[idx] = false;
        SeuilTriggered = true;
      }
    }
    else
    {
      if (Temperatures[idx] > ( Seuils[Reglage][idx] + Hysteresis[Reglage][idx]))
      {
        TemperatureDepasseSeuil[idx] = true;
        SeuilTriggered = true;
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
float ConvertThermistorValue(unsigned int input)
{
    signed int direction;
    signed int Ecart_X;
    float      Ecart_Y;
    signed int EcartInput;
    unsigned int index;
    unsigned int Dichotomie;

    float Result;

//Robustesse
    if (input > ThermistorTable[0].Reading)
        return -666.00;
    if (input < ThermistorTable[sizeof(ThermistorTable)/sizeof(ThermistorEntry)-1].Reading)
        return 666.00;

//On se rapproche par Dichotomie
    index = 64;
    for (Dichotomie = 32; Dichotomie > 0 ; Dichotomie=Dichotomie >> 1)
    {
        if (input == ThermistorTable[index].Reading)
        {
            break;
        }
        else if (input > ThermistorTable[index].Reading)
        {
            index = index - (Dichotomie);
        }
        else if (input < ThermistorTable[index].Reading)
        {
            index = index + (Dichotomie);
        }
    }

//On est à côté de l'indice voullu, mais il faut savoir su quel Range calculer
    if (input == ThermistorTable[index].Reading)
        direction=index;
    else if (input < ThermistorTable[index].Reading)
    {
        direction = index + 1;
    }
    else
    {
        direction = index - 1;
    }

//Interpolation linéaire
    Ecart_X = ThermistorTable[direction].Reading - ThermistorTable[index].Reading;
    Ecart_Y = ThermistorTable[direction].Temperature - ThermistorTable[index].Temperature;

    EcartInput= input - ThermistorTable[index].Reading;

    if (Ecart_X == 0)
        Result= ThermistorTable[index].Temperature;
    else
    {
        Result = ThermistorTable[index].Temperature + ((float)(EcartInput)/(float)(Ecart_X))*Ecart_Y;
    }
    return (Result);
}
