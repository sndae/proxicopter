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
  if(!hRow)
    return FALSE;

  CRowIdent *pRowId = static_cast<CRowIdent*>(hRow);
  Move(pRowId->m_iNmb);
  if(IsEOF() || IsBOF() || !CanUpdate())
    return FALSE;

  CDBVariant cDBVariant;
  GetFieldValue(_T("rev_nmb"), cDBVariant);
  if(cDBVariant.m_iVal != pRowId->m_iRev){
    return FALSE;
  }

  GetFieldValue(_T("Id"), cDBVariant);
  if(cDBVariant.m_iVal != pRowId->m_iId){
    return FALSE;
  }

  if(a_csRowData.GetCount() != (GetODBCFieldCount() - m_iUserOffset)){
    return FALSE;
  }

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
