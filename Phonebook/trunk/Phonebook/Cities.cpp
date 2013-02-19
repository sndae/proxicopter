// Cities.h : Implementation of the CCities class



// CCities implementation

// code generated on Tuesday, February 19, 2013, 1:38 PM

#include "stdafx.h"
#include "Cities.h"


IMPLEMENT_DYNAMIC(CCities, CRecordset)

CCities::CCities(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_Id = 0.0;
	m_rev_nmb = 0.0;
	m_Code = 0.0;
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
	RFX_Double(pFX, _T("[Id]"), m_Id);
	RFX_Double(pFX, _T("[rev_nmb]"), m_rev_nmb);
	RFX_Double(pFX, _T("[Code]"), m_Code);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Area]"), m_Area);

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

void CCities::EditAndUpdateFields(CArray<CString> &a_csRowData)
{

}

#endif //_DEBUG


