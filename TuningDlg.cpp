// TuningDlg.cpp : implementation file
//
#include "stdafx.h"
#include "TuningDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTuningDlg dialog


//-- create backup variables -----------------------
GoalieActionparameters lGoalieActionParameters;	//-- for CGoalieAction
BOOL lParallaxCorrectionEnabled;
BOOL lStopRobotsWhenBallLost;
BOOL lGoalieFollowClick;
float lBallClearTime;
startPhaseVal lstartPhaseVal[5];
//-- backup variables created -----------------------


CTuningDlg::CTuningDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTuningDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTuningDlg)
	m_GXcompensationVal = 0.0f;
	m_GBehaviour = -1;
	m_ParallaxCorrectionEnabled = FALSE;
	m_StopRobotsWhenBallLost = FALSE;
	m_BallClearTimeVal = 0.0f;
	m_KickstartSpeedVal = 0;
	m_KickstartDistanceVal = 0.0f;
	m_GoalkickDistanceVal = 0.0f;
	m_GoalkickSpeedVal = 0;
	m_PenaltyDistanceVal = 0.0f;
	m_PenaltySpeedVal = 0;
	m_FreekickDistanceVal = 0.0f;
	m_FreekickSpeedVal = 0;
	m_FreeballDistanceVal = 0.0f;
	m_FreeballSpeedVal = 0;
	m_GoalieFollowClick = FALSE;
	//}}AFX_DATA_INIT
}


void CTuningDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTuningDlg)
	DDX_Control(pDX, IDC_FREEBALLSPEED_SCROLLBAR, m_FreeballSpeed);
	DDX_Control(pDX, IDC_FREEBALLDISTANCE_SCROLLBAR, m_FreeballDistance);
	DDX_Control(pDX, IDC_FREEKICKSPEED_SCROLLBAR, m_FreekickSpeed);
	DDX_Control(pDX, IDC_FREEKICKDISTANCE_SCROLLBAR, m_FreekickDistance);
	DDX_Control(pDX, IDC_PENALTYSPEED_SCROLLBAR, m_PenaltySpeed);
	DDX_Control(pDX, IDC_PENALTYDISTANCE_SCROLLBAR, m_PenaltyDistance);
	DDX_Control(pDX, IDC_GOALKICKSPEED_SCROLLBAR, m_GoalkickSpeed);
	DDX_Control(pDX, IDC_GOALKICKDISTANCE_SCROLLBAR, m_GoalkickDistance);
	DDX_Control(pDX, IDC_KICKSTARTDISTANCE_SCROLLBAR, m_KickstartDistance);
	DDX_Control(pDX, IDC_KICKSTARTSPEED_SCROLLBAR, m_KickstartSpeed);
	DDX_Control(pDX, IDC_BALLCLEARTIME_SCROLLBAR, m_BallClearTime);
	DDX_Control(pDX, IDC_GXCOMPENSATION_SCROLLBAR, m_GXcompensation);
	DDX_Text(pDX, IDC_GXCOMPENSATION_EDIT, m_GXcompensationVal);
	DDX_Radio(pDX, IDC_CONSERVATIVE_RADIO, m_GBehaviour);
	DDX_Check(pDX, IDC_PARALLAXCORRECTION_CHECK, m_ParallaxCorrectionEnabled);
	DDX_Check(pDX, IDC_STOPROBOTSWHENBALLLOST_CHECK, m_StopRobotsWhenBallLost);
	DDX_Text(pDX, IDC_BALLCLEARTIME_EDIT, m_BallClearTimeVal);
	DDX_Text(pDX, IDC_KICKSTARTSPEED_EDIT, m_KickstartSpeedVal);
	DDX_Text(pDX, IDC_KICKSTARTDISTANCE_EDIT, m_KickstartDistanceVal);
	DDX_Text(pDX, IDC_GOALKICKDISTANCE_EDIT, m_GoalkickDistanceVal);
	DDX_Text(pDX, IDC_GOALKICKSPEED_EDIT, m_GoalkickSpeedVal);
	DDX_Text(pDX, IDC_PENALTYDISTANCE_EDIT, m_PenaltyDistanceVal);
	DDX_Text(pDX, IDC_PENALTYSPEED_EDIT, m_PenaltySpeedVal);
	DDX_Text(pDX, IDC_FREEKICKDISTANCE_EDIT, m_FreekickDistanceVal);
	DDX_Text(pDX, IDC_FREEKICKSPEED_EDIT, m_FreekickSpeedVal);
	DDX_Text(pDX, IDC_FREEBALLDISTANCE_EDIT, m_FreeballDistanceVal);
	DDX_Text(pDX, IDC_FREEBALLSPEED_EDIT, m_FreeballSpeedVal);
	DDX_Check(pDX, IDC_FOLLOWCLICK_CHECK, m_GoalieFollowClick);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTuningDlg, CDialog)
	//{{AFX_MSG_MAP(CTuningDlg)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CONSERVATIVE_RADIO, OnConservativeRadio)
	ON_BN_CLICKED(IDC_NORMAL_RADIO, OnNormalRadio)
	ON_BN_CLICKED(IDC_AGGRESSIVE_RADIO, OnAggressiveRadio)
	ON_BN_CLICKED(IDC_PARALLAXCORRECTION_CHECK, OnParallaxcorrectionCheck)
	ON_BN_CLICKED(IDC_STOPROBOTSWHENBALLLOST_CHECK, OnStoprobotswhenballlostCheck)
	ON_EN_CHANGE(IDC_BALLCLEARTIME_EDIT, OnChangeBallcleartimeEdit)
	ON_BN_CLICKED(IDC_DEFAULT_BUTTON, OnDefaultButton)
	ON_BN_CLICKED(IDC_FOLLOWCLICK_CHECK, OnFollowclickCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTuningDlg message handlers

BOOL CTuningDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//--  backup the variables - required when cancel button chosen
	lGoalieActionParameters = gGoalieActionParameters;

	lParallaxCorrectionEnabled= gParallaxCorrectionEnabled;
	lStopRobotsWhenBallLost = gStopRobotsWhenBallLost;
	lGoalieFollowClick = gGoalieFollowClick;
	lBallClearTime = gBallClearTime;
	for (int i=KICKSTART; i<=FREEBALL; i++)
	{
		lstartPhaseVal[i].kickdistance = gstartPhaseVal[i].kickdistance;
		lstartPhaseVal[i].kickspeed = gstartPhaseVal[i].kickspeed;
	}
	//-- backup over ------------------------------

	//------ CGoalieAction parameters
	m_GXcompensation.SetScrollRange(0, 40);	//-- 0 to 4 cms
	m_GXcompensation.SetScrollPos( (int) (gGoalieActionParameters.GXcompensation*10) );
	m_GXcompensationVal = (float) (gGoalieActionParameters.GXcompensation );

	m_BallClearTime.SetScrollRange(0, 100);	//-- 0 to 10 seconds
	m_BallClearTime.SetScrollPos( (int)(gBallClearTime*10) );
	m_BallClearTimeVal = gBallClearTime;

	//-- Kick Start
	m_KickstartDistance.SetScrollRange(1, 150); //1 to 150 cms
	m_KickstartDistance.SetScrollPos( (int) (gstartPhaseVal[KICKSTART].kickdistance) );
	m_KickstartDistanceVal = (float) gstartPhaseVal[KICKSTART].kickdistance;

	m_KickstartSpeed.SetScrollRange(1, 200); //1 to 200
	m_KickstartSpeed.SetScrollPos(gstartPhaseVal[KICKSTART].kickspeed);
	m_KickstartSpeedVal = gstartPhaseVal[KICKSTART].kickspeed;

	//-- Goal Kick
	m_GoalkickDistance.SetScrollRange(1, 150); //1 to 150 cms
	m_GoalkickDistance.SetScrollPos( (int) (gstartPhaseVal[GOALKICK].kickdistance) );
	m_GoalkickDistanceVal = (float) gstartPhaseVal[GOALKICK].kickdistance;

	m_GoalkickSpeed.SetScrollRange(1, 200); //1 to 200
	m_GoalkickSpeed.SetScrollPos(gstartPhaseVal[GOALKICK].kickspeed);
	m_GoalkickSpeedVal = gstartPhaseVal[GOALKICK].kickspeed;

	//-- Penalty
	m_PenaltyDistance.SetScrollRange(1, 150); //1 to 150 cms
	m_PenaltyDistance.SetScrollPos( (int) (gstartPhaseVal[PENALTY].kickdistance) );
	m_PenaltyDistanceVal = (float) gstartPhaseVal[PENALTY].kickdistance;

	m_PenaltySpeed.SetScrollRange(1, 200); //1 to 200
	m_PenaltySpeed.SetScrollPos(gstartPhaseVal[PENALTY].kickspeed);
	m_PenaltySpeedVal = gstartPhaseVal[PENALTY].kickspeed;

	//-- Free Kick
	m_FreekickDistance.SetScrollRange(1, 150); //1 to 150 cms
	m_FreekickDistance.SetScrollPos( (int) (gstartPhaseVal[FREEKICK].kickdistance) );
	m_FreekickDistanceVal = (float) gstartPhaseVal[FREEKICK].kickdistance;

	m_FreekickSpeed.SetScrollRange(1, 200); //1 to 200
	m_FreekickSpeed.SetScrollPos(gstartPhaseVal[FREEKICK].kickspeed);
	m_FreekickSpeedVal = gstartPhaseVal[FREEKICK].kickspeed;

	//-- Free Ball
	m_FreeballDistance.SetScrollRange(1, 150); //1 to 150 cms
	m_FreeballDistance.SetScrollPos( (int) (gstartPhaseVal[FREEBALL].kickdistance) );
	m_FreeballDistanceVal = (float) gstartPhaseVal[FREEBALL].kickdistance;

	m_FreeballSpeed.SetScrollRange(1, 200); //1 to 200
	m_FreeballSpeed.SetScrollPos(gstartPhaseVal[FREEBALL].kickspeed);
	m_FreeballSpeedVal = gstartPhaseVal[FREEBALL].kickspeed;

	//------------------ Scroll Bars settings done ---------------

	m_GBehaviour = gGoalieActionParameters.GBehaviour; //-- radio button

	m_ParallaxCorrectionEnabled = gParallaxCorrectionEnabled;
	m_StopRobotsWhenBallLost = gStopRobotsWhenBallLost;
	m_GoalieFollowClick = gGoalieFollowClick;

	UpdateData(FALSE);//-- transfer control variables to screen

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTuningDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int id = pScrollBar->GetDlgCtrlID();
	int JumpBy = 1;
	if (id == IDC_BALLCLEARTIME_SCROLLBAR ||
		id == IDC_KICKSTARTDISTANCE_SCROLLBAR ||
		id == IDC_KICKSTARTSPEED_SCROLLBAR ||
		id == IDC_GOALKICKDISTANCE_SCROLLBAR ||
		id == IDC_GOALKICKSPEED_SCROLLBAR ||
		id == IDC_PENALTYDISTANCE_SCROLLBAR ||
		id == IDC_PENALTYSPEED_SCROLLBAR ||
		id == IDC_FREEKICKDISTANCE_SCROLLBAR ||
		id == IDC_FREEKICKSPEED_SCROLLBAR ||
		id == IDC_FREEBALLDISTANCE_SCROLLBAR ||
		id == IDC_FREEBALLSPEED_SCROLLBAR
		) JumpBy = 5;

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
	//-- CGoalieAction XCompensation
	case IDC_GXCOMPENSATION_SCROLLBAR:
						//-- transfer value to edit box
						m_GXcompensationVal = (float)(pScrollBar->GetScrollPos()/10.0);
						//-- now transfer value to global variable
						gGoalieActionParameters.GXcompensation = m_GXcompensationVal;
						break;

	case IDC_BALLCLEARTIME_SCROLLBAR:
						//-- transfer value to edit box
						m_BallClearTimeVal = (float)(pScrollBar->GetScrollPos()/10.0);
						//-- now transfer value to global variable
						gBallClearTime = m_BallClearTimeVal;
						break;

	//-- Kick Start
	case IDC_KICKSTARTDISTANCE_SCROLLBAR:
						//-- transfer value to edit box
						m_KickstartDistanceVal = (float)(pScrollBar->GetScrollPos());
						//-- now transfer value to global variable
						gstartPhaseVal[KICKSTART].kickdistance = m_KickstartDistanceVal;
						break;
	case IDC_KICKSTARTSPEED_SCROLLBAR:
						//-- transfer value to edit box
						m_KickstartSpeedVal = pScrollBar->GetScrollPos();
						//-- now transfer value to global variable
						gstartPhaseVal[KICKSTART].kickspeed = m_KickstartSpeedVal;
						break;

	//-- Goal Kick
	case IDC_GOALKICKDISTANCE_SCROLLBAR:
						//-- transfer value to edit box
						m_GoalkickDistanceVal = (float)(pScrollBar->GetScrollPos());
						//-- now transfer value to global variable
						gstartPhaseVal[GOALKICK].kickdistance = m_GoalkickDistanceVal;
						break;
	case IDC_GOALKICKSPEED_SCROLLBAR:
						//-- transfer value to edit box
						m_GoalkickSpeedVal = pScrollBar->GetScrollPos();
						//-- now transfer value to global variable
						gstartPhaseVal[GOALKICK].kickspeed = m_GoalkickSpeedVal;
						break;

	//-- Penalty
	case IDC_PENALTYDISTANCE_SCROLLBAR:
						//-- transfer value to edit box
						m_PenaltyDistanceVal = (float)(pScrollBar->GetScrollPos());
						//-- now transfer value to global variable
						gstartPhaseVal[PENALTY].kickdistance = m_PenaltyDistanceVal;
						break;
	case IDC_PENALTYSPEED_SCROLLBAR:
						//-- transfer value to edit box
						m_PenaltySpeedVal = pScrollBar->GetScrollPos();
						//-- now transfer value to global variable
						gstartPhaseVal[PENALTY].kickspeed = m_PenaltySpeedVal;
						break;

	//-- Free Kick
	case IDC_FREEKICKDISTANCE_SCROLLBAR:
						//-- transfer value to edit box
						m_FreekickDistanceVal = (float)(pScrollBar->GetScrollPos());
						//-- now transfer value to global variable
						gstartPhaseVal[FREEKICK].kickdistance = m_FreekickDistanceVal;
						break;
	case IDC_FREEKICKSPEED_SCROLLBAR:
						//-- transfer value to edit box
						m_FreekickSpeedVal = pScrollBar->GetScrollPos();
						//-- now transfer value to global variable
						gstartPhaseVal[FREEKICK].kickspeed = m_FreekickSpeedVal;
						break;

	//-- Free Ball
	case IDC_FREEBALLDISTANCE_SCROLLBAR:
						//-- transfer value to edit box
						m_FreeballDistanceVal = (float)(pScrollBar->GetScrollPos());
						//-- now transfer value to global variable
						gstartPhaseVal[FREEBALL].kickdistance = m_FreeballDistanceVal;
						break;
	case IDC_FREEBALLSPEED_SCROLLBAR:
						//-- transfer value to edit box
						m_FreeballSpeedVal = pScrollBar->GetScrollPos();
						//-- now transfer value to global variable
						gstartPhaseVal[FREEBALL].kickspeed = m_FreeballSpeedVal;
						break;

	}	//-- end of switch statement

	UpdateData(false); //-- update the edit-box display	

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CTuningDlg::OnCancel() 
{
	//-- restore the variables from the backup ----
	gGoalieActionParameters = lGoalieActionParameters;
	gParallaxCorrectionEnabled= lParallaxCorrectionEnabled;
	gStopRobotsWhenBallLost = lStopRobotsWhenBallLost;
	gGoalieFollowClick = lGoalieFollowClick;
	gBallClearTime = lBallClearTime;
	for (int i=KICKSTART; i<=FREEBALL; i++)
	{
		gstartPhaseVal[i].kickdistance = lstartPhaseVal[i].kickdistance;
		gstartPhaseVal[i].kickspeed = lstartPhaseVal[i].kickspeed;
	}
	//-- variables restoration over----------------

	CDialog::OnCancel();
}

void CTuningDlg::OnOK() 
{
	UpdateData(TRUE);	//-- transfer screen position to variables

	gGoalieActionParameters.GXcompensation = m_GXcompensationVal;
	gGoalieActionParameters.GBehaviour = m_GBehaviour;
	gBallClearTime = m_BallClearTimeVal;

	gstartPhaseVal[KICKSTART].kickdistance = m_KickstartDistanceVal;
	gstartPhaseVal[KICKSTART].kickspeed = m_KickstartSpeedVal;

	gstartPhaseVal[GOALKICK].kickdistance = m_GoalkickDistanceVal;
	gstartPhaseVal[GOALKICK].kickspeed = m_GoalkickSpeedVal;

	gstartPhaseVal[PENALTY].kickdistance = m_PenaltyDistanceVal;
	gstartPhaseVal[PENALTY].kickspeed = m_PenaltySpeedVal;

	gstartPhaseVal[FREEKICK].kickdistance = m_FreekickDistanceVal;
	gstartPhaseVal[FREEKICK].kickspeed = m_FreekickSpeedVal;

	gstartPhaseVal[FREEBALL].kickdistance = m_FreeballDistanceVal;
	gstartPhaseVal[FREEBALL].kickspeed = m_FreeballSpeedVal;

	MessageBeep( (WORD) -1 );
	CDialog::OnOK();
}

void CTuningDlg::OnConservativeRadio() 
{
	UpdateData(TRUE);
	gGoalieActionParameters.GBehaviour = 0;	//-- conservative
}

void CTuningDlg::OnNormalRadio() 
{
	UpdateData(TRUE);
	gGoalieActionParameters.GBehaviour = 1;	//-- normal
}

void CTuningDlg::OnAggressiveRadio() 
{
	UpdateData(TRUE);
	gGoalieActionParameters.GBehaviour = 2;	//-- Aggressive
}

void CTuningDlg::OnParallaxcorrectionCheck() 
{
	UpdateData(true);
	gParallaxCorrectionEnabled = m_ParallaxCorrectionEnabled;
}

void CTuningDlg::OnStoprobotswhenballlostCheck() 
{
	UpdateData(true);
	gStopRobotsWhenBallLost = m_StopRobotsWhenBallLost;
}

void CTuningDlg::OnFollowclickCheck() 
{
	UpdateData(true);
	gGoalieFollowClick = m_GoalieFollowClick;
}

void CTuningDlg::OnChangeBallcleartimeEdit() 
{
	UpdateData(true);
	m_BallClearTime.SetScrollPos( (int)(m_BallClearTimeVal*10.0) );
	gBallClearTime = m_BallClearTimeVal;
}

void CTuningDlg::OnDefaultButton() 
{
	gstartPhaseVal[GOALKICK].kickdistance = 75;
	gstartPhaseVal[GOALKICK].kickspeed = 100;

	gstartPhaseVal[PENALTY].kickdistance = 30;
	gstartPhaseVal[PENALTY].kickspeed = 113;

	gstartPhaseVal[FREEKICK].kickdistance = 40;
	gstartPhaseVal[FREEKICK].kickspeed = 113;

	gstartPhaseVal[FREEBALL].kickdistance = 5;
	gstartPhaseVal[FREEBALL].kickspeed = 80;

	gstartPhaseVal[KICKSTART].kickdistance = 8;
	gstartPhaseVal[KICKSTART].kickspeed = 8;

	//-- Kick Start
	m_KickstartDistance.SetScrollPos( (int) (gstartPhaseVal[KICKSTART].kickdistance) );
	m_KickstartDistanceVal = (float) gstartPhaseVal[KICKSTART].kickdistance;

	m_KickstartSpeed.SetScrollPos(gstartPhaseVal[KICKSTART].kickspeed);
	m_KickstartSpeedVal = gstartPhaseVal[KICKSTART].kickspeed;

	//-- Goal Kick
	m_GoalkickDistance.SetScrollPos( (int) (gstartPhaseVal[GOALKICK].kickdistance) );
	m_GoalkickDistanceVal = (float) gstartPhaseVal[GOALKICK].kickdistance;

	m_GoalkickSpeed.SetScrollPos(gstartPhaseVal[GOALKICK].kickspeed);
	m_GoalkickSpeedVal = gstartPhaseVal[GOALKICK].kickspeed;

	//-- Penalty
	m_PenaltyDistance.SetScrollPos( (int) (gstartPhaseVal[PENALTY].kickdistance) );
	m_PenaltyDistanceVal = (float) gstartPhaseVal[PENALTY].kickdistance;

	m_PenaltySpeed.SetScrollPos(gstartPhaseVal[PENALTY].kickspeed);
	m_PenaltySpeedVal = gstartPhaseVal[PENALTY].kickspeed;

	//-- Free Kick
	m_FreekickDistance.SetScrollPos( (int) (gstartPhaseVal[FREEKICK].kickdistance) );
	m_FreekickDistanceVal = (float) gstartPhaseVal[FREEKICK].kickdistance;

	m_FreekickSpeed.SetScrollPos(gstartPhaseVal[FREEKICK].kickspeed);
	m_FreekickSpeedVal = gstartPhaseVal[FREEKICK].kickspeed;

	//-- Free Ball
	m_FreeballDistance.SetScrollPos( (int) (gstartPhaseVal[FREEBALL].kickdistance) );
	m_FreeballDistanceVal = (float) gstartPhaseVal[FREEBALL].kickdistance;

	m_FreeballSpeed.SetScrollPos(gstartPhaseVal[FREEBALL].kickspeed);
	m_FreeballSpeedVal = gstartPhaseVal[FREEBALL].kickspeed;

	UpdateData(FALSE);//-- transfer control variables to screen
}
