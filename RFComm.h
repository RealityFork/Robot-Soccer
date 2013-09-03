//-- Filename : RFComm.h
//-- Functions for RF communication

#if !defined (RFCOMM_INCLUDED_)
#define RFCOMM_INCLUDED_

#include "StdAfx.h"
#include "commondata.h"
#include "mmsystem.h"
#include "vision.h"


enum comports {COM1, COM2};

//-- robot IDs and Header
#define ROBOT1ID	0x33
	//0x33
	//0x01
	//-- Defender
#define ROBOT2ID	0x36
	//0x36
	//0x02
	//-- Striker
#define GOALIEID	0x63
	//0x63
	//0x03	
	//-- Goalie
#define HEADER		0x55
	//-- Header for transmission packet


//-- Function prototypes --------------------------------
void initPacket();
void openSerialPort();
void closeSerialPort();
void SendPacket();


#endif	//-- RFCOMM_INCLUDED_