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
