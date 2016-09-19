//**************************************************
/*
  Author: Malcolm Knapp
  Project: 
  Date: 
  Version:
  Description:
*/ 
//***************************************************

#include "State_Machine.h"

void updateState () {
 switch (state) {
    //**********************************************************************************************
    /* 
     UI Description: The UI is a polling based system. A switch statement is used to contain 
     state information. With each state there are events handle user interaction, timer completion
     and communication. The timer is based around a 1s clock taken from the millis() function.
     
     */
    //**********************************************************************************************

  case NORMAL:
  
      if (event == entry) {
        Serial.println ("In Normal");
        digitalWrite (LIGHT_PIN, OFF);
        event = NONE;
      }
   
    break; 
    
    
    case ALARM:
    
      if (event == entry) {
          Serial.println ("in Alarm");
          Serial.println("start speaker");
          timerList[SPEAKER_ON][VALUE] = START;
          Serial.println ("turning light on");
          digitalWrite (LIGHT_PIN, ON);
          timerList[LIGHT_ON][VALUE] = START;
          event = NONE;
      }
      
      if (event ==  alarm_ack ) {
        Serial.println ("alarm acknowledged");
        state = ALARM_ACK;
        event = entry;
        delay (10);   // to prevent the button from triggering more than once. There seems to be a bug in the Button library but this is a effective work around. 
      }
      
    break;
    
    
    case ALARM_ACK:
    
      if (event == entry) {
          Serial.println ("in Alarm acknowledged");
          Serial.println ("turning speaker off");
          noTone(SPEAKER_PIN);
          Serial.println ("turning off timers");
          for (byte timer = 0; timer < NUMBER_OF_TIMER; timer++) {
            timerList [timer][0] = TIMED_OUT;
          }
          Serial.println ("turning light on"); 
          digitalWrite (LIGHT_PIN, ON);
          event = NONE;
      }
      
      if (event == end_alarm) {
        Serial.println ("alarm ended");
        alarm = false;
        state = NORMAL;
        event = entry;
      }
    break;
    
 }
     
}

void printState () {
     Serial.print ("State "); Serial.println (state);
 
}
