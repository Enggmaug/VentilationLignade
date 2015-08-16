#include "lignade.h"
#include "Initialisation.h"

/*----- Autorise/Inhibe les messages sur le serial port -----*/
#define DEBUG 1

#if DEBUG
    #define DebugMessage(str) {Serial.println(str);}
#else
    #define DebugMessage(str) {}
#endif

/*-----------------------------------------------------------*/
/*----- Fonction d'initialisation                       -----*/
/*-----------------------------------------------------------*/
void setup() {
// si Debug autorisé, alors démarrage de la liaison serie
#if DEBUG
    Serial.begin(38400);
#endif

PinsSetup();
}
/*-----------------------------------------------------------*/
/*----- Machine d'états                                 -----*/
/*-----------------------------------------------------------*/
void loop() {
DebugMessage("Starting Loop");
delay(1000);

}
