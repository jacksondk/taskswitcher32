#include "stdafx.h"
#include "TaskSwitcher32.h"
#include "TaskSwitcher32Dlg.h"

#include <iostream>

#include "WindowItem.h"
#include "CommandLineParser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTaskSwitcher32App
BEGIN_MESSAGE_MAP(CTaskSwitcher32App, CWinApp)

END_MESSAGE_MAP()


// CTaskSwitcher32App construction
CTaskSwitcher32App::CTaskSwitcher32App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}
// The one and only CTaskSwitcher32App object
CTaskSwitcher32App theApp;


// CTaskSwitcher32App initialization
BOOL CTaskSwitcher32App::InitInstance()
{	
	CTaskCmdLineInfo info;
	ParseCommandLine( info );

	if ( info.Title.length() > 0 ) 
	{
		// Search for window title 
		int count = 0, idx = 0;
		window_list * list = window_item::get_window_list();
		for ( unsigned int i = 0; i < list->size(); i++ )
		{
			window_item *item = (*list)[i];
			if ( (item->get_lower_title().find( info.Title ) != std::string::npos) ||
				(item->get_process_name().find( info.Title ) != std::string::npos))
			{
				idx = i;
				count++;
			} 			
		}

		// If only one set the window to be foreground
		if ( count == 1 )
		{
			window_item *item = (*list)[idx];
			if ( ::IsIconic( item->get_handle() ) )
				::OpenIcon( item->get_handle() );

			SetForegroundWindow( item->get_handle() );
			return FALSE;
		}
		else if ( count == 0 ) // If no window found
		{
			if ( info.Executable.length() > 0 ) // and the /exe argument has been given start the program
			{
				STARTUPINFO si;
				PROCESS_INFORMATION pi;

				ZeroMemory( &si, sizeof(si) );
				si.cb = sizeof(si);
				ZeroMemory( &pi, sizeof(pi) );
				wchar_t *exe = _wcsdup( info.Executable.c_str() );
				wchar_t *wdir = NULL;
				if ( info.WorkingDir.length() > 0 ) wdir = _wcsdup( info.WorkingDir.c_str() );

				if ( ! CreateProcess( NULL, exe, NULL, NULL, FALSE, 0,NULL,
					wdir, &si, &pi ) )
				{
					DWORD err = GetLastError();	
				}
				free( exe );
				if (wdir) free( wdir );

				return FALSE;
			}
		}
	}
	// If abov special cases are not fulfilled show window with windows in listbox
	// Add the title argument as preentered search.

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	CTaskSwitcher32Dlg dlg( info.Title, NULL );
	m_pMainWnd = &dlg;

	INT_PTR nResponse = dlg.DoModal();

	return FALSE;
}
