void Menu(void)
{
 /* //actions sur le codeur rotatif
    if ((IndexMenu == 6) and (Switch == DROITE)) IndexMenu = 1;
    else if((IndexMenu == 1)and (Switch == PRESS) IndexMenu = 101;
    else if((IndexMenu == 2)and (Switch == PRESS) IndexMenu = 201;
    else if((IndexMenu == 3)and (Switch == PRESS) IndexMenu = 301;
    else if((IndexMenu == 4)and (Switch == PRESS) IndexMenu = 401;
    else if((IndexMenu == 5)and (Switch == PRESS)IndexMenu = 0;
    else if(IndexMenu == 111) 
    {
      IndexMenu = 1;
      Mode = NORMAL;
    }
    if(IndexMenu == 112) 
    {
      IndexMenu = 1;
      Mode = MAINTENANCE;
    }

    // affichage des menus
    // Menu de Base
  if ((IndexMenu > 0) && (IndexMenu < 100))
  {
    // Affichage du Menu de base
    tft.setTextColor(ILI9340_WHITE);
    tft.setCursor(120, 10);
    tft.setTextSize(3);
    tft.println("MENU");
    tft.setTextSize(2);

    if (IndexMenu == 1) {tft.setTextColor(ILI9340_RED);}
    else {tft.setTextColor(ILI9340_WHITE);}
    tft.setCursor(20, 10 + (tft.height() / 7) * 2);
    tft.println("MODE");

    if (IndexMenu == 2) {tft.setTextColor(ILI9340_RED);}
    else tft.setTextColor(ILI9340_WHITE);
    tft.setCursor(20, 10 + (tft.height() / 7) * 3);
    tft.println("SEUILS");

    if (IndexMenu == 3) {tft.setTextColor(ILI9340_RED);}
    else {tft.setTextColor(ILI9340_WHITE);}
    tft.setCursor(20, 10 + (tft.height() / 7) * 4);
    tft.println("HISTORIQUES");

    if (IndexMenu == 4)
    {
      if (Mode == MAINTENANCE) {tft.setTextColor(ILI9340_RED);}
      else {IndexMenu = 6;}
    }
    else
    {
      if (Mode == MAINTENANCE) {tft.setTextColor(ILI9340_WHITE);}
      else {tft.setTextColor(0x8408);}
    }
    tft.setCursor(20, 10 + (tft.height() / 7) *5);
    tft.println("TESTS TEMPERATURES");

    if (IndexMenu == 5) {tft.setTextColor(ILI9340_RED);}
    else {tft.setTextColor(ILI9340_WHITE);}
    tft.setCursor(20, 10 + (tft.height() / 7) * 6);
    tft.println("RETOUR");
  }

  // Menu Mode
  if ((IndexMenu > 100) && (IndexMenu < 200))
  {
        // Affichage du Menu de base
    tft.setTextColor(ILI9340_WHITE);
    tft.setCursor(120, 10);
    tft.setTextSize(3);
    tft.println("MODE");
    tft.setTextSize(2);
    
    if (IndexMenu == 1) {tft.setTextColor(ILI9340_RED);}
    else {tft.setTextColor(ILI9340_WHITE);}
    tft.setCursor(20, 10 + (tft.height() / 7) * 2);
    tft.println("NORMAL");

    if (IndexMenu == 2) {tft.setTextColor(ILI9340_RED);}
    else tft.setTextColor(ILI9340_WHITE);
    tft.setCursor(20, 10 + (tft.height() / 7) * 3);
    tft.println("MAINTENANCE");
  }*/
}

