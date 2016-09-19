//**************************************************
/*
  Author: Malcolm Knapp
  Project: 
  Date: 
  Version:
  Description:
*/ 
//***************************************************
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

enum {
  alarm_ack = 0,
  end_alarm,
  entry,
  NONE,
} EVENTS;

enum {
  // States
  NORMAL = 1,
  ALARM,
  ALARM_ACK,
  ERROR,
} STATES;

byte state = NORMAL;       // Tracks current state
byte prevState = NORMAL;
byte event = entry;        // Triggers a particular action within current state



#endif
