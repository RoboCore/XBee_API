#ifndef XBEE_API
#define XBEE_API

/*
	RoboCore XBee API Library
		(v1.3 - 23/05/2013)

  Library to use the XBEE in API mode
    (tested with Arduino 0022, 0023 and 1.0.1)

  Released under the Beerware license
  Written by François
  
  
  NOTE: uses the Pointer List in XBeeMaster::Listen()
        (but can be changed by undefining
        USE_POINTER_LIST in <Memory.h>)
  
  NOTE: this library can work with the SoftwareSerial
        library in Arduino versions 0022 and 0023, but
        is disabled by default.

  NOTES for versions:
	. Configure functions are general, they only change
	  the network ID, Channel and Baudrate. The only
	  difference is that Slaves are in AT mode whereas
	  Masters are in API mode. This means that version,
	  both for Slaves and Masters, do not apply to these
	  functions.
	. Version specific code must be implemented in the
	  parent code.
*/

//#define USE_SOFTWARE_SERIAL //comment to use the XBee in a HardwareSerial port
        // !!! the software serial sends the message, but does not listen to the response (tested with bd=19200)


#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h> //for Arduino 1.0 or later
#else
#include <WProgram.h> //for Arduino 0022 and 0023
#undef USE_SOFTWARE_SERIAL // the SoftwareSerial library is not recommended for versions before 1.0
#endif


//include the serial library
#ifdef USE_SOFTWARE_SERIAL
#include <SoftwareSerial.h>
#else
#include <HardwareSerial.h>
#endif
//include other libraries
#include <Memory.h>
#include <String_Functions.h>
#include <Hex_Strings.h> //to manipulate the messages
#include "XBee_API_ATCommands.h" //the AT commands

//--------------------------------------

// Data bytes that need to be escaped
#define FRAME_DELIMITER 0x7E
#define ESCAPE 0x7D
#define XON 0x11
#define XOFF 0x13


// API Identifiers
#define API_MODEM_STATUS 0x8A
#define API_AT_COMMAND 0x08
#define API_AT_COMMAND_QUEUE 0x09
#define API_AT_COMMAND_RESPONSE 0x88
#define API_REMOTE_AT_COMMAND_REQUEST 0x17
#define API_REMOTE_COMMAND_RESPONSE 0x97
#define API_TX_RESQUEST_64_BIT 0x00
#define API_TX_RESQUEST_16_BIT 0x01
#define API_TX_STATUS 0x89
#define API_RX_64_BIT 0x80
#define API_RX_16_BIT 0x81
#define API_RX_64_BIT_IO 0x82
#define API_RX_16_BIT_IO 0x83

// Transmission Types
#define USE_BROADCAST 0x00
#define USE_64_BIT_ADDRESS 0x01
#define USE_16_BIT_ADDRESS 0x02


class XBeeMaster{
  
  public:
    XBeeMaster(void);
#ifdef USE_SOFTWARE_SERIAL
    XBeeMaster(SoftwareSerial* xbee);
#else
    XBeeMaster(HardwareSerial* xbee);
#endif
    ~XBeeMaster(void);
    boolean AssignByteArray(ByteArray* barray);
    byte ConfigureAsMaster(long baudrate);
    byte ConfigureAsSlave(long baudrate);
    boolean CreateFrame(char* message, boolean is_hex);
    boolean CreateFrame(ByteArray* message);
    void Destroy(void);
    char* GetSerialNumber(void);
    void Initialize(void);
    void Initialize(HardwareSerial* computer);
    int Listen(char** str, boolean free_str);
    byte Restore(void);
    byte Restore(long baudrate);
    boolean Send(void);
    boolean SetComputer(HardwareSerial* computer);
    void UnsetComputer(void);
    
static long GetPCbaudrate(void);
static long GetXBeebaudrate(void);
    
  private:
    boolean _initialized;
    boolean _is_SerialNumber;
    boolean _use_computer;
    ByteArray _barray;
    HardwareSerial* _computer; // (Rx, Tx) = (0,1) ~ 9600
#ifdef USE_SOFTWARE_SERIAL
    SoftwareSerial* _xbee;
#else
    HardwareSerial* _xbee; // (Rx, Tx) = (19,18) ~ 19200 (Serial 1 on MEGA)
#endif
    byte CheckSum(ByteArray* barray_ptr);
    byte ConfigureXBee(long baudrate, boolean master);
};




class XBeeMessages{
  
  public:
    static boolean CreateRemoteATRequest(ByteArray* barray_ptr, char* destination_address_64bit, char* destination_address_16bit, byte transmission_type, char* command_name, char* command_values);
    static boolean ResponseOK(byte sent_message_type, char* response);
    static boolean ResponseOK(byte sent_message_type, ByteArray* barray);

};


#endif
