// AdjGameArea.cpp : implementation file
//

#include "stdafx.h"
#include "myrosot1.h"
#include "AdjGameArea.h"
#include "commondata.h"
#include "vision.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdjGameArea dialog


CAdjGameArea::CAdjGameArea(CWnd* pParent /*=NULL*/)
	: CDialog(CAdjGameArea::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdjGameArea)
	m_AdjustBoundary = -1;
	//}}AFX_DATA_INIT
}


void CAdjGameArea::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdjGameArea)
	DDX_Radio(pDX, IDC_FIELDAREA_RADIO, m_AdjustBoundary);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdjGameArea, CDialog)
	//{{AFX_MSG_MAP(CAdjGameArea)
	ON_BN_CLICKED(IDC_BOTTOM_DOWN_BUTTON, OnBottomDownButton)
	ON_BN_CLICKED(IDC_BOTTOM_UP_BUTTON, OnBottomUpButton)
	ON_BN_CLICKED(IDC_LEFT_LEFT_BUTTON, OnLeftLeftButton)
	ON_BN_CLICKED(IDC_LEFT_RIGHT_BUTTON, OnLeftRightButton)
	ON_BN_CLICKED(IDC_RIGHT_LEFT_BUTTON, OnRightLeftButton)
	ON_BN_CLICKED(IDC_RIGHT_RIGHT_BUTTON, OnRightRightButton)
	ON_BN_CLICKED(IDC_TOP_DOWN_BUTTON, OnTopDownButton)
	ON_BN_CLICKED(IDC_TOP_UP_BUTTON, OnTopUpButton)
	ON_BN_CLICKED(IDC_FIELDAREA_RADIO, OnFieldareaRadio)
	ON_BN_CLICKED(IDC_HOMEGOALAREA_RADIO, OnHomegoalareaRadio)
	ON_BN_CLICKED(IDC_OPPOGOALAREA_RADIO, OnOppogoalareaRadio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdjGameArea message handlers


BOOL CAdjGameArea::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_AdjustBoundary = globaldata.SetBoundary;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAdjGameArea::OnLeftLeftButton() 
{
	switch(globaldata.SetBoundary)
	{
	//-- case 0 -------> set field area
	case 0	:	(globaldata.lefttop.x)--;
				if (globaldata.lefttop.x < 0)
					globaldata.lefttop.x = 0;
				break;
	//-- case 1 -------> set home goal area
	case 1	:	(globaldata.homegoaltop.x)--;
				if (globaldata.homegoaltop.x < globaldata.lefttop.x)
					globaldata.lefttop.x = globaldata.lefttop.x;
				break;
	//-- case 2 -------> set opponent goal area
	case 2	:	(globaldata.oppgoaltop.x)--;
				if (globaldata.oppgoaltop.x < globaldata.lefttop.x)
					globaldata.lefttop.x = globaldata.lefttop.x;
				break;
	}
}

void CAdjGameArea::OnLeftRightButton() 
{
	switch(globaldata.SetBoundary)
	{
	//-- case 0 -------> set field area
	case 0	:	(globaldata.lefttop.x)++;
				if (globaldata.lefttop.x > globaldata.rightbottom.x)
					globaldata.lefttop.x = globaldata.rightbottom.x;
				break;
	//-- case 1 -------> set home goal area
	case 1	:	(globaldata.homegoaltop.x)++;
				if (globaldata.homegoaltop.x > globaldata.homegoalbottom.x)
					globaldata.homegoaltop.x = globaldata.homegoalbottom.x;
				break;
	//-- case 2 -------> set opponent goal area
	case 2	:	(globaldata.oppgoaltop.x)++;
				if (globaldata.oppgoaltop.x > globaldata.oppgoalbottom.x)
					globaldata.oppgoaltop.x = globaldata.oppgoalbottom.x;
				break;
	}
}

void CAdjGameArea::OnRightLeftButton() 
{
	switch(globaldata.SetBoundary)
	{
	//-- case 0 -------> set field area
	case 0	:	(globaldata.rightbottom.x)--;
				if (globaldata.rightbottom.x < globaldata.lefttop.x)
					globaldata.rightbottom.x = globaldata.lefttop.x;
				break;
	//-- case 1 -------> set home goal area
	case 1	:	(globaldata.homegoalbottom.x)--;
				if (globaldata.homegoalbottom.x < globaldata.homegoaltop.x)
					globaldata.homegoalbottom.x = globaldata.homegoaltop.x;
				break;
	//-- case 2 -------> set opponent goal area
	case 2	:	(globaldata.oppgoalbottom.x)--;
				if (globaldata.oppgoalbottom.x < globaldata.oppgoaltop.x)
					globaldata.oppgoalbottom.x = globaldata.oppgoaltop.x;
				break;
	}
}

void CAdjGameArea::OnRightRightButton() 
{
	switch(globaldata.SetBoundary)
	{
	//-- case 0 -------> set field area
	case 0	:	(globaldata.rightbottom.x)++;
				if (globaldata.rightbottom.x > MaxX)
					globaldata.rightbottom.x = MaxX;
				break;
	//-- case 1 -------> set home goal area
	case 1	:	(globaldata.homegoalbottom.x)++;
				if (globaldata.homegoalbottom.x > globaldata.rightbottom.x)
					globaldata.homegoalbottom.x = globaldata.rightbottom.x;
				break;
	//-- case 2 -------> set opponent goal area
	case 2	:	(globaldata.oppgoalbottom.x)++;
				if (globaldata.oppgoalbottom.x > globaldata.rightbottom.x)
					globaldata.oppgoalbottom.x = globaldata.rightbottom.x;
				break;
	}

}

void CAdjGameArea::OnTopDownButton() 
{
	switch(globaldata.SetBoundary)
	{
	//-- case 0 -------> set field area
	case 0	:	(globaldata.lefttop.y)++;
				if (globaldata.lefttop.y < 0)
					globaldata.lefttop.y = 0;
				break;
	//-- case 1 -------> set home goal area
	case 1	:	(globaldata.homegoaltop.y)++;
				if (globaldata.homegoaltop.y < globaldata.lefttop.y)
					globaldata.homegoaltop.y = globaldata.lefttop.y;
				break;
	//-- case 2 -------> set opponent goal area
	case 2	:	(globaldata.oppgoaltop.y)++;
				if (globaldata.oppgoaltop.y < globaldata.lefttop.y)
					globaldata.oppgoaltop.y = globaldata.lefttop.y;
				break;
	}

}

void CAdjGameArea::OnTopUpButton() 
{
	switch(globaldata.SetBoundary)
	{
	//-- case 0 -------> set field area
	case 0	:	(globaldata.lefttop.y)--;
				if (globaldata.lefttop.y > globaldata.rightbottom.y)
					globaldata.lefttop.y = globaldata.rightbottom.y;
				break;
	//-- case 1 -------> set home goal area
	case 1	:	(globaldata.homegoaltop.y)--;
				if (globaldata.homegoaltop.y > globaldata.homegoalbottom.y)
					globaldata.homegoaltop.y = globaldata.homegoalbottom.y;
				break;
	//-- case 2 -------> set opponent goal area
	case 2	:	(globaldata.oppgoaltop.y)--;
				if (globaldata.oppgoaltop.y > globaldata.oppgoalbottom.y)
					globaldata.oppgoaltop.y = globaldata.oppgoalbottom.y;
				break;
	}
}

void CAdjGameArea::OnBottomDownButton() 
{
	switch(globaldata.SetBoundary)
	{
	//-- case 0 -------> set field area
	case 0	:	(globaldata.rightbottom.y)++;
				if (globaldata.rightbottom.y < globaldata.lefttop.y)
					globaldata.rightbottom.y = globaldata.lefttop.y;
				break;
	//-- case 1 -------> set home goal area
	case 1	:	(globaldata.homegoalbottom.y)++;
				if (globaldata.homegoalbottom.y < globaldata.homegoaltop.y)
					globaldata.homegoalbottom.y = globaldata.homegoaltop.y;
				break;
	//-- case 2 -------> set opponent goal area
	case 2	:	(globaldata.oppgoalbottom.y)++;
				if (globaldata.oppgoalbottom.y < globaldata.oppgoaltop.y)
					globaldata.oppgoalbottom.y = globaldata.oppgoaltop.y;
				break;
	}
}

void CAdjGameArea::OnBottomUpButton() 
{
	switch(globaldata.SetBoundary)
	{
	//-- case 0 -------> set field area
	case 0	:	(globaldata.rightbottom.y)--;
				if (globaldata.rightbottom.y > MaxY)
					globaldata.rightbottom.y = MaxY;
				break;
	//-- case 1 -------> set home goal area
	case 1	:	(globaldata.homegoalbottom.y)--;
				if (globaldata.homegoalbottom.y > globaldata.rightbottom.y)
					globaldata.homegoalbottom.y = globaldata.rightbottom.y;
				break;
	//-- case 2 -------> set opponent goal area
	case 2	:	(globaldata.oppgoalbottom.y)--;
				if (globaldata.oppgoalbottom.y > globaldata.rightbottom.y)
					globaldata.oppgoalbottom.y = globaldata.rightbottom.y;
				break;
	}
}

void CAdjGameArea::OnFieldareaRadio() 
{
	UpdateData(TRUE);
	globaldata.SetBoundary = 0;	//-- set the field area	
}

void CAdjGameArea::OnHomegoalareaRadio() 
{
	UpdateData(TRUE);
	globaldata.SetBoundary = 1;	//-- set home goal area	
}

void CAdjGameArea::OnOppogoalareaRadio() 
{
	UpdateData(TRUE);
	globaldata.SetBoundary = 2;	//-- set Opponent goal area
}
