#pragma once
#include "afxdb.h"
#include "afxtempl.h"

class CPhonebookRecSet :
  private CRecordset
{
protected:
  int m_iRowAttrCntr;
  struct CDispnameToAttrname{
    TCHAR m_pszDispName[64];
    TCHAR m_pszAttrName[64];  
    CDispnameToAttrname(){};
    CDispnameToAttrname(TCHAR *pszDispName, TCHAR *pszAttrName)
    {
      if(pszDispName) _tcscpy(m_pszDispName, pszDispName);
      if(pszAttrName) _tcscpy(m_pszAttrName, pszAttrName);
    };
  };
private:
  CArray<CDispnameToAttrname> m_cAttrList;
  CDatabase *m_pcDatabase;
public:
  BOOL LoadDB(TCHAR *pszTableName, CDispnameToAttrname *apszAttr[], int fFlags);
  virtual BOOL   MoveToFirstRow();
  virtual BOOL   MoveToNextRow();
  virtual BOOL   GetRowFirstAtrrVal(CDBVariant &cDBVariant);
  virtual BOOL   GetRowNextAtrrVal(CDBVariant &cDBVariant);
  virtual TCHAR *GetCurrAttrName() = 0;

  CPhonebookRecSet(CDatabase *pcDatabase); 
  virtual ~CPhonebookRecSet(void);
};
