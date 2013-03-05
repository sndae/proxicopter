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
  CCities(void)
  {
    ZeroMemory(this, sizeof(*this));
  };
  CCities(int iId, int iRevNumb, TCHAR *pszCode, TCHAR *pszName, TCHAR *pszArea)
  {
    m_iId = iId;
    m_iRevNumb = iRevNumb;
    _tcscpy(m_szCode, pszCode);
    _tcscpy(m_szName, pszName);
    _tcscpy(m_szArea, pszArea);    
  }
};

typedef CRowsPtrArray<CCities>  CCitiesArray;
