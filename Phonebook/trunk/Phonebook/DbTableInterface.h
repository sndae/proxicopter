#pragma once
#include "afxdb.h"
#include "afxtempl.h"

class CDbTableInterface :
  virtual private  CRecordset
{
  struct CRowIdent{
    int m_iRev;
    int m_iNmb;
    int m_iId;
    CRowIdent(){};
    CRowIdent(int iNmb, int iRev, int iId):m_iNmb(iNmb), m_iRev(iRev), m_iId(iId){};
  };
  int m_iUserOffset;
  CString m_szTableName;
  CArray<CString> m_aszFieldsNames;
protected:
  virtual void     EditAndUpdateFields(CArray<CString> &a_csRowData) = 0;
public:
  virtual BOOL     WriteRow(CArray<CString> &a_csRowData, HANDLE hRow);
  virtual HANDLE   ReadRow(CArray<CString> &a_csRowData,  int iRowNmbr);
  virtual BOOL     ReadRowFieldNames(CArray<CString> &a_csRowData);
  virtual BOOL     LoadDb(const CString &csTableName, const CArray<CString> &a_csFieldsName);
  virtual CString* GetTableDispName(){ return &m_szTableName;};
  CDbTableInterface(void)
  {
    m_aszFieldsNames.Add(_T("Id"));
    m_aszFieldsNames.Add(_T("rev_nmb"));   
    m_iUserOffset = m_aszFieldsNames.GetCount();
  }

  ~CDbTableInterface(void);
};
