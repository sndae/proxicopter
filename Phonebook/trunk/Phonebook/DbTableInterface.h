#pragma once
#include "afxdb.h"
#include "afxtempl.h"

class CDbTableInterface
{
public:
  virtual ~CDbTableInterface(void){};
  enum    eFileterType {eEquals, eBiggerThan, eBiggerThanOrEqual, eLessThan, eLessThanOrEqual, eContains};  
  enum    eSortType {eAsc = 1, eDesc};
  /* pure virtual functions */
  virtual BOOL     SortTableByColumn(int iColumnNmb, eSortType eType) = 0;
  virtual BOOL     FilterTableByColumnValue(int iColNmb, const TCHAR *pszValue, eFileterType eFilter) = 0;
  virtual BOOL     DeleteRow(HANDLE hRow) = 0;
  virtual BOOL     GetColumnsRepresNames(CArray<CString> &a_csRowData) = 0;
  virtual TCHAR*   GetColumnRepresName(int iColnumb) = 0;
  virtual int      GetColumnsNumber() = 0;
  virtual TCHAR*   GetTableRepresName() = 0;
  virtual TCHAR*   GetDBPath() = 0;
  virtual BOOL     IsColumnValuePresent(int iColNmb, const TCHAR *pszValue, eFileterType eFilter=eEquals) = 0;
  virtual BOOL     ReadRowByIdentifier(int iId, CArray<CString> &a_csRowData) = 0;
  virtual BOOL     AddRow(CArray<CString> &a_csRowData) = 0;
  virtual HANDLE   ReadRow(CArray<CString> &a_csRowData,  int iRowNmbr) = 0;
  virtual BOOL     WriteRow(CArray<CString> &a_csRowData, HANDLE hRow) = 0;
  virtual int      ReadIdentifierByRowNumber(int iRowNmb) = 0;
};
