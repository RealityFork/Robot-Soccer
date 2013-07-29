//-- Filename : map.h
//-- Mapping functions to convert screen coordinates to physical coordinates.

#if !defined MAP_INCLUDED_
#define MAP_INCLUDED_

//-- the physical size of the field is 150cm X 130cm
#define Physical_X	(float)150.0
#define Physical_Y	(float)130.0

#define Physical_Xby2	(float)75.0
//-- Physical_X/2
#define Physical_Yby2	(float)65.0
 //-- Physical_Y/2

// Required for parallax correction
// camera height from field to lens in gCameraHeight
// Make sure these numbers are floats, used in (gCameraHeight - ROBOTHEIGHT)/CAMERAHEIGHT) calculation
#define ROBOTHEIGHT 6.4

#define BALLHEIGHT 3.4
//-- actual diameter is 4.27

void mapxy(floatPOINT *Screen, floatPOINT *Physical, commondata *pdata);
void rotatemapxy(floatPOINT *Physical);
void turnangle(float *angle);
void mapall(commondata *pdata);
void updateVariables(commondata *pdata);
void updateStrategyVariables(commondata *pdata);

//-- For diagnostics
void inversemapxy( floatPOINT *Screen, floatPOINT *Physical, commondata *pdata);
void PhysicaltoScreen(floatPOINT *Screen, floatPOINT *Physical, commondata *pdata);
floatPOINT rotatemapxyVal(floatPOINT *Physical);
//-- For diagnostics

//-- Parallax correction functions, using calculated physical image centre
float parallaxCorrectionX(float OriginalX, commondata *pdata, float ObjectHeight);
float parallaxCorrectionY(float OriginalY, commondata *pdata, float ObjectHeight);
floatPOINT parallaxCorrection(floatPOINT *pOriginal, commondata *pdata, float ObjectHeight);

float distanceGap(floatPOINT *A, floatPOINT *B);
float distanceGapI(POINT *A, POINT *B);
#endif
