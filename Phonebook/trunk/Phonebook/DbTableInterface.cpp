#include "StdAfx.h"
#include ".\dbtableinterface.h"

CDbTableInterface::CDbTableInterface(void):
m_pszRevNmbFieldName(_T("rev_nmb")), m_pszIdFieldName(_T("Id"))
{
  m_pszColumnsRepresNames.Add(m_pszIdFieldName);
  m_pszColumnsRepresNames.Add(m_pszRevNmbFieldName);   
  m_iUserOffset = m_pszColumnsRepresNames.GetCount();
}

CDbTableInterface::~CDbTableInterface(void)
{
  Close();
}

HANDLE CDbTableInterface::ReadRow(CArray<CString> &a_csRowData,  int iRowNmbr)
{
  Move(iRowNmbr);
  if(IsEOF() || IsBOF())
    return 0;

  CString szFieldData;

  CDBVariant cDBVariant;
  CRowIdent *pcRowId = new CRowIdent();
  
  GetFieldValue(m_pszRevNmbFieldName, cDBVariant);
  pcRowId->m_iRev = cDBVariant.m_iVal;
  GetFieldValue(m_pszIdFieldName, cDBVariant);
  pcRowId->m_iId = cDBVariant.m_iVal;
  pcRowId->m_iNmb = iRowNmbr;

  for(int i = m_iUserOffset; i < GetODBCFieldCount(); i++){
    GetFieldValue(i, szFieldData);
    a_csRowData.Add(szFieldData);
  }

  return (HANDLE)pcRowId; 
}

BOOL CDbTableInterface::WriteRow(CArray<CString> &a_csRowData, HANDLE hRow)
{
  if(!hRow)
    return FALSE;

  CRowIdent *pRowId = static_cast<CRowIdent*>(hRow);
  Move(pRowId->m_iNmb);
  if(IsEOF() || IsBOF() || !CanUpdate())
    return FALSE;

  CDBVariant cDBVariant;
  GetFieldValue(m_pszRevNmbFieldName, cDBVariant);
  if(cDBVariant.m_iVal != pRowId->m_iRev){
    return FALSE;
  }

  GetFieldValue(m_pszIdFieldName, cDBVariant);
  if(cDBVariant.m_iVal != pRowId->m_iId){
    return FALSE;
  }

  if(a_csRowData.GetCount() != (GetODBCFieldCount() - m_iUserOffset)){
    return FALSE;
  }

  CString szTemp;
  szTemp.Format(_T("%d"), pRowId->m_iId);
  a_csRowData.InsertAt(0, szTemp);

  szTemp.Format(_T("%d"), ++pRowId->m_iId);
  a_csRowData.InsertAt(1, szTemp);

  return EditAndUpdateFields(a_csRowData);
}



BOOL CDbTableInterface::GetColumnsRepresNames(CArray<CString> &acsRowData)
{
  for(int i = m_iUserOffset; i < m_pszColumnsRepresNames.GetCount(); i++){
    acsRowData.Add(m_pszColumnsRepresNames[i]);
  } 

  return TRUE;
}

int CDbTableInterface::GetColumnNumberByName(const TCHAR *pszColumnName)
{
  CString csKeyWord(pszColumnName);
  csKeyWord.MakeUpper();
  for(int i = m_iUserOffset; i < m_pszColumnsRepresNames.GetCount(); i++)
  {
    CString csCurrWord = m_pszColumnsRepresNames[i];
    csCurrWord.MakeUpper();
    if(csCurrWord == csKeyWord)
      return i;
  }

  return -1;
}

BOOL CDbTableInterface::LoadDb(const CString &csTableName, const CArray<CString> &a_csFieldsName)
{
  m_szTableRepresName = csTableName;
  m_pszColumnsRepresNames.Append(a_csFieldsName);

  return Open(CRecordset::dynaset);
}

BOOL CDbTableInterface::SortTableByColumn(const TCHAR *pszColumnName, eSortType eType)
{
  int iColumnNmb = GetColumnNumberByName(pszColumnName);
  if(iColumnNmb == -1)
    return FALSE;


  CODBCFieldInfo tFieldInfo;
  GetODBCFieldInfo(iColumnNmb, tFieldInfo);

  Close();
  m_strFilter = _T("");
  m_strSort = tFieldInfo.m_strName;
  m_strSort += _T(" ");

  switch(eType){
    case eNumerically:
    case eAlphabetically:     m_strSort += _T("ASC");  break;
    case eAlphabeticallyRev:  m_strSort += _T("DESC");
    case eNumericallyRev:     m_strSort += _T("DESC"); break;
    default:  return FALSE;
  }

  return Open(CRecordset::dynaset);
}

BOOL  CDbTableInterface::FilterTableByColumnValue(const TCHAR *pszColumnName, const TCHAR *pszValue, eFileterType eFilter)
{
  int iColumnNmb = GetColumnNumberByName(pszColumnName);
  if(iColumnNmb == -1)
    return FALSE;
  

  CODBCFieldInfo tFieldInfo;
  GetODBCFieldInfo(iColumnNmb, tFieldInfo);

  Close();  
  m_strSort = _T("");
  m_strFilter = tFieldInfo.m_strName;

  switch(eFilter){
    case eEquals:             m_strFilter += _T(" = ");  break;
    case eBiggerThan:         m_strFilter += _T(" > ");  break;
    case eBiggerThanOrEqual:  m_strFilter += _T(" >= "); break;
    case eLessThan:           m_strFilter += _T(" < ");  break;
    case eLessThanOrEqual:    m_strFilter += _T(" <= "); break;
    case eContains:           m_strFilter += _T(" LIKE ('%"); break;
    default: return FALSE;
  }

  if((tFieldInfo.m_nSQLType == SQL_VARCHAR) || (tFieldInfo.m_nSQLType == SQL_CHAR))
    m_strFilter += _T("'");

  m_strFilter += pszValue;

  if(eFilter == eContains)
  {
    if((tFieldInfo.m_nSQLType == SQL_VARCHAR) || (tFieldInfo.m_nSQLType == SQL_CHAR))
      m_strFilter += _T("%)'");
    else
      return FALSE;
  }else if((tFieldInfo.m_nSQLType == SQL_VARCHAR) || (tFieldInfo.m_nSQLType == SQL_CHAR))
  {
    m_strFilter += _T("'");
  }

  return Open(CRecordset::dynaset);
}

BOOL  CDbTableInterface::DeleteRow(int iRowNumber)
{
  Move(iRowNumber);
  if(IsEOF() || IsBOF() || !CanUpdate())
    return FALSE;

  Delete();
  MoveFirst();

  return TRUE;
}

BOOL  CDbTableInterface::IsColumnValuePresent(const TCHAR *pszColumnName, const TCHAR *pszValue, eFileterType eFilter)
{
#include "afxdb.h"
  FilterTableByColumnValue(pszColumnName, pszValue, eFilter);
  try{
    MoveFirst();
  }catch(CDBException*){
    return FALSE;
  }
  return TRUE;
}

void CDbTableInterface::ReloadCompleteTable()
{
  Close();
  m_strFilter = _T("");
  m_strSort = _T("");
  Open(CRecordset::dynaset);
}