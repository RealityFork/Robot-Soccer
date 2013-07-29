#if !defined(AFX_ADJCOLDLG_H__C09B7AE2_2305_11D3_ADD5_003506C10700__INCLUDED_)
#define AFX_ADJCOLDLG_H__C09B7AE2_2305_11D3_ADD5_003506C10700__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AdjColDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAdjColDlg dialog

class CAdjColDlg : public CDialog
{
// Construction
public:
	CAdjColDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAdjColDlg)
	enum { IDD = IDD_ADJUSTCOLOURS_DIALOG };
	CScrollBar	m_oppocolUmax;
	CScrollBar	m_oppocolUmin;
	CScrollBar	m_oppocolVmax;
	CScrollBar	m_oppocolVmin;
	CScrollBar	m_oppocolYmax;
	CScrollBar	m_oppocolYmin;
	CScrollBar	m_teamcolUmax;
	CScrollBar	m_teamcolUmin;
	CScrollBar	m_teamcolVmax;
	CScrollBar	m_teamcolVmin;
	CScrollBar	m_teamcolYmax;
	CScrollBar	m_teamcolYmin;
	CScrollBar	m_robot2colUmax;
	CScrollBar	m_robot2colUmin;
	CScrollBar	m_robot2colVmax;
	CScrollBar	m_robot2colVmin;
	CScrollBar	m_robot2colYmax;
	CScrollBar	m_robot2colYmin;
	CScrollBar	m_robot1colUmax;
	CScrollBar	m_robot1colUmin;
	CScrollBar	m_robot1colVmax;
	CScrollBar	m_robot1colVmin;
	CScrollBar	m_robot1colYmax;
	CScrollBar	m_robot1colYmin;
	CScrollBar	m_ballcolUmax;
	CScrollBar	m_ballcolUmin;
	CScrollBar	m_ballcolVmax;
	CScrollBar	m_ballcolVmin;
	CScrollBar	m_ballcolYmax;
	CScrollBar	m_ballcolYmin;
	UINT	m_teamcolYminVal;
	UINT	m_teamcolYmaxVal;
	UINT	m_teamcolVminVal;
	UINT	m_teamcolVmaxVal;
	UINT	m_teamcolUminVal;
	UINT	m_teamcolUmaxVal;
	UINT	m_robot2colYminVal;
	UINT	m_robot2colYmaxVal;
	UINT	m_robot2colVminVal;
	UINT	m_robot2colVmaxVal;
	UINT	m_robot2colUminVal;
	UINT	m_robot2colUmaxVal;
	UINT	m_robot1colYminVal;
	UINT	m_robot1colYmaxVal;
	UINT	m_robot1colVminVal;
	UINT	m_robot1colVmaxVal;
	UINT	m_robot1colUminVal;
	UINT	m_robot1colUmaxVal;
	UINT	m_ballcolYminVal;
	UINT	m_ballcolYmaxVal;
	UINT	m_ballcolVminVal;
	UINT	m_ballcolVmaxVal;
	UINT	m_ballcolUminVal;
	UINT	m_ballcolUmaxVal;
	UINT	m_oppocolUmaxVal;
	UINT	m_oppocolUminVal;
	UINT	m_oppocolVmaxVal;
	UINT	m_oppocolVminVal;
	UINT	m_oppocolYmaxVal;
	UINT	m_oppocolYminVal;
	BOOL	m_Bkcolour;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdjColDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAdjColDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnOK();
	afx_msg void OnChangeBallcolyminEdit();
	afx_msg void OnChangeBallcolymaxEdit();
	afx_msg void OnChangeBallcoluminEdit();
	afx_msg void OnChangeBallcolumaxEdit();
	afx_msg void OnChangeBallcolvminEdit();
	afx_msg void OnChangeBallcolvmaxEdit();
	afx_msg void OnChangeRobot1colyminEdit();
	afx_msg void OnChangeRobot1colymaxEdit();
	afx_msg void OnChangeRobot1columinEdit();
	afx_msg void OnChangeRobot1columaxEdit();
	afx_msg void OnChangeRobot1colvminEdit();
	afx_msg void OnChangeRobot1colvmaxEdit();
	afx_msg void OnChangeRobot2colyminEdit();
	afx_msg void OnChangeRobot2colymaxEdit();
	afx_msg void OnChangeRobot2columinEdit();
	afx_msg void OnChangeRobot2columaxEdit();
	afx_msg void OnChangeRobot2colvminEdit();
	afx_msg void OnChangeRobot2colvmaxEdit();
	afx_msg void OnChangeTeamcolyminEdit();
	afx_msg void OnChangeTeamcolymaxEdit();
	afx_msg void OnChangeTeamcoluminEdit();
	afx_msg void OnChangeTeamcolumaxEdit();
	afx_msg void OnChangeTeamcolvminEdit();
	afx_msg void OnChangeTeamcolvmaxEdit();
	afx_msg void OnChangeOppocolyminEdit();
	afx_msg void OnChangeOppocolumaxEdit();
	afx_msg void OnChangeOppocoluminEdit();
	afx_msg void OnChangeOppocolvmaxEdit();
	afx_msg void OnChangeOppocolvminEdit();
	afx_msg void OnChangeOppocolymaxEdit();
	afx_msg void OnBlackbackgroundCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADJCOLDLG_H__C09B7AE2_2305_11D3_ADD5_003506C10700__INCLUDED_)
