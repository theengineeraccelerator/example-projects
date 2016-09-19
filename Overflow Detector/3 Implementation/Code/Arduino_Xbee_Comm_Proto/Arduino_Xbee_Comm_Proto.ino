#include <SoftwareSerial.h>

SoftwareSerial mySerial =  SoftwareSerial(3, 2);

byte data[14] = {0};
byte index = 0;
boolean newData = 0;
char serialChar = ' ';
char xbeeChar =' ';

void setup()  {
  //pinMode(13, OUTPUT);
  Serial.begin(4800);
  Serial.println("Goodnight moon!");
  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  mySerial.println("Hello, world?");
}

void parseData () {
  Serial.println("parsing data");
  for (byte i=0; i< sizeof(data); i++) {
    Serial.print("Field: "); Serial.print(i); Serial.print(" the data is: "); Serial.println(data[i], HEX);
  }
  
  if (data[12] == 0x10) {
    Serial.println("Overflow detected");
  }
}


void loop()                     // run over and over again
{

  //mySerial.print("1,");
  //delay(500);
  while (mySerial.available() > 0) {
        xbeeChar = mySerial.read();
        //Serial.println(xbeeChar);
    
      newData = true;
      data [index] = byte(mySerial.read());
      Serial.print("byte: "); Serial.println(data [index], HEX);
      Serial.print(char(data [index]));       
      index++;
  }
  if (newData) {
    // Serial.println("parsing transmission"); 
    Serial.println("");    
    index = 0;
    parseData ();
    newData = false;
  }
  
  while (Serial.available() > 0 ) {
     serialChar = Serial.read();
      Serial.println(serialChar);
      mySerial.print(serialChar);
  }
  delay(100);
}
