#include "StdAfx.h"
#include "PhonebookRecSet.h"
#include "PhonebookDBException.h"

CPhonebookRecSet::CPhonebookRecSet(CDatabase *pcDatabase)
:CRecordset(pcDatabase)
{ 
  m_iCurrRowRevNumber = 0;
  m_iCurrRowRevNumber = 0;
  m_pcDatabase = pcDatabase;
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

BOOL CPhonebookRecSet::GetRowFirstAtrrVal(CDBVariant &cDBVariant, TCHAR **pszDispName)
{
  m_iRowAttrCntr = m_iUserOffset;    
  return GetRowNextAtrrVal(cDBVariant, pszDispName);
}

BOOL CPhonebookRecSet::GetRowPrevAtrrVal(CDBVariant &cDBVariant, TCHAR **pszDispName)
{
  if(m_iRowAttrCntr >= m_iUserOffset)
  {
    m_iRowAttrCntr--;
    if(pszDispName){
      *pszDispName = m_cAttrList.GetAt(m_iRowAttrCntr).m_szDispName;
    }
    GetFieldValue(m_iRowAttrCntr, cDBVariant);
    return TRUE;
  }

  return FALSE;
}

BOOL CPhonebookRecSet::GetRowNextAtrrVal(CDBVariant &cDBVariant,  TCHAR **pszDispName)
{
  if(m_iRowAttrCntr < GetODBCFieldCount())
  {
    if(pszDispName){
      *pszDispName = m_cAttrList.GetAt(m_iRowAttrCntr).m_szDispName;
    }
    GetFieldValue(m_iRowAttrCntr++, cDBVariant);
    return TRUE;
  }

  return FALSE;
}

BOOL CPhonebookRecSet::LoadDB(CDispnameToAttrname tTableName, CDispnameToAttrname *patAttrList, int fFlags)
{
  CString csSQLcmd(_T("SELECT "));

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
