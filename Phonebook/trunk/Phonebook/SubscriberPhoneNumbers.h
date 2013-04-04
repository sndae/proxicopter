#pragma once

#include "CommonDefinitions.h"

#define SUBSCRIBERPHONENUMBERS_TABLE_STRING_MAX_LEN		(64)
#define SUBSCRIBERPHONENUMBERS_ID_NUMB_LEN				(16)

struct CSubscriberPhoneNumbers
{
	TABLE_HEADER;
	int	 m_iSubscrId;
	int	 m_iPhoneId;
	TCHAR m_szPhoneNumber[SUBSCRIBERPHONENUMBERS_TABLE_STRING_MAX_LEN];
	
	CSubscriberPhoneNumbers(const int iId = DNC, const int iRevNumb = 0, const int iSubscrId = DNC, const int iPhoneId = DNC, const TCHAR *pszPhoneNumb = 0)
	{
		ZeroMemory(this, sizeof(*this));
		m_iId = iId;
		m_iRevNumb = iRevNumb;
		m_iSubscrId = iSubscrId;
		m_iPhoneId = iPhoneId;
		if(pszPhoneNumb)_tcscpy(m_szPhoneNumber, pszPhoneNumb);
	}
	
	CSubscriberPhoneNumbers & operator=(const CSubscriberPhoneNumbers &op)
	{
		m_iId = op.m_iId;
		m_iRevNumb = op.m_iRevNumb;
		m_iSubscrId = op.m_iSubscrId;
		m_iPhoneId = op.m_iPhoneId;
		_tcscpy(m_szPhoneNumber, op.m_szPhoneNumber);	

		return *this;
	}

	BOOL operator==(CSubscriberPhoneNumbers op)
	{
		if((m_iSubscrId != op.m_iSubscrId) ||
			(m_iPhoneId != op.m_iPhoneId) ||
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
