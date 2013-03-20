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
  	return _T("[dbo].[SubscriberPhoneNumbers]");
  else
    return _T("[SubscriberPhoneNumbers$]");
}

void CSubscriberPhoneNumbersTable::DoFieldExchange(CFieldExchange* pFX)
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

BOOL CSubscriberPhoneNumbersTable::SelectAll(CSubscriberPhoneNumbersArray &oSubscriberPhoneNumbersArray)
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
      CSubscriberPhoneNumbers *poSubscriberPhoneNumbers = new CSubscriberPhoneNumbers(int(m_ID), int(m_REV_NUMB), m_CODE, GetCityCodeByCityId(m_CITY_ID), m_FIRST_NAME.GetBuffer(), m_SECOND_NAME.GetBuffer(), 
                                                     m_THIRD_NAME.GetBuffer(), m_IDENT_NUMB.GetBuffer(), m_CITY_ADDR.GetBuffer());
      oSubscriberPhoneNumbersArray.Add(poSubscriberPhoneNumbers);     
      MoveNext();
    }
  }

  return TRUE;
}

BOOL CSubscriberPhoneNumbersTable::SelectWhereId(const int iId, CSubscriberPhoneNumbers &oSubscriberPhoneNumbers)
{
  if(IsOpen())
    Close(); 

  m_strFilter.Format(_T("ID = %d"), iId);
  Open(CRecordset::dynaset);

  if(IsBOF())
    return FALSE; 

  MoveFirst();

  DoExchangeFromDatabaseData(oSubscriberPhoneNumbers);
  
  return TRUE;  
}

BOOL CSubscriberPhoneNumbersTable::UpdateWhereId(const int iId, const CSubscriberPhoneNumbers &oSubscriberPhoneNumbers)
{
  /* Проверка дали има друг абонат със такъв код */
  if(SelectByContent(CSubscriberPhoneNumbers(oSubscriberPhoneNumbers.m_iId, 0, oSubscriberPhoneNumbers.m_iCode)) == TRUE)
    return FALSE;

  /* Проверка дали има запис със такова ЕГН на абонат */
  if(SelectByContent(CSubscriberPhoneNumbers(oSubscriberPhoneNumbers.m_iId, 0, DNC, 0, 0, 0, 0, oSubscriberPhoneNumbers.m_szIDNumb)) == TRUE)
    return FALSE;

  CSubscriberPhoneNumbers oCurrSubscriber;
  if(SelectWhereId(iId, oCurrSubscriber) == FALSE)
    return FALSE;
  
  if(oCurrSubscriber.m_iRevNumb != oSubscriberPhoneNumbers.m_iRevNumb)
    return FALSE;

  MoveFirst();  
  Edit();

  CSubscriberPhoneNumbers oSubscrCopy = oSubscriberPhoneNumbers;
  oSubscrCopy.m_iRevNumb = oCurrSubscriber.m_iRevNumb + 1;
  
  DoExchangeТоDatabaseData(oSubscrCopy);

  Update();

  m_strFilter = _T("");
  m_strSort = _T("");

  return TRUE;
}

BOOL CSubscriberPhoneNumbersTable::Insert(const CSubscriberPhoneNumbers &oSubscriberPhoneNumbers)
{
  if(!CanAppend())
    return FALSE;

  /* Проверка дали има запис с такъв код на абонат */
  if(SelectByContent(CSubscriberPhoneNumbers(DNC, 0, oSubscriberPhoneNumbers.m_iCode)) == TRUE)
    return FALSE;

  /* Проверка дали има запис със такова ЕГН на абонат */
  if(SelectByContent(CSubscriberPhoneNumbers(DNC, 0, DNC, 0, 0, 0, 0, oSubscriberPhoneNumbers.m_szIDNumb)) == TRUE)
    return FALSE;

  Close();
  m_strFilter = _T("");
  m_strSort = _T("");
  Open(CRecordset::dynaset);

  MoveLast();  
  /* буфериране ID на последният ред от раблицата */ 
  int iLastRowId = m_ID;
  AddNew();

  CSubscriberPhoneNumbers oSubscrCopy = oSubscriberPhoneNumbers;
  oSubscrCopy.m_iId = iLastRowId + 1;
  oSubscrCopy.m_iRevNumb = 0;

  DoExchangeТоDatabaseData(oSubscrCopy);

  Update();

  return TRUE;
}

BOOL CSubscriberPhoneNumbersTable::DeleteWhereId(const int iId)
{
  CSubscriberPhoneNumbers oSubscriberPhoneNumbers;
  if(SelectWhereId(iId, oSubscriberPhoneNumbers) == FALSE)
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

  Open(CRecordset::dynaset);

  return TRUE;
}

CString CSubscriberPhoneNumbersTable::GetCityCodeByCityId(const int iCityId)
{
  CCities oCity;
  if(!m_oCitiesTable.SelectWhereId(iCityId, oCity))
    return FALSE;

  return CString(oCity.m_szCode);
}

int CSubscriberPhoneNumbersTable::GetCityIdByCityCode(const TCHAR *pszCityCode)
{
  if(!m_oCitiesTable.SelectByContent(CCities(DNC, 0, pszCityCode)))
    return DNC;
  
  CCitiesArray apCities;
  if(!m_oCitiesTable.SelectAll(apCities))
    return DNC;

  return apCities[0]->m_iId;
}



BOOL CSubscriberPhoneNumbersTable::SelectByContent(const CSubscriberPhoneNumbers &oSubscriberPhoneNumbers)
{
  if(IsOpen())
    Close(); 

  m_strSort = _T("");
  m_strFilter = _T("");
  CString szColFilter;
  if(oSubscriberPhoneNumbers.m_iId != DNC)
  {
    /* изключване на текущият запис от по-нататъшното филтриране */
    szColFilter.Format(_T("ID != %d"), oSubscriberPhoneNumbers.m_iId);
    m_strFilter += szColFilter;
  }
  /* формиране на низ за филтриране, на база наличните в структурата ненулеви записи */
  if(oSubscriberPhoneNumbers.m_iCode != DNC)
  {
    if(m_strFilter.GetLength())
      m_strFilter += _T(" AND ");

    szColFilter.Format(_T("CODE = %d"), oSubscriberPhoneNumbers.m_iCode);
    m_strFilter += szColFilter;
  }
  if(_tcslen(oSubscriberPhoneNumbers.m_szFirstName))
  {
    if(m_strFilter.GetLength())
      m_strFilter += _T(" AND ");

    szColFilter.Format(_T("FIRST_NAME = '%s'"), oSubscriberPhoneNumbers.m_szFirstName);
    m_strFilter += szColFilter;
  }
  if(_tcslen(oSubscriberPhoneNumbers.m_szSecondName))
  {
    if(m_strFilter.GetLength())
      m_strFilter += _T(" AND ");

    szColFilter.Format(_T("SECOND_NAME = '%s'"), oSubscriberPhoneNumbers.m_szSecondName);
    m_strFilter += szColFilter;
  }
  if(_tcslen(oSubscriberPhoneNumbers.m_szThirdName))
  {
    if(m_strFilter.GetLength())
      m_strFilter += _T(" AND ");

    szColFilter.Format(_T("THIRD_NAME = '%s'"), oSubscriberPhoneNumbers.m_szThirdName);
    m_strFilter += szColFilter;
  }
  if(_tcslen(oSubscriberPhoneNumbers.m_szIDNumb))
  {
    if(m_strFilter.GetLength())
      m_strFilter += _T(" AND ");

    szColFilter.Format(_T("IDENT_NUMB = '%s'"), oSubscriberPhoneNumbers.m_szIDNumb);
    m_strFilter += szColFilter;
  }
  if(_tcslen(oSubscriberPhoneNumbers.m_szCityCode))
  {
    if(m_strFilter.GetLength())
      m_strFilter += _T(" AND ");

    //szColFilter.Format(_T("CITY_ID = '%s'"), oSubscriberPhoneNumbers.m_iCityId);
    //m_strFilter += szColFilter;
  }
  if(_tcslen(oSubscriberPhoneNumbers.m_szAddress))
  {
    if(m_strFilter.GetLength())
      m_strFilter += _T(" AND ");

    szColFilter.Format(_T("CITY_ADDR = '%s'"), oSubscriberPhoneNumbers.m_szAddress);
    m_strFilter += szColFilter;
  }

  Open(CRecordset::dynaset);

  if(IsBOF())
    return FALSE; 

  return TRUE;
}

BOOL CSubscriberPhoneNumbersTable::SelectAllCityCodes(CCitiesArray &oCitiesArray)
{
  if(!m_oCitiesTable.SelectByContent(CCities(DNC)))
    return FALSE;

  if(!m_oCitiesTable.SelectAll(oCitiesArray))
    return FALSE;

  return TRUE;
}

void CSubscriberPhoneNumbersTable::DoExchangeFromDatabaseData(CSubscriberPhoneNumbers &oSubscriber)
{
  oSubscriber.m_iId = m_ID;
  oSubscriber.m_iRevNumb = m_REV_NUMB;
  oSubscriber.m_iCode =  m_CODE;
  _tcscpy(oSubscriber.m_szFirstName,  m_FIRST_NAME);
  _tcscpy(oSubscriber.m_szSecondName, m_SECOND_NAME);
  _tcscpy(oSubscriber.m_szThirdName,  m_THIRD_NAME);
  _tcscpy(oSubscriber.m_szIDNumb,     m_IDENT_NUMB);
  _tcscpy(oSubscriber.m_szCityCode, GetCityCodeByCityId(m_CITY_ID));
  _tcscpy(oSubscriber.m_szAddress, m_CITY_ADDR);

}

void CSubscriberPhoneNumbersTable::DoExchangeТоDatabaseData(const CSubscriberPhoneNumbers &oSubscriber)
{
  m_ID = oSubscriber.m_iId;
  m_REV_NUMB = oSubscriber.m_iRevNumb;
  m_CODE = oSubscriber.m_iCode;
  m_FIRST_NAME = oSubscriber.m_szFirstName;  
  m_SECOND_NAME = oSubscriber.m_szSecondName; 
  m_THIRD_NAME = oSubscriber.m_szThirdName;  
  m_IDENT_NUMB = oSubscriber.m_szIDNumb;	 
  m_CITY_ID = GetCityIdByCityCode(oSubscriber.m_szCityCode);     
  m_CITY_ADDR	= oSubscriber.m_szAddress; 

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

