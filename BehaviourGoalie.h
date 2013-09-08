#ifndef BGOALIE_INCLUDED_
#define BGOALIE_INCLUDED_

#include "StdAfx.h"
#include "controlalgo.h"
#include "commondata.h"
#include "RFComm.h"
#include "map.h"
#include "math.h"
#include "BehaviourRobot.h"


class CGoalieAction : public RobotBehaviour //----- To defend the goal from attack by opponent
{
//  Has four states S0, S1, S2, S3
//	S0	initialisation
//	S1	clear ball
//	S2	track ball's y position + predict shot
//	S3	Idle in the centre of the goal

private:
	float MIDDLE;
	float NEARPOS;
	float XHYSTERESIS;
	float YHYSTERESIS;
	float CLEARYOFFSET;
	floatPOINT finalPos;
	float GOALIESTANDX;

public:
	CGoalieAction(int, int*);
	~CGoalieAction();

//  Switching Conditions/ State Transitions
//  Possible state transitions
//	S0S1, S0S2, S0S3
//	S1S2,
//	S2S3, S2S1,
//	S3S2

	BOOL S0S1();
	BOOL S0S2();
	BOOL S0S3();
	BOOL S1S2();
	BOOL S2S1();
	BOOL S2S3();
	BOOL S3S2();

	void S1(); //-- clear the ball 
	void S2(); //-- track ball y position + predict shot
	void S3(); //----	Follow the ball's current Y position

	//-- Run function
	void runAction(); // Override
};	//-- CGoalieAction class definition ends here
#endif