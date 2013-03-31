// PersonView.cpp : implementation file
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "PersonView.h"


// CPersonView

IMPLEMENT_DYNCREATE(CPersonView, CListView)

CPersonView::CPersonView()
{

}

CPersonView::~CPersonView()
{
}



BEGIN_MESSAGE_MAP(CPersonView, CListView)
END_MESSAGE_MAP()


// CPersonView diagnostics
BOOL CPersonView::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
  return CListView::OnChildNotify(message, wParam, lParam, pResult);	
}

void CPersonView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	long lWndStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	lWndStyle |= LVS_REPORT;
	SetWindowLong(m_hWnd, GWL_STYLE, lWndStyle);	
	CListCtrl& oListCtrl = GetListCtrl();
	oListCtrl.SetExtendedStyle( oListCtrl.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

	oListCtrl.InsertColumn(CPersonDoc::eColSubscrCode,     _T("Код на абонат"), LVCFMT_LEFT);
	oListCtrl.InsertColumn(CPersonDoc::eColFirstName,      _T("Първо име"), LVCFMT_LEFT);
	oListCtrl.InsertColumn(CPersonDoc::eColSecondName,     _T("Второ име"), LVCFMT_LEFT);
	oListCtrl.InsertColumn(CPersonDoc::eColThirdName,      _T("Трето име"), LVCFMT_LEFT);
	oListCtrl.InsertColumn(CPersonDoc::eColPhoneNumber,    _T("Телефонен номер"), LVCFMT_LEFT);
	oListCtrl.InsertColumn(CPersonDoc::eColPhoneNumberType,_T("Тип телефон"), LVCFMT_LEFT);

	/* Оразмеряване на колонита спрямо дължината на имената им */
	oListCtrl.SetColumnWidth(CPersonDoc::eColSubscrCode,     LVSCW_AUTOSIZE_USEHEADER);
	oListCtrl.SetColumnWidth(CPersonDoc::eColFirstName,      LVSCW_AUTOSIZE_USEHEADER);
	oListCtrl.SetColumnWidth(CPersonDoc::eColSecondName,     LVSCW_AUTOSIZE_USEHEADER);
	oListCtrl.SetColumnWidth(CPersonDoc::eColThirdName,      LVSCW_AUTOSIZE_USEHEADER);
	oListCtrl.SetColumnWidth(CPersonDoc::eColPhoneNumber,    LVSCW_AUTOSIZE_USEHEADER);
	oListCtrl.SetColumnWidth(CPersonDoc::eColPhoneNumberType,LVSCW_AUTOSIZE_USEHEADER);

	memset(m_abAscSorting, TRUE, sizeof(m_abAscSorting));

	/* запълване редовете на листът */
	UpdateColumnsContent();
	m_iCurrRowSelected = 0;
}

void CPersonView::UpdateColumnsContent()
{
  m_PersonsArray.RemoveAndFreeAll();
  /* запълване на листът с редове, спрямо последно наложеният филтър */
  if(GetDocument()->SelectAll(m_PersonsArray) == TRUE)
  {
    CListCtrl& oListCtrl = GetListCtrl();   
    oListCtrl.DeleteAllItems();
    for(int i = m_PersonsArray.GetCount(); i != 0 ; )
    {
      i--;
			for(int c = 0; c < m_PersonsArray[i]->m_oPhoneNumbsArr.GetCount(); c++)
			{
				CString csTempBuff;
				csTempBuff.Format(_T("%d"), m_PersonsArray[i]->m_tSubscriber.m_iCode);
				int iRowIdx = oListCtrl.InsertItem(CPersonDoc::eColSubscrCode, csTempBuff);
	      
				SetRowData(iRowIdx, *m_PersonsArray[i], *m_PersonsArray[i]->m_oPhoneNumbsArr[c]);
			}
    }
  }
}

void CPersonView::SetRowData(int iRowIdx, CPerson &oPerson, CSubscriberPhoneNumbers &oPhoneNumber)
{
	CListCtrl& oListCtrl = GetListCtrl();
	oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColCity,			oPerson.m_tCity.m_szName);
	oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColFirstName, oPerson.m_tSubscriber.m_szFirstName);
	oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColSecondName,oPerson.m_tSubscriber.m_szSecondName);
  oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColThirdName, oPerson.m_tSubscriber.m_szThirdName);

	oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColPhoneNumber, oPhoneNumber.m_szPhoneNumber);
	oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColPhoneNumberType, _T("")); 
	
	/* Оразмеряване на колоната спрямо дължината на името й */
  oListCtrl.SetColumnWidth(CPersonDoc::eColSubscrCode, LVSCW_AUTOSIZE_USEHEADER);
  /* Оразмеряване на колоната спрямо макс. дължина на неин запис */
  oListCtrl.SetColumnWidth(CPersonDoc::eColCity,			 LVSCW_AUTOSIZE);
  oListCtrl.SetColumnWidth(CPersonDoc::eColFirstName,  LVSCW_AUTOSIZE);
  oListCtrl.SetColumnWidth(CPersonDoc::eColSecondName, LVSCW_AUTOSIZE);
  oListCtrl.SetColumnWidth(CPersonDoc::eColThirdName,  LVSCW_AUTOSIZE);
  oListCtrl.SetColumnWidth(CPersonDoc::eColPhoneNumber,     LVSCW_AUTOSIZE);
  oListCtrl.SetColumnWidth(CPersonDoc::eColPhoneNumberType, LVSCW_AUTOSIZE);

}

CPersonDoc* CPersonView::GetDocument() const // non-debug version is inline
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersonDoc)));
  return (CPersonDoc*)m_pDocument;
}

#ifdef _DEBUG
void CPersonView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CPersonView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPersonView message handlers
