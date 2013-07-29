/*

FBus.h

Copyright (c) 1995-2000 -- Integral Technologies, Inc.

Public prototypes and declarations for FlashBus SDK

*/

/////////////////////////////////// Constants ////////////////////////////////

// Some constants that make DOS<=>Windows portability easier 
#ifndef _INC_FBUS_H
#define _INC_FBUS_H

#define FLASHBUSMV 1

#ifdef __OS2__
   #define INCL_DEV
   #define INCL_WINSYS
   #define INCL_WINWINDOWMGR
   #define INCL_GPICONTROL

   #include <os2.h>
#endif

#if (defined(_DOS) || defined(__OS2__) || defined(_LINUX)) && !defined(_INC_WINDOWS)

#define VOID          void

#if defined(__FLAT__) || defined(__OS2__) || defined(_TNT) || defined(FMODEL) || defined(_LINUX)
   #define FAR
   #define NEAR
#else
   #define FAR              _far
   #define NEAR               _near
#endif

#ifdef _LINUX
 #define PASCAL
#else
 #ifdef _TNT
   #define PASCAL        __stdcall
 #else
   #if __IBMC__ || __IBMCPP__
      #define PASCAL        _Pascal
   #else
      #define PASCAL        _pascal
   #endif
 #endif
#endif

#define CDECL         _cdecl
#define WINAPI              FAR PASCAL
#define CALLBACK            FAR PASCAL

#if !defined(__OS2__)
typedef int        BOOL;
typedef unsigned char       BYTE;
typedef unsigned int     UINT;
typedef short int SHORT;
#define LOBYTE(w)     ((BYTE)(w))
#define HIBYTE(w)           ((BYTE)(((UINT)(w) >> 8) & 0xFF))
#define MAKELONG(low, high) ((LONG)(((WORD)(low)) | (((DWORD)((WORD)(high))) << 16)))
#endif

#define FALSE         0
#define TRUE          1

typedef unsigned short      WORD;
typedef unsigned long       DWORD;
#define LONG long

#define LOWORD(l)           ((WORD)(DWORD)(l))
#define HIWORD(l)           ((WORD)((((DWORD)(l)) >> 16) & 0xFFFF))

#ifndef NOMINMAX
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif
#endif  // NOMINMAX

// Types used for passing & returning polymorphic values
typedef UINT WPARAM;
typedef LONG LPARAM;
typedef LONG LRESULT;
#define MAKELPARAM(low, high) ((LPARAM)MAKELONG(low, high))
#define MAKELRESULT(low, high)   ((LRESULT)MAKELONG(low, high))

#ifndef NULL
#define NULL          0
#endif
typedef char NEAR*          PSTR;
typedef char NEAR*          NPSTR;
typedef char FAR*           LPSTR;
typedef const char FAR*     LPCSTR;
#if !defined(__OS2__)
typedef BYTE NEAR*       PBYTE;
typedef int NEAR*     PINT;
typedef long NEAR*       PLONG;
#endif
typedef BYTE FAR*     LPBYTE;
typedef int FAR*      LPINT;
typedef WORD NEAR*          PWORD;
typedef WORD FAR*           LPWORD;
typedef long FAR*     LPLONG;
typedef DWORD NEAR*         PDWORD;
typedef DWORD FAR*          LPDWORD;
typedef void FAR*           LPVOID;
#define MAKELP(sel, off)    ((void FAR*)MAKELONG((off), (sel)))

#else

#include <windows.h> //Just in case

#endif	//ifdef (_DOS || __OS2__ || _LINUX) && !_INC_WINDOWS

// Windows and DOS constants
#ifdef _LINUX
//Linux shared lib has problems with HUGE already being defined
//Linux Apps shouldn't define FMODEL and shouldn't use HUGE
#if defined(FMODEL)
#ifdef HUGE
#undef HUGE
#endif
#define HUGE
#endif
#define HUGE16

#else

#if defined(WIN32) || defined(__FLAT__) || defined(__OS2__) || defined(_TNT) || defined(FMODEL)
#define HUGE
#define HUGE16
#else
#define HUGE _huge
#define HUGE16 _huge
typedef short int SHORT;
#endif

#endif

#ifdef _LINUX

typedef struct tagRECT
{
   int  left;
   int  top;
   int  right;
   int  bottom;
} RECT;

typedef RECT FAR*	LPRECT;

#define HWND unsigned int
#define HDC unsigned int
#endif

// Libary return values
#define RET_SUCCESS        0
#define RET_ERROR          -1
#define RET_INICONFIG      0
#define RET_DEFCONFIG      1
#define RET_EEPROMCONFIG   2
#define RET_AWFULLDCI      0
#define RET_AWPARTIALDCI   1
#define RET_AWNODCI        2
#define RET_UNSUPPORTED    1
#define RET_TIMEOUT        1

// Input video sizes
#define NTSCVIDEOWIDTH  640
#define NTSCVIDEOHEIGHT 480
#define NTSCVIDEOWIDTHIN  640
#define NTSCVIDEOHEIGHTIN 480
#define NTSCVIDEOWIDTHOUT  640
#define NTSCVIDEOHEIGHTOUT 480
#define PALVIDEOWIDTH   760
#define PALVIDEOHEIGHT  570  //Changed from 576 to provide 4x3 ratio
#define PALVIDEOWIDTHIN   760
#define PALVIDEOHEIGHTIN  570
#define PALVIDEOWIDTHOUT   760
#define PALVIDEOHEIGHTOUT  570

// Video standards
#define STANDARD_NTSC   0
#define STANDARD_PAL    1
#define MAXVIDSTANDARD	1

// Video types
#define TYPE_COMPOSITE  0
#define TYPE_SVIDEO     1
#define TYPE_RGB        2
#define TYPE_BETA       3
#define TYPE_RS170      4
#define MAXVIDTYPE	4

// Video sources
// ++Nelson changed this:++
#define MAXVIDSOURCE	9

// IRQ type for FB_EnableIRQ() call
#define IRQ_VIDEO       0
#define IRQ_VGA         1
#define IRQ_TRIGGER	2

// Rect types used in calls to FB_GetVideoRect()
#define ACQRECT         0
#define SOURCERECT      1
#define DESTRECT        2

// I2C Addresses
#define UARTCTRL_ADDR   0x40  //NA MV
#define UARTDATA_ADDR   0x42  //NA MV
#define GPIO_ADDR       0x44 // NA MV general purpose I/O
#define DIVIDER_ADDR    0x46 // NA MV programmable divider
#define ANALOG_ADDR     0x48 // NA MV analog output
#define MC44011_ADDR    0x8a // NA MV decoder
#define EEPROM_ADDR     0xa0
#define EEPROM_ADDRR    0xa1
#define SAA7186_ADDR    0xb8 // NA MV scaler
#define SAA7110ADDRW	0x9c
#define SAA7110ADDRR	0x9d
#define TDA8444ADDRW	0x4a

// Flash Types
#define FLASHTYPE_NONE        0
#define FLASHTYPE_UNIVERSAL   1
#define FLASHTYPE_CCD4000     2
#define FLASHTYPE_DUALFIELD   3
#define FLASHTYPE_DUALPULSE   4
#define FLASHTYPE_SONYLTE     5
#define FLASHTYPE_WAITSWITCH  6
#define FLASHTYPE_CANON       7
#define FLASHTYPE_WAITFLASH	8
#define FLASHTYPE_WAITFLASHFIELD 9
#define FLASHTYPE_ASYNCRESET 10  //Pulse low
#define FLASHTYPE_ASYNCRESETH 11  //Pulse high

// Flash flags OR'ed with type
#define FLASHFLAG_FIELDREP    0x8000
#define FLASHFLAG_REDGESMOOTH 0x4000
#define FLASHFLAG_FIELDREPO   0x2000
#define FLASHFLAG_FORCELIVE   0x1000
#define FLASHFLAG_FIELDREPAVG	0x800

// Field alignment values
#define ALIGN_EVEN            0
#define ALIGN_ODD             1
#define ALIGN_ANY             2
#define ALIGN_NONE            3
#define ALIGN_QUICK           4
#define ALIGNFLAG_NOREFRESH   0x8000
#define ALIGNFLAG_LTE         0x4000
#define ALIGNFLAG_CONSECWAIT  0x2000
#define ALIGNFLAG_CONSECONCE  0x1000
#define ALIGNFLAG_CONSECCONT  0x0800

//Indexes for async capture
#define AGI_DISABLE	0
#define AGI_ENABLE	1
#define AGI_SETCURFRAME	2
#define AGI_GETCURFRAME	3
#define AGI_SETCURFIELD	4
#define AGI_GETCURFIELD	5
#define AGI_GETDMASTATE	6
#define AGI_DEMANDSIGNAL 7
#define AGI_DEMANDUNSIGNAL 8

//Flags for async capture
#define AGRAB_WAIT		0x20000000
#define AGRAB_CONT		0x10000000
#define AGRAB_DEMAND		0x08000000
#define AGRAB_TRIGENABLE	0x04000000
#define AGRAB_TRIGHIGH		0x02000000
#define AGRAB_TRIGLEVEL		0x01000000
#define AGRAB_ALIGNODD		0x00800000
#define AGRAB_ALIGNEVEN		0x00400000

// VGA Mode depth flag
#define VGAMODE_VESA          -1

// Copy direction flag
#define COPYDIR_TOVGA         0
#define COPYDIR_FROMVGA       1
#define COPYDIR_FROMOFFSCREEN 2

// SaveFile flags
#define SAVEFILE_RLE             0x0100
#define SAVEFILE_GRAY8           0x0200
#define SAVEFILE_FLIPX           0x0400
#define SAVEFILE_COLOR8          0x0800
#define SAVEFILE_FLIPY           0x1000
#define SAVEFILE_FROMOFFSCREEN   0x8000

// Video adjustment types
#define ADJUST_HUE         0
#define ADJUST_SATURATION  1
#define ADJUST_BRIGHTNESS  2
#define ADJUST_CONTRAST    3
#define ADJUST_REDBRIGHT   4
#define ADJUST_BLUEBRIGHT  5
#define ADJUST_SHARPNESS   6
#define ADJUST_COMPMONO    7
#define ADJUST_SYNCMODE    8
#define ADJUST_FILTER      9
#define ADJUST_GREENBRIGHT	10
#define ADJUST_GAIN		11

// MIN and MAX adjust vals
#define MINADJUSTVAL    0
#define MAXADJUSTVAL    0x3f
// IRIS level is 0-4095
#define MAXIRISVAL      0xfff

// Windows DCI window watch types for FB_AutoWindow
#define AUTOWIN_FREEZE  0x01  //Freeze on occlusion
#define AUTOWIN_CLIP 0x02  //Clip on occlusion
#define AUTOWIN_POS  0x04  //Auto position video
#define AUTOWIN_SIZE 0x08  //Auto size video
#define AUTOWIN_ASPECT  0x10  //maintain aspect (requires AUTOWIN_ADJUSTWINDOW)
#define AUTOWIN_ADJUSTWINDOW  0x20  //Allow window to be moved, sized
#define AUTOWIN_FORCEPAINT 0x40  //Paint window background when sized
#define AUTOWIN_OVERSIZE   0x80  //Round up to DWORD length
#define AUTOWIN_REFRESH    0x100 //Redraw vid from buffer when frozen
#define AUTOWIN_TOPMOST    0x200 //Force window to topmost
#define AUTOWIN_LIVEDACTWIN   0x400 //Limited DCI no freeze on deactivate win
#define AUTOWIN_LIVEDACTAPP   0x800 //Limited DCI no freeze on deactivate app
#define AUTOWIN_FORCEAW1   0x1000   //Force AW level1 - no DCI callbacks
#define AUTOWIN_FORCEAW2   0x2000   //Force AW level2 - no DCI
#define AUTOWIN_MASKBLEEDFIX	0x4000  //Fix left edge mask bleed
#define AUTOWIN_DCIFREEZEFIX	0x8000  //Fix Win16 DCI video freeze problem
#define AUTOWIN_MASKBLEEDFIXTOP	0x10000  //Fix top edge mask bleed

// FB_AutoBlit() flags
#define AB_SETPAL    0x01
#define AB_GRAY8     0x02
#define AB_NOSCALE   0x04

// FB_ScreenToDIB() flags
#define STD_ONSCREEN    0x0000
#define STD_CLIPBOARD   0x0001
#define STD_GRAY8       0x0002
#define STD_OFFSCREEN   0x8000

// MaskDraw OPs
#define MD_INIT         0
#define MD_CLEANUP      1
#define MD_SETUP        2
#define MD_RESET        3
#define MD_UPDATE       4
#define MD_LINE         5
#define MD_UNLINE       6
#define MD_BOX          7
#define MD_UNBOX        8
#define MD_CROSSHAIR    9
#define MD_UNCROSSHAIR  10
#define MD_CIRCLE       11  //unimplemented
#define MD_UNCIRCLE     12  //unimplemented
#define MD_RECT         13
#define MD_UNRECT       14

// Get/Set Misc indexes
// Return connected video input type - type,standard,source,sog
// in byte0,byte1,byte2,byte3
#define MISCPARM_INPUTVID        0x01
#define MISCPARM_AWSELBOX        0x02
#define MISCPARM_MEMPTR          0x03
#define MISCPARM_MEMSIZE         0x04
#define MISCPARM_MEMFRAMES       0x05
#define MISCPARM_SINGLEFIELD     0x06 // ALIGN_EVEN, ALIGN_ODD or ALIGN_ANY
#define MISCPARM_MEMPHYSADDR     0x07
#define MISCPARM_MEMOFFSET       0x08
#define MISCPARM_MEMCOPYOFFSET   0x09
#define MISCPARM_VIDEOLOCK       0x0a
#define MISCPARM_AWBASEMASK      0x0b
#define MISCPARM_OUTSWITCH       0x0c
#define MISCPARM_WSTIMEOUT       0x0d
#define MISCPARM_PIXBUFDEPTH     0x0e
#define MISCPARM_RESERVED        0x0f
#define MISCPARM_ALWAYSLIVE      0x10
#define MISCPARM_LTEMS           0x11
#define MISCPARM_CAMERATYPE      0x12
#define MISCPARM_SYNCMODE        0x13
#define MISCPARM_WAITFLASHPARMS  0x14

#define MISCPARM_AGCENABLE	0x15
#define MISCPARM_POWEROUT	0x16
#define MISCPARM_CLEARSWITCH	0x17
#define MISCPARM_INVERTVIDEO	0x18
#define MISCPARM_SELBOXWIDTH	0x19
#define MISCPARM_SELBOXCOLOR	0x1a

#define MISCPARM_UPDATEMASK	0x1b
#define MISCPARM_AWKILLPAINTMSG	0x1c
#define MISCPARM_ONEFIELD	0x1d
#define MISCPARM_NONINTERLACED	0x1e
#define MISCPARM_MIRRORVIDEO	0x1f
#define MISCPARM_FRAMEMASK	0x20
#define MISCPARM_IOTRIGGERS	0x21
#define MISCPARM_WINDOWNUMBER	0x22
#define MISCPARM_LATCHINSWITCH  0x23
#define MISCPARM_CURCONSECFRAME 0x24
#define MISCPARM_MICROPHWRESET	0x25
#define MISCPARM_CURCONSECFIELD 0x26
#define MISCPARM_PICNOWAIT      0x27

// SetPalette indexes
#define SETPAL_CREATEGRAY8 0
#define SETPAL_DELGRAY8    1
#define SETPAL_SETCURRENT  2
#define SETPAL_SELHWND     3
#define SETPAL_DESELHWND   4
#define SETPAL_SELHDC      5
#define SETPAL_DESELHDC    6
#define SETPAL_ILUT        7  //YUV
#define SETPAL_ILUT2       8  //Red
#define SETPAL_ILUT3       9  //Green
#define SETPAL_ILUT4       10  //Blue

// MISCREG Indexes
#define MISCREG_BT252		0
#define MISCREG_74ACT715	1
#define MISCREG_RC6601		2
#define MISCREG_MVEPLD		3
#define MISCREG_DEBI		4

// Board config flags
#define CFG_INTPOLFIX   0x01
#define CFG_NOSERIAL    0x02
#define CFG_PROGFREQ    0x04
#define CFG_IRISCTRL    0x08
#define CFG_GRAY8       0x10
#define CFG_NORGB       0x20
#define CFG_MV          0x40
#define CFG_INVFLASH    0x80
#define CFG_MICROP      0x100
#define CFG_RS170	      0x200
#define CFG_SYNCGEN135  0x400
#define CFG_RS170_RGMUX 0x800

// Decoder Type
#define DECTYPE_MCC44011 0
#define DECTYPE_BT252 1
#define DECTYPE_SAA7110 2

// Camera Types
#define DC330		1
#define SONY950		2
#define DAGESLG		3
#define ASYNCNOVSYNC	4
#define ASYNCHNOVSYNC	5
/* Masters specify ffffxxps in low byte */
/* ffff is output delay, p is a pulse, and s is integration state */
#define GENERICMASTER	0x4000
/* CutomSync specifies sync chracteristics in middle nibbles */ 
#define CUSTOMSYNC	0x8000
#define CS_WENRISE 0x000  //WEN Polarity
#define CS_WENFALL 0x010
#define CS_INTPIXCLK 0x000  //PIX clk
#define CS_EXTPIXCLK 0x020
#define CS_PLLADCLK 0x000  //ADCLK
#define CS_7110ADCLK 0x040
#define CS_TWOSYNC 0x080  //Sync on both edges of WEN
#define CS_HSCTLHREFPLL 0x000  //HSYNC control
#define CS_HSCTL7110 0x100
#define CS_HSCTLEXT 0x200
#define CS_HSCTLSSEP 0x300
#define CS_VSCTLSSEP 0x000  //VSYNC control
#define CS_VSCTL7110 0x400
#define CS_VSCTLEXT 0x800
#define CS_VSCTLEXTPS 0xc00

// Video Capture Memory flags
#define VCM_GETCONFIG		0x10000
#define VCM_SETMEMBUFFER	0x20000
#define VCM_RELEASEMEMBUFFER	0x40000
#define VCM_SETOFFSET		0x80000
#define VCM_SETCOPYOFFSET	0x100000
#define VCM_SETPITCH		0x200000

//PCIConfig indexes
#define PCICFG_FINDDEV     0
#define PCICFG_READDWORD   1
#define PCICFG_WRITEDWORD  2
#define PCICFG_FINDCLASS   3

// EEPROM byte count
#define EEPROMSIZE 256

#define MAXBOARDS 4
#define MULTIB_INIT 0
#define MULTIB_CLEANUP 1
#define MULTIB_SWITCHBOARD 2
#define MULTIB_SETBOARD 3
///////////////////////////////// TYPEDEFS ///////////////////////////

// Video capture memory config structure
typedef struct tagCaptureMemInfo
{
   DWORD dwMemPtr;
   DWORD dwMemSize;
   DWORD dwMemOffset;
   DWORD dwMemCopyOffset;
   DWORD dwMemPhysAddr;
   DWORD dwMemFrames;
   DWORD dwVGAMemPtr;
   DWORD dwVGASize;
   DWORD dwVGAMemPhys;
   DWORD dwMaskPtr;
   DWORD dwPitch;
   DWORD dwReserved[5];
} CAPMEMINFO;

// Version info struct
typedef struct tagVersionInfo
{
   WORD  wLibVersion;
   WORD  wBetaVersion;
   WORD  wDebugStatus;
   WORD  wBusType;
   WORD  wVGAMem;
   WORD  wSClk;
   WORD  wBWidthLimit;
   WORD  wBIOSVersion;
   DWORD dwBoardCfg;
   DWORD dwSerialNum;
   WORD  wBoardRev;
   WORD  wScalerRev;
   WORD	wVGAType;
   WORD	wDecoderType;
   WORD	wEEPROMVer;
   WORD	wMicoPVer;
   WORD  wReserved[14];
} VERSIONINFO;

// File resolution info struct
typedef struct tagFileResInfo
{
   WORD  wWidth;
   WORD  wHeight;
   WORD  wDepth;
   WORD  wFlags;
} FILERESINFO;

// AutoWin info
typedef struct tagAutoWinInfo
{
   DWORD hWnd;
   WORD  wRsv;
   LPSTR lpMaskBuf;
   WORD  wMaskWidth;
   WORD  wMaskHeight;
   WORD  wOccluded;
   BOOL  bAWLive;
   LPSTR lpRefreshBuf;
   WORD  wMaskDelay;
   DWORD hWinWatch;
   WORD  wReserved[18];
} AUTOWININFO;

//////////////////////////////// Prototypes /////////////////////////////////

// Library routines return 0 or value for success, <0 for failure

#ifdef __cplusplus
extern "C" {
#endif 

// Locate the board, don't change any regs
SHORT WINAPI FB_Locate(void);
// Init the board using the currently loaded configuration
SHORT WINAPI FB_Init(void);
// Shut down in preparation for exit
SHORT WINAPI FB_Cleanup(void);

// Load configuration from .INI file.  A NULL file name loads the default vals
SHORT WINAPI FB_LoadConfig(LPSTR szIniFile);
// Save configuration to .INI file
SHORT WINAPI FB_SaveConfig(LPSTR szIniFile);
// Save current configuration to the EEPROM
// Developers should NOT make this call
SHORT WINAPI FB_SaveConfigToEEPROM(WORD, WORD, DWORD, DWORD);

// Write an I2C register
SHORT WINAPI FB_SetI2CReg(SHORT nAddr, SHORT nSubAddr, SHORT nVal);
// Read an I2C register
SHORT WINAPI FB_GetI2CReg(SHORT nAddr, SHORT nSubAddr);

// 7146 Set/Get functions
SHORT WINAPI FB_SetSAA7146Reg(SHORT nAddr, DWORD dwVal);
DWORD WINAPI FB_GetSAA7146Reg(SHORT nAddr);

//Set scaler in and out modes
SHORT WINAPI FB_SetColorSpace(SHORT nInSpace, SHORT nOutSpace);

// Return version info
SHORT WINAPI FB_GetVersionInfo(VERSIONINFO FAR *pVInfo);

// Return the VGA mode
SHORT WINAPI FB_GetVGAMode(BOOL bVESA);

// Convert pixel vals to a new resolution
SHORT WINAPI FB_ConvertPixel(SHORT nWidth, SHORT nDepthCur, SHORT nDepthNew,
      char HUGE16 *lpValCur, char HUGE16 *lpValNew, LPSTR lpCMap);
// Set a VGA pixel
SHORT WINAPI FB_SetVGAPixel(SHORT nX, SHORT nY, long lVal);
// Set a VGA rectangle to a uniform value
SHORT WINAPI FB_SetVGARect(SHORT nX, SHORT nY, SHORT nWidth, SHORT nHeight,
      long lVal);
// Copy a VGA rectangle to or from main memory
// Direction 0==to VGA 1==from VGA
SHORT WINAPI FB_CopyVGARect(SHORT nX, SHORT nY, SHORT nWidth, SHORT nHeight,
      char HUGE16 *hpPixBuf, SHORT nPitch, SHORT bFromVGA);
// Create a DIB from a screen rectangle
SHORT WINAPI FB_ScreenToDIB(SHORT nX, SHORT nY, SHORT nWidth, SHORT nHeight,
      SHORT nFlags, char HUGE16 *hpDIBBuf);

// Set the video type and standard
// Config types are: 0 source, 1 standard, 2 type
SHORT WINAPI FB_SetVideoConfig(SHORT nType, SHORT nStandard, SHORT nSource,
      BOOL bSyncOnGreen);
// Get the video type, standard, or source
SHORT WINAPI FB_GetVideoType(void);
SHORT WINAPI FB_GetVideoStandard(void);
SHORT WINAPI FB_GetVideoSource(void);

// Get or set a misc value 
SHORT WINAPI FB_GetMiscParm(SHORT nIndex, void FAR *lpRetBuf);
SHORT WINAPI FB_SetMiscParm(SHORT nIndex, LONG lVal);

// Get or set a misc reg value 
SHORT WINAPI FB_SetMiscReg(SHORT nIndex, DWORD dwReg, DWORD dwVal);
DWORD WINAPI FB_GetMiscReg(SHORT nIndex, DWORD dwReg);

// Set an 8 bit palette
SHORT WINAPI FB_SetPalette(SHORT nType, long lHandle);

// Set input(source) video rect
SHORT WINAPI FB_SetInputWindow(SHORT nSrcX, SHORT nSrcY, SHORT nSrcWidth,
      SHORT nSrcHeight);
// Set X and Y offset into the input(source) window
SHORT WINAPI FB_SetInputOffset(SHORT nOffX, SHORT nOffY);

// Set video window size and position
SHORT WINAPI FB_SetVideoWindow(SHORT nDstX, SHORT nDstY, SHORT nDstWidth,
      SHORT nDstHeight ,BOOL bScale);

SHORT WINAPI FB_VideoOffscreen(SHORT nDstWidth, SHORT nDstHeight,
      SHORT nDstDepth, BOOL bScale);

//Set/Get info on video capture memory
SHORT WINAPI FB_VideoCaptureMem(CAPMEMINFO FAR *pCMInfo, DWORD dwFlags);

//Access PCI config space
DWORD WINAPI FB_PCIConfig(SHORT nIndex, DWORD dwVal0, DWORD dwVal1, DWORD dwVal2);

// Set video acquisition rectangle
SHORT WINAPI FB_SetAcqRect(SHORT nAcqX, SHORT nAcqY, SHORT nAcqWidth,
      SHORT nAcqHeight);
// Set and get the video x and y delays
SHORT WINAPI FB_SetXYDelay(SHORT nXDelay, SHORT nYDelay);
SHORT WINAPI FB_GetXDelay(void);
SHORT WINAPI FB_GetYDelay(void);

// Get various video rects
SHORT WINAPI FB_GetVideoRect(SHORT nRectType, SHORT FAR *pnX, SHORT FAR *pnY,
      SHORT FAR *pnWidth, SHORT FAR *pnHeight);

// Vsync/LSync operations
// Get the current field type
SHORT WINAPI FB_GetFieldType(void);
// Wait for a particular field type
SHORT WINAPI FB_WaitFieldType(SHORT nFieldType);
// Wait a specified number of fields
SHORT WINAPI FB_WaitVSync(SHORT nSyncCnt);
// Wait a specified number of lines
SHORT WINAPI FB_WaitHSync(SHORT nSyncCnt);
// Wait a specified number of milliseconds
SHORT WINAPI FB_WaitMS(SHORT nMSCnt);

// Adjust video parms
// Adjustment types are: 0==hue 1==sat, 3==bright, 4==contrast
SHORT WINAPI FB_SetVideoAdjustments(SHORT nType, SHORT nVal);
// Get current video parms
SHORT WINAPI FB_GetVideoAdjustments(SHORT nType);
// Get video parms for any standard or type
SHORT WINAPI FB_GetSTVideoAdjustments(SHORT nStandard, SHORT nVideoType,
      SHORT nType);

// Freeze video with or without flash
// Alignment values: ALIGN_ANY  ALIGN_ODD  ALIGN_EVEN
// Flash delay values: FLASHTYPE_NONE FLASHTYPE_AUTO FLASHTYPE_MANUAL
SHORT WINAPI FB_VideoGrab(SHORT nAlign, SHORT nFlashType, SHORT nFlashDelayF,
      SHORT nFlashDelayL);
// Start live video
SHORT WINAPI FB_VideoLive(BOOL bLive, SHORT nAlign);
// Get live status
SHORT WINAPI FB_GetLiveStatus(void);
// Set async, multibuffer grab mode
SHORT WINAPI FB_AsyncGrab(SHORT nIndex, SHORT nFrameCnt, DWORD dwFlags);

// Check external switch
SHORT WINAPI FB_CheckSwitch(SHORT nBaseAddr, SHORT nTimeOutMS);

// Enable or Disable the video mask ram
SHORT WINAPI FB_EnableVideoMask(BOOL bEnable);
// Set the video mask ram
SHORT WINAPI FB_SetVideoMask(SHORT nX, SHORT nY, SHORT nWidth, SHORT nHeight, SHORT nPitch, LPSTR lpMaskBuf);
// Change the mask write delay
SHORT WINAPI FB_SetMaskDelay(SHORT nMDelay);
// Set the mask based on a key color
SHORT WINAPI FB_VGARectToMask(DWORD dwKeyColor, SHORT nX, SHORT nY
		, SHORT nWidth, SHORT nHeight
		, LPSTR lpMaskBuf, SHORT nPitch);
// Draw into video mask
SHORT WINAPI FB_MaskDraw(SHORT nOp, SHORT nX1, SHORT nY1
		, SHORT nX2, SHORT nY2, DWORD dwParam1, DWORD dwParam2);

// Enable or disable VGA or video VSync
SHORT WINAPI FB_EnableIRQ(SHORT nIRQType, SHORT nIRQNum, BOOL bEnable,
      void FAR *lpISR);
// Clear an IRQ
SHORT WINAPI FB_ClearIRQ(SHORT nIRQType, SHORT nIRQNum);
// Return the IRQ used
SHORT WINAPI FB_GetIRQNumber(void);

// Serial port functions
SHORT WINAPI FB_SetupSerial(SHORT nBaseIO, SHORT nIRQ, WORD wBaud,
      SHORT nDataBits, SHORT nParity, SHORT nStopBits);
SHORT WINAPI FB_ReadSerialBytes(LPSTR lpRcvBuf,SHORT nRcvCnt,SHORT nTimeOutMS);
SHORT WINAPI FB_WriteSerialBytes(LPSTR lpTxBuf,SHORT nTxCnt,SHORT nTimeOutMS);
SHORT WINAPI FB_GetSerialReg(SHORT nReg);
SHORT WINAPI FB_SetSerialReg(SHORT nReg, SHORT nRegVal);

//Mimic Windows private profile functions
SHORT WINAPI FB_GetPrivateProfileString(LPCSTR lpszSection, LPCSTR lpszEntry,
      LPCSTR lpszDefault, LPSTR lpszReturnBuffer, SHORT cbReturnBytes,
      LPCSTR lpszFileName);
SHORT WINAPI FB_WritePrivateProfileString(LPCSTR lpszSection, LPCSTR lpszEntry,
      LPCSTR lpszString, LPCSTR lpszFileName);
SHORT WINAPI FB_OpenPrivateProfileString(LPCSTR lpszFileName, BOOL bWrite);
SHORT WINAPI FB_ClosePrivateProfileString(BOOL bWrite);

// Load and save file will call seperate Dlls based on the file extension
// This allows new file formats to be added without changing the main DLL
// For DOS .TGA and .DIB are supported
// A NULL hpPixBuf will cause the image to be loaded directly into VGA mem
SHORT WINAPI FB_FileResInfo(LPSTR szPathName, FILERESINFO FAR *lpFileRes);
SHORT WINAPI FB_LoadFile(LPSTR szPathName, SHORT nX, SHORT nY, SHORT nWidth,
      SHORT nHeight, SHORT nFlags, char HUGE16 *hpPixBuf, SHORT nPitch);
SHORT WINAPI FB_SaveFile(LPSTR szPathName, SHORT nX, SHORT nY, SHORT nWidth,
      SHORT nHeight, SHORT nDepth, SHORT nFlags,char HUGE16 *hpPixBuf,
      SHORT nPitch);

// Available with programmable frequency boards
SHORT WINAPI FB_SetVidFreq(SHORT nNTSCBits, SHORT nPALBits);
// Available with programmable iris boards
SHORT WINAPI FB_SetIrisLevel(SHORT nIrisBits);

// Available under Windows with DCI
SHORT WINAPI FB_AutoWindow(UINT hWnd, SHORT nXOff, SHORT nYOff,
      SHORT nWidthAdj, SHORT nHeightAdj, long lFlags); 
SHORT WINAPI FB_AutoWindowInfo(AUTOWININFO FAR *pAWInfo);

SHORT WINAPI FB_AutoBlit(UINT nWnd, SHORT msec, SHORT nXOff, SHORT nYOff,
      SHORT nWidthAdj, SHORT nHeightAdj, long lFlags);

SHORT WINAPI FB_MultiBoard(SHORT nIndex, DWORD dwParm1);

#ifdef __cplusplus
}
#endif 

#endif   //ifndef _INC_FBUS_H
