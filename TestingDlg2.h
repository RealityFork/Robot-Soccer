#if !defined(AFX_TESTINGDLG_H__CA534121_C418_11D4_8CBA_005004A4F6ED__INCLUDED_)
#define AFX_TESTINGDLG_H__CA534121_C418_11D4_8CBA_005004A4F6ED__INCLUDED_

#include "Fbus.h"	// Added by ClassView
#include "commondata.h"
#include "stdafx.h"
#include "myrosot1.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestingDlg dialog

class CTestingDlg : public CDialog
{
// Construction
public:
	BOOL OnInitDialog();
	CTestingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestingDlg)
	enum { IDD = IDD_TESTING_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestingDlg)
	afx_msg void OnRadioCase0();
	afx_msg void OnRadioCase1();
	afx_msg void OnRadioCase2();
	afx_msg void OnRadioCase3();
	afx_msg void OnRadioCase4();
	afx_msg void OnRadioCase5();
	afx_msg void OnRadioCase6();
	afx_msg void OnRadioCase7();
	afx_msg void OnRadioCase8();
	afx_msg void OnRadioCase9();
	afx_msg void OnRadioCase10();
	afx_msg void OnRadioCase11();
	afx_msg void OnRadioCase12();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTINGDLG_H__CA534121_C418_11D4_8CBA_005004A4F6ED__INCLUDED_)
