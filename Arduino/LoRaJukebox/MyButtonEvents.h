/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
Written by Edward Wright (fasteddy@thewrightspace.net)
Utilizes the Bounce2 library (https://github.com/thomasfredericks/Bounce2) by Thomas O Fredericks (tof@t-o-f.info)
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef MyButtonEvents_h
#define MyButtonEvents_h

#include "MyBounce2.h" // use Thomas Fredericks' button debounce library


// enumerations to keep things readable
enum ButtonState { idle, pressed, released };
enum ButtonEvent { none, tap, doubleTap, hold };

class ButtonEvents {
  public:
    // public methods...
    ButtonEvents();
    ButtonEvents(int buttonID); // default constructor - follows the argument-free Bounce2 convention.  Use defaults, or set explicitly later
    void attach(SX1509* io, int pin); // passthru to Bounce2 attach() method
    void attach(SX1509* io, int pin, int mode); // passthru to Bounce2 attach() overload
    void activeHigh(); // set button mode to active high
    void activeLow(); // set button mode to active low
    void debounceTime(unsigned int debounce_ms); // alias/passthru to Bounce2 interval() method
    void doubleTapTime(unsigned int doubleTap_ms); // method for setting the doubleTap event detection window
    void holdTime(unsigned int hold_ms); // method for setting the time required to trigger a hold event
    void interval(unsigned int interval_ms); // passthru to Bounce2 interval() method
    bool update(); // calls the Bounce2 update() method, then runs button event detection logic
    void reset(); // resets the saved button state to idle
    void retime(); // sets the button event timestamp to the current value of millis()
    ButtonEvent event(); // returns the button event detected during update() call
    bool tapped(); // returns true if the 'tap' event was detected 
    bool doubleTapped(); // returns true if the 'doubleTap' event was detected
    bool held(); // returns true if the 'held' event was detected
    bool read(); // passthru to Bounce2 read() method;
    bool fell(); // passthru to Bounce2 fell() method;
    bool rose(); // passthru to Bounce2 rose() method;
    int getButtonID() {return buttonID;}
		
  private:
    // private instance variables...
    unsigned long eventTime_ms; // remember when the button was pressed/released
    unsigned int doubleTapTime_ms; // how long to wait for a double tap after the initial button release 
    unsigned int holdTime_ms; // how long the button must be held to generate a hold event
    ButtonState buttonState; // current button state
    ButtonEvent buttonEvent; // detected button event
    bool isActiveLow;
    Bounce debouncedButton; // button debounced using Thomas Fredericks' Bounce2 library
    
    // private methods...
    bool buttonPressed(); // returns true if the button was pressed (accounts for active high/low)
    bool buttonReleased(); // returns true if the button was released (accounts for active high/low)
    int buttonID;
};


#endif

