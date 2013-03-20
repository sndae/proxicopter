// SubscriberPhoneNumbersTable.h: interface of the CSubscriberPhoneNumbersTable class
//


#pragma once


// code generated on 05 март 2013 г., 19:08 ч.
#include "SubscriberPhoneNumbers.h"
#include "CitiesTable.h"
class CSubscriberPhoneNumbersTable : private CRecordset
{
public:
	CSubscriberPhoneNumbersTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSubscriberPhoneNumbersTable)

  //Enumerators
public:
  /* Изброяване имената на полетата и техните номера */
  enum  eColumn{cColIdx = 0, eColRevNumb, eColCode, eColFirstName, eColSecondName, eColThirdName, eColIDNumb, eColCityCode, eColAddress, eCOL_NUMB};


// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

  long	m_ID;
  long	m_REV_NUMB;
  long	m_CODE;
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

  BOOL SelectAll(CSubscriberPhoneNumbersArray &oSubscriberPhoneNumbersArray);
  BOOL SelectWhereId(const int iId, CSubscriberPhoneNumbers &oSubscriber);
  BOOL UpdateWhereId(const int iId, const CSubscriberPhoneNumbers &oSubscriber);
  BOOL Insert(const CSubscriberPhoneNumbers &oSubscriber);
  BOOL DeleteWhereId(const int iId);
  BOOL SortByColumn(const eColumn eCol, const BOOL bAsc);
  BOOL SelectByContent(const CSubscriberPhoneNumbers &oSubscriber);
  BOOL SelectAllCityCodes(CCitiesArray &oCitiesArray);
  /* Функции за достъп до таблица "Градове */
  CString GetCityCodeByCityId(const int iCityId);
  int    GetCityIdByCityCode(const TCHAR *pszCityCode);
private:
  void DoExchangeFromDatabaseData(CSubscriberPhoneNumbers &oSubscriber);
  void DoExchangeТоDatabaseData(const CSubscriberPhoneNumbers &oSubscriber);
// Implementation
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

};

