#pragma once

#include "CommonDefinitions.h"

#define PHONETYPES_TABLE_STRING_MAX_LEN   (64)

struct CPhoneTypes
{
  TABLE_HEADER;
  int   m_iCode;
  TCHAR m_szType[PHONETYPES_TABLE_STRING_MAX_LEN];
  
  CPhoneTypes(const int iId = -2, const int iRevNumb = 0, const int iCode = -1, const TCHAR *pszType = 0)
  {
    ZeroMemory(this, sizeof(*this));
    m_iId = iId;
    m_iRevNumb = iRevNumb;
    m_iCode = iCode;
    if(pszType)_tcscpy(m_szType, pszType);  
  }
};

typedef CRowsPtrArray<CPhoneTypes>  CPhoneTypesArray;
