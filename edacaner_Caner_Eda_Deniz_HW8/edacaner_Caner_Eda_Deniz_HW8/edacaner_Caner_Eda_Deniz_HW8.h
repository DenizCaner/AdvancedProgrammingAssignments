
// edacaner_Caner_Eda_Deniz_HW8.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Cedacaner_Caner_Eda_Deniz_HW8App:
// See edacaner_Caner_Eda_Deniz_HW8.cpp for the implementation of this class
//

class Cedacaner_Caner_Eda_Deniz_HW8App : public CWinApp
{
public:
	Cedacaner_Caner_Eda_Deniz_HW8App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Cedacaner_Caner_Eda_Deniz_HW8App theApp;