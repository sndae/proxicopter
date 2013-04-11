#pragma once

#include "CommonDefinitions.h"

#define PHONETYPES_TABLE_STRING_MAX_LEN	 (64)

struct CPhoneTypes
{
	TABLE_HEADER;
	int	 m_nCode;
	TCHAR m_szType[PHONETYPES_TABLE_STRING_MAX_LEN];
	
	CPhoneTypes(const int iId = DNC, const int iRevNumb = 0, const int iCode = DNC, const TCHAR *pszType = 0)
	{
		ZeroMemory(this, sizeof(*this));
		m_nId = iId;
		m_nRevNumb = iRevNumb;
		m_nCode = iCode;
		if(pszType)_tcscpy(m_szType, pszType);	
	}
};

typedef CRowsPtrArray<CPhoneTypes> CPhoneTypesArray;
