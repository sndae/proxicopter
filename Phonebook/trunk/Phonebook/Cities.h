// Cities.h : Declaration of the CCities

#pragma once

// code generated on Tuesday, February 19, 2013, 1:38 PM
#include "DbTableInterface.h"

class CCities :  virtual private CRecordset, public CDbTableInterface
{
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

	int	m_Id;
	int	m_rev_nmb;
	int	m_Code;
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
  virtual BOOL     WriteRow(CArray<CString> &a_csRowData, HANDLE hRow);
  virtual BOOL     AddRow(CArray<CString> &a_csRowData);
  virtual HANDLE   ReadRow(CArray<CString> &a_csRowData,  int iRowNmbr);
#endif
protected:
  virtual BOOL     EditAndUpdateFields(CArray<CString> &a_csRowData);
};


