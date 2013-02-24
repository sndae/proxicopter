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
  a_szFieldsNames.InsertAt(eColSubscriberId,  _T("Код на абонат"));
  a_szFieldsNames.InsertAt(eColPhoneId,       _T("Код на тип телефон"));
  a_szFieldsNames.InsertAt(eColPhoneNumb,     _T("Телефон"));

  LoadDb(_T("Телефонни номера на абонати"), a_szFieldsNames);
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

  /* has the revision number been incremented since the last read ? */
  CRowIdent *pRowId = static_cast<CRowIdent*>(hRow);
  Close();
  Open(CRecordset::dynaset);
  Move(pRowId->m_iNmb);
  if(IsEOF() || IsBOF() || !CanUpdate())
    return FALSE;

  if(m_id != pRowId->m_iId)
    return FALSE;
  else if(m_rev_nmb != pRowId->m_iRev)
    return FALSE;

  if(a_csRowData.GetCount() != m_nFields - m_iUserOffset)
    return FALSE;

  /* is there a subscriber row of such subscriber code ? */
  CSubscribers cSubscrTable(m_pDatabase, GetDBPath());
  if(!cSubscrTable.IsColumnValuePresent(CSubscribers::eColCode, a_csRowData[CSubscribersPhoneNumbers::eColSubscriberId], eEquals))
    return FALSE;

  int iSubscriberId = cSubscrTable.ReadIdentifierByRowNumber(0); 

  /* is there a phone woe of such phone code ? */
  CPhones cPhonesTable(m_pDatabase, GetDBPath());
  if(!cPhonesTable.IsColumnValuePresent(CPhones::eColCode, a_csRowData[CSubscribersPhoneNumbers::eColPhoneId]))
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

int CSubscribersPhoneNumbers::ReadIdentifierByRowNumber(int iRowNmb)
{
  Move(iRowNmb);
  if(IsEOF() || IsBOF())
    return 0;

  return m_id;
}


BOOL    CSubscribersPhoneNumbers::AddRow(CArray<CString> &a_csRowData)
{
  int iIndex = 0;
  try{
    MoveLast();
    iIndex = m_id;
  }
  catch(CDBException*){
    iIndex = 0;
  }

  if(!CanAppend())
    return FALSE;

  /* is there a subscriber row of such subscriber code ? */
  CSubscribers cSubscrTable(m_pDatabase, GetDBPath());
  if(!cSubscrTable.IsColumnValuePresent(CSubscribers::eColCode, a_csRowData[CSubscribersPhoneNumbers::eColSubscriberId], eEquals))
    return FALSE;

  /* get the subscriber row identifier */
  int iSubscriberId = cSubscrTable.ReadIdentifierByRowNumber(0); 

  /* is there a phone row of such phone code ? */
  CPhones cPhonesTable(m_pDatabase, GetDBPath());
  if(!cPhonesTable.IsColumnValuePresent(CPhones::eColCode, a_csRowData[CSubscribersPhoneNumbers::eColPhoneId], eEquals))
    return FALSE;

  /* get the phone row identifier */
  int iPhonesId = cPhonesTable.ReadIdentifierByRowNumber(0);

  AddNew();

	m_id = iIndex + 1;
	m_rev_nmb = 0;
	m_subscriber_id = iSubscriberId;
	m_phone_id = iPhonesId;
  m_phone_number = a_csRowData[CSubscribersPhoneNumbers::eColPhoneNumb];

  if(!Update())
    return FALSE;

  ReloadCompleteTable();
  return TRUE;
}

HANDLE  CSubscribersPhoneNumbers::ReadRow(CArray<CString> &a_csRowData,  int iRowNmbr)
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
  CRowIdent *pcRowId = new CRowIdent();
  
  pcRowId->m_iRev = m_rev_nmb;
  pcRowId->m_iId = m_id;
  pcRowId->m_iNmb = iRowNmbr;

  /* read the subscriber row of such a subscriber identifier and insert its code into the array */ 
  CSubscribers cSubsTable(m_pDatabase, GetDBPath());
  CArray<CString> a_csRelTableRowData;
  if(! cSubsTable.ReadRowByIdentifier(m_subscriber_id, a_csRelTableRowData))
    return FALSE;

  a_csRowData.InsertAt(eColSubscriberId, a_csRelTableRowData[CSubscribers::eColCode]);
  
  /* read the phone row of such a city identifier and insert its code into the array */ 
  CPhones cPhones(m_pDatabase, GetDBPath());
  a_csRelTableRowData.RemoveAll();
  if(! cPhones.ReadRowByIdentifier(m_phone_id, a_csRelTableRowData))
    return FALSE;

  a_csRowData.InsertAt(eColPhoneId, a_csRelTableRowData[CPhones::eColCode]);
  
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


