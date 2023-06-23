#include <Arduino.h>
//#include <def_compartidas.h>
typedef struct  {                                                                                       // coleccion de diferentes datos, 
  int16_t* leds;                                                                                        // puntero al array de los leds
  int16_t* botones;                                                                                     // puntero al array de los botones
  int16_t len;                                                                                          // long de los leds
  }control_Leds;

void mod(control_Leds cleds);                                                                          // funcion que se encarga del modo ya sea modo normal, alerta o descompuesto
void modoInit();                                                                                       // funcion que toma como inicio el programa y sera el modo normal
