#define relay 7
#define windowSwitch 6
#define rainMin 0
#define rainMax 1023
#define buzzer 4

boolean secured = false;



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




//Booleans

boolean rainy = false;
boolean lightStatus = false;
boolean windowStatus = false;


//Timers
unsigned long last_light_on = 0;
unsigned long last_window_open = 0;
unsigned long last_rain_check = 0;

int sentTimesWindow =0;
int sentTimesRainy = 0;


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

  if(data.equals("status")){
    //Securierty Stuff
    type = 10;

    payload[0] = type  >> 8 & 0xFF;
    payload[1] = type  & 0xFF;
    payload[2] = lightStatus >> 8 & 0xFF;
    payload[3] = lightStatus & 0xFF;
    payload[4] = windowStatus  >> 8 & 0xFF;
    payload[5] = windowStatus  & 0xFF;
    payload[6] = rainy >> 8 & 0xFF;
    payload[7] = rainy & 0xFF;

  } else if(data.equals("window")){
    //Device Concerning stuff
    int type = 20;
    payload[0] = type  >> 8 & 0xFF;
    payload[1] = type  & 0xFF;
    payload[2] = windowStatus >> 8 & 0xFF;
    payload[3] = windowStatus & 0xFF;

  } else if(data.equals("rain")){
    //Door status
    type = 30;
    payload[0] = type  >> 8 & 0xFF;
    payload[1] = type  & 0xFF;
    payload[2] = rainy >> 8 & 0xFF;
    payload[3] = rainy & 0xFF;

  }

  zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
  xbee.send(zbTx);

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



void lightOn(){
  Serial.println("Light On");
  digitalWrite(relay,HIGH);
  lightStatus = true;

}

void lightOff(){
  lightStatus = false;
  Serial.println("Going off");
  digitalWrite(relay,LOW);
}

//Window switch Functions
boolean checkWindow(){
  int value = digitalRead(windowSwitch);
  if(value == 0){
    last_window_open = 0;
    windowStatus = false;

  } else if(value == 1 ){
    last_window_open = millis();
    windowStatus = true;

  }
  return windowStatus;
}

void checkRain(){
  last_rain_check = millis();
  int reading = analogRead(A0);
  int range = map(reading, rainMin, rainMax, 0, 10);
  if(range < 4) {
    rainy =  true;
  } else{
    rainy =  false;
  }

}

void analysPacket(String rxData){
  if(rxData.equals("secured")){
    secured = true;
  }
   else if(rxData.equals("allstatus")){
    sendData("status");
   }
   else if(rxData.equals("100status")){
    sendData("status");
   }
   else if(rxData.equals("100lon")){
      lightOn();
   }
      else if(rxData.equals("100loff")){
      lightOff();
   }
      else if(rxData.equals("alloff")){
        //And turn off AC as well
      lightOff();
   } else if(rxData.equals("allloff")){
        //
      lightOff();
     
   }

     delay(10);
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
