#ifndef BSTRIKER_INCLUDED_
#define BSTRIKER_INCLUDED_


#include "controlalgo.h"
#include "commondata.h"
#include "RFComm.h"
#include "map.h"
#include "math.h"
#include "BehaviourRobot.h"

class CStrikerAction : public RobotBehaviour //----- To attack
{
private:
	float MIDDLE;
	float NEARPOS;
	float XHYSTERESIS;
	float YHYSTERESIS;
	float HALF_GOALSIZE;
	float CLEARYOFFSET;
	int *pstate;
	int which; //---- which robot we're referring to
	floatPOINT BallPos;
	float Ballspeed;
	floatPOINT finalPos;
	floatPOINT GPos;
	float GAngle;
	float GOALIESTANDX;
	float FARPOS;
	
public:
	CStrikerAction(int w, int *ps);
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