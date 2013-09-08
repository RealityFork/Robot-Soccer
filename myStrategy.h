//-- Filename : myStrategy.h

#if !defined MYSTRATEGY_INCLUDED_
#define MYSTRATEGY_INCLUDED_

#include "commondata.h"
#include "StdAfx.h"
#include "controlalgo.h"
#include "commondata.h"
#include "RFComm.h"
#include "map.h"
#include "math.h"
#include "BehaviourGoalie.h"
#include "BehaviourStriker.h"
#include "BehaviourDefender.h"
#include "BehaviourRobot.h"

#define ROBOTWIDTH	7.6
//--- width of the colour jacket on the robot
#define ROBOTWIDTHby2 3.8


//-- Function prototype ---------
void myStrategy(void);

//---- Used by User interface to place robots in starting position
//---- Excecuted if pdata->PositionState != 2  (stable state)
void placeRobots(void);

void myShoot(int which, floatPOINT *targetPos);
void myTackle(int which);
void chaseBall(int which);
void clearBall(int which);
void testMyShoot(int which);
void switchRobotsIfCan();
floatPOINT getPos(BehaviourType);

#endif