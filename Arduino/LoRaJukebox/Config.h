#pragma once


/*************************************************************************
 Protocol
 *************************************************************************/

#define CHANNEL_INDEX 1
#define VALUE_INDEX 2
#define COMMAND_INDEX 0

/*************************************************************************
 IO
 *************************************************************************/

#define NUM_BUTTONS   13
#define NUM_REGISTERS   3
#define NUM_OUTPUTS   3
#define DEFAULT_DEBOUNCE_MS   100 
#define DEFAULT_DOUBLETAP_MS  150
#define DEFAULT_HOLD_MS       1000
#define DEFAULT_ACTIVE_LOW    false


/*************************************************************************
 LoRa
 *************************************************************************/

//for feather m0  
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 434.0

// Ellapsed time between impulses in seconds
#define ELLAPSED_TIME_MS 2000 

/*************************************************************************
 Debug
 *************************************************************************/

//#define DEBUG 1
