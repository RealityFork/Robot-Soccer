// myrosot1Dlg.h : header file
//

#include "AdjColDlg.h"
#include "RFCommDlg.h"
#include "Parameters.h"
#include "commondata.h"
#include "AdjGameArea.h"
#include "GrabberSettingsDlg.h"
#include "TuningDlg.h"

#if !defined(AFX_MYROSOT1DLG_H__F3F95E86_E074_11D2_8B75_817FE7DC6734__INCLUDED_)
#define AFX_MYROSOT1DLG_H__F3F95E86_E074_11D2_8B75_817FE7DC6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


//UINT gameThread(LPVOID pParam);
//UINT txThread(LPVOID pParam);

/////////////////////////////////////////////////////////////////////////////
// CMyrosot1Dlg dialog

class CMyrosot1Dlg : public CDialog
{
	//---- [START] user added data members for the main Dialog class -------
	commondata *pdata;		//-- pointer to commondata
	POINT capPoint;		//-- Coordinates of the point clicked within
						//-- the capture window for zooming
	BOOL showZoomWindow;//-- show the zoom window?
	POINT Prev, Current;//-- these points define the extent of colour box
						//-- inside the zoom window
	COLORREF RGBColourBox; //-- average colour in the colour box

	BYTE refcol;
	BYTE refYmin, refYmax, refUmin, refUmax, refVmin, refVmax;

	//---- [END] user added data members for the main Dialog class -------

// Construction
public:

	CMyrosot1Dlg(CWnd* pParent = NULL);	// standard constructor

	CAdjColDlg m_AdjColDlg;		//-- Adjust Colour Dialog Box
	CRFCommDlg m_RFCommDlg;		//-- RF Communication Dialog Box
	CParameters m_ParametersDlg;//-- Parameters Dialog Box
	CAdjGameArea m_AdjGameAreaDlg;	//-- Adjust Game Area Dialog Box
	CGrabberSettingsDlg m_GrabberSettingsDlg;//-- Grabber settings dialog Box
	CTuningDlg m_TuningDlg;	//-- Dialog Box for tuning

// Dialog Data
	//{{AFX_DATA(CMyrosot1Dlg)
	enum { IDD = IDD_MYROSOT1_DIALOG };
	CScrollBar	m_VelStepSize;
	int		m_SetBoundary;
	BYTE	m_Red;
	BYTE	m_Green;
	BYTE	m_Blue;
	int		m_Selection;
	int		m_GameArea;
	BOOL	m_Bkcolour;
	CString	m_Goalieangle;
	CString	m_Robot1angle;
	CString	m_Robot2angle;
	UINT	m_FrameCount;
	UINT	m_BallFull;
	UINT	m_TeamFull;
	UINT	m_FullScan;
	int		m_Diagnostics;
	int		m_ColourNRange;
	CString	m_Observer;
	int		m_DisplayUnit;
	BOOL	m_FullTrackingOnly;
	int		m_startPhase;
	int		m_whosePossession;
	int		m_whichQuadrant;
	int		m_DisplayHome;
	UINT	m_Ball;
	UINT	m_Team;
	BOOL	m_colTuning;
	CString	m_Goaliex;
	CString	m_Goaliey;
	CString	m_Robot1x;
	CString	m_Robot1y;
	CString	m_Robot2x;
	CString	m_Robot2y;
	CString	m_Ballx;
	CString	m_Bally;
	BOOL	m_DisplayBoundaries;
	CString	m_Time;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyrosot1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyrosot1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileExit();
	afx_msg void OnHelpAbout();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLeftRadio();
	afx_msg void OnRightRadio();
	afx_msg void OnOffRadio();
	afx_msg void OnHighRadio();
	afx_msg void OnLowRadio();
	afx_msg void OnStartButton();
	afx_msg void OnStopButton();
	afx_msg void OnTestButton();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStoptestButton();
	afx_msg void OnBlackbackgroundCheck();
	afx_msg void OnGetreadyButton();
	afx_msg void OnSavecolorsButton();
	afx_msg void OnLoadcoloursButton();
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnAdjustrangeButton();
	afx_msg void OnUpdatelutButton();
	afx_msg void OnUtilsRfcomm();
	afx_msg void OnMapcoloursRadio();
	afx_msg void OnSetboundariesRadio();
	afx_msg void OnFieldareaRadio();
	afx_msg void OnHomegoalareaRadio();
	afx_msg void OnOppogoalareaRadio();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnUtilsSetparameters();
	afx_msg void OnUtilsAdjustgamearea();
	afx_msg void OnDisplayCmRadio();
	afx_msg void OnDisplayPixelRadio();
	afx_msg void OnFulltrackingonlyCheck();
	afx_msg void OnGrabberSettings();
	afx_msg void OnKickstartRadio();
	afx_msg void OnGoalkickRadio();
	afx_msg void OnPenaltyRadio();
	afx_msg void OnFreekickRadio();
	afx_msg void OnFreeballRadio();
	afx_msg void OnHomeRadio();
	afx_msg void OnOpponentRadio();
	afx_msg void OnTopleftRadio();
	afx_msg void OnToprightRadio();
	afx_msg void OnBottomleftRadio();
	afx_msg void OnBottomrightRadio();
	afx_msg void OnGoButton();
	afx_msg void OnUtilsTuning();
	afx_msg void OnDisplayHomeRadio();
	afx_msg void OnDisplayOppoRadio();
	afx_msg void OnUtilsTesting();
	afx_msg void OnColortuningCheck();
	afx_msg void OnQstateButton();
	afx_msg void OnDisplayboundariesCheck();
	afx_msg void OnBallRadio();
	afx_msg void OnRobot1Radio();
	afx_msg void OnRobot2Radio();
	afx_msg void OnTeamRadio();
	afx_msg void OnOppoRadio();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYROSOT1DLG_H__F3F95E86_E074_11D2_8B75_817FE7DC6734__INCLUDED_)
