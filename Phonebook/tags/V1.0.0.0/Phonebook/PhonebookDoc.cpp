// PhonebookDoc.cpp : implementation of the CPhonebookDoc class
//

#include "stdafx.h"
#include "Phonebook.h"

#include "PhonebookDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPhonebookDoc

IMPLEMENT_DYNCREATE(CPhonebookDoc, CDocument)

BEGIN_MESSAGE_MAP(CPhonebookDoc, CDocument)
END_MESSAGE_MAP()


// CPhonebookDoc construction/destruction

CPhonebookDoc::CPhonebookDoc()
{
	// TODO: add one-time construction code here

}

CPhonebookDoc::~CPhonebookDoc()
{
}

BOOL CPhonebookDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CPhonebookDoc serialization

void CPhonebookDoc::Serialize(CArchive& ar)
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


// CPhonebookDoc diagnostics

#ifdef _DEBUG
void CPhonebookDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPhonebookDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPhonebookDoc commands
