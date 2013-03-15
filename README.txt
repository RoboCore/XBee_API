
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

  NOTE: the API operation of the master isn't set to
	use escape characters, because at this moment
	none of the escape characters will be sent to
	the slave (messagens include addresses and
	set/unset IO, so uses just numbers and letters)




