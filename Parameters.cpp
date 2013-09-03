// Parameters.cpp : implementation file
//
#include "stdafx.h"
#include "Parameters.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParameters dialog

//-- backup variables
int lMinPatchSizeCol1;
int lMinPatchSizeCol2;
int lMinPatchSizeTeam;
int lMinPatchSizeBall;
int lMinPatchSizeOppo;
int ComPort;
BOOL GoalieRemoved;
BOOL Robot1Removed;
BOOL Robot2Removed;
BOOL TrackOpponent;
int NumOppoRobots;
float CameraHeight;
//-- backup variables

CParameters::CParameters(CWnd* pParent /*=NULL*/)
	: CDialog(CParameters::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParameters)
	m_GoalieRemoved = FALSE;
	m_Robot1Removed = FALSE;
	m_Robot2Removed = FALSE;
	m_ComPort = -1;
	m_CameraHeight = 0.0f;
	m_TrackOpponent = FALSE;
	m_NumOppoRobotsVal = 0;
	m_MinPatchSizeCol1Val = 0;
	m_MinPatchSizeCol2Val = 0;
	m_MinPatchSizeTeamVal = 0;
	m_MinPatchSizeBallVal = 0;
	m_MinPatchSizeOppoVal = 0;
	//}}AFX_DATA_INIT
}


void CParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParameters)
	DDX_Control(pDX, IDC_MINPATCHSIZEOPPO_SCROLLBAR, m_MinPatchSizeOppo);
	DDX_Control(pDX, IDC_MINPATCHSIZEBALL_SCROLLBAR, m_MinPatchSizeBall);
	DDX_Control(pDX, IDC_MINPATCHSIZETEAM_SCROLLBAR, m_MinPatchSizeTeam);
	DDX_Control(pDX, IDC_MINPATCHSIZECOL2_SCROLLBAR, m_MinPatchSizeCol2);
	DDX_Control(pDX, IDC_MINPATCHSIZECOL1_SCROLLBAR, m_MinPatchSizeCol1);
	DDX_Control(pDX, IDC_NUMOPPOROBOTS_SCROLLBAR, m_NumOppoRobots);
	DDX_Check(pDX, IDC_GOALIEREMOVED_CHECK, m_GoalieRemoved);
	DDX_Check(pDX, IDC_ROBOT1REMOVED_CHECK, m_Robot1Removed);
	DDX_Check(pDX, IDC_ROBOT2REMOVED_CHECK, m_Robot2Removed);
	DDX_Radio(pDX, IDC_COM1_RADIO, m_ComPort);
	DDX_Text(pDX, IDC_CAMERAHEIGHT_EDIT, m_CameraHeight);
	DDX_Check(pDX, IDC_TRACKOPPO_CHECK, m_TrackOpponent);
	DDX_Text(pDX, IDC_NUMOPPOROBOTS_EDIT, m_NumOppoRobotsVal);
	DDX_Text(pDX, IDC_MINPATCHSIZECOL1_EDIT, m_MinPatchSizeCol1Val);
	DDX_Text(pDX, IDC_MINPATCHSIZECOL2_EDIT, m_MinPatchSizeCol2Val);
	DDX_Text(pDX, IDC_MINPATCHSIZETEAM_EDIT, m_MinPatchSizeTeamVal);
	DDX_Text(pDX, IDC_MINPATCHSIZEBALL_EDIT, m_MinPatchSizeBallVal);
	DDX_Text(pDX, IDC_MINPATCHSIZEOPPO_EDIT, m_MinPatchSizeOppoVal);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParameters, CDialog)
	//{{AFX_MSG_MAP(CParameters)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_GOALIEREMOVED_CHECK, OnGoalieremovedCheck)
	ON_BN_CLICKED(IDC_ROBOT1REMOVED_CHECK, OnRobot1removedCheck)
	ON_BN_CLICKED(IDC_ROBOT2REMOVED_CHECK, OnRobot2removedCheck)
	ON_BN_CLICKED(IDC_COM1_RADIO, OnCom1Radio)
	ON_BN_CLICKED(IDC_COM2_RADIO, OnCom2Radio)
	ON_EN_CHANGE(IDC_CAMERAHEIGHT_EDIT, OnChangeCameraheightEdit)
	ON_BN_CLICKED(IDC_TRACKOPPO_CHECK, OnTrackoppoCheck)
	ON_EN_CHANGE(IDC_NUMOPPOROBOTS_EDIT, OnChangeNumopporobotsEdit)
	ON_EN_CHANGE(IDC_MINPATCHSIZECOL1_EDIT, OnChangeMinpatchsizecol1Edit)
	ON_EN_CHANGE(IDC_MINPATCHSIZECOL2_EDIT, OnChangeMinpatchsizecol2Edit)
	ON_EN_CHANGE(IDC_MINPATCHSIZETEAM_EDIT, OnChangeMinpatchsizeteamEdit)
	ON_EN_CHANGE(IDC_MINPATCHSIZEBALL_EDIT, OnChangeMinpatchsizeballEdit)
	ON_EN_CHANGE(IDC_MINPATCHSIZEOPPO_EDIT, OnChangeMinpatchsizeoppoEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParameters message handlers

BOOL CParameters::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//--  backup the variables - required when cancel chosen
	lMinPatchSizeCol1 = gMinPatchSizeCol1;
	lMinPatchSizeCol2 = gMinPatchSizeCol2;
	lMinPatchSizeTeam = gMinPatchSizeTeam;
	lMinPatchSizeBall = gMinPatchSizeBall;
	lMinPatchSizeOppo = gMinPatchSizeOppo;
	ComPort = globaldata.comport;
	GoalieRemoved = gRemoved.Goalie;
	Robot1Removed = gRemoved.Robot1;
	Robot2Removed = gRemoved.Robot2;
	TrackOpponent = gTrackOpponent;
	NumOppoRobots = gNumOppoRobots;
	CameraHeight = gCameraHeight;
	//-- backup over ------------------------------

	m_GoalieRemoved = gRemoved.Goalie;
	m_Robot1Removed = gRemoved.Robot1;
	m_Robot2Removed = gRemoved.Robot2;

	m_MinPatchSizeCol1.SetScrollRange(1,20);
	m_MinPatchSizeCol1.SetScrollPos(gMinPatchSizeCol1);
	m_MinPatchSizeCol1Val = gMinPatchSizeCol1;

	m_MinPatchSizeCol2.SetScrollRange(1,20);
	m_MinPatchSizeCol2.SetScrollPos(gMinPatchSizeCol2);
	m_MinPatchSizeCol2Val = gMinPatchSizeCol2;

	m_MinPatchSizeTeam.SetScrollRange(1,20);
	m_MinPatchSizeTeam.SetScrollPos(gMinPatchSizeTeam);
	m_MinPatchSizeTeamVal = gMinPatchSizeTeam;

	m_MinPatchSizeBall.SetScrollRange(1,20);
	m_MinPatchSizeBall.SetScrollPos(gMinPatchSizeBall);
	m_MinPatchSizeBallVal = gMinPatchSizeBall;

	m_MinPatchSizeOppo.SetScrollRange(1,20);
	m_MinPatchSizeOppo.SetScrollPos(gMinPatchSizeOppo);
	m_MinPatchSizeOppoVal = gMinPatchSizeOppo;

	m_ComPort = globaldata.comport;
	m_CameraHeight = gCameraHeight;

	//-- track opponent
	m_TrackOpponent = gTrackOpponent;

	m_NumOppoRobots.SetScrollRange(1,MAXROBOTS);
	m_NumOppoRobots.SetScrollPos(gNumOppoRobots);
	m_NumOppoRobotsVal = gNumOppoRobots;

	UpdateData(FALSE);//-- transfer control variables to screen

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CParameters::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int id = pScrollBar->GetDlgCtrlID();
	int JumpBy = 5;
	if (id == IDC_NUMOPPOROBOTS_SCROLLBAR) JumpBy = 1;

	int nCurPos = pScrollBar->GetScrollPos();	//-- current position

	switch (nSBCode)
	{
	case SB_LINELEFT:
			pScrollBar->SetScrollPos(nCurPos-1);
			break;
	case SB_LINERIGHT:
			pScrollBar->SetScrollPos(nCurPos+1);
			break;
	case SB_THUMBPOSITION:
			pScrollBar->SetScrollPos(nPos);
			break;
	case SB_PAGEUP:
			pScrollBar->SetScrollPos(nCurPos-JumpBy);
			break;
	case SB_PAGEDOWN:
			pScrollBar->SetScrollPos(nCurPos+JumpBy);
			break;
	}


	switch(id)
	{
	//-- Minimum Patch Size of Colour 1
	case IDC_MINPATCHSIZECOL1_SCROLLBAR:
						//-- transfer value to edit box
						m_MinPatchSizeCol1Val = pScrollBar->GetScrollPos();
						//-- now transfer value to global variable
						gMinPatchSizeCol1 = m_MinPatchSizeCol1Val;
						break;

	//-- Minimum Patch Size of Colour 2
	case IDC_MINPATCHSIZECOL2_SCROLLBAR:
						//-- transfer value to edit box
						m_MinPatchSizeCol2Val = pScrollBar->GetScrollPos();
						//-- now transfer value to global variable
						gMinPatchSizeCol2 = m_MinPatchSizeCol2Val;
						break;

	//-- Minimum Patch Size of Team Colour
	case IDC_MINPATCHSIZETEAM_SCROLLBAR:
						//-- transfer value to edit box
						m_MinPatchSizeTeamVal = pScrollBar->GetScrollPos();
						//-- now transfer value to global variable
						gMinPatchSizeTeam = m_MinPatchSizeTeamVal;
						break;

	//-- Minimum Patch Size of Ball Colour
	case IDC_MINPATCHSIZEBALL_SCROLLBAR:
						//-- transfer value to edit box
						m_MinPatchSizeBallVal = pScrollBar->GetScrollPos();
						//-- now transfer value to global variable
						gMinPatchSizeBall = m_MinPatchSizeBallVal;
						break;

	//-- Minimum Patch Size of Opponent Colour
	case IDC_MINPATCHSIZEOPPO_SCROLLBAR:
						//-- transfer value to edit box
						m_MinPatchSizeOppoVal = pScrollBar->GetScrollPos();
						//-- now transfer value to global variable
						gMinPatchSizeOppo = m_MinPatchSizeOppoVal;
						break;

	//-- Number of opponent robots
	case IDC_NUMOPPOROBOTS_SCROLLBAR:
						//-- transfer value to edit box
						m_NumOppoRobotsVal = pScrollBar->GetScrollPos();
						//-- now transfer value to global variable
						gNumOppoRobots = m_NumOppoRobotsVal;
						break;
	}	//-- end of switch statement

	UpdateData(false); //-- update the edit-box display	

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CParameters::OnCom1Radio() 
{
	UpdateData(TRUE);
	globaldata.comport = COM1;
}

void CParameters::OnCom2Radio() 
{
	UpdateData(TRUE);
	globaldata.comport = COM2;
}

void CParameters::OnGoalieremovedCheck() 
{
	UpdateData(TRUE);	//-- transfer screen position to variables
	gRemoved.Goalie = m_GoalieRemoved;
}

void CParameters::OnRobot1removedCheck() 
{
	UpdateData(TRUE);	//-- transfer screen position to variables
	gRemoved.Robot1 = m_Robot1Removed;
}

void CParameters::OnRobot2removedCheck() 
{
	UpdateData(TRUE);	//-- transfer screen position to variables
	gRemoved.Robot2 = m_Robot2Removed;
}

void CParameters::OnTrackoppoCheck() 
{
	UpdateData(TRUE);
	gTrackOpponent = m_TrackOpponent;	
}

void CParameters::OnCancel() 
{
	//-- restore the variables from the backup
	gMinPatchSizeCol1 = lMinPatchSizeCol1;
	gMinPatchSizeCol2 = lMinPatchSizeCol2;
	gMinPatchSizeTeam = lMinPatchSizeTeam;
	gMinPatchSizeBall = lMinPatchSizeBall;
	gMinPatchSizeOppo = lMinPatchSizeOppo;
	globaldata.comport = ComPort;

	gRemoved.Goalie = GoalieRemoved;
	gRemoved.Robot1 = Robot1Removed;
	gRemoved.Robot2 = Robot2Removed;
	
	gCameraHeight = CameraHeight;

	gTrackOpponent = TrackOpponent;
	gNumOppoRobots = NumOppoRobots;
	//-- variables restoration over

	CDialog::OnCancel();
}

void CParameters::OnOK() 
{
	UpdateData(TRUE);	//-- transfer screen position to variables
	gRemoved.Goalie = m_GoalieRemoved;
	gRemoved.Robot1 = m_Robot1Removed;
	gRemoved.Robot2 = m_Robot2Removed;
	gTrackOpponent = m_TrackOpponent;

	//-- calculate the number of robots in play
	gNumRobots = MAXROBOTS;
	if (gRemoved.Goalie) gNumRobots--;
	if (gRemoved.Robot1) gNumRobots--;
	if (gRemoved.Robot2) gNumRobots--;

	//-- COM port might have been changed
	if (globaldata.comport != ComPort)	//-- COM port has changed
	{
		closeSerialPort();
		openSerialPort();
	}

	MessageBeep( (WORD) -1 );
	CDialog::OnOK();
}

void CParameters::OnChangeCameraheightEdit() 
{
	UpdateData(true);
	gCameraHeight = m_CameraHeight;
}

void CParameters::OnChangeNumopporobotsEdit() 
{
	UpdateData(true);
	m_NumOppoRobots.SetScrollPos(m_NumOppoRobotsVal);
	gNumOppoRobots = m_NumOppoRobotsVal;	
}

void CParameters::OnChangeMinpatchsizecol1Edit() 
{
	UpdateData(true);
	m_MinPatchSizeCol1.SetScrollPos(m_MinPatchSizeCol1Val);
	gMinPatchSizeCol1 = m_MinPatchSizeCol1Val;
}

void CParameters::OnChangeMinpatchsizecol2Edit() 
{
	UpdateData(true);
	m_MinPatchSizeCol2.SetScrollPos(m_MinPatchSizeCol2Val);
	gMinPatchSizeCol2 = m_MinPatchSizeCol2Val;
}

void CParameters::OnChangeMinpatchsizeteamEdit() 
{
	UpdateData(true);
	m_MinPatchSizeTeam.SetScrollPos(m_MinPatchSizeTeamVal);
	gMinPatchSizeTeam = m_MinPatchSizeTeamVal;
}

void CParameters::OnChangeMinpatchsizeballEdit() 
{
	UpdateData(true);
	m_MinPatchSizeBall.SetScrollPos(m_MinPatchSizeBallVal);
	gMinPatchSizeBall = m_MinPatchSizeBallVal;
}

void CParameters::OnChangeMinpatchsizeoppoEdit() 
{
	UpdateData(true);
	m_MinPatchSizeOppo.SetScrollPos(m_MinPatchSizeOppoVal);
	gMinPatchSizeOppo = m_MinPatchSizeOppoVal;
}
