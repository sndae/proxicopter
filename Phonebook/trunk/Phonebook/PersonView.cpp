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
	int iPersonSelected = 0;
	
	int i = 0;
	for( ; i < m_iCurrRowSelected; i += m_PersonsArray[iPersonSelected - 1]->m_oPhoneNumbsArr.GetCount())
	{
		if((i + m_PersonsArray[iPersonSelected]->m_oPhoneNumbsArr.GetCount()) <= m_iCurrRowSelected)
			iPersonSelected++;
		else
			break;
	}

	int iPhoneNumbSelected = m_iCurrRowSelected - i;
	CPerson *poPerson = m_PersonsArray[iPersonSelected];
	if(eCmd == eCmdDelSubscr)
	{
		GetDocument()->DeleteWhereId(poPerson->m_iId);
	}
	else if(eCmd == eCmdDelNumb)
	{
		GetDocument()->DeleteSubscrPhoneNumb(poPerson->m_oPhoneNumbsArr[iPhoneNumbSelected]->m_iId);
	}
	else
	{
		CCitiesArray oCitiesArr;
		GetDocument()->SelectAllCities(oCitiesArr);
		CPhoneTypesArray oPhoneTyopesArr;
		GetDocument()->SelectAllPhoneTypes(oPhoneTyopesArr);
		
		CPersonDlg oEditDlg(eCmd, oCitiesArr, oPhoneTyopesArr);	
		
		switch(eCmd)
		{
		case eCmdInsertNumb: 
			if(IDOK != oEditDlg.DoModal(poPerson, DNC, DNC))
				return;

			poPerson = oEditDlg.GetPerson();
			if(!GetDocument()->InsertPhoneNumber(*poPerson->m_oPhoneNumbsArr[poPerson->m_oPhoneNumbsArr.GetCount() - 1]))
				MessageBox(_T("Грешка при запис.\nВалидарайте записа или го опреснете"), 0, MB_OK|MB_ICONWARNING);
			break;
		case eCmdInsertSubscr:
			if(IDOK != oEditDlg.DoModal(0))
				return;

			poPerson = oEditDlg.GetPerson();

			if(!GetDocument()->Insert(*poPerson))
				MessageBox(_T("Грешка при запис.\nВалидарайте записа или го опреснете"), 0, MB_OK|MB_ICONWARNING);
			break;
		case eCmdUpdate:			
			if(IDOK != oEditDlg.DoModal(poPerson, iPersonSelected, iPhoneNumbSelected))
				return;

			poPerson = oEditDlg.GetPerson();
			if(!GetDocument()->UpdateWhereId(poPerson->m_iId, *poPerson))
				MessageBox(_T("Грешка при запис.\nВалидарайте записа или го опреснете"), 0, MB_OK|MB_ICONWARNING);
			break;
		case eCmdFind:
			if(IDOK != oEditDlg.DoModal(0))
				return;

			poPerson = oEditDlg.GetPerson();

			if(!GetDocument()->SelectByContent(*poPerson))
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
		UpdateSingleRow(((CPerson*)lHint)->m_iId);
	}
}

void CPersonView::UpdateSingleRow(int iRecId)
{
  /* Проверка дали ред с такова ID в момента е показан на потребителят */
	for(int i = 0; i < m_PersonsArray.GetCount(); i++)
	{
		if(m_PersonsArray[i]->m_iId == iRecId)
		{      
			CPerson *poUpdPerson= new CPerson;
			if(!GetDocument()->SelectWhereId(iRecId, *poUpdPerson))
				return;

			delete m_PersonsArray[i];
			m_PersonsArray[i] = poUpdPerson;
			for(int c = 0; c < poUpdPerson->m_oPhoneNumbsArr.GetCount(); c++)
			{
				SetRowData(c, *poUpdPerson, *poUpdPerson->m_oPhoneNumbsArr[c]);
			}
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
  if(!GetDocument()->SelectAll(m_PersonsArray))
		return;

	UpdateColumnsContent(m_PersonsArray);
}

void CPersonView::UpdateColumnsContent(CPersonArray &oPersonsArr)
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
