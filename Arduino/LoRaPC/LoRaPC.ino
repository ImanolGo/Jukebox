
 /*
  
  LoRa PC
     
 Description:
 * Reading from LoRa messages and sending to the serial port 
 * The PC receives the serial commands and acts upon them
 * 
 Software:
 * RadioHead (RH_RF9x) Library 

 Hardware:4 
* Adafruit Feather M0 RFM96 LoRa Radio 433MHz


 created 21th September 2018
 This code is under A Creative Commons Attribution/Share-Alike License http://creativecommons.org/licenses/by-sa/4.0/
   (2018) by Imanol Gómez

 */
 

#include "LoraManager.h"
#include "SerialManager.h"


LoraManager loraManager;
SerialManager serialManager(&loraManager);

unsigned long StartTime = millis();


void setup() 
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    serialManager.setup();
    loraManager.setup();

    #ifdef DEBUG
      Serial.println("LoraPC::Setup Done!!!");
    #endif

    digitalWrite(LED_BUILTIN, HIGH);
    
}

void loop() 
{
    //digitalWrite(LED_BUILTIN, LOW);
    
    loraManager.update();
    serialManager.update();

//     if(millis() - StartTime > 5000){
//        StartTime = millis();
//        Serial.print("d,");
//        Serial.print(random(26));
//        Serial.print(",");
//        Serial.print(random(4));
//        Serial.println("");
//    }
    

    //delay(10);
    //Serial.println("Loop!!!");
 
}
