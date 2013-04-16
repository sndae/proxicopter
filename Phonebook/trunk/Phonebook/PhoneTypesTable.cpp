// PhoneTypesTable.cpp : implementation of the CPhoneTypesTable class
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "PhoneTypesTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPhoneTypesTable implementation

// code generated on 05 март 2013 г., 19:08 ч.

IMPLEMENT_DYNAMIC(CPhoneTypesTable, CRecordset)

CPhoneTypesTable::CPhoneTypesTable(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_nID = 0;
	m_REV_NUMB = 0;
	m_oCode = 0;
	m_PHONE_TYPE = L"";
	m_nFields = 4;
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
CString CPhoneTypesTable::GetDefaultConnect()
{
	if(m_bSQLEn)
		return _T("DSN=SQLExpress;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=PROXIMUS-PC;DATABASE=phonebook");
	else
		return EMPTY_STRING;
}

CString CPhoneTypesTable::GetDefaultSQL()
{
	if(m_bSQLEn)
		return _T("[dbo].[PHONE_TYPES]");
	else
		return _T("[PHONE_TYPES$]");
}

void CPhoneTypesTable::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	// Macros such as RFX_Text() and RFX_Int() are dependent on the
	// type of the member variable, not the type of the field in the database.
	// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ID]"), m_nID);
	RFX_Long(pFX, _T("[REV_NUMB]"), m_REV_NUMB);
	RFX_Long(pFX, _T("[CODE]"), m_oCode);
	RFX_Text(pFX, _T("[PHONE_TYPE]"), m_PHONE_TYPE);
}

BOOL const CPhoneTypesTable::SelectAll(CPhoneTypesArray &oPhoneTypesArray)
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
		// този път със запитване на потребителят. Очаква се че ще се окаже XLS файл 
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
				oPhoneTypesArray.Add(new CPhoneTypes(int(m_nID), int(m_REV_NUMB), int(m_oCode), m_PHONE_TYPE.GetBuffer()));		 
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

BOOL const CPhoneTypesTable::SelectWhereId(const int iId, CPhoneTypes &oPhoneTypes)
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

		DoExchangeFromDatabaseData(oPhoneTypes);
	}
	catch(CDBException *)
	{
		return FALSE;
	}

	return TRUE;	
}

BOOL CPhoneTypesTable::UpdateWhereId(const int iId, const CPhoneTypes &oPhoneTypes)
{
	// Проверка дали има друг запис със такъв код 
	if(SelectByContent(CPhoneTypes(oPhoneTypes.m_nId, oPhoneTypes.m_nRevNumb, oPhoneTypes.m_nCode)))
		return FALSE;

	// Проверка дали има друг запис със такъв тип 
	if(SelectByContent(CPhoneTypes(oPhoneTypes.m_nId, oPhoneTypes.m_nRevNumb, DNC, oPhoneTypes.m_szType)))
		return FALSE;

	CPhoneTypes oCurrPhoneType;
	if(!SelectWhereId(iId, oCurrPhoneType))
		return FALSE;
	
	if(oCurrPhoneType.m_nRevNumb != oPhoneTypes.m_nRevNumb)
		return FALSE;

	try
	{
		MoveFirst();	
		Edit();

		DoExchangeТоDatabaseData(CPhoneTypes(oPhoneTypes.m_nId, oCurrPhoneType.m_nRevNumb + 1, oPhoneTypes.m_nCode, oPhoneTypes.m_szType));

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

BOOL CPhoneTypesTable::Insert(const CPhoneTypes &oPhoneTypes)
{
	if(!CanAppend())
		return FALSE;

	// Проверка дали има запис с такъв код на	
	if(SelectByContent(CPhoneTypes(DNC, 0, oPhoneTypes.m_nCode)))
		return FALSE;

	// Проверка дали има запис със такъв тип телефон
	if(SelectByContent(CPhoneTypes(DNC, 0, DNC, oPhoneTypes.m_szType)))
		return FALSE;

	Close();
	m_strFilter = EMPTY_STRING;
	m_strSort = EMPTY_STRING;
	try
	{
		Open(CRecordset::dynaset);

		if(!IsBOF())
			MoveLast();	
		// буфериране ID на последният ред от раблицата  
		int iLastRowId = m_nID;
		AddNew();

		DoExchangeТоDatabaseData(CPhoneTypes(iLastRowId + 1, 0, oPhoneTypes.m_nCode, oPhoneTypes.m_szType));

		Update();
	}
	catch(CDBException *)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPhoneTypesTable::DeleteWhereId(const int iId)
{
	CPhoneTypes oPhoneTypes;
	if(!SelectWhereId(iId, oPhoneTypes))
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

BOOL CPhoneTypesTable::SortByColumn(const eColumn eCol, const BOOL bAsc, const BOOL bResetFilter)
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
	case eColType:
		bAsc ? m_strSort.Format(_T("%s ASC"), _T("PHONE_TYPE")): m_strSort.Format(_T("%s DESC"), _T("PHONE_TYPE"));
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

BOOL CPhoneTypesTable::SelectByContent(const CPhoneTypes &oPhoneTypes)
{
	if(IsOpen())
		Close(); 

	m_strSort = EMPTY_STRING;
	m_strFilter = EMPTY_STRING;
	CString szColFilter;
	if(oPhoneTypes.m_nId != DNC)
	{
		// изключване на текущият запис от по-нататъшното филтриране 
		szColFilter.Format(_T("ID != %d"), oPhoneTypes.m_nId);
		m_strFilter += szColFilter;
	}
	// формиране на низ за филтриране, на база наличните в структурата ненулеви записи 
	if(oPhoneTypes.m_nCode != DNC)
	{
		if(m_strFilter.GetLength())
			m_strFilter += _T(" AND ");

		szColFilter.Format(_T("CODE = %d"), oPhoneTypes.m_nCode);
		m_strFilter += szColFilter;
	}
	if(_tcslen(oPhoneTypes.m_szType))
	{
		if(m_strFilter.GetLength())
			m_strFilter += _T(" AND ");

		szColFilter.Format(_T("PHONE_TYPE = '%s'"), oPhoneTypes.m_szType);
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

void CPhoneTypesTable::DoExchangeТоDatabaseData(const CPhoneTypes &oPhoneType)
{
	m_nID = oPhoneType.m_nId;
	m_REV_NUMB = 0;
	m_oCode = oPhoneType.m_nCode;
	m_PHONE_TYPE = oPhoneType.m_szType;
}

void const CPhoneTypesTable::DoExchangeFromDatabaseData(CPhoneTypes &oPhoneType)
{
	oPhoneType.m_nId = m_nID;
	oPhoneType.m_nRevNumb = m_REV_NUMB;
	oPhoneType.m_nCode =	m_oCode;
	_tcscpy(oPhoneType.m_szType, m_PHONE_TYPE);
}

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesTable diagnostics

#ifdef _DEBUG
void CPhoneTypesTable::AssertValid() const
{
	CRecordset::AssertValid();
}

void CPhoneTypesTable::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

