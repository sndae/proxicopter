// CitiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "CitiesDlg.h"


// CCitiesDlg dialog

IMPLEMENT_DYNAMIC(CCitiesDlg, CDialog)

CCitiesDlg::CCitiesDlg(const CCities &oCities, CCitiesView::eMenuCmd eCmd, CWnd* pParent /*=NULL*/)
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
  if(CDialog::OnInitDialog())
  {
    switch(m_eMenuCmd)
    {
      case CCitiesView::eCmdFind:   
        SetWindowText(_T("�����")); 
        ZeroMemory(&m_oCity, sizeof(m_oCity)); 
        break;
      case CCitiesView::eCmdUpdate: 
        SetWindowText(_T("����������")); 
        break;
      case CCitiesView::eCmdInsert: 
        SetWindowText(_T("������")); 
        ZeroMemory(&m_oCity, sizeof(m_oCity)); 
        break;
      case CCitiesView::eCmdDelete: 
        SetWindowText(_T("������")); 
        m_Name.EnableWindow(FALSE); 
        m_Area.EnableWindow(FALSE);
        m_Code.EnableWindow(FALSE);
        break;
      default: 
        ASSERT(0);
        break;
    }

    m_Name.SetWindowTextW(m_oCity.m_szName);
    m_Area.SetWindowTextW(m_oCity.m_szArea);
    m_Code.SetWindowTextW(m_oCity.m_szCode);

    return TRUE;
  }
  return FALSE;
}
void CCitiesDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_CITIES_EDIT_NAME, m_Name);
  DDX_Control(pDX, IDC_CITIES_EDIT_AREA, m_Area);
  DDX_Control(pDX, IDC_CITIES_EDIT_CODE, m_Code);
}


BEGIN_MESSAGE_MAP(CCitiesDlg, CDialog)
  ON_BN_CLICKED(IDOK, &CCitiesDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CCitiesDlg message handlers

void CCitiesDlg::OnBnClickedOk()
{
  // TODO: Add your control notification handler code here
  m_Code.GetWindowTextW(m_oCity.m_szCode, sizeof(m_oCity.m_szCode)/sizeof(m_oCity.m_szCode[0]));
  m_Name.GetWindowTextW(m_oCity.m_szName, sizeof(m_oCity.m_szName)/sizeof(m_oCity.m_szName[0]));
  m_Area.GetWindowTextW(m_oCity.m_szArea, sizeof(m_oCity.m_szArea)/sizeof(m_oCity.m_szArea[0]));

  OnOK();
}