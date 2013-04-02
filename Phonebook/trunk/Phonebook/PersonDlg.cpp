// PersonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Phonebook.h"
#include "PersonDlg.h"


// CPersonDlg dialog

IMPLEMENT_DYNAMIC(CPersonDlg, CDialog)
CPersonDlg::CPersonDlg(const eMenuCmd eCmd, const CPerson &oPerson , const CSubscriberPhoneNumbers &oPhoneNumb, const CPhoneTypes &oPhoneType, 
											 CCitiesArray &oCitiesArr, CPhoneTypesArray &oPhoneTypesArr, CWnd* pParent)
											: CDialog(CPersonDlg::IDD, pParent)
{
	m_oPerson = oPerson;
	m_poCitiesArr = &oCitiesArr;
	m_poPhoneTypesArr = &oPhoneTypesArr;
	m_oPhoneNumb = oPhoneNumb;
	m_oPhoneType = oPhoneType;
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
			ZeroMemory(&m_oPerson, sizeof(m_oPerson)); 
			break;
		case eCmdUpdate: 
			SetWindowText(MENU_CMD_UPDATE); 
			break;
		case eCmdInsert: 
			SetWindowText(MENU_CMD_INSERT); 
			ZeroMemory(&m_oPerson, sizeof(m_oPerson)); 
			break;
		default: 
			ASSERT(0);
			break;
	}

	CString csTempBuff;
	csTempBuff.Format(_T("%d"), m_oPerson.m_tSubscriber.m_iCode);
	m_cSubscrCode.SetWindowText(csTempBuff);

	for(int i = 0; i < m_poCitiesArr->GetCount(); i++)
		m_cCities.InsertString(i, m_poCitiesArr->GetAt(i)->m_szName);
	
	m_cCities.SetWindowText(m_oPerson.m_tCity.m_szName);

	for(int i = 0; i < m_poPhoneTypesArr->GetCount(); i++)
		m_cPhoneType.InsertString(i, m_poPhoneTypesArr->GetAt(i)->m_szType);
	
	m_cPhoneType.SetWindowText(m_oPhoneType.m_szType);
	m_cFirstName.SetWindowText(m_oPerson.m_tSubscriber.m_szFirstName);
	m_cSecName.SetWindowText(m_oPerson.m_tSubscriber.m_szSecondName);
	m_cThirdName.SetWindowText(m_oPerson.m_tSubscriber.m_szThirdName);
	m_cSubscrCode.SetWindowText(m_oPerson.m_tSubscriber.m_szIDNumb);
	m_cAddress.SetWindowText(m_oPerson.m_tSubscriber.m_szAddress);
	m_cSubscrId.SetWindowText(m_oPerson.m_tSubscriber.m_szIDNumb);
	m_cPhoneNumber.SetWindowText(m_oPhoneNumb.m_szPhoneNumber);

	return TRUE;
}


BEGIN_MESSAGE_MAP(CPersonDlg, CDialog)
END_MESSAGE_MAP()


// CPersonDlg message handlers
