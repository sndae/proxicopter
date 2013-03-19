// SubscribersView.cpp : implementation of the CSubscribersView class
//

#include "stdafx.h"
#include "PhoneBook.h"

#include "SubscribersDoc.h"
#include "SubscribersView.h"
#include "SubscribersDlg.h"
#include ".\Subscribersview.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSubscribersView

IMPLEMENT_DYNCREATE(CSubscribersView, CListView)

BEGIN_MESSAGE_MAP(CSubscribersView, CListView)
END_MESSAGE_MAP()


// CSubscribersView construction/destruction

CSubscribersView::CSubscribersView()
{
  // TODO: add construction code here

}

CSubscribersView::~CSubscribersView()
{
}

BOOL CSubscribersView::PreCreateWindow(CREATESTRUCT& cs)
{
  // TODO: Modify the Window class or styles here by modifying
  //  the CREATESTRUCT cs

  return CListView::PreCreateWindow(cs);
}

void CSubscribersView::OnInitialUpdate()
{
  CListView::OnInitialUpdate();

  // TODO: You may populate your ListView with items by directly accessing
  //  its list control through a call to GetListCtrl().
  long lWndStyle = GetWindowLong(m_hWnd, GWL_STYLE);
  lWndStyle |= LVS_REPORT;
  SetWindowLong(m_hWnd, GWL_STYLE, lWndStyle);  
  CListCtrl& oListCtrl = GetListCtrl();
  oListCtrl.SetExtendedStyle( oListCtrl.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

  oListCtrl.InsertColumn(CSubscribersDoc::eColCode,       _T("Код на абонат"), LVCFMT_LEFT);
  oListCtrl.InsertColumn(CSubscribersDoc::eColFirstName,  _T("Име"), LVCFMT_LEFT);
  oListCtrl.InsertColumn(CSubscribersDoc::eColSecondName, _T("Презиме"), LVCFMT_LEFT);
  oListCtrl.InsertColumn(CSubscribersDoc::eColThirdName,  _T("Фамилия"), LVCFMT_LEFT);
  oListCtrl.InsertColumn(CSubscribersDoc::eColIDNumb,     _T("ЕГН"), LVCFMT_LEFT);
  oListCtrl.InsertColumn(CSubscribersDoc::eColCityCode,   _T("Код на град"), LVCFMT_LEFT);
  oListCtrl.InsertColumn(CSubscribersDoc::eColAddress,    _T("Адрес"), LVCFMT_LEFT);

  /* Оразмеряване на колонита спрямо дължината на имената им */
  oListCtrl.SetColumnWidth(CSubscribersDoc::eColCode,       LVSCW_AUTOSIZE_USEHEADER);
  oListCtrl.SetColumnWidth(CSubscribersDoc::eColFirstName,  LVSCW_AUTOSIZE_USEHEADER);
  oListCtrl.SetColumnWidth(CSubscribersDoc::eColSecondName, LVSCW_AUTOSIZE_USEHEADER);
  oListCtrl.SetColumnWidth(CSubscribersDoc::eColThirdName,  LVSCW_AUTOSIZE_USEHEADER);
  oListCtrl.SetColumnWidth(CSubscribersDoc::eColIDNumb,     LVSCW_AUTOSIZE_USEHEADER);
  oListCtrl.SetColumnWidth(CSubscribersDoc::eColCityCode,   LVSCW_AUTOSIZE_USEHEADER);
  oListCtrl.SetColumnWidth(CSubscribersDoc::eColAddress,    LVSCW_AUTOSIZE_USEHEADER);

  memset(m_abAscSorting, TRUE, sizeof(m_abAscSorting));

  /* запълване редовете на листът */
  UpdateColumnsContent();
  m_iCurrRowSelected = 0;
}

BOOL CSubscribersView::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
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
        GetDocument()->SortByColumn((CSubscribersDoc::eColumn)iNumb, m_abAscSorting[iNumb]);
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

void CSubscribersView::UpdateColumnsContent()
{
  m_SubscribersArray.RemoveAndFreeAll();
  /* запълване на листът с редове, спрямо последно наложеният филтър */
  if(GetDocument()->SelectAll(m_SubscribersArray) == TRUE)
  {
    CListCtrl& oListCtrl = GetListCtrl();   
    oListCtrl.DeleteAllItems();

    for(int i = m_SubscribersArray.GetCount(); i != 0 ; )
    {
      i--;
      CString csTempBuff;
      csTempBuff.Format(_T("%d"),  m_SubscribersArray[i]->m_iCode);
      int iRowIdx = oListCtrl.InsertItem(CSubscribersDoc::eColCode, csTempBuff);
      SetRowData(iRowIdx, *m_SubscribersArray[i]);
    }
  }
}

void CSubscribersView::ExecuteCntxMenuCmd(eMenuCmd eCmd)
{
  CSubscribers oSubscribers;
  if(m_SubscribersArray.GetCount())
    oSubscribers = *m_SubscribersArray[m_iCurrRowSelected];

  if(eCmd == eCmdDelete)
  {
    GetDocument()->DeleteWhereId(oSubscribers.m_iId);
  }
  else
  {
    CCitiesArray oCitiesArray;
    GetDocument()->SelectAllCityCodes(oCitiesArray);
    CSubscribersDlg oEditDlg(oSubscribers, eCmd, &oCitiesArray);
    
    if(oEditDlg.DoModal() != IDOK)
      return;

    CSubscribers oCity;
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

void CSubscribersView::OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint)
{
  if(lHint == 0)
  {
    UpdateColumnsContent();
  }
  else
  {
    UpdateSingleRow(((CSubscribers*)lHint)->m_iId);
  }
}

void CSubscribersView::UpdateSingleRow(int iRecId)
{
  for(int i = 0; i < m_SubscribersArray.GetCount(); i++)
  {
    /* Проверка дали ред с такова ID в момента е показан на потребителят */
    if(m_SubscribersArray[i]->m_iId == iRecId)
    {      
      CSubscribers *poUpdatedSubscriber = new CSubscribers;
      if(!GetDocument()->SelectWhereId(iRecId, *poUpdatedSubscriber))
        return;

      delete m_SubscribersArray[i];
      m_SubscribersArray[i] = poUpdatedSubscriber;
      SetRowData(i, *poUpdatedSubscriber);

      break;
    }
  }
}

void CSubscribersView::SetRowData(int iRowIdx, CSubscribers &oSubscriber)
{
  CListCtrl& oListCtrl = GetListCtrl();
  CString csTempBuff;
  csTempBuff.Format(_T("%d"),  oSubscriber.m_iCode);
  oListCtrl.SetItemText(iRowIdx, CSubscribersDoc::eColCode, csTempBuff);
  oListCtrl.SetItemText(iRowIdx, CSubscribersDoc::eColFirstName, oSubscriber.m_szFirstName);
  oListCtrl.SetItemText(iRowIdx, CSubscribersDoc::eColSecondName,oSubscriber.m_szSecondName);
  oListCtrl.SetItemText(iRowIdx, CSubscribersDoc::eColThirdName, oSubscriber.m_szThirdName);
  oListCtrl.SetItemText(iRowIdx, CSubscribersDoc::eColIDNumb,    oSubscriber.m_szIDNumb);
  oListCtrl.SetItemText(iRowIdx, CSubscribersDoc::eColCityCode,  oSubscriber.m_szCityCode);
  oListCtrl.SetItemText(iRowIdx, CSubscribersDoc::eColAddress,   oSubscriber.m_szAddress);  

  /* Оразмеряване на колоната спрямо дължината на името й */
  oListCtrl.SetColumnWidth(CSubscribersDoc::eColCode, LVSCW_AUTOSIZE_USEHEADER);
  /* Оразмеряване на колоната спрямо макс. дължина на неин запис */
  oListCtrl.SetColumnWidth(CSubscribersDoc::eColFirstName,  LVSCW_AUTOSIZE);
  oListCtrl.SetColumnWidth(CSubscribersDoc::eColSecondName, LVSCW_AUTOSIZE);
  oListCtrl.SetColumnWidth(CSubscribersDoc::eColThirdName,  LVSCW_AUTOSIZE);
  oListCtrl.SetColumnWidth(CSubscribersDoc::eColIDNumb,     LVSCW_AUTOSIZE);
  oListCtrl.SetColumnWidth(CSubscribersDoc::eColCityCode,   LVSCW_AUTOSIZE);
  oListCtrl.SetColumnWidth(CSubscribersDoc::eColAddress,    LVSCW_AUTOSIZE);
}

// CSubscribersView diagnostics

#ifdef _DEBUG
void CSubscribersView::AssertValid() const
{
  CListView::AssertValid();
}

void CSubscribersView::Dump(CDumpContext& dc) const
{
  CListView::Dump(dc);
}

CSubscribersDoc* CSubscribersView::GetDocument() const // non-debug version is inline
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSubscribersDoc)));
  return (CSubscribersDoc*)m_pDocument;
}
#endif //_DEBUG


// CSubscribersView message handlers
