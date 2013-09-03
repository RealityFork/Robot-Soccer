#if !defined(AFX_GRABBERSETTINGSDLG_H__27EED9E1_0A3B_11D4_B2AA_F3A4D0642B40__INCLUDED_)
#define AFX_GRABBERSETTINGSDLG_H__27EED9E1_0A3B_11D4_B2AA_F3A4D0642B40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrabberSettingsDlg.h : header file
//

#include "stdafx.h"
#include "myrosot1.h"
#include "vision.h"
#include "fbus.h"

/////////////////////////////////////////////////////////////////////////////
// CGrabberSettingsDlg dialog

class CGrabberSettingsDlg : public CDialog
{
// Construction
public:
	CGrabberSettingsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGrabberSettingsDlg)
	enum { IDD = IDD_GRABBERSETTINGS_DIALOG };
	CScrollBar	m_Sharpness;
	CScrollBar	m_Contrast;
	CScrollBar	m_Brightness;
	CScrollBar	m_Saturation;
	CScrollBar	m_Hue;
	UINT	m_HueVal;
	UINT	m_SaturationVal;
	UINT	m_BrightnessVal;
	UINT	m_ContrastVal;
	UINT	m_SharpnessVal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrabberSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGrabberSettingsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnCancel();
	afx_msg void OnDefaultButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRABBERSETTINGSDLG_H__27EED9E1_0A3B_11D4_B2AA_F3A4D0642B40__INCLUDED_)
