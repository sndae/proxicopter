// PhoneTypesTable.h : Implementation of the CPhoneTypesTable class



// CPhoneTypesTable implementation

// code generated on 07 март 2013 г., 20:47 ч.

#include "stdafx.h"
#include "PhoneTypesTable.h"
IMPLEMENT_DYNAMIC(CPhoneTypesTable, CRecordset)

CPhoneTypesTable::CPhoneTypesTable(CDatabase* pdb)
	: CRecordset(pdb)
{
  m_ID = 0;
  m_REV_NUMB = 0;
  m_CODE = 0;
  m_PHONE_TYPE = L"";
  m_nFields = 4;
  m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CPhoneTypesTable::GetDefaultConnect()
{
  return _T("DSN=SQLExpress;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=PROXIMUS-PC;DATABASE=phonebook");
}

CString CPhoneTypesTable::GetDefaultSQL()
{
  return _T("[dbo].[PHONE_TYPES]");
}

void CPhoneTypesTable::DoFieldExchange(CFieldExchange* pFX)
{
  pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
  RFX_Long(pFX, _T("[ID]"), m_ID);
  RFX_Long(pFX, _T("[REV_NUMB]"), m_REV_NUMB);
  RFX_Long(pFX, _T("[CODE]"), m_CODE);
  RFX_Text(pFX, _T("[PHONE_TYPE]"), m_PHONE_TYPE);
}
/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesTable diagnostics

#ifdef _DEBUG
void CPhoneTypesTable::AssertValid() const
{
  CRecordset::AssertValid();
}

void CPhoneTypesTable::Dump(CDumpContext& dc) const
{
  CRecordset::Dump(dc);
}
#endif //_DEBUG


