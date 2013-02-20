// phones.h : Implementation of the CPhones class



// CPhones implementation

// code generated on 20 �������� 2013 �., 21:19 �.

#include "stdafx.h"
#include "phones.h"
IMPLEMENT_DYNAMIC(CPhones, CRecordset)

CPhones::CPhones(CDatabase* pdb, const TCHAR *pszDBPath)
	: CDbTableInterface(pszDBPath), CRecordset(pdb)
{
	m_id = 0;
	m_rev_nmb = 0;
  m_Code = 0;
	m_PhoneType = L"";	
 	m_nFields = 4;
	m_nDefaultType = dynaset;

  CArray<CString> a_szFieldsNames;
  a_szFieldsNames.Add(_T("��� �� ��� �������"));
  a_szFieldsNames.Add(_T("��� �������"));

  LoadDb(_T("������ ��������"), a_szFieldsNames);
}

// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CPhones::GetDefaultConnect()
{
	return _T("DSN=SQLExpress;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=PROXIMUS-PC;DATABASE=phonebook");}

CString CPhones::GetDefaultSQL()
{
  TCHAR *pszDBPath = GetDBPath();
  if(pszDBPath)
  {
    return CString(pszDBPath) + _T(".phones");
  }
	return _T("[Phones$]");
}

void CPhones::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Int(pFX, _T("[id]"), m_id);
	RFX_Int(pFX, _T("[rev_nmb]"), m_rev_nmb);
	RFX_Int(pFX, _T("[code]"), m_Code);
	RFX_Text(pFX, _T("[phone_type]"), m_PhoneType);

}

BOOL CPhones::AddRow(CArray<CString> &a_csRowData)
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

	m_Code = _ttoi(a_csRowData[0]);
	m_PhoneType = a_csRowData[1];
  
  return Update();
}

HANDLE CPhones::ReadRow(CArray<CString> &a_csRowData,  int iRowNmbr)
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
	a_csRowData.Add(_itot(m_Code, szTemp, 10));
	a_csRowData.Add(m_PhoneType);

  return (HANDLE)pcRowId; 
}

BOOL CPhones::WriteRow(CArray<CString> &a_csRowData, HANDLE hRow)
{
  if(a_csRowData.GetCount() != m_nFields)
    return FALSE;

  Edit();

  m_Code =  _ttoi(a_csRowData[0]);
	m_PhoneType = a_csRowData[1];

  Update();

  return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CPhones diagnostics

#ifdef _DEBUG
void CPhones::AssertValid() const
{
	CRecordset::AssertValid();
}

void CPhones::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


