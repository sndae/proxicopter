// PhoneTypesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "PhoneTypesDlg.h"


// CPhoneTypesDlg dialog

IMPLEMENT_DYNAMIC(CPhoneTypesDlg, CDialog)

CPhoneTypesDlg::CPhoneTypesDlg(const CPhoneTypes &oPhoneTypes, eMenuCmd eCmd, CWnd* pParent /*=NULL*/)
	: CDialog(CPhoneTypesDlg::IDD, pParent)
{
	m_oPhoneTypes = oPhoneTypes;
	m_eMenuCmd = eCmd;
}

CPhoneTypesDlg::~CPhoneTypesDlg()
{
}

BOOL CPhoneTypesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	switch(m_eMenuCmd)
	{
		case eCmdFind:	 
			SetWindowText(MENU_CMD_FIND); 
			ZeroMemory(&m_oPhoneTypes, sizeof(m_oPhoneTypes)); 
			m_oPhoneTypes.m_nCode = DNC;
			break;
		case eCmdUpdate: 
			SetWindowText(MENU_CMD_UPDATE); 
			break;
		case eCmdInsert: 
			SetWindowText(MENU_CMD_INSERT); 
			ZeroMemory(&m_oPhoneTypes, sizeof(m_oPhoneTypes)); 
			break;
		default: 
			ASSERT(0);
			break;
	}

	m_PhoneType.SetWindowTextW(m_oPhoneTypes.m_szType);
	if(m_oPhoneTypes.m_nCode != DNC)
	{
		CString strTempBuff;
		strTempBuff.Format(_T("%d"), m_oPhoneTypes.m_nCode);
		m_oCode.SetWindowText(strTempBuff);
	}

	return TRUE;
}

void CPhoneTypesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, EDB_PHONETYPES_EDIT_TYPES, m_PhoneType);
	DDX_Control(pDX, EDB_PHONETYPES_EDIT_CODE, m_oCode);
}


BEGIN_MESSAGE_MAP(CPhoneTypesDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CPhoneTypesDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPhoneTypesDlg message handlers

void CPhoneTypesDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString cTempBuff;
	m_oCode.GetWindowTextW(cTempBuff);
	if(cTempBuff.GetLength())
		m_oPhoneTypes.m_nCode = _ttoi(cTempBuff);
	else
		m_oPhoneTypes.m_nCode = DNC;

	m_PhoneType.GetWindowTextW(m_oPhoneTypes.m_szType, sizeof(m_oPhoneTypes.m_szType)/sizeof(m_oPhoneTypes.m_szType[0]));

	OnOK();
}
