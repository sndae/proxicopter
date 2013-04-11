// SubscriberPhoneNumbersView.cpp : implementation of the CSubscriberPhoneNumbersView class
//

#include "stdafx.h"
#include "PhoneBook.h"

#include "SubscriberPhoneNumbersDoc.h"
#include "SubscriberPhoneNumbersView.h"
#include "SubscriberPhoneNumbersDlg.h"
#include ".\SubscriberPhoneNumbersview.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSubscriberPhoneNumbersView

IMPLEMENT_DYNCREATE(CSubscriberPhoneNumbersView, CListView)

BEGIN_MESSAGE_MAP(CSubscriberPhoneNumbersView, CListView)
END_MESSAGE_MAP()


// CSubscriberPhoneNumbersView construction/destruction

CSubscriberPhoneNumbersView::CSubscriberPhoneNumbersView()
{
	// TODO: add construction code here

}

CSubscriberPhoneNumbersView::~CSubscriberPhoneNumbersView()
{
}

BOOL CSubscriberPhoneNumbersView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//	the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CSubscriberPhoneNumbersView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: You may populate your ListView with items by directly accessing
	//	its list control through a call to GetListCtrl().
	long lWndStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	lWndStyle |= LVS_REPORT;
	SetWindowLong(m_hWnd, GWL_STYLE, lWndStyle);
	CListCtrl& oListCtrl = GetListCtrl();
	oListCtrl.SetExtendedStyle( oListCtrl.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

	oListCtrl.InsertColumn(CSubscriberPhoneNumbersDoc::eColSubscrCode, _T("Код на абонат"), LVCFMT_LEFT);
	oListCtrl.InsertColumn(CSubscriberPhoneNumbersDoc::eColPhoneCode, _T("Код на тип телефон"), LVCFMT_LEFT);
	oListCtrl.InsertColumn(CSubscriberPhoneNumbersDoc::eColPhoneNumber, _T("Телефон"), LVCFMT_LEFT);

	// Оразмеряване на колонита спрямо дължината на имената им 
	oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColSubscrCode, LVSCW_AUTOSIZE_USEHEADER);
	oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColPhoneCode, LVSCW_AUTOSIZE_USEHEADER);
	oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColPhoneNumber, LVSCW_AUTOSIZE_USEHEADER);

	memset(m_abAscSorting, TRUE, sizeof(m_abAscSorting));

	// запълване редовете на листът 
	UpdateColumnsContent();
	m_nCurrRowSelected = 0;
}

BOOL CSubscriberPhoneNumbersView::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
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
				// при двоен клик се отваря за редакция последно избраният ред 
				ExecuteCntxMenuCmd(eCmdUpdate); 
				break;
			case NM_RCLICK:	
				oCntxMenu.LoadMenuW(IDR_CONTEXT_MENU);
				pSubMenu = oCntxMenu.GetSubMenu(0);
				GetCursorPos(&tCur);
				iMenuChoice = pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD, tCur.x, tCur.y, this);
				// изпълнение на команда, избрана от конктекстното меню 
				switch(iMenuChoice)
				{
					case ID_OPTIONS_EDIT:	ExecuteCntxMenuCmd(eCmdUpdate); break;
					case ID_OPTIONS_DELETE: ExecuteCntxMenuCmd(eCmdDelete); break;
					case ID_OPTIONS_ADD:	ExecuteCntxMenuCmd(eCmdInsert); break;
					case ID_OPTIONS_FIND:	ExecuteCntxMenuCmd(eCmdFind);	break; 
					default: break; 
				}
				break;
			case LVN_COLUMNCLICK:
				// Сортиране по номер на колона 
				iNumb = ((LPNMLISTVIEW)lParam)->iSubItem;
				m_abAscSorting[iNumb] = !m_abAscSorting[iNumb];
				GetDocument()->SortByColumn((CSubscriberPhoneNumbersDoc::eColumn)iNumb, m_abAscSorting[iNumb]);
				UpdateColumnsContent();
				break;
			case LVN_ITEMCHANGED:
				// Запис на последно избраният ред 
				m_nCurrRowSelected = ((LPNMLISTVIEW)lParam)->iItem;
				break;
			default:
				break;
		}
	}

	return CListView::OnChildNotify(message, wParam, lParam, pResult);
}

void CSubscriberPhoneNumbersView::UpdateColumnsContent()
{
	m_SubscriberPhoneNumbersArray.RemoveAndFreeAll();
	// запълване на листът с редове, спрямо последно наложеният филтър 
	if(GetDocument()->SelectAll(m_SubscriberPhoneNumbersArray) == TRUE)
	{
		CListCtrl& oListCtrl = GetListCtrl();	 
		oListCtrl.DeleteAllItems();

		for(int i = m_SubscriberPhoneNumbersArray.GetCount(); i != 0 ; )
		{
			i--;
			CString csTempBuff;
			csTempBuff.Format(_T("%d"),	m_SubscriberPhoneNumbersArray[i]->m_nSubscrId);
			int iRowIdx = oListCtrl.InsertItem(CSubscriberPhoneNumbersDoc::eColSubscrCode, csTempBuff);
			SetRowData(iRowIdx, *m_SubscriberPhoneNumbersArray[i]);
		}
	}
}

void CSubscriberPhoneNumbersView::ExecuteCntxMenuCmd(eMenuCmd eCmd)
{
	CSubscriberPhoneNumbers oSubscriberPhoneNumber;
	if(m_SubscriberPhoneNumbersArray.GetCount())
		oSubscriberPhoneNumber = *m_SubscriberPhoneNumbersArray[m_nCurrRowSelected];

	if(eCmd == eCmdDelete)
	{
		GetDocument()->DeleteWhereId(oSubscriberPhoneNumber.m_nId);
	}
	else
	{
		CSubscribersArray oSubscrArray;
		GetDocument()->SelectAllSubscribersCodes(oSubscrArray);
		CPhoneTypesArray oPhoneTypesArray;
		GetDocument()->SelectAllPhoneTypesCodes(oPhoneTypesArray);

		CSubscriberPhoneNumbersDlg oEditDlg(oSubscriberPhoneNumber, eCmd, &oSubscrArray, &oPhoneTypesArray);
		
		if(oEditDlg.DoModal() != IDOK)
			return;

		CSubscriberPhoneNumbers oCity;
		switch(eCmd)
		{
		case eCmdUpdate:
			oCity = oEditDlg.GetCityData();
			if(GetDocument()->UpdateWhereId(oCity.m_nId, oCity) == FALSE)
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

void CSubscriberPhoneNumbersView::OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint)
{
	if(lHint == 0)
	{
		UpdateColumnsContent();
	}
	else
	{
		UpdateSingleRow(((CSubscriberPhoneNumbers*)lHint)->m_nId);
	}
}

void CSubscriberPhoneNumbersView::UpdateSingleRow(int iRecId)
{
	for(int i = 0; i < m_SubscriberPhoneNumbersArray.GetCount(); i++)
	{
		// Проверка дали ред с такова ID в момента е показан на потребителят 
		if(m_SubscriberPhoneNumbersArray[i]->m_nId == iRecId)
		{			
			CSubscriberPhoneNumbers *poUpdatedSubscriber = new CSubscriberPhoneNumbers;
			if(!GetDocument()->SelectWhereId(iRecId, *poUpdatedSubscriber))
				return;

			delete m_SubscriberPhoneNumbersArray[i];
			m_SubscriberPhoneNumbersArray[i] = poUpdatedSubscriber;
			SetRowData(i, *poUpdatedSubscriber);

			break;
		}
	}
}

void CSubscriberPhoneNumbersView::SetRowData(int iRowIdx, CSubscriberPhoneNumbers &oSubscriberPhoneNumb)
{
	CListCtrl& oListCtrl = GetListCtrl();
	CSubscribers oSubscriber;
	if(!GetDocument()->SelectSubscriberWhereId(oSubscriberPhoneNumb.m_nSubscrId, oSubscriber))
		return;

	CString csTempBuff;
	csTempBuff.Format(_T("%d"),	oSubscriber.m_nCode);
	oListCtrl.SetItemText(iRowIdx, CSubscriberPhoneNumbersDoc::eColSubscrCode,	csTempBuff);

	CPhoneTypes oPhoneType;
	if(!GetDocument()->SelectPhoneTypeWhereId(oSubscriberPhoneNumb.m_nPhoneId, oPhoneType))
		return;

	csTempBuff.Format(_T("%d"),	oPhoneType.m_nCode);
	oListCtrl.SetItemText(iRowIdx, CSubscriberPhoneNumbersDoc::eColPhoneCode, csTempBuff); 

	oListCtrl.SetItemText(iRowIdx, CSubscriberPhoneNumbersDoc::eColPhoneNumber, oSubscriberPhoneNumb.m_szPhoneNumber);
	// Оразмеряване на колоната спрямо дължината на името й 
	oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColSubscrCode, LVSCW_AUTOSIZE_USEHEADER);
	// Оразмеряване на колоната спрямо макс. дължина на неин запис 
	oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColPhoneCode,	 LVSCW_AUTOSIZE_USEHEADER);
	oListCtrl.SetColumnWidth(CSubscriberPhoneNumbersDoc::eColPhoneNumber, LVSCW_AUTOSIZE);
}

// CSubscriberPhoneNumbersView diagnostics

#ifdef _DEBUG
void CSubscriberPhoneNumbersView::AssertValid() const
{
	CListView::AssertValid();
}

void CSubscriberPhoneNumbersView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CSubscriberPhoneNumbersDoc* CSubscriberPhoneNumbersView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSubscriberPhoneNumbersDoc)));
	return (CSubscriberPhoneNumbersDoc*)m_pDocument;
}
#endif //_DEBUG


// CSubscriberPhoneNumbersView message handlers
