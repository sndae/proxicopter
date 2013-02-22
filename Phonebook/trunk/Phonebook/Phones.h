// phones.h : Declaration of the CPhones

#pragma once
#include "DbTableInterface.h"
// code generated on 20 февруари 2013 г., 21:19 ч.

class CPhones :  virtual private CRecordset, public CDbTableInterface
{
public:
	CPhones(CDatabase* pdb, const TCHAR *pszDBPath);
	DECLARE_DYNAMIC(CPhones)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	int	m_id;
	int	m_rev_nmb;
	int	m_Code;
	CStringW	m_PhoneType;

// Overrides
	// Wizard generated virtual function overrides
	public:
  enum    eTableColumns{eColCode = 0, eColPhoneType};
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

  virtual BOOL     AddRow(CArray<CString> &a_csRowData);
  virtual HANDLE   ReadRow(CArray<CString> &a_csRowData,  int iRowNmbr);
  virtual BOOL     WriteRow(CArray<CString> &a_csRowData, HANDLE hRow);
  virtual int      ReadIdentifierByRowNumber(int iRowNmb);

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


