// SubscribersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "SubscribersDlg.h"


// CSubscribersDlg dialog

IMPLEMENT_DYNAMIC(CSubscribersDlg, CDialog)

CSubscribersDlg::CSubscribersDlg(const CSubscribers &oSubscribers, CSubscribersView::eMenuCmd eCmd, CWnd* pParent /*=NULL*/)
	: CDialog(CSubscribersDlg::IDD, pParent)
{
  m_oSubscribers = oSubscribers;
  m_eMenuCmd = eCmd;
}

CSubscribersDlg::~CSubscribersDlg()
{
}

BOOL CSubscribersDlg::OnInitDialog()
{
  if(CDialog::OnInitDialog())
  {
    switch(m_eMenuCmd)
    {
      case CSubscribersView::eCmdFind:   
        SetWindowText(_T("Търси")); 
        ZeroMemory(&m_oSubscribers, sizeof(m_oSubscribers)); 
        m_oSubscribers.m_iCode = -1;
        break;
      case CSubscribersView::eCmdUpdate: 
        SetWindowText(_T("Редактирай")); 
        break;
      case CSubscribersView::eCmdInsert: 
        SetWindowText(_T("Вмъкни")); 
        ZeroMemory(&m_oSubscribers, sizeof(m_oSubscribers)); 
        break;
      case CSubscribersView::eCmdDelete: 
        SetWindowText(_T("Изтрий")); 
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

    m_FirstName.SetWindowTextW(m_oSubscribers.m_szFirstName);
    m_SecondName.SetWindowTextW(m_oSubscribers.m_szSecondName);
    m_ThirdName.SetWindowTextW(m_oSubscribers.m_szThirdName);
    m_IDNumber.SetWindowTextW(m_oSubscribers.m_szIDNumb);
    m_CityCode.SetWindowTextW(m_oSubscribers.m_szCityCode);
    m_Address.SetWindowTextW(m_oSubscribers.m_szAddress);

    if(m_oSubscribers.m_iCode != -1)
    {
      CString csTempBuff;
      csTempBuff.Format(_T("%d"), m_oSubscribers.m_iCode);
      m_Code.SetWindowTextW(csTempBuff);
    }

    return TRUE;
  }
  return FALSE;
}
void CSubscribersDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_SUBSCRIBERS_EDIT_CODE, m_Code);
  DDX_Control(pDX, IDC_SUBSCRIBERS_EDIT_FIRST_NAME, m_FirstName);
  DDX_Control(pDX, IDC_SUBSCRIBERS_EDIT_SECOND_NAME, m_SecondName);
  DDX_Control(pDX, IDC_SUBSCRIBERS_EDIT_THIRD_NAME, m_ThirdName);
  DDX_Control(pDX, IDC_SUBSCRIBERS_EDIT_IDNUMBER, m_IDNumber);
  DDX_Control(pDX, IDC_SUBSCRIBERS_EDIT_CITY_CODE, m_CityCode);
  DDX_Control(pDX, IDC_SUBSCRIBERS_EDIT_ADDRESS, m_Address);
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
    m_oSubscribers.m_iCode = _ttoi(cTempBuff);
  else
    m_oSubscribers.m_iCode = -1;

  m_FirstName.GetWindowTextW(m_oSubscribers.m_szFirstName, SUBSCRIBERS_TABLE_STRING_MAX_LEN);
  m_SecondName.GetWindowTextW(m_oSubscribers.m_szSecondName, SUBSCRIBERS_TABLE_STRING_MAX_LEN);
  m_ThirdName.GetWindowTextW(m_oSubscribers.m_szThirdName, SUBSCRIBERS_TABLE_STRING_MAX_LEN);
  m_IDNumber.GetWindowTextW(m_oSubscribers.m_szIDNumb, SUBSCRIBERS_ID_NUMB_LEN);
  m_Address.GetWindowTextW(m_oSubscribers.m_szAddress, SUBSCRIBERS_TABLE_STRING_MAX_LEN);
  
  OnOK();
}
