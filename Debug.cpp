#include "Debug.h"

void Debug::init()
{
	globaldata.debugDlg->m_checkDebug = true;
	globaldata.debugDlg->m_checkError = true;
	globaldata.debugDlg->m_checkInfo = true;
	globaldata.debugDlg->m_checkWarning = true;
	globaldata.debugDlg->UpdateData(FALSE);
}

void Debug::e(CString s)
{
	if (globaldata.debugDlg->m_checkError)
	{
		CString out;
		out.Format("\r\nERROR:      %s", s);
		appendEdit(out);
	}
}
void Debug::w(CString s)
{
	if (globaldata.debugDlg->m_checkWarning)
	{
		CString out;
		out.Format("\r\nWARNING: %s", s);
		appendEdit(out);
	}
}
void Debug::i(CString s)
{
	if (globaldata.debugDlg->m_checkInfo)
	{
		CString out;
		out.Format("\r\nINFO:           %s", s);
		appendEdit(out);
	}
}
void Debug::d(CString s)
{
	if (globaldata.debugDlg->m_checkDebug)
	{
		CString out;
		out.Format("\r\nDEBUG:       %s", s);
		appendEdit(out);
	}
}
void Debug::appendEdit(CString s)
{
	int end = globaldata.debugDlg->m_debugEdit.GetWindowTextLength();
	globaldata.debugDlg->m_debugEdit.SetSel(end, end);
	globaldata.debugDlg->m_debugEdit.ReplaceSel(s);
}