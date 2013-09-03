//-- Filename : commondata.h

#if !defined(COMMONDATA_INCLUDED_)
#define COMMONDATA_INCLUDED_

#include "fbus.h"
#include "afxwin.h"
//#include "BehaviourGoalie.h"
//#include "BehaviourRobot.h"
class CGoalieAction;
class RobotBehaviour;

enum play_area {LEFT_AREA, RIGHT_AREA};
enum Diagnostic_Level {OFF, LOW, HIGH};
enum colours {NoCOL, BALLCOL, ROBOT1COL, ROBOT2COL, TEAMCOL, OPPOCOL};

//-- added for robot placements before game ------------------------
enum startPhase {KICKSTART, GOALKICK, PENALTY, FREEKICK, FREEBALL};
enum whosePossession {HOME, OPPONENT};
enum whichQuadrant {TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT};
//------------------------------------------------------------------
enum FieldType {ODD,EVEN};
//-- 20 x 20 window around the capture point will be zoomed
#define CAPSIZE	10
#define MAXROBOTS 3
	//-- maximum number of robots in the game

#define MAXSTRING 40

struct floatPOINT
{
	float x;
	float y;
};

struct commondata
{	
	CWnd *pmainwindow;		//-- pointer to the main window
	BYTE diagnostics;		//-- Diagnostic level OFF, LOW, HIGH
	DWORD timeDiff;			//-- to monitor time difference

	BOOL coloursLoaded;

	//-- average colours ------------------
	COLORREF ballcol;
	COLORREF robot1col;
   	COLORREF robot2col;
   	COLORREF teamcol;
	COLORREF oppocol;
	
	//-- RGB components of each colour -----
	BYTE ballcolR, ballcolG, ballcolB;
	BYTE robot1colR, robot1colG, robot1colB;
	BYTE robot2colR, robot2colG, robot2colB;
	BYTE teamcolR, teamcolG, teamcolB;
	BYTE oppocolR, oppocolG, oppocolB;

	BYTE ballcolYmin, ballcolYmax;
	BYTE ballcolUmin, ballcolUmax;
	BYTE ballcolVmin, ballcolVmax;

	BYTE robot1colYmin, robot1colYmax;
	BYTE robot1colUmin, robot1colUmax;
	BYTE robot1colVmin, robot1colVmax;

	BYTE robot2colYmin, robot2colYmax;
	BYTE robot2colUmin, robot2colUmax;
	BYTE robot2colVmin, robot2colVmax;

	BYTE teamcolYmin, teamcolYmax;
	BYTE teamcolUmin, teamcolUmax;
	BYTE teamcolVmin, teamcolVmax;

	BYTE oppocolYmin, oppocolYmax;
	BYTE oppocolUmin, oppocolUmax;
	BYTE oppocolVmin, oppocolVmax;


	floatPOINT ballpos;
	floatPOINT goaliepos;
	floatPOINT robot1pos;
	floatPOINT robot2pos;

	floatPOINT teamcolpos1;
	floatPOINT teamcolpos2;
	floatPOINT teamcolpos3;

	floatPOINT oldballpos;
	floatPOINT oldgoaliepos;
	floatPOINT oldrobot1pos;
	floatPOINT oldrobot2pos;

	floatPOINT ballvel;	//-- linear velocities
	floatPOINT goalievel;
	floatPOINT robot1vel;
	floatPOINT robot2vel;

	float goalieangle;
	float robot1angle;
	float robot2angle;
	float ballangle;

	float oldgoalieangle;
	float oldrobot1angle;
	float oldrobot2angle;

	float goalieangvel;	//-- angular velocities
	float robot1angvel;
	float robot2angvel;

	//-- Opponent's color patch position is also its robot position
	floatPOINT oppocolpos1;	//-- position of opponent colour patch 1
	floatPOINT oppocolpos2;	//-- position of opponent colour patch 2
	floatPOINT oppocolpos3;	//-- position of opponent colour patch 3
	//-- Opponents ------------------------------------------------

	POINT lefttop;			//-- field lefttop
	POINT rightbottom;		//-- field rightbottom
	POINT homegoaltop;
	POINT homegoalbottom;
	POINT oppgoaltop;
	POINT oppgoalbottom;

	BOOL start;		//-- start/stop tracking and transmission
	BOOL update;	//-- to update the coordinates and angles
					//-- of the robots to the screen
	BOOL Bkcolour;	//-- Black background colour
	BOOL DisplayBoundaries;	//-- Display boundaries for guidance

	short game_area;	//-- LEFT_AREA or RIGHT_AREA

	BOOL FullTrackingOnly;	//-- TRUE if only full tracking requested

	UINT FullScan;
	UINT Team;
	UINT TeamFull;
	UINT Ball;
	UINT BallFull;
	UINT FrameCount;

	//-- ADDED FOR STRATEGY -----------
	floatPOINT ballposS;
	floatPOINT GballposS;	//-- ball position used by the goalie
							//-- normally the same as ballposS
	floatPOINT StartBallPosS;
	floatPOINT goalieposS;
	floatPOINT robot1posS;
	floatPOINT robot2posS;

	//-- for diagnostics
	floatPOINT gotoPosR1;	//-- position of where the robots should go
	floatPOINT gotoPosR2;
	floatPOINT gotoPosG;

	floatPOINT oldballposS;
	floatPOINT oldgoalieposS;
	floatPOINT oldrobot1posS;
	floatPOINT oldrobot2posS;

	floatPOINT ballvelS;
	floatPOINT goalievelS;
	floatPOINT robot1velS;
	floatPOINT robot2velS;

	float goalieangleS;
	float robot1angleS;
	float robot2angleS;
	float ballangleS;

	//-- Physical coordinates of the Opponent robot positions ---
	floatPOINT opporobot1posS;
	floatPOINT opporobot2posS;
	floatPOINT opporobot3posS;
	//-- Opponents ----------------------------------------------

	//---- added for communication
	char packet[12];		//-- current raw packet
	char encodedPacket[18];	//-- Manchester encoded packet
	int comport;		//-- com port : COM1 or COM2
	HANDLE hcomport;	//-- handle to communication port

	BOOL LUTupdated;	//-- is LUT updated?
	int SetBoundary;	//-- variable to track if game area,homegoal
						//-- area, or oppo goal area is selected

	POINT capPoint;		//-- Coordinates of the point clicked within
						//-- the capture window for zooming

	//-- behaviour state for individual robots
	int GState;		//-- for goal keeper behaviour

	int R1State;	//-- for defender behaviour
	int R2State;	//-- for striker behaviour

	//-- state for position robots action in CPlaceRobots
	int PositionState;

	//-- Used for the parallax calculation
	floatPOINT PhysicalImageCentre;

	BOOL timer1_installed;	//-- is timer installed for colour testing?
	BOOL timer2_installed;	//-- is timer installed for game area?

	BOOL colTuning;//-- Tuning mode on or not (controls stretch build display)
	BOOL fullFrame;	//-- process full image (ie. complete frame)
					//-- or ODD/EVEN field separately


	BOOL GVelSet, R1VelSet, R2VelSet;	//-- is the velocity set for the robots?

	BOOL IRQEnabled;	//-- has the IRQ been enabled?

	float goalieOldDistError;
	float robot1OldDistError;
	float robot2OldDIstError;

	//ELLIOT
	floatPOINT predicted;
	float ballAngleAve;

	//BEN
	float ballXAve;

	// Hamish
	
#define ballVelNSamples 10
	floatPOINT ballVelSamples[ballVelNSamples];
	int ballVelIndex;

	// These are used to maintain the same instances
	/*CGoalieAction  *gBehaviour;
	RobotBehaviour *r1Behaviour;
	RobotBehaviour *r2Behaviour;*/

};	//-- end of structure commondata

struct not_found_count
{
	int Goalie;
	int Robot1;
	int Robot2;
};

struct removed_robots
{
	BOOL Goalie;
	BOOL Robot1;
	BOOL Robot2;
};

struct startPhaseVal	//-- values for the start phase
{
	int kickspeed;
	float kickdistance;
};

//-- for placement of robots before the game starts
struct StartPosition
{
	int StartPhase;		//-- Kick start, Goal Kick, Penaly, Free Kick, Free Ball
	int whosePossession;//-- Home or Opponents
	int whichQuadrant;	//-- top-left, top-right, bottom-left, bottom-right
	int shootPenaltyWhere; // Kick Left, Kick Rihgt, Kick Centre
};

//-- Tuning Parameters for CGoalieAction class
struct GoalieActionparameters
{
	int GBehaviour;		//-- conservative, normal, aggressive
	float GXcompensation;
};


extern commondata globaldata;
extern BYTE LUT[256*256*256L];	//-- Look Up Table
extern int gMinPatchSizeTeam;	//-- minimum patch size for Team colour
extern int gMinPatchSizeCol1;	//-- minimum patch size for colour1
extern int gMinPatchSizeCol2;	//-- minimum patch size for colour2
extern int gMinPatchSizeOppo;	//-- minimum patch size for Oppo colour
extern int gMinPatchSizeBall;	//-- minimum patch size for Ball colour

extern int gNumRobots;			//-- number of robots in play
//-- count of how many times a particular robot is not found
extern not_found_count gNotFoundCount;
extern removed_robots gRemoved;	//-- robots removed from play
extern LPBYTE pCapData;		//-- pointer to the memory used to
							//-- copy the capture window
extern LPBYTE pZoomWin;		//-- pointer to the memory used to
							//-- store the zoom window
extern LPBYTE pSearchWin[MAXROBOTS];//-- pointers to the memory used to copy the
									//-- search window for locating robot colors
extern LPBYTE pTrackWinTeam[MAXROBOTS];	//-- pointers to the memory used to copy the
										//-- tracking window for locating team color
extern LPBYTE pTrackWinBall;	//-- pointer to the memory used to copy the
								//-- tracking window for locating ball color
extern LPBYTE pTrackWinOppo[MAXROBOTS];	//-- pointers to the memory used to copy the
										//-- tracking window for locating opponent color
extern BOOL gParallaxCorrectionEnabled;	//-- Parallax correction variable
extern BOOL gStopRobotsWhenBallLost;	//-- Stop Robots when ball not found
extern BOOL gGoalieFollowClick;		//-- goalie to follow the clicked point
									//-- when opponent takes penalty
extern float gVelocityScaling;	//-- velocity scaling factor
extern float gSpinVelocityScaling;	//-- velocity scaling factor
extern float gCameraHeight;

extern StartPosition gStartingPosition;	//-- starting positions

//----- for tuning
extern GoalieActionparameters gGoalieActionParameters;	//-- for CGoalieAction

extern BOOL gfoundBall;
extern BOOL gfoundR1, gfoundR2, gfoundGoalie;

//-- Opponents ----------------------
extern int gNumOppoRobots;	//-- number of opponent robots in play
extern BOOL gTrackOpponent;	//-- track the opponent position?
//-- Opponents ----------------------

extern BOOL VideoLive;	//-- is video live?

extern int gChoice;		//-- choice of testing

//-- incremental window size for colour patches -----
extern	POINT inctopTeam[MAXROBOTS];
extern	POINT incbottomTeam[MAXROBOTS];

extern	POINT inctopBall;
extern	POINT incbottomBall;

extern	POINT inctopOppo[MAXROBOTS];
extern	POINT incbottomOppo[MAXROBOTS];

extern LPBYTE lpImageBuf;
extern WORD wIRQNum;
extern BYTE *lpDib[4];
extern HANDLE hDib[4];
extern int nCount;
extern CAPMEMINFO CapMemInfo;	//-- Capture Memory Information
extern BYTE fieldType[4];

extern int halfFrameJump;
extern int timerCount;//used for counting timer values

extern float gBallClearTime;	//-- time after which goalie
								//-- will clear the ball (in Seconds)

extern startPhaseVal gstartPhaseVal[5];

extern BOOL FBUSINSTALLED;	//-- is the Vision Card installed?

#endif //!COMMONDATA_INCLUDED_