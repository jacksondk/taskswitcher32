#include "stdafx.h"

#include "CommandLineParser.h"

CTaskCmdLineInfo::CTaskCmdLineInfo()
{

}

void CTaskCmdLineInfo::ParseParam(const TCHAR *pszParam, BOOL bFlag, BOOL bLast)
{
	if ( bFlag )
	{
		this->_last_flag = std::wstring( pszParam );
	}
	else
	{
		if ( this->_last_flag.compare( _T( "exe" ) ) == 0 )
		{
			this->Executable = std::wstring( pszParam );
		}
		else if ( this->_last_flag.compare( _T( "title" ) ) == 0 )
		{
			this->Title = std::wstring( pszParam );
		}
		else if ( this->_last_flag.compare( _T( "dir" ) ) == 0 )
		{
			this->WorkingDir = std::wstring( pszParam );
		}
	}
}