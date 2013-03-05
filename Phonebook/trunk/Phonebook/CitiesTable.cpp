// CitiesTable.cpp : implementation of the CCitiesTable class
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "CitiesTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCitiesTable implementation

// code generated on 05 март 2013 г., 19:08 ч.

IMPLEMENT_DYNAMIC(CCitiesTable, CRecordset)

CCitiesTable::CCitiesTable(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_REV_NUMB = 0;
	m_CODE = L"";
	m_NAME = L"";
	m_AREA = L"";
	m_nFields = 5;
	m_nDefaultType = dynaset;
}
#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CCitiesTable::GetDefaultConnect()
{
	return _T("DSN=SQLExpress;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=PROXIMUS-PC;DATABASE=phonebook");
}

CString CCitiesTable::GetDefaultSQL()
{
	return _T("[dbo].[CITIES]");
}

void CCitiesTable::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[REV_NUMB]"), m_REV_NUMB);
	RFX_Text(pFX, _T("[CODE]"), m_CODE);
	RFX_Text(pFX, _T("[NAME]"), m_NAME);
	RFX_Text(pFX, _T("[AREA]"), m_AREA);

}
/////////////////////////////////////////////////////////////////////////////
// CCitiesTable diagnostics

#ifdef _DEBUG
void CCitiesTable::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCitiesTable::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

