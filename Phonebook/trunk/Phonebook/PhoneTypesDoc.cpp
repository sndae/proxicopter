// PhoneTypesDoc.cpp : implementation of the CPhoneTypesDoc class
//

#include "stdafx.h"
#include "PhoneBook.h"

#include "PhoneTypesDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPhoneTypesDoc

IMPLEMENT_DYNCREATE(CPhoneTypesDoc, CDocument)

BEGIN_MESSAGE_MAP(CPhoneTypesDoc, CDocument)
END_MESSAGE_MAP()


// CPhoneTypesDoc construction/destruction

CPhoneTypesDoc::CPhoneTypesDoc()
{
  // TODO: add one-time construction code here

}

CPhoneTypesDoc::~CPhoneTypesDoc()
{
}

BOOL CPhoneTypesDoc::OnNewDocument()
{
  if (!CDocument::OnNewDocument())
    return FALSE;

  // TODO: add reinitialization code here
  // (SDI documents will reuse this document)

  return TRUE;
}




// CPhoneTypesDoc serialization

void CPhoneTypesDoc::Serialize(CArchive& ar)
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

BOOL CPhoneTypesDoc::SelectAll(CPhoneTypesArray &oPhoneTypesArray)
{
  return m_oPhoneTypesTable.SelectAll(oPhoneTypesArray);
}

BOOL CPhoneTypesDoc::SelectWhereId(const int iId, CPhoneTypes &oCity)
{
  return m_oPhoneTypesTable.SelectWhereId(iId, oCity);
}
BOOL CPhoneTypesDoc::UpdateWhereId(const int iId, const CPhoneTypes &oCity)
{
  BOOL bRes = m_oPhoneTypesTable.UpdateWhereId(iId, oCity);
  if(!bRes)
    return FALSE;

  /* индициране за извършени промени по съдържанието на таблицата */
  SetModifiedFlag();
  UpdateAllViews(0);
    
  return bRes;
}

BOOL CPhoneTypesDoc::Insert(const CPhoneTypes &oCity)
{
  BOOL bRes = m_oPhoneTypesTable.Insert(oCity);
  if(!bRes)
    return FALSE;

  /* индициране за извършени промени по съдържанието на таблицата */
  SetModifiedFlag();
  UpdateAllViews(0);
  
  return bRes;
}

BOOL CPhoneTypesDoc::DeleteWhereId(const int iId)
{
  BOOL bRes = m_oPhoneTypesTable.DeleteWhereId(iId);
  if(!bRes)
    return FALSE;

  /* индициране за извършени промени по съдържанието на таблицата */
  SetModifiedFlag();
  UpdateAllViews(0);
  
  return bRes;
}

BOOL CPhoneTypesDoc::SortByColumn(const eColumn eCol, const BOOL bAsc)
{
  /* номерът на избраната колона се превежда в такъв, с начало първата потребителска колона от таблицата */
  int iTableCol = (int)eCol + (int)CPhoneTypesTable::eColCode ;
  return m_oPhoneTypesTable.SortByColumn((CPhoneTypesTable::eColumn)iTableCol , bAsc);
}

BOOL CPhoneTypesDoc::SelectByContent(const CPhoneTypes &oCity)
{
  CPhoneTypes oModCity = oCity;
  /* търсенето да включи всички записи */ 
  oModCity.m_iId = -1;
  return m_oPhoneTypesTable.SelectByContent(oModCity);
}

// CPhoneTypesDoc diagnostics

#ifdef _DEBUG
void CPhoneTypesDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void CPhoneTypesDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG


// CPhoneTypesDoc commands
