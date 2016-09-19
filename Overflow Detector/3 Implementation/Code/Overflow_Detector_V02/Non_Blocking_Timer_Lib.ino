//**************************************************
/*
  Author: Malcolm Knapp
  Project: 
  Date: 
  Version:
  Description:
*/ 
//***************************************************

#include "Non_Blocking_Timer.h"

void updateTimers() {
    for (byte timer = 0; timer < NUMBER_OF_TIMER; timer++) {
      if (timerList [timer][0] > TIMED_OUT ) { 
        if (timerList [timer][0] == timerList [timer][1]) {
          timerHandler(timer, timerList [timer][0] );
        } else {
          //Serial.print ("Timer "); Serial.print (timer); Serial.print (" value is "); Serial.println (timerList[timer][VALUE]);
          timerList [timer][0]++;
        }
      }
   }
}

void timerHandler(byte t, int t_value) {
 byte _t = t;
 int _tValue = t_value;

 timerList [_t][0] = TIMED_OUT;
 
 switch (_t) {
   
   case SPEAKER_ON:
       Serial.println("speaker off");
       noTone(SPEAKER_PIN);
       timerList[SPEAKER_OFF][VALUE] = START; 
   break;
   
   case SPEAKER_OFF:
       Serial.println("speaker on");
       tone (SPEAKER_PIN, 1047);
        timerList[SPEAKER_ON][VALUE] = START;     
   break;
   
   case LIGHT_ON:
       // turn Light off
       Serial.println("light off");
       digitalWrite (LIGHT_PIN,OFF);
       timerList[LIGHT_OFF][VALUE] = START;
       
   break;
   
   case LIGHT_OFF:
       // turn Light on
       Serial.println("light on");
       digitalWrite (LIGHT_PIN,ON);
       timerList[LIGHT_ON][VALUE] = START;
   break;
   
  case START_SPEAKER:
       // turn on speaker
//       Serial.println("start speaker");
//       timerList[SPEAKER_ON][VALUE] = START;
   break;
  
  
 
  }
}

void printTimers () {
  for (byte index = 0; index < NUMBER_OF_TIMER; index++){
    Serial.print ("Timer "); Serial.print (index); Serial.print (" value is "); Serial.println (timerList[index][VALUE]);
  }
    
}
  
