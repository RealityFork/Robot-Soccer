//-- Filename : myStrategy.cpp
//-- Implements strategy
#include "stdafx.h"
#include "myStrategy.h"

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


void myShoot(int which, floatPOINT *ptargetPos)
{
	float		targetAngle, ballAngle, robotAngle, dx, dy, distanceError, ballTargetAngle;
	floatPOINT	RobotBallvector, BallTargetvector, robotPos, robotVel, ballPos, targetPos, desiredPos, ballVel;


	ballPos = globaldata.ballposS;
	ballVel = globaldata.ballvelS;

	targetPos = *ptargetPos;

	switch(which)
	{
	case HGOALIE	:	robotAngle = globaldata.goalieangleS;
						robotPos = globaldata.goalieposS;
						robotVel = globaldata.goalievelS;
						break;
	case HROBOT1	:	robotAngle = globaldata.robot1angleS;
						robotPos = globaldata.robot1posS;
						robotVel = globaldata.robot1velS;
						break;
	case HROBOT2	:	robotAngle = globaldata.robot2angleS;
						robotPos = globaldata.robot2posS;
						robotVel = globaldata.robot2velS;
						break;
	}	//-- end of switch

	if (robotAngle > 90)
			robotAngle -= 180;
	if (robotAngle < -90)
			robotAngle += 180;
	
	dx = ballPos.x - robotPos.x;
	dy = ballPos.y - robotPos.y;
	RobotBallvector.x = dx;
	RobotBallvector.y = dy;

	distanceError = (float)sqrt(dx*dx+dy*dy);

	BallTargetvector.x = targetPos.x - ballPos.x;
	BallTargetvector.y = targetPos.y - ballPos.y;

	if(BallTargetvector.x == 0 && BallTargetvector.y == 0)
		targetAngle = 0;
	else
		targetAngle = (float)(atan2((double) BallTargetvector.y, (double) BallTargetvector.x)*180/PI);

	if(RobotBallvector.x == 0 && RobotBallvector.y == 0)
		ballAngle = targetAngle;
	else
		ballAngle = (float)(atan2((double) RobotBallvector.y, (double) RobotBallvector.x)*180/PI);
	ballTargetAngle = ballAngle - targetAngle;
	while(ballTargetAngle>180) ballTargetAngle-=360;
	while(ballTargetAngle<-180) ballTargetAngle+=360;

	float offset = 14;
	if (robotPos.x > ballPos.x)//If on wrong side then boost it to get on the other side
		offset = 30;

	desiredPos.x = (float) (ballPos.x + ballVel.x*2 - offset * cos(targetAngle*PI/180));
	desiredPos.y = (float) (ballPos.y + ballVel.y*2 - offset * sin(targetAngle*PI/180));

	//-- limit desiredPos
	if (desiredPos.x < 0)
		desiredPos.x = 0;
	if (desiredPos.x > (Physical_X))
		desiredPos.x = (Physical_X);
	if (desiredPos.y < 4)
		desiredPos.y = 4;
	if (desiredPos.y > (Physical_Y-4))
		desiredPos.y = (Physical_Y-4);


		//Lined up for shot?
		if ((ballTargetAngle <= 45 && ballTargetAngle >= -45) && distanceError < 18)
		{

			if (robotAngle <= targetAngle + 15 && //Might want to change these
				robotAngle >= targetAngle - 15)
			{
				//SHOOT!!!!
				//position(which, ballPos, targetAngle, 50.0);
				position(which, targetPos, targetAngle, 50.0);
				Debug::i("Shoot!");
			}
			else
			{
				angle(which, targetAngle);
				//Debug::i("Adjusting angle");
			}
		}
		else
				//-- need to get into position
		{
			//Debug::i("Positioning");
				//-- robot behind the ball?
				if ( robotPos.x < (ballPos.x) )
				{
					//line up shot
					position(which, desiredPos, targetAngle, 3.0);
				}
				else	
				{
					//Need to stop the robot from hitting the ball from the wrong side.
					if(desiredPos.x < (ballPos.x + 10) && desiredPos.x > (ballPos.x - 10))
					{
						//desiredpos tooo close
					}
					else{
			
						if ((ballPos.y - robotPos.y) >= 0)
						{
							if(desiredPos.y > (ballPos.y - 10))
								desiredPos.y = ballPos.y - 10;
							if (desiredPos.y < 4)
								desiredPos.y = 4;
							
						}
						else
						{
							if(desiredPos.y < (ballPos.y + 10))
								desiredPos.y = ballPos.y + 10;
							if (desiredPos.y > (Physical_Y-4))
								desiredPos.y = (Physical_Y-4);
						}

						//if(desiredPos.x > (ballPos.x - 10))
						//		desiredPos.x = ballPos.x - 10;
					}
					position(which, desiredPos, targetAngle, 2.0);


				}
		}

	return;
}	//-- myShoot() LATEST MY SHOOT FROM ELLIOT


// =========================================================================
// SOME STUFF I HAVE BEEN WORKING ON
// FEEL FREE TO CHANGE ANYTHING
void myTackle(int which)
{
	testMyShoot(which);
//	chaseBall(which);
}

// Chase the ball
void chaseBall(int which)
{
	floatPOINT	finalPos;
	float		finalAngle;
	float		finalVel;

	finalPos = globaldata.ballposS;
	finalAngle = 0;
	finalVel = 0;

	position(which, finalPos, finalAngle, finalVel);
	avoidBound(which, finalPos);
	avoidGoalAreas(which, finalPos);
}

// Test MyShoot Function
void testMyShoot(int which){
	floatPOINT	oppgoalbottom;
	float		FARPOS;
	floatPOINT	finalPos;
	float		finalAngle;
	float		finalVel;
	floatPOINT	nearpoint;
	
	oppgoalbottom.x = (float)globaldata.oppgoalbottom.x;
	oppgoalbottom.y = (float)globaldata.oppgoalbottom.y;
	mapxy(&oppgoalbottom, &nearpoint, &globaldata);
	FARPOS = nearpoint.x;

	finalPos.x = FARPOS;
	finalPos.y = Physical_Yby2;

	myShoot(which, &finalPos);
	//position(which, finalPos, 0, 0);

//	avoidBound(which, finalPos);
//	avoidGoalAreas(which, finalPos);
}

// =========================================================================


void switchRobots(RobotBehaviour* b1, RobotBehaviour* b2)
{
	int w1 = b1->which;
	b1->switchTo(b2->which);
	b2->switchTo(w1);
}

void switchRobotsIfCan()
{
	//-- Switch for faster defence --//
	floatPOINT dPos = getPos(DEFENDER);
	floatPOINT sPos = getPos(STRIKER);

	// Switch if both robots are in the wrong half,
	// And the defender is further away than the striker
	if (globaldata.ballposS.x < Physical_Xby2 &&
		dPos.x > Physical_Xby2 && sPos.x > Physical_Xby2 &&
		dPos.x > sPos.x)
	{
		Debug::i("Switching striker and defender");
		switchRobots(globaldata.dBehaviour, globaldata.sBehaviour);
	}
	//-------------------------------//


	floatPOINT gPos = getPos(GOALIE);
	floatPOINT home, h;
	home.x = (float)globaldata.homegoalbottom.x;
	home.y = (float)globaldata.homegoalbottom.y;
	mapxy(&home, &h, &globaldata);

	//-- Switch if Str/Def is closer to goal than goalie --//
	float dDist = sqrt(pow(h.x-dPos.x, 2) + pow(Physical_Yby2-dPos.y, 2));
	float sDist = sqrt(pow(h.x-sPos.x, 2) + pow(Physical_Yby2-sPos.y, 2));
	float gDist = sqrt(pow(h.x-gPos.x, 2) + pow(Physical_Yby2-gPos.y, 2));

	if (dDist < gDist && dDist < sDist) // Switch defender and goalie
	{
		CString lol = "";
		lol.Format("%f, %f", h.x, gDist);
		Debug::i("Switching goalie and defender");
		Debug::i(lol);
		switchRobots(globaldata.gBehaviour, globaldata.dBehaviour);
	}
	else if (sDist < gDist && sDist < dDist) // Switch striker and goalie
	{
		Debug::i("Switching goalie and striker");
		switchRobots(globaldata.gBehaviour, globaldata.sBehaviour);
	}
	//-----------------------------------------------------//
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

	chaseBall(HROBOT1);

  //-----------------------------------------------------
	break;

	case 1 :
	//-- TO MAKE THE GOALIE'S ANGLE 90 DEGREES ---------------
	desiredAngle = 90;
	angleG(which, desiredAngle);
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
	which = HROBOT1;

	position(which, finalPos, finalAngle, finalVel);
	avoidBound(which, finalPos);
	avoidGoalAreas(which, finalPos);
	//--------------------------------------------------------
	break;

	case 3 :	//Test myShoot()
		
		testMyShoot(HROBOT1);
		
		/*
		oppgoalbottom.x = (float)globaldata.oppgoalbottom.x;
		oppgoalbottom.y = (float)globaldata.oppgoalbottom.y;
		mapxy(&oppgoalbottom, &nearpoint, &globaldata);
		FARPOS = nearpoint.x;

		//	which = HGOALIE;	//-- goalie
			which = HROBOT1;	//-- defender
		// which = HROBOT2;	//-- striker

		finalPos.x = FARPOS;
		finalPos.y = Physical_Yby2;

		myShoot(which, &finalPos);
		//position(which, finalPos, 0, 0);

		//avoidBound(which, finalPos);
		//avoidGoalAreas(which, finalPos);
		*/
		
		break;

	case 4 :
		globaldata.dBehaviour->runAction();
		break;

	case 5 :	break;

	case 6:		break;

	case 7://---- State Based goal defense, the goal keeper
		{
			globaldata.gBehaviour->runAction();
		}
		break;

	case 8:		break;

	case 9:		break;

	case 10://---- Kick Start + Normal game
			//-- insert code here to play the game
		{
		globaldata.gBehaviour->runAction();
		globaldata.dBehaviour->runAction();
		globaldata.sBehaviour->runAction();
		}

		break;

	case 11:	break;

	case 12 :	break;

	default : break;

	}	//-- end of switch statement

	switchRobotsIfCan();

	return;
}	//-- myStrategy()

floatPOINT getPos(BehaviourType t)
{
	RobotBehaviour* b;
	floatPOINT pos;
	switch(t)
	{
	case GOALIE:
		b = globaldata.gBehaviour;
		break;
	case DEFENDER:
		b = globaldata.dBehaviour;
		break;
	case STRIKER:
		b = globaldata.sBehaviour;
		break;
	}

	switch (b->which)
	{
	case HGOALIE:
		pos = globaldata.goalieposS;
		break;
	case HROBOT1:
		pos = globaldata.robot1posS;
		break;
	case HROBOT2:
		pos = globaldata.robot2posS;
		break;
	}
	return pos;
}