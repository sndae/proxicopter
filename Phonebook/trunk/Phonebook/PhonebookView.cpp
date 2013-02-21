// PhonebookView.cpp : implementation of the CPhonebookView class
//

#include "stdafx.h"
#include "Phonebook.h"

#include "PhonebookDoc.h"
#include "PhonebookView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CPhonebookView, CFormView)

BEGIN_MESSAGE_MAP(CPhonebookView, CFormView)
  ON_BN_CLICKED(IDC_LOADDB, &CPhonebookView::OnBnClickedLoaddb)
  ON_CBN_SELCHANGE(IDC_REGISTER_SELECTOR, &CPhonebookView::OnCbnSelchangeRegisterSelector)
END_MESSAGE_MAP()

// CPhonebookView construction/destruction

CPhonebookView::CPhonebookView()
	: CFormView(CPhonebookView::IDD)
{
	// TODO: add construction code here

}

CPhonebookView::~CPhonebookView()
{
}

void CPhonebookView::DoDataExchange(CDataExchange* pDX)
{
  CFormView::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_REGISTER_SELECTOR, m_RegSelector);
  DDX_Control(pDX, IDC_REGISTER_CONTENT, m_RegContentList);
}

BOOL CPhonebookView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CPhonebookView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();
}


// CPhonebookView diagnostics

#ifdef _DEBUG
void CPhonebookView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPhonebookView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CPhonebookDoc* CPhonebookView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhonebookDoc)));
	return (CPhonebookDoc*)m_pDocument;
}
#endif //_DEBUG


// CPhonebookView message handlers

void CPhonebookView::OnBnClickedLoaddb()
{
  // TODO: Add your control notification handler code here

}

void CPhonebookView::OnCbnSelchangeRegisterSelector()
{
  // TODO: Add your control notification handler code here

}
