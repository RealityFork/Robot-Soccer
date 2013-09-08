#include "BehaviourDefender.h"


CDefenderAction::CDefenderAction(int w, int *ps)
{ 
	type = DEFENDER;
	which = w;
	pstate = ps;
	MIDDLE_X = Physical_Xby2;
	innerState = 0;
	clearVel = 0;
	clearIncDist = 30;
	hasBallDist = 20;
	loiterPos.x = Physical_Xby2;
	loiterPos.y = Physical_Yby2;
	trackingPos.x = Physical_Xby2/2;
	trackingPos.y = Physical_Yby2;
	
	home.x = (float)globaldata.homegoalbottom.x;
	home.y = (float)globaldata.homegoalbottom.y;

	//Debug::i("Defender Initialised");
}

//  Switching Conditions/ State Transitions
//  Possible state transitions
//	S0S1, S0S2, S0S3, S0S4
//	S1S2, S1S3, S1S4
//	S2S3, S2S1, S2S4
//	S3S2, S3S1, S3S4


BOOL CDefenderAction::S0S1() // If ball between DEFEND_X and halfway
{
	return true;
}
BOOL CDefenderAction::S0S2() // if ball behind tracking pos
{
	return false;
}
BOOL CDefenderAction::S0S3() // if we have ball
{
	return false;
}
BOOL CDefenderAction::S0S4() // if in other half
{
	return false;
}
BOOL CDefenderAction::S1S2()
{
	if (globaldata.ballposS.x < trackingPos.x)
	{
		Debug::d("Defender tackling");
		return true;
	}
	return false;
}
BOOL CDefenderAction::S1S3()
{
	floatPOINT pos;
	switch(which)
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
	if (hasBall(pos))
	{
		clearVel = 0;
		Debug::d("Defender clearing");
		return true;
	}
	return false;
}
BOOL CDefenderAction::S1S4()
{
	if (globaldata.ballposS.x > Physical_Xby2)
	{
		Debug::d("Defender loitering");
		return true;
	}
	return false;
}
BOOL CDefenderAction::S2S1()
{
	if (globaldata.ballposS.x > trackingPos.x && globaldata.ballposS.x <= Physical_Xby2)
	{
		Debug::d("Defender tracking");
		return true;
	}
	return false;
}
BOOL CDefenderAction::S2S3()
{
	return S1S3();
}
BOOL CDefenderAction::S2S4()
{
	return S1S4();
}
BOOL CDefenderAction::S3S1()
{
	floatPOINT pos;
	switch(which)
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
	if (globaldata.ballposS.x > trackingPos.x && globaldata.ballposS.x <= Physical_Xby2 && !hasBall(pos))
	{
		Debug::d("Defender tackling");
		return true;
	}
	return false;
}
BOOL CDefenderAction::S3S2()
{
	floatPOINT pos;
	switch(which)
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
	if (globaldata.ballposS.x < trackingPos.x && !hasBall(pos))
	{
		Debug::d("Defender tackling");
		return true;
	}
	return false;
}
BOOL CDefenderAction::S3S4()
{
	floatPOINT pos;
	switch(which)
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
	if (globaldata.ballposS.x > Physical_Xby2 && !hasBall(pos))
	{
		Debug::d("Defender loitering");
		return true;
	}
	return false;
}
BOOL CDefenderAction::S4S1()
{
	return S2S1();
}
BOOL CDefenderAction::S4S2()
{
	return S1S2();
}
BOOL CDefenderAction::S4S3()
{
	return S1S3();
}

// Action States
// S0 initialisation
//void S0() {}; // No Action for Initialisation State

void CDefenderAction::S1() //-- Track like goalie
{
	floatPOINT pos;
	mapxy(&home,&pos,&globaldata);
	pos.x += 30;
	pos.y = globaldata.ballposS.y;
	position(which, pos, 90, 0);
}

void CDefenderAction::S2()	//-- tackle
{
	myTackle(which);
}

void CDefenderAction::S3()//----	Clear
{
	// Place the target position some distance in front of the defender,
	// Each time swing the target point around my some angle towards 0degrees (clear into other half)
	// Increase the velocity with each frame to try to keep the ball
	floatPOINT target;
	int angle = globaldata.robot1angle;
	if (angle > 0) angle-=30;
	else if (angle < 0) angle+=30;
	//target = globaldata.robot1pos;
	//finalPos.y = (globaldata.GballposS.y - ((globaldata.GballposS.x - finalPos.x)/tan(ballAngle * 3.14159265 / 180.0)));
	target.y = globaldata.robot1pos.y + sin(angle*PI/180.0)*clearIncDist;
	target.x = globaldata.robot1pos.x + cos(angle*PI/180.0)*clearIncDist;
	clearVel++;

	position(which, target, 0, (clearVel/20)*(clearVel/20)); // Might need to change angle.
}
void CDefenderAction::S4()//----	Assist
{
	// This is just a draft. It will be pretty shoot happy
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
	// if someone has the ball or it is near the edges, dont shoot
	if (globaldata.ballposS.y > Physical_Yby2 + 30 || globaldata.ballposS.y < Physical_Yby2 - 30 ||
		hasBall(r1) || hasBall(r2) || hasBall(globaldata.opporobot1posS) || hasBall(globaldata.opporobot2posS) ||hasBall(globaldata.opporobot3posS))
		position(which, loiterPos, 0, 0); // Do trakcing here?
	else
	{
		//floatPOINT lol;
		//lol.y = loiterPos.y;
		//lol.x = loiterPos.x + 30;
		//position(which, lol, 0, 0);
		testMyShoot(which);
	}
}

BOOL CDefenderAction::hasBall(floatPOINT rPos)
{
	floatPOINT dist;
	dist.x = rPos.x - globaldata.ballposS.x;
	dist.y = rPos.y - globaldata.ballposS.y;
	if (sqrt(dist.x*dist.x + dist.y*dist.y) < hasBallDist)
		return true;
	return false;
}

//-- Run function
void CDefenderAction::runAction()
{
	//Debug::d("Defender runaction");
	switch(*pstate)
	{
		//Debug::d("Defender case");
	case 0://-- S0 (initialisation)
		//Debug::d("Defender 0");
		if( S0S1() ) { S1(); *pstate = 1;}	//-- move to state S1
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
		//Debug::d("Defender 1");
		if( S1S2() ) {S2(); *pstate = 2;}	//-- move to state S2
		else if( S1S3() ) {S3(); *pstate = 3;}	//-- move to state S3
		else if( S1S4() ) {S4(); *pstate = 4;}	//-- move to state S4
		else S1();					//-- continue to stay in state S1
		break;

	case 2://-- S2
		if( S2S3() ) { S3(); *pstate = 3;}	//-- move to state S3
		else if( S2S1() ) {S1();  *pstate = 1;}	//-- move to state S1
		else if( S2S4() ) { S4(); *pstate = 4;}	//-- move to state S4
		else S2();					//-- continue to stay in state S2
		break;

	case 3://-- S3
		if( S3S2() ) {S2(); *pstate = 2;}	//-- move to state S2
		else if( S3S1() ) {S1();  *pstate = 1;}	//-- move to state S1
		else if( S3S4() ) { S4(); *pstate = 4;}	//-- move to state S4
		else S3();					//-- continue to stay in state S3
		break;
	case 4://-- S4
		if( S4S1() ) {S1(); *pstate = 1;}	//-- move to state S1
		else if( S4S2() ) { S2(); *pstate = 2;}	//-- move to state S2
		else if( S4S3() ) { S3(); *pstate = 3;}	//-- move to state S3
		else S4();					//-- continue to stay in state S4
		break;

	default: // Give error alert message
		MessageBox( NULL, TEXT("State transtition error"), TEXT("Error"), MB_OK );
		break;
	}
}
