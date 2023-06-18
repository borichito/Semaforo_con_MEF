#include <Arduino.h>
#include <definiciones.h>
#include <semaforo.h>
#include <teclas.h>
 typedef enum {
   mverde,
   mamarillo,
   mrojo
  } colores_t;
   colores_t  colores; 

 typedef enum {
   apagado,
   encendido 
  } tit_t;
  tit_t estado_led;

typedef enum {
   normal,
   desc,
   alarma
  } modos_t;
  modos_t  modo; 

float temp=1;                                                                                       // tiempo inicial de encendio de cada led
int16_t banderaModos=0;
extern int16_t contadorp2;

 
void apagar_led( control_Leds cleds){                            // funcion para apagar los leds                          
for (int16_t i=0; i<cleds.len;i++){
  digitalWrite(*cleds.leds - i,LOW);
  }
}

void modoInit(){
  modo =  normal;
}

void modoNormal(control_Leds cleds){
  //velocidad();
switch (colores)
   { 
   case mverde: 
   if(nbDelay(temp*3000)) {     
         digitalWrite(*cleds.leds+1,HIGH);
         colores= mamarillo;
     } else{
        digitalWrite(*cleds.leds,HIGH);                                   // foco verde por 3000ms
        digitalWrite(*cleds.leds+1,LOW);
        digitalWrite(*cleds.leds+2,LOW);
        fsmButtonUpdate(*cleds.botones+1);                                 // paara cambio de modo
        fsmButtonUpdate(*cleds.botones);                                 // paara el modo de velocidad
       
       if (banderaModos==1){
          apagar_led(cleds);                                        // manda ha apagar todos los leds
          break;
        }
     }
    break;
   case mamarillo:
   if(nbDelay(temp*500)) {     
        colores= mrojo;
     } else{
        
        digitalWrite(*cleds.leds,HIGH);                            // foco verde + amarillo por 500ms
        digitalWrite(*cleds.leds+1,HIGH);
        digitalWrite(*cleds.leds+2,LOW);
        fsmButtonUpdate(*cleds.botones+1);                                 // paara cambio de modo
        fsmButtonUpdate(*cleds.botones);                                 // paara el modo de velocidad
        
        if (banderaModos==1){
          apagar_led(cleds);                                        // manda ha apagar todos los leds
          break;
        }
     }
   break;   
  case mrojo:
  if( nbDelay(temp*2000)) {     
        colores= mverde;
     } else{
        
        digitalWrite(*cleds.leds,LOW);                            // foco rojo por 2000 ms
        digitalWrite(*cleds.leds+1,LOW);
        digitalWrite(*cleds.leds+2,HIGH);
        fsmButtonUpdate(*cleds.botones+1);                                 // paara cambio de modo
        fsmButtonUpdate(*cleds.botones);                                 // paara el modo de velocidad
      if (banderaModos==1){
          digitalWrite(*cleds.leds+2,LOW);                            // apaga el led rojo
          apagar_led(cleds);                                         // manda ha apagar todos los leds
          break;
        } 
     }
  break; 
   default:
    break;
   }
}

void titilar(int16_t ledtt,int16_t tiempo,control_Leds cleds){
  switch (estado_led)
  {
  case encendido:
    if(nbDelay(tiempo)) {     
        estado_led= apagado;
     } else{
        digitalWrite(ledtt,HIGH);
        fsmButtonUpdate(*cleds.botones+1);                                 // paara cambio de modo
        if (banderaModos==1){
          digitalWrite(ledtt,LOW);
         apagar_led(cleds);                                        // manda ha apagar todos los leds
          break;
        }
         } 
  break;
  case apagado:
  if(nbDelay(tiempo)) {     
        estado_led= encendido;
     } else{
        digitalWrite(ledtt,LOW);
        fsmButtonUpdate(*cleds.botones+1);                                 // paara cambio de modo
        if (banderaModos==1){
         apagar_led(cleds);                                        // manda ha apagar todos los leds
          break;
        }
     }
    break;
  default:
    break;
  }
}




void mod(control_Leds cleds){ 

   // modo= normal;

    int16_t tiempoA =500;                                        // tiempo de parpadeo para modo desconectado
    int16_t tiempoR = 1000;                                      // tiempo de parpadeo para modo alarma
    int16_t foco_des = *cleds.leds+1;                           // foco amarillo para que titile
    int16_t foco_alar = *cleds.leds+2;                          // foco rojo para que titile
    switch (modo)
    {
    case normal:
    modoNormal(cleds);
    banderaModos = 0;   
    if (contadorp2==2){
      modo = desc;
    }
    break;
    case desc:
    titilar(foco_des,tiempoA,cleds);
    banderaModos = 0;   
    if (contadorp2==3){
      modo = alarma;
    }
     break;
    case alarma:
    titilar(foco_alar,tiempoR,cleds);
    banderaModos = 0;   
    if (contadorp2==1){
      modo = normal;
    }
     break;
    default:
      break;
    }    
}
