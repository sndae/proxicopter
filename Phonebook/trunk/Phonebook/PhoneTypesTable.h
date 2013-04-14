// PhoneTypesTable.h: interface of the CPhoneTypesTable class
//


#pragma once

// code generated on 05 март 2013 г., 19:08 ч.
#include "PhoneTypes.h"

class CPhoneTypesTable : private CRecordset
{
public:
	CPhoneTypesTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPhoneTypesTable)

	//Enumerators
public:
	// Изброяване имената на полетата и техните номера 
	enum	eColumn{cColIdx = 0, eColRevNumb, eColCode, eColType, eCOL_NUMB};


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
	long m_oCode;
	CStringW m_PHONE_TYPE;
	// Флаг разрешаващ търсенето на DSN:SQLEXPRESS 
	BOOL m_bSQLEn;

// Overrides
	// Wizard generated virtual function overrides
public:
	virtual CString GetDefaultConnect(); // Default connection string
	virtual CString GetDefaultSQL(); // default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

	BOOL SelectAll(CPhoneTypesArray &oPhoneTypesArray);
	BOOL SelectWhereId(const int iId, CPhoneTypes &oPhoneType);
	BOOL UpdateWhereId(const int iId, const CPhoneTypes &oPhoneType);
	BOOL Insert(const CPhoneTypes &oPhoneType);
	BOOL DeleteWhereId(const int iId);
	BOOL SortByColumn(const eColumn eCol, const BOOL bAsc = TRUE, const BOOL bResetFilter = TRUE);
	BOOL SelectByContent(const CPhoneTypes &oPhoneType);
private:
	void DoExchangeFromDatabaseData(CPhoneTypes &oPhoneType);
	void DoExchangeТоDatabaseData(const CPhoneTypes &oPhoneType);
// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

