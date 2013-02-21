#pragma once
#include "afxdb.h"
#include "afxtempl.h"

class CDbTableInterface :
  virtual private  CRecordset
{;
  CString m_csTableRepresName;
  CString m_csDBPath;
  CArray<CString> m_pszColumnsRepresNames;
  const TCHAR* m_pszIdFieldName;
  const TCHAR* m_pszRevNmbFieldName;
protected:
  int m_iUserOffset; 
  /* Row identification class */
  struct CRowIdent{
    int m_iRev;
    int m_iNmb;
    int m_iId;
    CRowIdent(){};
    CRowIdent(int iNmb, int iRev, int iId):m_iNmb(iNmb), m_iRev(iRev), m_iId(iId){};
  };

  virtual BOOL     LoadDb(const CString &csTableName, const CArray<CString> &a_csFieldsName);
  virtual int      GetColumnNumberByRepresName(const TCHAR *pszColumnName);
  virtual void     ReloadCompleteTable();
public:
  using   CRecordset::operator new;
  using   CRecordset::operator delete;
  enum    eSortType {eAlphabetically, eAlphabeticallyRev, eNumerically, eNumericallyRev};
  enum    eFileterType {eEquals, eBiggerThan, eBiggerThanOrEqual, eLessThan, eLessThanOrEqual, eContains};
  
  /*Constructor and deconstructor */
  CDbTableInterface(const TCHAR *pszDBPath = 0);
  ~CDbTableInterface(void);

  /* Interface functions */
  virtual BOOL     SortTableByColumn(const TCHAR *pszColumnName, eSortType eType);
  virtual BOOL     FilterTableByColumnValue(const TCHAR *pszColumnName, const TCHAR *pszValue, eFileterType eFilter);
  virtual BOOL     DeleteRow(int iRowNumber);  
  virtual BOOL     GetColumnsRepresNames(CArray<CString> &a_csRowData);
  virtual TCHAR*   GetColumnRepresName(int iColnumb)  {return m_pszColumnsRepresNames[m_iUserOffset + iColnumb].GetBuffer();};
  virtual TCHAR*   GetTableRepresName(){ return m_csTableRepresName.GetBuffer();};
  virtual TCHAR*   GetDBPath();
  virtual BOOL     IsColumnValuePresent(const TCHAR *pszColumnName, const TCHAR *pszValue, eFileterType eFilter=eEquals);
  virtual BOOL     ReadRowByIdentifier(int iId, CArray<CString> &a_csRowData);
  virtual int      ReadIdentifierByRowNumber(int iRowNmb);
  /* pure virtual functions */
  virtual BOOL     AddRow(CArray<CString> &a_csRowData) = 0;
  virtual HANDLE   ReadRow(CArray<CString> &a_csRowData,  int iRowNmbr) = 0;
  virtual BOOL     WriteRow(CArray<CString> &a_csRowData, HANDLE hRow) = 0;

};
