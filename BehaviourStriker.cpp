#include "BehaviourStriker.h"

CStrikerAction::CStrikerAction(int w, int *ps)
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

//  Switching Conditions/ State Transitions
//  Possible state transitions
//	S0S1, S0S2, S0S3
//	S1S2, S1S3
//	S2S3, S2S1,
//	S3S2, S3S1


BOOL CStrikerAction::S0S1()
{
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
	return S0S2();
}
BOOL CStrikerAction::S1S3()
{
	return S0S3();
}

BOOL CStrikerAction::S2S1()
{
	return S0S1();
}

BOOL CStrikerAction::S2S3()
{
	return S0S3();
}

BOOL CStrikerAction::S3S2()
{
	return S0S2();
}
BOOL CStrikerAction::S3S1()
{
	return S0S1();
}

// Action States
// S0 initialisation
//void S0() {}; // No Action for Initialisation State

void CStrikerAction::S1() //-- get ball 
{
	floatPOINT goalTarget;
	goalTarget.x = FARPOS;
	goalTarget.y = Physical_Yby2;

	myShoot(which, &goalTarget);
}

void CStrikerAction::S2()	//-- tackle
{	
	
}

void CStrikerAction::S3()//----	Defend
{

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
