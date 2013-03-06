// Subscribers.h : Declaration of the CSubscribers

#pragma once

// code generated on 20 февруари 2013 г., 22:07 ч.
#include "DbTableCommonInterface.h"

class CSubscribers : virtual private CRecordset, public CDbTableCommonInterface
{
public:
	CSubscribers(CDatabase* pDatabase, const TCHAR *pszDBPath = 0);
	DECLARE_DYNAMIC(CSubscribers)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	int	m_id;
	int	m_rev_numb;
	int	m_code;
	CStringW	m_first_name;
	CStringW	m_second_name;
	CStringW	m_third_name;
	CStringW	m_ident_numb;
	long	m_city_id;
	CStringW	m_city_addr;

// Overrides
	// Wizard generated virtual function overrides
	public:
  /* helper enumeration of the SQL columns expected to be encountered */
  enum    eTableColumns{eColCode = 0, eColFirstName, eColSecondName, eColThirdName, eColIdentNumb, eColCityId, eColCityAddr};

	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

  /* Implementation of the pure virtual functions inherited from CDbTableInterface */
  virtual BOOL     WriteRow(CArray<CString> &a_csRowData, HANDLE hRow);
  virtual BOOL     AddRow(CArray<CString> &a_csRowData);
  virtual HANDLE   ReadRow(CArray<CString> &a_csRowData,  int iRowNmbr);
  virtual int      ReadIdentifierByRowNumber(int iRowNmb);
// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


