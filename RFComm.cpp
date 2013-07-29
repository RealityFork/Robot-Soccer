//-- Filename : RFComm.cpp
//-- Contains the implementation of routines required for
//-- RF Communication

#include "StdAfx.h"
#include "RFComm.h"
#include "commondata.h"
#include "mmsystem.h"
#include "vision.h"

DCB dcb = {0};

//-- initialise communication packet
void initPacket()
{
	//-- initialise current packet
	globaldata.packet[0] = HEADER;
	globaldata.packet[1] = GOALIEID;
	globaldata.packet[2] = 0x00;
	globaldata.packet[3] = 0x00;
	globaldata.packet[4] = HEADER;
	globaldata.packet[5] = ROBOT1ID;
	globaldata.packet[6] = 0x00;
	globaldata.packet[7] = 0x00;
	globaldata.packet[8] = HEADER;
	globaldata.packet[9] = ROBOT2ID;
	globaldata.packet[10] = 0x00;
	globaldata.packet[11] = 0x00;

	//-- Manchester encoded packet
	globaldata.encodedPacket[0]  = HEADER;
	globaldata.encodedPacket[1]  = GOALIEID;

	globaldata.encodedPacket[6]  = HEADER;
	globaldata.encodedPacket[7]  = ROBOT1ID;

	globaldata.encodedPacket[12] = HEADER;
	globaldata.encodedPacket[13] = ROBOT2ID;

	return;
}

//-- Open & Initialise the communication port
void openSerialPort()
{
	if (globaldata.comport == COM1)
	{
		globaldata.hcomport=CreateFile("COM1",
						                GENERIC_WRITE,
										0,
										0,
										OPEN_EXISTING,
										FILE_ATTRIBUTE_NORMAL,
									  0);
	}
	else	//-- communication port is COM2
	{
		globaldata.hcomport=CreateFile("COM2",
						                GENERIC_WRITE,
										0,
										0,
										OPEN_EXISTING,
										FILE_ATTRIBUTE_NORMAL,
									  0);
	}

    if(globaldata.hcomport==INVALID_HANDLE_VALUE)
      AfxMessageBox("Error Opening COM port...");

    dcb.DCBlength         = sizeof(dcb);
	dcb.BaudRate          = 38400;	//-- bits per sec
    dcb.ByteSize          = 8;
    dcb.Parity            = 0;	//-- no parity
    dcb.StopBits          = 0;	//-- 1 stop bit
    dcb.EvtChar           = '\0';
    dcb.fDtrControl       = DTR_CONTROL_ENABLE;
    //dcb.fRtsControl       = RTS_CONTROL_TOGGLE;	//ENABLE;
	dcb.fRtsControl       = RTS_CONTROL_ENABLE;
    dcb.fOutxCtsFlow      = FALSE;
    dcb.fOutxDsrFlow      = FALSE;
    dcb.fDsrSensitivity   = FALSE;
    dcb.fOutX             = FALSE;
    dcb.fInX              = FALSE;
    //dcb.fTXContinueOnXoff = TRUE;	//FALSE;
	dcb.fTXContinueOnXoff = FALSE;
    dcb.fParity           = FALSE;	//-- disable parity checking

	if (!SetCommState(globaldata.hcomport, &dcb))
        AfxMessageBox("Error setting COM port...");
	return;
}

void closeSerialPort()
{
	if (!CloseHandle(globaldata.hcomport))
		AfxMessageBox("Error closing COM port...");
	return;
}

//-- Send a packet to the robots
void SendPacket()
{
	DWORD dwWritten;

	char ffheader = (char) 0xff;
	char header01 = (char) 0x01;

	char temp1, temp2;

	//-- Goalie
	temp1 = globaldata.packet[2] & 0xAA;	//-- Vl of Goalie
	temp2 = ( ~(temp1>>1) ) & 0x55;
	globaldata.encodedPacket[2] = temp1 | temp2;

	temp1 = globaldata.packet[2] & 0x55;	//-- Vl of Goalie
	temp2 = ( ~(temp1<<1) ) & 0xAA;
	globaldata.encodedPacket[3] = temp1 | temp2;

	temp1 = globaldata.packet[3] & 0xAA;	//-- Vr of Goalie
	temp2 = ( ~(temp1>>1) ) & 0x55;
	globaldata.encodedPacket[4] = temp1 | temp2;

	temp1 = globaldata.packet[3] & 0x55;	//-- Vr of Goalie
	temp2 = ( ~(temp1<<1) ) & 0xAA;
	globaldata.encodedPacket[5] = temp1 | temp2;


	//-- Robot1
	temp1 = globaldata.packet[6] & 0xAA;	//-- Vl of Robot1
	temp2 = ( ~(temp1>>1) ) & 0x55;
	globaldata.encodedPacket[8] = temp1 | temp2;

	temp1 = globaldata.packet[6] & 0x55;	//-- Vl of Robot1
	temp2 = ( ~(temp1<<1) ) & 0xAA;
	globaldata.encodedPacket[9] = temp1 | temp2;

	temp1 = globaldata.packet[7] & 0xAA;	//-- Vr of Robot1
	temp2 = ( ~(temp1>>1) ) & 0x55;
	globaldata.encodedPacket[10] = temp1 | temp2;

	temp1 = globaldata.packet[7] & 0x55;	//-- Vr of Robot1
	temp2 = ( ~(temp1<<1) ) & 0xAA;
	globaldata.encodedPacket[11] = temp1 | temp2;

	//-- Robot2
	temp1 = globaldata.packet[10] & 0xAA;	//-- Vl of Robot2
	temp2 = ( ~(temp1>>1) ) & 0x55;
	globaldata.encodedPacket[14] = temp1 | temp2;

	temp1 = globaldata.packet[10] & 0x55;	//-- Vl of Robot2
	temp2 = ( ~(temp1<<1) ) & 0xAA;
	globaldata.encodedPacket[15] = temp1 | temp2;

	temp1 = globaldata.packet[11] & 0xAA;	//-- Vr of Robot2
	temp2 = ( ~(temp1>>1) ) & 0x55;
	globaldata.encodedPacket[16] = temp1 | temp2;

	temp1 = globaldata.packet[11] & 0x55;	//-- Vr of Robot2
	temp2 = ( ~(temp1<<1) ) & 0xAA;
	globaldata.encodedPacket[17] = temp1 | temp2;

	//-- Preamble. Keep sending 0xAA (ie binar 10101010) for 3 mSec ----
	//-- This is essential to settle the data slicer

	char aaheader = (char) 0xaa;
	DWORD present, past, diff=0;
	past = timeGetTime();	//-- get the current time
	while (diff < 3)
	{
		WriteFile(globaldata.hcomport, &aaheader, 1, &dwWritten, NULL);
		present = timeGetTime();	//-- get the current time
		diff = present - past;
	}

	//-- send 0xFF for the oscillator to lock and stabilise the UART ---
	WriteFile(globaldata.hcomport, &ffheader, 1, &dwWritten, NULL);

	//-- send 0x01 to balance the 0xFF sent earlier
	WriteFile(globaldata.hcomport, &header01, 1, &dwWritten, NULL);

	//-- send the packet ------------------
	WriteFile(globaldata.hcomport, globaldata.encodedPacket, 18, &dwWritten, NULL);

	return;
}