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
  String temperature=String(random(0,100));
  String humidity=String(random(0,100));
  
  payload="{\"temperature\":"+temperature+",\"humidity\":"+humidity+"}";  //Please provide payload with json format
  
  magel.report(payload);                                                  //Report random data to Magellan IoT platform
  delay(5000);                                                            //Delay 5 second
}