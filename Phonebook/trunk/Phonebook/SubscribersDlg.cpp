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
		m_Code.SetWindowTextW(csTembBuff);
	}
	else
		m_Code.SetWindowTextW(_T(""));

	m_FirstName.SetWindowTextW(m_oSubscribers.m_szFirstName);
	m_SecondName.SetWindowTextW(m_oSubscribers.m_szSecondName);
	m_ThirdName.SetWindowTextW(m_oSubscribers.m_szThirdName);
	m_nDNumber.SetWindowTextW(m_oSubscribers.m_szIDNumb);
	if(m_pCitiesArray)
	{
		for(int i = 0; i < m_pCitiesArray->GetSize(); i++)
			m_CityCode.InsertString(i, (m_pCitiesArray->GetAt(i))->m_szCode);
	}
	if(m_oSubscribers.m_nCityId != DNC)
		m_CityCode.SetWindowTextW(m_pCitiesArray->GetAt(m_oSubscribers.m_nCityId)->m_szCode);
	
	m_Address.SetWindowTextW(m_oSubscribers.m_szAddress);

	return TRUE;

}
void CSubscribersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, EDB_SUBSCRIBERS_EDIT_CODE, m_Code);
	DDX_Control(pDX, EDB_SUBSCRIBERS_EDIT_FIRST_NAME, m_FirstName);
	DDX_Control(pDX, EDB_SUBSCRIBERS_EDIT_SECOND_NAME, m_SecondName);
	DDX_Control(pDX, EDB_SUBSCRIBERS_EDIT_THIRD_NAME, m_ThirdName);
	DDX_Control(pDX, EDB_SUBSCRIBERS_EDIT_IDNUMBER, m_nDNumber);
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
	m_Code.GetWindowTextW(cTempBuff);
	if(cTempBuff.GetLength())
		m_oSubscribers.m_nCode = _ttoi(cTempBuff);
	else
		m_oSubscribers.m_nCode = DNC;

	m_FirstName.GetWindowTextW(m_oSubscribers.m_szFirstName, SUBSCRIBERS_TABLE_STRING_MAX_LEN);
	m_SecondName.GetWindowTextW(m_oSubscribers.m_szSecondName, SUBSCRIBERS_TABLE_STRING_MAX_LEN);
	m_ThirdName.GetWindowTextW(m_oSubscribers.m_szThirdName, SUBSCRIBERS_TABLE_STRING_MAX_LEN);
	m_nDNumber.GetWindowTextW(m_oSubscribers.m_szIDNumb, SUBSCRIBERS_ID_NUMB_LEN);
	m_Address.GetWindowTextW(m_oSubscribers.m_szAddress, SUBSCRIBERS_TABLE_STRING_MAX_LEN);
	
	m_oSubscribers.m_nCityId = m_CityCode.GetCurSel();
	OnOK();
}
