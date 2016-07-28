#define CLOSE false
#define OPEN not(CLOSE)
#define TURN_OFF false
#define TURN_ON not(TURN_OFF)
#define DOUBLE_FLUX TURN_ON
#define SIMPLE_FLUX not(DOUBLE_FLUX)

#define TIMEOUT_BYPASS 30

#define NB_MODES    3

typedef struct
{
  int PinOpen;
  int PinClose;
  int SwitchOpen;
  int SwitchClosed;
  bool isOpen;
  bool isOpening;
  bool isClosed;
  bool isClosing;
  unsigned int TimeoutCounter;
} Bypass;

typedef struct OutputGoal
{
    bool VentiloCave;
    bool VentiloCheminee;
    bool DoubleFlux;
    bool BypassCave;
    bool BypassVMC;
} OutputGoal;

OutputGoal g_OutputGoal = {TURN_OFF, TURN_OFF, DOUBLE_FLUX, CLOSE, CLOSE};

const OutputGoal OutputTable[NB_MODES][12] = {
/*MODE ETE */
/*Air Ext.| Air Int | Cheminée*/  /*VentiloCave | VentiloCheminee | DoubleFlux | BypassCave | BypassVMC */
/*Froid   | Froid   | Arrêt   */ {{TURN_OFF     , TURN_OFF        , DOUBLE_FLUX, CLOSE      , OPEN      },
/*Froid   | Froid   | Marche  */  {TURN_OFF     , TURN_ON         , DOUBLE_FLUX, CLOSE      , OPEN      },
/*Froid   | Chaud   | Arrêt   */  {TURN_ON      , TURN_OFF        , DOUBLE_FLUX, OPEN       , OPEN      },
/*Froid   | Chaud   | Marche  */  {TURN_OFF     , TURN_ON         , DOUBLE_FLUX, CLOSE      , OPEN      },
/*Moyen   | Froid   | Arrêt   */  {TURN_OFF     , TURN_OFF        , DOUBLE_FLUX, CLOSE      , OPEN      },
/*Moyen   | Froid   | Marche  */  {TURN_ON      , TURN_ON         , DOUBLE_FLUX, OPEN       , OPEN      },
/*Moyen   | Chaud   | Arrêt   */  {TURN_OFF     , TURN_OFF        , SIMPLE_FLUX, CLOSE      , CLOSE     },
/*Moyen   | Chaud   | Marche  */  {TURN_ON      , TURN_ON         , SIMPLE_FLUX, OPEN       , CLOSE     },
/*Chaud   | Froid   | Arrêt   */  {TURN_OFF     , TURN_OFF        , DOUBLE_FLUX, CLOSE      , OPEN      },
/*Chaud   | Froid   | Marche  */  {TURN_OFF     , TURN_OFF        , DOUBLE_FLUX, CLOSE      , OPEN      },
/*Chaud   | Chaud   | Arrêt   */  {TURN_OFF     , TURN_OFF        , SIMPLE_FLUX, CLOSE      , CLOSE     },
/*Chaud   | Chaud   | Marche  */  {TURN_OFF     , TURN_OFF        , SIMPLE_FLUX, CLOSE      , CLOSE     }},

/*MODE MI-SAISON */
/*Air Ext.| Air Int | Cheminée*/  /*VentiloCave | VentiloCheminee | DoubleFlux | BypassCave | BypassVMC */
/*Froid   | Froid   | Arrêt   */ {{TURN_OFF     , TURN_OFF        , DOUBLE_FLUX, CLOSE      , OPEN      },
/*Froid   | Froid   | Marche  */  {TURN_OFF     , TURN_ON         , DOUBLE_FLUX, CLOSE      , OPEN      },
/*Froid   | Chaud   | Arrêt   */  {TURN_OFF     , TURN_OFF        , DOUBLE_FLUX, CLOSE      , OPEN      },
/*Froid   | Chaud   | Marche  */  {TURN_OFF     , TURN_ON         , DOUBLE_FLUX, CLOSE      , OPEN      },
/*Moyen   | Froid   | Arrêt   */  {TURN_ON      , TURN_OFF        , DOUBLE_FLUX, OPEN       , OPEN      },
/*Moyen   | Froid   | Marche  */  {TURN_ON      , TURN_ON         , DOUBLE_FLUX, OPEN       , OPEN      },
/*Moyen   | Chaud   | Arrêt   */  {TURN_ON      , TURN_OFF        , SIMPLE_FLUX, OPEN       , OPEN      },
/*Moyen   | Chaud   | Marche  */  {TURN_ON      , TURN_ON         , SIMPLE_FLUX, OPEN       , OPEN      },
/*Chaud   | Froid   | Arrêt   */  {TURN_OFF     , TURN_OFF        , DOUBLE_FLUX, CLOSE      , OPEN      },
/*Chaud   | Froid   | Marche  */  {TURN_OFF     , TURN_OFF        , DOUBLE_FLUX, CLOSE      , OPEN      },
/*Chaud   | Chaud   | Arrêt   */  {TURN_OFF     , TURN_OFF        , SIMPLE_FLUX, CLOSE      , CLOSE     },
/*Chaud   | Chaud   | Marche  */  {TURN_OFF     , TURN_OFF        , SIMPLE_FLUX, CLOSE      , CLOSE     }},

/*MODE HIVER */
/*Air Ext.| Air Int | Cheminée*/  /*VentiloCave | VentiloCheminee | DoubleFlux | BypassCave | BypassVMC */
/*Froid   | Froid   | Arrêt   */ {{TURN_OFF     , TURN_OFF        , DOUBLE_FLUX, CLOSE      , OPEN      },
/*Froid   | Froid   | Marche  */  {TURN_OFF     , TURN_ON         , DOUBLE_FLUX, CLOSE      , OPEN      },
/*Froid   | Chaud   | Arrêt   */  {TURN_OFF     , TURN_OFF        , DOUBLE_FLUX, CLOSE      , OPEN      },
/*Froid   | Chaud   | Marche  */  {TURN_OFF     , TURN_ON         , DOUBLE_FLUX, CLOSE      , OPEN      },
/*Moyen   | Froid   | Arrêt   */  {TURN_ON      , TURN_OFF        , DOUBLE_FLUX, OPEN       , OPEN      },
/*Moyen   | Froid   | Marche  */  {TURN_ON      , TURN_ON         , DOUBLE_FLUX, OPEN       , OPEN      },
/*Moyen   | Chaud   | Arrêt   */  {TURN_ON      , TURN_OFF        , DOUBLE_FLUX, OPEN       , OPEN      },
/*Moyen   | Chaud   | Marche  */  {TURN_ON      , TURN_ON         , DOUBLE_FLUX, OPEN       , OPEN      },
/*Chaud   | Froid   | Arrêt   */  {TURN_ON      , TURN_OFF        , DOUBLE_FLUX, OPEN       , OPEN      },
/*Chaud   | Froid   | Marche  */  {TURN_ON      , TURN_ON         , DOUBLE_FLUX, OPEN       , OPEN      },
/*Chaud   | Chaud   | Arrêt   */  {TURN_ON      , TURN_OFF        , SIMPLE_FLUX, OPEN       , CLOSE     },
/*Chaud   | Chaud   | Marche  */  {TURN_ON      , TURN_ON         , SIMPLE_FLUX, OPEN       , CLOSE     }}};
