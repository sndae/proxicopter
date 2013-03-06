// phones.h : Implementation of the CPhones class



// CPhones implementation

// code generated on 20 февруари 2013 г., 21:19 ч.

#include "stdafx.h"
#include "phones.h"
IMPLEMENT_DYNAMIC(CPhones, CRecordset)

CPhones::CPhones(CDatabase* pdb, const TCHAR *pszDBPath)
	: CDbTableCommonInterface(pszDBPath), CRecordset(pdb)
{
	m_id = 0;
	m_rev_numb = 0;
  m_Code = 0;
	m_PhoneType = L"";	
 	m_nFields = 4;
	m_nDefaultType = dynaset;

  CArray<CString> a_szFieldsNames;
  a_szFieldsNames.InsertAt(eColCode, _T("Код на тип телефон"));
  a_szFieldsNames.InsertAt(eColPhoneType, _T("Тип телефон"));

  LoadDb(_T("Типове телефони"), a_szFieldsNames);
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
    return CString(pszDBPath) + _T(".phone_types");
  }
	return _T("[phone_types$]");
}

void CPhones::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Int(pFX, _T("[id]"), m_id);
	RFX_Int(pFX, _T("[rev_numb]"), m_rev_numb);
	RFX_Int(pFX, _T("[code]"), m_Code);
	RFX_Text(pFX, _T("[phone_type]"), m_PhoneType);

}

BOOL CPhones::AddRow(CArray<CString> &a_csRowData)
{
  int iIndex = 0;
  try{
    MoveLast();
    iIndex = m_id;
  }
  catch(CDBException*){
    iIndex = 0;
  }

    /* validate if the same phone code has not already been appended */
  if( !CanAppend() ||
      IsColumnValuePresent(eColCode, a_csRowData[eColCode]))
  {
    ReloadCompleteTable(); 
    return FALSE;
  }
  
  AddNew();
	m_id = iIndex + 1;
	m_rev_numb = 0;

	m_Code = _ttoi(a_csRowData[eColCode]);
	m_PhoneType = a_csRowData[eColPhoneType];
  
  if(!Update())
    return FALSE;

  ReloadCompleteTable();
  return TRUE;
}

HANDLE CPhones::ReadRow(CArray<CString> &a_csRowData,  int iRowNmbr)
{
  Close();
  Open(CRecordset::dynaset);

  try{
    Move(iRowNmbr);
  }catch(CDBException *){
    return 0;
  }
  if(IsEOF() || IsBOF())
    return 0;

  CDBVariant cDBVariant;
  /* create a row identifier struct */
  CRowIdent *pcRowId = new CRowIdent();
  
  pcRowId->m_iRev = m_rev_numb;
  pcRowId->m_iId = m_id;
  pcRowId->m_iNmb = iRowNmbr;

  TCHAR szTemp[64];
	a_csRowData.Add(_itot(m_Code, szTemp, 10));
	a_csRowData.Add(m_PhoneType);

  return (HANDLE)pcRowId; 
}

BOOL CPhones::WriteRow(CArray<CString> &a_csRowData, HANDLE hRow)
{
  if(!hRow)
    return FALSE;

  /* cast the row handle to a row identifier struct */
  CRowIdent *pRowId = static_cast<CRowIdent*>(hRow);
  Close();
  Open(CRecordset::dynaset);
  Move(pRowId->m_iNmb);
  if(IsEOF() || IsBOF() || !CanUpdate())
    return FALSE;

  if(m_id != pRowId->m_iId)
    return FALSE;
  else if(m_rev_numb != pRowId->m_iRev)
    return FALSE;

  if(a_csRowData.GetCount() != m_nFields - m_iUserOffset)
    return FALSE;

  Edit();

	m_id      = pRowId->m_iId;
	m_rev_numb = ++pRowId->m_iRev;
  m_Code    = _ttoi(a_csRowData[eColCode]);
	m_PhoneType = a_csRowData[eColPhoneType];

  Update();

  return TRUE;
}

int CPhones::ReadIdentifierByRowNumber(int iRowNmb)
{
  Move(iRowNmb);
  if(IsEOF() || IsBOF())
  {
    return 0;
  }
  return m_id;
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


