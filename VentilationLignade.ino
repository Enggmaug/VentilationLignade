#define VERSION "1.0.0"

#include "ILI9341_t3.h"
#include <SD.h>
#include "ds3234.h"
#include "Thermistor.h"
#include "Outputs.h"
#include "lignade.h"

// DEFINE
#define NB_CAR_LIGNE   24
#define NB_CAR_T       9
#define DEFAULT_SEUILS {15.0, 24.0, 22.0, 40.0}
#define DEFAULT_HYSTERESIS {0.0, 0.0, 0.0, 0.0}
#define NB_TEMP 5
#define EXTERIEUR_L 0
#define EXTERIEUR_H 1
#define INTERIEUR   2
#define CHEMINEE    4
#define PUIT_CANAD  3
#define NB_TYP_HISTO  4  // Jours / Semaines / Mois / Année
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define TEMP_SAMPLES_NB 10

//DEFINE des Numeros de Pins
#define BYPASS_1_F     0
#define BYPASS_1_O     1
#define BYPASS_2_F     2
#define BYPASS_2_O     3
#define VENT_CAVE      4
#define VENT_CHEM      5
#define V12_1_ON       6
#define SELECT_VMC     7
#define RTCLK_INT      8
#define RTCLK_CS       9
#define TFT_CS         10
#define SPI_MOSI       11
#define SPI_MISO       12
#define SPI_CLK        13
#define T_INT          14
#define SDCARD_CS      15
#define ENDSTOP_2_2    16
#define ENDSTOP_2_1    17
#define ENDSTOP_1_2    18
#define ENDSTOP_1_1    19
#define TFT_DC         20
#define T_EXT          21
#define T_PUIT         22
#define T_CHEMINEE     23
#define COD_SW         24
#define COD_CLK        25
#define RX_SPARE       26
#define SPARE          27
#define V12_2_ON       28
#define SCL1_SPARE     29
#define SDA1_SPARE     30
#define TX_SPARE       31
#define COD_DT         32
#define SELECT_12V     33
#define TFT_RST        -1

//Couleurs
//                       R     V      B
#define BLANC 0xFFFF //11111 111111 11111
#define NOIR  0x0000 //00000 000000 00000
#define GRIS  0x3186 //00110 001100 00110
#define ROUGE 0xF800 //11111 000000 00000
#define BLEU  0x001F //00000 000000 11111
#define VERT  0x07E0 //00000 111111 00000

//TEMPERATURES
#define MIN 0
#define MAX 1

//Definitions des Ecrans Menu
typedef void(*FctPtr)(void);
const int ct_NbItemMax          = 7;
const int ct_DisplayTNbItems    = 5;
const int ct_DispOutputsNbItems = 7;
const int ct_MenuMainNbItems    = 7;
const int ct_MenuModeNbItems    = 3;
const int ct_MenuDeclNbItems    = 4;
const int ct_MenuSeuilsNbItems  = 7;
const int ct_HysteresisNbItems  = 7;
const int ct_MenuHistNbItems    = 7;
const int ct_MenuCourbesNbItems = 6;
const int ct_MenuMinMaxNbItems  = 6;
const int ct_ResetNbItems       = 3;
const int ct_MaintenanceNbItems = 4;
const int ct_MenuDebugNbItems   = 7;
const int ct_MenuDHNbItems      = 6;
const int ct_MenuDatebItems     = 5;
const int ct_MenuHeureNbItems   = 4;
const int ct_SauvegarderNbItems = 3;


//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
//                   ITEMS sur Ecran :                               |TITRE,            |Item 1          |Item 2           |Item 3          |Item 4            |Item 6              |Item 7           |
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_DisplayT[ct_DisplayTNbItems][NB_CAR_LIGNE]       =  {"TEMPERATURES"    , "EXTERIEUR"    ,                   "INTERIEUR"    , "PUIT CAN."      , "CHEMINEE"         }; //             |
const FctPtr tab_DisplayTFonct[ct_DisplayTNbItems]                =  {GotoMainMenu      } ; //           |                 |                |                  |                    |                 |
/*-*/ bool   tab_DisplayTEnable[ct_DisplayTNbItems]               =  {true              , true           ,                   true           , true             , true               }; //             |
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_DispOutputs[ct_DispOutputsNbItems][NB_CAR_LIGNE] =  {"SORTIES"         , "VMC :    "    , "     "         , "INSUFLATION"  , "     "          , "CHEMINEE :"       , "     "         };
const FctPtr tab_DispOutputsFonct[ct_DispOutputsNbItems]          =  {GotoMainMenu      } ; //           |                 |                |                  |                    |                 |
/*-*/ bool   tab_DispOutputsEnable[ct_DispOutputsNbItems]         =  {true              , true           , true            , true           , true             , true               , true            };
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuMain[ct_MenuMainNbItems][NB_CAR_LIGNE]       =  {"MENU"            , "MODE"         , "REGLAGE SEUILS", "HISTORIQUE"   , "MAINTENANCE"    , "REGLER DATE/HEURE", "RETOUR"        };
const FctPtr tab_MenuMainFonct[ct_MenuMainNbItems]                =  {None              , SetMode        , GotoDeclenche   , GotoHisto      , GotoMaintenance  , GotoSetDateHeure   , GotoDisplayTemp };
/*-*/ bool   tab_MenuMainEnable[ct_MenuMainNbItems]               =  {true              , true           , true            , true           , true             , true               , true            };
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuMode[ct_MenuModeNbItems][NB_CAR_LIGNE]       =  {"ETE"             , "MI-SAISON"    , "HIVER"        }; //            |                  |                    |                 |
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuDeclenche[ct_MenuDeclNbItems][NB_CAR_LIGNE]  =  {"REGLAGES SEUILS" , "SEUILS"       , "SENSIBILITE"   , "RETOUR"       }; //              |                    |                 |
const FctPtr tab_MenuDeclencheFonct[ct_MenuDeclNbItems]           =  {None              , GotoSeuils     , GotoHysteresis  , GotoMainMenu   }; //              |                    |                 |
/*-*/ bool   tab_MenuDeclencheEnable[ct_MenuDeclNbItems]          =  {true              , true           , true            , true           }; //              |                    |                 |
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuSeuils[ct_MenuSeuilsNbItems][NB_CAR_LIGNE]   =  {"REGLAGE SEUILS"  , ""             , "T. EXT. HAUTE" , "T. INTERIEURE", "T. CHEMINEE"    , ""                 , "RETOUR"        };
const FctPtr tab_MenuSeuilsFonct[ct_MenuSeuilsNbItems]            =  {None              , None           , SetOnOff        , SetOnOff       , SetOnOff         , None               , SaveYesNo       };
/*-*/ bool   tab_MenuSeuilsEnable[ct_MenuSeuilsNbItems]           =  {true              , false          , true            , true           , true             , false              , true            };
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_Hysteresis[ct_HysteresisNbItems][NB_CAR_LIGNE]   =  {"SENSIBILITE"     , "T. EXT. BASSE", "T. EXT. HAUTE" , "T. INTERIEURE", "T. CHEMINEE"    , ""                 , "RETOUR"        };
const FctPtr tab_HysteresisFonct[ct_HysteresisNbItems]            =  {None              , SetOnOff       , SetOnOff        , SetOnOff       , SetOnOff         , None               , SaveYesNo       };
/*-*/ bool   tab_HysteresisEnable[ct_HysteresisNbItems]           =  {true              , true           , true            , true           , true             , false              , true            };
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuHist[ct_MenuHistNbItems][NB_CAR_LIGNE]       =  {"HISTORIQUE"      , "COURBES HISTO", "MIN/MAX"       , "RESET COURBES", "RESET MIN/MAX"  , "RESET TOUT"       , "RETOUR"        };
const FctPtr tab_MenuHistFonct[ct_MenuHistNbItems]                =  {None              , GotoCourbes    , GotoMinMax      , GotoResetScreen, GotoResetScreen  , GotoResetScreen    , GotoMainMenu    };
/*-*/ bool   tab_MenuHistEnable[ct_MenuHistNbItems]               =  {true              , true           , true            , true           , true             , true               , true            };
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuCourbes[ct_MenuHistNbItems][NB_CAR_LIGNE]    =  {"COURBES"         , "EXTERIEUR"    ,                   "INTERIEUR"    , "PUIT CAN."      , "CHEMINEE"         , "RETOUR"        };
const FctPtr tab_MenuCourbesFonct[ct_MenuCourbesNbItems]          =  {None              , ShowHistoExt   ,                   ShowHistoInt   , ShowHistoPuit    , ShowHistoChem      , GotoHisto       };
/*-*/ bool   tab_MenuCourbesEnable[ct_MenuCourbesNbItems]         =  {true              , true           ,                   true           , true             , true               , true            };
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuMinMax[ct_MenuHistNbItems][NB_CAR_LIGNE]     =  {"MIN/MAX"         , "EXTERIEUR"    ,                   "INTERIEUR"    , "PUIT CAN."      , "CHEMINEE"         , "RETOUR"        };
const FctPtr tab_MenuMinMaxFonct[ct_MenuMinMaxNbItems]            =  {None              , None           ,                   None           , None             , None               , GotoHisto       };
/*-*/ bool   tab_MenuMinMaxEnable[ct_MenuMinMaxNbItems]           =  {true              , true           ,                   true           , true             , true               , true            };
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_Reset[ct_ResetNbItems][NB_CAR_LIGNE]             =  {"RESET"           , "OUI"          , "ANNULER"       }; //            |                  |                    |                 |
const FctPtr tab_ResetFonct[ct_ResetNbItems]                      =  {None              , Reset          , GotoHisto       }; //            |                  |                    |                 |
/*-*/ bool   tab_ResetEnable[ct_ResetNbItems]                     =  {true              , true           , true            }; //            |                  |                    |                 |
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuMaint[ct_MaintenanceNbItems][NB_CAR_LIGNE]   =  {"MAINTENANCE"     , "NORMAL"       , "FORCER TEMPER.", "RETOUR"       }; //              |                    |                 |
const FctPtr tab_MenuMaintFonct[ct_MaintenanceNbItems]            =  {None              , DebugOnOff     , ShowChangeTemp  , GotoMainMenu   }; //              |                    |                 |
/*-*/ bool   tab_MenuMaintEnable[ct_MaintenanceNbItems]           =  {true              , true           , true            , true           }; //              |                    |                 |
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuDebug[ct_MenuDebugNbItems][NB_CAR_LIGNE]     =  {"DEBUG"           , ""             , "T. EXTERIEURE" , "T. INTERIEURE", "T. PUIT CAN"    , "T. CHEMINEE"      , "RETOUR"        };
const FctPtr tab_MenuDebugFonct[ct_MenuDebugNbItems]              =  {None              , None           , SetOnOff        , SetOnOff       , SetOnOff         , SetOnOff           , GotoMaintenance };
/*-*/ bool   tab_MenuDebugEnable[ct_MenuDebugNbItems]             =  {true              , false          , true            , true           , true             , true               , true            };
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuDateHeure[ct_MenuDHNbItems][NB_CAR_LIGNE]    =  {"DATE / HEURE"    , "REGLER DATE"  , "DATE ICI"      , "REGLER HEURE" , "HEURE ICI"      , "RETOUR"           }; //             |
const FctPtr tab_MenuDateHeureFonct[ct_MenuDHNbItems]             =  {None              , GotoSetDate    , None            , GotoSetHeure   , None             , GotoMainMenu       }; //             |
/*-*/ bool   tab_MenuDateHeureEnable[ct_MenuDHNbItems]            =  {true              , true           , false           , true           , false            , true               }; //             |
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuDate[ct_MenuDatebItems][NB_CAR_LIGNE]        =  {"REGLER DATE"     , "ANNEE"        , "MOIS"          , "JOUR"         , "RETOUR"         }; //                |                 |
const FctPtr tab_MenuDateFonct[ct_MenuDatebItems]                 =  {None              , SetDateOnOff   , SetDateOnOff    , SetDateOnOff   , SaveYesNo        }; //                |                 |
/*-*/ bool   tab_MenuDateEnable[ct_MenuDatebItems]                =  {true              , true           , true            , true           , true             }; //                |                 |
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_MenuHeure[ct_MenuHeureNbItems][NB_CAR_LIGNE]     =  {"REGLER HEURE"    , "HEURES"       , "MINUTES"       , "RETOUR"       }; //              |                    |                 |
const FctPtr tab_MenuHeureFonct[ct_MenuHeureNbItems]              =  {None              , SetHeuresOnOff , SetHeuresOnOff  , SaveYesNo      }; //              |                    |                 |
/*-*/ bool   tab_MenuHeureEnable[ct_MenuHeureNbItems]             =  {true              , true           , true            , true           }; //              |                    |                 |
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+
const char   tab_Sauvegarder[ct_SauvegarderNbItems][NB_CAR_LIGNE] =  {"SAUVEGARDER"     , "OUI"          , "NON"           }; //            |                  |                    |                 |
const FctPtr tab_SaveSeuilsFonct[ct_SauvegarderNbItems]           =  {None              , SaveSeuils2File, RecallSeuils    }; //            |                  |                    |                 |
const FctPtr tab_SaveHysteresisFonct[ct_SauvegarderNbItems]       =  {None              , SaveHyster2File, RecallHyster    }; //            |                  |                    |                 |
const FctPtr tab_SaveDateFonct[ct_SauvegarderNbItems]             =  {None              , SaveDate       , RecallDate      }; //            |                  |                    |                 |
const FctPtr tab_SaveHoursFonct[ct_SauvegarderNbItems]            =  {None              , SaveTime       , RecallTime      }; //            |                  |                    |                 |
/*-*/ bool   tab_SauvegarderSDEnable[ct_SauvegarderNbItems]       =  {true              , true           , true            }; //            |                  |                    |                 |
/*-*/ bool   tab_SauvegarderRTCEnable[ct_SauvegarderNbItems]      =  {true              , true           , true            }; //            |                  |                    |                 |
//-------------------------------------------------------------------+------------------+----------------+-----------------+----------------+------------------+--------------------+-----------------+

const char* BlankLine = "                       ";
char tab_MenuTemp[ct_NbItemMax][NB_CAR_LIGNE];

//Seuils et Température par défaut
float Seuils[NB_MODES][NB_TEMP-1]     = {DEFAULT_SEUILS, DEFAULT_SEUILS, DEFAULT_SEUILS};
float Hysteresis[NB_MODES][NB_TEMP-1] = {DEFAULT_HYSTERESIS, DEFAULT_HYSTERESIS, DEFAULT_HYSTERESIS};
float MinMax[2][NB_TEMP]            = {DEFAULT_SEUILS, DEFAULT_SEUILS};
float Temperatures[NB_TEMP];
bool TemperatureDepasseSeuil[NB_TEMP-1];
bool SeuilTriggered;


// Si carte SD présente
bool SdCardPresent;

// TFT Screen
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);

//Gestion de navigation - écrans menu
typedef enum
{
  MENU,
  TEMPERATURES,
  HISTO,
  DEBUG
} ScreenType;

typedef struct
{
  int NbItem;
  char *pt_tab_menu;
  bool *pt_tab_EnabledItems;
  FctPtr *pt_MenuFonct;
  int SelectedItem;
  char NbItems;
  void (*Droite)(void);
  void (*Gauche)(void);
  void (*Select)(void);
  ScreenType TypeEcran;
} ScreenDef;

ScreenDef EcranEnCours;
bool MenuChanged = true;

//Gestion de l'encodeur rotatif
bool RotDetect = false;
enum CodeurActions
{
  NONE,
  GAUCHE,
  DROITE,
  SELECT
} MenuAction;


// Definition des Réglages
enum Reglages {
  ETE = 0,
  MI_SAISON = 1,
  HIVER = 2
} Reglage;

//Definition de la date/heure courante
struct ts DateHeureCourante;
const struct ts BlankDateHeure = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

bool RTClockAlarm = true;
bool InhibRTCAlarms = false;

unsigned int IndexHistoriques[NB_TYP_HISTO] = {0};

float Historiques[NB_TEMP - 1][NB_TYP_HISTO][SCREEN_WIDTH] = {0.0};

extern const ThermistorEntry ThermistorTable[];

Bypass   ByPass_DoubleFlux = {BYPASS_1_O,BYPASS_1_F,ENDSTOP_1_1,ENDSTOP_1_2,false,false,false,false};
Bypass   ByPass_Cave       = {BYPASS_2_O,BYPASS_2_F,ENDSTOP_2_1,ENDSTOP_2_2,false,false,false,false};

bool DebugActivated = false;

  const int PinNumber[NB_TEMP] = {T_EXT, T_EXT, T_INT, T_CHEMINEE, T_PUIT};


