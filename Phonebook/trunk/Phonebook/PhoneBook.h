// PhoneBook.h : main header file for the PhoneBook application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPhoneBookApp:
// See PhoneBook.cpp for the implementation of this class
//

class CPhoneBookApp : public CWinApp
{
public:
	CPhoneBookApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPhoneBookApp theApp;