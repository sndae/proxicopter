#pragma once
#include "PhonebookRecSet.h"

class CCitiesTable :
  public  CPhonebookRecSet
{
  static const CDispnameToAttrname m_stDispAttrName[2];
public:
  CCitiesTable(CDatabase &cDatabase);
  ~CCitiesTable(void);
  TCHAR *GetCurrAttrName();
};
