#if !defined(AFX_ADJGAMEAREA_H__D02C4561_6B59_11D3_8E3E_D081DE4DDE35__INCLUDED_)
#define AFX_ADJGAMEAREA_H__D02C4561_6B59_11D3_8E3E_D081DE4DDE35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdjGameArea.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAdjGameArea dialog

class CAdjGameArea : public CDialog
{
// Construction
public:
	CAdjGameArea(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAdjGameArea)
	enum { IDD = IDD_ADJUSTGAMEAREA_DIALOG };
	int		m_AdjustBoundary;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdjGameArea)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAdjGameArea)
	afx_msg void OnBottomDownButton();
	afx_msg void OnBottomUpButton();
	afx_msg void OnLeftLeftButton();
	afx_msg void OnLeftRightButton();
	afx_msg void OnRightLeftButton();
	afx_msg void OnRightRightButton();
	afx_msg void OnTopDownButton();
	afx_msg void OnTopUpButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnFieldareaRadio();
	afx_msg void OnHomegoalareaRadio();
	afx_msg void OnOppogoalareaRadio();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADJGAMEAREA_H__D02C4561_6B59_11D3_8E3E_D081DE4DDE35__INCLUDED_)
