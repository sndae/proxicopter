// SubscribersPhoneNumbers.h : Implementation of the CSubscribersPhoneNumbers class



// CSubscribersPhoneNumbers implementation

// code generated on 20 февруари 2013 г., 23:56 ч.

#include "stdafx.h"
#include "SubscribersPhoneNumbers.h"
IMPLEMENT_DYNAMIC(CSubscribersPhoneNumbers, CRecordset)

CSubscribersPhoneNumbers::CSubscribersPhoneNumbers(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_id = 0;
	m_rev_nmb = 0;
	m_subscriber_id = 0;
	m_phone_id = 0;
	m_phone_number = L"";
	m_nFields = 5;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CSubscribersPhoneNumbers::GetDefaultConnect()
{
	return _T("DSN=SQLExpress;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=PROXIMUS-PC;DATABASE=phonebook");
}

CString CSubscribersPhoneNumbers::GetDefaultSQL()
{
	return _T("[dbo].[subscriber_phone_numbers]");
}

void CSubscribersPhoneNumbers::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[id]"), m_id);
	RFX_Long(pFX, _T("[rev_nmb]"), m_rev_nmb);
	RFX_Long(pFX, _T("[subscriber_id]"), m_subscriber_id);
	RFX_Long(pFX, _T("[phone_id]"), m_phone_id);
	RFX_Text(pFX, _T("[phone_number]"), m_phone_number);

}
/////////////////////////////////////////////////////////////////////////////
// CSubscribersPhoneNumbers diagnostics

#ifdef _DEBUG
void CSubscribersPhoneNumbers::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSubscribersPhoneNumbers::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


