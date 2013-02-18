#include "StdAfx.h"
#include "PhonebookRecSet.h"
#include "PhonebookDBException.h"

CPhonebookRecSet::CPhonebookRecSet(CDatabase &cDatabase, TCHAR *pszTableName, TCHAR *pszAttr)
:CRecordset(&cDatabase)
{ 
  CString csSQLcmd;
  if(pszAttr)
    csSQLcmd.Format(_T("SELECT %s FROM %s"), pszAttr, pszTableName);
  else
    csSQLcmd.Format(_T("SELECT * FROM %s"), pszTableName);

  if(Open(CRecordset::dynaset, csSQLcmd) == 0)
    throw CPhoneBookDBException(_T("Unable to open recordset"));
  else if(IsBOF())
    throw CPhoneBookDBException(_T("Empty recordset"));

  int iFieldsNmb = GetODBCFieldCount();
  CDBVariant varValue;
  while(!IsEOF()){
    for(int i = 0; i < iFieldsNmb; i++ )
    {
      GetFieldValue( i, varValue );
      // do something with varValue
    }
    MoveNext( );
  }
}

CPhonebookRecSet::~CPhonebookRecSet(void)
{  
}
