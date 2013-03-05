#pragma once

#include "DBTableInterface.h"
#include "Cities.h"
#include "Phones.h"
#include "Subscribers.h"
#include "SubscribersPhoneNumbers.h"

class CDBTablesFactory
{
  int m_iTablesCounter;
  TCHAR m_szDBName[64];
  CDatabase m_Database;
  CSubscribersPhoneNumbers *m_pcSubscrPhoneNmbTable;
  enum  eTableTypes{eCities = 0, ePhones, eSubscribers, eSubscrPhoneNumbs};
public:
  CDbTableInterface *GetFirstTable(void);
  CDbTableInterface *GetNextTable(void);
  CDBTablesFactory(const TCHAR *pszDSNName = 0, const TCHAR *pszDBName = 0);
  ~CDBTablesFactory(void);
};
