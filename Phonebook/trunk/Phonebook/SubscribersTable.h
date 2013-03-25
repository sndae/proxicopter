// SubscribersTable.h: interface of the CSubscribersTable class
//


#pragma once


// code generated on 05 март 2013 г., 19:08 ч.
#include "Subscribers.h"
#include "CitiesTable.h"
class CSubscribersTable : private CRecordset
{
public:
	CSubscribersTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSubscribersTable)

	//Enumerators
public:
	/* Изброяване имената на полетата и техните номера */
	enum	eColumn{cColIdx = 0, eColRevNumb, eColCode, eColFirstName, eColSecondName, eColThirdName, eColIDNumb, eColCityCode, eColAddress, eCOL_NUMB};


// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.	If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long m_ID;
	long m_REV_NUMB;
	long m_CODE;
	CStringW m_FIRST_NAME ;
	CStringW m_SECOND_NAME;
	CStringW m_THIRD_NAME; 
	CStringW m_IDENT_NUMB; 
	long m_CITY_ID;
	CStringW m_CITY_ADDR;

	/* Флаг разрешаващ търсенето на DSN:SQLEXPRESS */
	BOOL m_bSQLEn;
		
	CCitiesTable m_oCitiesTable;

// Overrides
	// Wizard generated virtual function overrides
public:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

	BOOL SelectAll(CSubscribersArray &oSubscribersArray);
	BOOL SelectWhereId(const int iId, CSubscribers &oSubscriber);
	BOOL UpdateWhereId(const int iId, const CSubscribers &oSubscriber);
	BOOL Insert(const CSubscribers &oSubscriber);
	BOOL DeleteWhereId(const int iId);
	BOOL SortByColumn(const eColumn eCol, const BOOL bAsc);
	BOOL SelectByContent(const CSubscribers &oSubscriber);
	BOOL SelectAllCityCodes(CCitiesArray &oCitiesArray);
	/* Функции за достъп до таблица "Градове */
	CString GetCityCodeByCityId(const int iCityId);
	int		GetCityIdByCityCode(const TCHAR *pszCityCode);
private:
	void DoExchangeFromDatabaseData(CSubscribers &oSubscriber);
	void DoExchangeТоDatabaseData(const CSubscribers &oSubscriber);
// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

