// GrabberSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrabberSettingsDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrabberSettingsDlg dialog

//-- backup variables
grabber_settings FBusCopy;
//-- backup variables


CGrabberSettingsDlg::CGrabberSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGrabberSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGrabberSettingsDlg)
	m_HueVal = 0;
	m_SaturationVal = 0;
	m_BrightnessVal = 0;
	m_ContrastVal = 0;
	m_SharpnessVal = 0;
	//}}AFX_DATA_INIT
}


void CGrabberSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrabberSettingsDlg)
	DDX_Control(pDX, IDC_SHARPNESS_SCROLLBAR, m_Sharpness);
	DDX_Control(pDX, IDC_CONTRAST_SCROLLBAR, m_Contrast);
	DDX_Control(pDX, IDC_BRIGHTNESS_SCROLLBAR, m_Brightness);
	DDX_Control(pDX, IDC_SATURATION_SCROLLBAR, m_Saturation);
	DDX_Control(pDX, IDC_HUE_SCROLLBAR, m_Hue);
	DDX_Text(pDX, IDC_HUE_EDIT, m_HueVal);
	DDV_MinMaxUInt(pDX, m_HueVal, 0, 63);
	DDX_Text(pDX, IDC_SATURATION_EDIT, m_SaturationVal);
	DDV_MinMaxUInt(pDX, m_SaturationVal, 0, 63);
	DDX_Text(pDX, IDC_BRIGHTNESS_EDIT, m_BrightnessVal);
	DDV_MinMaxUInt(pDX, m_BrightnessVal, 0, 63);
	DDX_Text(pDX, IDC_CONTRAST_EDIT, m_ContrastVal);
	DDV_MinMaxUInt(pDX, m_ContrastVal, 0, 63);
	DDX_Text(pDX, IDC_SHARPNESS_EDIT, m_SharpnessVal);
	DDV_MinMaxUInt(pDX, m_SharpnessVal, 0, 7);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrabberSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CGrabberSettingsDlg)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_DEFAULT_BUTTON, OnDefaultButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrabberSettingsDlg message handlers

BOOL CGrabberSettingsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//--  backup the variables - required when cancel chosen
	FBusCopy = FBus;
	//-- backup over ------------------------------

	//-- set the values in the edit box -----------
	m_BrightnessVal = FBus.brightness;
	m_ContrastVal = FBus.contrast;
	m_SaturationVal = FBus.saturation;
	m_HueVal = FBus.hue;
	m_SharpnessVal = FBus.sharpness;

	//-- set the scroll bar range & positions -------------
	m_Brightness.SetScrollRange(0, 63);
	m_Brightness.SetScrollPos(FBus.brightness);

	m_Contrast.SetScrollRange(0, 63);
	m_Contrast.SetScrollPos(FBus.contrast);

	m_Saturation.SetScrollRange(0, 63);
	m_Saturation.SetScrollPos(FBus.saturation);

	m_Hue.SetScrollRange(0, 63);
	m_Hue.SetScrollPos(FBus.hue);

	m_Sharpness.SetScrollRange(0, 7);
	m_Sharpness.SetScrollPos(FBus.sharpness);

	UpdateData(FALSE);//-- transfer control variables to screen

	//-- put the Grabber in Live mode
	if (!FB_GetLiveStatus()) //-- Video is NOT live
	{
		FB_VideoLive(TRUE, ALIGN_ODD);	//-- enable live video
		Delay(30); //-- put in a delay of 30 msec
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGrabberSettingsDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int id = pScrollBar->GetDlgCtrlID();
	int JumpBy = 5;
	if (id == IDC_SHARPNESS_SCROLLBAR) JumpBy = 2;

	int nCurPos = pScrollBar->GetScrollPos();	//-- current position

	switch (nSBCode)
	{
	case SB_LINELEFT:
			pScrollBar->SetScrollPos(nCurPos-1);
			break;
	case SB_LINERIGHT:
			pScrollBar->SetScrollPos(nCurPos+1);
			break;
	case SB_THUMBPOSITION:
			pScrollBar->SetScrollPos(nPos);
			break;
	case SB_PAGEUP:
			pScrollBar->SetScrollPos(nCurPos-JumpBy);
			break;
	case SB_PAGEDOWN:
			pScrollBar->SetScrollPos(nCurPos+JumpBy);
			break;
	}

	switch(id)
	{
	//-- brightness
	case IDC_BRIGHTNESS_SCROLLBAR:
						//-- transfer value to edit box
						m_BrightnessVal = pScrollBar->GetScrollPos();
						//-- now transfer value to global variable
						FBus.brightness = m_BrightnessVal;
						FB_SetVideoAdjustments(ADJUST_BRIGHTNESS, FBus.brightness);
						break;

	//-- contrast
	case IDC_CONTRAST_SCROLLBAR:
						//-- transfer value to edit box
						m_ContrastVal = pScrollBar->GetScrollPos();
						//-- now transfer value to global variable
						FBus.contrast = m_ContrastVal;
						FB_SetVideoAdjustments(ADJUST_CONTRAST, FBus.contrast);
						break;
	//-- saturation
	case IDC_SATURATION_SCROLLBAR:
						//-- transfer value to edit box
						m_SaturationVal = pScrollBar->GetScrollPos();
						//-- now transfer value to global variable
						FBus.saturation = m_SaturationVal;
						FB_SetVideoAdjustments(ADJUST_SATURATION, FBus.saturation);
						break;
	//-- Hue
	case IDC_HUE_SCROLLBAR:
						//-- transfer value to edit box
						m_HueVal = pScrollBar->GetScrollPos();
						//-- now transfer value to global variable
						FBus.hue = m_HueVal;
						FB_SetVideoAdjustments(ADJUST_HUE, FBus.hue);
						break;
	//-- Sharpness
	case IDC_SHARPNESS_SCROLLBAR:
						//-- transfer value to edit box
						m_SharpnessVal = pScrollBar->GetScrollPos();
						//-- now transfer value to global variable
						FBus.sharpness = m_SharpnessVal;
						FB_SetVideoAdjustments(ADJUST_SHARPNESS, FBus.sharpness);
						break;

	}	//-- end of switch statement

	UpdateData(false); //-- update the edit-box display		

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CGrabberSettingsDlg::OnCancel() 
{
	//-- restore the originals
	FBus = 	FBusCopy;
	//-- Do the Video Adjustments -----------
	FB_SetVideoAdjustments(ADJUST_BRIGHTNESS, FBus.brightness);
	FB_SetVideoAdjustments(ADJUST_CONTRAST, FBus.contrast);
	FB_SetVideoAdjustments(ADJUST_SATURATION, FBus.saturation);
	FB_SetVideoAdjustments(ADJUST_HUE, FBus.hue);
	FB_SetVideoAdjustments(ADJUST_SHARPNESS, FBus.sharpness);
	CDialog::OnCancel();
}

void CGrabberSettingsDlg::OnDefaultButton() 
{
	//-- load default values -------------
	FBus.brightness = 34;
	FBus.contrast = 35;
	FBus.saturation = 32;
	FBus.hue = 0;
	FBus.sharpness = 7;

	//-- set the values in the edit box -----------
	m_BrightnessVal = FBus.brightness;
	m_ContrastVal = FBus.contrast;
	m_SaturationVal = FBus.saturation;
	m_HueVal = FBus.hue;
	m_SharpnessVal = FBus.sharpness;

	//-- set the scroll bar positions -------------
	m_Brightness.SetScrollPos(FBus.brightness);
	m_Contrast.SetScrollPos(FBus.contrast);
	m_Saturation.SetScrollPos(FBus.saturation);
	m_Hue.SetScrollPos(FBus.hue);
	m_Sharpness.SetScrollPos(FBus.sharpness);

	UpdateData(FALSE);//-- transfer control variables to screen

	//-- Do the Video Adjustments -----------
	FB_SetVideoAdjustments(ADJUST_BRIGHTNESS, FBus.brightness);
	FB_SetVideoAdjustments(ADJUST_CONTRAST, FBus.contrast);
	FB_SetVideoAdjustments(ADJUST_SATURATION, FBus.saturation);
	FB_SetVideoAdjustments(ADJUST_HUE, FBus.hue);
	FB_SetVideoAdjustments(ADJUST_SHARPNESS, FBus.sharpness);
}
