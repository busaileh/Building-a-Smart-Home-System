XBee xbee = XBee();
//---------------
XBeeResponse response = XBeeResponse();
ZBRxResponse rx = ZBRxResponse();
//---------------
XBeeAddress64 addr64 = XBeeAddress64(0x0); //Broadcast
ZBTxRequest zbTx;
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

//----------------
#define buzzer 4
const int IRPin =  13;
const int relay =7;

boolean lightStatus = false;
boolean tvStatus = false;
boolean satDown = false;
boolean autoTvOn = false;
boolean autoTvOff = false;
boolean fsrStatus = false;
#include "TVIR.h"

//-----------------
uint8_t payload[4];

String sentData ="";
//----------------
String getDataResponse(ZBRxResponse rx){
   xbee.getResponse().getZBRxResponse(rx);
   int len = rx.getPacketLength() - 12;
   char arr[len];
   String str;
   for (int i = 0; i < len; i++) {
          char c = (rx.getData()[i]);
          arr[i]=c;
          str += c;
    }
   return str;
}

void getFSR(){
  int value = analogRead(A0);
  value = map(value,0,1023,0,10);
  if(value >= 2){
    fsrStatus = true;
  }else{
    fsrStatus = false;
  }
}

void lightOn(){
  if(!lightStatus){
    lightStatus = true;
    digitalWrite(relay,HIGH);
  }
}
void lightOff(){
  if(lightStatus){
   lightStatus = false;
   digitalWrite(relay,LOW);
  }
}

void tvOn(){
  SendChannelUpCode();
  tvStatus = true;
  Serial.println("Tv Going on");
}

void tvOff(){
  SendChannelUpCode();
  tvStatus = false;
  Serial.println("Tv Going off");
}



void sendStatus(){
  //Serial.println(tvStatus);
  //tvStatus = true;
  //Serial.println(tvStatus);
  int devStatus = digitalRead(7);
  //int tvStatus =1; //For now untill we find a way to read
  uint8_t statusPayload[4];
  statusPayload[0]=lightStatus >> 8 & 0xFF;
  statusPayload[1]=lightStatus & 0xFF;
  statusPayload[2]=tvStatus >> 8 & 0xFF;
  statusPayload[3]=tvStatus & 0xFF;
 
  //txRequest.setAddress64(0x0000000000000000);
  //txRequest.setPayload(statusPayload,sizeof(statusPayload));
  zbTx = ZBTxRequest(addr64, statusPayload, sizeof(statusPayload));
  xbee.send(zbTx);
}

void analysPacket(String rxData){
  sentData =rxData;
  if (rxData.equals("011lon")){
        //Light On
        Serial.println("Turning light on");
        lightOn();
       
      } else if(rxData.equals("011loff")){
        //Light Off
        Serial.println("Turning light off");
        lightOff();
        
      } else if(rxData.equals("011ton")){
        //TV On if the tv was off if t was on do nothing
         if(!tvStatus){
          tvOn();
         }
        
      } else if(rxData.equals("011toff")){
        Serial.println("Trying to turn tv OFF if tv was on");
        if(tvStatus) { //This will only read tv on if tv was triggered from arduino No other way to tell for now
          tvOff();
        }
        
      }else if(rxData.equals("011status")){
        Serial.println("Sending status");
        sendStatus();
        
      }else if(rxData.equals("allstatus")){
        sendStatus();
      }else if(rxData.equals("alloff")){
        if(tvStatus){
          tvOff();
        }
        lightOff();
      }
      else if(rxData.equals("allloff")){
        lightOff();
      }
      else if(rxData.equals("alllon")){
        lightOn();
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

