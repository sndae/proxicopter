// Cities.h : Declaration of the CCities

#pragma once

// code generated on Tuesday, February 19, 2013, 1:38 PM
#include "DbTableInterface.h"

class CCities :  virtual private CRecordset, public CDbTableInterface
{
protected:
  virtual void     EditAndUpdateFields(CArray<CString> &a_csRowData);
public:
	CCities(CDatabase* pDatabase);
	DECLARE_DYNAMIC(CCities)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	double	m_Id;
	double	m_rev_nmb;
	double	m_Code;
	CStringW	m_Name;
	CStringW	m_Area;

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


