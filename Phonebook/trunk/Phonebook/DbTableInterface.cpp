#include "StdAfx.h"
#include ".\dbtableinterface.h"


CDbTableInterface::~CDbTableInterface(void)
{
  Close();
}

HANDLE CDbTableInterface::ReadRow(CArray<CString> &a_csRowData,  int iRowNmbr)
{
  Move(iRowNmbr);
  if(IsEOF() || IsBOF())
    return 0;

  CString szFieldData;

  CDBVariant cDBVariant;
  CRowIdent *pcRowId = new CRowIdent();
  
  GetFieldValue(_T("rev_nmb"), cDBVariant);
  pcRowId->m_iRev = cDBVariant.m_iVal;
  GetFieldValue(_T("Id"), cDBVariant);
  pcRowId->m_iId = cDBVariant.m_iVal;
  pcRowId->m_iNmb = iRowNmbr;

  for(int i = m_iUserOffset; i < GetODBCFieldCount(); i++){
    GetFieldValue(i, szFieldData);
    a_csRowData.Add(szFieldData);
  }

  return (HANDLE)pcRowId; 
}

BOOL CDbTableInterface::WriteRow(CArray<CString> &a_csRowData, HANDLE hRow)
{
  return TRUE;
}



BOOL CDbTableInterface::ReadRowFieldNames(CArray<CString> &acsRowData)
{
  for(int i = m_iUserOffset; i < m_aszFieldsNames.GetCount(); i++){
    acsRowData.Add(m_aszFieldsNames[i]);
  } 

  return TRUE;
}

BOOL CDbTableInterface::LoadDb(const CString &csTableName, const CArray<CString> &a_csFieldsName)
{
  m_szTableName = csTableName;
  m_aszFieldsNames.Append(a_csFieldsName);

  return Open(CRecordset::dynaset);
}
