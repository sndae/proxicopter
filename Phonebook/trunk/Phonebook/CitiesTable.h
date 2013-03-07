// CitiesTable.h: interface of the CCitiesTable class
//


#pragma once

// code generated on 05 март 2013 г., 19:08 ч.
#include "Cities.h"

class CCitiesTable : private CRecordset
{
public:
	CCitiesTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCitiesTable)

  //Enumerators
public:
  /* Изброяване имената на полетата и техните номера */
  enum  eColumn{cColIdx = 0, eColRevNumb, eColCode, eColName, eColArea, eCOL_NUMB};


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
	CStringW	m_CODE;
	CStringW	m_NAME;
	CStringW	m_AREA;
  /* Флаг разрешаващ търсенето на DSN:SQLEXPRESS */
  BOOL m_bSQLEn;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string
  virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

  BOOL SelectAll(CCitiesArray &oCitiesArray);
  BOOL SelectWhereId(const int iId, CCities &oCity);
  BOOL UpdateWhereId(const int iId, const CCities &oCity);
  BOOL Insert(const CCities &oCity);
  BOOL DeleteWhereId(const int iId);
  BOOL SortByColumn(const eColumn eCol, const BOOL bAsc);
  BOOL SelectByContent(const CCities &oCity);
// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

