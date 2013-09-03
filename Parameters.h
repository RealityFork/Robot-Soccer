#if !defined(AFX_PARAMETERS_H__08281821_3A01_11D3_ADD5_444553540000__INCLUDED_)
#define AFX_PARAMETERS_H__08281821_3A01_11D3_ADD5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Parameters.h : header file
//

#include "stdafx.h"
#include "myrosot1.h"
#include "commondata.h"
#include "RFComm.h"

/////////////////////////////////////////////////////////////////////////////
// CParameters dialog

class CParameters : public CDialog
{
// Construction
public:
	CParameters(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CParameters)
	enum { IDD = IDD_PARAMETERS_DIALOG };
	CScrollBar	m_MinPatchSizeOppo;
	CScrollBar	m_MinPatchSizeBall;
	CScrollBar	m_MinPatchSizeTeam;
	CScrollBar	m_MinPatchSizeCol2;
	CScrollBar	m_MinPatchSizeCol1;
	CScrollBar	m_NumOppoRobots;
	BOOL	m_GoalieRemoved;
	BOOL	m_Robot1Removed;
	BOOL	m_Robot2Removed;
	int		m_ComPort;
	float	m_CameraHeight;
	BOOL	m_TrackOpponent;
	int		m_NumOppoRobotsVal;
	int		m_MinPatchSizeCol1Val;
	int		m_MinPatchSizeCol2Val;
	int		m_MinPatchSizeTeamVal;
	int		m_MinPatchSizeBallVal;
	int		m_MinPatchSizeOppoVal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParameters)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CParameters)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnGoalieremovedCheck();
	afx_msg void OnRobot1removedCheck();
	afx_msg void OnRobot2removedCheck();
	afx_msg void OnCom1Radio();
	afx_msg void OnCom2Radio();
	afx_msg void OnChangeMinpatchsizeEdit();
	afx_msg void OnChangeCameraheightEdit();
	afx_msg void OnTrackoppoCheck();
	afx_msg void OnChangeNumopporobotsEdit();
	afx_msg void OnChangeMinpatchsizecol1Edit();
	afx_msg void OnChangeMinpatchsizecol2Edit();
	afx_msg void OnChangeMinpatchsizeteamEdit();
	afx_msg void OnChangeMinpatchsizeballEdit();
	afx_msg void OnChangeMinpatchsizeoppoEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMETERS_H__08281821_3A01_11D3_ADD5_444553540000__INCLUDED_)
