#if !defined(AFX_RFCOMMDLG_H__E6180741_2A24_11D3_ADD5_444553540000__INCLUDED_)
#define AFX_RFCOMMDLG_H__E6180741_2A24_11D3_ADD5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RFCommDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRFCommDlg dialog

class CRFCommDlg : public CDialog
{
// Construction
public:
	CRFCommDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRFCommDlg)
	enum { IDD = IDD_RFCOMM_DIALOG };
	CScrollBar	m_Speed;
	CScrollBar	m_Robot2L;
	CScrollBar	m_Robot2R;
	CScrollBar	m_Robot1L;
	CScrollBar	m_Robot1R;
	CScrollBar	m_GoalieL;
	CScrollBar	m_GoalieR;
	int		m_GoalieLVal;
	int		m_Robot1RVal;
	int		m_Robot1LVal;
	int		m_Robot2RVal;
	int		m_Robot2LVal;
	int		m_GoalieRVal;
	int		m_SpeedVal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRFCommDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRFCommDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnChangeGoalielEdit();
	afx_msg void OnChangeGoalierEdit();
	afx_msg void OnChangeRobot1lEdit();
	afx_msg void OnChangeRobot1rEdit();
	afx_msg void OnChangeRobot2lEdit();
	afx_msg void OnChangeRobot2rEdit();
	afx_msg void OnSendButton();
	afx_msg void OnStopButton();
	afx_msg void OnForwardButton();
	afx_msg void OnReverseButton();
	afx_msg void OnTurnleftButton();
	afx_msg void OnTurnrightButton();
	virtual void OnOK();
	afx_msg void OnChangeSpeedEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RFCOMMDLG_H__E6180741_2A24_11D3_ADD5_444553540000__INCLUDED_)
