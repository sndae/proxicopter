// CitiesView.cpp : implementation of the CCitiesView class
//

#include "stdafx.h"
#include "PhoneBook.h"

#include "CitiesDoc.h"
#include "CitiesView.h"
#include "CitiesDlg.h"
#include ".\citiesview.h"

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
  oListCtrl.SetExtendedStyle( oListCtrl.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

  oListCtrl.InsertColumn(CCitiesDoc::eColCode, _T("Код"), LVCFMT_LEFT);
  oListCtrl.InsertColumn(CCitiesDoc::eColName, _T("Име"), LVCFMT_LEFT);
  oListCtrl.InsertColumn(CCitiesDoc::eColArea, _T("Област"), LVCFMT_LEFT);
  
  /* Оразмеряване на колонита спрямо дължината на имената им */
  oListCtrl.SetColumnWidth(CCitiesDoc::eColCode, LVSCW_AUTOSIZE_USEHEADER);
  oListCtrl.SetColumnWidth(CCitiesDoc::eColName, LVSCW_AUTOSIZE_USEHEADER);
  oListCtrl.SetColumnWidth(CCitiesDoc::eColArea, LVSCW_AUTOSIZE_USEHEADER);

  memset(m_abAscSorting, TRUE, sizeof(m_abAscSorting));

  /* запълване редовете на листът */
  UpdateColumnsContent();
  m_iCurrRowSelected = 0;
}

BOOL CCitiesView::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
  CMenu oCntxMenu;
  CMenu *pSubMenu = 0;
  POINT tCur;
  
  int iMenuChoice;
  if (message == WM_NOTIFY)
  {
    int iNumb = 0;
    switch(((LPNMHDR)lParam)->code)
    {
      case NM_DBLCLK:
        /* при двоен клик се отваря за редакция последно избраният ред */
        ExecuteCntxMenuCmd(eCmdUpdate); 
        break;
      case NM_RCLICK:        
        oCntxMenu.LoadMenuW(IDR_CONTEXT_MENU);
        pSubMenu = oCntxMenu.GetSubMenu(0);
        GetCursorPos(&tCur);
        iMenuChoice = pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD, tCur.x, tCur.y, this);
        /* изпълнение на команда, избрана от конктекстното меню */
        switch(iMenuChoice)
        {
          case ID_OPTIONS_EDIT:   ExecuteCntxMenuCmd(eCmdUpdate); break;
          case ID_OPTIONS_DELETE: ExecuteCntxMenuCmd(eCmdDelete); break;
          case ID_OPTIONS_ADD:    ExecuteCntxMenuCmd(eCmdInsert); break;        
          case ID_OPTIONS_FIND:   ExecuteCntxMenuCmd(eCmdFind);   break; 
          default: break; 
        }
        break;
      case LVN_COLUMNCLICK:
        /* Сортиране по номер на колона */
        iNumb = ((LPNMLISTVIEW)lParam)->iSubItem;
        m_abAscSorting[iNumb] = !m_abAscSorting[iNumb];
        GetDocument()->SortByColumn((CCitiesDoc::eColumn)iNumb, m_abAscSorting[iNumb]);
        UpdateColumnsContent();
        break;
      case LVN_ITEMCHANGED:
        /* Запис на последно избраният ред */
        m_iCurrRowSelected = ((LPNMLISTVIEW)lParam)->iItem;
        break;
      default:
        break;
    }
  }

  return CListView::OnChildNotify(message, wParam, lParam, pResult);
}

void CCitiesView::UpdateColumnsContent()
{
  m_CitiesArray.RemoveAndFreeAll();
  /* запълване на листът с редове, спрямо последно наложеният филтър */
  if(GetDocument()->SelectAll(m_CitiesArray) == TRUE)
  {
    CListCtrl& oListCtrl = GetListCtrl();   
    oListCtrl.DeleteAllItems();
    for(int i = m_CitiesArray.GetCount(); i != 0 ; )
    {
      i--;
      int iRowIdx = oListCtrl.InsertItem(CCitiesDoc::eColCode, m_CitiesArray[i]->m_szCode);
      oListCtrl.SetItemText(iRowIdx, CCitiesDoc::eColName, m_CitiesArray[i]->m_szName);
      oListCtrl.SetItemText(iRowIdx, CCitiesDoc::eColArea, m_CitiesArray[i]->m_szArea);
    }
    /* Оразмеряване на колоната спрямо дължината на името й */
    oListCtrl.SetColumnWidth(CCitiesDoc::eColCode, LVSCW_AUTOSIZE_USEHEADER);
    /* Оразмеряване на колоната спрямо макс. дължина на неин запис */
    oListCtrl.SetColumnWidth(CCitiesDoc::eColName, LVSCW_AUTOSIZE);
    oListCtrl.SetColumnWidth(CCitiesDoc::eColArea, LVSCW_AUTOSIZE);
  }
}

void CCitiesView::ExecuteCntxMenuCmd(eMenuCmd eCmd)
{
  CCities oCities;
  if(m_CitiesArray.GetCount())
    oCities = *m_CitiesArray[m_iCurrRowSelected];

  CCitiesDlg oEditDlg(oCities, eCmd);
  if(oEditDlg.DoModal() == IDOK)
  {
    CCities oCity;
    switch(eCmd)
    {
    case eCmdUpdate:
      oCity = oEditDlg.GetCityData();
      if(GetDocument()->UpdateWhereId(oCity.m_iId, oCity) == FALSE)
        MessageBox(_T("Грешка при запис.\nВалидарайте записа или го опреснете"), 0, MB_OK|MB_ICONWARNING);
      
      break;
    case eCmdInsert:
      oCity = oEditDlg.GetCityData();
      if(GetDocument()->Insert(oCity) == FALSE)
        MessageBox(_T("Грешка при запис.\nВалидарайте записа"), 0, MB_OK|MB_ICONWARNING); 
      break;
    case eCmdDelete:
      oCity = oEditDlg.GetCityData();
      GetDocument()->DeleteWhereId(oCity.m_iId);

      break;
    case eCmdFind:
      oCity = oEditDlg.GetCityData();
      GetDocument()->SelectByContent(oCity);
      UpdateColumnsContent();
      break;
    default:
      ASSERT(0);
      break;
    }
  }
  
}

void CCitiesView::OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint)
{
  UpdateColumnsContent();
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
