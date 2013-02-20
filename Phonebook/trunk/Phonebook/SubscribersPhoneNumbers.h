// SubscribersPhoneNumbers.h : Declaration of the CSubscribersPhoneNumbers

#pragma once

// code generated on 20 февруари 2013 г., 23:56 ч.

class CSubscribersPhoneNumbers : public CRecordset
{
public:
	CSubscribersPhoneNumbers(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSubscribersPhoneNumbers)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_id;
	long	m_rev_nmb;
	long	m_subscriber_id;
	long	m_phone_id;
	CStringW	m_phone_number;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


