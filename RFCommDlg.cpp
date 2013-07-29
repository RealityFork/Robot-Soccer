// RFCommDlg.cpp : implementation file
//

#include "stdafx.h"
#include "myrosot1.h"
#include "RFCommDlg.h"
#include "vision.h"
#include "mmsystem.h"

#include "commondata.h"
#include "RFComm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRFCommDlg dialog


CRFCommDlg::CRFCommDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRFCommDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRFCommDlg)
	m_GoalieLVal = 0;
	m_Robot1RVal = 0;
	m_Robot1LVal = 0;
	m_Robot2RVal = 0;
	m_Robot2LVal = 0;
	m_GoalieRVal = 0;
	m_SpeedVal = 0;
	//}}AFX_DATA_INIT
}


void CRFCommDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRFCommDlg)
	DDX_Control(pDX, IDC_SPEED_SCROLLBAR, m_Speed);
	DDX_Control(pDX, IDC_ROBOT2L_SCROLLBAR, m_Robot2L);
	DDX_Control(pDX, IDC_ROBOT2R_SCROLLBAR, m_Robot2R);
	DDX_Control(pDX, IDC_ROBOT1L_SCROLLBAR, m_Robot1L);
	DDX_Control(pDX, IDC_ROBOT1R_SCROLLBAR, m_Robot1R);
	DDX_Control(pDX, IDC_GOALIEL_SCROLLBAR, m_GoalieL);
	DDX_Control(pDX, IDC_GOALIER_SCROLLBAR, m_GoalieR);
	DDX_Text(pDX, IDC_GOALIEL_EDIT, m_GoalieLVal);
	DDV_MinMaxInt(pDX, m_GoalieLVal, -127, 127);
	DDX_Text(pDX, IDC_ROBOT1R_EDIT, m_Robot1RVal);
	DDV_MinMaxInt(pDX, m_Robot1RVal, -127, 127);
	DDX_Text(pDX, IDC_ROBOT1L_EDIT, m_Robot1LVal);
	DDV_MinMaxInt(pDX, m_Robot1LVal, -127, 127);
	DDX_Text(pDX, IDC_ROBOT2R_EDIT, m_Robot2RVal);
	DDV_MinMaxInt(pDX, m_Robot2RVal, -127, 127);
	DDX_Text(pDX, IDC_ROBOT2L_EDIT, m_Robot2LVal);
	DDV_MinMaxInt(pDX, m_Robot2LVal, -127, 127);
	DDX_Text(pDX, IDC_GOALIER_EDIT, m_GoalieRVal);
	DDV_MinMaxInt(pDX, m_GoalieRVal, -127, 127);
	DDX_Text(pDX, IDC_SPEED_EDIT, m_SpeedVal);
	DDV_MinMaxInt(pDX, m_SpeedVal, 0, 127);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRFCommDlg, CDialog)
	//{{AFX_MSG_MAP(CRFCommDlg)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_GOALIEL_EDIT, OnChangeGoalielEdit)
	ON_EN_CHANGE(IDC_GOALIER_EDIT, OnChangeGoalierEdit)
	ON_EN_CHANGE(IDC_ROBOT1L_EDIT, OnChangeRobot1lEdit)
	ON_EN_CHANGE(IDC_ROBOT1R_EDIT, OnChangeRobot1rEdit)
	ON_EN_CHANGE(IDC_ROBOT2L_EDIT, OnChangeRobot2lEdit)
	ON_EN_CHANGE(IDC_ROBOT2R_EDIT, OnChangeRobot2rEdit)
	ON_BN_CLICKED(IDC_SEND_BUTTON, OnSendButton)
	ON_BN_CLICKED(IDC_STOP_BUTTON, OnStopButton)
	ON_BN_CLICKED(IDC_FORWARD_BUTTON, OnForwardButton)
	ON_BN_CLICKED(IDC_REVERSE_BUTTON, OnReverseButton)
	ON_BN_CLICKED(IDC_TURNLEFT_BUTTON, OnTurnleftButton)
	ON_BN_CLICKED(IDC_TURNRIGHT_BUTTON, OnTurnrightButton)
	ON_EN_CHANGE(IDC_SPEED_EDIT, OnChangeSpeedEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRFCommDlg message handlers

BOOL CRFCommDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//-- Goalie Speed Scroll Bars and Edit Boxes
	m_GoalieL.SetScrollRange(-127, 127);
	m_GoalieL.SetScrollPos(0);
	m_GoalieLVal = 0;
	m_GoalieR.SetScrollRange(-127, 127);
	m_GoalieR.SetScrollPos(0);
	m_GoalieRVal = 0;

	//-- Robot1 Speed Scroll Bars and Edit Boxes
	m_Robot1L.SetScrollRange(-127, 127);
	m_Robot1L.SetScrollPos(0);
	m_Robot1LVal = 0;
	m_Robot1R.SetScrollRange(-127, 127);
	m_Robot1R.SetScrollPos(0);
	m_Robot1RVal = 0;

	//-- Robot2 Speed Scroll Bars and Edit Boxes
	m_Robot2L.SetScrollRange(-127, 127);
	m_Robot2L.SetScrollPos(0);
	m_Robot2LVal = 0;
	m_Robot2R.SetScrollRange(-127, 127);
	m_Robot2R.SetScrollPos(0);
	m_Robot2RVal = 0;

	//-- Speed Scroll Bar and Edit Box
	m_Speed.SetScrollRange(0, 127);
	m_Speed.SetScrollPos(8);
	m_SpeedVal = 8;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRFCommDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
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
			pScrollBar->SetScrollPos(nCurPos-5);
			break;
	case SB_PAGEDOWN:
			pScrollBar->SetScrollPos(nCurPos+5);
			break;
	}

	int id = pScrollBar->GetDlgCtrlID();
	switch(id)
	{
	//-- Goalie
	case IDC_GOALIEL_SCROLLBAR:
						m_GoalieLVal = pScrollBar->GetScrollPos();
						break;
	case IDC_GOALIER_SCROLLBAR:
						m_GoalieRVal = pScrollBar->GetScrollPos();
						break;
	//-- ROBOT1
	case IDC_ROBOT1L_SCROLLBAR:
						m_Robot1LVal = pScrollBar->GetScrollPos();
						break;
	case IDC_ROBOT1R_SCROLLBAR:
						m_Robot1RVal = pScrollBar->GetScrollPos();
						break;

	//-- ROBOT2
	case IDC_ROBOT2L_SCROLLBAR:
						m_Robot2LVal = pScrollBar->GetScrollPos();
						break;
	case IDC_ROBOT2R_SCROLLBAR:
						m_Robot2RVal = pScrollBar->GetScrollPos();
						break;

	//-- SPEED Scroll Bar
	case IDC_SPEED_SCROLLBAR:
						m_SpeedVal = pScrollBar->GetScrollPos();
						break;

	}	//-- end of switch statement

	UpdateData(false); //-- update the edit-box display
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CRFCommDlg::OnChangeGoalielEdit() 
{
	UpdateData(true);
	m_GoalieL.SetScrollPos(m_GoalieLVal);
}

void CRFCommDlg::OnChangeGoalierEdit() 
{
	UpdateData(true);
	m_GoalieR.SetScrollPos(m_GoalieRVal);
}

void CRFCommDlg::OnChangeRobot1lEdit() 
{
	UpdateData(true);
	m_Robot1L.SetScrollPos(m_Robot1LVal);
}

void CRFCommDlg::OnChangeRobot1rEdit() 
{
	UpdateData(true);
	m_Robot1R.SetScrollPos(m_Robot1RVal);
}

void CRFCommDlg::OnChangeRobot2lEdit() 
{
	UpdateData(true);
	m_Robot2L.SetScrollPos(m_Robot2LVal);
}

void CRFCommDlg::OnChangeRobot2rEdit() 
{
	UpdateData(true);
	m_Robot2R.SetScrollPos(m_Robot2RVal);
}

void CRFCommDlg::OnChangeSpeedEdit() 
{
	UpdateData(true);
	m_Speed.SetScrollPos(m_SpeedVal);
}

void CRFCommDlg::OnSendButton() 
{
	//-- goalie
	globaldata.packet[2] = (char) m_GoalieLVal;
	globaldata.packet[3] = (char) m_GoalieRVal;

	//-- robot1
	globaldata.packet[6] = (char) m_Robot1LVal;
	globaldata.packet[7] = (char) m_Robot1RVal;
	
	//-- robot2
	globaldata.packet[10] = (char) m_Robot2LVal;
	globaldata.packet[11] = (char) m_Robot2RVal;

	SendPacket();
}

void CRFCommDlg::OnStopButton()
{
	globaldata.packet[2] = 0x00;
	globaldata.packet[3] = 0x00;

	globaldata.packet[6] = 0x00;
	globaldata.packet[7] = 0x00;

	globaldata.packet[10] = 0x00;
	globaldata.packet[11] = 0x00;
	
	SendPacket();
}

void CRFCommDlg::OnForwardButton() 
{
	//-- goalie
	globaldata.packet[2] = (char) m_SpeedVal;
	globaldata.packet[3] = (char) m_SpeedVal;

	//-- robot1
	globaldata.packet[6] = (char) m_SpeedVal;
	globaldata.packet[7] = (char) m_SpeedVal;
	
	//-- robot2
	globaldata.packet[10] = (char) m_SpeedVal;
	globaldata.packet[11] = (char) m_SpeedVal;

	SendPacket();
}

void CRFCommDlg::OnReverseButton()
{
	//-- goalie
	globaldata.packet[2]=(char) -m_SpeedVal;
	globaldata.packet[3]=(char) -m_SpeedVal;

	//-- robot1
	globaldata.packet[6]=(char) -m_SpeedVal;
	globaldata.packet[7]=(char) -m_SpeedVal;

	//-- robot2
	globaldata.packet[10]=(char) -m_SpeedVal;
	globaldata.packet[11]=(char) -m_SpeedVal;

	SendPacket();
}

void CRFCommDlg::OnTurnleftButton() 
{
	globaldata.packet[2]=(char) -m_SpeedVal;
	globaldata.packet[3]=(char) m_SpeedVal;

	globaldata.packet[6]=(char) -m_SpeedVal;
	globaldata.packet[7]=(char) m_SpeedVal;

	globaldata.packet[10]=(char) -m_SpeedVal;
	globaldata.packet[11]=(char) m_SpeedVal;

	SendPacket();
}

void CRFCommDlg::OnTurnrightButton() 
{
	globaldata.packet[2]=(char) m_SpeedVal;
	globaldata.packet[3]=(char) -m_SpeedVal;

	globaldata.packet[6]=(char) m_SpeedVal;
	globaldata.packet[7]=(char) -m_SpeedVal;

	globaldata.packet[10]=(char) m_SpeedVal;
	globaldata.packet[11]=(char) -m_SpeedVal;

	SendPacket();
}

void CRFCommDlg::OnOK() 
{
	//-- before closing the RF Comm Dialog Box, set the speed for
	//-- all the robots to zero. (same as Stop Button)
	OnStopButton();

	CDialog::OnOK();
}
