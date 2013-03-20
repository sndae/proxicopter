// SubscriberPhoneNumbersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "SubscriberPhoneNumbersDlg.h"


// CSubscriberPhoneNumbersDlg dialog

IMPLEMENT_DYNAMIC(CSubscriberPhoneNumbersDlg, CDialog)

CSubscriberPhoneNumbersDlg::CSubscriberPhoneNumbersDlg(const CSubscriberPhoneNumbers &oSubscriberPhoneNumbers, eMenuCmd eCmd, CCitiesArray *pCitiesArray, CWnd* pParent /*=NULL*/)
	: CDialog(CSubscriberPhoneNumbersDlg::IDD, pParent)
{
  m_oSubscriberPhoneNumbers = oSubscriberPhoneNumbers;
  m_eMenuCmd = eCmd;
  m_pCitiesArray = pCitiesArray;
}

CSubscriberPhoneNumbersDlg::~CSubscriberPhoneNumbersDlg()
{
}

BOOL CSubscriberPhoneNumbersDlg::OnInitDialog()
{
  if(CDialog::OnInitDialog())
  {
    switch(m_eMenuCmd)
    {
      case eCmdFind:   
        SetWindowText(MENU_CMD_FIND); 
        ZeroMemory(&m_oSubscriberPhoneNumbers, sizeof(m_oSubscriberPhoneNumbers)); 
        m_oSubscriberPhoneNumbers.m_iCode = DNC;
        break;
      case eCmdUpdate: 
        SetWindowText(MENU_CMD_UPDATE); 
        break;
      case eCmdInsert: 
        SetWindowText(MENU_CMD_INSERT); 
        ZeroMemory(&m_oSubscriberPhoneNumbers, sizeof(m_oSubscriberPhoneNumbers)); 
        break;
      case eCmdDelete: 
        SetWindowText(MENU_CMD_DELETE); 
        m_Code.EnableWindow(FALSE); 
        m_FirstName.EnableWindow(FALSE);
        m_SecondName.EnableWindow(FALSE);
        m_ThirdName.EnableWindow(FALSE);
        m_IDNumber.EnableWindow(FALSE);
        m_CityCode.EnableWindow(FALSE);
        m_Address.EnableWindow(FALSE);
        break;
      default: 
        ASSERT(0);
        break;
    }

    m_FirstName.SetWindowTextW(m_oSubscriberPhoneNumbers.m_szFirstName);
    m_SecondName.SetWindowTextW(m_oSubscriberPhoneNumbers.m_szSecondName);
    m_ThirdName.SetWindowTextW(m_oSubscriberPhoneNumbers.m_szThirdName);
    m_IDNumber.SetWindowTextW(m_oSubscriberPhoneNumbers.m_szIDNumb);
    if(m_pCitiesArray)
    {
      for(int i = 0; i < m_pCitiesArray->GetSize(); i++)
        m_CityCode.InsertString(i, (m_pCitiesArray->GetAt(i))->m_szCode);
    }
    m_CityCode.SetWindowTextW(m_oSubscriberPhoneNumbers.m_szCityCode);
    m_Address.SetWindowTextW(m_oSubscriberPhoneNumbers.m_szAddress);

    if(m_oSubscriberPhoneNumbers.m_iCode != DNC)
    {
      CString csTempBuff;
      csTempBuff.Format(_T("%d"), m_oSubscriberPhoneNumbers.m_iCode);
      m_Code.SetWindowTextW(csTempBuff);
    }

    return TRUE;
  }
  return FALSE;
}
void CSubscriberPhoneNumbersDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_SUBSCRIBERPHONENUMBERS_EDIT_CODE_SUBSCRIBER, m_Code);
  DDX_Control(pDX, IDC_SUBSCRIBERPHONENUMBERS_EDIT_CODE_PHONE, m_FirstName);
  DDX_Control(pDX, IDC_SUBSCRIBERPHONENUMBERS_EDIT_PHONE_NUMBER, m_SecondName);
}


BEGIN_MESSAGE_MAP(CSubscriberPhoneNumbersDlg, CDialog)
  ON_BN_CLICKED(IDOK, &CSubscriberPhoneNumbersDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSubscriberPhoneNumbersDlg message handlers

void CSubscriberPhoneNumbersDlg::OnBnClickedOk()
{
  // TODO: Add your control notification handler code here
  CString cTempBuff;
  m_Code.GetWindowTextW(cTempBuff);
  if(cTempBuff.GetLength())
    m_oSubscriberPhoneNumbers.m_iCode = _ttoi(cTempBuff);
  else
    m_oSubscriberPhoneNumbers.m_iCode = DNC;

  m_FirstName.GetWindowTextW(m_oSubscriberPhoneNumbers.m_szFirstName, SubscriberPhoneNumbers_TABLE_STRING_MAX_LEN);
  m_SecondName.GetWindowTextW(m_oSubscriberPhoneNumbers.m_szSecondName, SubscriberPhoneNumbers_TABLE_STRING_MAX_LEN);
  m_ThirdName.GetWindowTextW(m_oSubscriberPhoneNumbers.m_szThirdName, SubscriberPhoneNumbers_TABLE_STRING_MAX_LEN);
  m_IDNumber.GetWindowTextW(m_oSubscriberPhoneNumbers.m_szIDNumb, SubscriberPhoneNumbers_ID_NUMB_LEN);
  m_Address.GetWindowTextW(m_oSubscriberPhoneNumbers.m_szAddress, SubscriberPhoneNumbers_TABLE_STRING_MAX_LEN);
  m_CityCode.GetWindowText(m_oSubscriberPhoneNumbers.m_szCityCode, SubscriberPhoneNumbers_TABLE_STRING_MAX_LEN);
  OnOK();
}
