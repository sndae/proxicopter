// SubscribersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "SubscribersDlg.h"


// CSubscribersDlg dialog

IMPLEMENT_DYNAMIC(CSubscribersDlg, CDialog)

CSubscribersDlg::CSubscribersDlg(const CSubscribers &oSubscribers, eMenuCmd eCmd, CCitiesArray *pCitiesArray, CWnd* pParent /*=NULL*/)
	: CDialog(CSubscribersDlg::IDD, pParent)
{
	m_oSubscribers = oSubscribers;
	m_eMenuCmd = eCmd;
	m_pCitiesArray = pCitiesArray;
}

CSubscribersDlg::~CSubscribersDlg()
{
}

BOOL CSubscribersDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	switch(m_eMenuCmd)
	{
		case eCmdFind:	 
			SetWindowText(MENU_CMD_FIND); 
			ZeroMemory(&m_oSubscribers, sizeof(m_oSubscribers)); 
			m_oSubscribers.m_nCode = DNC;
			break;
		case eCmdUpdate: 
			SetWindowText(MENU_CMD_UPDATE); 
			break;
		case eCmdInsert: 
			SetWindowText(MENU_CMD_INSERT); 
			ZeroMemory(&m_oSubscribers, sizeof(m_oSubscribers)); 
			m_oSubscribers.m_nCode = DNC;
			break;
		default: 
			ASSERT(0);
			break;
	}
	CString csTembBuff;
	if(m_oSubscribers.m_nCode != DNC)
	{
		csTembBuff.Format(_T("%d"), m_oSubscribers.m_nCode);
		m_oCode.SetWindowTextW(csTembBuff);
	}
	else
		m_oCode.SetWindowTextW(_T(""));

	m_oFirstName.SetWindowTextW(m_oSubscribers.m_szFirstName);
	m_oSecondName.SetWindowTextW(m_oSubscribers.m_szSecondName);
	m_oThirdName.SetWindowTextW(m_oSubscribers.m_szThirdName);
	m_oIDNumber.SetWindowTextW(m_oSubscribers.m_szIDNumb);
	if(m_pCitiesArray)
	{
		for(int i = 0; i < m_pCitiesArray->GetSize(); i++)
			m_CityCode.InsertString(i, (m_pCitiesArray->GetAt(i))->m_szCode);
	}
	if(m_oSubscribers.m_nCityId != DNC)
	{
		for(int i = 0; i < m_pCitiesArray->GetCount(); i++)
		{
			if(m_pCitiesArray->GetAt(i)->m_nId == m_oSubscribers.m_nCityId)
			{
				m_CityCode.SetWindowTextW(m_pCitiesArray->GetAt(i)->m_szCode);
				break;
			}
		}
	}
	m_Address.SetWindowTextW(m_oSubscribers.m_szAddress);

	return TRUE;

}
void CSubscribersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, EDB_SUBSCRIBERS_EDIT_CODE, m_oCode);
	DDX_Control(pDX, EDB_SUBSCRIBERS_EDIT_FIRST_NAME, m_oFirstName);
	DDX_Control(pDX, EDB_SUBSCRIBERS_EDIT_SECOND_NAME, m_oSecondName);
	DDX_Control(pDX, EDB_SUBSCRIBERS_EDIT_THIRD_NAME, m_oThirdName);
	DDX_Control(pDX, EDB_SUBSCRIBERS_EDIT_IDNUMBER, m_oIDNumber);
	DDX_Control(pDX, CMB_SUBSCRIBERS_EDIT_CITY_CODE, m_CityCode);
	DDX_Control(pDX, EDB_SUBSCRIBERS_EDIT_ADDRESS, m_Address);
}


BEGIN_MESSAGE_MAP(CSubscribersDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CSubscribersDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSubscribersDlg message handlers

void CSubscribersDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString cTempBuff;
	m_oCode.GetWindowTextW(cTempBuff);
	if(cTempBuff.GetLength())
		m_oSubscribers.m_nCode = _ttoi(cTempBuff);
	else
		m_oSubscribers.m_nCode = DNC;

	m_oFirstName.GetWindowTextW(m_oSubscribers.m_szFirstName, SUBSCRIBERS_TABLE_STRING_MAX_LEN);
	m_oSecondName.GetWindowTextW(m_oSubscribers.m_szSecondName, SUBSCRIBERS_TABLE_STRING_MAX_LEN);
	m_oThirdName.GetWindowTextW(m_oSubscribers.m_szThirdName, SUBSCRIBERS_TABLE_STRING_MAX_LEN);
	m_oIDNumber.GetWindowTextW(m_oSubscribers.m_szIDNumb, SUBSCRIBERS_ID_NUMB_LEN);
	m_Address.GetWindowTextW(m_oSubscribers.m_szAddress, SUBSCRIBERS_TABLE_STRING_MAX_LEN);
	
	m_oSubscribers.m_nCityId = m_CityCode.GetCurSel();
	OnOK();
}
