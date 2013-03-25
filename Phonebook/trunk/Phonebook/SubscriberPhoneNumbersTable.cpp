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
	m_ID = 0;
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
		return _T("");
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
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[REV_NUMB]"), m_REV_NUMB);
	RFX_Long(pFX, _T("[SUBSCRIBER_ID]"), m_SUBSCRIBER_ID);
	RFX_Long(pFX, _T("[PHONE_ID]"), m_PHONE_ID);
	RFX_Text(pFX, _T("[PHONE_NUMB]"), m_PHONE_NUMB);
}

BOOL CSubscriberPhoneNumbersTable::SelectAll(CSubscriberPhoneNumbersArray &oSubscrPhoneNmbPhoneNumbersArray)
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
		/* В случай на неуспех при отваряне на връзката по подразбиране се прави нов опит, 
			 този път със запитване на потребителят. Очаква се че ще се окаже XLS файл */
		m_bSQLEn = FALSE;
		bRes = Open(CRecordset::dynaset);
	}
		
	if(bRes && !IsBOF())
	{
		/* запъвлване на масива с указатели към данни на редове от таблицата */
		while(!IsEOF())
		{
			CSubscriberPhoneNumbers *poSubscrPhoneNmbPhoneNumbers = new CSubscriberPhoneNumbers(int(m_ID), int(m_REV_NUMB), GetSubscrCodeBySubscrId(m_SUBSCRIBER_ID), 
																								GetPhoneCodeByPhoneId(m_PHONE_ID), m_PHONE_NUMB);
			oSubscrPhoneNmbPhoneNumbersArray.Add(poSubscrPhoneNmbPhoneNumbers);		 
			MoveNext();
		}
	}

	return TRUE;
}

BOOL CSubscriberPhoneNumbersTable::SelectWhereId(const int iId, CSubscriberPhoneNumbers &oSubscrPhoneNmbPhoneNumbers)
{
	if(IsOpen())
		Close(); 

	m_strFilter.Format(_T("ID = %d"), iId);
	Open(CRecordset::dynaset);

	if(IsBOF())
		return FALSE; 

	MoveFirst();

	DoExchangeFromDatabaseData(oSubscrPhoneNmbPhoneNumbers);
	
	return TRUE;	
}

BOOL CSubscriberPhoneNumbersTable::UpdateWhereId(const int iId, const CSubscriberPhoneNumbers &oSubscrPhoneNmbPhoneNumbers)
{
//	/* Проверка дали има друг абонат със такъв код */
//	if(SelectByContent(CSubscriberPhoneNumbers(oSubscrPhoneNmbPhoneNumbers.m_iId, 0, oSubscrPhoneNmbPhoneNumbers.m_iCode)) == TRUE)
//		return FALSE;

//	/* Проверка дали има запис със такова ЕГН на абонат */
//	if(SelectByContent(CSubscriberPhoneNumbers(oSubscrPhoneNmbPhoneNumbers.m_iId, 0, DNC, 0, 0, 0, 0, oSubscrPhoneNmbPhoneNumbers.m_szIDNumb)) == TRUE)
//		return FALSE;

	CSubscriberPhoneNumbers oCurrSubscriber;
	if(SelectWhereId(iId, oCurrSubscriber) == FALSE)
		return FALSE;
	
	if(oCurrSubscriber.m_iRevNumb != oSubscrPhoneNmbPhoneNumbers.m_iRevNumb)
		return FALSE;

	MoveFirst();	
	Edit();

	CSubscriberPhoneNumbers oSubscrCopy = oSubscrPhoneNmbPhoneNumbers;
	oSubscrCopy.m_iRevNumb = oCurrSubscriber.m_iRevNumb + 1;
	
	DoExchangeТоDatabaseData(oSubscrCopy);

	Update();

	m_strFilter = _T("");
	m_strSort = _T("");

	return TRUE;
}

BOOL CSubscriberPhoneNumbersTable::Insert(const CSubscriberPhoneNumbers &oSubscrPhoneNmbPhoneNumbers)
{
	if(!CanAppend())
		return FALSE;

	Close();
	m_strFilter = _T("");
	m_strSort = _T("");
	Open(CRecordset::dynaset);

	MoveLast();	
	/* буфериране ID на последният ред от раблицата */ 
	int iLastRowId = m_ID;
	AddNew();

	CSubscriberPhoneNumbers oSubscrCopy = oSubscrPhoneNmbPhoneNumbers;
	oSubscrCopy.m_iId = iLastRowId + 1;
	oSubscrCopy.m_iRevNumb = 0;

	DoExchangeТоDatabaseData(oSubscrCopy);

	Update();

	return TRUE;
}

BOOL CSubscriberPhoneNumbersTable::DeleteWhereId(const int iId)
{
	CSubscriberPhoneNumbers oSubscrPhoneNmbPhoneNumbers;
	if(SelectWhereId(iId, oSubscrPhoneNmbPhoneNumbers) == FALSE)
	{
		m_strFilter = _T("");
		return FALSE;
	}
	
	if(!CanUpdate())
		return FALSE;

	Delete();
	m_strFilter = _T("");

	return TRUE;
}

BOOL CSubscriberPhoneNumbersTable::SortByColumn(const eColumn eCol, const BOOL bAsc)
{
	if(IsOpen())
		Close(); 

	m_strFilter = _T("");
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

	Open(CRecordset::dynaset);

	return TRUE;
}

int	CSubscriberPhoneNumbersTable::GetSubscrCodeBySubscrId(const int iId)
{
	CSubscribers oSubscriber;
	if(!m_oSubscribersTable.SelectWhereId(iId, oSubscriber))
		return DNC;

	return oSubscriber.m_iCode;
}

int	CSubscriberPhoneNumbersTable::GetSubscrIdBySubscrCode(const int iSubscrCode)
{	
	if(!m_oSubscribersTable.SelectByContent(CSubscribers(DNC, 0, iSubscrCode)))
		return DNC;

	CSubscribersArray oPtrToSubscrsArray;
	if(!m_oSubscribersTable.SelectAll(oPtrToSubscrsArray))
		return DNC;

	return oPtrToSubscrsArray[0]->m_iId;
}

int	CSubscriberPhoneNumbersTable::GetPhoneCodeByPhoneId(const int iId)
{
	CPhoneTypes oPhoneType;
	if(!m_oPhoneTypesTable.SelectWhereId(iId, oPhoneType))
		return DNC;

	return oPhoneType.m_iCode;
}

int	CSubscriberPhoneNumbersTable::GetPhoneIdByPhoneCode(const int iPhoneCode)
{
	if(!m_oPhoneTypesTable.SelectByContent(CPhoneTypes(DNC, 0, iPhoneCode)))
		return DNC;

	CPhoneTypesArray oPtrToPhoneTypesArray;
	if(!m_oPhoneTypesTable.SelectAll(oPtrToPhoneTypesArray))
		return DNC;

	return oPtrToPhoneTypesArray[0]->m_iId;
}


BOOL CSubscriberPhoneNumbersTable::SelectByContent(const CSubscriberPhoneNumbers &oSubscrPhoneNmbPhoneNumbers)
{
	if(IsOpen())
		Close(); 

	m_strSort = _T("");
	m_strFilter = _T("");
	CString szColFilter;
	if(oSubscrPhoneNmbPhoneNumbers.m_iId != DNC)
	{
		/* изключване на текущият запис от по-нататъшното филтриране */
		szColFilter.Format(_T("ID != %d"), oSubscrPhoneNmbPhoneNumbers.m_iId);
		m_strFilter += szColFilter;
	}
	/* формиране на низ за филтриране, на база наличните в структурата ненулеви записи */
	if(oSubscrPhoneNmbPhoneNumbers.m_iPhoneCode != DNC)
	{
		if(m_strFilter.GetLength())
			m_strFilter += _T(" AND ");

		szColFilter.Format(_T("PHONE_ID = %d"), GetPhoneIdByPhoneCode(oSubscrPhoneNmbPhoneNumbers.m_iPhoneCode));
		m_strFilter += szColFilter;
	}
	if(oSubscrPhoneNmbPhoneNumbers.m_iSubscrCode != DNC)
	{
		if(m_strFilter.GetLength())
			m_strFilter += _T(" AND ");

		szColFilter.Format(_T("SUBSCRIBER_ID = %d"), GetSubscrIdBySubscrCode(oSubscrPhoneNmbPhoneNumbers.m_iSubscrCode));
		m_strFilter += szColFilter;
	}
	if(_tcslen(oSubscrPhoneNmbPhoneNumbers.m_szPhoneNumber))
	{
		if(m_strFilter.GetLength())
			m_strFilter += _T(" AND ");

		szColFilter.Format(_T("PHONE_NUMB = '%s'"), oSubscrPhoneNmbPhoneNumbers.m_szPhoneNumber);
		m_strFilter += szColFilter;
	}	

	Open(CRecordset::dynaset);

	if(IsBOF())
		return FALSE; 

	return TRUE;
}

BOOL CSubscriberPhoneNumbersTable::SelectAllSubscribersCodes(CSubscribersArray &oSubscribersArray)
{
	if(!m_oSubscribersTable.SelectByContent(CSubscribers(DNC)))
		return FALSE;

	if(!m_oSubscribersTable.SelectAll(oSubscribersArray))
		return FALSE;

	return TRUE;
}

BOOL CSubscriberPhoneNumbersTable::SelectAllPhoneTypesCodes(CPhoneTypesArray &oPhoneTypesArray)
{
	if(!m_oPhoneTypesTable.SelectByContent(CPhoneTypes(DNC)))
		return FALSE;

	if(!m_oPhoneTypesTable.SelectAll(oPhoneTypesArray))
		return FALSE;

	return TRUE;
}


void CSubscriberPhoneNumbersTable::DoExchangeFromDatabaseData(CSubscriberPhoneNumbers &oSubscrPhoneNmb)
{
	oSubscrPhoneNmb.m_iId = m_ID;
	oSubscrPhoneNmb.m_iRevNumb = m_REV_NUMB;
	oSubscrPhoneNmb.m_iSubscrCode =	GetSubscrCodeBySubscrId(m_SUBSCRIBER_ID);
	oSubscrPhoneNmb.m_iPhoneCode = GetPhoneCodeByPhoneId(m_PHONE_ID);
	_tcscpy(oSubscrPhoneNmb.m_szPhoneNumber, m_PHONE_NUMB);
}

void CSubscriberPhoneNumbersTable::DoExchangeТоDatabaseData(const CSubscriberPhoneNumbers &oSubscrPhoneNmb)
{
	m_ID = oSubscrPhoneNmb.m_iId;
	m_REV_NUMB = oSubscrPhoneNmb.m_iRevNumb;
	m_SUBSCRIBER_ID = GetSubscrIdBySubscrCode(oSubscrPhoneNmb.m_iSubscrCode);
	m_PHONE_ID = GetPhoneIdByPhoneCode(oSubscrPhoneNmb.m_iPhoneCode);
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

