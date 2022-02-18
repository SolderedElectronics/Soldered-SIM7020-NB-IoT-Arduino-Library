/**
 **************************************************
 *
 * @file        powerSavingMode.ino
 * @brief       Pre required install library
 * 
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
#define TIME_MICRO_SECONDS 1000000ULL  // Conversion factor for micro seconds to seconds 
#define TIME_SLEEP  90                 // Set a minimum of 60 Seconds 

Magellan_SIM7020E magel;          
RTC_DATA_ATTR int Count = 0;           // Save data on the RTC memory

const int lightSensorPin=34; 
String payload;

void setup() 
{
  Serial.begin(115200);

  Serial.println("Analog read");
      
  magel.begin();                                                      // Init Magellan LIB
  esp_sleep_enable_timer_wakeup(TIME_SLEEP * TIME_MICRO_SECONDS);     // Set to wake up after the next 100 Seconds
  if(Count == 0)
     Serial.println("Run this only the first time");
  else
     Serial.println("Deep Sleep Mode : Off  ");
}
void loop() 
{
  /*
    Example read sensor on board and report data to Magellan IoT platform
  */
  for(int i = 1 ; i <= 5 ; i++){
	int read = analogRead(A0);
    payload="{\"Analog read: \":" + read + "}";  // Please provide payload with json format
    magel.report(payload);                                                                      // Report sensor data
    delay(5000);                                                                                // Delay 5 second
  }
  Count++;
  Serial.println("Round : "+String(Count));
  Serial.println("Deep Sleep Mode : On ");
  magel.powerSavingMode(1);                                                                     // Set powerSavingMode : 0 turn off, 1 turn on 
  esp_deep_sleep_start();                                                                       // Start Deep Sleep Mode                                      
}
