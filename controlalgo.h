//-- Filename : controlalgo.h
//-- Implements control algorithms

#if !defined(CONTROLALGO_INCLUDED_)
#define CONTROLALGO_INCLUDED_

#include "stdAfx.h"
#include "commondata.h"
#include "math.h"
#include "vision.h"
#include "map.h"
#include "myStrategy.h"

#define HGOALIE	0
#define HROBOT1	1
#define HROBOT2	2

#define G_LENGTH 40		//-- length of goal mouth 40 cms

#define VELOCITYSCALING 1.0
//-- Velocity Scaling Factor [ used in Velocity() function ]
#define SPINVELOCITYSCALING 1.0
//-- Spin Velocity Scaling Factor [ used in Spin() function ]

enum spin_dir {CLOCKWISE, ANTICLOCKWISE};

void position(int which, floatPOINT finalPos, float finalAngle, float finalVel);
//void positionG(floatPOINT finalPos, float finalAngle, float finalVel);
void angle(int which, float desiredAngle);
void angleG(int, float desiredAngle);
void velocity(int which, int Vl, int Vr);

void avoidBound(int which, floatPOINT finalPos);
void avoidGoalAreas(int which, floatPOINT finalPos);
void escapeGoal(int which);

void spin(int which, int direction);
void avoidGoalie(int which);
void separateRobots(void);
void turnAtWalls(int which);

#endif