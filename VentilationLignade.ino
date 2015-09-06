#include "lignade.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9340.h"
#include <SD.h>

/*----- Autorise/Inhibe les messages sur le serial port -----*/
#define DEBUG 1

#if DEBUG
#define DebugMessage(str) {Serial.println(str);}
#else
#define DebugMessage(str) {}
#endif

/*----- Ajout pour affichage ILI9340                    -----*/
#define _sclk SPI_SCK
#define _miso SPI_MISO
#define _mosi SPI_MOSI
// Use hardware SPI
Adafruit_ILI9340 tft = Adafruit_ILI9340(TFT_CS, TFT_DC, TFT_RST);

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
bool SdCardPresent;

//Fonction Setup est appelée automatiquement

//Fonction Loop est appelée automatiquement en boucle infinie

