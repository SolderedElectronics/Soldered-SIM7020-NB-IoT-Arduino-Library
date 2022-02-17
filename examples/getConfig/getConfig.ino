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

///  This is pinout for arduino UNO, for other board configuration check boards.h file
///    |  Do not use PIN  |
///    |  9 TX            |
///    |  8 RX            |
///    |  4 EINT          |
///    |  26 power key    |
///    |  5 reset         |


#include "SIM7020-NB-IoT-SOLDERED.h"
Magellan_SIM7020E magel;          

String threshold;

void setup() 
{
  Serial.begin(115200);
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
