// AdjColDlg.cpp : implementation file
//

#include "stdafx.h"
#include "myrosot1.h"
#include "AdjColDlg.h"

#include "commondata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdjColDlg dialog


CAdjColDlg::CAdjColDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdjColDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdjColDlg)
	m_teamcolYminVal = 0;
	m_teamcolYmaxVal = 0;
	m_teamcolVminVal = 0;
	m_teamcolVmaxVal = 0;
	m_teamcolUminVal = 0;
	m_teamcolUmaxVal = 0;
	m_robot2colYminVal = 0;
	m_robot2colYmaxVal = 0;
	m_robot2colVminVal = 0;
	m_robot2colVmaxVal = 0;
	m_robot2colUminVal = 0;
	m_robot2colUmaxVal = 0;
	m_robot1colYminVal = 0;
	m_robot1colYmaxVal = 0;
	m_robot1colVminVal = 0;
	m_robot1colVmaxVal = 0;
	m_robot1colUminVal = 0;
	m_robot1colUmaxVal = 0;
	m_ballcolYminVal = 0;
	m_ballcolYmaxVal = 0;
	m_ballcolVminVal = 0;
	m_ballcolVmaxVal = 0;
	m_ballcolUminVal = 0;
	m_ballcolUmaxVal = 0;
	m_oppocolUmaxVal = 0;
	m_oppocolUminVal = 0;
	m_oppocolVmaxVal = 0;
	m_oppocolVminVal = 0;
	m_oppocolYmaxVal = 0;
	m_oppocolYminVal = 0;
	m_Bkcolour = FALSE;
	//}}AFX_DATA_INIT
}


void CAdjColDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdjColDlg)
	DDX_Control(pDX, IDC_OPPOCOLUMAX_SCROLLBAR, m_oppocolUmax);
	DDX_Control(pDX, IDC_OPPOCOLUMIN_SCROLLBAR, m_oppocolUmin);
	DDX_Control(pDX, IDC_OPPOCOLVMAX_SCROLLBAR, m_oppocolVmax);
	DDX_Control(pDX, IDC_OPPOCOLVMIN_SCROLLBAR, m_oppocolVmin);
	DDX_Control(pDX, IDC_OPPOCOLYMAX_SCROLLBAR, m_oppocolYmax);
	DDX_Control(pDX, IDC_OPPOCOLYMIN_SCROLLBAR, m_oppocolYmin);
	DDX_Control(pDX, IDC_TEAMCOLUMAX_SCROLLBAR, m_teamcolUmax);
	DDX_Control(pDX, IDC_TEAMCOLUMIN_SCROLLBAR, m_teamcolUmin);
	DDX_Control(pDX, IDC_TEAMCOLVMAX_SCROLLBAR, m_teamcolVmax);
	DDX_Control(pDX, IDC_TEAMCOLVMIN_SCROLLBAR, m_teamcolVmin);
	DDX_Control(pDX, IDC_TEAMCOLYMAX_SCROLLBAR, m_teamcolYmax);
	DDX_Control(pDX, IDC_TEAMCOLYMIN_SCROLLBAR, m_teamcolYmin);
	DDX_Control(pDX, IDC_ROBOT2COLUMAX_SCROLLBAR, m_robot2colUmax);
	DDX_Control(pDX, IDC_ROBOT2COLUMIN_SCROLLBAR, m_robot2colUmin);
	DDX_Control(pDX, IDC_ROBOT2COLVMAX_SCROLLBAR, m_robot2colVmax);
	DDX_Control(pDX, IDC_ROBOT2COLVMIN_SCROLLBAR, m_robot2colVmin);
	DDX_Control(pDX, IDC_ROBOT2COLYMAX_SCROLLBAR, m_robot2colYmax);
	DDX_Control(pDX, IDC_ROBOT2COLYMIN_SCROLLBAR, m_robot2colYmin);
	DDX_Control(pDX, IDC_ROBOT1COLUMAX_SCROLLBAR, m_robot1colUmax);
	DDX_Control(pDX, IDC_ROBOT1COLUMIN_SCROLLBAR, m_robot1colUmin);
	DDX_Control(pDX, IDC_ROBOT1COLVMAX_SCROLLBAR, m_robot1colVmax);
	DDX_Control(pDX, IDC_ROBOT1COLVMIN_SCROLLBAR, m_robot1colVmin);
	DDX_Control(pDX, IDC_ROBOT1COLYMAX_SCROLLBAR, m_robot1colYmax);
	DDX_Control(pDX, IDC_ROBOT1COLYMIN_SCROLLBAR, m_robot1colYmin);
	DDX_Control(pDX, IDC_BALLCOLUMAX_SCROLLBAR, m_ballcolUmax);
	DDX_Control(pDX, IDC_BALLCOLUMIN_SCROLLBAR, m_ballcolUmin);
	DDX_Control(pDX, IDC_BALLCOLVMAX_SCROLLBAR, m_ballcolVmax);
	DDX_Control(pDX, IDC_BALLCOLVMIN_SCROLLBAR, m_ballcolVmin);
	DDX_Control(pDX, IDC_BALLCOLYMAX_SCROLLBAR, m_ballcolYmax);
	DDX_Control(pDX, IDC_BALLCOLYMIN_SCROLLBAR, m_ballcolYmin);
	DDX_Text(pDX, IDC_TEAMCOLYMIN_EDIT, m_teamcolYminVal);
	DDV_MinMaxUInt(pDX, m_teamcolYminVal, 0, 255);
	DDX_Text(pDX, IDC_TEAMCOLYMAX_EDIT, m_teamcolYmaxVal);
	DDV_MinMaxUInt(pDX, m_teamcolYmaxVal, 0, 255);
	DDX_Text(pDX, IDC_TEAMCOLVMIN_EDIT, m_teamcolVminVal);
	DDV_MinMaxUInt(pDX, m_teamcolVminVal, 0, 255);
	DDX_Text(pDX, IDC_TEAMCOLVMAX_EDIT, m_teamcolVmaxVal);
	DDV_MinMaxUInt(pDX, m_teamcolVmaxVal, 0, 255);
	DDX_Text(pDX, IDC_TEAMCOLUMIN_EDIT, m_teamcolUminVal);
	DDV_MinMaxUInt(pDX, m_teamcolUminVal, 0, 255);
	DDX_Text(pDX, IDC_TEAMCOLUMAX_EDIT, m_teamcolUmaxVal);
	DDV_MinMaxUInt(pDX, m_teamcolUmaxVal, 0, 255);
	DDX_Text(pDX, IDC_ROBOT2COLYMIN_EDIT, m_robot2colYminVal);
	DDV_MinMaxUInt(pDX, m_robot2colYminVal, 0, 255);
	DDX_Text(pDX, IDC_ROBOT2COLYMAX_EDIT, m_robot2colYmaxVal);
	DDV_MinMaxUInt(pDX, m_robot2colYmaxVal, 0, 255);
	DDX_Text(pDX, IDC_ROBOT2COLVMIN_EDIT, m_robot2colVminVal);
	DDV_MinMaxUInt(pDX, m_robot2colVminVal, 0, 255);
	DDX_Text(pDX, IDC_ROBOT2COLVMAX_EDIT, m_robot2colVmaxVal);
	DDV_MinMaxUInt(pDX, m_robot2colVmaxVal, 0, 255);
	DDX_Text(pDX, IDC_ROBOT2COLUMIN_EDIT, m_robot2colUminVal);
	DDV_MinMaxUInt(pDX, m_robot2colUminVal, 0, 255);
	DDX_Text(pDX, IDC_ROBOT2COLUMAX_EDIT, m_robot2colUmaxVal);
	DDV_MinMaxUInt(pDX, m_robot2colUmaxVal, 0, 255);
	DDX_Text(pDX, IDC_ROBOT1COLYMIN_EDIT, m_robot1colYminVal);
	DDV_MinMaxUInt(pDX, m_robot1colYminVal, 0, 255);
	DDX_Text(pDX, IDC_ROBOT1COLYMAX_EDIT, m_robot1colYmaxVal);
	DDV_MinMaxUInt(pDX, m_robot1colYmaxVal, 0, 255);
	DDX_Text(pDX, IDC_ROBOT1COLVMIN_EDIT, m_robot1colVminVal);
	DDV_MinMaxUInt(pDX, m_robot1colVminVal, 0, 255);
	DDX_Text(pDX, IDC_ROBOT1COLVMAX_EDIT, m_robot1colVmaxVal);
	DDV_MinMaxUInt(pDX, m_robot1colVmaxVal, 0, 255);
	DDX_Text(pDX, IDC_ROBOT1COLUMIN_EDIT, m_robot1colUminVal);
	DDV_MinMaxUInt(pDX, m_robot1colUminVal, 0, 255);
	DDX_Text(pDX, IDC_ROBOT1COLUMAX_EDIT, m_robot1colUmaxVal);
	DDV_MinMaxUInt(pDX, m_robot1colUmaxVal, 0, 255);
	DDX_Text(pDX, IDC_BALLCOLYMIN_EDIT, m_ballcolYminVal);
	DDV_MinMaxUInt(pDX, m_ballcolYminVal, 0, 255);
	DDX_Text(pDX, IDC_BALLCOLYMAX_EDIT, m_ballcolYmaxVal);
	DDV_MinMaxUInt(pDX, m_ballcolYmaxVal, 0, 255);
	DDX_Text(pDX, IDC_BALLCOLVMIN_EDIT, m_ballcolVminVal);
	DDV_MinMaxUInt(pDX, m_ballcolVminVal, 0, 255);
	DDX_Text(pDX, IDC_BALLCOLVMAX_EDIT, m_ballcolVmaxVal);
	DDV_MinMaxUInt(pDX, m_ballcolVmaxVal, 0, 255);
	DDX_Text(pDX, IDC_BALLCOLUMIN_EDIT, m_ballcolUminVal);
	DDV_MinMaxUInt(pDX, m_ballcolUminVal, 0, 255);
	DDX_Text(pDX, IDC_BALLCOLUMAX_EDIT, m_ballcolUmaxVal);
	DDV_MinMaxUInt(pDX, m_ballcolUmaxVal, 0, 255);
	DDX_Text(pDX, IDC_OPPOCOLUMAX_EDIT, m_oppocolUmaxVal);
	DDV_MinMaxUInt(pDX, m_oppocolUmaxVal, 0, 255);
	DDX_Text(pDX, IDC_OPPOCOLUMIN_EDIT, m_oppocolUminVal);
	DDV_MinMaxUInt(pDX, m_oppocolUminVal, 0, 255);
	DDX_Text(pDX, IDC_OPPOCOLVMAX_EDIT, m_oppocolVmaxVal);
	DDV_MinMaxUInt(pDX, m_oppocolVmaxVal, 0, 255);
	DDX_Text(pDX, IDC_OPPOCOLVMIN_EDIT, m_oppocolVminVal);
	DDV_MinMaxUInt(pDX, m_oppocolVminVal, 0, 255);
	DDX_Text(pDX, IDC_OPPOCOLYMAX_EDIT, m_oppocolYmaxVal);
	DDV_MinMaxUInt(pDX, m_oppocolYmaxVal, 0, 255);
	DDX_Text(pDX, IDC_OPPOCOLYMIN_EDIT, m_oppocolYminVal);
	DDV_MinMaxUInt(pDX, m_oppocolYminVal, 0, 255);
	DDX_Check(pDX, IDC_BLACKBACKGROUND_CHECK, m_Bkcolour);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdjColDlg, CDialog)
	//{{AFX_MSG_MAP(CAdjColDlg)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_BALLCOLYMIN_EDIT, OnChangeBallcolyminEdit)
	ON_EN_CHANGE(IDC_BALLCOLYMAX_EDIT, OnChangeBallcolymaxEdit)
	ON_EN_CHANGE(IDC_BALLCOLUMIN_EDIT, OnChangeBallcoluminEdit)
	ON_EN_CHANGE(IDC_BALLCOLUMAX_EDIT, OnChangeBallcolumaxEdit)
	ON_EN_CHANGE(IDC_BALLCOLVMIN_EDIT, OnChangeBallcolvminEdit)
	ON_EN_CHANGE(IDC_BALLCOLVMAX_EDIT, OnChangeBallcolvmaxEdit)
	ON_EN_CHANGE(IDC_ROBOT1COLYMIN_EDIT, OnChangeRobot1colyminEdit)
	ON_EN_CHANGE(IDC_ROBOT1COLYMAX_EDIT, OnChangeRobot1colymaxEdit)
	ON_EN_CHANGE(IDC_ROBOT1COLUMIN_EDIT, OnChangeRobot1columinEdit)
	ON_EN_CHANGE(IDC_ROBOT1COLUMAX_EDIT, OnChangeRobot1columaxEdit)
	ON_EN_CHANGE(IDC_ROBOT1COLVMIN_EDIT, OnChangeRobot1colvminEdit)
	ON_EN_CHANGE(IDC_ROBOT1COLVMAX_EDIT, OnChangeRobot1colvmaxEdit)
	ON_EN_CHANGE(IDC_ROBOT2COLYMIN_EDIT, OnChangeRobot2colyminEdit)
	ON_EN_CHANGE(IDC_ROBOT2COLYMAX_EDIT, OnChangeRobot2colymaxEdit)
	ON_EN_CHANGE(IDC_ROBOT2COLUMIN_EDIT, OnChangeRobot2columinEdit)
	ON_EN_CHANGE(IDC_ROBOT2COLUMAX_EDIT, OnChangeRobot2columaxEdit)
	ON_EN_CHANGE(IDC_ROBOT2COLVMIN_EDIT, OnChangeRobot2colvminEdit)
	ON_EN_CHANGE(IDC_ROBOT2COLVMAX_EDIT, OnChangeRobot2colvmaxEdit)
	ON_EN_CHANGE(IDC_TEAMCOLYMIN_EDIT, OnChangeTeamcolyminEdit)
	ON_EN_CHANGE(IDC_TEAMCOLYMAX_EDIT, OnChangeTeamcolymaxEdit)
	ON_EN_CHANGE(IDC_TEAMCOLUMIN_EDIT, OnChangeTeamcoluminEdit)
	ON_EN_CHANGE(IDC_TEAMCOLUMAX_EDIT, OnChangeTeamcolumaxEdit)
	ON_EN_CHANGE(IDC_TEAMCOLVMIN_EDIT, OnChangeTeamcolvminEdit)
	ON_EN_CHANGE(IDC_TEAMCOLVMAX_EDIT, OnChangeTeamcolvmaxEdit)
	ON_EN_CHANGE(IDC_OPPOCOLYMIN_EDIT, OnChangeOppocolyminEdit)
	ON_EN_CHANGE(IDC_OPPOCOLUMAX_EDIT, OnChangeOppocolumaxEdit)
	ON_EN_CHANGE(IDC_OPPOCOLUMIN_EDIT, OnChangeOppocoluminEdit)
	ON_EN_CHANGE(IDC_OPPOCOLVMAX_EDIT, OnChangeOppocolvmaxEdit)
	ON_EN_CHANGE(IDC_OPPOCOLVMIN_EDIT, OnChangeOppocolvminEdit)
	ON_EN_CHANGE(IDC_OPPOCOLYMAX_EDIT, OnChangeOppocolymaxEdit)
	ON_BN_CLICKED(IDC_BLACKBACKGROUND_CHECK, OnBlackbackgroundCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdjColDlg message handlers

BOOL CAdjColDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//-- BALL colour
	m_ballcolYmin.SetScrollRange(0, 255);
	m_ballcolYmin.SetScrollPos(globaldata.ballcolYmin);
	m_ballcolYminVal = globaldata.ballcolYmin;

	m_ballcolYmax.SetScrollRange(0, 255);
	m_ballcolYmax.SetScrollPos(globaldata.ballcolYmax);
	m_ballcolYmaxVal = globaldata.ballcolYmax;

	m_ballcolUmin.SetScrollRange(0, 255);
	m_ballcolUmin.SetScrollPos(globaldata.ballcolUmin);
	m_ballcolUminVal = globaldata.ballcolUmin;

	m_ballcolUmax.SetScrollRange(0, 255);
	m_ballcolUmax.SetScrollPos(globaldata.ballcolUmax);
	m_ballcolUmaxVal = globaldata.ballcolUmax;

	m_ballcolVmin.SetScrollRange(0, 255);
	m_ballcolVmin.SetScrollPos(globaldata.ballcolVmin);
	m_ballcolVminVal = globaldata.ballcolVmin;

	m_ballcolVmax.SetScrollRange(0, 255);
	m_ballcolVmax.SetScrollPos(globaldata.ballcolVmax);
	m_ballcolVmaxVal = globaldata.ballcolVmax;

	//-- ROBOT1 colour
	m_robot1colYmin.SetScrollRange(0, 255);
	m_robot1colYmin.SetScrollPos(globaldata.robot1colYmin);
	m_robot1colYminVal = globaldata.robot1colYmin;

	m_robot1colYmax.SetScrollRange(0, 255);
	m_robot1colYmax.SetScrollPos(globaldata.robot1colYmax);
	m_robot1colYmaxVal = globaldata.robot1colYmax;

	m_robot1colUmin.SetScrollRange(0, 255);
	m_robot1colUmin.SetScrollPos(globaldata.robot1colUmin);
	m_robot1colUminVal = globaldata.robot1colUmin;

	m_robot1colUmax.SetScrollRange(0, 255);
	m_robot1colUmax.SetScrollPos(globaldata.robot1colUmax);
	m_robot1colUmaxVal = globaldata.robot1colUmax;

	m_robot1colVmin.SetScrollRange(0, 255);
	m_robot1colVmin.SetScrollPos(globaldata.robot1colVmin);
	m_robot1colVminVal = globaldata.robot1colVmin;

	m_robot1colVmax.SetScrollRange(0, 255);
	m_robot1colVmax.SetScrollPos(globaldata.robot1colVmax);
	m_robot1colVmaxVal = globaldata.robot1colVmax;

	//-- ROBOT2 colour
	m_robot2colYmin.SetScrollRange(0, 255);
	m_robot2colYmin.SetScrollPos(globaldata.robot2colYmin);
	m_robot2colYminVal = globaldata.robot2colYmin;

	m_robot2colYmax.SetScrollRange(0, 255);
	m_robot2colYmax.SetScrollPos(globaldata.robot2colYmax);
	m_robot2colYmaxVal = globaldata.robot2colYmax;

	m_robot2colUmin.SetScrollRange(0, 255);
	m_robot2colUmin.SetScrollPos(globaldata.robot2colUmin);
	m_robot2colUminVal = globaldata.robot2colUmin;

	m_robot2colUmax.SetScrollRange(0, 255);
	m_robot2colUmax.SetScrollPos(globaldata.robot2colUmax);
	m_robot2colUmaxVal = globaldata.robot2colUmax;

	m_robot2colVmin.SetScrollRange(0, 255);
	m_robot2colVmin.SetScrollPos(globaldata.robot2colVmin);
	m_robot2colVminVal = globaldata.robot2colVmin;

	m_robot2colVmax.SetScrollRange(0, 255);
	m_robot2colVmax.SetScrollPos(globaldata.robot2colVmax);
	m_robot2colVmaxVal = globaldata.robot2colVmax;

	//-- TEAM colour
	m_teamcolYmin.SetScrollRange(0, 255);
	m_teamcolYmin.SetScrollPos(globaldata.teamcolYmin);
	m_teamcolYminVal = globaldata.teamcolYmin;

	m_teamcolYmax.SetScrollRange(0, 255);
	m_teamcolYmax.SetScrollPos(globaldata.teamcolYmax);
	m_teamcolYmaxVal = globaldata.teamcolYmax;

	m_teamcolUmin.SetScrollRange(0, 255);
	m_teamcolUmin.SetScrollPos(globaldata.teamcolUmin);
	m_teamcolUminVal = globaldata.teamcolUmin;

	m_teamcolUmax.SetScrollRange(0, 255);
	m_teamcolUmax.SetScrollPos(globaldata.teamcolUmax);
	m_teamcolUmaxVal = globaldata.teamcolUmax;

	m_teamcolVmin.SetScrollRange(0, 255);
	m_teamcolVmin.SetScrollPos(globaldata.teamcolVmin);
	m_teamcolVminVal = globaldata.teamcolVmin;

	m_teamcolVmax.SetScrollRange(0, 255);
	m_teamcolVmax.SetScrollPos(globaldata.teamcolVmax);
	m_teamcolVmaxVal = globaldata.teamcolVmax;

	//-- OPPONENT colour
	m_oppocolYmin.SetScrollRange(0, 255);
	m_oppocolYmin.SetScrollPos(globaldata.oppocolYmin);
	m_oppocolYminVal = globaldata.oppocolYmin;

	m_oppocolYmax.SetScrollRange(0, 255);
	m_oppocolYmax.SetScrollPos(globaldata.oppocolYmax);
	m_oppocolYmaxVal = globaldata.oppocolYmax;

	m_oppocolUmin.SetScrollRange(0, 255);
	m_oppocolUmin.SetScrollPos(globaldata.oppocolUmin);
	m_oppocolUminVal = globaldata.oppocolUmin;

	m_oppocolUmax.SetScrollRange(0, 255);
	m_oppocolUmax.SetScrollPos(globaldata.oppocolUmax);
	m_oppocolUmaxVal = globaldata.oppocolUmax;

	m_oppocolVmin.SetScrollRange(0, 255);
	m_oppocolVmin.SetScrollPos(globaldata.oppocolVmin);
	m_oppocolVminVal = globaldata.oppocolVmin;

	m_oppocolVmax.SetScrollRange(0, 255);
	m_oppocolVmax.SetScrollPos(globaldata.oppocolVmax);
	m_oppocolVmaxVal = globaldata.oppocolVmax;

	//-- background colour for colour testing
	m_Bkcolour = globaldata.Bkcolour;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAdjColDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
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
	//-- BALL
	case IDC_BALLCOLYMIN_SCROLLBAR:
						//-- transfer value to edit box
						m_ballcolYminVal = pScrollBar->GetScrollPos();
						//-- now transfer value to global variable
						globaldata.ballcolYmin = m_ballcolYminVal;
						break;
	case IDC_BALLCOLYMAX_SCROLLBAR:
						m_ballcolYmaxVal = pScrollBar->GetScrollPos();
						globaldata.ballcolYmax = m_ballcolYmaxVal;
						break;
	case IDC_BALLCOLUMIN_SCROLLBAR:
						m_ballcolUminVal = pScrollBar->GetScrollPos();
						globaldata.ballcolUmin = m_ballcolUminVal;
						break;
	case IDC_BALLCOLUMAX_SCROLLBAR:
						m_ballcolUmaxVal = pScrollBar->GetScrollPos();
						globaldata.ballcolUmax = m_ballcolUmaxVal;
						break;
	case IDC_BALLCOLVMIN_SCROLLBAR:
						m_ballcolVminVal = pScrollBar->GetScrollPos();
						globaldata.ballcolVmin = m_ballcolVminVal;
						break;
	case IDC_BALLCOLVMAX_SCROLLBAR:
						m_ballcolVmaxVal = pScrollBar->GetScrollPos();
						globaldata.ballcolVmax = m_ballcolVmaxVal;
						break;

	//-- ROBOT1
	case IDC_ROBOT1COLYMIN_SCROLLBAR:
						m_robot1colYminVal = pScrollBar->GetScrollPos();
						globaldata.robot1colYmin = m_robot1colYminVal;
						break;
	case IDC_ROBOT1COLYMAX_SCROLLBAR:
						m_robot1colYmaxVal = pScrollBar->GetScrollPos();
						globaldata.robot1colYmax = m_robot1colYmaxVal;
						break;
	case IDC_ROBOT1COLUMIN_SCROLLBAR:
						m_robot1colUminVal = pScrollBar->GetScrollPos();
						globaldata.robot1colUmin = m_robot1colUminVal;
						break;
	case IDC_ROBOT1COLUMAX_SCROLLBAR:
						m_robot1colUmaxVal = pScrollBar->GetScrollPos();
						globaldata.robot1colUmax = m_robot1colUmaxVal;
						break;
	case IDC_ROBOT1COLVMIN_SCROLLBAR:
						m_robot1colVminVal = pScrollBar->GetScrollPos();
						globaldata.robot1colVmin = m_robot1colVminVal;
						break;
	case IDC_ROBOT1COLVMAX_SCROLLBAR:
						m_robot1colVmaxVal = pScrollBar->GetScrollPos();
						globaldata.robot1colVmax = m_robot1colVmaxVal;
						break;

	//-- ROBOT2
	case IDC_ROBOT2COLYMIN_SCROLLBAR:
						m_robot2colYminVal = pScrollBar->GetScrollPos();
						globaldata.robot2colYmin = m_robot2colYminVal;
						break;
	case IDC_ROBOT2COLYMAX_SCROLLBAR:
						m_robot2colYmaxVal = pScrollBar->GetScrollPos();
						globaldata.robot2colYmax = m_robot2colYmaxVal;
						break;
	case IDC_ROBOT2COLUMIN_SCROLLBAR:
						m_robot2colUminVal = pScrollBar->GetScrollPos();
						globaldata.robot2colUmin = m_robot2colUminVal;
						break;
	case IDC_ROBOT2COLUMAX_SCROLLBAR:
						m_robot2colUmaxVal = pScrollBar->GetScrollPos();
						globaldata.robot2colUmax = m_robot2colUmaxVal;
						break;
	case IDC_ROBOT2COLVMIN_SCROLLBAR:
						m_robot2colVminVal = pScrollBar->GetScrollPos();
						globaldata.robot2colVmin = m_robot2colVminVal;
						break;
	case IDC_ROBOT2COLVMAX_SCROLLBAR:
						m_robot2colVmaxVal = pScrollBar->GetScrollPos();
						globaldata.robot2colVmax = m_robot2colVmaxVal;
						break;

	//-- TEAM
	case IDC_TEAMCOLYMIN_SCROLLBAR:
						m_teamcolYminVal = pScrollBar->GetScrollPos();
						globaldata.teamcolYmin = m_teamcolYminVal;
						break;
	case IDC_TEAMCOLYMAX_SCROLLBAR:
						m_teamcolYmaxVal = pScrollBar->GetScrollPos();
						globaldata.teamcolYmax = m_teamcolYmaxVal;
						break;
	case IDC_TEAMCOLUMIN_SCROLLBAR:
						m_teamcolUminVal = pScrollBar->GetScrollPos();
						globaldata.teamcolUmin = m_teamcolUminVal;
						break;
	case IDC_TEAMCOLUMAX_SCROLLBAR:
						m_teamcolUmaxVal = pScrollBar->GetScrollPos();
						globaldata.teamcolUmax = m_teamcolUmaxVal;
						break;
	case IDC_TEAMCOLVMIN_SCROLLBAR:
						m_teamcolVminVal = pScrollBar->GetScrollPos();
						globaldata.teamcolVmin = m_teamcolVminVal;
						break;
	case IDC_TEAMCOLVMAX_SCROLLBAR:
						m_teamcolVmaxVal = pScrollBar->GetScrollPos();
						globaldata.teamcolVmax = m_teamcolVmaxVal;
						break;

	//-- OPPONENT
	case IDC_OPPOCOLYMIN_SCROLLBAR:
						m_oppocolYminVal = pScrollBar->GetScrollPos();
						globaldata.oppocolYmin = m_oppocolYminVal;
						break;
	case IDC_OPPOCOLYMAX_SCROLLBAR:
						m_oppocolYmaxVal = pScrollBar->GetScrollPos();
						globaldata.oppocolYmax = m_oppocolYmaxVal;
						break;
	case IDC_OPPOCOLUMIN_SCROLLBAR:
						m_oppocolUminVal = pScrollBar->GetScrollPos();
						globaldata.oppocolUmin = m_oppocolUminVal;
						break;
	case IDC_OPPOCOLUMAX_SCROLLBAR:
						m_oppocolUmaxVal = pScrollBar->GetScrollPos();
						globaldata.oppocolUmax = m_oppocolUmaxVal;
						break;
	case IDC_OPPOCOLVMIN_SCROLLBAR:
						m_oppocolVminVal = pScrollBar->GetScrollPos();
						globaldata.oppocolVmin = m_oppocolVminVal;
						break;
	case IDC_OPPOCOLVMAX_SCROLLBAR:
						m_oppocolVmaxVal = pScrollBar->GetScrollPos();
						globaldata.oppocolVmax = m_oppocolVmaxVal;
						break;

	}	//-- end of switch statement

	UpdateData(false); //-- update the edit-box display

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CAdjColDlg::OnOK() 
{
	MessageBeep( (WORD) -1);
	CDialog::OnOK();
}

void CAdjColDlg::OnChangeBallcolyminEdit() 
{
	UpdateData(true);
	m_ballcolYmin.SetScrollPos(m_ballcolYminVal);
	globaldata.ballcolYmin = m_ballcolYminVal;
}

void CAdjColDlg::OnChangeBallcolymaxEdit() 
{
	UpdateData(true);
	m_ballcolYmax.SetScrollPos(m_ballcolYmaxVal);
	globaldata.ballcolYmax = m_ballcolYmaxVal;
}

void CAdjColDlg::OnChangeBallcoluminEdit() 
{
	UpdateData(true);
	m_ballcolUmin.SetScrollPos(m_ballcolUminVal);
	globaldata.ballcolUmin = m_ballcolUminVal;
}

void CAdjColDlg::OnChangeBallcolumaxEdit() 
{
	UpdateData(true);
	m_ballcolUmax.SetScrollPos(m_ballcolUmaxVal);
	globaldata.ballcolUmax = m_ballcolUmaxVal;
}

void CAdjColDlg::OnChangeBallcolvminEdit() 
{
	UpdateData(true);
	m_ballcolVmin.SetScrollPos(m_ballcolVminVal);
	globaldata.ballcolVmin = m_ballcolVminVal;
}

void CAdjColDlg::OnChangeBallcolvmaxEdit() 
{
	UpdateData(true);
	m_ballcolVmax.SetScrollPos(m_ballcolVmaxVal);
	globaldata.ballcolVmax = m_ballcolVmaxVal;
}

void CAdjColDlg::OnChangeRobot1colyminEdit() 
{
	UpdateData(true);
	m_robot1colYmin.SetScrollPos(m_robot1colYminVal);
	globaldata.robot1colYmin = m_robot1colYminVal;
}

void CAdjColDlg::OnChangeRobot1colymaxEdit() 
{
	UpdateData(true);
	m_robot1colYmax.SetScrollPos(m_robot1colYmaxVal);
	globaldata.robot1colYmax = m_robot1colYmaxVal;
}

void CAdjColDlg::OnChangeRobot1columinEdit() 
{
	UpdateData(true);
	m_robot1colUmin.SetScrollPos(m_robot1colUminVal);
	globaldata.robot1colUmin = m_robot1colUminVal;
}

void CAdjColDlg::OnChangeRobot1columaxEdit() 
{
	UpdateData(true);
	m_robot1colUmax.SetScrollPos(m_robot1colUmaxVal);
	globaldata.robot1colUmax = m_robot1colUmaxVal;
}

void CAdjColDlg::OnChangeRobot1colvminEdit() 
{
	UpdateData(true);
	m_robot1colVmin.SetScrollPos(m_robot1colVminVal);
	globaldata.robot1colVmin = m_robot1colVminVal;
}

void CAdjColDlg::OnChangeRobot1colvmaxEdit() 
{
	UpdateData(true);
	m_robot1colVmax.SetScrollPos(m_robot1colVmaxVal);
	globaldata.robot1colVmax = m_robot1colVmaxVal;
}

void CAdjColDlg::OnChangeRobot2colyminEdit() 
{
	UpdateData(true);
	m_robot2colYmin.SetScrollPos(m_robot2colYminVal);
	globaldata.robot2colYmin = m_robot2colYminVal;
}

void CAdjColDlg::OnChangeRobot2colymaxEdit() 
{
	UpdateData(true);
	m_robot2colYmax.SetScrollPos(m_robot2colYmaxVal);
	globaldata.robot2colYmax = m_robot2colYmaxVal;
}

void CAdjColDlg::OnChangeRobot2columinEdit() 
{
	UpdateData(true);
	m_robot2colUmin.SetScrollPos(m_robot2colUminVal);
	globaldata.robot2colUmin = m_robot2colUminVal;
}

void CAdjColDlg::OnChangeRobot2columaxEdit() 
{
	UpdateData(true);
	m_robot2colUmax.SetScrollPos(m_robot2colUmaxVal);
	globaldata.robot2colUmax = m_robot2colUmaxVal;
}

void CAdjColDlg::OnChangeRobot2colvminEdit() 
{
	UpdateData(true);
	m_robot2colVmin.SetScrollPos(m_robot2colVminVal);
	globaldata.robot2colVmin = m_robot2colVminVal;
}

void CAdjColDlg::OnChangeRobot2colvmaxEdit() 
{
	UpdateData(true);
	m_robot2colVmax.SetScrollPos(m_robot2colVmaxVal);
	globaldata.robot2colVmax = m_robot2colVmaxVal;
}

void CAdjColDlg::OnChangeTeamcolyminEdit() 
{
	UpdateData(true);
	m_teamcolYmin.SetScrollPos(m_teamcolYminVal);
	globaldata.teamcolYmin = m_teamcolYminVal;
}

void CAdjColDlg::OnChangeTeamcolymaxEdit() 
{
	UpdateData(true);
	m_teamcolYmax.SetScrollPos(m_teamcolYmaxVal);
	globaldata.teamcolYmax = m_teamcolYmaxVal;
}

void CAdjColDlg::OnChangeTeamcoluminEdit() 
{
	UpdateData(true);
	m_teamcolUmin.SetScrollPos(m_teamcolUminVal);
	globaldata.teamcolUmin = m_teamcolUminVal;
}

void CAdjColDlg::OnChangeTeamcolumaxEdit() 
{
	UpdateData(true);
	m_teamcolUmax.SetScrollPos(m_teamcolUmaxVal);
	globaldata.teamcolUmax = m_teamcolUmaxVal;
}

void CAdjColDlg::OnChangeTeamcolvminEdit() 
{
	UpdateData(true);
	m_teamcolVmin.SetScrollPos(m_teamcolVminVal);
	globaldata.teamcolVmin = m_teamcolVminVal;
}

void CAdjColDlg::OnChangeTeamcolvmaxEdit() 
{
	UpdateData(true);
	m_teamcolVmax.SetScrollPos(m_teamcolVmaxVal);
	globaldata.teamcolVmax = m_teamcolVmaxVal;
}

void CAdjColDlg::OnChangeOppocolyminEdit() 
{
	UpdateData(true);
	m_oppocolYmin.SetScrollPos(m_oppocolYminVal);
	globaldata.oppocolYmin = m_oppocolYminVal;
}

void CAdjColDlg::OnChangeOppocolymaxEdit() 
{
	UpdateData(true);
	m_oppocolYmax.SetScrollPos(m_oppocolYmaxVal);
	globaldata.oppocolYmax = m_oppocolYmaxVal;
}

void CAdjColDlg::OnChangeOppocoluminEdit() 
{
	UpdateData(true);
	m_oppocolUmin.SetScrollPos(m_oppocolUminVal);
	globaldata.oppocolUmin = m_oppocolUminVal;
}

void CAdjColDlg::OnChangeOppocolumaxEdit() 
{
	UpdateData(true);
	m_oppocolUmax.SetScrollPos(m_oppocolUmaxVal);
	globaldata.oppocolUmax = m_oppocolUmaxVal;
}

void CAdjColDlg::OnChangeOppocolvminEdit() 
{
	UpdateData(true);
	m_oppocolVmin.SetScrollPos(m_oppocolVminVal);
	globaldata.oppocolVmin = m_oppocolVminVal;
}

void CAdjColDlg::OnChangeOppocolvmaxEdit() 
{
	UpdateData(true);
	m_oppocolVmax.SetScrollPos(m_oppocolVmaxVal);
	globaldata.oppocolVmax = m_oppocolVmaxVal;
}

void CAdjColDlg::OnBlackbackgroundCheck() 
{
	UpdateData(true);
	globaldata.Bkcolour = m_Bkcolour;
}
