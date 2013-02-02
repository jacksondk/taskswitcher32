// TaskSwitcher32.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTaskSwitcher32App:
// See TaskSwitcher32.cpp for the implementation of this class
//

class CTaskSwitcher32App : public CWinApp
{
public:
	CTaskSwitcher32App();

// Overrides
	public:
	virtual BOOL InitInstance();
	
// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTaskSwitcher32App theApp;