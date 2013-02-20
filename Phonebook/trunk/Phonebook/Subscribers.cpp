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
  a_szFieldsNames.Add(_T("Код на абонат"));
  a_szFieldsNames.Add(_T("Име"));
  a_szFieldsNames.Add(_T("Презиме"));
  a_szFieldsNames.Add(_T("Фамилия"));
  a_szFieldsNames.Add(_T("ЕГН"));
  a_szFieldsNames.Add(_T("Код на град"));
  a_szFieldsNames.Add(_T("Адрес"));

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
      IsColumnValuePresent(GetColumnRepresName(0), a_csRowData[0]))
  {
    return FALSE;
  }
  
  AddNew();
	m_id = iIndex + 1;
	m_rev_nmb = 0;
	m_code        = _ttoi(a_csRowData[0]);
	m_first_name  = a_csRowData[1];
	m_second_name = a_csRowData[2];
	m_third_name  = a_csRowData[3];
	m_ident_nmb = _ttoi(a_csRowData[4]);
	m_city_id   = _ttoi(a_csRowData[5]);
	m_city_addr = a_csRowData[6];

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
	a_csRowData.Add(_itot(m_code, szTemp, 10));
	a_csRowData.Add(m_first_name);
	a_csRowData.Add(m_second_name);
	a_csRowData.Add(m_third_name);
	a_csRowData.Add(_itot(m_ident_nmb, szTemp, 10));
	
  GetCityNameById(m_city_id, szTemp);
  //a_csRowData.Add(GetCityNameById(m_city_id));
	
  a_csRowData.Add(m_city_addr);



  return (HANDLE)pcRowId; 
}

BOOL CSubscribers::WriteRow(CArray<CString> &a_csRowData, HANDLE hRow)
{
  if(a_csRowData.GetCount() != m_nFields)
    return FALSE;

  Edit();

 // m_Code =  _ttoi(a_csRowData[0]);
 // m_PhoneType = a_csRowData[1];

  Update();

  return TRUE;
}

BOOL CSubscribers::GetCityNameById(int iId, TCHAR *pszCityName)
{
  CCities cCitiesTable(m_pDatabase, GetDBPath());
//  cCitiesTable.Close();

  return  TRUE;
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


