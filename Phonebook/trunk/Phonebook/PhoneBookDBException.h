#pragma once

class CPhoneBookDBException
{
private:
  TCHAR m_szErrorMsg[64];
public:
  CPhoneBookDBException(TCHAR *szErrMsg);
  ~CPhoneBookDBException(void);
  TCHAR *GetErrorMsg();
};
