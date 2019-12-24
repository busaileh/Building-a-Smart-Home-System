
#include <XBee.h>
#include <Printers.h>
#include <AltSoftSerial.h>
#include "hexa.h"

AltSoftSerial SoftSerial;
#define DebugSerial Serial
#define XBeeSerial SoftSerial

//Last Update variables

unsigned long last_tx_time = 0;


void setup() {
  // Setup debug serial output
  DebugSerial.begin(115200);
  DebugSerial.println(F("Starting..."));
  // Setup XBee serial communication
  dht.begin();
  pinMode(buzzer,OUTPUT);
  XBeeSerial.begin(9600);
  xbee.begin(XBeeSerial);
  delay(2000);
  buzzYes();
}


void loop() {

  xbee.readPacket();

  // Check the serial port to see if there is a new packet available
  
  if(xbee.getResponse().isAvailable()){

       if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
        DebugSerial.println("In here");
             String rxData = (getDataResponse(rx));
              DebugSerial.println(rxData);
      
      if (rxData.equals("001status")){
        DebugSerial.println("Sending status now");
        sendData();
        delay(10);
        
      } else if(rxData.equals("allstatus")){
        sendData();
        delay(10);
      }
    }
    
    if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE){
       //Transmite Request Status
      //DebugSerial.println("Response recived");
      if (txStatus.getDeliveryStatus() == SUCCESS) {
        DebugSerial.println("Succefuly sent"); 
      }
     
    }
    
    if(xbee.getResponse().isError()){
      DebugSerial.println("Error Reading Packet");
    }
      
  
      }
  
}
