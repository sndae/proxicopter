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

  bSQLEn = TRUE;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CCitiesTable::GetDefaultConnect()
{
	return _T("DSN=SQLExpress;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=PROXIMUS-PC;DATABASE=phonebook");
}

CString CCitiesTable::GetDefaultSQL()
{
  if(bSQLEn)
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
  if(!IsOpen())
    Open(CRecordset::dynaset);
  
  if(!IsBOF())
  {
    while(!IsEOF())
    {
      CCities *poCity = new CCities(int(m_ID), int(m_REV_NUMB), m_CODE.GetBuffer(), m_NAME.GetBuffer(), m_AREA.GetBuffer());
      oCitiesArray.Add(poCity);     
      MoveNext();
    }
  }

  return TRUE;
}

BOOL CCitiesTable::SelectWhereId(const int iId, CCities &oCity)
{
  if(IsOpen())
    Close(); 

  m_strFilter = _T("ID = ");
  m_strFilter.Format(_T("%d"), iId);
  Open(CRecordset::dynaset);

  if(IsBOF())
    return FALSE; 

  MoveFirst();
  oCity.m_iId = m_ID;
  oCity.m_iRevNumb = m_REV_NUMB;
  _tcscpy(oCity.m_szCode, m_CODE);
  _tcscpy(oCity.m_szName, m_NAME);
  _tcscpy(oCity.m_szArea, m_AREA); 

  return TRUE;  
}

BOOL CCitiesTable::UpdateWhereId(const int iId, const CCities &oCity)
{
  CCities oNewCity = oCity;
  oNewCity.m_szArea[0] = 0;
  SelectByContent(oNewCity);
  if(IsBOF() == FALSE)
    return FALSE;
  
  CCities oCurrCity;
  if(SelectWhereId(iId, oCurrCity) == FALSE)
    return FALSE;
  
  if(oCurrCity.m_iRevNumb != oNewCity.m_iRevNumb)
    return FALSE;

  MoveFirst();  
  Edit();
  m_ID = oCity.m_iId;
  m_REV_NUMB = oCurrCity.m_iRevNumb + 1;
  m_CODE = oCity.m_szCode;
  m_NAME = oCity.m_szName;
  m_AREA = oCity.m_szArea; 

  Update();

  return TRUE;
}

BOOL CCitiesTable::Insert(const CCities &oCity)
{
  return TRUE;
}

BOOL CCitiesTable::DeleteWhereId(const int iId)
{
  CCities oCities;
  if(SelectWhereId(iId, oCities) == FALSE)
    return FALSE;
  
  if(!CanUpdate())
    return FALSE;

  Delete();

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

  Open(CRecordset::dynaset);

  return TRUE;
}

BOOL CCitiesTable::SelectByContent(const CCities &oCity)
{
  if(IsOpen())
    Close(); 

  m_strSort = _T("");
  CString szColFilter;
  if(_tcslen(oCity.m_szArea))
  {
    szColFilter.Format(_T("AREA LIKE '%%s%'"), oCity.m_szArea);
    m_strFilter += szColFilter;
  }
  if(_tcslen(oCity.m_szName))
  {
    if(m_strFilter.GetLength())
      m_strFilter += _T(" AND ");

    szColFilter.Format(_T("NAME LIKE '%%s%'"), oCity.m_szName);
  }

  Open(CRecordset::dynaset);

  if(IsBOF())
    return FALSE; 

  return TRUE;
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

