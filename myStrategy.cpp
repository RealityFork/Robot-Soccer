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
	//-- declare more variables as required ---------
	
public:
	CGoalieAction(int w, int *ps) 
	{ 
		floatPOINT nearpoint;
		floatPOINT homegoalbottom;
		pstate = ps ;  
		which = w;
		MIDDLE = Physical_Xby2 + 30;
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

		GOALIESTANDX = (NEARPOS-XHYSTERESIS)/2 - gGoalieActionParameters.GXcompensation;

		//-- add more code here as required ------


	}
	~CGoalieAction(){}

//  Switching Conditions/ State Transitions
//  Possible state transitions
//	S0S1, S0S2, S0S3
//	S1S2,
//	S2S3, S2S1,
//	S3S2

	//-- write code for the switching/transition functions here -----

	BOOL S0S1()
	{ //---- ball in goal area
		if ((BallPos.x <= NEARPOS+20)
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
		if ((BallPos.x <= NEARPOS+20)
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
				//-- write code here which makes the goalkeeper clear the ball
	{
		float FINALVELOCITY = (float)0.88;

		positionG(BallPos, 90, FINALVELOCITY);
		avoidBound(which,BallPos);
		escapeGoal(which);
	}

	void S2()	//-- track ball y position + predict shot
	{	
		//-- calculate final position for the goalkeeper
		finalPos.x = GOALIESTANDX+20;


		if(Ballspeed >= 0.5){
		globaldata.ballAngleAve = (globaldata.ballangleS + globaldata.ballAngleAve*5)/6;
		}
		float ballAngle = 0;
		float ballAngleActual = globaldata.ballangleS; //or... = globaldata.ballAngleAve;

		//May need to flip angle
		//ballAngleActual = -ballAngleActual;



		if(ballAngleActual > 90)//90 to 180
			ballAngle = ballAngleActual - 90;
		else if(ballAngleActual > 0)//0 to 90
			ballAngle = 0;
		else if(ballAngleActual < -90)//-90 to -180
			ballAngle = ballAngleActual + 90;
		else //0 to -90
			ballAngle = 0;

		//if (ballAngleActual > 0)
		//	ballAngle = -(globaldata.ballAngleAve - 90);
		//else 
		//	ballAngle = -(globaldata.ballAngleAve + 90);
		

		//Might need to change +/- here...
		//------------------->here<
		finalPos.y = BallPos.y - ((BallPos.x - finalPos.x)/tan(ballAngle * 3.14159265 / 180.0));


		if(finalPos.y > Physical_Yby2 + CLEARYOFFSET)
			finalPos.y = Physical_Yby2 + CLEARYOFFSET;

		if(finalPos.y < Physical_Yby2 - CLEARYOFFSET)
			finalPos.y = Physical_Yby2 - CLEARYOFFSET;

		globaldata.predicted = finalPos;

		positionG(finalPos, 90, 0);
		avoidBound(which,finalPos);
		escapeGoal(which);
	}

	void S3()//----	Idle in the centre of the goal
	{
		floatPOINT finalPos;
		finalPos.x = GOALIESTANDX+20;
		finalPos.y = Physical_Yby2;

		//---- Add code here to limit tracking y to penalty area boundary
		//----------------------------------------------------------

		positionG(finalPos, 90, 0);
		//avoidBound(which, finalPos);
		//escapeGoal(which);
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
			break;
		}
		return;
	}

};	//-- CGoalieAction class definition ends here

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

	case 3 :	break;

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

		break;

	case 11:	break;

	case 12 :	break;

	default : break;

	}	//-- end of switch statement

	return;
}	//-- myStrategy()
