// PhoneTypesDoc.cpp : implementation file
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "PhoneTypesDoc.h"


// CPhoneTypesDoc

IMPLEMENT_DYNCREATE(CPhoneTypesDoc, CDocument)

CPhoneTypesDoc::CPhoneTypesDoc()
{
}

BOOL CPhoneTypesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CPhoneTypesDoc::~CPhoneTypesDoc()
{
}


BEGIN_MESSAGE_MAP(CPhoneTypesDoc, CDocument)
END_MESSAGE_MAP()


// CPhoneTypesDoc diagnostics

#ifdef _DEBUG
void CPhoneTypesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CPhoneTypesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
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
#endif


// CPhoneTypesDoc commands
BOOL CPhoneTypesDoc::SelectAll(CPhoneTypesArray &oCitiesArray)
{
  return TRUE;
}

BOOL CPhoneTypesDoc::SelectWhereId(const int iId, CPhoneTypes &oCity)
{
  return TRUE;
}

BOOL CPhoneTypesDoc::UpdateWhereId(const int iId, const CPhoneTypes &oCity)
{
  return TRUE;
}

BOOL CPhoneTypesDoc::Insert(const CPhoneTypes &oCity)
{
  return TRUE;
}

BOOL CPhoneTypesDoc::DeleteWhereId(const int iId)
{
  return TRUE;
}

BOOL CPhoneTypesDoc::SortByColumn(const eColumn eCol, const BOOL bAsc)
{
  return TRUE;
}

BOOL CPhoneTypesDoc::SelectByContent(const CPhoneTypes &oCity)
{
  return TRUE;
}
