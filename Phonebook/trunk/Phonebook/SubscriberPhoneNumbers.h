#pragma once

#include "CommonDefinitions.h"

#define SUBSCRIBERPHONENUMBERS_TABLE_STRING_MAX_LEN		(64)
#define SUBSCRIBERPHONENUMBERS_ID_NUMB_LEN				(16)

struct CSubscriberPhoneNumbers
{
	TABLE_HEADER;
	int	 m_nSubscrId;
	int	 m_nPhoneId;
	TCHAR m_szPhoneNumber[SUBSCRIBERPHONENUMBERS_TABLE_STRING_MAX_LEN];
	
	CSubscriberPhoneNumbers(const int iId = DNC, const int iRevNumb = 0, const int iSubscrId = DNC, const int iPhoneId = DNC, const TCHAR *pszPhoneNumb = 0)
	{
		ZeroMemory(this, sizeof(*this));
		m_nId = iId;
		m_nRevNumb = iRevNumb;
		m_nSubscrId = iSubscrId;
		m_nPhoneId = iPhoneId;
		if(pszPhoneNumb)_tcscpy(m_szPhoneNumber, pszPhoneNumb);
	}
	
	CSubscriberPhoneNumbers & operator=(const CSubscriberPhoneNumbers &op)
	{
		m_nId = op.m_nId;
		m_nRevNumb = op.m_nRevNumb;
		m_nSubscrId = op.m_nSubscrId;
		m_nPhoneId = op.m_nPhoneId;
		_tcscpy(m_szPhoneNumber, op.m_szPhoneNumber);	

		return *this;
	}

	BOOL operator==(CSubscriberPhoneNumbers op)
	{
		if((m_nSubscrId != op.m_nSubscrId) ||
			(m_nPhoneId != op.m_nPhoneId) ||
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
