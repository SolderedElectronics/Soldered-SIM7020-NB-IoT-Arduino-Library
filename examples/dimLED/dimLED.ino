/**
 **************************************************
 *
 * @file        dimLED.ino
 * @brief       This is an example for digital dimmer. That has control the LED on board from Magellan IoT Platform.
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

String dimmer_state="0";
String dimmer="0";
String payload;
const int ledPin = 9;

#ifdef ARDUINO_ESP32_DEV
ledcSetup(ledChannel, freq, resolution);
ledcAttachPin(ledPin, 0);
#endif

void setup() 
{
  Serial.begin(115200);
    
  magel.begin();            //Init Magellan LIB

  payload="{\"dimmer\":0}"; //Please provide payload with json format
  magel.report(payload);    //Initial dimmer data to Magellan 

  pinMode(ledPin, OUTPUT);
  #ifdef ARDUINO_ESP32_DEV
  const int freq = 5000;
  const int ledChannel = 0;
  const int resolution = 8;
  ledcWrite(0, 1023);
  #else
  analogWrite(ledPin,255);
  #endif
}

void loop() 
{
  /*
    Example control the LED on board from Magellan IoT Platform
  */
  dimmer_state=magel.getControl("dimmer"); //Get dimmer data from Magellan

  if(dimmer_state.indexOf("40300")==-1)   //Response data is not 40300
  {
    dimmer=dimmer_state;
  }

  Serial.print("dimmer ");
  Serial.println(dimmer);
  #ifdef ARDUINO_ESP32_DEV
  ledcWrite(0, dimmer.toInt() * 4);
  #else
  analogWrite(ledPin,255);
  #endif
}
