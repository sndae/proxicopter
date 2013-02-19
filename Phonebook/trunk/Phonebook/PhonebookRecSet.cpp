#include "StdAfx.h"
#include "PhonebookRecSet.h"
#include "PhonebookDBException.h"

CPhonebookRecSet::CPhonebookRecSet(CDatabase *pcDatabase)
:CRecordset(pcDatabase)
{ 
  m_iCurrRowRevNumber = 0;
  m_iCurrRowRevNumber = 0;
  m_cAttrList.Add(CDispnameToAttrname(_T(""), _T("Id")));
  m_cAttrList.Add(CDispnameToAttrname(_T(""), _T("rev_nmb")));   
  m_iUserOffset = m_cAttrList.GetCount();
}

CPhonebookRecSet::~CPhonebookRecSet(void)
{
  Close();
}

BOOL CPhonebookRecSet::MoveToFirstRow()
{
  if(!IsBOF()){
    MoveFirst();
    UpdateCurrRowRevNumber();
    return TRUE;
  }
  
  return FALSE;
}

BOOL CPhonebookRecSet::MoveToNextRow()
{
  MoveNext();
  if(!IsEOF())
  {
    UpdateCurrRowRevNumber();
    return TRUE;
  }

  return FALSE;
}

BOOL CPhonebookRecSet::MoveToPrevRow()
{
  MovePrev();
  if(!IsBOF())    
    return TRUE;

  return FALSE;
}

BOOL CPhonebookRecSet::GetRowFirstAtrrVal(TCHAR *pszText, TCHAR **pszDispName)
{
  m_iRowAttrCntr = m_iUserOffset;    
  return GetRowNextAtrrVal(pszText, pszDispName);
}

BOOL CPhonebookRecSet::GetRowPrevAtrrVal(TCHAR *pszText, TCHAR **pszDispName)
{
  CString csTextData;
  if(m_iRowAttrCntr >= m_iUserOffset)
  {
    m_iRowAttrCntr--;
    if(pszDispName){
      *pszDispName = m_cAttrList.GetAt(m_iRowAttrCntr).m_szDispName;
    }
    GetFieldValue(m_iRowAttrCntr, csTextData);
    _tcscpy(pszText, csTextData);
    return TRUE;
  }

  return FALSE;
}

BOOL CPhonebookRecSet::GetRowNextAtrrVal(TCHAR *pszText,  TCHAR **pszDispName)
{
  CString csTextData;
  if(m_iRowAttrCntr < GetODBCFieldCount())
  {
    if(pszDispName){
      *pszDispName = m_cAttrList.GetAt(m_iRowAttrCntr).m_szDispName;
    }
    GetFieldValue(m_iRowAttrCntr++, csTextData);
    _tcscpy(pszText, csTextData);
    return TRUE;
  }

  return FALSE;
}

BOOL  CPhonebookRecSet::MoveToRow(int iNmbr)
{
  m_iRowAttrCntr = m_iUserOffset + iNmbr;
  SetAbsolutePosition(m_iRowAttrCntr);
  if(IsEOF() || IsBOF())
    return FALSE;

  return TRUE;
}

BOOL  CPhonebookRecSet::ReadRowAttributesNames(CArray<CString> &a_csRowData)
{
  for(int i = m_iUserOffset; i < m_cAttrList.GetCount(); i++){
    a_csRowData.Add(m_cAttrList[i].m_szDispName);
  } 

  return TRUE;
}

BOOL  CPhonebookRecSet::WriteRow(CArray<CString> &a_csRowData, HANDLE hRow)
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
}

HANDLE CPhonebookRecSet::ReadRow(CArray<CString> &a_csRowData, int iRowNmbr)
{
  Move(iRowNmbr);
  if(IsEOF() || IsBOF())
    return 0;

  CString szFieldData;

  CDBVariant cDBVariant;
  CRowIdent *pcRowId = new CRowIdent();
  
  GetFieldValue(_T("rev_nmb"), cDBVariant);
  pcRowId->m_iRev = cDBVariant.m_iVal;
  GetFieldValue(_T("id"), cDBVariant);
  pcRowId->m_iId = cDBVariant.m_iVal;
  pcRowId->m_iNmb = iRowNmbr;

  for(int i = m_iUserOffset; i < GetODBCFieldCount(); i++){
    GetFieldValue(i, szFieldData);
    a_csRowData.Add(szFieldData);
  }

  return (HANDLE)pcRowId; 
} 

BOOL CPhonebookRecSet::LoadDB(CDispnameToAttrname tTableName, CDispnameToAttrname *patAttrList, int fFlags)
{  
  if(IsOpen())
    Close();

  CString csSQLcmd(_T("SELECT "));
  for(int i = m_iUserOffset; i < m_cAttrList.GetCount(); i++)
  {
    m_cAttrList.RemoveAt(i);
  }

  if(patAttrList){
    while(1)
    {
      if(_tcsclen(patAttrList->m_szAttrName))
        m_cAttrList.Add(*patAttrList++);
      else
        break;
    }
  }

  for(int i = 0; i < m_cAttrList.GetCount(); )
  {
    csSQLcmd += m_cAttrList.GetAt(i).m_szAttrName;
    if(++i != m_cAttrList.GetCount())
      csSQLcmd += _T(",");
  }

  csSQLcmd += _T(" FROM ");
  csSQLcmd += tTableName.m_szAttrName;

  if(Open(CRecordset::dynaset, csSQLcmd) == 0)
    return FALSE;
  else if(IsBOF())
    return FALSE;

  m_cTableName = tTableName;

  return TRUE;
}

void CPhonebookRecSet::UpdateCurrRowRevNumber()
{
  CDBVariant cDBVariant;
  GetFieldValue(_T("rev_nmb"), cDBVariant);
  m_iCurrRowRevNumber = cDBVariant.m_iVal;
}
