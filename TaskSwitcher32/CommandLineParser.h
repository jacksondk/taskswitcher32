#ifndef COMMAND_LINE_PARSE
#define COMMAND_LINE_PARSE

#include "stdafx.h"

#include <string>

class CTaskCmdLineInfo : public CCommandLineInfo
{
public:
	CTaskCmdLineInfo();

	std::wstring Title;
	std::wstring Executable;
	std::wstring WorkingDir;

	virtual void ParseParam( const TCHAR *pszParam, BOOL bFlag, BOOL bLast );

private:
	std::wstring _last_flag;
};

#endif