#include "BehaviourStriker.h"
//#include ""

CStrikerAction::CStrikerAction(int w, int *ps)
{ 

	//variables from goalie action
	type = STRIKER;
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
	GOALX = nearpoint.x/2 + 5;// - gGoalieActionParameters.GXcompensation;

	oppgoalbottom.x = (float)globaldata.oppgoaltop.x;
	oppgoalbottom.y = (float)globaldata.oppgoaltop.y;
	mapxy(&oppgoalbottom, &nearpoint, &globaldata);
	FARPOS = nearpoint.x;

}

//  Switching Conditions/ State Transitions
//  Possible state transitions
//	S0S1, S0S2, S0S3
//	S1S2, S1S3
//	S2S3, S2S1,
//	S3S2, S3S1


BOOL CStrikerAction::S0S1()
{
	Debug::i("S0S1");
	return true;
}

BOOL CStrikerAction::S0S2()
{
	return false;
}

BOOL CStrikerAction::S0S3()
{
	return false;
}

BOOL CStrikerAction::S1S2()
{
	if(hasBalls(globaldata.opporobot1posS) || hasBalls(globaldata.opporobot2posS) || hasBalls(globaldata.opporobot3posS) || (globaldata.ballposS.x < MIDDLE && !isInGoal()))
	{
		Debug::i("S1S2");
		return true;
	}
	else
		return false;
}
BOOL CStrikerAction::S1S3()
{
	if (isInGoal())
	{
		Debug::i("S1S3");
		return true;
	}
	else
		return false; 
}

BOOL CStrikerAction::S2S1()
{
	if (globaldata.ballposS.x > MIDDLE)
	{
		Debug::i("S2S1");
		return true;
	}
	else
		return false;
}

BOOL CStrikerAction::S2S3()
{
	if (isInGoal())
	{
		Debug::i("S2S3");
		return true;
	}
	else
		return false; 
}

BOOL CStrikerAction::S3S2()
{
	if (globaldata.ballposS.x < MIDDLE && !isInGoal())
	{
		Debug::i("S3S2");
		return true;
	}
	else
		return false;
}
BOOL CStrikerAction::S3S1()
{
	if (globaldata.ballposS.x > MIDDLE)
	{
		Debug::i("S3S1");
		return true;
	}
	else
		return false;
}



// Action States
// S0 initialisation
//void S0() {}; // No Action for Initialisation State

void CStrikerAction::S1() //-- shooting
{
	floatPOINT r1, r2;
	switch(which)
	{
	case HGOALIE:
		r1 = globaldata.robot1posS;
		r2 = globaldata.robot2posS;
		break;
	case HROBOT1:
		r1 = globaldata.goalieposS;
		r2 = globaldata.robot2posS;
		break;
	case HROBOT2:
		r1 = globaldata.goalieposS;
		r2 = globaldata.robot1posS;
		break;
	}
	floatPOINT goalTarget;
	goalTarget.x = FARPOS;
	goalTarget.y = Physical_Yby2;

	if (!hasBalls(r1))
		myShoot(which, &goalTarget);
	else
	{
		floatPOINT pos;
		//mapxy(&home,&pos,&globaldata);
		pos.x = MIDDLE;
		pos.y = globaldata.ballposS.y;
		position(which, pos, 90, 0);
	}

}

void CStrikerAction::S2()	//-- chasing
{	
	chaseBall(which);
}

void CStrikerAction::S3()//----	Defend/ready
{
	floatPOINT pos;
	//mapxy(&home,&pos,&globaldata);
	pos.x = MIDDLE;
	pos.y = globaldata.ballposS.y;
	position(which, pos, 90, 0);
}

//-- Run function
void CStrikerAction::runAction()
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

BOOL CStrikerAction::hasBalls(floatPOINT rPos)
{
	floatPOINT dist;
	dist.x = rPos.x - globaldata.ballposS.x;
	dist.y = rPos.y - globaldata.ballposS.y;
	if (sqrt(dist.x*dist.x + dist.y*dist.y) < 20)
		return true;
	return false;
}

BOOL CStrikerAction::isInGoal()
{
	if ((globaldata.ballposS.x < 20) && (globaldata.ballposS.y > (Physical_Yby2 - (Physical_Yby2/3.5))) && (globaldata.ballposS.y < (Physical_Yby2 + (Physical_Yby2/3.5))))
		return true;
	else
		return false;
}
