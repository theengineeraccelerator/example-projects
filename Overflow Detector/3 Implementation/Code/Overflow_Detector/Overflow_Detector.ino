

//**************************************************
/*
  Author: Malcolm Knapp
 Project: Overflow Detector 
 Date: 4/14/13
 Version: 0.1
 Description:  This code handles the alarm indicators and user interface for the Overlfow detector. 
 */
//***************************************************
#include <SoftwareSerial.h>
#include <Button.h>
#include "Non_Blocking_Timer.h"
#include "State_Machine.h"


#define OFF LOW
#define ON HIGH

// define pin connections
#define LIGHT_PIN 13
#define BUTTON_PIN 12
#define SPEAKER_PIN  11
SoftwareSerial mySerial =  SoftwareSerial(3, 2);  // (tx, rx)
Button resetButton = Button(BUTTON_PIN, BUTTON_PULLUP_INTERNAL, true, 50);

String userInput;
boolean cmdFlag = false;

byte data[13] = {
  0};
byte index = 0;
boolean newData = false;
boolean alarm = false;


void parseData () {
  Serial.println("parsing data");
    for (byte i=0; i< sizeof(data); i++) {
      Serial.print("Field: "); Serial.print(i); Serial.print(" the data is: "); Serial.println(data[i], HEX);
    }


  if (alarm == false) {
    state = ALARM;
    event = entry;
    alarm = true;
  }


  if (data[11] == 0x10) {
    Serial.println("Overflow detected");

  }
}


void setup () {
  Serial.begin (4800);
  mySerial.begin(4800);

  // initialize input and outputs
  pinMode (LIGHT_PIN, OUTPUT);
  digitalWrite(LIGHT_PIN, OFF); // initialize to off
  pinMode (SPEAKER_PIN, OUTPUT);
  digitalWrite(SPEAKER_PIN, OFF); // initialize to off
  digitalWrite (LIGHT_PIN,ON);
  delay(200);
  digitalWrite (LIGHT_PIN,OFF);
  delay(200);
  digitalWrite (LIGHT_PIN,ON);
  delay(200);
  digitalWrite (LIGHT_PIN,OFF);
  delay(200);
  digitalWrite (LIGHT_PIN,ON);
  delay(500);
  digitalWrite (LIGHT_PIN,OFF);

}

void loop () {
  //  if(resetButton.isPressed()){
  //     Serial.println("button is pressed");
  //  }
  //  
  if(resetButton.uniquePress()){
    Serial.println("button pressed"); 
    if (state == ALARM) {
      event = alarm_ack;
    }
    if (state == ALARM_ACK) {
      event = end_alarm;
    }

  }

  updateState();

  if (millis() < (baseTimedOut-BASE_TIMEOUT)) {  // millis() overflow protection
    Serial.println ("millis() overflowed\n");
    baseTimedOut = millis() + BASE_TIMEOUT;  
  }

  if(millis() > baseTimedOut) {
    updateTimers();
    printState();
    //printTimers();
    baseTimedOut = millis() + BASE_TIMEOUT;  
  }


  //**********************************************************************************************
  /* 
   PC Serial Input: Serial input comes from a PC over a USB cable. The termination character is
   a carriage return. It is read in and then sent to command parsing. 
   */
  //**********************************************************************************************

  while (mySerial.available() > 0) {
    newData = true;
    data [index] = byte(mySerial.read());
    //Serial.print("byte: "); Serial.println(data [index], HEX);      
    index++;
  }
  if (newData) {
    // Serial.println("parsing transmission");    
    index = 0;
    parseData ();
    newData = false;
  }


  if(Serial.available()>0){

    int inByte = Serial.read();
    if (inByte == 13) {  // carraige return
      cmdFlag = true;                 
      Serial.print("Command sent: ");  
      Serial.println(userInput); 
      inByte = 0;
    } 
    else {
      userInput.concat(char(inByte)); 
    }
  }
  if (cmdFlag) {
    parseCommand(userInput);
    userInput = "";
    cmdFlag = false;
  }
}

