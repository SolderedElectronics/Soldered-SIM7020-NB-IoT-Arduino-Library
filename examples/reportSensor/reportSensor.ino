/**
 **************************************************
 *
 * @file        reportSensor.ino
 * @brief       Pre required install library
 *              - ClosedCube_HDC1080
 *        
 *              This is an example for DEVIO NB-DEVKIT I. That has read sensor on board and report data to Magellan IoT Platform.
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

const int lightSensorPin=A0; 
String payload;

void setup() 
{
  Serial.begin(115200); //Begin serial communication with PC using baud rate of 115200 bauds/s

  Serial.println("Analog Read");
      
  magel.begin();                                     //Init Magellan LIB
}

void loop() 
{
   /*
    Example read sensor on board and report data to Magellan IoT platform
  */
  
  String Light=String(analogRead(lightSensorPin));  //Read value from sensor
  
  payload="{\"light\":" + Light + "}";  //Please provide payload with json format
  magel.report(payload);                //Report sensor data
  delay(5000);                          //Delay 5 second
}
