// Cities.h : Implementation of the CCities class



// CCities implementation

// code generated on Tuesday, February 19, 2013, 1:38 PM

#include "stdafx.h"
#include "Cities.h"


IMPLEMENT_DYNAMIC(CCities, CRecordset)

CCities::CCities(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_Id = 0;
	m_rev_nmb = 0;
	m_Code = 0;
	m_Name = L"";
	m_Area = L"";
	m_nFields = 5;
	m_nDefaultType = dynaset;

  CArray<CString> a_szFieldsNames;
  a_szFieldsNames.Add(_T("Kod"));
  a_szFieldsNames.Add(_T("Grad"));
  a_szFieldsNames.Add(_T("Oblast"));

  LoadDb(_T("Gradove"), a_szFieldsNames);
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CCities::GetDefaultConnect()
{
	return _T("DSN=Excel Files;DBQ=C:\\PROJECTS\\Phonebook\\phonebook.xls;DefaultDir=C:\\PROJECTS\\Phonebook;DriverId=790;MaxBufferSize=2048;PageTimeout=5;");
}

CString CCities::GetDefaultSQL()
{
	return _T("[Cities$]");
}

void CCities::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Int(pFX, _T("[id]"), m_Id);
	RFX_Int(pFX, _T("[rev_nmb]"), m_rev_nmb);
	RFX_Int(pFX, _T("[code]"), m_Code);
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

BOOL CCities::EditAndUpdateFields(CArray<CString> &a_csRowData)
{
  if(a_csRowData.GetCount() != m_nDefaultType)
    return FALSE;

  Edit();
	m_Id =      _ttoi(a_csRowData[0]);
	m_rev_nmb = _ttoi(a_csRowData[1]);
	m_Code    = _ttoi(a_csRowData[2]);
	m_Name    = a_csRowData[3];
	m_Area    = a_csRowData[4];  
  Update();

  return TRUE;
}

BOOL CCities::WriteRow(CArray<CString> &a_csRowData, HANDLE hRow)
{
  if(!hRow)
    return FALSE;

  CRowIdent *pRowId = static_cast<CRowIdent*>(hRow);
  Move(pRowId->m_iNmb);
  if(IsEOF() || IsBOF() || !CanUpdate())
    return FALSE;

  if(m_Id != pRowId->m_iId)
    return FALSE;
  else if(m_rev_nmb != pRowId->m_iRev)
    return FALSE;
  else if(a_csRowData.GetCount() != m_nFields)
    return FALSE;

  CString szTemp;
  szTemp.Format(_T("%d"), pRowId->m_iId);
  a_csRowData.InsertAt(0, szTemp);

  szTemp.Format(_T("%d"), ++pRowId->m_iId);
  a_csRowData.InsertAt(1, szTemp);

  return EditAndUpdateFields(a_csRowData);
}

HANDLE   CCities::ReadRow(CArray<CString> &a_csRowData,  int iRowNmbr)
{
  Move(iRowNmbr);
  if(IsEOF() || IsBOF())
  {
    return 0;
  }

  CDBVariant cDBVariant;
  CRowIdent *pcRowId = new CRowIdent();
  
  pcRowId->m_iRev = m_rev_nmb;
  pcRowId->m_iId = m_Id;
  pcRowId->m_iNmb = iRowNmbr;
  
  CString szFieldData;
  szFieldData.Format(_T("%d"), m_Code); 
	a_csRowData.Add(szFieldData);
	a_csRowData.Add(m_Name);
	a_csRowData.Add(m_Area);

  return (HANDLE)pcRowId; 
}

BOOL  CCities::AddRow(CArray<CString> &a_csRowData)
{
  ReloadCompleteTable();
  MoveLast();
  int iIndex = m_Id;
  if( !CanAppend() ||
      IsColumnValuePresent(GetColumnRepresName(0), a_csRowData[0]) ||
      IsColumnValuePresent(GetColumnRepresName(1), a_csRowData[1]) )
  {
    return FALSE;
  }
  
  AddNew();
	m_Id = iIndex + 1;
	m_rev_nmb = 0;
	m_Code = _ttoi(a_csRowData[0]);
	m_Name = a_csRowData[1];
	m_Area = a_csRowData[2];  
  
  return Update();
}
#endif //_DEBUG


