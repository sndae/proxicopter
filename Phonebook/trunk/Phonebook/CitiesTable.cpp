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
  m_ID = 0;
  m_REV_NUMB = 0;
  m_CODE = L"";
  m_NAME = L"";
  m_AREA = L"";
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
    return _T("");
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
  RFX_Long(pFX, _T("[ID]"), m_ID);
  RFX_Long(pFX, _T("[REV_NUMB]"), m_REV_NUMB);
  RFX_Text(pFX, _T("[CODE]"), m_CODE);
  RFX_Text(pFX, _T("[NAME]"), m_NAME);
  RFX_Text(pFX, _T("[AREA]"), m_AREA);

}

BOOL CCitiesTable::SelectAll(CCitiesArray &oCitiesArray)
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
				CCities *poCity = new CCities(int(m_ID), int(m_REV_NUMB), m_CODE.GetBuffer(), m_NAME.GetBuffer(), m_AREA.GetBuffer());
				oCitiesArray.Add(poCity);     
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

BOOL CCitiesTable::SelectWhereId(const int iId, CCities &oCity)
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
  /* Проверка дали има друг запис със такова име на град */
  if(SelectByContent(CCities(oCity.m_iId, oCity.m_iRevNumb, oCity.m_szCode)) == TRUE)
    return FALSE;

  /* Проверка дали има друг запис със такъва код на град */
  if(SelectByContent(CCities(oCity.m_iId, oCity.m_iRevNumb, 0, oCity.m_szName)) == TRUE)
    return FALSE;

  CCities oCurrCity;
  if(SelectWhereId(iId, oCurrCity) == FALSE)
    return FALSE;
  
  if(oCurrCity.m_iRevNumb != oCity.m_iRevNumb)
    return FALSE;

	try
	{
		MoveFirst();  
		Edit();

		DoExchangeТоDatabaseData(CCities(oCity.m_iId, oCurrCity.m_iRevNumb + 1, oCity.m_szCode, oCity.m_szName, oCity.m_szArea)); 

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

BOOL CCitiesTable::Insert(const CCities &oCity)
{
  if(!CanAppend())
    return FALSE;

  /* Проверка дали има запис със такова име на град */
  if(SelectByContent(CCities(DNC, 0, oCity.m_szCode)) == TRUE)
    return FALSE;

  /* Проверка дали има запис със такъв код на град */
  if(SelectByContent(CCities(DNC, 0, 0, oCity.m_szName)) == TRUE)
    return FALSE;

  Close();
  m_strFilter = _T("");
  m_strSort = _T("");
  Open(CRecordset::dynaset);

  MoveLast();  
  /* буфериране ID на последният ред от раблицата */ 
  int iLastRowId = m_ID;
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
  if(SelectWhereId(iId, oCities) == FALSE)
  {
    m_strFilter = _T("");
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
		m_strFilter = _T("");
		return FALSE;
	}
  m_strFilter = _T("");

  return TRUE;
}

BOOL CCitiesTable::SortByColumn(const eColumn eCol, const BOOL bAsc)
{
  if(IsOpen())
    Close(); 

  m_strFilter = _T("");
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

  m_strSort = _T("");
  m_strFilter = _T("");
  CString szColFilter;
  if(oCity.m_iId != DNC)
  {
    /* изключване на текущият запис от по-нататъшното филтриране */
    szColFilter.Format(_T("ID != %d"), oCity.m_iId);
    m_strFilter += szColFilter;
  }
  /* формиране на низ за филтриране, на база наличните в структурата ненулеви записи */
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
  m_ID = oCity.m_iId;
  m_REV_NUMB = oCity.m_iRevNumb;
  m_CODE = oCity.m_szCode;
  m_NAME = oCity.m_szName;
  m_AREA = oCity.m_szArea; 
}

void CCitiesTable::DoExchangeFromDatabaseData(CCities &oCity)
{
  oCity.m_iId = m_ID;
  oCity.m_iRevNumb = m_REV_NUMB;
  _tcscpy(oCity.m_szCode, m_CODE);
  _tcscpy(oCity.m_szName, m_NAME);
  _tcscpy(oCity.m_szArea, m_AREA); 

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

