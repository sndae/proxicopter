// CitiesView.cpp : implementation of the CPhoneTypesView class
//

#include "stdafx.h"
#include "PhoneBook.h"

#include "PhoneTypesDoc.h"
#include "PhoneTypesView.h"
//#include "CitiesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPhoneTypesView

IMPLEMENT_DYNCREATE(CPhoneTypesView, CListView)

BEGIN_MESSAGE_MAP(CPhoneTypesView, CListView)
END_MESSAGE_MAP()


// CPhoneTypesView construction/destruction

CPhoneTypesView::CPhoneTypesView()
{
	// TODO: add construction code here

}

CPhoneTypesView::~CPhoneTypesView()
{
}

BOOL CPhoneTypesView::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
  /*
  if (message == WM_NOTIFY)
  {
    int iNumb = 0;
    switch(((LPNMHDR)lParam)->code)
    {
      case NM_DBLCLK:  
        OnRowDbClicked();
        break;
      case LVN_COLUMNCLICK:
        iNumb = ((LPNMLISTVIEW)lParam)->iSubItem;
        m_abAscSorting[iNumb] = !m_abAscSorting[iNumb];
        GetDocument()->SortByColumn((CPhoneTypesDoc::eColumn)iNumb, m_abAscSorting[iNumb]);
        UpdateColumnsContent();
        break;
      case LVN_ITEMCHANGED:
        m_iCurrRowSelected = ((LPNMLISTVIEW)lParam)->iItem;
        break;
      default:
        break;
    }
  }
  */

  return CListView::OnChildNotify(message, wParam, lParam, pResult);
}

BOOL CPhoneTypesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CPhoneTypesView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
 
  long lWndStyle = GetWindowLong(m_hWnd, GWL_STYLE);
  lWndStyle |= LVS_REPORT;
  SetWindowLong(m_hWnd, GWL_STYLE, lWndStyle);  
  CListCtrl& oListCtrl = GetListCtrl();
  oListCtrl.SetExtendedStyle( oListCtrl.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

  oListCtrl.InsertColumn(CPhoneTypesDoc::eColCode, _T("Код"), LVCFMT_LEFT);
  oListCtrl.InsertColumn(CPhoneTypesDoc::eColType, _T("Тип телефон"), LVCFMT_LEFT);
  oListCtrl.SetColumnWidth(CPhoneTypesDoc::eColCode, LVSCW_AUTOSIZE_USEHEADER);
  oListCtrl.SetColumnWidth(CPhoneTypesDoc::eColType, LVSCW_AUTOSIZE_USEHEADER);

  UpdateColumnsContent();
  m_iCurrRowSelected = 0;
  memset(m_abAscSorting, TRUE, sizeof(m_abAscSorting));

}

void CPhoneTypesView::UpdateColumnsContent()
{
  m_PhoneTypesArray.RemoveAndFreeAll();
  if(GetDocument()->SelectAll(m_PhoneTypesArray) == TRUE)
  {
    CListCtrl& oListCtrl = GetListCtrl();   
    oListCtrl.DeleteAllItems();
    for(int i = m_PhoneTypesArray.GetCount(); i != 0 ; )
    {
      i--;
      int iRowIdx = oListCtrl.InsertItem(CPhoneTypesDoc::eColCode, m_PhoneTypesArray[i]->m_szCode);
      oListCtrl.SetItemText(iRowIdx, CPhoneTypesDoc::eColType, m_PhoneTypesArray[i]->m_szType);
    }
    oListCtrl.SetColumnWidth(CPhoneTypesDoc::eColCode, LVSCW_AUTOSIZE_USEHEADER);
    oListCtrl.SetColumnWidth(CPhoneTypesDoc::eColType, LVSCW_AUTOSIZE);
  }
}

void CPhoneTypesView::OnRowDbClicked()
{
  /*
  CPhoneTypesDlg oEditDlg(*m_PhoneTypesArray[m_iCurrRowSelected]);
  if(oEditDlg.DoModal() == IDOK)
  {
    CPhoneTypes oCity;
    switch(oEditDlg.GetCityCmd())
    {
    case CPhoneTypesDlg::eCityUpdate:
      oCity = oEditDlg.GetCityData();
      if(GetDocument()->UpdateWhereId(oCity.m_iId, oCity) == FALSE)
        MessageBox(_T("Грешка при запис.\nВалидарайте записа или го опреснете"), 0, MB_OK|MB_ICONWARNING);
      else
        UpdateColumnsContent();
      break;
    case CPhoneTypesDlg::eCityInsert:
      oCity = oEditDlg.GetCityData();
      if(GetDocument()->Insert(oCity) == FALSE)
        MessageBox(_T("Грешка при запис.\nВалидарайте записа"), 0, MB_OK|MB_ICONWARNING);
      else
        UpdateColumnsContent();      
      break;
    case CPhoneTypesDlg::eCityDelete:
      oCity = oEditDlg.GetCityData();
      GetDocument()->DeleteWhereId(oCity.m_iId);
      UpdateColumnsContent();
      break;
    case CPhoneTypesDlg::eCityFind:
      oCity = oEditDlg.GetCityData();
      GetDocument()->SelectByContent(oCity);
      UpdateColumnsContent();
      break;
    }
  }
  */
}


// CPhoneTypesView diagnostics

#ifdef _DEBUG
void CPhoneTypesView::AssertValid() const
{
	CListView::AssertValid();
}

void CPhoneTypesView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CPhoneTypesDoc* CPhoneTypesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhoneTypesDoc)));
	return (CPhoneTypesDoc*)m_pDocument;
}
#endif //_DEBUG


// CPhoneTypesView message handlers
