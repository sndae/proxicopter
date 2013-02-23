// Cities.h : Implementation of the CCities class



// CCities implementation

// code generated on Tuesday, February 19, 2013, 1:38 PM

#include "stdafx.h"
#include "Cities.h"


IMPLEMENT_DYNAMIC(CCities, CRecordset)

CCities::CCities(CDatabase* pdb, const TCHAR *pszDBPath)
	: CDbTableInterface(pszDBPath), CRecordset(pdb)
{
	m_id = 0;
	m_rev_nmb = 0;
	m_Code = L"";
	m_Name = L"";
	m_Area = L"";
	m_nFields = 5;
	m_nDefaultType = dynaset;

  CArray<CString> a_szFieldsNames;
  a_szFieldsNames.InsertAt(eColCode, _T("Код"));
  a_szFieldsNames.InsertAt(eColName, _T("Град"));
  a_szFieldsNames.InsertAt(eColArea, _T("Област"));

  LoadDb(_T("Градове"), a_szFieldsNames);
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CCities::GetDefaultConnect()
{
	return _T("DSN=SQLExpress;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=PROXIMUS-PC;DATABASE=phonebook");}

CString CCities::GetDefaultSQL()
{
  TCHAR *pszDBPath = GetDBPath();
  if(pszDBPath)
  {
    return CString(pszDBPath) + _T(".cities");
  }
	return _T("[Cities$]");
}

void CCities::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Int(pFX, _T("[id]"), m_id);
	RFX_Int(pFX, _T("[rev_nmb]"), m_rev_nmb);
	RFX_Text(pFX, _T("[code]"), m_Code);
	RFX_Text(pFX, _T("[name]"), m_Name);
	RFX_Text(pFX, _T("[area]"), m_Area);
 
}
/////////////////////////////////////////////////////////////////////////////
// CCities diagnostics

#ifdef _DEBUG
void CCities::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCities::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

BOOL CCities::WriteRow(CArray<CString> &a_csRowData, HANDLE hRow)
{
  if(!hRow)
    return FALSE;

  CRowIdent *pRowId = static_cast<CRowIdent*>(hRow);
  Close();
  Open(CRecordset::dynaset);
  Move(pRowId->m_iNmb);
  if(IsEOF() || IsBOF() || !CanUpdate())
    return FALSE;

  if(m_id != pRowId->m_iId)
    return FALSE;
  else if(m_rev_nmb != pRowId->m_iRev)
    return FALSE;

  if(a_csRowData.GetCount() != m_nFields - m_iUserOffset)
    return FALSE;

  Edit();

	m_id =      pRowId->m_iId;
	m_rev_nmb = ++pRowId->m_iRev;
	m_Code    = a_csRowData[eColCode];
	m_Name    = a_csRowData[eColName];
	m_Area    = a_csRowData[eColArea];  
  
  Update();

  return TRUE;
}

HANDLE   CCities::ReadRow(CArray<CString> &a_csRowData,  int iRowNmbr)
{
  Close();
  Open(CRecordset::dynaset);

  try{
    Move(iRowNmbr);
  }catch(CDBException *){
    return 0;
  }
  if(IsEOF() || IsBOF())
  {
    return 0;
  }

  CDBVariant cDBVariant;
  CRowIdent *pcRowId = new CRowIdent();
  
  pcRowId->m_iRev = m_rev_nmb;
  pcRowId->m_iId = m_id;
  pcRowId->m_iNmb = iRowNmbr;

	a_csRowData.Add(m_Code);
	a_csRowData.Add(m_Name);
	a_csRowData.Add(m_Area);

  return (HANDLE)pcRowId; 
}

BOOL  CCities::AddRow(CArray<CString> &a_csRowData)
{
  int iIndex = 0;
  try{
    MoveLast();
    iIndex = m_id;
  }
  catch(CDBException*){
    iIndex = 0;
  }
  
  if( !CanAppend() ||
      IsColumnValuePresent(eColCode, a_csRowData[eColCode]) ||
      IsColumnValuePresent(eColName, a_csRowData[eColCode]) )
  {
    return FALSE;
  }
  
  AddNew();
	m_id = iIndex + 1;
	m_rev_nmb = 0;
	m_Code = a_csRowData[eColCode];
	m_Name = a_csRowData[eColName];
	m_Area = a_csRowData[eColArea];  
  
  if(!Update())
    return FALSE;

  ReloadCompleteTable();
  return TRUE;
}

int CCities::ReadIdentifierByRowNumber(int iRowNmb)
{
  Move(iRowNmb);
  if(IsEOF() || IsBOF())
  {
    return 0;
  }
  return m_id;
}




