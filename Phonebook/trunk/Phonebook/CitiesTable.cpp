// CitiesTable.cpp : implementation of the CCitiesTable class
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "CitiesTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

 
// CCitiesTable implementation

// code generated on 05 март 2013 г., 19:08 ч.

IMPLEMENT_DYNAMIC(CCitiesTable, CRecordset)

CCitiesTable::CCitiesTable(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_nID = 0;
	m_REV_NUMB = 0;
	m_oCode = L"";
	m_oName = L"";
	m_oArea = L"";
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
CString CCitiesTable::GetDefaultConnect()
{
	if(m_bSQLEn)
		return _T("DSN=SQLExpress;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=PROXIMUS-PC;DATABASE=phonebook");
	else
		return EMPTY_STRING;
}

CString CCitiesTable::GetDefaultSQL()
{
	if(m_bSQLEn)
		return _T("[dbo].[CITIES]");
	else
		return _T("[Cities$]");
}

void CCitiesTable::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	// Macros such as RFX_Text() and RFX_Int() are dependent on the
	// type of the member variable, not the type of the field in the database.
	// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_nID);
	RFX_Long(pFX, _T("[REV_NUMB]"), m_REV_NUMB);
	RFX_Text(pFX, _T("[CODE]"), m_oCode);
	RFX_Text(pFX, _T("[NAME]"), m_oName);
	RFX_Text(pFX, _T("[AREA]"), m_oArea);

}

BOOL const CCitiesTable::SelectAll(CCitiesArray &oCitiesArray)
{
	if(IsOpen())
		Close();
	
	BOOL bRes = FALSE;
	try
	{
	 bRes = Open(CRecordset::dynaset);
	}
	catch(CDBException *)
	{
		// В случай на неуспех при отваряне на връзката по подразбиране се прави нов опит, 
		//	този път със запитване на потребителят. Очаква се че ще се окаже XLS файл 
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
				oCitiesArray.Add(new CCities(int(m_nID), int(m_REV_NUMB), m_oCode.GetBuffer(), m_oName.GetBuffer(), m_oArea.GetBuffer()));		 
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

BOOL const CCitiesTable::SelectWhereId(const int iId, CCities &oCity)
{
	if(IsOpen())
		Close(); 

	m_strFilter.Format(_T("ID = %d"), iId);
	try
	{
		Open(CRecordset::dynaset);

		if(IsBOF())
			return FALSE; 

		MoveFirst();

		DoExchangeFromDatabaseData(oCity);
	}
	catch(CDBException *)
	{
		return FALSE;
	}
	return TRUE;	
}

BOOL CCitiesTable::UpdateWhereId(const int iId, const CCities &oCity)
{
	// Проверка дали има друг запис със такова име на град 
	if(SelectByContent(CCities(oCity.m_nId, oCity.m_nRevNumb, oCity.m_szCode)))
		return FALSE;

	// Проверка дали има друг запис със такъва код на град 
	if(SelectByContent(CCities(oCity.m_nId, oCity.m_nRevNumb, 0, oCity.m_szName)))
		return FALSE;

	CCities oCurrCity;
	if(!SelectWhereId(iId, oCurrCity))
		return FALSE;
	
	if(oCurrCity.m_nRevNumb != oCity.m_nRevNumb)
		return FALSE;

	try
	{
		MoveFirst();	
		Edit();

		DoExchangeТоDatabaseData(CCities(oCity.m_nId, oCurrCity.m_nRevNumb + 1, oCity.m_szCode, oCity.m_szName, oCity.m_szArea)); 

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

BOOL CCitiesTable::Insert(const CCities &oCity)
{
	if(!CanAppend())
		return FALSE;

	// Проверка дали има запис със такова име на град 
	if(SelectByContent(CCities(DNC, 0, oCity.m_szCode)))
		return FALSE;

	// Проверка дали има запис със такъв код на град 
	if(SelectByContent(CCities(DNC, 0, 0, oCity.m_szName)))
		return FALSE;

	Close();
	m_strFilter = EMPTY_STRING;
	m_strSort = EMPTY_STRING;
	Open(CRecordset::dynaset);

	if(!IsBOF())
		MoveLast();	 
	// буфериране ID на последният ред от раблицата	
	int iLastRowId = m_nID;
	try
	{
		AddNew();
		DoExchangeТоDatabaseData(CCities(iLastRowId + 1, 0, oCity.m_szCode, oCity.m_szName, oCity.m_szArea)); 
		Update();
	}
	catch(CDBException *)
	{
		return FALSE;
	}	
	return TRUE;
}

BOOL CCitiesTable::DeleteWhereId(const int iId)
{
	CCities oCities;
	if(!SelectWhereId(iId, oCities))
	{
		m_strFilter = EMPTY_STRING;
		return FALSE;
	}

	if(!CanUpdate())
		return FALSE;

	try
	{
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

BOOL CCitiesTable::SortByColumn(const eColumn eCol, const BOOL bAsc, const BOOL bResetFilter)
{
	if(IsOpen())
		Close(); 

	if(bResetFilter)
		m_strFilter = EMPTY_STRING;

	switch(eCol)
	{
		case eColCode:		
			bAsc ? m_strSort.Format(_T("%s ASC"), _T("CODE")): m_strSort.Format(_T("%s DESC"), _T("CODE"));
			break;
		case eColName:
			bAsc ? m_strSort.Format(_T("%s ASC"), _T("NAME")): m_strSort.Format(_T("%s DESC"), _T("NAME"));
			break;
		case eColArea:
			bAsc ? m_strSort.Format(_T("%s ASC"), _T("AREA")): m_strSort.Format(_T("%s DESC"), _T("AREA"));
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

BOOL CCitiesTable::SelectByContent(const CCities &oCity)
{
	if(IsOpen())
		Close(); 

	m_strSort = EMPTY_STRING;
	m_strFilter = EMPTY_STRING;
	CString szColFilter;
	if(oCity.m_nId != DNC)
	{
		// изключване на текущият запис от по-нататъшното филтриране 
		szColFilter.Format(_T("ID != %d"), oCity.m_nId);
		m_strFilter += szColFilter;
	}
	// формиране на низ за филтриране, на база наличните в структурата ненулеви записи 
	if(_tcslen(oCity.m_szCode))
	{
		if(m_strFilter.GetLength())
			m_strFilter += _T(" AND ");

		szColFilter.Format(_T("CODE = '%s'"), oCity.m_szCode);
		m_strFilter += szColFilter;
	}
	if(_tcslen(oCity.m_szName))
	{
		if(m_strFilter.GetLength())
			m_strFilter += _T(" AND ");

		szColFilter.Format(_T("NAME = '%s'"), oCity.m_szName);
		m_strFilter += szColFilter;
	}
	if(_tcslen(oCity.m_szArea))
	{
		if(m_strFilter.GetLength())
			m_strFilter += _T(" AND ");

		szColFilter.Format(_T("AREA = '%s'"), oCity.m_szArea);
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

void CCitiesTable::DoExchangeТоDatabaseData(const CCities &oCity)
{
	m_nID = oCity.m_nId;
	m_REV_NUMB = oCity.m_nRevNumb;
	m_oCode = oCity.m_szCode;
	m_oName = oCity.m_szName;
	m_oArea = oCity.m_szArea; 
}

void const CCitiesTable::DoExchangeFromDatabaseData(CCities &oCity)
{
	oCity.m_nId = m_nID;
	oCity.m_nRevNumb = m_REV_NUMB;
	_tcscpy(oCity.m_szCode, m_oCode);
	_tcscpy(oCity.m_szName, m_oName);
	_tcscpy(oCity.m_szArea, m_oArea); 

}
/////////////////////////////////////////////////////////////////////////////
// CCitiesTable diagnostics

#ifdef _DEBUG
void CCitiesTable::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCitiesTable::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

