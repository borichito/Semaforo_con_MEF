#include <Arduino.h>
#include <semaforo.h>
#include <definiciones.h>
#include <teclas.h>


const int16_t rojo = 6;const int16_t verde = 4; const int16_t amarillo = 5;                             // leds
const int16_t pul1= 9 ;const int16_t pul2= 10 ;const int16_t pul3= 11;       const int16_t pul4= 12;    // botones
int16_t led_arreglo [] = {verde,amarillo,rojo};                                                         // arreglo de leds
int16_t pulsantes [] = {pul1,pul2,pul3,pul4};                                                           // arreglo de pulsantes
int16_t len = sizeof(led_arreglo)/ sizeof(int16_t);                                                     // longitud(da bits y se necesita didivir para bits)
int16_t lenp = sizeof(pulsantes)/ sizeof(int16_t);                                                     // longitud(da bits y se necesita didivir para bits)


void setup() {
  Serial.begin(115200);
  for(int i=0;i<len;i++){
    pinMode(led_arreglo[i], OUTPUT);                              // declaro leds de salida
    }
  for(int i=0;i<lenp;i++){
    pinMode(pulsantes[i], INPUT);                                 // declaro los pulsantes de entrada
    }    
}

void loop() {
control_Leds cleds = {led_arreglo,pulsantes,len};  // uso de la estructura 
modoInit();                                        // iniciara em mod normal
fsmButtonInit ();                                  // iniciara el boton alzado
while (1){
mod(cleds);                                         // funcion para el control general del semaforo
}
}
