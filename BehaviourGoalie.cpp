#include "BehaviourGoalie.h"

CGoalieAction::CGoalieAction(int w, int *ps)
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
CGoalieAction::~CGoalieAction(){}

//  Switching Conditions/ State Transitions
//  Possible state transitions
//	S0S1, S0S2, S0S3
//	S1S2,
//	S2S3, S2S1,
//	S3S2


BOOL CGoalieAction::S0S1()
{ //---- ball in goal area
	if ((BallPos.x <= NEARPOS)
		&& (BallPos.y < (Physical_Yby2 + CLEARYOFFSET)) 
		&& (BallPos.y > (Physical_Yby2 - CLEARYOFFSET)) )//ball in near
		return true;
	else
		return false;
}

BOOL CGoalieAction::S0S2()
{//---- ball in middle (outside goal area but inside centre half line)
	if((!S0S1()) && (BallPos.x < MIDDLE))
		return true;
	else
		return false;
}

BOOL CGoalieAction::S0S3()
{//---- ball moves beyond centre line
	if(BallPos.x >= MIDDLE)
		return true;
	else
		return false;
}

BOOL CGoalieAction::S1S2()
{//-- ball moves from goal area to middle
	if (BallPos.x > NEARPOS + XHYSTERESIS ||
		(BallPos.x < NEARPOS + XHYSTERESIS &&(
		(BallPos.y > Physical_Yby2 + CLEARYOFFSET + YHYSTERESIS)
		|| (BallPos.y < Physical_Yby2 - CLEARYOFFSET - YHYSTERESIS) ) ))
		return true;
	else
		return false;
}

BOOL CGoalieAction::S2S1()
{//---- ball moves from middle to goal area
	if ((BallPos.x <= NEARPOS)
		&& (BallPos.y < (Physical_Yby2 + CLEARYOFFSET))
		&& (BallPos.y > (Physical_Yby2 - CLEARYOFFSET)) )//ball in near
		return true;
	else
		return false;
}

BOOL CGoalieAction::S2S3()
{//---- ball moves from middle to far

	if(BallPos.x >= MIDDLE + XHYSTERESIS)
		return true;
	else
		return false;
}

BOOL CGoalieAction::S3S2()
{//---- ball moves from far to middle

	if(BallPos.x <= MIDDLE - XHYSTERESIS)
		return true;
	else
		return false;
}

// Action States
// S0 initialisation
//void S0() {}; // No Action for Initialisation State

void CGoalieAction::S1() //-- clear the ball 
{
	float FINALVELOCITY = (float)10;

	positionG(BallPos, 90, FINALVELOCITY);
	avoidBound(which,BallPos);
	escapeGoal(which);
	
}

void CGoalieAction::S2()	//-- track ball y position + predict shot
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

void CGoalieAction::S3()//----	Follow the ball's current Y position
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
void CGoalieAction::runAction()
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
}
