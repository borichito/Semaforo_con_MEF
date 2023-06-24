#include <Arduino.h>
#include <definiciones.h>
#include <semaforo.h>
#include <teclas.h>
 typedef enum {                                                 // variables para control para cada color del semaforo
   mverde,
   mamarillo,
   mrojo
  } colores_t;
   colores_t  colores; 

 typedef enum {                                               // variables usadas en la funcion de titilar usadas para la misma
   apagado,
   encendido 
  } tit_t;
  tit_t estado_led;

typedef enum {                                                 // modos de operacion del semaforo
   normal,
   desc,
   alarma
  } modos_t;
  modos_t  modo; 

float temp=1;                                                            // tiempo inicial de encendio de cada led, ira camiando cuando se presione el primer switch
int16_t banderaModos=0;
extern int16_t contadorp2;                                               // contadorp2 sera el encargado de cambiar los modos del semaforo

 
void apagar_led( control_Leds cleds){                                    // funcion para apagar los leds                          
for (int16_t i=0; i<cleds.len;i++){
  digitalWrite(*cleds.leds - i,LOW);
  }
}

void modoInit(){
  modo =  normal;                                                        // el semaforo inicia con el modo normal
}

void modoNormal(control_Leds cleds){
  //velocidad();
switch (colores)
   { 
   case mverde:                                                          // funcion para encender el led verde
   if(nbDelay(temp*3000)) {      
         digitalWrite(*cleds.leds+1,HIGH);                               // antes de pasar a ecender el led amarillo, el led verde se queda encendido
         colores= mamarillo;                                             // cuando se cumpla el tiempo pasa al siguiente color que es el amarillo
     } else{
        digitalWrite(*cleds.leds,HIGH);                                  // foco verde por 3000ms
        digitalWrite(*cleds.leds+1,LOW);
        digitalWrite(*cleds.leds+2,LOW);
        fsmButtonUpdate(*cleds.botones+1);                                // paara cambio de modo
        fsmButtonUpdate(*cleds.botones);                                  // paara el modo de velocidad
       
       if (banderaModos==1){
          apagar_led(cleds);                                              // manda ha apagar todos los leds
          break;
        }
     }
    break;
   case mamarillo:                                                        // encendido del led amarillo
   if(nbDelay(temp*500)) {     
        colores= mrojo;                                                   // cuando se cumpla el tiempo de delay pasara a encnder al led rojo
     } else{
        
        digitalWrite(*cleds.leds,HIGH);                                   // foco verde + amarillo por 500ms
        digitalWrite(*cleds.leds+1,HIGH);
        digitalWrite(*cleds.leds+2,LOW);
        fsmButtonUpdate(*cleds.botones+1);                                // paara cambio de modo
        fsmButtonUpdate(*cleds.botones);                                  // paara el modo de velocidad
        
        if (banderaModos==1){
          apagar_led(cleds);                                             // manda ha apagar todos los leds
          break;
        }
     }
   break;   
  case mrojo:                                                            // led rojo encendido
  if( nbDelay(temp*2000)) {     
        colores= mverde;                                                 // cuando se cumpla el delay, pasara al led verde nuevamente
     } else{
        
        digitalWrite(*cleds.leds,LOW);                                  // foco rojo por 2000 ms
        digitalWrite(*cleds.leds+1,LOW);
        digitalWrite(*cleds.leds+2,HIGH);
        fsmButtonUpdate(*cleds.botones+1);                               // paara cambio de modo
        fsmButtonUpdate(*cleds.botones);                                 // paara el modo de velocidad
      if (banderaModos==1){
          digitalWrite(*cleds.leds+2,LOW);                              // apaga el led rojo
          apagar_led(cleds);                                            // manda ha apagar todos los leds
          break;
        } 
     }
  break; 
   default:
    break;
   }
}

void titilar(int16_t ledtt,int16_t tiempo,control_Leds cleds){           // funcion usada para los modos de alarma y descompuesto, ya que en ambos modos titilan los leds
  switch (estado_led)
  {
  case encendido:                                                        // controla el tiempo de encendido del led
    if(nbDelay(tiempo)) {     
        estado_led= apagado;
     } else{
        digitalWrite(ledtt,HIGH);
        fsmButtonUpdate(*cleds.botones+1);                               // paara cambio de modo
        if (banderaModos==1){
          digitalWrite(ledtt,LOW);
         apagar_led(cleds);                                              // manda ha apagar todos los leds
          break;
        }
         } 
  break;
  case apagado:                                                          // controla el tiempo de apago del led
  if(nbDelay(tiempo)) {     
        estado_led= encendido;
     } else{
        digitalWrite(ledtt,LOW);
        fsmButtonUpdate(*cleds.botones+1);                                // paara cambio de modo
        if (banderaModos==1){
         apagar_led(cleds);                                               // manda ha apagar todos los leds
          break;
        }
     }
    break;
  default:
    break;
  }
}




void mod(control_Leds cleds){                                          // funcion para los distintos modos de operacion del semaforo
    int16_t tiempoA =500;                                              // tiempo de parpadeo para modo desconectado
    int16_t tiempoR = 1000;                                           // tiempo de parpadeo para modo alarma
    int16_t foco_des = *cleds.leds+1;                                 // foco amarillo para que titile
    int16_t foco_alar = *cleds.leds+2;                                // foco rojo para que titile
    switch (modo)
    {
    case normal: 
    modoNormal(cleds);                                                // entra ala fucnion donde el semaforo opera de manera normañ
    banderaModos = 0;   
    if (contadorp2==2){                                               // cuando se pulse el boton 2 pasara al sigueinte modo hacueno que la variable modo que controla el switch pase al siguiente estado
      modo = desc;
    }
    break;
    case desc:
    titilar(foco_des,tiempoA,cleds);
    banderaModos = 0;   
    if (contadorp2==3){                                                // pasa al sigueinte de estado (alarma) cuando se pulsa nuevamente el switch 2
      modo = alarma;
    }
     break;
    case alarma:
    titilar(foco_alar,tiempoR,cleds);
    banderaModos = 0;                                                  
    if (contadorp2==1){
      modo = normal;                                                    // vulve al estado normal si se preciona nuevamente el switch 2                                           
    }
     break;
    default:
      break;
    }    
}
