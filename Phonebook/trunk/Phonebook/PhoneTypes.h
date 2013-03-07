#pragma once
#include "RowsPtrArray.h"
#define PHONETYPES_TABLE_STRING_MAX_LEN   (64)

struct CPhoneTypes
{
  int   m_iId;
  int   m_iRevNumb;
  TCHAR m_szType[PHONETYPES_TABLE_STRING_MAX_LEN];
  TCHAR m_szCode[PHONETYPES_TABLE_STRING_MAX_LEN];  
  
  CPhoneTypes(const int iId = 0, const int iRevNumb = 0, const TCHAR *pszCode = 0, const TCHAR *pszType = 0)
  {
    ZeroMemory(this, sizeof(*this));
    m_iId = iId;
    m_iRevNumb = iRevNumb;
    if(pszCode)_tcscpy(m_szCode, pszCode);
    if(pszType)_tcscpy(m_szType, pszType);  
  }
};

typedef CRowsPtrArray<CPhoneTypes>  CPhoneTypesArray;
