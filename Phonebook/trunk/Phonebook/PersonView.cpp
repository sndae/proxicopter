// PersonView.cpp : implementation file
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "PersonView.h"
#include "PersonDlg.h"

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
				oCntxMenu.LoadMenuW(IDR_PERSONS_MENU);
        pSubMenu = oCntxMenu.GetSubMenu(0);
        GetCursorPos(&tCur);
        iMenuChoice = pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD, tCur.x, tCur.y, this);
        /* изпълнение на команда, избрана от конктекстното меню */
        switch(iMenuChoice)
        {
					case ID_OPTIONS_PERSON_EDIT					 :ExecuteCntxMenuCmd(eCmdUpdate); break;
					case ID_OPTIONS_PERSON_ADD_SUBSCR    :ExecuteCntxMenuCmd(eCmdInsertSubscr); break;
					case ID_OPTIONS_PERSON_ADD_NUMB			 :ExecuteCntxMenuCmd(eCmdInsertNumb); break;        
					case ID_OPTIONS_PERSON_DELETE_SUBSCR :ExecuteCntxMenuCmd(eCmdDelSubscr);  break; 
					case ID_OPTIONS_PERSON_DELETE_NUMB	 :ExecuteCntxMenuCmd(eCmdDelNumb); break; 	
					case ID_OPTIONS_PERSON_FIND 				 :ExecuteCntxMenuCmd(eCmdFind); break;
					default: break; 
        }
        break;
      case LVN_COLUMNCLICK:
        /* Сортиране по номер на колона */
        iNumb = ((LPNMLISTVIEW)lParam)->iSubItem;
        m_abAscSorting[iNumb] = !m_abAscSorting[iNumb];
				m_PersonsArray.RemoveAndFreeAll();
				if(GetDocument()->SelectAll(m_PersonsArray, (CPersonDoc::eColumn)iNumb, m_abAscSorting[iNumb]))
	        UpdateColumnsContent(m_PersonsArray);
        
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

void CPersonView::ExecuteCntxMenuCmd(eMenuCmd eCmd)
{
	CPerson *poPerson = m_PersonsArray[m_iCurrRowSelected];
	if(eCmd == eCmdDelSubscr)
	{
		GetDocument()->DeleteWhereId(poPerson->m_iSubscriberId);
	}
	else if(eCmd == eCmdDelNumb)
	{
		GetDocument()->DeleteSubscrPhoneNumb(poPerson->m_iPhoneNumbId);
	}
	else
	{
		CCitiesArray oCitiesArr;
		int iCount;
		if(!GetDocument()->SelectAllCities(oCitiesArr))
			return;

		CPhoneTypesArray oPhoneTyopesArr;
		if(!GetDocument()->SelectAllPhoneTypes(oPhoneTyopesArr))
			return;
		CSubscriberPhoneNumbers oSubscrPhoneNumb;
		if(!GetDocument()->SelectPhoneNumberWhereId(poPerson->m_iPhoneNumbId, oSubscrPhoneNumb))
			return;
		CSubscribers oSubscriber;		
		if(!GetDocument()->SelectSubscriberWhereId(poPerson->m_iSubscriberId, oSubscriber))
			return;
		
		CPersonDlg oEditDlg(eCmd, oCitiesArr, oPhoneTyopesArr, oSubscriber, oSubscrPhoneNumb);	
		
		switch(eCmd)
		{
		case eCmdInsertNumb: 
			if(IDOK != oEditDlg.DoModal(poPerson))
				return;

			if(!GetDocument()->Insert(oEditDlg.GetSubscriber(), oEditDlg.GetPhoneNumber()))
				MessageBox(_T("Грешка при запис.\nВалидарайте записа или го опреснете"), 0, MB_OK|MB_ICONWARNING);
			break;
		case eCmdInsertSubscr:
			if(IDOK != oEditDlg.DoModal(0))
				return;

			if(!GetDocument()->Insert(oEditDlg.GetSubscriber(), oEditDlg.GetPhoneNumber()))
				MessageBox(_T("Грешка при запис.\nВалидарайте записа или го опреснете"), 0, MB_OK|MB_ICONWARNING);
			break;
		case eCmdUpdate:			
			if(IDOK != oEditDlg.DoModal(poPerson))
				return;

			if(!GetDocument()->UpdateWhereId(oEditDlg.GetPerson(), oEditDlg.GetSubscriber(), oEditDlg.GetPhoneNumber()))
				MessageBox(_T("Грешка при запис.\nВалидарайте записа или го опреснете"), 0, MB_OK|MB_ICONWARNING);
			break;
		case eCmdFind:
			if(IDOK != oEditDlg.DoModal(0))
				return;

			if(!GetDocument()->SelectByContent(oEditDlg.GetSubscriber(), oEditDlg.GetPhoneNumber()))
				MessageBox(_T("Грешка при търсене.\nВалидарайте записа"), 0, MB_OK|MB_ICONWARNING);
			
			UpdateColumnsContent();
							
			break;
		default:
			ASSERT(0);
		}
	}
}

void CPersonView::OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint)
{
	if(lHint == 0)
	{
		UpdateColumnsContent();
	}
	else
	{
		UpdateSingleRow(*((CPerson*)lHint));
	}
}

void CPersonView::UpdateSingleRow(CPerson &oUpdPerson)
{
  /* Проверка дали ред с такова ID в момента е показан на потребителят */
	for(int i = 0; i < m_PersonsArray.GetCount(); i++)
	{
		if(m_PersonsArray[i]->m_iId == oUpdPerson.m_iId)
		{      
			*m_PersonsArray[i] = oUpdPerson;
			InsertNewRow(oUpdPerson);
			break;
		}
	}
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
	oListCtrl.InsertColumn(CPersonDoc::eColCity,					 _T("Град"), LVCFMT_LEFT);
	oListCtrl.InsertColumn(CPersonDoc::eColFirstName,      _T("Първо име"), LVCFMT_LEFT);
	oListCtrl.InsertColumn(CPersonDoc::eColSecondName,     _T("Второ име"), LVCFMT_LEFT);
	oListCtrl.InsertColumn(CPersonDoc::eColThirdName,      _T("Трето име"), LVCFMT_LEFT);
	oListCtrl.InsertColumn(CPersonDoc::eColIdNumb,				 _T("ЕГН"), LVCFMT_LEFT);
	oListCtrl.InsertColumn(CPersonDoc::eColAddress,				 _T("Адрес"), LVCFMT_LEFT);

	oListCtrl.InsertColumn(CPersonDoc::eColPhoneNumber,    _T("Телефонен номер"), LVCFMT_LEFT);
	oListCtrl.InsertColumn(CPersonDoc::eColPhoneNumberType,_T("Тип телефон"), LVCFMT_LEFT);

	/* Оразмеряване на колонита спрямо дължината на имената им */
	oListCtrl.SetColumnWidth(CPersonDoc::eColSubscrCode,     LVSCW_AUTOSIZE_USEHEADER);
	oListCtrl.SetColumnWidth(CPersonDoc::eColFirstName,      LVSCW_AUTOSIZE_USEHEADER);
	oListCtrl.SetColumnWidth(CPersonDoc::eColSecondName,     LVSCW_AUTOSIZE_USEHEADER);
	oListCtrl.SetColumnWidth(CPersonDoc::eColThirdName,      LVSCW_AUTOSIZE_USEHEADER);
	oListCtrl.SetColumnWidth(CPersonDoc::eColIdNumb,				 LVSCW_AUTOSIZE_USEHEADER);
	oListCtrl.SetColumnWidth(CPersonDoc::eColAddress,				 LVSCW_AUTOSIZE_USEHEADER);
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
	if(!GetDocument()->SelectAll(m_PersonsArray, CPersonDoc::eColFirstName))
		return;

	UpdateColumnsContent(m_PersonsArray);
}

void CPersonView::UpdateColumnsContent(CPersonArray &oPersonsArr)
{
	CListCtrl& oListCtrl = GetListCtrl();   
  oListCtrl.DeleteAllItems();
	for(int i = oPersonsArr.GetCount() - 1; i != -1; i--)
  {
		InsertNewRow(*oPersonsArr[i]);
	}  
}

void CPersonView::InsertNewRow(CPerson &oPerson)
{
	CListCtrl& oListCtrl = GetListCtrl();
	CSubscribers oSubscriber;
	if(!GetDocument()->SelectSubscriberWhereId(oPerson.m_iSubscriberId, oSubscriber))
		return;

	CCities oCity;
	if(!GetDocument()->SelectCityWhereId(oSubscriber.m_iCityId, oCity))
		return;

	CSubscriberPhoneNumbers oPhoneNumber;
	if(!GetDocument()->SelectPhoneNumberWhereId(oPerson.m_iPhoneNumbId, oPhoneNumber))
		return;

	CString csTempBuff;
	csTempBuff.Format(_T("%d"), oSubscriber.m_iCode);
	int iRowIdx = oListCtrl.InsertItem(CPersonDoc::eColSubscrCode, csTempBuff);
	oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColCity,				oCity.m_szName);
	oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColFirstName,		oSubscriber.m_szFirstName);
	oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColSecondName,	oSubscriber.m_szSecondName);
  oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColThirdName,		oSubscriber.m_szThirdName);
  oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColIdNumb,			oSubscriber.m_szIDNumb);
  oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColAddress,			oSubscriber.m_szAddress);
	oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColPhoneNumber, oPhoneNumber.m_szPhoneNumber);
	CPhoneTypes oPhoneType;
	if(GetDocument()->SelectPhoneTypeWhereId(oPhoneNumber.m_iPhoneId, oPhoneType))
		oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColPhoneNumberType, oPhoneType.m_szType); 
	
	/* Оразмеряване на колоната спрямо дължината на името й */
  oListCtrl.SetColumnWidth(CPersonDoc::eColSubscrCode, LVSCW_AUTOSIZE_USEHEADER);
  /* Оразмеряване на колоната спрямо макс. дължина на неин запис */
  oListCtrl.SetColumnWidth(CPersonDoc::eColCity,			 LVSCW_AUTOSIZE);
  oListCtrl.SetColumnWidth(CPersonDoc::eColFirstName,  LVSCW_AUTOSIZE);
  oListCtrl.SetColumnWidth(CPersonDoc::eColSecondName, LVSCW_AUTOSIZE);
  oListCtrl.SetColumnWidth(CPersonDoc::eColThirdName,  LVSCW_AUTOSIZE);
  oListCtrl.SetColumnWidth(CPersonDoc::eColIdNumb,     LVSCW_AUTOSIZE);
  oListCtrl.SetColumnWidth(CPersonDoc::eColAddress,    LVSCW_AUTOSIZE);
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
