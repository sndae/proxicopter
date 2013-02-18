#pragma once
#include "afxdb.h"
#include "afxtempl.h"

class CPhonebookRecSet :
  private CRecordset
{
protected:
  int m_iRowAttrCntr;
  struct CDispnameToAttrname{
    TCHAR m_szDispName[64];
    TCHAR m_szAttrName[64];  
    CDispnameToAttrname(){};
    CDispnameToAttrname(TCHAR *pszDispName, TCHAR *pszAttrName)
    {
      if(pszDispName) _tcscpy_s(m_szDispName, pszDispName);
      if(pszAttrName) _tcscpy_s(m_szAttrName, pszAttrName);
    };
  };
  CDispnameToAttrname m_cTableName;
private:
  CArray<CDispnameToAttrname> m_cAttrList;
  CDatabase *m_pcDatabase;
  int m_iUserOffset;
  int m_iCurrRowRevNumber;
  void UpdateCurrRowRevNumber();
public:
  BOOL LoadDB(CDispnameToAttrname tTableName, CDispnameToAttrname *patAttrList = 0, int fFlags = 0);
  virtual BOOL   MoveToFirstRow();
  virtual BOOL   MoveToNextRow();
  virtual BOOL   MoveToPrevRow();
  virtual BOOL   GetRowFirstAtrrVal(CDBVariant &cDBVariant, TCHAR **pszDispName = 0);
  virtual BOOL   GetRowNextAtrrVal(CDBVariant &cDBVariant,  TCHAR **pszDispName = 0);
  virtual BOOL   GetRowPrevAtrrVal(CDBVariant &cDBVariant,  TCHAR **pszDispName = 0);
  virtual TCHAR *GetTableDispName() {return m_cTableName.m_szDispName;} ;

  CPhonebookRecSet(CDatabase *pcDatabase); 
  virtual ~CPhonebookRecSet(void);
};
