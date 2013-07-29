//-- Filename : myStrategy.h

#if !defined MYSTRATEGY_INCLUDED_
#define MYSTRATEGY_INCLUDED_

#include "commondata.h"

#define ROBOTWIDTH	7.6
//--- width of the colour jacket on the robot
#define ROBOTWIDTHby2 3.8


//-- Function prototype ---------
void myStrategy(void);

//---- Used by User interface to place robots in starting position
//---- Excecuted if pdata->PositionState != 2  (stable state)
void placeRobots(void);

void myShoot(int which, floatPOINT *targetPos);

#endif