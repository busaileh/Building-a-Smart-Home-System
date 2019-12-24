#include <XBee.h>
#include <AltSoftSerial.h>
#include "Device4Hexa.h"

AltSoftSerial SoftSerial;

#define DebugSerial Serial
#define XBeeSerial SoftSerial

boolean window = false;

boolean lastRainyStatus = false;


void setup() {
  // put your setup code here, to run once:
  pinMode(windowSwitch,INPUT_PULLUP);
  pinMode(relay,OUTPUT);
  digitalWrite(relay,LOW);
  pinMode(buzzer , OUTPUT);
  DebugSerial.begin(115200);
  DebugSerial.println(F("Starting..."));
  XBeeSerial.begin(9600);
  xbee.begin(XBeeSerial);
  delay(2000);
  buzzYes();
}

void loop() {
  // put your main code here, to run repeatedly:
    xbee.readPacket();
  //If we found a packet we'll wait and see what it is;
  if(xbee.getResponse().isAvailable()){
       if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
         String rxData = (getDataResponse(rx));
          analysPacket(rxData);
       }
  }

boolean lastWindowStatus = windowStatus;
 window = checkWindow();
 if(windowStatus != lastWindowStatus){
  sendData("window");
 }

  lastRainyStatus = rainy;

 if(rainy != lastRainyStatus){
  sendData("rain");
  if(rainy){
    last_rain_check = millis();
  } else {
    last_rain_check = 0;
 }
 
 checkRain();

 
 } if(rainy && millis() - last_rain_check > 100000){
    sendData("rain");
 }

 
  

}
