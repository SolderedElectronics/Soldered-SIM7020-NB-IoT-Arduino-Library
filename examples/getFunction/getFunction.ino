/**
 **************************************************
 *
 * @file        getFunction.ino
 * @brief       This is an example for DEVIO NB-DEVKIT I.
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

void setup() {
  Serial.begin(115200);
  magel.begin();           //Init Magellan LIB
}

void loop() {
  Serial.println("---------- Clock ------------"); // Date,Time
  dateTime timeClock = magel.getClock();
  Serial.println("date : "+timeClock.date);
  Serial.println("time : "+timeClock.time);
  Serial.println("------------ End ------------");
  delay(1000);
  Serial.println("---------- Radio ------------"); // Radio Network State
  radio radioStat = magel.getRadioStat();
  Serial.println("pci : "+radioStat.pci);
  Serial.println("rsrq : "+radioStat.rsrq);
  Serial.println("rsrp : "+radioStat.rsrp);
  Serial.println("snr : "+radioStat.snr);
  Serial.println("------------ End ------------");
  delay(1000);
  Serial.println("---------- Signal -----------"); // Signal Quality Report 
  Serial.println("Signal : "+magel.getSignal());
  Serial.println("------------ End ------------");
  delay(1000);
  Serial.println("----------- Ping ------------"); // Test IP Network Connectivity to A Remote Host
  String address  = "8.8.8.8"; 
  pingRESP pingIP = magel.pingIP(address);
  Serial.print("Status : ");
  Serial.println(pingIP.status);
  Serial.println("Addr : "+pingIP.addr);
  Serial.println("ttl : "+pingIP.ttl);
  Serial.println("rtt : "+pingIP.rtt);
  Serial.println("------------ End ------------");
  delay(1000);
}
