#include "stdafx.h"
#include <psapi.h>
#include <string.h>
#include "WindowItem.h"

// Ctor for window description class
window_item::window_item(std::wstring title, std::wstring process_name, HWND handle)
{
	this->_title = title;
	this->_lower_title = _title;
	for ( std::wstring::size_type i = 0; i < _lower_title.length(); i++ )
	{
		this->_lower_title[i] = towlower( this->_lower_title[i] );
	}
	this->_process_name = process_name;
	this->_handle = handle;
}

window_list *list = NULL;

/// Call back for EnumWindows in window::get_window_list() method. Adds window_items to global list 
BOOL CALLBACK addWindows( HWND handle, LPARAM param )
{
	TCHAR title[100];
	WINDOWINFO window_info;
	
	GetWindowInfo( handle,&window_info );

	if ( window_info.rcWindow.right - window_info.rcWindow.left > 0 &&
		window_info.rcWindow.bottom - window_info.rcClient.top > 0 && 
		IsWindowVisible( handle ))
	{
		GetWindowText( handle, title, 100 );
		//GetWindowThreadProcessId( handle, & processId );
		wchar_t processname[200];
		//int length = GetWindowModuleFileName( handle, processname, 200 );
		DWORD processID;
		GetWindowThreadProcessId( handle, &processID );
		HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                            PROCESS_VM_READ,
                            FALSE, processID );

		int length = GetModuleFileNameEx( hProcess, NULL, processname, 200 );
		CloseHandle( hProcess );
		if ( length == 0 )
			processname[0] = '\0';
		
		if ( wcslen( title ) > 0  )
		{
			list->push_back( new window_item( title , processname, handle ) );
		}
	}
	return TRUE;
}

/// Initial enumeration of window list
window_list * window_item::get_window_list()
{
	if ( list == NULL )
	{
		list = new window_list();
		EnumWindows( addWindows, 0 );
	}
	return list;
}