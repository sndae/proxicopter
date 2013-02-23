#include "StdAfx.h"
#include "DBTablesContainer.h"
#include "DBTableInterface.h"

CDBTablesFactory::CDBTablesFactory(const TCHAR *pszDSNName, const TCHAR *pszDBName)
{
  if(!m_Database.Open(pszDSNName))
    return;

  if(pszDBName)
    _tcscpy(m_szDBName, pszDBName);
}

CDBTablesFactory::~CDBTablesFactory(void)
{
  m_Database.Close();
}

CDbTableInterface *CDBTablesFactory::GetFirstTable(void)
{
  m_iTablesCounter = 0;
  return GetNextTable();
}

CDbTableInterface *CDBTablesFactory::GetNextTable(void)
{
  CDbTableInterface *pcTable = 0;
  switch(m_iTablesCounter++)
  {
    case eCities: pcTable = new CCities(&m_Database, m_szDBName); break;
    case ePhones: pcTable = new CPhones(&m_Database, m_szDBName); break;
    case eSubscribers: pcTable = new CSubscribers(&m_Database, m_szDBName); break;
    case eSubscrPhoneNumbs: pcTable = new CSubscribersPhoneNumbers(&m_Database, m_szDBName); break;
  }
  
 return pcTable;
}
