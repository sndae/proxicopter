// PersonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Phonebook.h"
#include "PersonDlg.h"
#include ".\persondlg.h"


// CPersonDlg dialog

IMPLEMENT_DYNAMIC(CPersonDlg, CDialog)
CPersonDlg::CPersonDlg(eMenuCmd eCmd, CCitiesArray &oCitiesArr, CPhoneTypesArray &oPhoneTypesArr, 
											 CSubscribersArray &oSubscribersArr, CSubscriberPhoneNumbersArray &oSubscrPhoneNumbsArr, CWnd* pParent)
											: CDialog(CPersonDlg::IDD, pParent)
{
	m_poCitiesArr = &oCitiesArr;
	m_poPhoneTypesArr = &oPhoneTypesArr;
	m_poSubscrbPhoneNumbsArr = &oSubscrPhoneNumbsArr;
	m_poSubscribersArr = &oSubscribersArr;
	m_eMenuCmd = eCmd;
}

CPersonDlg::~CPersonDlg()
{
}

void CPersonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PERSON_EDIT_SUSCR_CODE,	m_cSubscrCode);
	DDX_Control(pDX, IDC_PERSON_EDIT_CITY,			  m_cCities);
	DDX_Control(pDX, IDC_PERSON_EDIT_FIRST_NAME,	m_cFirstName);
	DDX_Control(pDX, IDC_PERSON_EDIT_SECOND_NAME, m_cSecName);
	DDX_Control(pDX, IDC_PERSON_EDIT_THIRD_NAME,	m_cThirdName);
	DDX_Control(pDX, IDC_PERSON_EDIT_SUBSCR_ID,		m_cSubscrId);
	DDX_Control(pDX, IDC_PERSON_EDIT_ADDRESS,			m_cAddress);
	DDX_Control(pDX, IDC_PERSON_EDIT_PHONE_NUMB,	m_cPhoneNumber);
	DDX_Control(pDX, IDC_PERSON_EDIT_PHONE_TYPES, m_cPhoneType);
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
			m_cSubscrCode.EnableWindow(FALSE);
		  m_cCities.EnableWindow(FALSE);
			m_cFirstName.EnableWindow(FALSE);
			m_cSecName.EnableWindow(FALSE);
			m_cThirdName.EnableWindow(FALSE);
			m_cSubscrId.EnableWindow(FALSE);
			m_cAddress.EnableWindow(FALSE);
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
		m_cCities.InsertString(i, m_poCitiesArr->GetAt(i)->m_szName);

	for(int i = 0; i < m_poPhoneTypesArr->GetCount(); i++)
		m_cPhoneType.InsertString(i, m_poPhoneTypesArr->GetAt(i)->m_szType);

	if((m_eMenuCmd == eCmdInsertNumb) || (m_eMenuCmd == eCmdUpdate))
	{
		int iCount = m_poSubscribersArr->GetCount();
		CSubscribers *poSubscr = m_poSubscribersArr->GetAt(m_oPerson.m_iSubscriberId);

		CString csTempBuff;
		csTempBuff.Format(_T("%d"), poSubscr->m_iCode);
		m_cSubscrCode.SetWindowText(csTempBuff);
		
		m_cCities.SetCurSel(m_poCitiesArr->GetAt(poSubscr->m_iCityId)->m_iId);
		m_cFirstName.SetWindowText(poSubscr->m_szFirstName);
		m_cSecName.SetWindowText(poSubscr->m_szSecondName);
		m_cThirdName.SetWindowText(poSubscr->m_szThirdName);
		m_cAddress.SetWindowText(poSubscr->m_szAddress);
		m_cSubscrId.SetWindowText(poSubscr->m_szIDNumb);

		if(m_eMenuCmd == eCmdUpdate)
		{
			CSubscriberPhoneNumbers *poPhoneNumb = m_poSubscrbPhoneNumbsArr->GetAt(m_oPerson.m_iPhoneNumbId); 
			m_cPhoneType.SetCurSel(poPhoneNumb->m_iPhoneId);
			m_cPhoneNumber.SetWindowText(poPhoneNumb->m_szPhoneNumber);
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
	
	//if((m_cPhoneType.GetCurSel() < 0) && (m_eMenuCmd != eCmdFind))
	//	return;


	//if(m_cCities.GetCurSel() >= 0)
	//{
	m_oPhoneNumber.m_iId = m_oPerson.m_iPhoneNumbId;
	m_oPhoneNumber.m_iPhoneId = (m_cPhoneType.GetCurSel() != -1 ?  m_poPhoneTypesArr->GetAt(m_cPhoneType.GetCurSel())->m_iId : DNC);
	m_cPhoneNumber.GetWindowText(m_oPhoneNumber.m_szPhoneNumber, SUBSCRIBERPHONENUMBERS_TABLE_STRING_MAX_LEN);
	m_oPhoneNumber.m_iSubscrId = m_oPerson.m_iSubscriberId;

	//}
	//else if(m_eMenuCmd != eCmdFind)
	//{
	//	return;
	//}

	m_oSubscriber.m_iId = m_oPerson.m_iSubscriberId;
	
	m_oSubscriber.m_iCityId = m_poCitiesArr->GetAt(m_cCities.GetCurSel())->m_iId;
	m_cFirstName.GetWindowText(m_oSubscriber.m_szFirstName, SUBSCRIBERS_TABLE_STRING_MAX_LEN);
	m_cSecName.GetWindowText(m_oSubscriber.m_szSecondName, SUBSCRIBERS_TABLE_STRING_MAX_LEN);
	m_cThirdName.GetWindowText(m_oSubscriber.m_szThirdName, SUBSCRIBERS_TABLE_STRING_MAX_LEN);
	m_cAddress.GetWindowText(m_oSubscriber.m_szAddress, SUBSCRIBERS_TABLE_STRING_MAX_LEN);
	m_cSubscrId.GetWindowText(m_oSubscriber.m_szIDNumb, SUBSCRIBERS_ID_NUMB_LEN);
	
	CString csTempBuff;
	m_cSubscrCode.GetWindowText(csTempBuff);
	m_oSubscriber.m_iCode = _ttoi(csTempBuff);

	OnOK();
}

INT_PTR	 CPersonDlg::DoModal(const CPerson *poPerson)
{
	if(poPerson)
		m_oPerson = *poPerson;

	return CDialog::DoModal();
}
