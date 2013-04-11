// PersonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Phonebook.h"
#include "PersonDlg.h"
#include ".\persondlg.h"


// CPersonDlg dialog

IMPLEMENT_DYNAMIC(CPersonDlg, CDialog)
CPersonDlg::CPersonDlg(eMenuCmd eCmd, CCitiesArray &oCitiesArr, CPhoneTypesArray &oPhoneTypesArr, 
											 CSubscribers &oSubscriber, CSubscriberPhoneNumbers &oSubscrPhoneNumb, CWnd* pParent)
											: CDialog(CPersonDlg::IDD, pParent)
{
	m_poCitiesArr = &oCitiesArr;
	m_poPhoneTypesArr = &oPhoneTypesArr;
	m_oPhoneNumberTab = oSubscrPhoneNumb;
	m_oSubscriberTab = oSubscriber;
	m_eMenuCmd = eCmd;
}

CPersonDlg::~CPersonDlg()
{
}

void CPersonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, EDB_PERSON_EDIT_SUSCR_CODE,	m_oSubscrCode);
	DDX_Control(pDX, CMB_PERSON_EDIT_CITY,			  m_oCities);
	DDX_Control(pDX, EDB_PERSON_EDIT_FIRST_NAME,	m_oFirstName);
	DDX_Control(pDX, EDB_PERSON_EDIT_SECOND_NAME, m_oSecName);
	DDX_Control(pDX, EDB_PERSON_EDIT_THIRD_NAME,	m_oThirdName);
	DDX_Control(pDX, EDB_PERSON_EDIT_SUBSCR_ID,		m_oSubscrId);
	DDX_Control(pDX, EDB_PERSON_EDIT_ADDRESS,			m_oAddress);
	DDX_Control(pDX, EDB_PERSON_EDIT_PHONE_NUMB,	m_oPhoneNumber);
	DDX_Control(pDX, CMB_PERSON_EDIT_PHONE_TYPES, m_oPhoneType);
}



BOOL CPersonDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	switch(m_eMenuCmd)
	{
		case eCmdFind:	 
			SetWindowText(MENU_CMD_FIND); 
			break;
		case eCmdUpdate: 
			SetWindowText(MENU_CMD_UPDATE); 
			break;
		case eCmdInsertNumb: 
			SetWindowText(MENU_CMD_INSERT_NUMBER); 
			m_oSubscrCode.EnableWindow(FALSE);
		  m_oCities.EnableWindow(FALSE);
			m_oFirstName.EnableWindow(FALSE);
			m_oSecName.EnableWindow(FALSE);
			m_oThirdName.EnableWindow(FALSE);
			m_oSubscrId.EnableWindow(FALSE);
			m_oAddress.EnableWindow(FALSE);
			break;
		case eCmdInsertSubscr: 
			SetWindowText(MENU_CMD_INSERT_SUBSCRIBER); 
			break;
		case eCmdDelNumb: 
			SetWindowText(MENU_CMD_DELETE_NUMBER); 
			break;
		case eCmdDelSubscr: 
			SetWindowText(MENU_CMD_DELETE_SUBSCRIBER); 
			break;

		default: 
			ASSERT(0);
			break;
	}
	for(int i = 0; i < m_poCitiesArr->GetCount(); i++)
		m_oCities.InsertString(i, m_poCitiesArr->GetAt(i)->m_szName);

	for(int i = 0; i < m_poPhoneTypesArr->GetCount(); i++)
		m_oPhoneType.InsertString(i, m_poPhoneTypesArr->GetAt(i)->m_szType);

	if((m_eMenuCmd == eCmdInsertNumb) || (m_eMenuCmd == eCmdUpdate))
	{
		CString csTempBuff;
		csTempBuff.Format(_T("%d"), m_oSubscriberTab.m_nCode);
		m_oSubscrCode.SetWindowText(csTempBuff);
		
		int iPos = 0;
		for(iPos = 0; iPos != m_poCitiesArr->GetCount(); iPos++)
		{
			if(m_poCitiesArr->GetAt(iPos)->m_nId == m_oSubscriberTab.m_nCityId)
				break;
		}

		m_oCities.SetCurSel(iPos);
		m_oFirstName.SetWindowText(m_oSubscriberTab.m_szFirstName);
		m_oSecName.SetWindowText(m_oSubscriberTab.m_szSecondName);
		m_oThirdName.SetWindowText(m_oSubscriberTab.m_szThirdName);
		m_oAddress.SetWindowText(m_oSubscriberTab.m_szAddress);
		m_oSubscrId.SetWindowText(m_oSubscriberTab.m_szIDNumb);

		if(m_eMenuCmd == eCmdUpdate)
		{
			for(iPos = 0; iPos < m_poPhoneTypesArr->GetCount(); iPos++)
			{
				if(m_poPhoneTypesArr->GetAt(iPos)->m_nId == m_oPhoneNumberTab.m_nPhoneId)
					break;
			}
			
			m_oPhoneType.SetCurSel(iPos);
			m_oPhoneNumber.SetWindowText(m_oPhoneNumberTab.m_szPhoneNumber);
		}
	}

	return TRUE;
}


BEGIN_MESSAGE_MAP(CPersonDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CPersonDlg message handlers

void CPersonDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	
	//if((m_oPhoneType.GetCurSel() < 0) && (m_eMenuCmd != eCmdFind))
	//	return;


	//if(m_oCities.GetCurSel() >= 0)
	//{
	if((m_eMenuCmd != eCmdInsertNumb) && (m_eMenuCmd != eCmdInsert))
		m_oPhoneNumberTab.m_nId = m_oPerson.m_nPhoneNumbId;
	else
		m_oPhoneNumberTab.m_nId = DNC;
	
	m_oPhoneNumberTab.m_nPhoneId = (m_oPhoneType.GetCurSel() != -1 ?  m_poPhoneTypesArr->GetAt(m_oPhoneType.GetCurSel())->m_nId : DNC);
	m_oPhoneNumber.GetWindowText(m_oPhoneNumberTab.m_szPhoneNumber, SUBSCRIBERPHONENUMBERS_TABLE_STRING_MAX_LEN);
	m_oPhoneNumberTab.m_nSubscrId = m_oPerson.m_nSubscriberId;

	//}
	//else if(m_eMenuCmd != eCmdFind)
	//{
	//	return;
	//}

	if(m_eMenuCmd != eCmdInsert)
		m_oSubscriberTab.m_nId = m_oPerson.m_nSubscriberId;
	else
		m_oSubscriberTab.m_nId = DNC;

	m_oSubscriberTab.m_nCityId = m_poCitiesArr->GetAt(m_oCities.GetCurSel())->m_nId;
	m_oFirstName.GetWindowText(m_oSubscriberTab.m_szFirstName, SUBSCRIBERS_TABLE_STRING_MAX_LEN);
	m_oSecName.GetWindowText(m_oSubscriberTab.m_szSecondName, SUBSCRIBERS_TABLE_STRING_MAX_LEN);
	m_oThirdName.GetWindowText(m_oSubscriberTab.m_szThirdName, SUBSCRIBERS_TABLE_STRING_MAX_LEN);
	m_oAddress.GetWindowText(m_oSubscriberTab.m_szAddress, SUBSCRIBERS_TABLE_STRING_MAX_LEN);
	m_oSubscrId.GetWindowText(m_oSubscriberTab.m_szIDNumb, SUBSCRIBERS_ID_NUMB_LEN);
	
	CString csTempBuff;
	m_oSubscrCode.GetWindowText(csTempBuff);
	m_oSubscriberTab.m_nCode = _ttoi(csTempBuff);

	OnOK();
}

INT_PTR	 CPersonDlg::DoModal(const CPerson *poPerson)
{
	if(poPerson)
		m_oPerson = *poPerson;

	return CDialog::DoModal();
}
