

#include <SoftwareSerial.h>
#include <Memory.h>
#include <String_Functions.h>
#include <Hex_Strings.h>
#include "XBee_API.h"

//-------------------------------------------------------------------------------------------------
extern int __heap_start;



#define BUFFER_SIZE 100
byte buffer[BUFFER_SIZE];

//XBeeMaster xbee(2,3);
XBeeMaster xbee; //TESTE - while using Ethernet and XBee shield
ByteArray barray;

void setup(){
  Serial.begin(9600);
  xbee.Initialize(&Serial);
  
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  
  InitializeByteArray(&barray);

  Serial.print("\tAddress: ");
  Serial.println((int)&xbee, HEX);
  Serial.print("\theap start: ");
  Serial.println((int)&__heap_start, HEX);
  
  
  Serial.print("\t<Memory> ");
  if(UsingPointerList())
    Serial.println("OK");
  else
    Serial.println("no");
  Serial.println();
}


char c;
char* str;
boolean b;

void loop(){
  
  
/*
  char* s = "17 05 00 13 A2 00 40 79 1A BB FF FE 02 44 34 05";
  HexStringToByteArray(StrRemove(s, ' '), &barray);
  DisplayByteArray(Serial, &barray, true);
  xbee.AssignByteArray(barray);
  DisplayByteArray(Serial, &barray, true);
  DisplayByteArray(Serial, &xbee._barray, true);
  Serial.println(xbee.CheckSum(), HEX);
  
  xbee.CreateFrame(StrRemove(s, ' '), true);
  DisplayByteArray(Serial, &xbee._barray, true);
  
  Serial.println("Frame...");
  FreeByteArray(&xbee._barray);
  DisplayByteArray(Serial, &xbee._barray, true);
  HexStringToByteArray(StrRemove(s, ' '), &barray);
  xbee.CreateFrame(StrRemove(s, ' '), true);
  DisplayByteArray(Serial, &xbee._barray, true);
  
  Serial.println("Messages...");
  FreeByteArray(&barray);
  barray = xmessages.CreateRemoteATRequest("0013A20040791ABB","0000",USE_64_BIT_ADDRESS, D4, "05");
  DisplayByteArray(Serial, &barray, true);
  xbee.CreateFrame(barray);
  DisplayByteArray(Serial, &xbee._barray, true);


  char* teste = "ab-cd-ef gh ij kl";
  Serial.println(teste);
  Serial.println(StrRemove(teste, '-'));
  Serial.println(StrRemove(teste, ' '));
  Serial.println(StrRemove(teste, " -"));
*/
/*
  byte res = xbee.ConfigureAsSlave(19200);
  Serial.print("res: ");
  Serial.println(res);
  if(res == 1)
    digitalWrite(13, HIGH);
  DisplayByteArray(Serial, &xbee._barray, true);
  Serial.println(xbee.GetSerialNumber());
*/

//  Serial.println("---FIM---");
//  FreeByteArray(&barray);
//  while(1);
  
  c = '#';
  if(Serial.available()){
    c = Serial.read();
    
    AvailableMemory(&Serial, true);
    
    
    if(c == 'o'){ // acende
      Serial.println("Messages...");
      b = XBeeMessages::CreateRemoteATRequest(&barray, "0013A200409FAA21","0000",USE_64_BIT_ADDRESS, D1, "05"); // 0013A20040791ABB
//      DisplayByteArray(&Serial, &barray, true);
      xbee.CreateFrame(&barray);
//      DisplayByteArray(Serial, &xbee._barray, true);
      
      //SEND
      Serial.println("Sending...");
      xbee.Send();
      Serial.println("Sent!");
      
      xbee.Listen(&str, true);
//      b = XBeeMessages::ResponseOK(API_REMOTE_AT_COMMAND_REQUEST, str);
      HexStringToByteArray(str, &barray);
      b = XBeeMessages::ResponseOK(API_REMOTE_AT_COMMAND_REQUEST, &barray);
      if(b !=  true)
        Serial.println("ERROR");
      else
        Serial.println("OK");
      Serial.println("--- end ---");
      FreeByteArray(&barray);
      
    } else if(c == 'f'){ // apaga
      Serial.println("Messages...");
      b = XBeeMessages::CreateRemoteATRequest(&barray, "0013A200409FAA21","0000",USE_64_BIT_ADDRESS, D1, "04"); // 0013A20040791ABB
//      DisplayByteArray(&Serial, &barray, true);
      xbee.CreateFrame(&barray);
//      DisplayByteArray(Serial, &xbee._barray, true);
      
      //SEND
      Serial.println("Sending...");
      xbee.Send();
      Serial.println("Sent!");
      
      xbee.Listen(&str, true);
//      b = XBeeMessages::ResponseOK(API_REMOTE_AT_COMMAND_REQUEST, str);
      HexStringToByteArray(str, &barray);
      b = XBeeMessages::ResponseOK(API_REMOTE_AT_COMMAND_REQUEST, &barray);
      if(b !=  true)
        Serial.println("ERROR");
      else
        Serial.println("OK");
      Serial.println("--- end ---");
      FreeByteArray(&barray);
    } else if(c == 'm'){ //configura como mestre
      Serial.println(xbee.ConfigureAsMaster(19200));
    } else if(c == 's'){ //configura como escravo
      Serial.println(xbee.ConfigureAsSlave(19200));
    } else if(c == 'p'){ //print PointerList
      PointerList::DisplayList(&Serial);
    }
  }
  
}

