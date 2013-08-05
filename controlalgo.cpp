//-- Filename : controlalgo.cpp
//-- Implements control algorithms

#include "stdAfx.h"
#include "commondata.h"
#include "math.h"
#include "controlalgo.h"
#include "map.h"
#include "myStrategy.h"

void angle(int which, float desiredAngle)
{
	float robotAngle;
	float angleError;
	float angvel;	//-- angular velocity
	float Ka;
	float Kad = (float)(0.2);
	float offset;
	int Vl=0, Vr=0;
	float Angle;
	float Ka70, Ka50, Ka30, Ka10, Ka5, Ka2, Ka0;

	switch(which)
	{
	case HGOALIE	:	robotAngle = globaldata.goalieangleS;
						angvel = globaldata.goalieangvel;
						break;
	case HROBOT1	:	robotAngle = globaldata.robot1angleS;
						angvel = globaldata.robot1angvel;
						break;
	case HROBOT2	:	robotAngle = globaldata.robot2angleS;
						angvel = globaldata.robot2angvel;
						break;
	}	//-- end of switch

	angleError = desiredAngle - robotAngle;

	while (angleError > 180)		//-- normalisation for -180 to +180
		angleError -= 360;
	while (angleError < -180)
		angleError += 360;

	if (angleError < -90)	//-- switch robot's front direction
	{
		angleError += 180;
	}
	else
		if (angleError > 90)
		{
			angleError -= 180;
		}

	float mulFactor = (float)0.88;	//1.1

	Ka70 = (float)0.2857*mulFactor;
	Ka50 = (float)0.3429*mulFactor;
	Ka30 = (float)0.40*mulFactor;
	Ka10 = (float)0.457*mulFactor;
	Ka5	= (float)0.2857*mulFactor;	//0.6857*mulFactor;
	Ka2 = (float)0.15*mulFactor;	//0.25*mulFactor;
	Ka0 = (float)0.10*mulFactor;	//0.257*mulFactor;

	//-- set the value of Ka based on absolute angle error
	if (fabs(angleError) > 70)
	{
		Angle = 70;
		//offset = (float) ((70-50)*Ka50 +(50-30)*Ka30 + (30-10)*Ka10 + (10-5)*Ka5 + (5-2)*Ka2 + 2*Ka0);
		offset = (float) (20*Ka50 + 20*Ka30 + 20*Ka10 + 5*Ka5 + 3*Ka2 + 2*Ka0);
		Ka = Ka70;
	}
	else
		if (fabs(angleError) > 50)
		{
			Angle = 50;
			//offset = (float)((50-30)*Ka30 + (30-10)*Ka10 + (10-5)*Ka5 + (5-2)*Ka2 + 2*Ka0);
			offset = (float)(20*Ka30 + 20*Ka10 + 5*Ka5 + 3*Ka2 + 2*Ka0);
			Ka = Ka50;
		}
		else
			if (fabs(angleError) > 30)
			{
				Angle = 30;
				//offset = (float)((30-10)*Ka10 + (10-5)*Ka5 + (5-2)*Ka2 + 2*Ka0);
				offset = (float)(20*Ka10 + 5*Ka5 + 3*Ka2 + 2*Ka0);
				Ka = Ka30;
				Kad = (float)0.10;
			}
			else
				if (fabs(angleError) > 10)
				{
					Angle = 10;
					//offset = (float)( (10-5)*Ka5 + (5-2)*Ka2 + 2*Ka0);
					offset = (float)(5*Ka5 + 3*Ka2 + 2*Ka0);
					Ka = Ka10;
					Kad = (float)0.10;
				}
				else 
					if (fabs(angleError) > 5)
					{
						Angle = 5;
						//offset = (float)( (5-2)*Ka2 + 2*Ka0);
						offset = (float)(3*Ka2 + 2*Ka0);
						Ka=(float) (Ka2 + fabs( (angleError-5.0)*(Ka5-Ka2)/5.0 ));
						Kad = (float)0.05;
					}
					else
						if (fabs(angleError) > 2)
						{
							Angle = 2;
							offset = (float)(2*Ka0);
							Ka= (float) (Ka0 + fabs( (angleError-2.0)*(Ka2-Ka0)/3.0 ));
							Kad = (float)0;
							if (angleError>0)
								angleError=angleError*angleError/(float)8.0;
							else angleError=-angleError*angleError/(float)8.0;
							Kad = 0;
						}
						else	//-- angleError <= 2
						{
							Angle = 0;
							offset = 0;
							Ka=(float) (fabs(angleError*Ka0/2.0));
							angleError=angleError*angleError*angleError/(float)8.0;
							Kad = 0;
						}

	if (angleError > 0)
	{
		Vl = (int) (-Ka*(angleError-Angle) + Kad*angvel - offset);
		Vr = -Vl;
	}
	else if (angleError < 0)
	{
		Vl = (int) (-Ka*(angleError+Angle) + Kad*angvel + offset);
		Vr = -Vl;
	}
	else	//-- angleError is 0
		Vl = Vr = 0;

	velocity(which, Vl, Vr);

	return;
}	//-- angle()

//-- angle() function exclusively for Goalie to make it nippier
void angleG(float desiredAngle)
{
	float robotAngle;
	float angleError;
	float angvel;	//-- angular velocity
	float Ka;
	float Kad = (float)(0.2);
	float offset;
	int Vl=0, Vr=0;
	float Angle;
	float Ka70, Ka50, Ka30, Ka10, Ka5, Ka2, Ka0;

	robotAngle = globaldata.goalieangleS;
	angvel = globaldata.goalieangvel;

	angleError = desiredAngle - robotAngle;

	while (angleError > 180)		//-- normalisation for -180 to +180
		angleError -= 360;
	while (angleError < -180)
		angleError += 360;

	if (angleError < -90)	//-- switch robot's front direction
	{
		angleError += 180;
	}
	else
		if (angleError > 90)
		{
			angleError -= 180;
		}

	float mulFactor = (float)1.25;

	Ka70 = (float)0.2857*mulFactor;
	Ka50 = (float)0.3429*mulFactor;
	Ka30 = (float)0.40*mulFactor;
	Ka10 = (float)0.457*mulFactor;
	Ka5	= (float)0.2857*mulFactor;	//0.6857*mulFactor;
	Ka2 = (float)0.15*mulFactor;	//0.25*mulFactor;
	Ka0 = (float)0.10*mulFactor;	//0.257*mulFactor;
	
	//-- set the value of Ka based on absolute angle error
	if (fabs(angleError) > 70)
	{
		Angle = 70;
		//offset = (float) ((70-50)*Ka50 +(50-30)*Ka30 + (30-10)*Ka10 + (10-5)*Ka5 + (5-2)*Ka2 + 2*Ka0);
		offset = (float) (20*Ka50 + 20*Ka30 + 20*Ka10 + 5*Ka5 + 3*Ka2 + 2*Ka0);
		Ka = Ka70;
	}
	else
		if (fabs(angleError) > 50)
		{
			Angle = 50;
			//offset = (float)((50-30)*Ka30 + (30-10)*Ka10 + (10-5)*Ka5 + (5-2)*Ka2 + 2*Ka0);
			offset = (float)(20*Ka30 + 20*Ka10 + 5*Ka5 + 3*Ka2 + 2*Ka0);
			Ka = Ka50;
		}
		else
			if (fabs(angleError) > 30)
			{
				Angle = 30;
				//offset = (float)((30-10)*Ka10 + (10-5)*Ka5 + (5-2)*Ka2 + 2*Ka0);
				offset = (float)(20*Ka10 + 5*Ka5 + 3*Ka2 + 2*Ka0);
				Ka = Ka30;
			}
			else
				if (fabs(angleError) > 10)
				{
					Angle = 10;
					//offset = (float)( (10-5)*Ka5 + (5-2)*Ka2 + 2*Ka0);
					offset = (float)(5*Ka5 + 3*Ka2 + 2*Ka0);
					Ka = Ka10;
				}
				else 
					if (fabs(angleError) > 5)
					{
						Angle = 5;
						//offset = (float)( (5-2)*Ka2 + 2*Ka0);
						offset = (float)(3*Ka2 + 2*Ka0);
						Ka=(float) (Ka2 + fabs( (angleError-5.0)*(Ka5-Ka2)/5.0 ));
						Kad = (float)0.05;
					}
					else
						if (fabs(angleError) > 2)
						{
							Angle = 2;
							offset = (float)(2*Ka0);
							Ka= (float) (Ka0 + fabs( (angleError-2.0)*(Ka2-Ka0)/3.0 ));
							Kad = (float)0;
							if (angleError>0)
								angleError=angleError*angleError/(float)8.0;
							else angleError=-angleError*angleError/(float)8.0;
						}
						else	//-- angleError <= 2
						{
							Angle = 0;
							offset = 0;
							Ka=(float) (fabs(angleError*Ka0/2.0));
							Kad = 0;
							angleError=angleError*angleError*angleError/(float)8.0;
						}

	if (angleError > 0)
	{
		Vl = (int) (-Ka*(angleError-Angle) + Kad*angvel - offset);
		Vr = -Vl;
	}
	else if (angleError < 0)
	{
		Vl = (int) (-Ka*(angleError+Angle) + Kad*angvel + offset);
		Vr = -Vl;
	}
	else	//-- angleError is 0
		Vl = Vr = 0;

	velocity(HGOALIE, Vl, Vr);

	return;
}	//-- angleG()


void position(int which, floatPOINT finalPos, float finalAngle, float finalVel)
{
	float dx, dy;
	floatPOINT robotPos, robotVel;
	float currentVel;
	float angleError;
	float robotAngle;
	float speedError;
	float desiredAngle;
	float distanceError;
	
	float Kd0;
	float Kd1;
	float Kd2;
	float Kd3;
	float Kd4;
	
	float Kd;
	float Ka = (float)0.20;
	float Kdd = 48;
	float d;
	
	float maxAngleError = 70; 
	int Vl=0, Vr=0; //-- left and right velocities 
	float D0 = (float)2.5; //-- CLOSEDISTANCE 
	float D1 = (float)20.0; //-- LONGDISTANCE 
	float D2 = (float)40.0; 
	float D3 = (float)60.0; //-- VERYLONGDISTANCE 
	
	switch(which)
	{
	case HGOALIE	:	
		robotAngle = globaldata.goalieangleS;
		robotVel = globaldata.goalievelS;
		robotAngle = globaldata.goalieangleS;
		break;
	case HROBOT1	:	
		robotAngle = globaldata.robot1angleS;					
		robotVel = globaldata.robot1velS;
		robotAngle = globaldata.robot1angleS;
		break;
	case HROBOT2	:	
		robotAngle = globaldata.robot2angleS;
		robotVel = globaldata.robot2velS;
		robotAngle = globaldata.robot2angleS;
		break;
	}	//-- end of switch
	
	dx = finalPos.x - robotPos.x; 
	dy = finalPos.y - robotPos.y; 
	distanceError = (float) sqrt(dx*dx + dy*dy); 
	currentVel = (float) sqrt(robotVel.x*robotVel.x + robotVel.y*robotVel.y); 
	speedError = finalVel - currentVel; 
	
	if(distanceError < D0) //---- when near the target position, correct the angle 
		desiredAngle = finalAngle; 
	else 
		desiredAngle = (float) (atan2(dy, dx)*180/PI); //-- in degrees 
	angleError = desiredAngle - robotAngle; 
	while (angleError > 180) //-- normalisation for -180 to +180 
		angleError -= 360; 
	while (angleError < -180) 
		angleError += 360; 
	if (-maxAngleError < angleError && angleError < maxAngleError) 
		d = 1; 
	else 
		if ((180 >= angleError && angleError > 180-maxAngleError) || 
			(-180 < angleError && angleError <= -180+maxAngleError) ) 
		{ 
			if (angleError < -90) //-- switch robot's front direction 
			{ 
				angleError += 180; 
				d = -1; 
			} 
			else 
				if (angleError > 90) 
				{ 
					angleError -= 180; 
					d = -1; 
				} 
		} 
		else 
			d = 0; 
		//-- factor to multiply the Kd values 
		float mulFactor = (float) 1.0; 
		Kd0 = (float)(3.8*mulFactor); //-- 4.5 
		Kd1 = (float)(3.8*mulFactor); //-- 4.0 
		Kd2 = (float)(0.8*mulFactor); 
		Kd3 = (float)(0.2*mulFactor); 
		Kd4 = (float)(0.1*mulFactor);
		
		if (distanceError > D3) //-- 60 cms 
		{ 
			Kd = Kd4; 
			Kdd = (float)(0.05 * Kdd); 
		} 
		else 
			if (distanceError > D2) //-- 40 cms 
			{ 
				Kd = Kd3; 
				Kdd = (float)(0.05 * Kdd); 
			} 
			else 
				if (distanceError > D1) //-- 20 cms 
				{ 
					Kd = Kd2; 
					Kdd = (float)(0.3 * Kdd); 
				} 
				else 
					if (distanceError>=D0) //-- 2.5 cms 
					{ 
						Kd = Kd1; 
						Kdd = (float)(Kdd*0.5); 
					} 
					else //-- distanceError<D0 (2.5 cms) i.e. very close to final position, just turn 
					{ 
						angle(which, finalAngle); 
					} 
					if (distanceError>=D0) //-- 2.5 cms 
					{ 
						Vl = (int) (Kd*distanceError + Kdd*speedError)*d - Ka*angleError; 
						Vr = (int) (Kd*distanceError + Kdd*speedError)*d + Ka*angleError; 
						velocity(which, Vl, Vr); 
					} 
					if(d==0 && distanceError>=D0) //-- no linear movement, just turn 
					{ 
						angle(which, desiredAngle); 
					} 
					
					return;
}	//-- position()


//-- position() function exclusively for Goalie -------------------
void positionG(floatPOINT finalPos, float finalAngle, float finalVel)
{
	int Vl=0, Vr=0;

	velocity(HGOALIE, Vl, Vr);
	return;
}	//-- positionG()


void velocity(int which, int Vl, int Vr)
{
	//-- Velocity Scaling NOT to be done for Goalie
	if (which != HGOALIE)
	{
		if(Vl*Vr>0 && Vl>-127 && Vl<127 && Vr>-127 && Vr<127)
		{
			Vl = (int) (Vl*gVelocityScaling + 0.5);
			Vr = (int) (Vr*gVelocityScaling + 0.5);
		}
	}

	if (Vl < -127) Vl = -127;		//-- clamp velocity between
	else if (Vl > 127) Vl = 127;	//-- -127 and +127

	if (Vr < -127) Vr = -127;		//-- clamp velocity between
	else if (Vr > 127) Vr = 127;	//-- -127 and +127

	if (!gfoundBall && gStopRobotsWhenBallLost)
	{
		//-- Stop the robot because the ball is lost
		Vl = 0;
		Vr = 0;
	}

	if (globaldata.ballposS.x > Physical_X + 2)	
	{
		//-- Stop the robot because the ball is past the opponent goalline
		Vl = 0;
		Vr = 0;
	}

	switch(which)
	{
	case HGOALIE	:	if (gfoundGoalie)
						{
							globaldata.packet[2] = (char)Vl;
							globaldata.packet[3] = (char)Vr;
						}
						else	//-- Goalie not found
						{
							globaldata.packet[2] = (char)0;
							globaldata.packet[3] = (char)0;
						}
						globaldata.GVelSet = TRUE;
						break;

	case HROBOT1	:	if (gfoundR1)
						{
							globaldata.packet[6] = (char)Vl;
							globaldata.packet[7] = (char)Vr;
						}
						else	//-- Robot1 not found
						{
							globaldata.packet[6] = (char)0;
							globaldata.packet[7] = (char)0;
						}
						globaldata.R1VelSet = TRUE;
						break;

	case HROBOT2	:	if (gfoundR2)
						{
							globaldata.packet[10] = (char)Vl;
							globaldata.packet[11] = (char)Vr;
						}
						else	//-- Robot2 not found
						{
							globaldata.packet[10] = (char)0;
							globaldata.packet[11] = (char)0;
						}
						globaldata.R2VelSet = TRUE;
						break;
	}	//-- end of switch

	return;
}	//-- velocity()

void escapeGoal(int which)
{
	float robotAngle;
	floatPOINT robotPos;
	float absRobotAngle;

	float G_OFFSET = (float)7.5;
	int G_ANGLE_BOUND=60; //-- 40 gets stuck when close to the wall with a small angle
	float G_BOUND = (float)5.0;

	int PUMP_LARGE=20;//---- Turning parameters
	int PUMP_SMALL=5;

	switch(which)
	{
	case HGOALIE	:	robotAngle = globaldata.goalieangleS;
						robotPos = globaldata.goalieposS;
						break;
	case HROBOT1	:	robotAngle = globaldata.robot1angleS;
						robotPos = globaldata.robot1posS;
						break;
	case HROBOT2	:	robotAngle = globaldata.robot2angleS;
						robotPos = globaldata.robot2posS;
						break;
	}	//-- end of switch

	if(robotPos.x < 3.0) //---- Robot is stuck inside own goal
	{
		floatPOINT goaliePos;
		goaliePos.x = (float) G_OFFSET - gGoalieActionParameters.GXcompensation;  //-- G_OFFSET is 7.5 cms
		goaliePos.y = Physical_Yby2;
		if (which == HGOALIE)
			positionG(goaliePos, 90, 0);
		else
			position(which, goaliePos, 90, 0);
	}
	else //-- robotPos.x >= 3.0
	{
		absRobotAngle = (float)fabs(robotAngle);

		if(robotPos.y < Physical_Yby2) //---- Bottom half of goal
		{
			if(absRobotAngle > 180 - G_ANGLE_BOUND && //-- robot is facing the wall too much
				robotPos.x < G_BOUND ) //-- and within the bound distance to the goal
			{
				//---- Spin anti-clockwise and move backwards
				velocity(which, -PUMP_LARGE, -PUMP_SMALL);
			}
			else if(absRobotAngle < G_ANGLE_BOUND && //-- robot is facing the wall too much
				robotPos.x < G_BOUND ) //-- and within the bound distance to the goal
			{
				//---- Spin anti-clockwise and move forwards
				velocity(which, PUMP_SMALL, PUMP_LARGE);
			}

		}
		else //---- Top half of goal  (robotPos.y >= Physical_Yby2)
		{
			if(absRobotAngle > 180 - G_ANGLE_BOUND && //-- robot is facing the wall too much
				robotPos.x < G_BOUND ) //-- and within the bound distance to the goal
			{
				//---- Spin clockwise and move backwards
				velocity(which, -PUMP_SMALL, -PUMP_LARGE);
			}
			else if(absRobotAngle < G_ANGLE_BOUND && //-- robot is facing the wall too much
				robotPos.x < G_BOUND ) //-- and within the bound distance to the goal
			{
				//---- Spin clockwise and move forwards
				velocity(which, PUMP_LARGE, PUMP_SMALL);
			}
		}
	}
}	//---- escapeGoal()

void avoidBound(int which, floatPOINT finalPos)
{
	int ANGLE_BOUND=40;

	float DISTANCE_BOUND=(float)5.5;	//7.5 //8.5	//9.5	

	float robotAngle, angleError;
	float desiredAngle;
	floatPOINT robotPos;
	float dx, dy;
	//-- speed to back out of wall
	float Vc = 20;
	float Ka = (float)0.2;
	int Vl, Vr;
	float absRobotAngle;
	switch(which)
	{
	case HGOALIE	:	robotAngle = globaldata.goalieangleS;
						robotPos = globaldata.goalieposS;
						break;
	case HROBOT1	:	robotAngle = globaldata.robot1angleS;
						robotPos = globaldata.robot1posS;
						break;
	case HROBOT2	:	robotAngle = globaldata.robot2angleS;
						robotPos = globaldata.robot2posS;
						break;
	}	//-- end of switch

	dx = finalPos.x - robotPos.x;
	dy = finalPos.y - robotPos.y;

	if ( (dx==0) && (dy==0) )//-- check for small dx and dy
		desiredAngle = 90;
	else
		desiredAngle = (float) (atan2(dy, dx)*180/PI);

	angleError = desiredAngle - robotAngle;

	while(angleError > 180)		//-- normalisation for -180 to +180
		angleError -= 360;
	while(angleError < -180)
		angleError += 360;

	//---- Top and Bottom boundary avoidance
	//-- Top boundary
	if(robotAngle > -90 - ANGLE_BOUND &&	//-- robot is facing away from 
		robotAngle < -90 + ANGLE_BOUND &&	//-- the wall too much
		robotPos.y > Physical_Y - DISTANCE_BOUND ) //-- and within the bound distance to the top wall
	{
		Vr = (int)(Vc + Ka*angleError);
		Vl = (int)(Vc - Ka*angleError);
		velocity(which, Vl, Vr); //---- Spin correcting angle error
								 //---- and move forwards
	}
	else if(robotAngle > 90 - ANGLE_BOUND && //-- robot is facing towards the wall too much
		robotAngle < 90 + ANGLE_BOUND &&
		robotPos.y > Physical_Y - DISTANCE_BOUND ) //-- and within the bound distance to the top wall
	{
		Vr = (int)(-Vc + Ka*angleError);
		Vl = (int)(-Vc - Ka*angleError);
		velocity(which, Vl, Vr); //---- Spin correcting angle error
								 //---- and move backwards
	}
	//-- Bottom boundary
	else if(robotAngle > -90 - ANGLE_BOUND && //---- robot is facing towards 
		robotAngle < -90 + ANGLE_BOUND &&	  //---- the wall too much
		robotPos.y < DISTANCE_BOUND )	  //---- and within the bound distance to the bottom wall
	{
		Vr = (int)(-Vc + Ka*angleError);
		Vl = (int)(-Vc - Ka*angleError);
		velocity(which, Vl, Vr);	//---- Spin correcting angle error
									//---- and move backwards
	}
	else if(robotAngle > 90 - ANGLE_BOUND && //---- robot is facing away from 
		robotAngle < 90 + ANGLE_BOUND &&	 //---- the wall too much
		robotPos.y < DISTANCE_BOUND )	 //---- and within the bound distance to the bottom wall
	{
		Vr = (int)(Vc + Ka*angleError);
		Vl = (int)(Vc - Ka*angleError);
		velocity(which, Vl, Vr);//---- Spin correcting angle error
								//---- and move forwards
	}

	
	absRobotAngle = (float)fabs(robotAngle);	
	//---- Left boundary avoidance
	if(absRobotAngle < ANGLE_BOUND && // robot is facing away from left wall too much
		robotPos.x < DISTANCE_BOUND &&//and within the bound distance to the left wall
		robotPos.y > Physical_Yby2 + G_LENGTH/2 ) // and above the top of the goal post
	{
		Vr = (int)(Vc + Ka*angleError);
		Vl = (int)(Vc - Ka*angleError);
		velocity(which, Vl, Vr);//Spin correcting angle error
								//and move forwards
	}
	else if(absRobotAngle > 180 - ANGLE_BOUND && // robot is facing towards left wall too much
		robotPos.x < DISTANCE_BOUND &&//and within the bound distance to the left wall
		robotPos.y > Physical_Yby2 + G_LENGTH/2 ) // and above the top of the goal post
	{
		Vr = (int)(-Vc + Ka*angleError);
		Vl = (int)(-Vc - Ka*angleError);
		velocity(which, Vl, Vr);//Spin correcting angle error
								//and move backwards
	}
	else if(absRobotAngle < ANGLE_BOUND && // robot is facing away from left wall too much
		robotPos.x < DISTANCE_BOUND &&//and within the bound distance to the left wall
		robotPos.y < Physical_Yby2 - G_LENGTH/2 ) // and below the bottom of the goal post
	{
		Vr = (int)(Vc + Ka*angleError);
		Vl = (int)(Vc - Ka*angleError);
		velocity(which, Vl, Vr);//Spin correcting angle error
								//and move forwards
	}
	else if(absRobotAngle > 180 - ANGLE_BOUND && // robot is facing towards left wall too much
		robotPos.x < DISTANCE_BOUND &&//and within the bound distance to the left wall
		robotPos.y < Physical_Yby2 - G_LENGTH/2 ) // and below the bottom of the goal post
	{
		Vr = (int)(-Vc + Ka*angleError);
		Vl = (int)(-Vc - Ka*angleError);
		velocity(which, Vl, Vr);//Spin correcting angle error
								//and move backwards
	}

	//---- Right boundary avoidance
	if(absRobotAngle < ANGLE_BOUND && // robot is facing towards right wall too much
		robotPos.x > Physical_X - DISTANCE_BOUND &&//and within the bound distance to the right wall
		robotPos.y > Physical_Yby2 + G_LENGTH/2 ) // and above the top of the goal post
	{
		Vr = (int)(-Vc + Ka*angleError);
		Vl = (int)(-Vc - Ka*angleError);
		velocity(which, Vl, Vr);//Spin correcting angle error
								//and move backwards
	}
	else if(absRobotAngle > 180 - ANGLE_BOUND && // robot is facing away from right wall too much
		robotPos.x > Physical_X - DISTANCE_BOUND &&//and within the bound distance to the right wall
		robotPos.y > Physical_Yby2 + G_LENGTH/2 ) // and above the top of the goal post
	{
		Vr = (int)(Vc + Ka*angleError);
		Vl = (int)(Vc - Ka*angleError);
		velocity(which, Vl, Vr);//Spin correcting angle error
								//and move forwards
	}
	else if(absRobotAngle < ANGLE_BOUND && // robot is facing towards right wall too much
		robotPos.x > Physical_X - DISTANCE_BOUND &&//and within the bound distance to the right wall
		robotPos.y < Physical_Yby2 - G_LENGTH/2 ) // and below the bottom of the goal post
	{
		Vr = (int)(-Vc + Ka*angleError);
		Vl = (int)(-Vc - Ka*angleError);
		velocity(which, Vl, Vr);//Spin correcting angle error
								//and move backwards
	}
	else if(absRobotAngle > 180 - ANGLE_BOUND && // robot is facing away from right wall too much
		robotPos.x > Physical_X - DISTANCE_BOUND &&//and within the bound distance to the right wall
		robotPos.y < Physical_Yby2 - G_LENGTH/2 ) // and below the bottom of the goal post
	{
		Vr = (int)(Vc + Ka*angleError);
		Vl = (int)(Vc - Ka*angleError);
		velocity(which, Vl, Vr);//Spin correcting angle error
								//and move forwards
	}

	return;
}	//---- avoidBound()


BOOL ownArea(int which)
{	//-- To check if robot is in own penalty area

	floatPOINT robotPos;
	float NEARPOS, NEAR_Y_OFFSET;
	floatPOINT nearpoint;
	floatPOINT homegoalbottom;
	BOOL thisRemoved;

	homegoalbottom.x = (float)globaldata.homegoalbottom.x;
	homegoalbottom.y = (float)globaldata.homegoalbottom.y;
	mapxy(&homegoalbottom, &nearpoint, &globaldata);
	NEARPOS = nearpoint.x + (float)2.0;	//4.0;	//5.5;
	NEAR_Y_OFFSET = (float)fabs(nearpoint.y - Physical_Yby2) + (float)2.0;	//4.0;
	switch(which)
	{
	case HGOALIE	:	robotPos = globaldata.goalieposS;
						thisRemoved = gRemoved.Goalie;
						break;
	case HROBOT1	:	robotPos = globaldata.robot1posS;
						thisRemoved = gRemoved.Robot1;
						break;
	case HROBOT2	:	robotPos = globaldata.robot2posS;
						thisRemoved = gRemoved.Robot2;
						break;
	}	//-- end of switch

	if(	robotPos.x < NEARPOS
		&& robotPos.y > (Physical_Yby2 - NEAR_Y_OFFSET)
		&& robotPos.y < (Physical_Yby2 + NEAR_Y_OFFSET)
		&& !thisRemoved)

		return true;
	else
		return false;

}	//-- ownArea(int which)


BOOL oppArea(int which)
{	//---- To check if robot is in opponents penalty area

	floatPOINT robotPos;
	float NEARPOS, NEAR_Y_OFFSET;
	floatPOINT nearpoint;
	floatPOINT homegoalbottom;
	BOOL thisRemoved;

	homegoalbottom.x = (float)globaldata.homegoalbottom.x;
	homegoalbottom.y = (float)globaldata.homegoalbottom.y;
	mapxy(&homegoalbottom, &nearpoint, &globaldata);
	NEARPOS = nearpoint.x + (float)4.0;	//5.5;
	NEAR_Y_OFFSET = (float)fabs(nearpoint.y - Physical_Yby2) + (float)4.0;
	switch(which)
	{
	case HGOALIE	:	robotPos = globaldata.goalieposS;
						thisRemoved = gRemoved.Goalie;
						break;
	case HROBOT1	:	robotPos = globaldata.robot1posS;
						thisRemoved = gRemoved.Robot1;
						break;
	case HROBOT2	:	robotPos = globaldata.robot2posS;
						thisRemoved = gRemoved.Robot2;
						break;
	}	//-- end of switch

	if(	robotPos.x > (Physical_X - NEARPOS)
		&& robotPos.y > (Physical_Yby2 - NEAR_Y_OFFSET)
		&& robotPos.y < (Physical_Yby2 + NEAR_Y_OFFSET)
		&& !thisRemoved)

		return true;
	else
		return false;
}	//-- oppArea()

void avoidGoalAreas(int which, floatPOINT finalPos)
{
	floatPOINT robotPos;
	floatPOINT nearpoint;
	floatPOINT movePos;
	floatPOINT homegoalbottom;
	float NEARPOS;
	int NUM_ROBOTS = 3;
	homegoalbottom.x = (float)globaldata.homegoalbottom.x;
	homegoalbottom.y = (float)globaldata.homegoalbottom.y;
	mapxy(&homegoalbottom, &nearpoint, &globaldata);
	NEARPOS = nearpoint.x;

	switch(which)
	{
	case HGOALIE	:	robotPos = globaldata.goalieposS;
						break;
	case HROBOT1	:	robotPos = globaldata.robot1posS;
						break;
	case HROBOT2	:	robotPos = globaldata.robot2posS;
						break;
	}	//-- end of switch

	//------ Our own goal area

	if( ownArea(which) ) //-- this robot is in our goal area
	{
		//---- back out
		if (finalPos.x < NEARPOS + ROBOTWIDTHby2)
		{
			movePos.y = finalPos.y + (finalPos.y-robotPos.y)*((float)2.0/3);

			movePos.x = NEARPOS + (float)ROBOTWIDTHby2;
		}
		else
			movePos = finalPos;

		if (which == HGOALIE)
			positionG(movePos, 90, 0);
		else
			position(which, movePos, 90, 0);
	}

	//----- Opponent's goal area -------------------------------------
	if(oppArea(which) && ( oppArea((which+1)%NUM_ROBOTS) ||
		oppArea((which+2)%NUM_ROBOTS) )) // take care when modifying for different number of robots
	// another robot in area
	// this robot in area
	{
		//-- back off
		movePos.y = finalPos.y+ (finalPos.y-robotPos.y)*((float)2.0/3);
		movePos.x = Physical_X - (NEARPOS + 8); // Adjust this value (8) for how far 
												//out the goal area you want to back off
		position(which, movePos, 90, 0);
	}

	return;
}	//---- avoidGoalAreas()

void spin(int which, int direction)
{
	int lVel, rVel;

	switch (direction)
	{
	case CLOCKWISE :	lVel = (int)(48 * gSpinVelocityScaling + 0.5);
						//rVel = (int)(-48 * gSpinVelocityScaling + 0.5);
						rVel = -lVel;
						break;
	case ANTICLOCKWISE :	rVel = (int)(48 * gSpinVelocityScaling + 0.5);
							//lVel = (int)(-48 * gSpinVelocityScaling + 0.5);
							lVel = -rVel;
							break;
	}
	
	velocity(which, lVel, rVel);
	return;
}	//---- spin()

void avoidGoalie(int which)
{
	floatPOINT robotPos, GPos, finalPos;
	float dx, dy, distanceError;

	GPos = globaldata.goalieposS;
	switch(which)
	{
	case HROBOT1	:	robotPos = globaldata.robot1posS;
						break;
	case HROBOT2	:	robotPos = globaldata.robot2posS;
						break;
	}

	dx = GPos.x - robotPos.x;
	dy = GPos.y - robotPos.y;
	distanceError = (float) sqrt(dx*dx + dy*dy);

	if (distanceError < 10)	//-- robot is very close to Goalie
							//-- so separate them
	{
		if (robotPos.y >= GPos.y)	//-- robot above goalie
		{
			finalPos.y = robotPos.y + 12;
			if (robotPos.x <= 15)	//-- robot inside goalarea
				finalPos.x = robotPos.x + 15;
			else
			{
				if (robotPos.x >= GPos.x)	//-- robot right of goalie
					finalPos.x = robotPos.x + 15;
				else	//-- robot left of goalie
					finalPos.x = robotPos.x - 15;
			}
		}
		else	//-- robot below goalie
		{
			finalPos.y = robotPos.y - 12;
			if (robotPos.x <= 15)	//-- robot inside goalarea
				finalPos.x = robotPos.x + 15;
			else
			{
				if (robotPos.x >= GPos.x) //-- robot right of goalie
					finalPos.x = robotPos.x + 15;
				else	//-- robot left of goalie
					finalPos.x = robotPos.x - 15;
			}
		}
		position(which, finalPos, 0, 0);
	}

	return;
}	//-- avoidGoalie()

void separateRobots(void)
{
	floatPOINT R1pos, R2pos;
	floatPOINT R1GoTopos, R2GoTopos;
	float dx, dy, distanceError;

	R1pos = globaldata.robot1posS;
	R2pos = globaldata.robot2posS;

	dx = R1pos.x - R2pos.x;
	dy = R1pos.y - R2pos.y;
	distanceError = (float) sqrt(dx*dx + dy*dy);

	if (distanceError < 8)	//-- robots are very close
								//-- so separate them
	{
		if (R1pos.y >= R2pos.y)	//-- R1 is above R2
		{
			R1GoTopos.y = R1pos.y + 2;	//-- R1 go up
			R2GoTopos.y = R2pos.y - 2;	//-- R2 go down

			if (R1pos.x <= R2pos.x)	//-- R1 is left of R2
			{
				R1GoTopos.x = R1pos.x - 2;	//-- R1 go left
				R2GoTopos.x = R2pos.x + 2;	//-- R2 go right
			}
			else	//-- R1 is right of R2
			{
				R1GoTopos.x = R1pos.x + 2;	//-- R1 go right
				R2GoTopos.x = R2pos.x - 2;	//-- R2 go left
			}
		}
		else		//-- R1 is below R2
		{
			R1GoTopos.y = R1pos.y - 2;	//-- R1 go down
			R2GoTopos.y = R2pos.y + 2;	//-- R2 go up

			if (R1pos.x <= R2pos.x)	//-- R1 is left of R2
			{
				R1GoTopos.x = R1pos.x - 2;	//-- R1 go left
				R2GoTopos.x = R2pos.x + 2;	//-- R2 go right
			}
			else	//-- R1 is right of R2
			{
				R1GoTopos.x = R1pos.x + 2;	//-- R1 go right
				R2GoTopos.x = R2pos.x - 2;	//-- R2 go left
			}
		}

		position(HROBOT1, R1GoTopos, 0, 0);
		position(HROBOT2, R2GoTopos, 0, 0);

	}
	return;
}	//-- separateRobots()

void turnAtWalls(int which)
{
	floatPOINT robotPos, Ballpos;
	float robotAngle;
	float dx, dy, distanceError;

	switch(which)
	{
	case HROBOT1	:	robotPos = globaldata.robot1posS;
						robotAngle = globaldata.robot1angleS;
						break;
	case HROBOT2	:	robotPos = globaldata.robot2posS;
						robotAngle = globaldata.robot2angleS;
						break;
	}
	Ballpos = globaldata.ballposS;

	dx = robotPos.x - Ballpos.x;
	dy = robotPos.y - Ballpos.y;
	distanceError = (float) sqrt(dx*dx + dy*dy);

	if (distanceError < 7.5)	//-- robot very close to ball
	{
		//-- is ball along upper wall?
		if (Ballpos.y >= Physical_Y - 5)
		{
			if ( (Ballpos.x > robotPos.x - ROBOTWIDTHby2) &&
				 (Ballpos.x < robotPos.x + ROBOTWIDTHby2)
				)
			{
				if (Ballpos.x < Physical_Xby2)
					spin(which, CLOCKWISE);
				else
				{
					robotAngle -= 15;
					angle(which, robotAngle);
				}
			}
		}
		else
		//-- is ball along lower wall?
		if (Ballpos.y <= 5)
		{
			if ( (Ballpos.x > robotPos.x - ROBOTWIDTHby2) &&
				 (Ballpos.x < robotPos.x + ROBOTWIDTHby2)
				)
			{
				if (Ballpos.x < Physical_Xby2)
					spin(which, ANTICLOCKWISE);
				else
				{
					robotAngle += 15;
					angle(which, robotAngle);
				}
			}
		}

		//-- is the ball along the right wall?
		if (Ballpos.x > Physical_X - 10)
		{
			//-- upper half
			if (Ballpos.y < Physical_Y-12 && 
				Ballpos.y > Physical_Yby2 + 20 &&
				Ballpos.y <= robotPos.y + ROBOTWIDTHby2 &&
				Ballpos.y >= robotPos.y - ROBOTWIDTHby2)
			{
				robotAngle -= 15;
				angle(which, robotAngle);
			}
			//-- lower half
			else
			if (Ballpos.y > 12 && 
				Ballpos.y < Physical_Yby2 - 20 &&
				Ballpos.y <= robotPos.y + ROBOTWIDTHby2 &&
				Ballpos.y >= robotPos.y - ROBOTWIDTHby2)
			{
				robotAngle += 15;
				angle(which, robotAngle);
			}
		}

	}	//-- if (distanceError < 7.5)

	return;
}	//-- turnAtWalls()