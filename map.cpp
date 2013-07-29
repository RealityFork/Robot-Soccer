//-- Filename : map.cpp
//-- Mapping functions to convert screen coordinates to physical coordinates.

#include "stdafx.h"
#include "commondata.h"
#include "map.h"
#include "vision.h"
#include "math.h"

//-- Standard Mapping Functions

void mapxy(floatPOINT *Screen, floatPOINT *Physical, commondata *pdata)
{
	//-- Converts a Screen coordinate to a Physical coordinate
	//-- Screen origin at top left corner
	//-- Physical origin at bottom left corner

	Physical->x=(Screen->x - pdata->homegoaltop.x)*Physical_X/
							(pdata->oppgoalbottom.x - pdata->homegoaltop.x);
	Physical->y=(pdata->rightbottom.y - Screen->y)*Physical_Y/
							(pdata->rightbottom.y - pdata->lefttop.y);

	if ( (Physical->x < 0) && (Physical->y < 0) )	//-- both negative
	{
		Physical->x = 0;
		Physical->y = 0;
	}
}

void rotatemapxy(floatPOINT *Physical)
{
	//-- Swaps BottomLeft (0,0) position with TopRight (150,130) position
	//-- and vice-versa
	if ( !(Physical->x == 0 && Physical->y == 0) )
	{
		Physical->x = Physical_X - Physical->x;
		Physical->y = Physical_Y - Physical->y;
	}
}

void turnangle(float *angle)
{
	//-- Turns the angle 180 degree, used  when attacking Right to Left
	//-- TopRight is (0,0) position

	*angle += 180;
	if(*angle>180) *angle-=360;
	if(*angle<-180) *angle+=360;

	/*
	if (*angle >= 0)	//-- i.e. positive
		*angle = *angle - 180;
	else
		if (*angle < 0)	//-- i.e. negative
			*angle = 180 + *angle;
	*/
}

void mapall(commondata *pdata)
{
	//-- Changes all Screen Positions to Physical positions

	//-- if Left to Right (i.e (0,0) is bottomLeft)
	mapxy(&(pdata->ballpos),&(pdata->ballposS),pdata);
	mapxy(&(pdata->goaliepos),&(pdata->goalieposS),pdata);
	mapxy(&(pdata->robot1pos),&(pdata->robot1posS),pdata);
	mapxy(&(pdata->robot2pos),&(pdata->robot2posS),pdata);

	if (gParallaxCorrectionEnabled)
	{
		//-- Parallax correction functions, using calculated physical image centre

		pdata->ballposS = parallaxCorrection(&(pdata->ballposS),pdata, (float)BALLHEIGHT);
		pdata->goalieposS = parallaxCorrection(&(pdata->goalieposS), pdata, (float)ROBOTHEIGHT);
		pdata->robot1posS = parallaxCorrection(&(pdata->robot1posS), pdata, (float)ROBOTHEIGHT);
		pdata->robot2posS = parallaxCorrection(&(pdata->robot2posS), pdata, (float)ROBOTHEIGHT);
		
	}
	
	//-- Copy Screen angle to Physical angle
	pdata->ballangleS = pdata->ballangle;
	pdata->goalieangleS = pdata->goalieangle;
	pdata->robot1angleS = pdata->robot1angle;
	pdata->robot2angleS = pdata->robot2angle;

	//-- if Right to Left (i.e (0,0) is topright)
	if(pdata->game_area==RIGHT_AREA)
	{
		//-- swap the coordinates and angle

		rotatemapxy(&(pdata->ballposS));
		rotatemapxy(&(pdata->goalieposS));
		rotatemapxy(&(pdata->robot1posS));
		rotatemapxy(&(pdata->robot2posS));

		turnangle(&(pdata->goalieangleS));
		turnangle(&(pdata->robot1angleS));
		turnangle(&(pdata->robot2angleS));
		turnangle(&(pdata->ballangleS));
	}

	//-- everything is converted
}

void updateVariables(commondata *pdata)
{
	//-- calculate velocities from present and old positions
	pdata->ballvel.x = (pdata->ballpos.x - pdata->oldballpos.x)/halfFrameJump;
	pdata->ballvel.y = (pdata->ballpos.y - pdata->oldballpos.y)/halfFrameJump;

	pdata->ballangle = (float)atan2(pdata->ballvel.y, pdata->ballvel.x)*180/PI;
	while (pdata->ballangle > 180)  pdata->ballangle-=360;
	while (pdata->ballangle <- 180) pdata->ballangle+=360;
	
	//-- Calculate Linear velocities
	pdata->goalievel.x = (pdata->goaliepos.x - pdata->oldgoaliepos.x)/halfFrameJump;
	pdata->goalievel.y = (pdata->goaliepos.y - pdata->oldgoaliepos.y)/halfFrameJump;

	pdata->robot1vel.x = (pdata->robot1pos.x - pdata->oldrobot1pos.x)/halfFrameJump;
	pdata->robot1vel.y = (pdata->robot1pos.y - pdata->oldrobot1pos.y)/halfFrameJump;

	pdata->robot2vel.x = (pdata->robot2pos.x - pdata->oldrobot2pos.x)/halfFrameJump;
	pdata->robot2vel.y = (pdata->robot2pos.y - pdata->oldrobot2pos.y)/halfFrameJump;

	//-- Calculate Angular velocities
	pdata->goalieangvel = (pdata->goalieangle - pdata->oldgoalieangle)/halfFrameJump;
	pdata->robot1angvel = (pdata->robot1angle - pdata->oldrobot1angle)/halfFrameJump;
	pdata->robot2angvel = (pdata->robot2angle - pdata->oldrobot2angle)/halfFrameJump;

	//-- normalise the angular velocities -----------------
	while(pdata->goalieangvel>180)pdata->goalieangvel-=360;
	while(pdata->goalieangvel<-180)pdata->goalieangvel+=360;

	while(pdata->robot1angvel>180)pdata->robot1angvel-=360;
	while(pdata->robot1angvel<-180)pdata->robot1angvel+=360;

	while(pdata->robot2angvel>180)pdata->robot2angvel-=360;
	while(pdata->robot2angvel<-180)pdata->robot2angvel+=360;


	//-- copy the present positions to old positions
	pdata->oldballpos = pdata->ballpos;
	pdata->oldgoaliepos = pdata->goaliepos;
	pdata->oldrobot1pos = pdata->robot1pos;
	pdata->oldrobot2pos = pdata->robot2pos;

	//-- copy the present angles to old angles
	pdata->oldgoalieangle = pdata->goalieangle;
	pdata->oldrobot1angle = pdata->robot1angle;
	pdata->oldrobot2angle = pdata->robot2angle;

	return;
}	//-- end of function updateVariables()

void updateStrategyVariables(commondata *pdata)
{
	//-- Called every sample to calculate velocity in Physical coordinates

	//-- calculate physical velocities from present and old positions
	pdata->ballvelS.x = (pdata->ballposS.x - pdata->oldballposS.x)/halfFrameJump;
	pdata->ballvelS.y = (pdata->ballposS.y - pdata->oldballposS.y)/halfFrameJump;

	pdata->goalievelS.x = (pdata->goalieposS.x - pdata->oldgoalieposS.x)/halfFrameJump;
	pdata->goalievelS.y = (pdata->goalieposS.y - pdata->oldgoalieposS.y)/halfFrameJump;

	pdata->robot1velS.x = (pdata->robot1posS.x - pdata->oldrobot1posS.x)/halfFrameJump;
	pdata->robot1velS.y = (pdata->robot1posS.y - pdata->oldrobot1posS.y)/halfFrameJump;

	pdata->robot2velS.x = (pdata->robot2posS.x - pdata->oldrobot2posS.x)/halfFrameJump;
	pdata->robot2velS.y = (pdata->robot2posS.y - pdata->oldrobot2posS.y)/halfFrameJump;

	//-- transfer the present positions to old positions
	pdata->oldballposS = pdata->ballposS;
	pdata->oldgoalieposS = pdata->goalieposS;
	pdata->oldrobot1posS = pdata->robot1posS;
	pdata->oldrobot2posS = pdata->robot2posS;

	//-- copy ballpos to Gballpos
	pdata->GballposS = pdata->ballposS;

	return;
}

/***********************/
//-- All diagnostic functions
//-- Take Physical values and produce corresponding Screen values

void inversemapxy(floatPOINT *Screen, floatPOINT *Physical, commondata *pdata)
{
	Screen->x = Physical->x*(pdata->oppgoalbottom.x - pdata->homegoaltop.x)/Physical_X
					+ pdata->homegoaltop.x;
	Screen->y = pdata->rightbottom.y -
				Physical->y*(pdata->rightbottom.y - pdata->lefttop.y)/Physical_Y;
}

void PhysicaltoScreen(floatPOINT *Screen, floatPOINT *Physical, commondata *pdata)
{
	//-- Convert any physical coordinate to a screen coordinate

	if(pdata->game_area==RIGHT_AREA)//--if Right to Left (i.e (0,0) is topright
	{
		floatPOINT Rotated;
		//-- swap the coordinates and angle
		Rotated = rotatemapxyVal(Physical);
		inversemapxy(Screen, &Rotated, pdata);
	}
	else //-- if Left to Right (i.e (0,0) is bottomLeft
		inversemapxy(Screen, Physical, pdata);
}

floatPOINT rotatemapxyVal(floatPOINT *Physical)
{
	//-- Returns swapped BottomLeft (0,0) position with TopRight (150,130) position
	//-- and vice-versa 

	floatPOINT Rotated;
	Rotated.x = Physical_X - Physical->x;
	Rotated.y = Physical_Y - Physical->y;
	return Rotated;
}
/***********************/

//-- Parallax correction functions, using calculated physical image centre
//--
float parallaxCorrectionX(float OriginalX, commondata *pdata, float ObjectHeight)// OriginalX is the physical (cm) x position coordinate as received from the camera
{
	float CorrectedX;

	CorrectedX = (float)(pdata->PhysicalImageCentre.x - (pdata->PhysicalImageCentre.x - OriginalX)*(gCameraHeight - ObjectHeight)/gCameraHeight);

	return CorrectedX;
}

float parallaxCorrectionY(float OriginalY, commondata *pdata, float ObjectHeight)// OriginalY is the physical (cm) y position coordinate as received from the camera
{
	float CorrectedY;

	CorrectedY = (float)(pdata->PhysicalImageCentre.y - (pdata->PhysicalImageCentre.y - OriginalY)*(gCameraHeight - ObjectHeight)/gCameraHeight);

	return CorrectedY;
}


floatPOINT parallaxCorrection(floatPOINT *pOriginal, commondata *pdata, float ObjectHeight )
{
	//-- pOriginal is the pointer to physical (cm) position coordinates as received from the camera
	floatPOINT Corrected;

	Corrected.x = parallaxCorrectionX(pOriginal->x, pdata, ObjectHeight);
	Corrected.y = parallaxCorrectionY(pOriginal->y, pdata, ObjectHeight);

	return Corrected;
}

float distanceGap(floatPOINT *pA, floatPOINT *pB)
{
	float dx = pA->x - pB->x;
	float dy = pA->y - pB->y;
	return (float)sqrt(dx*dx+dy*dy);
}

float distanceGapI(POINT *pA, POINT *pB)
{
	float dx = (float)(pA->x - pB->x);
	float dy = (float)(pA->y - pB->y);
	return (float)sqrt(dx*dx+dy*dy);
}