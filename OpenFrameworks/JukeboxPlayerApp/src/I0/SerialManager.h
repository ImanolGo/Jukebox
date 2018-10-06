/*
 *  SerialManager.h
 *  Jukebox Player App
 *
 *  Created by Imanol Gomez on 01/10/18.
 *
 */



#pragma once

#include "ofMain.h"
#include "Manager.h"


//========================== class SerialManager =======================================
//==============================================================================
/** \class SerialManager SerialManager.h
 *    \brief class for managing the serial connection
 *    \details  It connects the Adafruit Feather M0 board to communicate color changes on the RGB LEDs.
 */


class SerialManager: public Manager
{
    static const int BAUD_RATE;
    static const int HEADER_SIZE;
    static const int DATA_SIZE;
    
    struct serial_header {
        unsigned char f1;
        unsigned char f2;
        unsigned char f3;
        unsigned char size;
        unsigned char command;
        unsigned char  channel;
    };
    
public:
    //! Constructor
    SerialManager();
    
    //! Destructor
    virtual ~SerialManager();
    
    //! setups the udp manager
    void setup();
    
    //! updates the udp manager
    void update();
    
    //void onSetColor(const ofColor& color);
    
    void sendSampleToggle(bool value);
    
    void sendRelayToggle(bool value);
    
    bool getConnected() const {return m_connected;}
    
    
private:
    
    void readSerialSettings();
    
    void setupSerial();
    
    void setupHeaders();
    
    void autoConnect();
    
    void connect(int portNum);
    
    bool checkConnection(int portNum);
    
    void sendConnection();
    
    bool receivedConnected();
    
    bool isMessage(unsigned char * buffer, int size);
    
    bool isData(unsigned char * buffer, int size);
    
    bool isConnected(unsigned char * buffer, int size);
    
    bool parseData(unsigned char * buffer, int size);
    
private:
    
    ofSerial   m_serial;
    bool       m_connected;
    
    serial_header    m_dataHeader;
    serial_header    m_connectHeader;
    
    
};


