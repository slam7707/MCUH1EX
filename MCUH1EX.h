
// MCUH1EX.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMCUH1EXApp:
// See MCUH1EX.cpp for the implementation of this class
//

class CMCUH1EXApp : public CWinApp
{
public:
	CMCUH1EXApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMCUH1EXApp theApp;
