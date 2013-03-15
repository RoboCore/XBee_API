#ifndef XBEE_API
#define XBEE_API

/*
	RoboCore XBee API Library
		(v1.2 - 15/03/2013)

  Library to use the XBEE in API mode
    (tested with Arduino 0022, 0023 and 1.0.1)

  Released under the Beerware licence
  
  
  NOTE: uses the Pointer List in XBeeMaster::Listen()
        (but can be changed by undefining
        USE_POINTER_LIST in <Memory.h>)
  
  NOTE: for Arduino Uno or Duamilanove, use v_1.1 because
        of SoftwareSerial library. For Mega & shield
        from RoboCore, use v_1.2 (with a regular shield
        use v_1.1)
        # v_1.1 not compatible with previous versions of
        Arduino (only 1.0.1 and later) because of the
        SoftwareSerial library
*/

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h> //for Arduino 1.0 or later
#else
#include <WProgram.h> //for Arduino 22
#endif

//verify board
#if not (defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__)) //Arduino Mega 1280 and Mega 2560
#error For Arduino Duemilanove or Uno, change _xbee to v_1.1 (with SoftwareSerial)
#endif


#include <HardwareSerial.h>
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
    boolean Listen(char** str, boolean free_str);
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
    HardwareSerial* _xbee; // (Rx, Tx) = (19,18) ~ 19200 (Serial 1 on MEGA)
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
