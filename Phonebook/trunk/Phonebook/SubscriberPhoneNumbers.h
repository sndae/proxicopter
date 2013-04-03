#pragma once

#include "CommonDefinitions.h"

#define SUBSCRIBERPHONENUMBERS_TABLE_STRING_MAX_LEN		(64)
#define SUBSCRIBERPHONENUMBERS_ID_NUMB_LEN				(16)

struct CSubscriberPhoneNumbers
{
	TABLE_HEADER;
	int	 m_iSubscrCode;
	int	 m_iPhoneCode;
	TCHAR m_szPhoneNumber[SUBSCRIBERPHONENUMBERS_TABLE_STRING_MAX_LEN];
	
	CSubscriberPhoneNumbers(const int iId = DNC, const int iRevNumb = 0, const int iSubscrCode = DNC, const int iPhoneCode = DNC, const TCHAR *pszCityCode = 0)
	{
		ZeroMemory(this, sizeof(*this));
		m_iId = iId;
		m_iRevNumb = iRevNumb;
		m_iSubscrCode = iSubscrCode;
		m_iPhoneCode = iPhoneCode;
		if(pszCityCode)_tcscpy(m_szPhoneNumber, pszCityCode);
	}
	
	BOOL operator==(CSubscriberPhoneNumbers op)
	{
		if((m_iSubscrCode != op.m_iSubscrCode) ||
			(m_iPhoneCode != op.m_iPhoneCode) ||
			_tcscmp(m_szPhoneNumber, op.m_szPhoneNumber))
			return FALSE;

		return TRUE;
	}
	BOOL operator!=(CSubscriberPhoneNumbers op)
	{
		return !(*this == op);
	}
};

typedef CRowsPtrArray<CSubscriberPhoneNumbers>	CSubscriberPhoneNumbersArray;
