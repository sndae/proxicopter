// PersonDoc.cpp : implementation of the CPersonDoc class
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "Person.h"
#include "PersonDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPersonDoc

IMPLEMENT_DYNCREATE(CPersonDoc, CDocument)

BEGIN_MESSAGE_MAP(CPersonDoc, CDocument)
END_MESSAGE_MAP()


// CPersonDoc construction/destruction

CPersonDoc::CPersonDoc()
{
  // TODO: add one-time construction code here
}

CPersonDoc::~CPersonDoc()
{
}

BOOL CPersonDoc::OnNewDocument()
{
  if (!CDocument::OnNewDocument())
    return FALSE;

  // TODO: add reinitialization code here
  // (SDI documents will reuse this document)

  return TRUE;
}




// CPersonDoc serialization

void CPersonDoc::Serialize(CArchive& ar)
{
  if (ar.IsStoring())
  {
    // TODO: add storing code here
  }
  else
  {
    // TODO: add loading code here
  }
}

BOOL CPersonDoc::SelectAll(CPersonArray &oPersonArray)
{

	CSubscribersArray oSubscrArr;
	if(!m_oSubscrTable.SelectAll(oSubscrArr))
		return FALSE;

	for(int i = 0; i < oSubscrArr.GetCount(); i++)
	{
		CPerson *poPerson = new CPerson;
		poPerson->m_tSubscriber = *oSubscrArr[i];

		if(!m_oCityTable.SelectByContent(CCities(DNC, 0, oSubscrArr[i]->m_szCityCode)))
			return FALSE;

		CCitiesArray oCitiesArr;
		if(!m_oCityTable.SelectAll(oCitiesArr))
			return FALSE;

	  poPerson->m_tCity = *oCitiesArr[0];

		if(m_oSubscrPhoneNumbsTable.SelectByContent(CSubscriberPhoneNumbers(DNC, 0,  oSubscrArr[i]->m_iCode)))
		{
			if(!m_oSubscrPhoneNumbsTable.SelectAll(poPerson->m_oPhoneNumbsArr))
				return FALSE;
		}
	}

	return TRUE;
}

BOOL CPersonDoc::SortByColumn(const eColumn eCol, const BOOL bAsc)
{
  /* номерът на избраната колона се превежда в такъв, с начало първата потребителска колона от таблицата */
  //int iTableCol = (int)eCol + (int)CPersonTable::eColCode ;
  //return m_oCityTable.SortByColumn((CPersonTable::eColumn)iTableCol , bAsc);
	return FALSE;
}

#if 0
BOOL CPersonDoc::SelectWhereId(const int iId, CPerson &oCity)
{
  return m_oCityTable.SelectWhereId(iId, oCity);
}

BOOL CPersonDoc::UpdateWhereId(const int iId, const CPerson &oCity)
{
  BOOL bRes = m_oCityTable.UpdateWhereId(iId, oCity);
  if(!bRes)
    return FALSE;

  /* индициране за извършени промени по съдържанието на таблицата */
  
  UpdateAllViews(0, (LPARAM)&oCity);
    
  return bRes;
}

BOOL CPersonDoc::Insert(const CPerson &oCity)
{
  BOOL bRes = m_oCityTable.Insert(oCity);
  if(!bRes)
    return FALSE;

  /* индициране за извършени промени по съдържанието на таблицата */
  
  UpdateAllViews(0);
  
  return bRes;
}

BOOL CPersonDoc::DeleteWhereId(const int iId)
{
  BOOL bRes = m_oCityTable.DeleteWhereId(iId);
  if(!bRes)
    return FALSE;

  /* индициране за извършени промени по съдържанието на таблицата */
  
  UpdateAllViews(0);
  
  return bRes;
}

BOOL CPersonDoc::SelectByContent(const CPerson &oCity)
{
  CPerson oModCity = oCity;
  /* търсенето да включи всички записи */ 
  oModCity.m_iId = DNC;
  return m_oCityTable.SelectByContent(oModCity);
}
#endif



// CPersonDoc diagnostics

#ifdef _DEBUG
void CPersonDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void CPersonDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG


// CPersonDoc commands
