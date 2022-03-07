 /**
 **************************************************
 *
 * @file        reportUserButton.ino
 * @brief       This is an example for DEVIO NB-DEVKIT I. That has read sensor on board and report data to Magellan IoT Platform.
 *
 *
 *				      product: www.solde.red/333072
 *
 * 				      Modified by soldered.com
 *
 * @author		  Device Innovation team     
 ***************************************************/

//Connection diagram for Dasduino Core(or any other ATMega328P board),
//for other boards check boards.h file in this library
//Breakout      Arduino
//|-------------|
//VCC-----------5V
//RXD-----------4
//TXD-----------2
//PWRKEY--------5
//ADC-----------NOT CONNECTED
//UARTRI--------NOT CONNECTED
//GND-----------GND

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
    
  Serial.begin(115200); //Begin serial communication with PC using baud rate of 115200 bauds/s
  nb.begin(address,serverPort); //Initialize server
  Serial.println(F("-------------BEGIN-------------"));
  Serial.print(F(">>DeviceIP: "));
  Serial.println(nb.getDeviceIP()); //Get IP address of device
  nb.pingIP(address);
  previousMillis = millis();

}

void loop() {
  data_return="";
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval){     
      cnt++;    
      nb.sendMsgSTR(address,serverPort,payload+String(cnt));// Send data in String 
      //nb.sendMsgHEX(address,serverPort,payload+String(cnt)); // Send data in HexString    
      previousMillis = currentMillis;  
  }
  nb.waitResponse(data_return,address);
  if(data_return!="")Serial.println("# Receive : "+data_return);
}
