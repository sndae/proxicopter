// SubscriberPhoneNumbersTable.h: interface of the CSubscriberPhoneNumbersTable class
//


#pragma once


// code generated on 05 март 2013 г., 19:08 ч.
#include "SubscriberPhoneNumbers.h"
#include "SubscribersTable.h"
#include "PhoneTypesTable.h"

class CSubscriberPhoneNumbersTable : private CRecordset
{
public:
	CSubscriberPhoneNumbersTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSubscriberPhoneNumbersTable)

	//Enumerators
public:
	// Изброяване имената на полетата и техните номера 
	enum eColumn{cColIdx = 0, eColRevNumb, eColSubscrCode, eColPhoneCode, eColPhoneNumber, eCOL_NUMB};


// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.	If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long m_nID;
	long m_REV_NUMB;
	long m_SUBSCRIBER_ID;
	long m_PHONE_ID;
	CStringW m_PHONE_NUMB ;

	// Флаг разрешаващ търсенето на DSN:SQLEXPRESS 
	BOOL m_bSQLEn;
		
	CSubscribersTable m_oSubscribersTable;
	CPhoneTypesTable  m_oPhoneTypesTable;

// Overrides
	// Wizard generated virtual function overrides
public:
	virtual CString GetDefaultConnect(); // Default connection string
	virtual CString GetDefaultSQL();     // default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX); // RFX support

	BOOL SelectAll(CSubscriberPhoneNumbersArray &oSubscriberPhoneNumbersArray);
	BOOL SelectWhereId(const int iId, CSubscriberPhoneNumbers &oPhoneNumb);
	BOOL UpdateWhereId(const int iId, const CSubscriberPhoneNumbers &oPhoneNumb);
	BOOL Insert(const CSubscriberPhoneNumbers &oPhoneNumb);
	BOOL DeleteWhereId(const int iId);
	BOOL SortByColumn(const eColumn eCol, const BOOL bAsc = TRUE, const BOOL bResetFilter = TRUE);
	BOOL SelectByContent(const CSubscriberPhoneNumbers &oPhoneNumb, BOOL bClearFilter = TRUE);
	BOOL SelectAllSubscribersCodes(CSubscribersArray &oSubscribersArray);
	BOOL SelectAllPhoneTypesCodes(CPhoneTypesArray &oPhoneTypesArray);

private:
	void DoExchangeFromDatabaseData(CSubscriberPhoneNumbers &oPhoneNumb);
	void DoExchangeТоDatabaseData(const CSubscriberPhoneNumbers &oPhoneNumb);
// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

