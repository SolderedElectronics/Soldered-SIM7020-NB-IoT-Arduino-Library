/*
  Supported DEVIO NB-DEVKIT I Board 
    |  Do not use PIN   |
    |        9 TX        |
    |        8 RX        |
    |      4 EINT       |
    |   26 power key    |
    |     5 reset      |
  This is an example for DEVIO NB-DEVKIT I. That has report the user button to Magellan IoT Platform.
  
  Please login and enjoy with https://magellan.ais.co.th
  
  If you have any questions, please see more details at https://www.facebook.com/AISDEVIO
*/
#include "SIM7020-NB-IoT-SOLDERED.h"
Magellan_SIM7020E magel;          

String payload;
const int userButton = 12;

void setup() 
{
  Serial.begin(115200);
  magel.begin();               //Init Magellan LIB
  pinMode(userButton,INPUT);   //User switch
}

void loop() 
{
  /*
    Example report the user button to Magellan IoT platform
  */
  String struserButton="0";
  if(!digitalRead(userButton))
  {
    struserButton="1";
  }
  payload="{\"button\":"+struserButton+"}"; //Please provide payload with json format
  magel.report(payload);                    //Report Userbutton state
}
