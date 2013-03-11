#pragma once
#include "RowsPtrArray.h"
#define SUBSCRIBERS_TABLE_STRING_MAX_LEN   (64)
#define SUBSCRIBERS_ID_NUMB_LEN			       (16)

struct CSubscribers
{
  int   m_iId;
  int   m_iRevNumb;
  int   m_iCode;
  TCHAR m_szFirstName[SUBSCRIBERS_TABLE_STRING_MAX_LEN];
  TCHAR m_szSecondName[SUBSCRIBERS_TABLE_STRING_MAX_LEN];
  TCHAR m_szThirdName[SUBSCRIBERS_TABLE_STRING_MAX_LEN];
  TCHAR m_szIDNumb[SUBSCRIBERS_ID_NUMB_LEN];
  TCHAR m_szCityCode[SUBSCRIBERS_TABLE_STRING_MAX_LEN];
  TCHAR m_szAddress[SUBSCRIBERS_TABLE_STRING_MAX_LEN];
  
  CSubscribers(const int iId = -1, const int iRevNumb = 0, const int iCode = -1, const TCHAR *pszCityCode = 0, const TCHAR *pszFirstName = 0, 
			   const TCHAR *pszSecondName = 0, const TCHAR *pszThirdName = 0, const TCHAR *pszIDNumb = 0, const TCHAR *pszAddress = 0)
  {
    ZeroMemory(this, sizeof(*this));
    m_iId = iId;
    m_iRevNumb = iRevNumb;
    m_iCode = iCode;
    if(pszCityCode)_tcscpy(m_szCityCode, pszCityCode);  
    if(pszFirstName)_tcscpy(m_szFirstName, pszFirstName);  
    if(pszSecondName)_tcscpy(m_szSecondName, pszSecondName);  
    if(pszThirdName)_tcscpy(m_szThirdName, pszThirdName);  
    if(pszIDNumb)_tcscpy(m_szIDNumb, pszIDNumb);  
    if(pszAddress)_tcscpy(m_szAddress, pszAddress);  
  }
};

typedef CRowsPtrArray<CSubscribers>  CSubscribersArray;
