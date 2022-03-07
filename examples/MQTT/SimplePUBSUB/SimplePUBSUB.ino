/**
 **************************************************
 *
 * @file        SimplePUBUSB.ino
 * @brief       This is an example for DEVIO NB-DEVKIT I.
 *
 *
 *				      product: www.solde.red/333072
 *
 * 				      Modified by soldered.com
 *
 * @author		  Device Innovation team     
 ***************************************************/

//Connection diagram for Dasduino Core(or any other ATMega328P board), 
//for other boards check boards.h file in this library
//Breakout      Arduino
//|-------------|
//VCC-----------5V
//RXD-----------4
//TXD-----------2
//PWRKEY--------5
//ADC-----------NOT CONNECTED
//UARTRI--------NOT CONNECTED
//GND-----------GND

#include "SIM7020-NB-IoT-API-SOLDERED.h"
String address    = "";               //Your IPaddress or mqtt server url
String serverPort = "";               //Your server port
String clientID   = "";               //Your client id < 120 characters
String topic      = "";               //Your topic     < 128 characters
String payload    = "HelloWorld!";    //Your payload   < 500 characters
String username   = "";               //username for mqtt server, username <= 100 characters
String password   = "";               //password for mqtt server, password <= 100 characters 
unsigned int subQoS       = 0;
unsigned int pubQoS       = 0;
unsigned int pubRetained  = 0;
unsigned int pubDuplicate = 0;


const long interval = 5000;           //time in millisecond 
unsigned long previousMillis = 0;
int cnt = 0;

AIS_SIM7020E_API nb;
void setup() {
  Serial.begin(115200); //Begin serial communication with PC using baud rate of 115200 bauds/s
  nb.begin();                   // Initialize SIM7020
  setupMQTT();                  // Initialize MQTT server
  nb.setCallback(callback);     // Set callback
  previousMillis = millis();    // Take timestamp
}
void loop() {   
  nb.MQTTresponse(); // Check if SIM7020 have response
  unsigned long currentMillis = millis(); // Take current timestamp
  if (currentMillis - previousMillis >= interval) {
        cnt++;
        connectStatus();
        nb.publish(topic,payload+String(cnt)); //Publish payload within  1000 characters.
        //QoS = 0, 1, or 2, retained = 0 or 1, dup = 0 or 1
//      nb.publish(topic, payload, pubQoS, pubRetained, pubDuplicate); 
        previousMillis = currentMillis;  
  }
}

//=========== MQTT Function ================
void setupMQTT(){
  if(!nb.connectMQTT(address,serverPort,clientID,username,password)){ 
     Serial.println("\nconnectMQTT");
  }
    nb.subscribe(topic,subQoS);// Subscribe to the topic to receive data
//  nb.unsubscribe(topic); 
}

void connectStatus()
{
    if(!nb.MQTTstatus()) //Check MQTT connection status.
    {
        if(!nb.NBstatus()) //Check NB connection status.
        {
           Serial.println("reconnectNB ");
           nb.begin();
        }
       Serial.println("reconnectMQ ");
       setupMQTT(); //Initialize MQTT 
    }   
}

//Call this function when data is received
void callback(String &topic,String &payload, String &QoS,String &retained){
  Serial.println("-------------------------------"); //Print received data
  Serial.println("# Message from Topic \""+topic+"\" : "+nb.toString(payload)); //Decode payload
  Serial.println("# QoS = "+QoS);
  if(retained.indexOf(F("1"))!=-1)
  {
    Serial.println("# Retained = "+retained);
  }
}
