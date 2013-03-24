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
  m_bAutoDelete = FALSE;
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

BOOL CPhoneTypesDoc::SelectWhereId(const int iId, CPhoneTypes &oPhoneType)
{
  return m_oPhoneTypesTable.SelectWhereId(iId, oPhoneType);
}
BOOL CPhoneTypesDoc::UpdateWhereId(const int iId, const CPhoneTypes &oPhoneType)
{
  BOOL bRes = m_oPhoneTypesTable.UpdateWhereId(iId, oPhoneType);
  if(!bRes)
    return FALSE;

  /* индициране за извършени промени по съдържанието на таблицата */
  
  UpdateAllViews(0, (LPARAM)&oPhoneType);
    
  return bRes;
}

BOOL CPhoneTypesDoc::Insert(const CPhoneTypes &oPhoneType)
{
  BOOL bRes = m_oPhoneTypesTable.Insert(oPhoneType);
  if(!bRes)
    return FALSE;

  /* индициране за извършени промени по съдържанието на таблицата */
  
  UpdateAllViews(0);
  
  return bRes;
}

BOOL CPhoneTypesDoc::DeleteWhereId(const int iId)
{
  BOOL bRes = m_oPhoneTypesTable.DeleteWhereId(iId);
  if(!bRes)
    return FALSE;

  /* индициране за извършени промени по съдържанието на таблицата */
  
  UpdateAllViews(0);
  
  return bRes;
}

BOOL CPhoneTypesDoc::SortByColumn(const eColumn eCol, const BOOL bAsc)
{
  /* номерът на избраната колона се превежда в такъв, с начало първата потребителска колона от таблицата */
  int iTableCol = (int)eCol + (int)CPhoneTypesTable::eColCode ;
  return m_oPhoneTypesTable.SortByColumn((CPhoneTypesTable::eColumn)iTableCol , bAsc);
}

BOOL CPhoneTypesDoc::SelectByContent(const CPhoneTypes &oPhoneType)
{
  CPhoneTypes oModCity = oPhoneType;
  /* търсенето да включи всички записи */ 
  oModCity.m_iId = DNC;
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
