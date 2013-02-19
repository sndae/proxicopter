#pragma once
#include "afxdb.h"
#include "afxtempl.h"

class CPhonebookRecSet :
  virtual public CRecordset
{
#define STR_MAX_LEN  64
protected:
  int m_iRowAttrCntr;
  struct CDispnameToAttrname{
    TCHAR m_szDispName[STR_MAX_LEN];
    TCHAR m_szAttrName[STR_MAX_LEN];  
    CDispnameToAttrname(){};
    CDispnameToAttrname(TCHAR *pszDispName, TCHAR *pszAttrName)
    {
      if(pszDispName) _tcscpy(m_szDispName, pszDispName);
      if(pszAttrName) _tcscpy(m_szAttrName, pszAttrName);
    };
  };
  struct CRowIdent{
    int m_iRev;
    int m_iNmb;
    int m_iId;
    CRowIdent(){};
    CRowIdent(int iNmb, int iRev, int iId):m_iNmb(iNmb), m_iRev(iRev), m_iId(iId){};
  };
  CDispnameToAttrname m_cTableName;
private:
  CArray<CDispnameToAttrname> m_cAttrList;
  int m_iUserOffset;
  int m_iCurrRowRevNumber;
  void UpdateCurrRowRevNumber();
public:
  BOOL LoadDB(CDispnameToAttrname tTableName, CDispnameToAttrname *patAttrList = 0, int fFlags = 0);
  virtual TCHAR *GetTableDispName() {return m_cTableName.m_szDispName;} ;

  virtual BOOL   MoveToFirstRow();
  virtual BOOL   MoveToNextRow();
  virtual BOOL   MoveToPrevRow();
  virtual BOOL   MoveToRow(int iNmbr);
  virtual BOOL   GetRowFirstAtrrVal(TCHAR *pszText, TCHAR **pszDispName = 0);
  virtual BOOL   GetRowNextAtrrVal(TCHAR *pszText,  TCHAR **pszDispName = 0);
  virtual BOOL   GetRowPrevAtrrVal(TCHAR *pszText,  TCHAR **pszDispName = 0);

  virtual BOOL   WriteRow(CArray<CString> &a_csRowData, HANDLE hRow);
  virtual HANDLE ReadRow(CArray<CString> &a_csRowData, int iRowNmbr);
  virtual BOOL   ReadRowAttributesNames(CArray<CString> &a_csRowData);
  CPhonebookRecSet(CDatabase *pcDatabase); 
  virtual ~CPhonebookRecSet(void);
};
