#include "StdAfx.h"
#include "PhoneBookDBException.h"

CPhoneBookDBException::CPhoneBookDBException(TCHAR *szErrMsg)
{
  _tcscpy(m_szErrorMsg, szErrMsg);
}

CPhoneBookDBException::~CPhoneBookDBException(void)
{
}

TCHAR* CPhoneBookDBException::GetErrorMsg()
{
  return m_szErrorMsg;
}