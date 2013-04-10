#pragma once

#include "CommonDefinitions.h"

#define SUBSCRIBERS_TABLE_STRING_MAX_LEN	(64)
#define SUBSCRIBERS_ID_NUMB_LEN				(16)

struct CSubscribers
{
	TABLE_HEADER;
	int	 m_iCode;
	TCHAR m_szFirstName[SUBSCRIBERS_TABLE_STRING_MAX_LEN];
	TCHAR m_szSecondName[SUBSCRIBERS_TABLE_STRING_MAX_LEN];
	TCHAR m_szThirdName[SUBSCRIBERS_TABLE_STRING_MAX_LEN];
	TCHAR m_szIDNumb[SUBSCRIBERS_ID_NUMB_LEN];
	int   m_iCityId;
	TCHAR m_szAddress[SUBSCRIBERS_TABLE_STRING_MAX_LEN];
	
	CSubscribers(const int iId = DNC, const int iRevNumb = 0, const int iCode = DNC, const int iCityId = DNC, const TCHAR *pszFirstName = 0, 
				 const TCHAR *pszSecondName = 0, const TCHAR *pszThirdName = 0, const TCHAR *pszIDNumb = 0, const TCHAR *pszAddress = 0)
	{
		ZeroMemory(this, sizeof(*this));
		m_iId = iId;
		m_iRevNumb = iRevNumb;
		m_iCode = iCode;
		m_iCityId = iCityId;	 
		if(pszFirstName)_tcscpy(m_szFirstName, pszFirstName);	
		if(pszSecondName)_tcscpy(m_szSecondName, pszSecondName);	
		if(pszThirdName)_tcscpy(m_szThirdName, pszThirdName);	
		if(pszIDNumb)_tcscpy(m_szIDNumb, pszIDNumb);	
		if(pszAddress)_tcscpy(m_szAddress, pszAddress);	
	}

	BOOL operator==(CSubscribers op)
	{
		if(_tcscmp(m_szFirstName, op.m_szFirstName) ||
			 _tcscmp(m_szSecondName, op.m_szSecondName) ||
			 _tcscmp(m_szThirdName, op.m_szThirdName) ||
			 _tcscmp(m_szIDNumb, op.m_szIDNumb) ||
			 m_iCityId != op.m_iCityId ||
			 _tcscmp(m_szAddress, op.m_szAddress))
			 return FALSE;

		return TRUE;
 	}
	BOOL operator!=(CSubscribers op)
	{
		return !(*this == op);
	}
};

typedef CRowsPtrArray<CSubscribers>	CSubscribersArray;
