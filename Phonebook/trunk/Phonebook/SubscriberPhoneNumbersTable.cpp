// SubscriberPhoneNumbersTable.cpp : implementation of the CSubscriberPhoneNumbersTable class
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "SubscriberPhoneNumbersTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSubscriberPhoneNumbersTable implementation

// code generated on 05 март 2013 г., 19:08 ч.

IMPLEMENT_DYNAMIC(CSubscriberPhoneNumbersTable, CRecordset)

CSubscriberPhoneNumbersTable::CSubscriberPhoneNumbersTable(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_nID = 0;
	m_REV_NUMB = 0;
	m_PHONE_ID = 0;
	m_SUBSCRIBER_ID = 0;
	m_PHONE_NUMB = L""; 
	
	m_nFields = 5;
	m_nDefaultType = dynaset;

#if (_SQL_DE)
	m_bSQLEn = FALSE;
#else
	m_bSQLEn = TRUE;
#endif
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CSubscriberPhoneNumbersTable::GetDefaultConnect()
{
	if(m_bSQLEn)
		return _T("DSN=SQLExpress;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=PROXIMUS-PC;DATABASE=phonebook");
	else
		return EMPTY_STRING;
}

CString CSubscriberPhoneNumbersTable::GetDefaultSQL()
{
	if(m_bSQLEn)
		return _T("[dbo].[SUBSCRIBER_PHONE_NUMBERS]");
	else
		return _T("[SUBSCRIBER_PHONE_NUMBERS$]");
}

void CSubscriberPhoneNumbersTable::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	// Macros such as RFX_Text() and RFX_Int() are dependent on the
	// type of the member variable, not the type of the field in the database.
	// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_nID);
	RFX_Long(pFX, _T("[REV_NUMB]"), m_REV_NUMB);
	RFX_Long(pFX, _T("[SUBSCRIBER_ID]"), m_SUBSCRIBER_ID);
	RFX_Long(pFX, _T("[PHONE_ID]"), m_PHONE_ID);
	RFX_Text(pFX, _T("[PHONE_NUMB]"), m_PHONE_NUMB);
}

BOOL const CSubscriberPhoneNumbersTable::SelectAll(CSubscriberPhoneNumbersArray &oSubscrPhoneNmbPhoneNumbersArray)
{
	if(IsOpen())
		Close();
	
	BOOL bRes = FALSE;
	try
	{
	 bRes= Open(CRecordset::dynaset);
	}
	catch(CDBException *)
	{
		// В случай на неуспех при отваряне на връзката по подразбиране се прави нов опит, 
		//този път със запитване на потребителят. Очаква се че ще се окаже XLS файл 
		m_bSQLEn = FALSE;
		bRes = Open(CRecordset::dynaset);
	}
	
	try
	{
		if(bRes && !IsBOF())
		{
			// запъвлване на масива с указатели към данни на редове от таблицата 
			while(!IsEOF())
			{
				oSubscrPhoneNmbPhoneNumbersArray.Add(new CSubscriberPhoneNumbers(int(m_nID), int(m_REV_NUMB), m_SUBSCRIBER_ID, m_PHONE_ID, m_PHONE_NUMB));		 
				MoveNext();
			}
		}
	}
	catch(CDBException *)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL const CSubscriberPhoneNumbersTable::SelectWhereId(const int iId, CSubscriberPhoneNumbers &oSubscrPhoneNmbPhoneNumbers)
{
	if(IsOpen())
		Close(); 

	m_strFilter.Format(_T("ID = %d"), iId);
	Open(CRecordset::dynaset);

	try
	{
		if(IsBOF())
			return FALSE; 

		MoveFirst();

		DoExchangeFromDatabaseData(oSubscrPhoneNmbPhoneNumbers);
	}
	catch(CDBException *)
	{
		return FALSE;
	}

	return TRUE;	
}

BOOL CSubscriberPhoneNumbersTable::UpdateWhereId(const int iId, const CSubscriberPhoneNumbers &oSubscrPhoneNmbPhoneNumbers)
{
	CSubscriberPhoneNumbers oCurrSubscriber;
	if(!SelectWhereId(iId, oCurrSubscriber))
		return FALSE;
	
	if(oCurrSubscriber.m_nRevNumb != oSubscrPhoneNmbPhoneNumbers.m_nRevNumb)
		return FALSE;

	try
	{
		MoveFirst();	
		Edit();

		CSubscriberPhoneNumbers oSubscrCopy = oSubscrPhoneNmbPhoneNumbers;
		oSubscrCopy.m_nRevNumb = oCurrSubscriber.m_nRevNumb + 1;
		
		DoExchangeТоDatabaseData(oSubscrCopy);

		Update();
	}
	catch(CDBException *)
	{
		m_strFilter = EMPTY_STRING;
		m_strSort = EMPTY_STRING;
		return FALSE;
	}

	m_strFilter = EMPTY_STRING;
	m_strSort = EMPTY_STRING;

	return TRUE;
}

BOOL CSubscriberPhoneNumbersTable::Insert(const CSubscriberPhoneNumbers &oSubscrPhoneNmbPhoneNumbers)
{
	if(IsOpen())
		Close(); 

	m_strFilter = EMPTY_STRING;
	m_strSort = EMPTY_STRING;
	Open(CRecordset::dynaset);

	if(!CanAppend())
		return FALSE;

	if(!IsBOF())
		MoveLast();	

	// буфериране ID на последният ред от раблицата  
	int iLastRowId = m_nID;
	
	try
	{
		AddNew();

		CSubscriberPhoneNumbers oSubscrCopy = oSubscrPhoneNmbPhoneNumbers;
		oSubscrCopy.m_nId = iLastRowId + 1;
		oSubscrCopy.m_nRevNumb = 0;

		DoExchangeТоDatabaseData(oSubscrCopy);

		Update();
	}
	catch(CDBException *)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSubscriberPhoneNumbersTable::DeleteWhereId(const int iId)
{
	CSubscriberPhoneNumbers oSubscrPhoneNmbPhoneNumbers;
	if(!SelectWhereId(iId, oSubscrPhoneNmbPhoneNumbers))
	{
		m_strFilter = EMPTY_STRING;
		return FALSE;
	}

	try
	{
		if(!CanUpdate())
			return FALSE;

		Delete();
	}
	catch(CDBException *)
	{
		m_strFilter = EMPTY_STRING;
		return FALSE;
	}

  m_strFilter = EMPTY_STRING;
	return TRUE;
}

BOOL CSubscriberPhoneNumbersTable::SortByColumn(const eColumn eCol, const BOOL bAsc, const BOOL bResetFilter)
{
	if(IsOpen())
		Close(); 

	if(bResetFilter)
		m_strFilter = EMPTY_STRING;

	switch(eCol)
	{
	case eColPhoneCode:		
		bAsc ? m_strSort.Format(_T("%s ASC"), _T("PHONE_ID")): m_strSort.Format(_T("%s DESC"), _T("PHONE_ID"));
		break;
	case eColSubscrCode:
		bAsc ? m_strSort.Format(_T("%s ASC"), _T("SUBSCRIBER_ID")): m_strSort.Format(_T("%s DESC"), _T("SUBSCRIBER_ID"));
		break;
	case eColPhoneNumber:
		bAsc ? m_strSort.Format(_T("%s ASC"), _T("PHONE_NUMB")): m_strSort.Format(_T("%s DESC"), _T("PHONE_NUMB"));
		break;
	default:
		return FALSE;
	}
	
	try
	{
		Open(CRecordset::dynaset);
	}
	catch(CDBException *)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSubscriberPhoneNumbersTable::SelectByContent(const CSubscriberPhoneNumbers &oSubscrPhoneNmbPhoneNumbers, BOOL bClearFilter)
{
	if(IsOpen())
		Close(); 

	if(bClearFilter)
	{
		m_strSort = EMPTY_STRING;
		m_strFilter = EMPTY_STRING;
	}

	CString szColFilter;
	if(oSubscrPhoneNmbPhoneNumbers.m_nId != DNC)
	{
		// изключване на текущият запис от по-нататъшното филтриране 
		szColFilter.Format(_T("ID != %d"), oSubscrPhoneNmbPhoneNumbers.m_nId);
		m_strFilter += szColFilter;
	}
	// формиране на низ за филтриране, на база наличните в структурата ненулеви записи 
	if(oSubscrPhoneNmbPhoneNumbers.m_nPhoneId != DNC)
	{
		if(m_strFilter.GetLength())
			m_strFilter += _T(" AND ");

		szColFilter.Format(_T("PHONE_ID = %d"), oSubscrPhoneNmbPhoneNumbers.m_nPhoneId);
		m_strFilter += szColFilter;
	}
	if(oSubscrPhoneNmbPhoneNumbers.m_nSubscrId != DNC)
	{
		if(m_strFilter.GetLength())
			m_strFilter += _T(" AND ");

		szColFilter.Format(_T("SUBSCRIBER_ID = %d"), oSubscrPhoneNmbPhoneNumbers.m_nSubscrId);
		m_strFilter += szColFilter;
	}
	if(_tcslen(oSubscrPhoneNmbPhoneNumbers.m_szPhoneNumber))
	{
		if(m_strFilter.GetLength())
			m_strFilter += _T(" AND ");

		szColFilter.Format(_T("PHONE_NUMB = '%s'"), oSubscrPhoneNmbPhoneNumbers.m_szPhoneNumber);
		m_strFilter += szColFilter;
	}	

	try
	{
		Open(CRecordset::dynaset);

		if(IsBOF())
			return FALSE; 
	}
	catch(CDBException *)
	{
		return FALSE;
	}

	return TRUE;
}



void const CSubscriberPhoneNumbersTable::DoExchangeFromDatabaseData(CSubscriberPhoneNumbers &oSubscrPhoneNmb)
{
	oSubscrPhoneNmb.m_nId = m_nID;
	oSubscrPhoneNmb.m_nRevNumb = m_REV_NUMB;
	oSubscrPhoneNmb.m_nSubscrId =	m_SUBSCRIBER_ID;
	oSubscrPhoneNmb.m_nPhoneId = m_PHONE_ID;
	_tcscpy(oSubscrPhoneNmb.m_szPhoneNumber, m_PHONE_NUMB);
}

void CSubscriberPhoneNumbersTable::DoExchangeТоDatabaseData(const CSubscriberPhoneNumbers &oSubscrPhoneNmb)
{
	m_nID = oSubscrPhoneNmb.m_nId;
	m_REV_NUMB = oSubscrPhoneNmb.m_nRevNumb;
	m_SUBSCRIBER_ID = oSubscrPhoneNmb.m_nSubscrId;
	m_PHONE_ID = oSubscrPhoneNmb.m_nPhoneId;
	m_PHONE_NUMB = oSubscrPhoneNmb.m_szPhoneNumber;	
}

/////////////////////////////////////////////////////////////////////////////
// CSubscriberPhoneNumbersTable diagnostics

#ifdef _DEBUG
void CSubscriberPhoneNumbersTable::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSubscriberPhoneNumbersTable::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

