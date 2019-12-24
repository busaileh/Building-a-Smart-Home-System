#define buzzer 2


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
#include "DHT.h"
#define DHTPIN 4
DHT dht(DHTPIN,DHT11);
//-----------------
uint8_t payload[4];
//----------------

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
float getHum(){
    int i =0;
    float hum = dht.readHumidity();
    if (isnan(hum) && i <=3) {
      Serial.println(F("Failed to read from DHT sensor!"));
       getHum();
       i++;
    } 
    else if (i >=3 && isnan(hum)){
      Serial.println(F("Hum Couldnt be found"));
      return -100.0;
     }
    return hum;
  }
float getTemp(){
   int i =0;
   float temp = dht.readTemperature();
   if (isnan(temp) && i <=3) {
      getTemp();
      i++;
    } 
    else if (i >=3 && isnan(temp)){
      return -100.0;
    }
   return temp;
}
void sendData(){
  uint8_t payload[4];
  int temp = getTemp();
  int hum = getHum();
  Serial.println(getTemp());
  Serial.println(getHum());
  payload[0] = temp >> 8 & 0xFF;
  payload[1] = temp & 0xFF;
  payload[2] = hum >> 8 & 0xFF;
  payload[3] = hum & 0xFF;
  zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
  xbee.send(zbTx);
 
}


