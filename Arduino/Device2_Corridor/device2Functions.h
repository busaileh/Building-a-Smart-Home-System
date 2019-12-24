#define motionSensor 3
#define relay 7
#define doorSwitch 6
#define SS_PIN 10
#define RST_PIN 5
#define buzzer 4


//-------XBee Initate---------
  XBee xbee = XBee();
  //--------XBee variable-------
  XBeeResponse response = XBeeResponse();
  ZBRxResponse rx = ZBRxResponse();
  //--------Addresses and stuff-------
  XBeeAddress64 addr64 = XBeeAddress64(0x0); //Broadcast
  ZBTxRequest zbTx;
  ZBTxStatusResponse txStatus = ZBTxStatusResponse();
  //----------------
  uint8_t payload[4];
  //----------------


//---NFC initiate---
MFRC522 mfrc522(SS_PIN,RST_PIN);
MFRC522::MIFARE_Key key;//Which creates a struct key

//NFC Variables
    byte block = 4;
  byte len = 18;
  byte buffer1[18];
  
  MFRC522::StatusCode status;
  
  byte readbackblock[18];//This array is used for reading out a block. The MIFARE_Read method requires a buffer that is at least 18 bytes to hold the 16 bytes of a block.
  int nuidPICC[4];
  //String cards[2] ={"22420820526","5510012857"};
  int cardOne[4] = {110,53,71,41};
  int cardTwo[4] = {82,1,155,13};
  char secuirtyOn[16] = {'h','o','m','e','_','s','e','c','u','r','i','t','y','_','o','n'};
  char securityOff[16] = {'h','o','m','e','_','s','e','c','u','r','i','t','y','_','o','f'};
  char data[16];
  int sector;

//Booleans
boolean secure = false;
boolean fsr = false;
boolean door = false;
boolean lightStatus = false;
boolean doorStatus = false;
boolean motionDetected= false;

boolean success = false;

//Timers
unsigned long last_light_on = 0;
unsigned long last_door_open = 0;


String sendData = "";
//XBEE FUNCTIONS
void sendData(String data){
  int type = 0;
  Serial.println("Sending Data");
    int i =0; //Define the payload size according the message being sent
  if(data.equals("status")){
    i = 8;
  } else {
    i = 4;
  }
  uint8_t payload[i];
  sendData = data;
  if(data.equals("secure")){
    //Securierty Stuff
    type = 40;
    payload[0] = type  >> 8 & 0xFF;
    payload[1] = type  & 0xFF;
    payload[2] = secure >> 8 & 0xFF;
    payload[3] = secure & 0xFF;

  } else if(data.equals("device")){
    //Device Concerning stuff
    int type = 30;
    int off = 11; //Means all devices to go off
    payload[0] = type  >> 8 & 0xFF;
    payload[1] = type  & 0xFF;
    payload[2] = off >> 8 & 0xFF;
    payload[3] = off & 0xFF;

  } else if(data.equals("door")){
    //Door status
    type = 20;
    payload[0] = type  >> 8 & 0xFF;
    payload[1] = type  & 0xFF;
    payload[2] = doorStatus >> 8 & 0xFF;
    payload[3] = doorStatus & 0xFF;


  } else if(data.equals("status")){
    //Data status
    type = 10;
    payload[0] = type  >> 8 & 0xFF;
    payload[1] = type  & 0xFF;
    payload[2] = lightStatus >> 8 & 0xFF;
    payload[3] = lightStatus& 0xFF;
    payload[4] = doorStatus >> 8 & 0xFF;
    payload[5] = doorStatus & 0xFF;
    payload[6] = secure >> 8 & 0xFF;
    payload[7] = secure & 0xFF;

  }

  zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
  xbee.send(zbTx);

  delay(10);

}


int getPinState(){
  int pin = digitalRead(motionSensor);
  return pin;
}

void lightOn(){
  if(!lightStatus){
     Serial.println("Light On");
    digitalWrite(relay,HIGH);
    lightStatus = true;}
 
  //motionDetected = true;
}

void lightOff(){
  if(lightStatus){
     motionDetected = false;
    lightStatus = false;
    Serial.println("Going off");
    digitalWrite(relay,LOW);
  }
 
}

//Door switch Functions
void checkDoor(){
  int value = digitalRead(doorSwitch);
  if(value == 1){
    doorStatus = true;
  } else if(value == 0 ){
    doorStatus = false;
  }
}

void analysPacket(String rxData){
     if(rxData == "010status"){
        sendData("status");
        
     }else if(rxData.equals("010secure")){
        //Turn Homesecurity on then confirm it is on
        secure = true;
        //Confirm it is on
        sendData("secure");
        
     }else if(rxData.equals("010unsecure")){
        secure = false;
        sendData("secure");
        
     }else if(rxData.equals("010lon")){
        //Turn light ON
        if(!lightStatus){
          lightOn();
          }
          
     }else if(rxData.equals("010loff")){
        //Turn Light Off
        if(lightStatus){
           lightOff();
        }
      else if(rxData.equals("alloff")){
          if(lightStatus){
           lightOff();
        }
      }
     } else if(rxData.equals("allstatus")){
       sendData("status");
       
     } 
     else if(rxData.equals("allloff")){
      
       lightOff();
      
     } else if(rxData.equals("alllon")){
      
      if(!lightStatus){
        lightOn();
      }
     }
      delay(10);
}

void detectMotion(){
  int value = getPinState();
  if(value ==1){
    if(!lightStatus && !motionDetected){
      motionDetected = true;
      last_light_on = millis();
      Serial.println("Light going on");
      lightOn();
    }
  }else if(motionDetected){
    if(lightStatus){
      Serial.println("Attempting");
      if(millis() - last_light_on  > 30000){
         lightOff();
      }
    }
  }
}

//FSR Functions
boolean checkFSR(){
  int value = analogRead(A0);
  value = map(value ,0,1023,0,50);
  
  if(value > 20) {
    Serial.println(F("We have splash down"));
    //touch discovered turn all devices off
    fsr =  true;
  } else {
    fsr =  false;
  }
}

void buzzYes(){
  tone(buzzer,1200);
  delay(200);
  noTone(buzzer);
  delay(10);
}
void buzzNo(){
  tone(buzzer,1200);
  delay(200);
  noTone(buzzer);
  delay(100);
  tone(buzzer,1200);
  delay(200);
  noTone(buzzer);

}


//NFC Functions
void readBlock() {
  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  Serial.println(F("**Card Detected:**"));
  //-------------------------------------------
  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex
  //-------------------------------------------
  byte buffer1[18];
  block = 4;
  len = 18;
  //------------------------------------------- GET Data
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  char temp ;
  String data = "";
  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32)
    {
      //Serial.write(buffer1[i]);
      temp = int(buffer1[i]);
      data += temp;
    }
  }

  if(data == "home_security_on" && !secure){
    success = true;
    secure = true;
  } else if(data == "home_security_of" && secure){
    success =true;
    secure = false;
  } else {
    success = false;
  }
  
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  
  if(success){
     buzzYes();
     
  }else {
      buzzNo();
   }
   delay(10);
}


String getDataResponse(ZBRxResponse rx){
   xbee.getResponse().getZBRxResponse(rx);
   //DebugSerial.print(F("Data Length:   "));
   //DebugSerial.println(rx.getPacketLength());
   int len = rx.getPacketLength() - 12;
   //DebugSerial.println(len);
   char arr[len];
   String str;
   for (int i = 0; i < len; i++) {
          char c = (rx.getData()[i]);
          arr[i]=c;
          str += String(arr[i]);
    }
   return str;
}



