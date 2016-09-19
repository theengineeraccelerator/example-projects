//**************************************************
/*
  Author: Malcolm Knapp
  Project: 
  Date: 
  Version:
  Description:
*/ 
//***************************************************
#ifndef NON_BLOCKING_TIMER_H
#define NON_BLOCKING_TIMER_H

#define SECONDS 4
typedef unsigned char byte;

unsigned long BASE_TIMEOUT = 250; // timer tick for the whole system set at 250ms. 
unsigned long baseTimedOut = 250;

const int VALUE = 0;
const int START = 0;

const int TIMEOUT = 1;
const int TIMED_OUT = -1;

int timerValue = 0;
int timeOut = 0;

enum {
  SPEAKER_ON = 0, // Add timer names 
  SPEAKER_OFF, // Add timer names 
  LIGHT_ON,
  LIGHT_OFF,
  START_SPEAKER,
  NUMBER_OF_TIMER,   // do not put timer names after this enrty 
}TIMER_NAMES;

int timerList [][2] = {   // [current timer value][timeout value]
  {-1,1*SECONDS},       //SPEAKER_ON
  {-1,1*SECONDS},        // SPEAKER_OFF
  {-1,2},       // LIGHT_ON
  {-1,2},         // LIGHT_OFF
  {-1,7200*SECONDS}         // START_SPEAKER
};

#endif
