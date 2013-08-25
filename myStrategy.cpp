//-- Filename : myStrategy.cpp
//-- Implements strategy

#include "StdAfx.h"
#include "myStrategy.h"
#include "controlalgo.h"
#include "commondata.h"
#include "RFComm.h"
#include "map.h"
#include "math.h"

//--- used by smart targeting function
BOOL oppoArea(floatPOINT robotPos, float NEARPOS, float NEAR_Y_OFFSET)
{
	if(	robotPos.x >  Physical_X - NEARPOS 
		&& robotPos.y > Physical_Yby2 - NEAR_Y_OFFSET
		&& robotPos.y < Physical_Yby2 + NEAR_Y_OFFSET)

		return true;
	else
		return false;
}	//-- oppoArea()
//--- used by smart targeting function

BOOL ownArea(floatPOINT Pos)
{	//-- To check if Pos is in own penalty area
	float NEARPOS, NEAR_Y_OFFSET;
	floatPOINT nearpoint;
	floatPOINT homegoalbottom;

	homegoalbottom.x = (float)globaldata.homegoalbottom.x;
	homegoalbottom.y = (float)globaldata.homegoalbottom.y;
	mapxy(&homegoalbottom, &nearpoint, &globaldata);
	NEARPOS = nearpoint.x + (float)2.0;
	NEAR_Y_OFFSET = (float)fabs(nearpoint.y - Physical_Yby2) + (float)2.0;

	if(	Pos.x <  NEARPOS
		&& Pos.y > Physical_Yby2 - NEAR_Y_OFFSET
		&& Pos.y < Physical_Yby2 + NEAR_Y_OFFSET)
	{
		return true;
	}
	else
		return false;
}	//-- ownArea()

void smartTarget(floatPOINT *Targetpos)
{
	float NEARPOS, NEAR_Y_OFFSET;
	floatPOINT nearpoint;
	floatPOINT homegoalbottom;
	float GOALSIZE = 40;

	homegoalbottom.x = (float)globaldata.homegoalbottom.x;
	homegoalbottom.y = (float)globaldata.homegoalbottom.y;
	mapxy(&homegoalbottom,&nearpoint,&globaldata);
	NEARPOS = nearpoint.x;
	NEAR_Y_OFFSET = (float)fabs(nearpoint.y - Physical_Yby2);

	floatPOINT oppoGoaliepos;
	//---- dumb tracking
	 Targetpos->x = Physical_X;
	 Targetpos->y = Physical_Yby2;
	//----

	 if(gTrackOpponent)
	 {
		BOOL oppoGoalieFound = FALSE;

		if(gNumOppoRobots>0 && oppoArea(globaldata.opporobot1posS, NEARPOS, NEAR_Y_OFFSET))
		{	
			oppoGoalieFound = TRUE;
			oppoGoaliepos = globaldata.opporobot1posS;
		}
		else if(gNumOppoRobots>1 && oppoArea(globaldata.opporobot2posS, NEARPOS, NEAR_Y_OFFSET))
		{
			oppoGoalieFound = TRUE;
			oppoGoaliepos = globaldata.opporobot2posS;
		}
		else if(gNumOppoRobots>2 && oppoArea(globaldata.opporobot3posS, NEARPOS, NEAR_Y_OFFSET))
		{
			oppoGoalieFound = TRUE;
			oppoGoaliepos = globaldata.opporobot3posS;
		}

		if (oppoGoalieFound)
		{
			float GOALPOSTSHOTRATIO = 0.5; // 0 is goal keeper, 1 is goal post
			if(oppoGoaliepos.y > Physical_Yby2)
			{
				//-- Shoot to left (lower half of goal)
				Targetpos->y = Physical_Yby2 - GOALSIZE*GOALPOSTSHOTRATIO/2;	
			}
			else if(oppoGoaliepos.y < Physical_Yby2)
			{
				//-- Shoot to right (lower half of goal)
				Targetpos->y = Physical_Yby2 + GOALSIZE*GOALPOSTSHOTRATIO/2;	
			}
		}
	 }	//-- if(gTrackOpponent)
	 return;
}	//-- smartTarget()


//---- CPlaceRobots : Used for placement of robots before game starts -------
class CPlaceRobots
{
	//  Has three states S0, S1, S2
	//	S0	initialisation
	//	S1	move robots
	//	S2	end stable condition. The robots have reached the desired positions
	

private:
	int *pstate;
	//---- Desired Robot Positions
	floatPOINT GPosition;
	floatPOINT R1Position;
	floatPOINT R2Position;
	//---- Desired Robot Angles
	float Gangle;
	float R1angle;
	float R2angle;
	//---- Robot Position Errors
	float GPositionError;
	float R1PositionError;
	float R2PositionError;
	//---- Robot Angle Errors
	float GangleError;
	float R1angleError;
	float R2angleError;

	float ANGLETHRESHOLD;
	float POSITIONTHRESHOLD;
public:
	CPlaceRobots( int *ps, floatPOINT GP, floatPOINT R1P, floatPOINT R2P, float Ga, float R1a, float R2a) //-- constructor
	{ 
		pstate = ps ;  
		
		//---- Initialisations
		GPosition = GP;
		R1Position = R1P;
		R2Position = R2P;

		Gangle = Ga;
		R1angle = R1a;
		R2angle = R2a;

		float Gdx = GPosition.x - globaldata.goalieposS.x;
		float Gdy = GPosition.y - globaldata.goalieposS.y;
		GPositionError = (float)sqrt(Gdx*Gdx+Gdy*Gdy);
		GangleError = Gangle - globaldata.goalieangleS;
		while(GangleError> 180) GangleError -= 360;
		while(GangleError< -180) GangleError += 360;

		float R1dx = R1Position.x - globaldata.robot1posS.x;
		float R1dy = R1Position.y - globaldata.robot1posS.y;
		R1PositionError = (float)sqrt(R1dx*R1dx+R1dy*R1dy);
		R1angleError = R1angle - globaldata.robot1angleS;
		while(R1angleError> 180) R1angleError -= 360;
		while(R1angleError< -180) R1angleError += 360;

		float R2dx = R2Position.x - globaldata.robot2posS.x;
		float R2dy = R2Position.y - globaldata.robot2posS.y;
		R2PositionError = (float)sqrt(R2dx*R2dx+R2dy*R2dy);
		R2angleError = R2angle - globaldata.robot2angleS;
		while(R2angleError> 180) R2angleError -= 360;
		while(R2angleError< -180) R2angleError += 360;

		ANGLETHRESHOLD = 5;	//4;
		POSITIONTHRESHOLD = (float)2.5;	//1.8;
	}	//-- end of constructor
	
	~CPlaceRobots(){}	//-- destructor

	//  Switching Conditions/ State Transitions
	//  Possible state transitions
	//	S0S1, S0S2
	//	S2S1,
	//	S1S2

	BOOL S0S1()
	{
		return !S0S2();
	}

	BOOL S0S2()
	{
		if(	  ( fabs(GangleError) < ANGLETHRESHOLD || fabs(180 - GangleError) < ANGLETHRESHOLD || fabs(180 + GangleError) < ANGLETHRESHOLD)
			&& (fabs(R1angleError) < ANGLETHRESHOLD  || fabs(180 - R1angleError) < ANGLETHRESHOLD  || fabs(180 + R1angleError) < ANGLETHRESHOLD)
			&& (fabs(R2angleError) < ANGLETHRESHOLD || fabs(180 - R2angleError) < ANGLETHRESHOLD  || fabs(180 + R2angleError) < ANGLETHRESHOLD)
			&& fabs(GPositionError) < POSITIONTHRESHOLD 
			&& fabs(R1PositionError) < POSITIONTHRESHOLD 
			&& fabs(R2PositionError) < POSITIONTHRESHOLD )
			return true;
		else
			return false;

	}

	BOOL S2S1()
	{	//-- once in this state, never go to any other state.
		//-- this is the final stable state
		return false;
	}

	BOOL S1S2()
	{
		return S0S2();
	}
	
	//--  Action States
	//--  S0	initialisation
	//--  void S0() {} //---- No Action for Initialisation State

	//---- S1 move robots in position
	void S1() 
	{
		//---- Action that is required
		position(HGOALIE, GPosition, Gangle, 0);
		position(HROBOT1, R1Position, R1angle, 0);
		position(HROBOT2, R2Position, R2angle, 0);
	}

	//----	S2	robots are in final desired positions
	void S2() 
	{
		//---- Action that is required - Stop the robots
		velocity(HGOALIE, 0, 0);
		velocity(HROBOT1, 0, 0);
		velocity(HROBOT2, 0, 0);
	}

	//---- Run function
	void runAction()
	{
		switch(*pstate)
		{
		case 0://---- S0 initialisation
			if( S0S1() ) { S1(); *pstate = 1;}
			else if( S0S2() ) { S2(); *pstate = 2;}
			else 
			{
				//-- Give error alert message;
			}
			break;
		case 1: //---- S1 move robots in position
			if( S1S2() ) { S2(); *pstate = 2;}
			else S1();
			break;
		case 2: //---- S2 robots in position
			if( S2S1() ) { S1(); *pstate = 1;}
			else S2();
			break;
		default: //---- Give error alert message
			break;
		}
		return;
	}

};	//-- CPlaceRobots class definition ends here


class CGoalieAction //----- To defend the goal from attack by opponent
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


	
public:
	CGoalieAction(int w, int *ps)
	{ 
		floatPOINT nearpoint;
		floatPOINT homegoalbottom;
		pstate = ps ;  
		which = w;
		MIDDLE = Physical_Xby2;
		homegoalbottom.x = (float)globaldata.homegoalbottom.x;
		homegoalbottom.y = (float)globaldata.homegoalbottom.y;
		mapxy(&homegoalbottom,&nearpoint,&globaldata);
		XHYSTERESIS = 3.0;
		YHYSTERESIS = 2.0;
		NEARPOS = nearpoint.x + XHYSTERESIS;
		float Balldx=globaldata.ballvelS.x;
		float Balldy=globaldata.ballvelS.y;


		BallPos = globaldata.GballposS;
		Ballspeed = (float)sqrt(Balldx*Balldx + Balldy*Balldy);

		switch(gGoalieActionParameters.GBehaviour)
		{
		case 0://---- Conservative
			CLEARYOFFSET = (float)fabs(Physical_Yby2 - nearpoint.y);
			break;
		case 1://---- Normal
			CLEARYOFFSET = (float)fabs(Physical_Yby2 - nearpoint.y/2);
			break;
		case 2://---- Aggressive
			CLEARYOFFSET = Physical_Yby2;
			break;
		}

		GAngle = globaldata.goalieangleS;

		GOALIESTANDX = nearpoint.x/2 + 5;// - gGoalieActionParameters.GXcompensation;
	}
	~CGoalieAction(){}

//  Switching Conditions/ State Transitions
//  Possible state transitions
//	S0S1, S0S2, S0S3
//	S1S2,
//	S2S3, S2S1,
//	S3S2


	BOOL S0S1()
	{ //---- ball in goal area
		if ((BallPos.x <= NEARPOS)
			&& (BallPos.y < (Physical_Yby2 + CLEARYOFFSET)) 
			&& (BallPos.y > (Physical_Yby2 - CLEARYOFFSET)) )//ball in near
			return true;
		else
			return false;
	}

	BOOL S0S2()
	{//---- ball in middle (outside goal area but inside centre half line)
		if((!S0S1()) && (BallPos.x < MIDDLE))
			return true;
		else
			return false;
	}

	BOOL S0S3()
	{//---- ball moves beyond centre line
		if(BallPos.x >= MIDDLE)
			return true;
		else
			return false;
	}

	BOOL S1S2()
	{//-- ball moves from goal area to middle
		if (BallPos.x > NEARPOS + XHYSTERESIS ||
			(BallPos.x < NEARPOS + XHYSTERESIS &&(
			(BallPos.y > Physical_Yby2 + CLEARYOFFSET + YHYSTERESIS)
			|| (BallPos.y < Physical_Yby2 - CLEARYOFFSET - YHYSTERESIS) ) ))
			return true;
		else
			return false;
	}

	BOOL S2S1()
	{//---- ball moves from middle to goal area
		if ((BallPos.x <= NEARPOS)
			&& (BallPos.y < (Physical_Yby2 + CLEARYOFFSET))
			&& (BallPos.y > (Physical_Yby2 - CLEARYOFFSET)) )//ball in near
			return true;
		else
			return false;
	}

	BOOL S2S3()
	{//---- ball moves from middle to far
	
		if(BallPos.x >= MIDDLE + XHYSTERESIS)
			return true;
		else
			return false;
	}

	BOOL S3S2()
	{//---- ball moves from far to middle

		if(BallPos.x <= MIDDLE - XHYSTERESIS)
			return true;
		else
			return false;
	}

	// Action States
	// S0 initialisation
	//void S0() {}; // No Action for Initialisation State

	void S1() //-- clear the ball 
	{
		float FINALVELOCITY = (float)10;

		positionG(BallPos, 90, FINALVELOCITY);
		avoidBound(which,BallPos);
		escapeGoal(which);
		
	}

	void S2()	//-- track ball y position + predict shot
	{	
		//-- calculate final position for the goalkeeper
		finalPos.x = GOALIESTANDX;

		// Take a ball velocity sample
		globaldata.ballVelSamples[globaldata.ballVelIndex].x = globaldata.ballvel.x;
		globaldata.ballVelSamples[globaldata.ballVelIndex].y = globaldata.ballvel.y;
		globaldata.ballAngleAve = globaldata.ballVelIndex;

		globaldata.ballVelIndex = (globaldata.ballVelIndex+1) % ballVelNSamples;
		floatPOINT ballVelAve;
		ballVelAve.x = 0;
		ballVelAve.y = 0;

		// Sum x and y samples
		for (int i = 0; i < ballVelNSamples; i++)
		{
			ballVelAve.x += globaldata.ballVelSamples[i].x;
			ballVelAve.y += globaldata.ballVelSamples[i].y;
		}

		
		float ballAngleActual = (float)atan2(ballVelAve.y, ballVelAve.x)*180/PI;
		
		float ballAngle = 0;
		if(ballAngleActual > 90)//90 to 180
			ballAngle = ballAngleActual - 90;
		else if(ballAngleActual > 0)//0 to 90
			ballAngle = 90;
		else if(ballAngleActual < -90)//-90 to -180
			ballAngle = ballAngleActual + 90;
		else //0 to -90
		ballAngle = 90;
		

		// Predict the final Y position of the ball.
		finalPos.y = (BallPos.y - ((BallPos.x - finalPos.x)/tan(ballAngle * 3.14159265 / 180.0)));

		// Set hard limits for this state
		if (finalPos.y > Physical_Yby2 + (Physical_Yby2/3.5))
			finalPos.y = Physical_Yby2 + (Physical_Yby2/2.5);	
		if (finalPos.y < Physical_Yby2 - (Physical_Yby2/3.5))
			finalPos.y = Physical_Yby2 - (Physical_Yby2/3.5);

		// Convert predicted co ords back to screen co ords for display:
		inversemapxy(&globaldata.predicted,&finalPos,&globaldata);

		positionG(finalPos, 90, 0);
		avoidBound(which,finalPos);
		escapeGoal(which);
	}

	void S3()//----	Follow the ball's current Y position
	{
		floatPOINT finalPos;
		finalPos.x = GOALIESTANDX;
		finalPos.y = BallPos.y;

		// Hard limits
		if (finalPos.y > Physical_Yby2 + (Physical_Yby2/3.5))
			finalPos.y = Physical_Yby2 + (Physical_Yby2/3.5);	
		if (finalPos.y < Physical_Yby2 - (Physical_Yby2/3.5))
			finalPos.y = Physical_Yby2 - (Physical_Yby2/3.5);

		globaldata.predicted = finalPos;

		positionG(finalPos, 90, 0);
		avoidBound(which,finalPos);
		escapeGoal(which);
	}

	//-- Run function
	void runAction()
	{
		switch(*pstate)
		{
		case 0://-- S0 (initialisation)
			if( S0S1() ) { S1(); *pstate = 1;}		//-- move to state S1
			else if( S0S2() ) { S2(); *pstate = 2;}	//-- move to state S2
			else if( S0S3() ) { S3(); *pstate = 3;}	//-- move to state S3
			else 
			{
			// Give error alert message;
				MessageBox( NULL, TEXT("State transtition error"), TEXT("Error"), MB_OK );
			}
			break;

		case 1://-- S1 (clear ball)
			if( S1S2() ) {S2(); *pstate = 2;}		//-- move to state S2
			else S1();					//-- continue to stay in state S1
			break;

		case 2://-- S2 (track ball y position + predict shot
			if( S2S3() ) { S3(); *pstate = 3;}		//-- move to state S3
			else if( S2S1() ) {S1();  *pstate = 1;}	//-- move to state S1
			else S2();					//-- continue to stay in state S2
			break;

		case 3://-- S3 (Idle in the centre of goal)
			if( S3S2() ) {S2(); *pstate = 2;}		//-- move to state S2
			else S3();					//-- continue to stay in state S3
			break;

		default: // Give error alert message
			MessageBox( NULL, TEXT("State transtition error"), TEXT("Error"), MB_OK );
			break;
		}
		return;
	}

};	//-- CGoalieAction class definition ends here

class CStrikerAction //----- To attack
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
	CStrikerAction(int w, int *ps)
	{ 
		floatPOINT nearpoint;
		floatPOINT homegoalbottom, oppgoalbottom;
		pstate = ps ;  
		which = w;
		MIDDLE = Physical_Xby2;
		homegoalbottom.x = (float)globaldata.homegoalbottom.x;
		homegoalbottom.y = (float)globaldata.homegoalbottom.y;
		mapxy(&homegoalbottom,&nearpoint,&globaldata);
		XHYSTERESIS = 3.0;
		YHYSTERESIS = 2.0;
		NEARPOS = nearpoint.x + XHYSTERESIS;
		oppgoalbottom.x = (float)globaldata.oppgoalbottom.x;
		oppgoalbottom.y = (float)globaldata.oppgoalbottom.y;
		mapxy(&oppgoalbottom, &nearpoint, &globaldata);
		FARPOS = nearpoint.x;
		float Balldx=globaldata.ballvelS.x;
		float Balldy=globaldata.ballvelS.y;


		BallPos = globaldata.GballposS;
		Ballspeed = (float)sqrt(Balldx*Balldx + Balldy*Balldy);


		GAngle = globaldata.goalieangleS;

	}
	~CStrikerAction(){}

//  Switching Conditions/ State Transitions
//  Possible state transitions
//	S0S1, S0S2, S0S3
//	S1S2, S1S3
//	S2S3, S2S1,
//	S3S2, S3S1


	BOOL S0S1()
	{

			return true;
	}

	BOOL S0S2()
	{

			return false;
	}

	BOOL S0S3()
	{

			return false;
	}

	BOOL S1S2()
	{

			return S0S2();
	}
	BOOL S1S3()
	{

			return S0S3();
	}

	BOOL S2S1()
	{

			return S0S1();
	}

	BOOL S2S3()
	{

			return S0S3();
	}

	BOOL S3S2()
	{

			return S0S2();
	}
	BOOL S3S1()
	{

			return S0S1();
	}

	// Action States
	// S0 initialisation
	//void S0() {}; // No Action for Initialisation State

	void S1() //-- get ball 
	{
		floatPOINT goalTarget;
		goalTarget.x = FARPOS;
		goalTarget.y = Physical_Yby2;


		myShoot(which, &goalTarget);
	}

	void S2()	//-- tackle
	{	
		
	}

	void S3()//----	Defend
	{

	}

	//-- Run function
	void runAction()
	{
		switch(*pstate)
		{
		case 0://-- S0 (initialisation)
			if( S0S1() ) { S1(); *pstate = 1;}		//-- move to state S1
			else if( S0S2() ) { S2(); *pstate = 2;}	//-- move to state S2
			else if( S0S3() ) { S3(); *pstate = 3;}	//-- move to state S3
			else 
			{
			// Give error alert message;
				MessageBox( NULL, TEXT("State transtition error"), TEXT("Error"), MB_OK );
			}
			break;

		case 1://-- S1
			if( S1S2() ) {S2(); *pstate = 2;}		//-- move to state S2
			else if( S1S3() ) { S3(); *pstate = 3;}	//-- move to state S3
			else S1();					//-- continue to stay in state S1
			break;

		case 2://-- S2
			if( S2S3() ) { S3(); *pstate = 3;}		//-- move to state S3
			else if( S2S1() ) {S1();  *pstate = 1;}	//-- move to state S1
			else S2();					//-- continue to stay in state S2
			break;

		case 3://-- S3
			if( S3S2() ) {S2(); *pstate = 2;}		//-- move to state S2
			else if( S3S1() ) {S1();  *pstate = 1;}	//-- move to state S1
			else S3();					//-- continue to stay in state S3
			break;

		default: // Give error alert message
			MessageBox( NULL, TEXT("State transtition error"), TEXT("Error"), MB_OK );
			break;
		}
		return;
	}

};	//-- CStrikerAction class definition ends here


class CDefenderAction //----- To defend the goal from attack by opponent
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


	
public:
	CDefenderAction(int w, int *ps)
	{ 
		floatPOINT nearpoint;
		floatPOINT homegoalbottom;
		pstate = ps ;  
		which = w;
		MIDDLE = Physical_Xby2;
		homegoalbottom.x = (float)globaldata.homegoalbottom.x;
		homegoalbottom.y = (float)globaldata.homegoalbottom.y;
		mapxy(&homegoalbottom,&nearpoint,&globaldata);
		XHYSTERESIS = 3.0;
		YHYSTERESIS = 2.0;
		NEARPOS = nearpoint.x + XHYSTERESIS;
		float Balldx=globaldata.ballvelS.x;
		float Balldy=globaldata.ballvelS.y;


		BallPos = globaldata.GballposS;
		Ballspeed = (float)sqrt(Balldx*Balldx + Balldy*Balldy);


		GAngle = globaldata.goalieangleS;

	}
	~CDefenderAction(){}

//  Switching Conditions/ State Transitions
//  Possible state transitions
//	S0S1, S0S2, S0S3, S0S4
//	S1S2, S1S3, S1S4
//	S2S3, S2S1, S2S4
//	S3S2, S3S1, S3S4


	BOOL S0S1()
	{

			return true;
	}

	BOOL S0S2()
	{

			return false;
	}

	BOOL S0S3()
	{

			return false;
	}
	BOOL S0S4()
	{

			return false;
	}

	BOOL S1S2()
	{

			return S0S2();
	}
	BOOL S1S3()
	{

			return S0S3();
	}
	BOOL S1S4()
	{

			return S0S4();
	}

	BOOL S2S1()
	{

			return S0S1();
	}

	BOOL S2S3()
	{

			return S0S3();
	}
	BOOL S2S4()
	{

			return S0S4();
	}

	BOOL S3S1()
	{

			return S0S1();
	}
	BOOL S3S2()
	{

			return S0S2();
	}
	
	BOOL S3S4()
	{

			return S0S4();
	}
	BOOL S4S1()
	{

			return S0S1();
	}
	BOOL S4S2()
	{

			return S0S2();
	}

	BOOL S4S3()
	{

			return S0S3();
	}

	// Action States
	// S0 initialisation
	//void S0() {}; // No Action for Initialisation State

	void S1() //-- Track like goalie
	{
		
	}

	void S2()	//-- tackle
	{	
		
	}

	void S3()//----	Clear
	{

	}
	void S4()//----	Assist
	{

	}

	//-- Run function
	void runAction()
	{
		switch(*pstate)
		{
		case 0://-- S0 (initialisation)
			if( S0S1() ) { S1(); *pstate = 1;}		//-- move to state S1
			else if( S0S2() ) { S2(); *pstate = 2;}	//-- move to state S2
			else if( S0S3() ) { S3(); *pstate = 3;}	//-- move to state S3
			else if( S0S4() ) { S4(); *pstate = 4;}	//-- move to state S4
			else 
			{
			// Give error alert message;
				MessageBox( NULL, TEXT("State transtition error"), TEXT("Error"), MB_OK );
			}
			break;

		case 1://-- S1
			if( S1S2() ) {S2(); *pstate = 2;}		//-- move to state S2
			else if( S1S3() ) { S3(); *pstate = 3;}	//-- move to state S3
			else if( S1S4() ) { S4(); *pstate = 4;}	//-- move to state S4
			else S1();					//-- continue to stay in state S1
			break;

		case 2://-- S2
			if( S2S3() ) { S3(); *pstate = 3;}		//-- move to state S3
			else if( S2S1() ) {S1();  *pstate = 1;}	//-- move to state S1
			else if( S2S4() ) { S4(); *pstate = 4;}	//-- move to state S4
			else S2();					//-- continue to stay in state S2
			break;

		case 3://-- S3
			if( S3S2() ) {S2(); *pstate = 2;}		//-- move to state S2
			else if( S3S1() ) {S1();  *pstate = 1;}	//-- move to state S1
			else if( S3S4() ) { S4(); *pstate = 4;}	//-- move to state S4
			else S3();					//-- continue to stay in state S3
			break;
		case 4://-- S4
			if( S4S1() ) {S1(); *pstate = 1;}		//-- move to state S1
			else if( S4S2() ) { S2(); *pstate = 2;}	//-- move to state S2
			else if( S4S3() ) { S3(); *pstate = 3;}	//-- move to state S3
			else S4();					//-- continue to stay in state S4
			break;

		default: // Give error alert message
			MessageBox( NULL, TEXT("State transtition error"), TEXT("Error"), MB_OK );
			break;
		}
		return;
	}

};	//-- CDefenderAction class definition ends here

void placeRobots()
{
	//---- Desired Robot Positions
	floatPOINT GPosition;
	floatPOINT R1Position;
	floatPOINT R2Position;
	//---- Desired Robot Angles
	float Gangle;
	float R1angle;
	float R2angle;

	switch(gStartingPosition.StartPhase)
	{
		case KICKSTART:
			if(gStartingPosition.whosePossession == HOME)
			{
				GPosition.x = 7.5;
				GPosition.y = Physical_Yby2;
				R1Position.x = 50; //-- defender
				R1Position.y = 65;
				R2Position.x = 85;	//Physical_Xby2 + 7.5;
				R2Position.y = 65;	//Physical_Yby2 + 7.5;
				Gangle = 90;
				R1angle = 0;
				R2angle = 0;
			}
			else	//-- Kickstart by opponent
			{
				GPosition.x = 7.5;
				GPosition.y = 65;
				R1Position.x = 45;
				R1Position.y = 65-20;
				R2Position.x = 45;
				R2Position.y = 65+20;
				Gangle = 90;
				R1angle = 45;
				R2angle = -45;
			}
		break;

		case GOALKICK:
			if(gStartingPosition.whosePossession == HOME)
			{
				GPosition.x = 8;
				GPosition.y = 26;
				R1Position.x = 18;	
				R1Position.y = 68;	
				R2Position.x = 7.5;
				R2Position.y = 90;
				Gangle = 90;
				R1angle = 0;
				R2angle = 0;
			}
			else	//-- Goalkick by opponent
			{
				GPosition.x = 7.5;
				GPosition.y = 65;
				R1Position.x = 95;
				R1Position.y = 65-20;
				R2Position.x = 95;
				R2Position.y = 65+20;
				Gangle = 90;
				R1angle = 30;
				R2angle = -30;
			}
		break;
		case PENALTY:
			if(gStartingPosition.whosePossession == HOME)
			{
				GPosition.x = 7.5;
				GPosition.y = 65;
				R1Position.x = 71;
				R1Position.y = 25;
				R2Position.x = 100;
				R2Position.y = 65;
				Gangle = 90;
				R1angle = 0;
				R2angle = 0;
			}
			else	//-- penalty by opponent
			{
				GPosition.x = 3.5;
				GPosition.y = 65;
				R1Position.x = 81;
				R1Position.y = 65-20;
				R2Position.x = 81;
				R2Position.y = 65+20;
				Gangle = 90;
				R1angle = 0;
				R2angle = 0;
			}
		break;
		case FREEKICK:
			if(gStartingPosition.whosePossession == HOME)
			{
				GPosition.x = 7.5;
				GPosition.y = 65;
				R1Position.x = 70;
				R1Position.y = 105;
				R2Position.x = 100;
				R2Position.y = 65;
				Gangle = 90;
				R1angle = 0;
				R2angle = 0;
			}
			else	//-- freekick by opponent
			{
				GPosition.x = 7.5 + 2;
				GPosition.y = 65;
				R1Position.x = 19;
				R1Position.y = 51;
				R2Position.x = 19;
				R2Position.y = 79;
				Gangle = 90;
				R1angle = 0;
				R2angle = 0;
			}
		break;
		case FREEBALL:
			int CORRECTEDQUADRANT;
			if(globaldata.game_area == LEFT_AREA) //-- normal situation Left to Right
			{
				CORRECTEDQUADRANT = gStartingPosition.whichQuadrant;
			}
			else	//-- reverse situation Right to Left
			{
				switch(gStartingPosition.whichQuadrant)
				{
				case TOPLEFT:
					CORRECTEDQUADRANT = BOTTOMRIGHT;
					break;
				case BOTTOMLEFT:
					CORRECTEDQUADRANT = TOPRIGHT;
					break;
				case TOPRIGHT:
					CORRECTEDQUADRANT = BOTTOMLEFT;
					break;
				case BOTTOMRIGHT:
					CORRECTEDQUADRANT = TOPLEFT;
					break;
				}
			}
			switch( CORRECTEDQUADRANT )
			{
			case TOPLEFT:
				GPosition.x = 7.5;
				GPosition.y = 65;
				R1Position.x = 17.5 + 5;  // unspecified
				R1Position.y = 37.5 + 20; // unspecified
				R2Position.x = 17.5;	  // R2 always takes the kick
				R2Position.y = 105;
				Gangle = 90;
				R1angle = 90;
				R2angle = 0;
				break;
			case BOTTOMLEFT:
				GPosition.x = 7.5;
				GPosition.y = 65;
				R1Position.x = 17.5 + 5; // unspecified
				R1Position.y = 105 - 30; // unspecified
				R2Position.x = 17.5;	 // R2 always takes the kick
				R2Position.y = 25;
				Gangle = 90;
				R1angle = 90;
				R2angle = 0;
				break;
			case TOPRIGHT:
				GPosition.x = 7.5;
				GPosition.y = 65;
				R1Position.x = 92.5;	// unspecified
				R1Position.y = 25 + 30; // unspecified
				R2Position.x = 92.5;	// R2 always takes the kick
				R2Position.y = 105;
				Gangle = 90;
				R1angle = 90;
				R2angle = 0;
				break;
			case BOTTOMRIGHT:
				GPosition.x = 7.5;
				GPosition.y = 65;
				R1Position.x = 92.5;	// unspecified
				R1Position.y = 105 - 30;// unspecified
				R2Position.x = 92.5;	// R2 always takes the kick
				R2Position.y = 25;
				Gangle = 90;
				R1angle = 90;
				R2angle = 0;
				break;
			}
		break;
	}

	CPlaceRobots move(&(globaldata.PositionState),GPosition,
					R1Position, R2Position, Gangle, R1angle, R2angle);
	move.runAction();

}	//-- placeRobots()


void myShoot(int which, floatPOINT *targetPos)
{
	floatPOINT target = *targetPos;
	
	float maxAngleError = 80;
	
	int d= 0; 
	float robotAngle, dx, dy, dx1, dy1, angle1, angle2, angle3, angleError, Vl, Vr;
	floatPOINT robotVel, robotPos, ballPos;

	float Ka = 0.4; //MIGHT NEED ADJUSTING
	float speed = 20;//MIGHT NEED ADJUSTING

	ballPos = globaldata.ballposS;
	
	switch(which)
	{
	case HGOALIE:
			robotAngle = globaldata.goalieangleS;
			robotPos = globaldata.goalieposS;
			//robotVel = globaldata.goalievelS;
			break;
	case HROBOT1:
			robotAngle = globaldata.robot1angleS;
			robotPos = globaldata.robot1posS;
			//robotVel = globaldata.robot1velS;
			break;
	case HROBOT2:	
			robotAngle = globaldata.robot2angleS;
			robotPos = globaldata.robot2posS;
			//robotVel = globaldata.robot2velS;
			break;
	}	//-- end of switch
	
	dx = fabs(target.x - ballPos.x);
	dy =  ballPos.y - target.y; //??

	dx1 = fabs(ballPos.x - robotPos.x);
	dy1 = ballPos.y - robotPos.y; //??

	angle1 = atan2(dy1,dx1)*(180/PI);
	angle2 = atan2(dy,dx)*(180/PI);

	angle3 = 2*angle2 - angle1;
	
	if (angle3 > 180)		//-- normalisation for -180 to +180
		angle3 -= 360;
	else if (angle3 < -180)
		angle3 += 360;

	angleError = angle3 - robotAngle;

	if (angleError > 180)		//-- normalisation for -180 to +180
		angleError -= 360;
	else if (angleError < -180)
		angleError += 360;

	if (-maxAngleError < angleError && angleError < maxAngleError)
		d = 1;
	else
		if ((180 >= angleError && angleError > 180-maxAngleError) ||
		(-180 < angleError && angleError <= -180+maxAngleError) )
		{
			if (angleError < -90) //-- switch robot's front direction
			{
				angleError += 180;
				d = -1;
			}
			else
			if (angleError > 90)
			{
				angleError -= 180;
				d = -1;
			}
		}
		else
			d = 0;


if(d==0)
	angle(which, angle3);
else{

	Vl = d*speed - Ka*angleError;
	Vr = d*speed + Ka*angleError;

	velocity(which, Vl, Vr);
}




}


////////////////////////////////////////////////////
void myStrategy()
{
	//gchoice = 0;	//-- Striker chase the ball
	//gchoice = 1;	//-- Position Goalie at 90 degrees - Testing Angle() function
	//gchoice = 2;	//-- TO POSITION STRIKER AT THE POINT CLICKED IN THE CAPTURE WINDOW
					//-- Testing Position() function
	//gchoice = 3;
	//gchoice = 4;
	//gchoice = 5;
	//gchoice = 6;
	//gchoice = 7;	//-- State Based GOALIE
	//gchoice = 8;
	//gchoice = 9;
	//gchoice = 10;	//-- State Based kick start & NORMAL Game
	//gchoice = 11;
	//gchoice = 12;

	floatPOINT finalPos;
	floatPOINT clickPoint;
	static floatPOINT oldClickPoint={0,0};
	float finalAngle;
	float finalVel;
	float desiredAngle;
	int which;

	floatPOINT nearpoint;
	floatPOINT movePos;
	floatPOINT oppgoalbottom;
	float FARPOS;

	switch (gChoice)
	{
	case 0 :
	//-- STRIKER TO CHASE THE BALL --------------------------------

	finalPos = globaldata.ballposS;
	finalAngle = 0;
	finalVel = 0;
//	which = HGOALIE;	//-- goalie
//	which = HROBOT1;	//-- defender
	which = HROBOT2;	//-- striker
	position(which, finalPos, finalAngle, finalVel);
	avoidBound(which, finalPos);
	avoidGoalAreas(which, finalPos);

  //-----------------------------------------------------
	break;

	case 1 :
	//-- TO MAKE THE GOALIE'S ANGLE 90 DEGREES ---------------
	desiredAngle = 90;
	angleG(desiredAngle);
	//-----------------------------------------------------
	break;

	case 2 :
	//-- TO POSITION STRIKER AT THE POINT CLICKED IN THE CAPTURE WINDOW -----
	//-- -- Testing Position() function

	clickPoint.x = (float)globaldata.capPoint.x;
	clickPoint.y = (float)globaldata.capPoint.y;

	//-- covert the screen coordinates to physical coordinates
	//-- physical coordinates are in the variable finalPos
	mapxy(&clickPoint, &finalPos, &globaldata);

	finalAngle = 0;
	finalVel = 0;
	which = HROBOT2;

	position(which, finalPos, finalAngle, finalVel);
	avoidBound(which, finalPos);
	avoidGoalAreas(which, finalPos);
	//--------------------------------------------------------
	break;

	case 3 :	//Test myShoot()

		oppgoalbottom.x = (float)globaldata.oppgoalbottom.x;
		oppgoalbottom.y = (float)globaldata.oppgoalbottom.y;
		mapxy(&oppgoalbottom, &nearpoint, &globaldata);
		FARPOS = nearpoint.x;

		//	which = HGOALIE;	//-- goalie
		//	which = HROBOT1;	//-- defender
		which = HROBOT2;	//-- striker

		finalPos.x = FARPOS;
		finalPos.y = Physical_Yby2;

		myShoot(which, &finalPos);
		//position(which, finalPos, 0, 0);

		//avoidBound(which, finalPos);
		//avoidGoalAreas(which, finalPos);
		
		break;

	case 4 :	break;

	case 5 :	break;

	case 6:		break;

	case 7://---- State Based goal defense, the goal keeper
		{
			CGoalieAction Goalie(HGOALIE, &(globaldata.GState));
			Goalie.runAction();
		}
		break;

	case 8:		break;

	case 9:		break;

	case 10://---- Kick Start + Normal game
			//-- insert code here to play the game
		{
		CGoalieAction Goalie(HGOALIE, &(globaldata.GState));
		Goalie.runAction();

		CDefenderAction Defender(HROBOT1, &(globaldata.R1State));
		Defender.runAction();

		CStrikerAction Striker(HROBOT2, &(globaldata.R2State));
		Striker.runAction();
		}

		break;

	case 11:	break;

	case 12 :	break;

	default : break;

	}	//-- end of switch statement

	return;
}	//-- myStrategy()

