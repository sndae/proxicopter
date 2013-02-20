#pragma once
#include "afxdb.h"
#include "afxtempl.h"

class CDbTableInterface :
  virtual private  CRecordset
{
  int m_iUserOffset;
  CString m_csTableRepresName;
  CString m_csDBPath;
  CArray<CString> m_pszColumnsRepresNames;
  const TCHAR* m_pszIdFieldName;
  const TCHAR* m_pszRevNmbFieldName;
protected:
  struct CRowIdent{
    int m_iRev;
    int m_iNmb;
    int m_iId;
    CRowIdent(){};
    CRowIdent(int iNmb, int iRev, int iId):m_iNmb(iNmb), m_iRev(iRev), m_iId(iId){};
  };
  virtual BOOL     EditAndUpdateFields(CArray<CString> &a_csRowData) = 0;
  virtual BOOL     LoadDb(const CString &csTableName, const CArray<CString> &a_csFieldsName);
  virtual int      GetColumnNumberByName(const TCHAR *pszColumnName);
  virtual void     ReloadCompleteTable();
public:
  enum    eSortType {eAlphabetically, eAlphabeticallyRev, eNumerically, eNumericallyRev};
  enum    eFileterType {eEquals, eBiggerThan, eBiggerThanOrEqual, eLessThan, eLessThanOrEqual, eContains};
  
  virtual BOOL     SortTableByColumn(const TCHAR *pszColumnName, eSortType eType);
  virtual BOOL     FilterTableByColumnValue(const TCHAR *pszColumnName, const TCHAR *pszValue, eFileterType eFilter);
  virtual HANDLE   ReadRow(CArray<CString> &a_csRowData,  int iRowNmbr);
  virtual BOOL     DeleteRow(int iRowNumber);
  virtual BOOL     AddRow(CArray<CString> &a_csRowData) = 0;
  virtual BOOL     WriteRow(CArray<CString> &a_csRowData, HANDLE hRow) = 0;
  virtual BOOL     GetColumnsRepresNames(CArray<CString> &a_csRowData);
  virtual TCHAR*   GetColumnRepresName(int iRow)  {return m_pszColumnsRepresNames[m_iUserOffset + iRow].GetBuffer();};
  virtual CString* GetTableRepresName(){ return &m_csTableRepresName;};
  virtual TCHAR*   GetDBPath();
  virtual BOOL     IsColumnValuePresent(const TCHAR *pszColumnName, const TCHAR *pszValue, eFileterType eFilter=eEquals);
  CDbTableInterface(const TCHAR *pszDBPath = 0);

  ~CDbTableInterface(void);
};
