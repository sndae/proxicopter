// SubscribersDoc.cpp : implementation of the CSubscribersDoc class
//

#include "stdafx.h"
#include "PhoneBook.h"

#include "SubscribersDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSubscribersDoc

IMPLEMENT_DYNCREATE(CSubscribersDoc, CDocument)

BEGIN_MESSAGE_MAP(CSubscribersDoc, CDocument)
END_MESSAGE_MAP()


// CSubscribersDoc construction/destruction

CSubscribersDoc::CSubscribersDoc()
{
  // TODO: add one-time construction code here

}

CSubscribersDoc::~CSubscribersDoc()
{
}

BOOL CSubscribersDoc::OnNewDocument()
{
  if (!CDocument::OnNewDocument())
    return FALSE;

  // TODO: add reinitialization code here
  // (SDI documents will reuse this document)

  return TRUE;
}




// CSubscribersDoc serialization

void CSubscribersDoc::Serialize(CArchive& ar)
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

BOOL CSubscribersDoc::SelectAll(CSubscribersArray &oSubscribersArray)
{
  return m_oSubscribersTable.SelectAll(oSubscribersArray);
}

BOOL CSubscribersDoc::SelectWhereId(const int iId, CSubscribers &oSubscriber)
{
  return m_oSubscribersTable.SelectWhereId(iId, oSubscriber);
}
BOOL CSubscribersDoc::UpdateWhereId(const int iId, const CSubscribers &oSubscriber)
{
  BOOL bRes = m_oSubscribersTable.UpdateWhereId(iId, oSubscriber);
  if(!bRes)
    return FALSE;

  /* индициране за извършени промени по съдържанието на таблицата */
  SetModifiedFlag();
  UpdateAllViews(0);
    
  return bRes;
}

BOOL CSubscribersDoc::Insert(const CSubscribers &oSubscriber)
{
  BOOL bRes = m_oSubscribersTable.Insert(oSubscriber);
  if(!bRes)
    return FALSE;

  /* индициране за извършени промени по съдържанието на таблицата */
  SetModifiedFlag();
  UpdateAllViews(0);
  
  return bRes;
}

BOOL CSubscribersDoc::DeleteWhereId(const int iId)
{
  BOOL bRes = m_oSubscribersTable.DeleteWhereId(iId);
  if(!bRes)
    return FALSE;

  /* индициране за извършени промени по съдържанието на таблицата */
  SetModifiedFlag();
  UpdateAllViews(0);
  
  return bRes;
}

BOOL CSubscribersDoc::SortByColumn(const eColumn eCol, const BOOL bAsc)
{
  /* номерът на избраната колона се превежда в такъв, с начало първата потребителска колона от таблицата */
  int iTableCol = (int)eCol + (int)CSubscribersTable::eColCode ;
  return m_oSubscribersTable.SortByColumn((CSubscribersTable::eColumn)iTableCol , bAsc);
}

BOOL CSubscribersDoc::SelectByContent(const CSubscribers &oSubscriber)
{
  CSubscribers oModCity = oSubscriber;
  /* търсенето да включи всички записи */ 
  oModCity.m_iId = -1;
  return m_oSubscribersTable.SelectByContent(oModCity);
}

BOOL CSubscribersDoc::SelectAllCityCodes(CCitiesArray &oCitiesArray)
{
  return m_oSubscribersTable.SelectAllCityCodes(oCitiesArray);
}

// CSubscribersDoc diagnostics

#ifdef _DEBUG
void CSubscribersDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void CSubscribersDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG


// CSubscribersDoc commands
