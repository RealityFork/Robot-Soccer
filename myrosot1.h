// myrosot1.h : main header file for the MYROSOT1 application
//

#if !defined(AFX_MYROSOT1_H__F3F95E84_E074_11D2_8B75_817FE7DC6734__INCLUDED_)
#define AFX_MYROSOT1_H__F3F95E84_E074_11D2_8B75_817FE7DC6734__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "resource.h"		// main symbols
#include "myrosot1Dlg.h"
#include "stdafx.h"
#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif


/////////////////////////////////////////////////////////////////////////////
// CMyrosot1App:
// See myrosot1.cpp for the implementation of this class
//

class CMyrosot1App : public CWinApp
{
public:
	CMyrosot1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyrosot1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyrosot1App)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYROSOT1_H__F3F95E84_E074_11D2_8B75_817FE7DC6734__INCLUDED_)
