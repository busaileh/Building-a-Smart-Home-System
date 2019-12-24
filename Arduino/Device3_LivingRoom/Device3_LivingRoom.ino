
#include <XBee.h>
#include <Printers.h>
#include <AltSoftSerial.h>
#include "hexa.h"
//XBee xbee = XBee();
AltSoftSerial SoftSerial;
#define DebugSerial Serial
#define XBeeSerial SoftSerial


unsigned long last_tv_on = 0;
unsigned long last_fsr_time = 0;

boolean lastTvStatus = false;
boolean lastFsrStatus = false;

String rxData;
int value =0;

int trySending = 0;


void setup() {
  // Setup debug serial output
  DebugSerial.begin(115200);
  DebugSerial.println(F("Starting..."));
  // Setup XBee serial communication
  XBeeSerial.begin(9600);
  xbee.begin(XBeeSerial);
  pinMode(buzzer,OUTPUT);
  pinMode(relay,OUTPUT);
  digitalWrite(relay,LOW);
  pinMode(IRPin,OUTPUT);
  
  delay(2000);
  buzzYes();
}

void loop() {
  // Check the serial port to see if there is a new packet available

   xbee.readPacket();

  if(xbee.getResponse().isAvailable()){
    
    DebugSerial.print(F("Got Something, API ID is: "));
    
    DebugSerial.println(xbee.getResponse().getApiId());
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
      rxData = (getDataResponse(rx));
      Serial.println("Recieved: ");
      Serial.println(rxData);
      //DebugSerial.println(rxData);
      
    }
    
    if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE){
       //Transmite Request Status
      //DebugSerial.println("Response recived");
      trySending++;
      if (txStatus.getDeliveryStatus() == SUCCESS) {
        DebugSerial.println("Succefuly sent");
        trySending = 0;
      }else if(trySending <=2){
        //Try sending again
        sendData(sentData);
      }
    }
    if(xbee.getResponse().isError()){
      DebugSerial.println("Error Reading Packet");
    }

  if (millis() - last_fsr_time > 100) {
       value = getFSR();
        last_fsr_time = millis();
   }
  }

  if(value >=2){
    satDown = true;
  } else{
    satDown =false;
  }

  
  if(satDown && !tvStatus){
    autoTvOn = true;
    tvOn();
    
  } else if(tvStatus &&  autoTvOn && !satDown){
    last_tv_on = millis();
    autoTvOff = true;
    autoTvOn = false;
    
  } if(autoTvOff && millis() - last_tv_on > 1200000){
    tvOff();
    autoTvOff = false; 
  }
  
}
