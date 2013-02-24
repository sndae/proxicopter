#pragma once
#include "afxdb.h"
#include "afxtempl.h"

class CDbTableInterface :
  virtual private  CRecordset
{
  CString m_csTableRepresName;  //Table representation name
  CString m_csDBPath;           // Path to the database
  CArray<CString> m_acsColumnsRepresNames;  // Array of columns representation names
  const TCHAR* m_pszIdFieldName;     // Name of the identifier name
  const TCHAR* m_pszRevNmbFieldName; // Name of the revision number name
protected:
  int m_iUserOffset; // offset of the user columns (identifier + revision = 2)
  /* Row identification class */
  struct CRowIdent
  {
    int m_iRev;
    int m_iNmb;
    int m_iId;
    CRowIdent(){};
    CRowIdent(int iNmb, int iRev, int iId):m_iNmb(iNmb), m_iRev(iRev), m_iId(iId){};
  };
  virtual BOOL     LoadDb(const CString &csTableName, const CArray<CString> &a_csFieldsName);
  virtual void     ReloadCompleteTable();
public:
  using   CRecordset::operator new;
  using   CRecordset::operator delete;
  enum    eSortType {eAsc = 1, eDesc};
  enum    eFileterType {eEquals, eBiggerThan, eBiggerThanOrEqual, eLessThan, eLessThanOrEqual, eContains};
  
  /*Constructor and deconstructor */
  CDbTableInterface(const TCHAR *pszDBPath = 0);
  ~CDbTableInterface(void);

  /* Interface functions */
  virtual BOOL     SortTableByColumn(int iColumnNmb, eSortType eType);
  virtual BOOL     FilterTableByColumnValue(int iColNmb, const TCHAR *pszValue, eFileterType eFilter);
  virtual BOOL     DeleteRow(HANDLE hRow);  
  virtual BOOL     GetColumnsRepresNames(CArray<CString> &a_csRowData);
  virtual TCHAR*   GetColumnRepresName(int iColnumb)  {return m_acsColumnsRepresNames[m_iUserOffset + iColnumb].GetBuffer();};
  virtual int      GetColumnsNumber(){return m_acsColumnsRepresNames.GetCount() - m_iUserOffset;};
  virtual TCHAR*   GetTableRepresName(){ return m_csTableRepresName.GetBuffer();};
  virtual TCHAR*   GetDBPath();
  virtual BOOL     IsColumnValuePresent(int iColNmb, const TCHAR *pszValue, eFileterType eFilter=eEquals);
  virtual BOOL     ReadRowByIdentifier(int iId, CArray<CString> &a_csRowData);
  /* pure virtual functions */
  virtual BOOL     AddRow(CArray<CString> &a_csRowData) = 0;
  virtual HANDLE   ReadRow(CArray<CString> &a_csRowData,  int iRowNmbr) = 0;
  virtual BOOL     WriteRow(CArray<CString> &a_csRowData, HANDLE hRow) = 0;
  virtual int      ReadIdentifierByRowNumber(int iRowNmb) = 0;
};
