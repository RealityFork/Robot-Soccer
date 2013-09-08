#ifndef BSTRIKER_INCLUDED_
#define BSTRIKER_INCLUDED_


#include "controlalgo.h"
#include "commondata.h"
#include "RFComm.h"
#include "map.h"
#include "math.h"
#include "BehaviourRobot.h"
#include "Debug.h"

class CStrikerAction : public RobotBehaviour //----- To attack
{
private:
	float MIDDLE;
	float NEARPOS;
	float XHYSTERESIS;
	float YHYSTERESIS;
	float CLEARYOFFSET;
	floatPOINT finalPos;
	float FARPOS;
	float STRIKERSTANDX;
	float GOALX;
	
	BOOL hasBalls(floatPOINT);
	BOOL isInGoal();

public:
	CStrikerAction(int, int*);
	~CStrikerAction(){};

//  Switching Conditions/ State Transitions
//  Possible state transitions
//	S0S1, S0S2, S0S3
//	S1S2, S1S3
//	S2S3, S2S1,
//	S3S2, S3S1


	BOOL S0S1();
	BOOL S0S2();
	BOOL S0S3();
	BOOL S1S2();
	BOOL S1S3();
	BOOL S2S1();
	BOOL S2S3();
	BOOL S3S2();
	BOOL S3S1();

	// Action States
	// S0 initialisation
	//void S0() {}; // No Action for Initialisation State

	void S1(); //-- get ball 
	void S2(); //-- tackle
	void S3(); //----	Defend

	//-- Run function
	void runAction();
};

#endif