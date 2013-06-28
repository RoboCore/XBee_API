
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

  NOTE: the API operation of the master isn't set to
	use escape characters, because at this moment
	none of the escape characters will be sent to
	the slave (messagens include addresses and
	set/unset IO, so uses just numbers and letters)

  NOTES for versions:
	. Configure functions are general, they only change
	  the network ID, Channel and Baudrate. The only
	  difference is that Slaves are in AT mode whereas
	  Masters are in API mode. This means that version,
	  both for Slaves and Masters, do not apply to these
	  functions.
	. Version specific code must be implemented in the
	  parent code.

