
/*********************************************************************************/
/*                    Fonction d'Affichage sur Ecran                             */
/*********************************************************************************/
void DisplayScreen(void)
{
  if (!SdCardPresent) {
    DebugMessage("NO SD Found");
    DisplayNoSD();
  }
  else {
    DebugMessage("Display from SD");
    DisplaySD();
  }
}

void DisplaySD(void)
{
  int condition = 0;
  char CharArray[16];
  char* filename;
  condition = 0;
  if (NewInputs.InputTempOutHigh == true)condition += 8 ;
  if (NewInputs.InputTempOutLow == true)condition += 4 ;
  if (NewInputs.InputTempInt == true)condition += 2 ;
  if (NewInputs.InputTempCheminee == true )condition += 1 ;

  filename = CharArray;
  switch (condition)
  {
    case 0 :
      filename =  strcpy ( filename,  "ffoff");
      break;
    case 1:
      filename =   strcpy ( filename,  "ffon");
      break;
    case 2:
      filename =   strcpy ( filename,  "fcoff");
      break;
    case 3:
      filename =  strcpy ( filename,  "fcon");
      break;
    case 4:
      filename =  strcpy ( filename,  "mfoff");
      break;
    case 5:
      filename = strcpy ( filename,  "mfon");
      break;
    case 6:
      filename =  strcpy ( filename,  "mcoff");
      break;
    case 7:
      filename =  strcpy ( filename,  "mcon");
      break;
    case 8:
    case 12:
      filename =  strcpy ( filename,  "cfoff");
      break;
    case 9:
    case 13:
      filename =  strcpy ( filename,  "cfon");
      break;
    case 10:
    case 14:
      filename =   strcpy ( filename,  "ccoff");
      break;
    case 11:
    case 15:
      filename =  strcpy ( filename,  "ccon");
      break;
    default :
      filename =  strcpy ( filename,  "error");
  }

  filename = strcat(filename, ".bmp");

  if (bmpDraw(filename, 0, 0) == false)
  {
    DisplayNoSD();
    SdCardPresent = false;
  }
  else
  {
    //************* PARTIE OUTPUTS ********************

    //Texte Recyclage
    tft.setTextColor(ILI9340_BLACK);  tft.setTextSize(2);
    tft.setCursor(50, (tft.height() / 7) * 2);
    tft.println("VMC");
    tft.setCursor(130, (tft.height() / 7) * 2);
    if (NewOutputs.SortieAirDirect == false)
    {
      tft.println(": D. FLUX");
    }
    else
    {
      tft.println(": S. FLUX");
    }

    //Texte Puit Canadien
    tft.setCursor(50,  (tft.height() / 7) * 3);
    tft.println("Puit C.");
    tft.setCursor(130, (tft.height() / 7) * 3);
    if (NewOutputs.EntreeAirPuit == true)
    {
      tft.println(": MARCHE");
    }
    else
    {
      tft.println(": CAVE");
    }


    //Texte Cheminee
    tft.setCursor(50, (tft.height() / 7) * 4);
    tft.println("V Chem.");
    tft.setCursor(130, (tft.height() / 7) * 4);
    if (NewOutputs.OutputVentiloCheminee == true)
    {
      tft.println(": RECYCLE");
    }
    else
    {
      tft.println(": ARRET");
    }
    //************* PARTIE REGLAGES ********************

    //Texte Réglage
    tft.setCursor(50,  (tft.height() / 7) * 5);
    tft.println("Reglage");
    tft.setCursor(130,  (tft.height() / 7) * 5);
    tft.print(": ");
    tft.setTextColor(ILI9340_GREEN);
    tft.println("NORMAL");

    if (Mode == MAINTENANCE)
    {
      tft.setTextColor(ILI9340_RED); tft.setTextSize(3);
      tft.setCursor(20,  215);
      tft.println("MODE MAINTENANCE");
    }
  }

}

void DisplayNoSD(void)
{
  int color;
  tft.fillScreen(ILI9340_BLACK);

  //************* PARTIE INPUTS ********************

  //Rectangle Exterieur
  if (NewInputs.InputTempOutLow == false)
  {
    color = 0x001F;
  }
  else if (NewInputs.InputTempOutHigh == false)
  {
    color = 0x8408;
  }
  else
  {
    color = 0xF800;
  }
  tft.fillRect(0, 0, tft.width() / 3, (tft.height() / 7) * 2, color);

  // Rectangle Intérieur
  if (NewInputs.InputTempInt == false)
  {
    color = 0x001F;
  }
  else
  {
    color = 0xF800;
  }
  tft.fillRect(tft.width() / 3 + 1, 0, tft.width() / 3, (tft.height() / 7) * 2, color);

  // Rectangle Cheminée
  if (NewInputs.InputTempCheminee == false)
  {
    color = 0x001F;
  }
  else
  {
    color = 0xF800;
  }
  tft.fillRect(2 * tft.width() / 3 + 1, 0, tft.width() / 3, (tft.height() / 7) * 2, color);

  //Text Extérieur
  tft.setCursor(20, 10);
  tft.setTextColor(ILI9340_BLACK);  tft.setTextSize(2);
  tft.println("Ext :");
  tft.setCursor(20, 10 + (tft.height() / 7));
  if (NewInputs.InputTempOutLow == false)
  {
    tft.setTextSize(2);
    tft.print("F"); tft.setTextSize(1);
    tft.print(" - ");
    tft.print("M");
    tft.print(" - ");
    tft.print("C");
  }
  else if (NewInputs.InputTempOutHigh == false)
  {
    tft.setTextSize(1);
    tft.print("F");
    tft.print(" - "); tft.setTextSize(2);
    tft.print("M"); tft.setTextSize(1);
    tft.print(" - ");
    tft.print("C");
  }
  else
  {
    tft.setTextSize(1);
    tft.print("F");
    tft.print(" - ");
    tft.print("M");
    tft.print(" - "); tft.setTextSize(2);
    tft.print("C");
  }


  //Texte Intérieur
  tft.setCursor(tft.width() / 3 + 1 + 20, 10);
  tft.setTextColor(ILI9340_BLACK);  tft.setTextSize(2);
  tft.println("Int :");
  tft.setCursor(tft.width() / 3 + 1 + 20, 10 + (tft.height() / 7));
  if (NewInputs.InputTempInt == false)
  {
    tft.print("Froid");
  }
  else
  {
    tft.print("Chaud");
  }


  //Texte cheminée
  tft.setCursor(2 * tft.width() / 3 + 1 + 20, 10);
  tft.setTextColor(ILI9340_BLACK);  tft.setTextSize(2);
  tft.println("Chem :");
  tft.setCursor(2 * tft.width() / 3 + 1 + 20, 10 + (tft.height() / 7));
  if (NewInputs.InputTempCheminee == false)
  {
    tft.print("Froide");
  }
  else
  {
    tft.print("Chaude");
  }


  //************* PARTIE OUTPUTS ********************

  //Texte Recyclage
  tft.setTextColor(ILI9340_WHITE);  tft.setTextSize(2);
  tft.setCursor(20, 10 + (tft.height() / 7) * 2);
  tft.println("Recyclage");
  tft.setCursor(150, 10 + (tft.height() / 7) * 2);
  if (NewOutputs.SortieAirDirect == false)
  {
    tft.println(": DOUBLE FLUX");
  }
  else
  {
    tft.println(": SIMPLE FLUX");
  }

  //Texte Puit Canadien
  tft.setTextColor(ILI9340_WHITE);  tft.setTextSize(2);
  tft.setCursor(20, 10 + (tft.height() / 7) * 3);
  tft.println("Puit C.");
  tft.setCursor(150, 10 + (tft.height() / 7) * 3);
  if (NewOutputs.EntreeAirPuit == true)
  {
    tft.println(": FONCTIONNE");
  }
  else
  {
    tft.println(": CAVE");
  }


  //Texte Cheminee
  tft.setTextColor(ILI9340_WHITE);  tft.setTextSize(2);
  tft.setCursor(20, 10 + (tft.height() / 7) * 4);
  tft.println("Air Chem.");
  tft.setCursor(150, 10 + (tft.height() / 7) * 4);
  if (NewOutputs.OutputVentiloCheminee == true)
  {
    tft.println(": RECYCLE");
  }
  else
  {
    tft.println(": ARRET");
  }


  //************* PARTIE REGLAGES ********************

  //Texte Mode
  tft.setTextColor(ILI9340_WHITE);  tft.setTextSize(2);
  tft.setCursor(20, 10 + (tft.height() / 7) * 6);
  tft.println("Mode");
  tft.setCursor(150, 10 + (tft.height() / 7) * 6);
  tft.print(": ");
  if (Mode == MAINTENANCE)
  {
    tft.setTextColor(ILI9340_RED);
    tft.println("MAINT.");
  }
  else
  {
    tft.setTextColor(ILI9340_GREEN);
    tft.println("NORMAL");
  }

  //Texte Réglage
  tft.setTextColor(ILI9340_WHITE);  tft.setTextSize(2);
  tft.setCursor(20, 10 + (tft.height() / 7) * 5);
  tft.println("Reglage");
  tft.setCursor(150, 10 + (tft.height() / 7) * 5);
  tft.print(": ");
  tft.setTextColor(ILI9340_GREEN);
  tft.println("NORMAL");
}


// This function opens a Windows Bitmap (BMP) file and
// displays it at the given coordinates.  It's sped up
// by reading many pixels worth of data at a time
// (rather than pixel by pixel).  Increasing the buffer
// size takes more of the Arduino's precious RAM but
// makes loading a little faster.  20 pixels seems a
// good balance.

#define BUFFPIXEL 20

bool bmpDraw(char *filename, uint16_t x, uint16_t y) {

  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3 * BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();

  if ((x >= tft.width()) || (y >= tft.height())) return (false);

  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    DebugMessage("File not found");
    return (false);
  }

  // Parse BMP header
  if (read16(bmpFile) == 0x4D42) { // BMP signature
    read32(bmpFile);
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    // Read DIB header
    read32(bmpFile);
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if (read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      if ((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

        goodBmp = true; // Supported BMP format -- proceed!

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if (bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if ((x + w - 1) >= tft.width())  w = tft.width()  - x;
        if ((y + h - 1) >= tft.height()) h = tft.height() - y;

        // Set TFT address window to clipped image bounds
        tft.setAddrWindow(x, y, x + w - 1, y + h - 1);

        for (row = 0; row < h; row++) { // For each scanline...

          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if (flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if (bmpFile.position() != pos) { // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }

          for (col = 0; col < w; col++) { // For each pixel...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
            }

            // Convert pixel from BMP to TFT format, push to display
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            tft.pushColor(tft.Color565(r, g, b));
          } // end pixel
        } // end scanline
      } // end goodBmp
    }
  }

  bmpFile.close();
  if (!goodBmp) DebugMessage("BMP format not recognized.");
  return (goodBmp);
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File & f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File & f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}
/*********************************************************************************/
/*                    Affichage Message Attente                                  */
/*********************************************************************************/

void Display_Wait(void)
{
  char CharArray[16];
  char* filename;
  filename = "Wait.bmp";

  if (SdCardPresent == true)
  {
    if (bmpDraw(filename, 0, 0) == false)
    {
      SdCardPresent = false;
    }
  }
  if (SdCardPresent == false)
  {
    tft.fillScreen(ILI9340_WHITE); tft.setTextSize(2);
    tft.setTextColor(ILI9340_BLACK);
    tft.setCursor(60, tft.height() / 2 - 5);
    tft.println("PATIENTEZ SVP ...");
  }
}
