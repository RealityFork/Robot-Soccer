#ifndef DEBUG_INCLUDED_
#define DEBUG_INCLUDED_

#include "DebugDlg.h"

class Debug
{
public:
	Debug(){};
	static void init();
	static void e(CString);
	static void w(CString);
	static void i(CString);
	static void d(CString);
	static void appendEdit(CString);
};

#endif