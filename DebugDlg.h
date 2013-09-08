#if !defined(AFX_DEBUGDLG_H__542E226B_D79C_42FC_BDE5_1774EFB5C543__INCLUDED_)
#define AFX_DEBUGDLG_H__542E226B_D79C_42FC_BDE5_1774EFB5C543__INCLUDED_
#include "stdafx.h"

#include "myrosot1.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DebugDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DebugDlg dialog

class DebugDlg : public CDialog
{
// Construction
public:
	DebugDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DebugDlg)
	enum { IDD = IDD_DEBUGDLG };
	CEdit	m_debugEdit;
	BOOL	m_checkDebug;
	BOOL	m_checkError;
	BOOL	m_checkInfo;
	BOOL	m_checkWarning;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DebugDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DebugDlg)
	afx_msg void OncheckDebug();
	afx_msg void OncheckInfo();
	afx_msg void OncheckWarning();
	afx_msg void OncheckError();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEBUGDLG_H__542E226B_D79C_42FC_BDE5_1774EFB5C543__INCLUDED_)
