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
        //GetDocument()->SortByColumn((CCitiesDoc::eColumn)iNumb, m_abAscSorting[iNumb]);
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

void CPersonView::ExecuteCntxMenuCmd(eMenuCmd eCmd)
{
	int iPersonSelected = 0;
	
	int i = 0;
	for( ; i < m_iCurrRowSelected; i += m_PersonsArray[iPersonSelected - 1]->m_oPhoneNumbsArr.GetCount())
	{
		if((i + m_PersonsArray[iPersonSelected]->m_oPhoneNumbsArr.GetCount()) <= m_iCurrRowSelected)
			iPersonSelected++;
		else
			break;
	}

	CSubscriberPhoneNumbers *poPhoneNumbSelected = m_PersonsArray[iPersonSelected]->m_oPhoneNumbsArr[m_iCurrRowSelected - i];
	CPerson *poPersons = m_PersonsArray[iPersonSelected];

	if(eCmd == eCmdDelete)
	{
		//GetDocument()->DeleteWhereId(oPersons.m_iId);
	}
	else
	{
		CCitiesArray oCitiesArr;
		GetDocument()->SelectAllCities(oCitiesArr);
		CPhoneTypesArray oPhoneTyopesArr;
		GetDocument()->SelectAllPhoneTypes(oPhoneTyopesArr);
		CPersonDlg oEditDlg(eCmd, poPersons, poPhoneNumbSelected, &(GetDocument()->GetPhoneType(*poPhoneNumbSelected)), &oCitiesArr, &oPhoneTyopesArr);
		if(oEditDlg.DoModal() != IDOK)
			return;

		CPerson oPerson;
		switch(eCmd)
		{
		case eCmdUpdate:
			//oPerson = oEditDlg.GetCityData();
			//if(GetDocument()->UpdateWhereId(oPhoneType.m_iId, oPhoneType) == FALSE)
			//	MessageBox(_T("Грешка при запис.\nВалидарайте записа или го опреснете"), 0, MB_OK|MB_ICONWARNING);
			
			break;
		case eCmdInsert:
			//oPhoneType = oEditDlg.GetCityData();
			//if(GetDocument()->Insert(oPhoneType) == FALSE)
			//	MessageBox(_T("Грешка при запис.\nВалидарайте записа"), 0, MB_OK|MB_ICONWARNING); 
			break;
		case eCmdFind:
			//oPhoneType = oEditDlg.GetCityData();
			//GetDocument()->SelectByContent(oPhoneType);
			UpdateColumnsContent();
			break;
		default:
			ASSERT(0);
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
	      
				SetRowData(iRowIdx, *m_PersonsArray[i], *m_PersonsArray[i]->m_oPhoneNumbsArr[m_PersonsArray[i]->m_oPhoneNumbsArr.GetCount() - c - 1]);
			}
    }
  }
}

void CPersonView::SetRowData(int iRowIdx, CPerson &oPerson, CSubscriberPhoneNumbers &oPhoneNumber)
{
	CListCtrl& oListCtrl = GetListCtrl();
	oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColCity,				oPerson.m_tCity.m_szName);
	oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColFirstName,		oPerson.m_tSubscriber.m_szFirstName);
	oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColSecondName,	oPerson.m_tSubscriber.m_szSecondName);
  oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColThirdName,		oPerson.m_tSubscriber.m_szThirdName);
  oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColIdNumb,			oPerson.m_tSubscriber.m_szIDNumb);
  oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColAddress,			oPerson.m_tSubscriber.m_szAddress);
	oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColPhoneNumber, oPhoneNumber.m_szPhoneNumber);
	oListCtrl.SetItemText(iRowIdx, CPersonDoc::eColPhoneNumberType, GetDocument()->GetPhoneType(oPhoneNumber).m_szType); 
	
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
