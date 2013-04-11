// CitiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "CitiesDlg.h"


// CCitiesDlg dialog

IMPLEMENT_DYNAMIC(CCitiesDlg, CDialog)

CCitiesDlg::CCitiesDlg(const CCities &oCities, eMenuCmd eCmd, CWnd* pParent /*=NULL*/)
	: CDialog(CCitiesDlg::IDD, pParent)
{
  m_oCity = oCities;
  m_eMenuCmd = eCmd;
}

CCitiesDlg::~CCitiesDlg()
{
}

BOOL CCitiesDlg::OnInitDialog()
{
  CDialog::OnInitDialog();

  switch(m_eMenuCmd)
  {
    case eCmdFind:   
      SetWindowText(MENU_CMD_FIND); 
      ZeroMemory(&m_oCity, sizeof(m_oCity)); 
      break;
    case eCmdUpdate: 
      SetWindowText(MENU_CMD_UPDATE); 
      break;
    case eCmdInsert: 
      SetWindowText(MENU_CMD_INSERT); 
      ZeroMemory(&m_oCity, sizeof(m_oCity)); 
      break;
    default: 
      ASSERT(0);
      break;
  }

  m_oName.SetWindowTextW(m_oCity.m_szName);
  m_oArea.SetWindowTextW(m_oCity.m_szArea);
  m_oCode.SetWindowTextW(m_oCity.m_szCode);

  return TRUE;  
}
void CCitiesDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, EDB_CITIES_EDIT_NAME, m_oName);
  DDX_Control(pDX, EDB_CITIES_EDIT_AREA, m_oArea);
  DDX_Control(pDX, EDB_CITIES_EDIT_CODE, m_oCode);
}


BEGIN_MESSAGE_MAP(CCitiesDlg, CDialog)
  ON_BN_CLICKED(IDOK, &CCitiesDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CCitiesDlg message handlers

void CCitiesDlg::OnBnClickedOk()
{
  // TODO: Add your control notification handler code here
  m_oCode.GetWindowTextW(m_oCity.m_szCode, sizeof(m_oCity.m_szCode)/sizeof(m_oCity.m_szCode[0]));
  m_oName.GetWindowTextW(m_oCity.m_szName, sizeof(m_oCity.m_szName)/sizeof(m_oCity.m_szName[0]));
  m_oArea.GetWindowTextW(m_oCity.m_szArea, sizeof(m_oCity.m_szArea)/sizeof(m_oCity.m_szArea[0]));

  OnOK();
}
