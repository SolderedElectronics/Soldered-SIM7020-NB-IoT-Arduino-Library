/**
 **************************************************
 *
 * @file        reportUsreButton.ino
 * @brief       This is an example for DEVIO NB-DEVKIT I. That has read sensor on board and report data to Magellan IoT Platform.
 *
 *
 *				product: www.solde.red/333072
 *
 * 				Modified by soldered.com
 *
 * @author		Device Innovation team     
 ***************************************************/

///  This is pinout for arduino UNO, for other board configuration check boards.h file
///    |  Do not use PIN  |
///    |  9 TX            |
///    |  8 RX            |
///    |  4 EINT          |
///    |  26 power key    |
///    |  5 reset         |

#include "SIM7020-NB-IoT-API-SOLDERED.h"
String address      = "";    // Your Server IP
String serverPort   = "";    // Your Server Port
String payload = "HelloWorld!";
String data_return;

const long interval = 20000;  //millisecond 
unsigned long previousMillis = 0;
int cnt=0;

AIS_SIM7020E_API nb;
void setup() {
    
  Serial.begin(115200);
  nb.begin(address,serverPort);
  Serial.println(F("-------------BEGIN-------------"));
  Serial.print(F(">>DeviceIP: "));
  Serial.println(nb.getDeviceIP());
  nb.pingIP(address);
  previousMillis = millis();

}

void loop() {
  data_return="";
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval){     
      cnt++;    
      // Send data in String 
      nb.sendMsgSTR(address,serverPort,payload+String(cnt));
      
      // Send data in HexString     
      //nb.sendMsgHEX(address,serverPort,payload+String(cnt));
      previousMillis = currentMillis;  
  }
  nb.waitResponse(data_return,address);
  if(data_return!="")Serial.println("# Receive : "+data_return);
}