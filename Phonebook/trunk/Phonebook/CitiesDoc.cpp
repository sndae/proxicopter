// CitiesDoc.cpp : implementation of the CCitiesDoc class
//

#include "stdafx.h"
#include "PhoneBook.h"

#include "CitiesDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCitiesDoc

IMPLEMENT_DYNCREATE(CCitiesDoc, CDocument)

BEGIN_MESSAGE_MAP(CCitiesDoc, CDocument)
END_MESSAGE_MAP()


// CCitiesDoc construction/destruction

CCitiesDoc::CCitiesDoc()
{
  // TODO: add one-time construction code here

}

CCitiesDoc::~CCitiesDoc()
{
}

BOOL CCitiesDoc::OnNewDocument()
{
  if (!CDocument::OnNewDocument())
    return FALSE;

  // TODO: add reinitialization code here
  // (SDI documents will reuse this document)

  return TRUE;
}




// CCitiesDoc serialization

void CCitiesDoc::Serialize(CArchive& ar)
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

BOOL CCitiesDoc::SelectAll(CCitiesArray &oCitiesArray)
{
  return m_oCityTable.SelectAll(oCitiesArray);
}

BOOL CCitiesDoc::SelectWhereId(const int iId, CCities &oCity)
{
  return m_oCityTable.SelectWhereId(iId, oCity);
}

BOOL CCitiesDoc::UpdateWhereId(const int iId, const CCities &oCity)
{
  BOOL bRes = m_oCityTable.UpdateWhereId(iId, oCity);
  if(!bRes)
    return FALSE;

  /* индициране за извършени промени по съдържанието на таблицата */
  SetModifiedFlag();
  UpdateAllViews(0, (LPARAM)&oCity);
    
  return bRes;
}

BOOL CCitiesDoc::Insert(const CCities &oCity)
{
  BOOL bRes = m_oCityTable.Insert(oCity);
  if(!bRes)
    return FALSE;

  /* индициране за извършени промени по съдържанието на таблицата */
  SetModifiedFlag();
  UpdateAllViews(0);
  
  return bRes;
}

BOOL CCitiesDoc::DeleteWhereId(const int iId)
{
  BOOL bRes = m_oCityTable.DeleteWhereId(iId);
  if(!bRes)
    return FALSE;

  /* индициране за извършени промени по съдържанието на таблицата */
  SetModifiedFlag();
  UpdateAllViews(0);
  
  return bRes;
}

BOOL CCitiesDoc::SortByColumn(const eColumn eCol, const BOOL bAsc)
{
  /* номерът на избраната колона се превежда в такъв, с начало първата потребителска колона от таблицата */
  int iTableCol = (int)eCol + (int)CCitiesTable::eColCode ;
  return m_oCityTable.SortByColumn((CCitiesTable::eColumn)iTableCol , bAsc);
}

BOOL CCitiesDoc::SelectByContent(const CCities &oCity)
{
  CCities oModCity = oCity;
  /* търсенето да включи всички записи */ 
  oModCity.m_iId = -1;
  return m_oCityTable.SelectByContent(oModCity);
}

// CCitiesDoc diagnostics

#ifdef _DEBUG
void CCitiesDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void CCitiesDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG


// CCitiesDoc commands
