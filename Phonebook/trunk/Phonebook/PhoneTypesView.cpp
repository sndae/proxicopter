// PhoneTypesView.cpp : implementation of the CPhoneTypesView class
//

#include "stdafx.h"
#include "PhoneBook.h"

#include "PhoneTypesDoc.h"
#include "PhoneTypesView.h"
#include "PhoneTypesDlg.h"
#include ".\PhoneTypesview.h"

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
  
  /* Оразмеряване на колонита спрямо дължината на имената им */
  oListCtrl.SetColumnWidth(CPhoneTypesDoc::eColCode, LVSCW_AUTOSIZE_USEHEADER);
  oListCtrl.SetColumnWidth(CPhoneTypesDoc::eColType, LVSCW_AUTOSIZE_USEHEADER);

  memset(m_abAscSorting, TRUE, sizeof(m_abAscSorting));

  /* запълване редовете на листът */
  UpdateColumnsContent();
  m_iCurrRowSelected = 0;
}

BOOL CPhoneTypesView::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
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
        GetDocument()->SortByColumn((CPhoneTypesDoc::eColumn)iNumb, m_abAscSorting[iNumb]);
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

void CPhoneTypesView::UpdateColumnsContent()
{
  m_PhoneTypesArray.RemoveAndFreeAll();
  /* запълване на листът с редове, спрямо последно наложеният филтър */
  if(GetDocument()->SelectAll(m_PhoneTypesArray) == TRUE)
  {
    CListCtrl& oListCtrl = GetListCtrl();   
    oListCtrl.DeleteAllItems();
    for(int i = m_PhoneTypesArray.GetCount(); i != 0 ; )
    {
      i--;
      CString csTempBuff;
      csTempBuff.Format(_T("%d"),  m_PhoneTypesArray[i]->m_iCode);
      int iRowIdx = oListCtrl.InsertItem(CPhoneTypesDoc::eColCode, csTempBuff);
      SetRowData(iRowIdx, *m_PhoneTypesArray[i]);
    }
  }
}

void CPhoneTypesView::ExecuteCntxMenuCmd(eMenuCmd eCmd)
{
  CPhoneTypes oPhoneTypes;
  if(m_PhoneTypesArray.GetCount())
    oPhoneTypes = *m_PhoneTypesArray[m_iCurrRowSelected];

  if(eCmd == eCmdDelete)
  {
    GetDocument()->DeleteWhereId(oPhoneTypes.m_iId);
  }
  else
  {
    CPhoneTypesDlg oEditDlg(oPhoneTypes, eCmd);
    if(oEditDlg.DoModal() != IDOK)
      return;

    CPhoneTypes oPhoneType;
    switch(eCmd)
    {
    case eCmdUpdate:
      oPhoneType = oEditDlg.GetCityData();
      if(GetDocument()->UpdateWhereId(oPhoneType.m_iId, oPhoneType) == FALSE)
        MessageBox(_T("Грешка при запис.\nВалидарайте записа или го опреснете"), 0, MB_OK|MB_ICONWARNING);
      
      break;
    case eCmdInsert:
      oPhoneType = oEditDlg.GetCityData();
      if(GetDocument()->Insert(oPhoneType) == FALSE)
        MessageBox(_T("Грешка при запис.\nВалидарайте записа"), 0, MB_OK|MB_ICONWARNING); 
      break;
    case eCmdFind:
      oPhoneType = oEditDlg.GetCityData();
      GetDocument()->SelectByContent(oPhoneType);
      UpdateColumnsContent();
      break;
    default:
      ASSERT(0);
      break;
    }  
  }  
}

void CPhoneTypesView::OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint)
{
  if(lHint == 0)
  {
    UpdateColumnsContent();
  }
  else
  {
    UpdateSingleRow(((CPhoneTypes*)lHint)->m_iId);
  }
}

void CPhoneTypesView::UpdateSingleRow(int iRecId)
{
  for(int i = 0; i < m_PhoneTypesArray.GetCount(); i++)
  {
    /* Проверка дали ред с такова ID в момента е показан на потребителят */
    if(m_PhoneTypesArray[i]->m_iId == iRecId)
    {      
      CPhoneTypes *poUpdatedPhoneType = new CPhoneTypes;
      if(!GetDocument()->SelectWhereId(iRecId, *poUpdatedPhoneType))
        return;

      delete m_PhoneTypesArray[i];
      m_PhoneTypesArray[i] = poUpdatedPhoneType;
      SetRowData(i, *poUpdatedPhoneType);

      break;
    }
  }
}

void CPhoneTypesView::SetRowData(int iRowIdx, CPhoneTypes &oPhoneType)
{
  CListCtrl& oListCtrl = GetListCtrl();
  CString csTempBuff;
  csTempBuff.Format(_T("%d"),  oPhoneType.m_iCode);
  oListCtrl.SetItemText(iRowIdx, CPhoneTypesDoc::eColCode, csTempBuff);
  oListCtrl.SetItemText(iRowIdx, CPhoneTypesDoc::eColType, oPhoneType.m_szType);

  /* Оразмеряване на колоната спрямо дължината на името й */
  oListCtrl.SetColumnWidth(CPhoneTypesDoc::eColCode, LVSCW_AUTOSIZE_USEHEADER);
  /* Оразмеряване на колоната спрямо макс. дължина на неин запис */
  oListCtrl.SetColumnWidth(CPhoneTypesDoc::eColType, LVSCW_AUTOSIZE);
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
