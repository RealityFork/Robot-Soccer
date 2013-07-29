#if !defined(AFX_TUNINGDLG_H__5E630640_20E3_11D4_ACDA_0000C0C350EB__INCLUDED_)
#define AFX_TUNINGDLG_H__5E630640_20E3_11D4_ACDA_0000C0C350EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TuningDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTuningDlg dialog

class CTuningDlg : public CDialog
{
// Construction
public:
	CTuningDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTuningDlg)
	enum { IDD = IDD_TUNING_DIALOG };
	CScrollBar	m_FreeballSpeed;
	CScrollBar	m_FreeballDistance;
	CScrollBar	m_FreekickSpeed;
	CScrollBar	m_FreekickDistance;
	CScrollBar	m_PenaltySpeed;
	CScrollBar	m_PenaltyDistance;
	CScrollBar	m_GoalkickSpeed;
	CScrollBar	m_GoalkickDistance;
	CScrollBar	m_KickstartDistance;
	CScrollBar	m_KickstartSpeed;
	CScrollBar	m_BallClearTime;
	CScrollBar	m_GXcompensation;
	float	m_GXcompensationVal;
	int		m_GBehaviour;
	BOOL	m_ParallaxCorrectionEnabled;
	BOOL	m_StopRobotsWhenBallLost;
	float	m_BallClearTimeVal;
	int		m_KickstartSpeedVal;
	float	m_KickstartDistanceVal;
	float	m_GoalkickDistanceVal;
	int		m_GoalkickSpeedVal;
	float	m_PenaltyDistanceVal;
	int		m_PenaltySpeedVal;
	float	m_FreekickDistanceVal;
	int		m_FreekickSpeedVal;
	float	m_FreeballDistanceVal;
	int		m_FreeballSpeedVal;
	BOOL	m_GoalieFollowClick;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTuningDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTuningDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnConservativeRadio();
	afx_msg void OnNormalRadio();
	afx_msg void OnAggressiveRadio();
	afx_msg void OnParallaxcorrectionCheck();
	afx_msg void OnStoprobotswhenballlostCheck();
	afx_msg void OnChangeBallcleartimeEdit();
	afx_msg void OnDefaultButton();
	afx_msg void OnFollowclickCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TUNINGDLG_H__5E630640_20E3_11D4_ACDA_0000C0C350EB__INCLUDED_)
