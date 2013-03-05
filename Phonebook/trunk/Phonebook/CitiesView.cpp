// CitiesView.cpp : implementation of the CCitiesView class
//

#include "stdafx.h"
#include "PhoneBook.h"

#include "CitiesDoc.h"
#include "CitiesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCitiesView

IMPLEMENT_DYNCREATE(CCitiesView, CListView)

BEGIN_MESSAGE_MAP(CCitiesView, CListView)
END_MESSAGE_MAP()

// CCitiesView construction/destruction

CCitiesView::CCitiesView()
{
	// TODO: add construction code here

}

CCitiesView::~CCitiesView()
{
}

BOOL CCitiesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CCitiesView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
  long lWndStyle = GetWindowLong(m_hWnd, GWL_STYLE);
  lWndStyle |= LVS_REPORT;
  SetWindowLong(m_hWnd, GWL_STYLE, lWndStyle);  
  CListCtrl& oListCtrl = GetListCtrl();

  oListCtrl.InsertColumn(eCode, _T("Код"), LVCFMT_LEFT);
  oListCtrl.InsertColumn(eName, _T("Име"), LVCFMT_LEFT);
  oListCtrl.InsertColumn(eArea, _T("Област"), LVCFMT_LEFT);
  oListCtrl.SetColumnWidth(eCode, LVSCW_AUTOSIZE_USEHEADER);
  oListCtrl.SetColumnWidth(eName, LVSCW_AUTOSIZE_USEHEADER);
  oListCtrl.SetColumnWidth(eArea, LVSCW_AUTOSIZE_USEHEADER);

  UpdateColumnsContent();
}

void CCitiesView::UpdateColumnsContent()
{
  CCitiesDoc *poDoc = GetDocument();
  CCitiesArray oCitiesArray;
  if(poDoc->SelectAll(oCitiesArray) == TRUE)
  {
    CListCtrl& oListCtrl = GetListCtrl();   
    for(int i = 0; i < oCitiesArray.GetCount(); i++)
    {
      int iRowIdx = oListCtrl.InsertItem(eCode, oCitiesArray[i]->m_szCode);
      oListCtrl.SetItemText(iRowIdx, eName, oCitiesArray[i]->m_szName);
      oListCtrl.SetItemText(iRowIdx, eArea, oCitiesArray[i]->m_szArea);
    }
    oListCtrl.SetColumnWidth(eCode, LVSCW_AUTOSIZE_USEHEADER);
    oListCtrl.SetColumnWidth(eName, LVSCW_AUTOSIZE);
    oListCtrl.SetColumnWidth(eArea, LVSCW_AUTOSIZE);
  }
}

// CCitiesView diagnostics

#ifdef _DEBUG
void CCitiesView::AssertValid() const
{
	CListView::AssertValid();
}

void CCitiesView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CCitiesDoc* CCitiesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCitiesDoc)));
	return (CCitiesDoc*)m_pDocument;
}
#endif //_DEBUG


// CCitiesView message handlers
