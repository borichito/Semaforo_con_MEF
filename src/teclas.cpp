#include <Arduino.h>
#include <definiciones.h>

typedef enum  {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_FALLING,
    BUTTON_RISING
  } fsmButtonState_t;
   fsmButtonState_t fsmButtonState; 
int16_t contadorp1 = 1;                                                              // contador para el pulsante uno
int16_t contadorp2 = 1;                                                              // contador para el pulsante dos
extern float temp;
extern int16_t banderaModos;

void fsmButtonInit (void){                                                           // inicia con el boton en estado alto                                                      
fsmButtonState = BUTTON_UP;
}



void fsmButtonError(void){                                                           // cuando se de algun error
  fsmButtonState= BUTTON_UP;
}

void buttonPressed(void){                                                           // funcion que se ejecuta cuando detecta que se preciono
}

void buttonReleased(void){                                                         // funcion que se ejecuta en flancos de subida
  contadorp1 = contadorp1 +1;                                                      // contador que controla la velocidad del modo normal
if (contadorp1>3){                                     
  contadorp1 =1;                                                                   // cuando pase de  3 regresa a  1 
}
if (contadorp1 == 1){                                                             // contador 1 para la velocidad de X0.5
  temp=0.5;
}
if (contadorp1 == 2){
  temp=1;                                                                        // contador 2 para la velocidad de X1
}
if (contadorp1 == 3){                                                            // contador 3 para la velocidad de X2
  temp=2;
}
//Serial.println(contadorp1);
}


void  buttonModos(){                                                              // funcion que se ejecuta en fancos de subida
banderaModos=1;
contadorp2 = contadorp2 +1;
if (contadorp2>3){
  contadorp2 =1;
  }
}


void fsmButtonUpdate( int16_t SW){                                              // funcion para controlar los estados de los pulsantes
  //Serial.println(SW);
  switch (fsmButtonState){
    case BUTTON_UP:
      if (!digitalRead(SW)){
        fsmButtonState = BUTTON_FALLING;  
      }
      break;
    case BUTTON_DOWN:
      if (!digitalRead(SW)){
        fsmButtonState = BUTTON_RISING;
      }
      break;
    case BUTTON_FALLING:
      if (nbDelay(40)){
           if (!digitalRead(SW)){
               fsmButtonState = BUTTON_DOWN;
               buttonPressed();
           } else {
            fsmButtonState = BUTTON_UP;
           }
      case BUTTON_RISING:
      if (nbDelay(40)){
           if (digitalRead(SW)){
               fsmButtonState = BUTTON_UP;
               Serial.println(SW);
               if(SW==9){                                                   // para la velocidad
                  buttonReleased(); 
                  Serial.begin(115200);
                  Serial.println("Entro al boton de cambio de velocidad");
                  Serial.write("1");                                      // impresion  uart
               }
               if (SW==10){                                              // para el cambio de modo
                  buttonModos();
                 Serial.println("Entro al boton de cambio de modo");
                 Serial.write("2");                                      // impresion p uart
               }
           } else {
               fsmButtonState = BUTTON_DOWN;
           }
        }
        break;
      default:
      fsmButtonError();
      break;
      }
  }
}
