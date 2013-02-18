#include "StdAfx.h"
#include "PhonebookRecSet.h"
#include "PhonebookDBException.h"

CPhonebookRecSet::CPhonebookRecSet(CDatabase *pcDatabase)
:CRecordset(pcDatabase)
{ 
  m_pcDatabase = pcDatabase;
  m_cAttrList.Add(CDispnameToAttrname(0, _T("Id")));
  m_cAttrList.Add(CDispnameToAttrname(0, _T("rev_nmb")));    
}

CPhonebookRecSet::~CPhonebookRecSet(void)
{
  Close();
}

BOOL CPhonebookRecSet::MoveToFirstRow()
{
  if(!IsBOF()){
    MoveFirst();
    return TRUE;
  }

  return FALSE;
}

BOOL CPhonebookRecSet::MoveToNextRow()
{
  if(!IsEOF())
  {
    MoveNext();
    return TRUE;
  }

  return FALSE;
}

BOOL CPhonebookRecSet::GetRowFirstAtrrVal(CDBVariant &cDBVariant)
{
  m_iRowAttrCntr = 0;  
  return GetRowNextAtrrVal(cDBVariant);
}

BOOL CPhonebookRecSet::GetRowNextAtrrVal(CDBVariant &cDBVariant)
{
  if(m_iRowAttrCntr < GetODBCFieldCount())
  {
    GetFieldValue(m_iRowAttrCntr++, cDBVariant);
    return TRUE;
  }

  return FALSE;
}

BOOL CPhonebookRecSet::LoadDB(TCHAR *pszTableName, CDispnameToAttrname *apszAttr[], int fFlags)
{
  CString csSQLcmd(_T("SELECT "));
  
  if(apszAttr){
    for (int i = 0; *apszAttr[i]->m_pszAttrName == 0; ){
      m_cAttrList.Add(*apszAttr[i]);
      csSQLcmd += *apszAttr[i]->m_pszAttrName;
      if(*apszAttr[++i]->m_pszAttrName)
        csSQLcmd += _T(",");
    };

    csSQLcmd += _T(" FROM ");
    csSQLcmd += pszTableName;

  }else
    csSQLcmd.Format(_T("SELECT * FROM %s"), pszTableName);

  if(Open(CRecordset::dynaset, csSQLcmd) == 0)
    return FALSE;
  else if(IsBOF())
    return FALSE;

  return TRUE;
}

