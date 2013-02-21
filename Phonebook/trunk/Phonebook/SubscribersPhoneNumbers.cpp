// SubscribersPhoneNumbers.h : Implementation of the CSubscribersPhoneNumbers class



// CSubscribersPhoneNumbers implementation

// code generated on 20 февруари 2013 г., 23:56 ч.

#include "stdafx.h"
#include "SubscribersPhoneNumbers.h"
#include "Subscribers.h"
#include "Phones.h"

IMPLEMENT_DYNAMIC(CSubscribersPhoneNumbers, CRecordset)

CSubscribersPhoneNumbers::CSubscribersPhoneNumbers(CDatabase* pdb, const TCHAR *pszDBPath)
	: CDbTableInterface(pszDBPath), CRecordset(pdb)
{
	m_id = 0;
	m_rev_nmb = 0;
	m_subscriber_id = 0;
	m_phone_id = 0;
	m_phone_number = L"";
	m_nFields = 5;
	m_nDefaultType = dynaset;

  CArray<CString> a_szFieldsNames;
  a_szFieldsNames.InsertAt(eColSubscriberId,  _T("Име"));
  a_szFieldsNames.InsertAt(eColPhoneId, _T("Презиме"));
  a_szFieldsNames.InsertAt(eColPhoneNumb, _T("Презиме"));

  LoadDb(_T("Абонати"), a_szFieldsNames);
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CSubscribersPhoneNumbers::GetDefaultConnect()
{
	return _T("DSN=SQLExpress;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=PROXIMUS-PC;DATABASE=phonebook");
}

CString CSubscribersPhoneNumbers::GetDefaultSQL()
{
  TCHAR *pszDBPath = GetDBPath();
  if(pszDBPath)
  {
    return CString(pszDBPath) + _T(".subscriber_phone_numbers");
  }
	return _T("[subscriber_phone_numbers$]");
}

void CSubscribersPhoneNumbers::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[id]"), m_id);
	RFX_Long(pFX, _T("[rev_nmb]"), m_rev_nmb);
	RFX_Long(pFX, _T("[subscriber_id]"), m_subscriber_id);
	RFX_Long(pFX, _T("[phone_id]"), m_phone_id);
	RFX_Text(pFX, _T("[phone_number]"), m_phone_number);

}

BOOL    CSubscribersPhoneNumbers::WriteRow(CArray<CString> &a_csRowData, HANDLE hRow)
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


  CSubscribers cSubscrTable(m_pDatabase, GetDBPath());
  cSubscrTable.FilterTableByColumnValue(cSubscrTable.GetColumnRepresName(CSubscribers::eColCode), a_csRowData[CSubscribersPhoneNumbers::eColSubscriberId], eEquals);
  if(IsBOF())
    return FALSE;

  int iSubscriberId = cSubscrTable.ReadIdentifierByRowNumber(0); 

  CPhones cPhonesTable(m_pDatabase, GetDBPath());
  cPhonesTable.FilterTableByColumnValue(cPhonesTable.GetColumnRepresName(CPhones::eColCode), a_csRowData[CSubscribersPhoneNumbers::eColPhoneId], eEquals);
  if(IsBOF())
    return FALSE;

  int iPhonesId = cPhonesTable.ReadIdentifierByRowNumber(0);

  Edit();

	m_id = pRowId->m_iId;
	m_rev_nmb = ++pRowId->m_iRev;
	m_subscriber_id = iSubscriberId;
	m_phone_id = iPhonesId;
  m_phone_number = a_csRowData[CSubscribersPhoneNumbers::eColPhoneNumb];

  return Update();
}

BOOL    CSubscribersPhoneNumbers::AddRow(CArray<CString> &a_csRowData)
{
  ReloadCompleteTable();
  MoveLast();
  int iIndex = m_id;
  if(!CanAppend())
  {
    return FALSE;
  }

  CSubscribers cSubscrTable(m_pDatabase, GetDBPath());
  cSubscrTable.FilterTableByColumnValue(cSubscrTable.GetColumnRepresName(CSubscribers::eColCode), a_csRowData[CSubscribersPhoneNumbers::eColSubscriberId], eEquals);
  if(IsBOF())
    return FALSE;

  int iSubscriberId = cSubscrTable.ReadIdentifierByRowNumber(0); 

  CPhones cPhonesTable(m_pDatabase, GetDBPath());
  cPhonesTable.FilterTableByColumnValue(cPhonesTable.GetColumnRepresName(CPhones::eColCode), a_csRowData[CSubscribersPhoneNumbers::eColPhoneId], eEquals);
  if(IsBOF())
    return FALSE;

  int iPhonesId = cPhonesTable.ReadIdentifierByRowNumber(0);

  AddNew();

	m_id = iIndex + 1;
	m_rev_nmb = 0;
	m_subscriber_id = iSubscriberId;
	m_phone_id = iPhonesId;
  m_phone_number = a_csRowData[CSubscribersPhoneNumbers::eColPhoneNumb];

  return Update();
}

HANDLE  CSubscribersPhoneNumbers::ReadRow(CArray<CString> &a_csRowData,  int iRowNmbr)
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

  CSubscribers cSubsTable(m_pDatabase, GetDBPath());
  CArray<CString> a_csRelTableRowData;
  if(! cSubsTable.ReadRowByIdentifier(m_subscriber_id, a_csRelTableRowData))
    return FALSE;

  a_csRowData.InsertAt(eColSubscriberId, a_csRelTableRowData[CSubscribers::eColCode]);
  
  CPhones cPhones(m_pDatabase, GetDBPath());
  a_csRelTableRowData.RemoveAll();
  if(! cPhones.ReadRowByIdentifier(m_phone_id, a_csRelTableRowData))
    return FALSE;

  a_csRowData.InsertAt(eColPhoneId, a_csRelTableRowData[CPhones::eColPhoneType]);
  
  a_csRowData.InsertAt(eColPhoneNumb, m_phone_number);

  return (HANDLE)pcRowId;
}


/////////////////////////////////////////////////////////////////////////////
// CSubscribersPhoneNumbers diagnostics

#ifdef _DEBUG
void CSubscribersPhoneNumbers::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSubscribersPhoneNumbers::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


