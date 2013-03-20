#pragma once

#include "CommonDefinitions.h"

#define SubscriberPhoneNumbers_TABLE_STRING_MAX_LEN   (64)
#define SubscriberPhoneNumbers_ID_NUMB_LEN			       (16)

struct CSubscriberPhoneNumbers
{
  TABLE_HEADER;
  int   m_iCode;
  TCHAR m_szFirstName[SubscriberPhoneNumbers_TABLE_STRING_MAX_LEN];
  TCHAR m_szSecondName[SubscriberPhoneNumbers_TABLE_STRING_MAX_LEN];
  TCHAR m_szThirdName[SubscriberPhoneNumbers_TABLE_STRING_MAX_LEN];
  TCHAR m_szIDNumb[SubscriberPhoneNumbers_ID_NUMB_LEN];
  TCHAR m_szCityCode[SubscriberPhoneNumbers_TABLE_STRING_MAX_LEN];
  TCHAR m_szAddress[SubscriberPhoneNumbers_TABLE_STRING_MAX_LEN];
  
  CSubscriberPhoneNumbers(const int iId = DNC, const int iRevNumb = 0, const int iCode = DNC, const TCHAR *pszCityCode = 0, const TCHAR *pszFirstName = 0, 
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

typedef CRowsPtrArray<CSubscriberPhoneNumbers>  CSubscriberPhoneNumbersArray;
