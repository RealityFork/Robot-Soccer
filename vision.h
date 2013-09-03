//-- Filename : vision.h  (TEAM_N1)

#if !defined VISION_INCLUDED_
#define VISION_INCLUDED_

#include "commondata.h"
#include "math.h"

struct floatPOINT;
struct commondata;

#define TEAM	0
#define BALL	1
#define OPPO	2

#define FROMGETREADY	1
#define FROMGAMEHANDLER 2


#define MINPATCHSIZETEAM	8
//-- minimum size for home team colour
#define MINPATCHSIZECOL1	8
//-- minimum size for home team colour #1
#define MINPATCHSIZECOL2	8
//-- minimum size for home team colour #2
#define MINPATCHSIZEOPPO	8
//-- minimum size for oppo team colour
#define MINPATCHSIZEBALL	8
//-- minimum size for ball colour

#define AREATHRESHOLD_TEAM	8
//-- team patch colours below this level will be discarded
#define AREATHRESHOLD_COL12 4
//-- colour1/colour2 patch colours below this level will be discarded

#define SEPARATIONTHRESHOLD_TEAM 9.5
//8
//-- team patches closer by this distance are merged
//-- approx 5 cms
#define SEPARATIONTHRESHOLD_COL12 5.8
//6
//-- colour1/colour2 patches closer by this distance are merged
//-- approx 3 cms


//============ Screen Size ==================
#define ScreenX	800
#define ScreenY	600

//============ Video Capture Window Origin ===========
#define VideoOriginX	0
#define VideoOriginY	19

//============= Position of the zoom window  ==========
#define ZoomWinX	540
#define ZoomWinY	19

//== define the resolution of the Capture Window ======
#define CapSizeX	320
#define CapSizeY	240


//== define the maximum coordinates of the Capture Window =====
#define MaxX	319
	//-- (CapSizeX-1)
#define MaxY	239
	//-- (CapSizeY-1)

//======  Define colours ============
#define BLUE	0x000000ff
#define	GREEN	0x0000ff00
#define RED		0x00ff0000
#define BLACK	0x00

//========= INI file for grabber =============
#define INIFile "c:\\windows\\fbg.ini"


#define MAXPATCHES_F	80
//100
//-- max patches expected for fullFindPatch() for team/ball/oppo colour
#define MAXPATCHES_I	40
//40
//-- max patches expected for incrementalFindPatch() for team/ball/oppo patch
#define MAXPATCHES_S	20
//16
//-- max colour1 or colour2 patches expected in the search window

#define CIRCLE_RADIUS 9
//8
	//-- size of circular search window
	//-- this should be related to SEARCH_WIN size below
#define CIRCLE_RADIUS_SQUARE 81
//64
	//-- CIRCLE_RADIUS*CIRCLE_RADIUS

#define SEARCH_WIN	18
//16
	//-- size of square search window to look for robot colors
#define HALF_SEARCH_WIN 9
//8
	//-- SEARCH_WIN/2

#define TRACK_WIN_SIZE_TEAM	12
//-- tracking window size for incremental tracking of team patches
//-- 12 actually means a window of size 24x24
#define TRACK_WIN_SIZE_BALL	20
//16
//20
//25
//-- tracking window size for incremental tracking of ball
//-- 20 actually means a window of size 40x40
#define TRACK_WIN_SIZE_OPPO	10
//-- tracking window size for incremental tracking of opponent patches
//-- 10 actually means a window of size 20x20

#define FULLSCANLIMIT 25
//-- Number of continuous fullscans required before a robot is marked as removed

const float PI=(float)3.1415926;
//(float)asin(1.0)*2;

#define ANGLE_OFFSET	PI/4
//-- 45 degrees

struct group_details
{
	int grouparea;
	int groupno;
	int minX, maxX;
	int minY, maxY;
};

struct valid_group_details
{
	int grouparea;
	float COGx;
	float COGy;
};


struct grabber_settings	//-- settings for the Vision Card
{
	UINT brightness;
	UINT contrast;
	UINT saturation;
	UINT hue;
	UINT sharpness;
	BOOL CameraOnOff;	//-- camera on/off status
	short wStandard;	//-- Video Standard
	short wVideoType;	//-- Video type
};

//-- FUNCTION PROTOTYPES
void Delay(int num);
int CalX(struct group_details *thisgroup);
int CalY(struct group_details *thisgroup);
floatPOINT CalXY(struct group_details *thisgroup);

floatPOINT COGCalXY(struct group_details *thisgroup, BYTE grpdata[CapSizeY][CapSizeX]);
floatPOINT COGCalxy(struct group_details *thisgroup, BYTE label[SEARCH_WIN][SEARCH_WIN], POINT *ptop);

inline void matchLabel(int key, int value, BYTE col1table[MAXPATCHES_S][3]);

void fullTracking(commondata *pdata, int origin);
int fullFindPatch(BYTE which, commondata *pdata, floatPOINT colxy[MAXROBOTS]);

int incrementalTracking(commondata *pdata);
int incrementalFindPatch(BYTE which, commondata *pdata, floatPOINT colxy[MAXROBOTS]);

void copyRAMRect(POINT *ptopPos, LPBYTE *pTrackWin);
void copyPointerFromRAM(commondata *pdata);

void definewindow(POINT *ptop, POINT *pbottom, floatPOINT *pcentre, UINT size);

extern grabber_settings FBus;	//-- Vision card settings

#endif

/*

In X Direction:

  180cms -> 320 pixels
  1cm  -> 1.88 pixels
  3cms -> 1.88*3 = 5.64 pixels
  4cms -> 1.88*4 = 7.52 pixels
  5cms -> 1.88*5 = 9.4 pixels

In Y Direction:

  135cms -> 240 pixels
  1cm  -> 1.78 pixels
  3cms -> 1.78*3 = 5.34 pixels
  4cms -> 1.78*4 = 7.12 pixels
  5cms -> 1.78*5 = 8.88 pixels

Hence the circle radius must be 8 pixels

*/