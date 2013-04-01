// PersonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Phonebook.h"
#include "PersonDlg.h"


// CPersonDlg dialog

IMPLEMENT_DYNAMIC(CPersonDlg, CDialog)
CPersonDlg::CPersonDlg(eMenuCmd eCmd, CPerson *poPerson , CCitiesArray *poCitiesArr, CPhoneTypesArray *poPhoneTypesArr, CWnd* pParent /*=NULL*/)
	: CDialog(CPersonDlg::IDD, pParent)
{
	m_oPerson = *poPerson;
	m_poCitiesArr = poCitiesArr;
	m_poPhoneTypesArr = poPhoneTypesArr;

	m_eMenuCmd = eCmd;
}

CPersonDlg::~CPersonDlg()
{
}

void CPersonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PERSON_EDIT_SUSCR_CODE, m_oSubscrCode);
	DDX_Control(pDX, IDC_PERSON_EDIT_CITY, m_oCities);
	DDX_Control(pDX, IDC_PERSON_EDIT_FIRST_NAME, m_oFirstName);
	DDX_Control(pDX, IDC_PERSON_EDIT_SECOND_NAME, m_SecName);
	DDX_Control(pDX, IDC_PERSON_EDIT_THIRD_NAME, m_oThirdName);
	DDX_Control(pDX, IDC_PERSON_EDIT_SUBSCR_ID, m_SubscrId);
	DDX_Control(pDX, IDC_PERSON_EDIT_ADDRESS, m_oAddress);
	DDX_Control(pDX, IDC_PERSON_EDIT_PHONE_NUMB, m_oPhoneNumber);
	DDX_Control(pDX, IDC_PERSON_EDIT_PHONE_TYPES, m_oPhoneType);
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
	m_oSubscrCode.SetWindowText(csTempBuff);

	for(int i = 0; i < m_poCitiesArr->GetCount(); i++)
		m_oCities.InsertString(i, m_poCitiesArr->GetAt(i)->m_szName);
	
	m_oCities.SetWindowText(m_oPerson.m_tCity.m_szName);

	for(int i = 0; i < m_poPhoneTypesArr->GetCount(); i++)
		m_oPhoneType.InsertString(i, m_poPhoneTypesArr->GetAt(i)->m_szType);
	
	//m_oPhoneType.SetWindowText(m_oPerson.m_tSubscriber.
	//m_oPhoneType.SetWindowTextW(m_oPhoneTyp .m_szType);
	m_oFirstName.SetWindowText(m_oPerson.m_tSubscriber.m_szFirstName);
	m_SecName.SetWindowText(m_oPerson.m_tSubscriber.m_szSecondName);
	m_oThirdName.SetWindowText(m_oPerson.m_tSubscriber.m_szThirdName);
	m_oSubscrCode.SetWindowText(m_oPerson.m_tSubscriber.m_szIDNumb);
	m_oAddress.SetWindowText(m_oPerson.m_tSubscriber.m_szAddress);
	m_SubscrId.SetWindowText(m_oPerson.m_tSubscriber.m_szIDNumb);
	//m_oPhoneNumber.SetWindowText(m_oPerson.m_oPhoneNumbsArr[]);

	return TRUE;
}


BEGIN_MESSAGE_MAP(CPersonDlg, CDialog)
END_MESSAGE_MAP()


// CPersonDlg message handlers
