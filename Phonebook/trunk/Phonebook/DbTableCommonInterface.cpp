#include "StdAfx.h"
#include ".\dbtablecommoninterface.h"


CDbTableCommonInterface::CDbTableCommonInterface(const TCHAR *pszDBPath):
m_pszRevNmbFieldName(_T("rev_nmb")), m_pszIdFieldName(_T("Id"))
{
  /* Read DB path, if set */
  if(pszDBPath)
    m_csDBPath = pszDBPath;

  /* Insert identifier and revision number names at the beginning ot the representation names array */
  m_acsColumnsRepresNames.InsertAt(0, m_pszIdFieldName);
  m_acsColumnsRepresNames.InsertAt(1, m_pszRevNmbFieldName);   
  m_iUserOffset = m_acsColumnsRepresNames.GetCount();
}

BOOL CDbTableCommonInterface::GetColumnsRepresNames(CArray<CString> &acsRowData)
{
  /* return an array of user representation column names */
  for(int i = m_iUserOffset; i < m_acsColumnsRepresNames.GetCount(); i++)
  {
    acsRowData.Add(m_acsColumnsRepresNames[i]);
  } 

  return TRUE;
}

BOOL CDbTableCommonInterface::LoadDb(const CString &csTableName, const CArray<CString> &a_csFieldsName)
{
  /* Append user representation names to the columns to the existing ones*/
  m_csTableRepresName = csTableName;
  m_acsColumnsRepresNames.Append(a_csFieldsName);

  /* load database in dynamic mode */
  return Open(CRecordset::dynaset);
}

BOOL CDbTableCommonInterface::SortTableByColumn(int iColumnNmb, eSortType eType)
{
  CODBCFieldInfo tFieldInfo;
  GetODBCFieldInfo(iColumnNmb + m_iUserOffset, tFieldInfo);

  Close();
  m_strFilter = _T("");
  m_strSort = tFieldInfo.m_strName;
  m_strSort += _T(" ");

  switch(eType)
  {
    case eAsc:  m_strSort += _T("ASC");  break;
    case eDesc: m_strSort += _T("DESC"); break;
    default:  return FALSE;
  }

  return Open(CRecordset::dynaset);
}

BOOL  CDbTableCommonInterface::FilterTableByColumnValue(int iColumnNmb, const TCHAR *pszValue, eFileterType eFilter)
{
#define SQL_VARCHAR2 (-9)
  CODBCFieldInfo tFieldInfo;
  GetODBCFieldInfo(iColumnNmb + m_iUserOffset, tFieldInfo);

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
    default: ASSERT(TRUE);
  }

  if((tFieldInfo.m_nSQLType == SQL_VARCHAR) || (tFieldInfo.m_nSQLType == SQL_VARCHAR2))
    m_strFilter += _T("'");

  m_strFilter += pszValue;

  if(eFilter == eContains)
  {
    if((tFieldInfo.m_nSQLType == SQL_VARCHAR) || (tFieldInfo.m_nSQLType == SQL_VARCHAR2))
      m_strFilter += _T("%)'");
    else
      return FALSE;
  }
  else if((tFieldInfo.m_nSQLType == SQL_VARCHAR) || (tFieldInfo.m_nSQLType == SQL_VARCHAR2))
  {
    m_strFilter += _T("'");
  }

  return Open(CRecordset::dynaset);
}

BOOL  CDbTableCommonInterface::DeleteRow(HANDLE hRow)
{
  if(!hRow)
    return FALSE;
  
  CRowIdent *pRow = static_cast<CRowIdent*>(hRow);
  ReloadCompleteTable();
  Move(pRow->m_iNmb);
  if(IsEOF() || IsBOF() || !CanUpdate())
    return FALSE;

  Delete();
  MoveFirst();

  return TRUE;
}

BOOL  CDbTableCommonInterface::IsColumnValuePresent(int iColNmb, const TCHAR *pszValue, eFileterType eFilter)
{
  if(!pszValue)
    return FALSE;

  FilterTableByColumnValue(iColNmb, pszValue, eFilter);
  
  if(!IsBOF()){
    MoveFirst();
  }else{
    ReloadCompleteTable();  
    return FALSE;
  }

  return TRUE;
}

void CDbTableCommonInterface::ReloadCompleteTable()
{
  Close();
  m_strFilter = _T("");
  m_strSort = _T("");
  Open(CRecordset::dynaset);
}

TCHAR* CDbTableCommonInterface::GetDBPath()
{
  if(m_csDBPath.GetLength() != 0)
    return m_csDBPath.GetBuffer();
  
  return 0;
}

BOOL CDbTableCommonInterface::ReadRowByIdentifier(int iId, CArray<CString> &a_csRowData)
{
  Close(); 
  TCHAR szStr[64];
  _itot(iId, szStr, 10);
  m_strSort = _T("");
  m_strFilter += m_pszIdFieldName;
  m_strFilter += _T(" = ");
  m_strFilter += szStr;
  Open(CRecordset::dynaset);
  if(IsBOF())
    return FALSE;

  HANDLE hRow = ReadRow(a_csRowData, 0);
  delete hRow;

  return TRUE;
}
