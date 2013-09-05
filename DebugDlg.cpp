// DebugDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DebugDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DebugDlg dialog


DebugDlg::DebugDlg(CWnd* pParent /*=NULL*/)
	: CDialog(DebugDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DebugDlg)
	m_checkDebug = FALSE;
	m_checkError = FALSE;
	m_checkInfo = FALSE;
	m_checkWarning = FALSE;
	//}}AFX_DATA_INIT
}


void DebugDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DebugDlg)
	DDX_Control(pDX, debugEdit, m_debugEdit);
	DDX_Check(pDX, checkDebug, m_checkDebug);
	DDX_Check(pDX, checkError, m_checkError);
	DDX_Check(pDX, checkInfo, m_checkInfo);
	DDX_Check(pDX, checkWarning, m_checkWarning);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DebugDlg, CDialog)
	//{{AFX_MSG_MAP(DebugDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DebugDlg message handlers
