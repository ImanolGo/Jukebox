///////////////////////////////////////////////////////////////////
// Class controlling the Serial communication
//
//
// This code is under A Creative Commons Attribution/Share-Alike License
// http://creativecommons.org/licenses/by-sa/4.0/
// 2018, Imanol Gomez
///////////////////////////////////////////////////////////////////


#pragma once
#include "Arduino.h"
#include "FastLED.h"
#include "LoraManager.h"
#include "Config.h"

class SerialManager
{
  private:

  LoraManager* loraManager;  ///< it sends/reads the commands to/from the lora manager
 
  public:
    
    SerialManager(LoraManager* loraManager);
    
    void setup();
    void update();

    void write(uint8_t* _buffer, uint8_t bufferSize);

  private:

    void initializeSerial();
    void updateSerial();
    void updateLora();
    void sendConnected();
    void parseMessage(uint8_t* _buffer, uint8_t bufferSize);
    bool isMessage(uint8_t* _buffer, uint8_t bufferSize);
    bool isData(uint8_t* _buffer, uint8_t bufferSize);
    bool isConnection(uint8_t* _buffer, uint8_t bufferSize);
  
    bool _connected;
  
};


SerialManager::SerialManager(LoraManager* loraManager)
{
    this->loraManager=loraManager;
    _connected = false;
}

void SerialManager::setup()
{
    initializeSerial();
    //Serial.println("SerialManager::setup");
    //Serial.print("OK");
}

void SerialManager::initializeSerial()
{
    Serial.begin(115200);
    delay(500);
}


void SerialManager::update()
{
    updateSerial();
    updateLora();
}

void SerialManager::updateSerial()
{     

    uint8_t numBytes = Serial.available();
    
    if (numBytes > 0) 
    {
         //Serial.print("SerialManager::received -> ");
         //Serial.print(numBytes);
         //Serial.println(numBytes);
         //Serial.print("OK"); 
         uint8_t buf[numBytes];
         Serial.readBytes((char *) buf,numBytes);
         //Serial.print("OK");
         this->parseMessage(buf, numBytes);
    }
    
}


void SerialManager::updateLora()
{ 
    if(this->loraManager->isNewMessage()){
        this->write(this->loraManager->getBuffer(), this->loraManager->getSize());
    }
}

void SerialManager::parseMessage(uint8_t* buf, uint8_t len)
{
      if(this->isMessage(buf,len))
      {
          if(this->isConnection(buf, len)){
            this->sendConnected();
            
          }
          else if(this->isData(buf, len)){
              this->loraManager->sendMessage(buf, len);
          } 
         
      }
}


void SerialManager::sendConnected()
{
      int len = HEADER_SIZE+1;
      byte buf[len];
      buf[0] = 0x10;
      buf[1] = 0x41;
      buf[2] = 0x37;
      buf[3] = 1;
      buf[4] = 'c';
      buf[5] = 'c';
      
      Serial.write(buf, len);
      _connected = true;
}


void SerialManager::write(uint8_t* _buffer, uint8_t bufferSize)
{
    Serial.write(_buffer, bufferSize);
}

bool SerialManager::isMessage(uint8_t* _buffer, uint8_t bufferSize)
{
    if ( _buffer[0] == 0x10 && _buffer[1] == 0x41 && _buffer[2] == 0x37) 
    { 
        uint8_t data_size = _buffer[SIZE_INDEX];
        if ( (bufferSize-HEADER_SIZE) == data_size ) 
        {
           //Serial.println("SerialManager::isMessage -> true");
          return true; 
        }
    }

    //Serial.println("SerialManager::isMessage -> false");
    return false;
}


bool SerialManager::isData(uint8_t* _buffer, uint8_t bufferSize)
{
    if ( _buffer[COMMAND_INDEX] == 'd') { 
      return true;
    }

    return false;
}


bool SerialManager::isConnection(uint8_t* _buffer, uint8_t bufferSize)
{
    if ( _buffer[COMMAND_INDEX] == 'c') { 
       //Serial.println("SerialManager::isConnection -> true");
      return true;
    }

    //Serial.println("SerialManager::isConnection -> false");
    return false;
}