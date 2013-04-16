#pragma once

#include "CommonDefinitions.h"

#define CITIES_TABLE_STRING_MAX_LEN	 (64)

struct CCities
{
	TABLE_HEADER;
	TCHAR m_szCode[CITIES_TABLE_STRING_MAX_LEN];
	TCHAR m_szName[CITIES_TABLE_STRING_MAX_LEN];
	TCHAR m_szArea[CITIES_TABLE_STRING_MAX_LEN];	
	CCities(const int iId = DNC, const int iRevNumb = 0, const TCHAR *pszCode = 0, 
					const TCHAR *pszName = 0, const TCHAR *pszArea = 0)
	{
		ZeroMemory(this, sizeof(*this));
		m_nId = iId;
		m_nRevNumb = iRevNumb;
		if(pszCode)_tcscpy(m_szCode, pszCode);
		if(pszName)_tcscpy(m_szName, pszName);
		if(pszArea)_tcscpy(m_szArea, pszArea);		
	}
	BOOL operator==(CCities op)
	{
		if(_tcscmp(m_szCode, op.m_szCode) ||
		 	 _tcscmp(m_szName, op.m_szName) ||
			 _tcscmp(m_szArea, op.m_szArea))
			 return FALSE;

		return TRUE;
	}
};

typedef CRowsPtrArray<CCities>	CCitiesArray;
