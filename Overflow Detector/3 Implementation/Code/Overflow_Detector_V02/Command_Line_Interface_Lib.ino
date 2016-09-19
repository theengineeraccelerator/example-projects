//**************************************************
//
//  Author: Malcolm Knapp
//  Project: 
//  Date: 
//  Version:
//  Description:
// 
//***************************************************

String cmdType = "";
String cmdSubType ="";
String cmdBody = "";


//**********************************************************************************************
/* 
 Function: parseCommand
 
 Inputs: char *cmd: command parsed
 
 Returns: None
 
 Description: parses commands that come from either the PC or the GSM module. Commands are of 
 the form
 
 XXXYYYZZZZZZZZZZZZZZZZ
 
 XXX: Command type
 YYY: Command Subtype
 ZZZZZZZZZZZ: Command body
 
 Commands 
 
 */
//**********************************************************************************************
void parseCommand (String cmd) {
  int len = 0;
  int index;
  byte section = 0;
  char delimiter = ' ';
  for (index = 0; index < cmd.length(); index++) {
    if (cmd.charAt(index) == delimiter) section++;
    else {
      switch (section){
        case 0: 
          //Serial.println ("section 0");
          cmdType.concat(cmd.charAt(index));
          break;
        case 1: 
          //Serial.println ("section 1");
          cmdSubType.concat(cmd.charAt(index));
          break;
        case 2:
          //Serial.println ("section 2"); 
          cmdBody.concat(cmd.charAt(index));
        break;
      }
    }
  }


   Serial.print("cmd type: "); Serial.println(cmdType);
   Serial.print("cmd sub type: "); Serial.println(cmdSubType);
   Serial.print("cmd Body: "); Serial.println(cmdBody);

  if(cmdType.equals("MSG")) {

    if(cmdSubType.equals("XBE")) {
      Serial.println("Sending Command to Xbee");
      len = cmd.length();
      Serial.print("command length: "); Serial.println (len);
      for (index; index < len; index++) {
          Serial.print(cmd.charAt(index));
          mySerial.print(cmd.charAt(index));
      }
    }
  }
  
  
  if(cmdType.equals("TMR")) {

    if(cmdSubType.equals("LGT")) {
      Serial.println("starting light toggle");
      digitalWrite (8, ON);
      timerList[LIGHT_ON][VALUE] = START;
      }
  }
      
  if(cmdType.equals("TST")) {

    if(cmdSubType.equals("OVR")) {
      state = ALARM;
      event = entry;
      alarm = true;
      }
      
  }
  cmd = "";
  cmdType = "";
  cmdSubType ="";
  cmdBody = "";
  
}
   
