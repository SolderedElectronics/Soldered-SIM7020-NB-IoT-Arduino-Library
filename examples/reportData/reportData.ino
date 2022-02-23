/**
 **************************************************
 *
 * @file        reportData.ino
 * @brief       Example for report random data to Magellan IoT Platform
 *				please use payload with json format e.g. {"Temperature":25.5,"Humidity":90.4,"Light":45}
 *				and {"Location":"13.001,100.44"} for plot the location on MAP
 *									|        |
 *								latitude  longitude 
 *
 *				and {"Lamp":0} or {"Lamp":1"} for show the Lamp status on dashboard
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

String payload;

void setup() 
{
  Serial.begin(115200);
  magel.begin();           //Init Magellan LIB
}

void loop() 
{
  /*
    Example report random temperature and humidity to Magellan IoT platform
  */
  String temperature=String(random(0,100)); //Take random number
  String humidity=String(random(0,100));  //Take random number
  
  payload="{\"temperature\":"+temperature+",\"humidity\":"+humidity+"}";  //Please provide payload with json format
  
  magel.report(payload);                                                  //Report random data to Magellan IoT platform
  delay(5000);                                                            //Delay 5 second
}
