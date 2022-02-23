/**
 **************************************************
 *
 * @file        getConfig.ino
 * @brief        Example for get config data from Magellan IoT Platform
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

String threshold;

void setup() 
{
  Serial.begin(115200); //Begin serial communication with PC using baud rate of 115200 bauds/s
  magel.begin();           //Init Magellan LIB
}

void loop() 
{
  /*
    Example get config data from Magellan IoT platform
  */
  threshold = magel.getConfig("threshold"); //Get configuration data from Magellan
  Serial.print("threshold = ");
  
  if(threshold.indexOf("40300")!=-1)        //Response data is 40300
  {
    Serial.println("Device has not registered or it has not configuraton profile in Magellan Platform");
  }
  else
  {
    Serial.println(threshold);              //Config data from Magellan IoT platform
  }
  Serial.println();
}
