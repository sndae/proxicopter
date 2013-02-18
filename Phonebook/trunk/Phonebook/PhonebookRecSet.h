#pragma once
#include "afxdb.h"

class CPhonebookRecSet :
  private CRecordset
{
public:
  CPhonebookRecSet(CDatabase &cDatabase, TCHAR *pszTableName, TCHAR *pszAttr = 0); 
  ~CPhonebookRecSet(void);
};
