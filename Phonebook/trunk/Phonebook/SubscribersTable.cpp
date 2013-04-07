// SubscribersTable.cpp : implementation of the CSubscribersTable class
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "SubscribersTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSubscribersTable implementation

// code generated on 05 март 2013 г., 19:08 ч.

IMPLEMENT_DYNAMIC(CSubscribersTable, CRecordset)

CSubscribersTable::CSubscribersTable(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_REV_NUMB = 0;
	m_CODE = 0;
	m_FIRST_NAME = L"";
	m_SECOND_NAME = L"";
	m_THIRD_NAME = L"";
	m_IDENT_NUMB = L"";
	m_CITY_ID = 0;
	m_CITY_ADDR	= L"";
	
	m_nFields = 9;
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
CString CSubscribersTable::GetDefaultConnect()
{
	if(m_bSQLEn)
		return _T("DSN=SQLExpress;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=PROXIMUS-PC;DATABASE=phonebook");
	else
		return _T("");
}

CString CSubscribersTable::GetDefaultSQL()
{
	if(m_bSQLEn)
		return _T("[dbo].[SUBSCRIBERS]");
	else
		return _T("[SUBSCRIBERS$]");
}

void CSubscribersTable::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	// Macros such as RFX_Text() and RFX_Int() are dependent on the
	// type of the member variable, not the type of the field in the database.
	// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[REV_NUMB]"), m_REV_NUMB);
	RFX_Long(pFX, _T("[CODE]"), m_CODE);
	RFX_Text(pFX, _T("[FIRST_NAME]"), m_FIRST_NAME);
	RFX_Text(pFX, _T("[SECOND_NAME]"), m_SECOND_NAME);
	RFX_Text(pFX, _T("[THIRD_NAME]"), m_THIRD_NAME);
	RFX_Text(pFX, _T("[IDENT_NUMB]"), m_IDENT_NUMB);
	RFX_Long(pFX, _T("[CITY_ID]"), m_CITY_ID);
	RFX_Text(pFX, _T("[CITY_ADDR]"), m_CITY_ADDR);
}

BOOL CSubscribersTable::SelectAll(CSubscribersArray &oSubscribersArray)
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
		
	try
	{
		if(bRes && !IsBOF())
		{
			/* запъвлване на масива с указатели към данни на редове от таблицата */
			while(!IsEOF())
			{
				CSubscribers *poSubscribers = new CSubscribers(int(m_ID), int(m_REV_NUMB), m_CODE, m_CITY_ID, m_FIRST_NAME.GetBuffer(), m_SECOND_NAME.GetBuffer(), 
																m_THIRD_NAME.GetBuffer(), m_IDENT_NUMB.GetBuffer(), m_CITY_ADDR.GetBuffer());
				oSubscribersArray.Add(poSubscribers);		 
				MoveNext();
			}
		}
	}
	catch(CDBException *)
	{
		//return FALSE;
	}

	return TRUE;
}

BOOL CSubscribersTable::SelectWhereId(const int iId, CSubscribers &oSubscribers)
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

		DoExchangeFromDatabaseData(oSubscribers);
	}
	catch(CDBException *)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSubscribersTable::UpdateWhereId(const int iId, const CSubscribers &oSubscribers)
{
	/* Проверка дали има друг абонат със такъв код */
	if(SelectByContent(CSubscribers(oSubscribers.m_iId, 0, oSubscribers.m_iCode)) == TRUE)
		return FALSE;

	/* Проверка дали има запис със такова ЕГН на абонат */
	if(SelectByContent(CSubscribers(oSubscribers.m_iId, 0, DNC, 0, 0, 0, 0, oSubscribers.m_szIDNumb)) == TRUE)
		return FALSE;

	CSubscribers oCurrSubscriber;
	if(SelectWhereId(iId, oCurrSubscriber) == FALSE)
		return FALSE;
	
	if(oCurrSubscriber.m_iRevNumb != oSubscribers.m_iRevNumb)
		return FALSE;

	try
	{
		MoveFirst();
		Edit();

		CSubscribers oSubscrCopy = oSubscribers;
		oSubscrCopy.m_iRevNumb = oCurrSubscriber.m_iRevNumb + 1;
		
		DoExchangeТоDatabaseData(oSubscrCopy);

		Update();
	}
	catch(CDBException *)
	{
		m_strFilter = _T("");
		m_strSort = _T("");

		return FALSE;
	}

	m_strFilter = _T("");
	m_strSort = _T("");

	return TRUE;
}

BOOL CSubscribersTable::Insert(CSubscribers &oSubscribers)
{
	if(!CanAppend())
		return FALSE;

	/* Проверка дали има запис с такъв код на абонат */
	if(SelectByContent(CSubscribers(DNC, 0, oSubscribers.m_iCode)) == TRUE)
		return FALSE;

	/* Проверка дали има запис със такова ЕГН на абонат */
	if(SelectByContent(CSubscribers(DNC, 0, DNC, 0, 0, 0, 0, oSubscribers.m_szIDNumb)) == TRUE)
		return FALSE;

	Close();
	m_strFilter = _T("");
	m_strSort = _T("");
	Open(CRecordset::dynaset);

	try
	{
		if(!IsBOF())
			MoveLast();	
		/* буфериране ID на последният ред от раблицата */ 
		int iLastRowId = m_ID;
		AddNew();

		oSubscribers.m_iId = iLastRowId + 1;
		oSubscribers.m_iRevNumb = 0;

		DoExchangeТоDatabaseData(oSubscribers);

		Update();
	}
	catch(CDBException *)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CSubscribersTable::DeleteWhereId(const int iId)
{
	CSubscribers oSubscribers;
	if(SelectWhereId(iId, oSubscribers) == FALSE)
	{
		m_strFilter = _T("");
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
		m_strFilter = _T("");
		return FALSE;
	}
	
	m_strFilter = _T("");
	return TRUE;
}

BOOL CSubscribersTable::SortByColumn(const eColumn eCol, const BOOL bAsc)
{
	if(IsOpen())
		Close(); 

	m_strFilter = _T("");
	switch(eCol)
	{
	case eColCode:		
		bAsc ? m_strSort.Format(_T("%s ASC"), _T("CODE")): m_strSort.Format(_T("%s DESC"), _T("CODE"));
		break;
	case eColFirstName:
		bAsc ? m_strSort.Format(_T("%s ASC"), _T("FIRST_NAME")): m_strSort.Format(_T("%s DESC"), _T("FIRST_NAME"));
		break;
	case eColSecondName:
		bAsc ? m_strSort.Format(_T("%s ASC"), _T("SECOND_NAME")): m_strSort.Format(_T("%s DESC"), _T("SECOND_NAME"));
		break;
	case eColThirdName:
		bAsc ? m_strSort.Format(_T("%s ASC"), _T("THIRD_NAME")): m_strSort.Format(_T("%s DESC"), _T("THIRD_NAME"));
		break;
	case eColIDNumb:
		bAsc ? m_strSort.Format(_T("%s ASC"), _T("IDENT_NUMB")): m_strSort.Format(_T("%s DESC"), _T("IDENT_NUMB"));
		break;
	case eColAddress:
		bAsc ? m_strSort.Format(_T("%s ASC"), _T("CITY_ADDR")): m_strSort.Format(_T("%s DESC"), _T("CITY_ADDR"));
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

BOOL CSubscribersTable::SelectByContent(const CSubscribers &oSubscribers)
{
	if(IsOpen())
		Close(); 

	m_strSort = _T("");
	m_strFilter = _T("");
	CString szColFilter;
	if(oSubscribers.m_iId != DNC)
	{
		/* изключване на текущият запис от по-нататъшното филтриране */
		szColFilter.Format(_T("ID != %d"), oSubscribers.m_iId);
		m_strFilter += szColFilter;
	}
	/* формиране на низ за филтриране, на база наличните в структурата ненулеви записи */
	if(oSubscribers.m_iCode != DNC)
	{
		if(m_strFilter.GetLength())
			m_strFilter += _T(" AND ");

		szColFilter.Format(_T("CODE = %d"), oSubscribers.m_iCode);
		m_strFilter += szColFilter;
	}
	if(_tcslen(oSubscribers.m_szFirstName))
	{
		if(m_strFilter.GetLength())
			m_strFilter += _T(" AND ");

		szColFilter.Format(_T("FIRST_NAME = '%s'"), oSubscribers.m_szFirstName);
		m_strFilter += szColFilter;
	}
	if(_tcslen(oSubscribers.m_szSecondName))
	{
		if(m_strFilter.GetLength())
			m_strFilter += _T(" AND ");

		szColFilter.Format(_T("SECOND_NAME = '%s'"), oSubscribers.m_szSecondName);
		m_strFilter += szColFilter;
	}
	if(_tcslen(oSubscribers.m_szThirdName))
	{
		if(m_strFilter.GetLength())
			m_strFilter += _T(" AND ");

		szColFilter.Format(_T("THIRD_NAME = '%s'"), oSubscribers.m_szThirdName);
		m_strFilter += szColFilter;
	}
	if(_tcslen(oSubscribers.m_szIDNumb))
	{
		if(m_strFilter.GetLength())
			m_strFilter += _T(" AND ");

		szColFilter.Format(_T("IDENT_NUMB = '%s'"), oSubscribers.m_szIDNumb);
		m_strFilter += szColFilter;
	}
	if(oSubscribers.m_iCityId != DNC)
	{
		if(m_strFilter.GetLength())
			m_strFilter += _T(" AND ");

		szColFilter.Format(_T("CITY_ID = %d"), oSubscribers.m_iCityId);
		m_strFilter += szColFilter;
	}
	if(_tcslen(oSubscribers.m_szAddress))
	{
		if(m_strFilter.GetLength())
			m_strFilter += _T(" AND ");

		szColFilter.Format(_T("CITY_ADDR = '%s'"), oSubscribers.m_szAddress);
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

void CSubscribersTable::DoExchangeFromDatabaseData(CSubscribers &oSubscriber)
{
	oSubscriber.m_iId = m_ID;
	oSubscriber.m_iRevNumb = m_REV_NUMB;
	oSubscriber.m_iCode =	m_CODE;
	_tcscpy(oSubscriber.m_szFirstName,	m_FIRST_NAME);
	_tcscpy(oSubscriber.m_szSecondName, m_SECOND_NAME);
	_tcscpy(oSubscriber.m_szThirdName,	m_THIRD_NAME);
	_tcscpy(oSubscriber.m_szIDNumb,		 m_IDENT_NUMB);
	oSubscriber.m_iCityId = m_CITY_ID;
	_tcscpy(oSubscriber.m_szAddress, m_CITY_ADDR);
}

void CSubscribersTable::DoExchangeТоDatabaseData(const CSubscribers &oSubscriber)
{
	m_ID = oSubscriber.m_iId;
	m_REV_NUMB = oSubscriber.m_iRevNumb;
	m_CODE = oSubscriber.m_iCode;
	m_FIRST_NAME = oSubscriber.m_szFirstName;	
	m_SECOND_NAME = oSubscriber.m_szSecondName; 
	m_THIRD_NAME = oSubscriber.m_szThirdName;	
	m_IDENT_NUMB = oSubscriber.m_szIDNumb;	 
	m_CITY_ID = oSubscriber.m_iCityId;		 
	m_CITY_ADDR	= oSubscriber.m_szAddress; 

}

/////////////////////////////////////////////////////////////////////////////
// CSubscribersTable diagnostics

#ifdef _DEBUG
void CSubscribersTable::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSubscribersTable::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

