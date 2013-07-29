// TestingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "myrosot1.h"
#include "TestingDlg2.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestingDlg dialog


CTestingDlg::CTestingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestingDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CTestingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestingDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestingDlg, CDialog)
	//{{AFX_MSG_MAP(CTestingDlg)
	ON_BN_CLICKED(IDC_RADIO_CASE0, OnRadioCase0)
	ON_BN_CLICKED(IDC_RADIO_CASE1, OnRadioCase1)
	ON_BN_CLICKED(IDC_RADIO_CASE2, OnRadioCase2)
	ON_BN_CLICKED(IDC_RADIO_CASE3, OnRadioCase3)
	ON_BN_CLICKED(IDC_RADIO_CASE4, OnRadioCase4)
	ON_BN_CLICKED(IDC_RADIO_CASE5, OnRadioCase5)
	ON_BN_CLICKED(IDC_RADIO_CASE6, OnRadioCase6)
	ON_BN_CLICKED(IDC_RADIO_CASE7, OnRadioCase7)
	ON_BN_CLICKED(IDC_RADIO_CASE8, OnRadioCase8)
	ON_BN_CLICKED(IDC_RADIO_CASE9, OnRadioCase9)
	ON_BN_CLICKED(IDC_RADIO_CASE10, OnRadioCase10)
	ON_BN_CLICKED(IDC_RADIO_CASE11, OnRadioCase11)
	ON_BN_CLICKED(IDC_RADIO_CASE12, OnRadioCase12)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestingDlg message handlers

void CTestingDlg::OnRadioCase0() 
{
	gChoice=0;	//-- Striker chase the ball
	//-- remove other robots from the field
	gRemoved.Goalie = TRUE;
	gRemoved.Robot1 = TRUE;
	gRemoved.Robot2 = FALSE;
	gNumRobots = 1;
}

void CTestingDlg::OnRadioCase1() 
{
	gChoice = 1;	//-- Position Goalie at 90 degrees - Testing Angle() function
	gRemoved.Goalie = FALSE;
	gRemoved.Robot1 = TRUE;
	gRemoved.Robot2 = TRUE;
	gNumRobots = 1;
}

void CTestingDlg::OnRadioCase2() 
{
	gChoice = 2;	//-- TO POSITION STRIKER AT THE POINT CLICKED IN THE CAPTURE WINDOW
					//-- Testing Position() function
	gRemoved.Goalie = TRUE;
	gRemoved.Robot1 = TRUE;
	gRemoved.Robot2 = FALSE;
	gNumRobots = 1;
}

void CTestingDlg::OnRadioCase3() 
{
	gChoice = 3;
}

void CTestingDlg::OnRadioCase4() 
{
	gChoice = 4;
}

void CTestingDlg::OnRadioCase5() 
{
	gChoice = 5;
}

void CTestingDlg::OnRadioCase6() 
{
	gChoice = 6;
}

void CTestingDlg::OnRadioCase7() 
{
	gChoice = 7;	//-- State Based GOALIE
	//-- remove other robots from the field
	gRemoved.Goalie = FALSE;
	gRemoved.Robot1 = TRUE;
	gRemoved.Robot2 = TRUE;
	gNumRobots = 1;
}

void CTestingDlg::OnRadioCase8() 
{
	gChoice = 8;
}

void CTestingDlg::OnRadioCase9() 
{
	gChoice = 9;
}

void CTestingDlg::OnRadioCase10() 
{
	gChoice = 10;	//-- State Based kick start & NORMAL Game
	gRemoved.Goalie = FALSE;
	gRemoved.Robot1 = FALSE;
	gRemoved.Robot2 = FALSE;
	gNumRobots = 3;
}

void CTestingDlg::OnRadioCase11() 
{
	gChoice = 11;
}

void CTestingDlg::OnRadioCase12() 
{
	gChoice = 12;
}

BOOL CTestingDlg::OnInitDialog()
{
/*--------------
	gChoice = 0;	//-- Striker chase the ball
	gChoice = 1;	//-- Position robot at 90 degrees - Testing Angle() function
	gChoice = 2;	//-- TO POSITION STRIKER AT THE POINT CLICKED IN THE CAPTURE WINDOW
					//-- Testing Position() function
	gChoice = 3;
	gChoice = 4;
	gChoice = 5;
	gChoice = 6;
	gChoice = 7;	//-- State Based GOALIE
	gChoice = 8;
	gChoice = 9;
	gChoice = 10;	//-- State Based kick start & NORMAL Game
	gChoice = 11;
	gChoice = 12;
*/

	CDialog::OnInitDialog();
	switch (gChoice)
	{
	case 0:
		CheckDlgButton(IDC_RADIO_CASE0,1);
		break;
	case 1:
		CheckDlgButton(IDC_RADIO_CASE1,1);
		break;
	case 2:
		CheckDlgButton(IDC_RADIO_CASE2,1);
		break;
	case 3:
		CheckDlgButton(IDC_RADIO_CASE3,1);
		break;
	case 4:
		CheckDlgButton(IDC_RADIO_CASE4,1);
		break;
	case 5:
		CheckDlgButton(IDC_RADIO_CASE5,1);
		break;
	case 6:
		CheckDlgButton(IDC_RADIO_CASE6,1);
		break;
	case 7:
		CheckDlgButton(IDC_RADIO_CASE7,1);
		break;
	case 8:
		CheckDlgButton(IDC_RADIO_CASE8,1);
		break;
	case 9:
		CheckDlgButton(IDC_RADIO_CASE9,1);
		break;
	case 10:
		CheckDlgButton(IDC_RADIO_CASE10,1);
		break;
	case 11:
		CheckDlgButton(IDC_RADIO_CASE11,1);
		break;
	case 12:
		CheckDlgButton(IDC_RADIO_CASE12,1);
		break;
	default:
		break;
	}
	return TRUE;
}

void CTestingDlg::OnOK() 
{
	MessageBeep( (WORD) -1 );
	CDialog::OnOK();
}
