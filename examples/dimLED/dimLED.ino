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

//Connection diagram for Dasduino Core(or any other ATMega328P board), for other boards check boards.h file in this library
//Breakout      Arduino
//|-------------|
//VCC-----------5V
//RXD-----------4
//TXD-----------2
//PWRKEY--------5
//ADC-----------NOT CONNECTED
//UARTRI--------NOT CONNECTED
//GND-----------GND

#include "SIM7020-NB-IoT-SOLDERED.h"
Magellan_SIM7020E magel;          

String dimmer_state="0";
String dimmer="0";
String payload;
const int ledPin = 9;



void setup() 
{
  Serial.begin(115200); //Begin serial communication with PC using baud rate of 115200 bauds/s
    
  magel.begin();            //Init Magellan LIB

  payload="{\"dimmer\":0}"; //Please provide payload with json format
  magel.report(payload);    //Initial dimmer data to Magellan 
  pinMode(ledPin, OUTPUT);
  
  #ifdef ARDUINO_ESP32_DEV  //If ESP32 is used, analogWrite will not work,
                            //so it is needed to define use of ESP32 or other
                            //libraries
  const int freq = 5000;    
  const int ledChannel = 0;
  const int resolution = 8;//Those are parameters for ESP32 PWM
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPin, 0);
  ledcWrite(0, 1023);
  #else
  analogWrite(ledPin,255);  //If any other than ESP32 MCU is used, analogWrite
                            //will work
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
  #ifdef ARDUINO_ESP32_DEV            //Again, ESP32 does not support analogWrite
  ledcWrite(0, dimmer.toInt() * 4);   //Convert dimmer into int datatype and set that value to PWM
  #else
  analogWrite(ledPin,dimmer.toInt());
  #endif
}
