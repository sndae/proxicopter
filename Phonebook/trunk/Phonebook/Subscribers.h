// Subscribers.h : Declaration of the CSubscribers

#pragma once

// code generated on 20 �������� 2013 �., 22:07 �.
#include "DbTableInterface.h"

class CSubscribers : virtual private CRecordset, public CDbTableInterface
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

	double	m_id;
	double	m_rev_nmb;
	double	m_code;
	CStringW	m_first_name;
	CStringW	m_second_name;
	CStringW	m_third_name;
	double	m_ident_nmb;
	long	m_city_id;
	CStringW	m_city_addr;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
  virtual BOOL     WriteRow(CArray<CString> &a_csRowData, HANDLE hRow);
  virtual BOOL     AddRow(CArray<CString> &a_csRowData);
  virtual HANDLE   ReadRow(CArray<CString> &a_csRowData,  int iRowNmbr);
// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
private:
  BOOL GetCityNameById(int iId, TCHAR *pszCityName);
};


