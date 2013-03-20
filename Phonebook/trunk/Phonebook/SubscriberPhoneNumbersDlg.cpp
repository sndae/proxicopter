// SubscriberPhoneNumbersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "SubscriberPhoneNumbersDlg.h"


// CSubscriberPhoneNumbersDlg dialog

IMPLEMENT_DYNAMIC(CSubscriberPhoneNumbersDlg, CDialog)

CSubscriberPhoneNumbersDlg::CSubscriberPhoneNumbersDlg(const CSubscriberPhoneNumbers &oSubscriberPhoneNumbers, eMenuCmd eCmd, CSubscribersArray *poSubscrArray,
                             CPhoneTypesArray *poPhoneTypesArray, CWnd* pParent)
	: CDialog(CSubscriberPhoneNumbersDlg::IDD, pParent)
{
  m_oSubscriberPhoneNumbers = oSubscriberPhoneNumbers;
  m_eMenuCmd = eCmd;
  m_poSubscrArray = poSubscrArray;
  m_poPhoneTypesArray = poPhoneTypesArray;
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
        m_oSubscriberPhoneNumbers.m_iSubscrCode = DNC;
        m_oSubscriberPhoneNumbers.m_iPhoneCode  = DNC;
        break;
      case eCmdUpdate: 
        SetWindowText(MENU_CMD_UPDATE); 
        break;
      case eCmdInsert: 
        SetWindowText(MENU_CMD_INSERT); 
        ZeroMemory(&m_oSubscriberPhoneNumbers, sizeof(m_oSubscriberPhoneNumbers)); 
        m_oSubscriberPhoneNumbers.m_iSubscrCode = DNC;
        m_oSubscriberPhoneNumbers.m_iPhoneCode  = DNC;
        break;
      default: 
        ASSERT(0);
        break;
    }

    CString csTempBuff;
    m_PhoneNumber.SetWindowTextW(m_oSubscriberPhoneNumbers.m_szPhoneNumber);
    if(m_poSubscrArray)
    {
      for(int i = 0; i < m_poSubscrArray->GetSize(); i++)
      {
        csTempBuff.Format(_T("%d"), (m_poSubscrArray->GetAt(i))->m_iCode);
        m_SubscriberCode.InsertString(i, csTempBuff);
      }
      m_SubscriberCode.SetCurSel(m_oSubscriberPhoneNumbers.m_iSubscrCode);
    }

    if(m_poPhoneTypesArray)
    {
      for(int i = 0; i < m_poPhoneTypesArray->GetSize(); i++)
      {
        csTempBuff.Format(_T("%d"), (m_poPhoneTypesArray->GetAt(i))->m_iCode);
        m_PhoneTypeCode.InsertString(i, csTempBuff);
      }
    }
    if(m_oSubscriberPhoneNumbers.m_iPhoneCode != DNC)
    {
      csTempBuff.Format(_T("%d"), m_oSubscriberPhoneNumbers.m_iPhoneCode);
      m_PhoneTypeCode.SetWindowTextW(csTempBuff);
    }

    if(m_oSubscriberPhoneNumbers.m_iSubscrCode != DNC)
    {
      csTempBuff.Format(_T("%d"), m_oSubscriberPhoneNumbers.m_iSubscrCode);
      m_SubscriberCode.SetWindowTextW(csTempBuff);
    }
    return TRUE;
  }
  return FALSE;
}
void CSubscriberPhoneNumbersDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_SUBSCRIBERPHONENUMBERS_EDIT_CODE_SUBSCRIBER, m_SubscriberCode);
  DDX_Control(pDX, IDC_SUBSCRIBERPHONENUMBERS_EDIT_CODE_PHONE,      m_PhoneTypeCode);
  DDX_Control(pDX, IDC_SUBSCRIBERPHONENUMBERS_EDIT_PHONE_NUMBER,    m_PhoneNumber);
}


BEGIN_MESSAGE_MAP(CSubscriberPhoneNumbersDlg, CDialog)
  ON_BN_CLICKED(IDOK, &CSubscriberPhoneNumbersDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSubscriberPhoneNumbersDlg message handlers

void CSubscriberPhoneNumbersDlg::OnBnClickedOk()
{
  // TODO: Add your control notification handler code here
  CString cTempBuff;
  m_SubscriberCode.GetWindowTextW(cTempBuff);
  if(cTempBuff.GetLength())
    m_oSubscriberPhoneNumbers.m_iSubscrCode = _ttoi(cTempBuff);
  else
    m_oSubscriberPhoneNumbers.m_iSubscrCode = DNC;

  m_PhoneTypeCode.GetWindowTextW(cTempBuff);
  if(cTempBuff.GetLength())
    m_oSubscriberPhoneNumbers.m_iPhoneCode = _ttoi(cTempBuff);
  else
    m_oSubscriberPhoneNumbers.m_iPhoneCode = DNC;  

  m_PhoneNumber.GetWindowTextW(m_oSubscriberPhoneNumbers.m_szPhoneNumber, SUBSCRIBERPHONENUMBERS_TABLE_STRING_MAX_LEN);
  
  OnOK();
}
