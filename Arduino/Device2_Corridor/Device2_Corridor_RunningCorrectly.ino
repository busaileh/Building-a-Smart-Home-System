#include<SPI.h>
#include<MFRC522.h>
#include <XBee.h>
#include <Printers.h>
#include <AltSoftSerial.h>
#include "device2Functions.h"

AltSoftSerial SoftSerial;

#define DebugSerial Serial
#define XBeeSerial SoftSerial

int alreadySetup = 0;

boolean lastDoorStatus = false;
boolean lastFSRStatus = false;

unsigned long last_rx_time = 0;

int trySending = 0;


void setup() {

  pinMode(doorSwitch,INPUT_PULLUP);
  pinMode(motionSensor,INPUT);
  pinMode(relay,OUTPUT);
  digitalWrite(relay,LOW);
  pinMode(buzzer,OUTPUT);
  // put your setup code here, to run once:
  DebugSerial.begin(115200);
  DebugSerial.println(F("Starting..."));
  XBeeSerial.begin(9600);
  xbee.begin(XBeeSerial);

    SPI.begin();

    mfrc522.PCD_Init();
    

  delay(2000);
  Serial.println("Starting...");
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean lastStateSecure = secure;
   if(millis() - last_rx_time > 100){
    last_rx_time = millis();
    xbee.readPacket();
    if(xbee.getResponse().isAvailable()){
       if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
         String rxData = (getDataResponse(rx));
          analysPacket(rxData);
       }
       if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE){
          trySending++;
          DebugSerial.println("Response recived");
          
       if (txStatus.getDeliveryStatus() == SUCCESS) {
          trySending =0;
          DebugSerial.println("Succefuly sent");
          
      } else if(trySending <=2) {
        sendData(sendData);
        DebugSerial.println("Did'nt recieve confirmation trying again");
      }
    }
       delay(100);
  }
   }
  //
  //If we found a packet we'll wait and see what it is;   
  readBlock();
  //Fsr stuff
  fsr = lastFSRStatus;
  checkFSR();
  if(fsr != lastFSRStatus){
    if(fsr){
      sendData("device");
    }
   }
   
    //DOOOR Status stuff
   doorStatus = lastDoorStatus;
   door = checkDoor();
   if(doorStatus != lastDoorStatus){
    
      sendData("door");
    }

  //Security Stuff    
  if(secure != lastStateSecure){
  
    sendData("secure");
  }
  //Detecting the motion
   detectMotion();
 
}
  
      


