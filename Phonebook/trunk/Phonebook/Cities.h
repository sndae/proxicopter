#pragma once
#include "RowsPtrArray.h"
#define CITIES_TABLE_STRING_MAX_LEN   (64)

struct CCities
{
  int   m_iId;
  int   m_iRevNumb;
  TCHAR m_szCode[CITIES_TABLE_STRING_MAX_LEN];
  TCHAR m_szName[CITIES_TABLE_STRING_MAX_LEN];
  TCHAR m_szArea[CITIES_TABLE_STRING_MAX_LEN];  
  CCities(const int iId = 0, const int iRevNumb = 0, const TCHAR *pszCode = 0, 
          const TCHAR *pszName = 0, const TCHAR *pszArea = 0)
  {
    ZeroMemory(this, sizeof(*this));
    m_iId = iId;
    m_iRevNumb = iRevNumb;
    if(pszCode)_tcscpy(m_szCode, pszCode);
    if(pszName)_tcscpy(m_szName, pszName);
    if(pszArea)_tcscpy(m_szArea, pszArea);    
  }
};

typedef CRowsPtrArray<CCities>  CCitiesArray;
