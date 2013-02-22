// Subscribers.h : Implementation of the CSubscribers class



// CSubscribers implementation

// code generated on 20 февруари 2013 г., 22:07 ч.

#include "stdafx.h"
#include "Subscribers.h"
#include "Cities.h"
IMPLEMENT_DYNAMIC(CSubscribers, CRecordset)

CSubscribers::CSubscribers(CDatabase* pdb, const TCHAR *pszDBPath)
	: CDbTableInterface(pszDBPath), CRecordset(pdb)
{
	m_id = 0;
	m_rev_nmb = 0;
	m_code = 0;
	m_first_name = L"";
	m_second_name = L"";
	m_third_name = L"";
	m_ident_nmb = 0;
	m_city_id = 0;
	m_city_addr = L"";
	m_nFields = 9;
	m_nDefaultType = dynaset;

  CArray<CString> a_szFieldsNames;
  a_szFieldsNames.InsertAt(eColCode,       _T("Код на абонат"));
  a_szFieldsNames.InsertAt(eColFirstName,  _T("Име"));
  a_szFieldsNames.InsertAt(eColSecondName, _T("Презиме"));
  a_szFieldsNames.InsertAt(eColThirdName,  _T("Фамилия"));
  a_szFieldsNames.InsertAt(eColIdentNumb,  _T("ЕГН"));
  a_szFieldsNames.InsertAt(eColCityId,     _T("Код на град"));
  a_szFieldsNames.InsertAt(eColCityAddr,    _T("Адрес"));

  LoadDb(_T("Абонати"), a_szFieldsNames);
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CSubscribers::GetDefaultConnect()
{
	return _T("DSN=SQLExpress;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=PROXIMUS-PC;DATABASE=phonebook");
}

CString CSubscribers::GetDefaultSQL()
{
  TCHAR *pszDBPath = GetDBPath();
  if(pszDBPath)
  {
    return CString(pszDBPath) + _T(".subscribers");
  }
	return _T("[Subscribers$]");

}

void CSubscribers::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
  RFX_Double(pFX, _T("[id]"), m_id);
	RFX_Double(pFX, _T("[rev_nmb]"), m_rev_nmb);
	RFX_Double(pFX, _T("[code]"), m_code);
	RFX_Text(pFX, _T("[first_name]"), m_first_name);
	RFX_Text(pFX, _T("[second_name]"), m_second_name);
	RFX_Text(pFX, _T("[third_name]"), m_third_name);
	RFX_Double(pFX, _T("[ident_nmb]"), m_ident_nmb);
	RFX_Long(pFX, _T("[city_id]"), m_city_id);
	RFX_Text(pFX, _T("[city_addr]"), m_city_addr);

}


BOOL CSubscribers::AddRow(CArray<CString> &a_csRowData)
{
  ReloadCompleteTable();
  MoveLast();
  int iIndex = m_id;
  if( !CanAppend() ||
    IsColumnValuePresent(eColCode, a_csRowData[eColCode]))
  {
    return FALSE;
  }

  CCities cCityTable(m_pDatabase, GetDBPath());
  CArray<CString> csRelTableRowData;
  cCityTable.FilterTableByColumnValue(CCities::eColCode, a_csRowData[eColCityId], eEquals);
  if(IsBOF())
    return FALSE;
  
  AddNew();
	m_id          = iIndex + 1;
	m_rev_nmb     = 0;
	m_code        = _ttoi(a_csRowData[eColCode]);
	m_first_name  = a_csRowData[eColFirstName];
  m_second_name = a_csRowData[eColSecondName];
	m_third_name  = a_csRowData[eColThirdName];
	m_ident_nmb   = _ttoi(a_csRowData[eColIdentNumb]);
  m_city_id     = cCityTable.ReadIdentifierByRowNumber(0);
  m_city_addr   = a_csRowData[eColCityAddr];

  return Update();
}

HANDLE CSubscribers::ReadRow(CArray<CString> &a_csRowData,  int iRowNmbr)
{
  Move(iRowNmbr);
  if(IsEOF() || IsBOF())
  {
    return 0;
  }

  CDBVariant cDBVariant;
  CRowIdent *pcRowId = new CRowIdent();
  
  pcRowId->m_iRev = m_rev_nmb;
  pcRowId->m_iId = m_id;
  pcRowId->m_iNmb = iRowNmbr;

  TCHAR szTemp[64];
  a_csRowData.InsertAt(eColCode,       _itot(m_code, szTemp, 10));
	a_csRowData.InsertAt(eColFirstName,  m_first_name);
	a_csRowData.InsertAt(eColSecondName, m_second_name);
	a_csRowData.InsertAt(eColThirdName,  m_third_name);
	a_csRowData.InsertAt(eColIdentNumb,  _itot(m_ident_nmb, szTemp, 10));

  CCities cCityTable(m_pDatabase, GetDBPath());
  CArray<CString> csRowData;
  if(! cCityTable.ReadRowByIdentifier(m_city_id, csRowData))
    return FALSE;

  a_csRowData.InsertAt(eColCityId, csRowData[CCities::eColCode]);
  CString csCityAddress = csRowData[CCities::eColName];
  csCityAddress += _T(", ");
  csCityAddress += m_city_addr;
  a_csRowData.InsertAt(eColCityAddr, csCityAddress);

  return (HANDLE)pcRowId; 
}

BOOL CSubscribers::WriteRow(CArray<CString> &a_csRowData, HANDLE hRow)
{
  if(!hRow)
    return FALSE;

  CRowIdent *pRowId = static_cast<CRowIdent*>(hRow);
  Move(pRowId->m_iNmb);
  if(IsEOF() || IsBOF() || !CanUpdate())
    return FALSE;

  if(m_id != pRowId->m_iId)
    return FALSE;
  else if(m_rev_nmb != pRowId->m_iRev)
    return FALSE;

  if(a_csRowData.GetCount() != m_nFields - m_iUserOffset)
    return FALSE;

  CCities cCityTable(m_pDatabase, GetDBPath());
  CArray<CString> csRelTableRowData;
  cCityTable.FilterTableByColumnValue(CCities::eColCode, a_csRowData[eColCityId], eEquals);
  if(IsBOF())
    return FALSE;
    
  Edit();

	m_id          = pRowId->m_iId ;
	m_rev_nmb     = ++pRowId->m_iRev;
	m_code        = _ttoi(a_csRowData[eColCode]);
	m_first_name  = a_csRowData[eColFirstName];
	m_second_name = a_csRowData[eColSecondName];
	m_third_name  = a_csRowData[eColThirdName];
  m_ident_nmb   = _ttoi(a_csRowData[eColIdentNumb]);
  m_city_id     = cCityTable.ReadIdentifierByRowNumber(0);
  m_city_addr   = a_csRowData[eColCityAddr];

  Update();

  return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CSubscribers diagnostics

#ifdef _DEBUG
void CSubscribers::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSubscribers::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


