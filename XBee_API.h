#ifndef XBEE_API
#define XBEE_API

/*
	RoboCore XBee API Library
		(v1.0 - 18/02/2013)

  Library to use the XBEE in API mode

  Released under the Beerware licence
*/

#include <Arduino.h> //for Arduino 1.0 and later
#include <SoftwareSerial.h>
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
    XBeeMaster(byte pinRx, byte pinTx);
    ~XBeeMaster();
    boolean AssignByteArray(ByteArray* barray);
    byte ConfigureAsMaster(long baudrate);
    byte ConfigureAsSlave(long baudrate);
    boolean CreateFrame(char* message, boolean is_hex);
    boolean CreateFrame(ByteArray* message);
    void Destroy();
    char* GetSerialNumber();
    void Initialize();
    void Initialize(HardwareSerial* computer);
    boolean Listen(char** str, boolean free_str);
    boolean Send();
    boolean SetComputer(HardwareSerial* computer);
    void UnsetComputer();
    
  private:
    boolean _initialized;
    boolean _is_SerialNumber;
    boolean _use_computer;
    ByteArray _barray;
    byte _xbeePins[2]; //{Rx, Tx}
    HardwareSerial* _computer; // (Rx, Tx) = (0,1) ~ 9600
    SoftwareSerial _xbee; // (Rx, Tx) = (2,3) ~ 19200
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
