// CitiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "CitiesDlg.h"


// CCitiesDlg dialog

IMPLEMENT_DYNAMIC(CCitiesDlg, CDialog)

CCitiesDlg::CCitiesDlg(const CCities &oCities, CWnd* pParent /*=NULL*/)
	: CDialog(CCitiesDlg::IDD, pParent)
{
  m_oCity = oCities;
}

CCitiesDlg::~CCitiesDlg()
{
}

BOOL CCitiesDlg::OnInitDialog()
{
  if(CDialog::OnInitDialog())
  {
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
  ON_BN_CLICKED(IDC_CITY_EDIT_UPDATE, &CCitiesDlg::OnBnClickedCityEditUpdate)
  ON_BN_CLICKED(IDC_CITY_EDIT_INSERT, &CCitiesDlg::OnBnClickedCityEdiInsert)
  ON_BN_CLICKED(IDC_CITY_EDIT_DELETE, &CCitiesDlg::OnBnClickedCityEditDelete)
  ON_BN_CLICKED(IDC_CITY_EDIT_FIND, &CCitiesDlg::OnBnClickedCityEditFind)
END_MESSAGE_MAP()


// CCitiesDlg message handlers

void CCitiesDlg::OnBnClickedCityEditUpdate()
{
  // TODO: Add your control notification handler code here
  m_eCityCmd = eCityUpdate;

  m_Code.GetWindowTextW(m_oCity.m_szCode, sizeof(m_oCity.m_szCode)/sizeof(m_oCity.m_szCode[0]));
  m_Name.GetWindowTextW(m_oCity.m_szName, sizeof(m_oCity.m_szName)/sizeof(m_oCity.m_szName[0]));
  m_Area.GetWindowTextW(m_oCity.m_szArea, sizeof(m_oCity.m_szArea)/sizeof(m_oCity.m_szArea[0]));

  CDialog::OnOK();
}

void CCitiesDlg::OnBnClickedCityEdiInsert()
{
  // TODO: Add your control notification handler code here
  m_eCityCmd = eCityInsert;

  m_Code.GetWindowTextW(m_oCity.m_szCode, sizeof(m_oCity.m_szCode)/sizeof(m_oCity.m_szCode[0]));
  m_Name.GetWindowTextW(m_oCity.m_szName, sizeof(m_oCity.m_szName)/sizeof(m_oCity.m_szName[0]));
  m_Area.GetWindowTextW(m_oCity.m_szArea, sizeof(m_oCity.m_szArea)/sizeof(m_oCity.m_szArea[0]));

  CDialog::OnOK();
}

void CCitiesDlg::OnBnClickedCityEditDelete()
{
  // TODO: Add your control notification handler code here
  m_eCityCmd = eCityDelete;

  m_Code.GetWindowTextW(m_oCity.m_szCode, sizeof(m_oCity.m_szCode)/sizeof(m_oCity.m_szCode[0]));
  m_Name.GetWindowTextW(m_oCity.m_szName, sizeof(m_oCity.m_szName)/sizeof(m_oCity.m_szName[0]));
  m_Area.GetWindowTextW(m_oCity.m_szArea, sizeof(m_oCity.m_szArea)/sizeof(m_oCity.m_szArea[0]));

  CDialog::OnOK();
}

void CCitiesDlg::OnBnClickedCityEditFind()
{
  // TODO: Add your control notification handler code here
  // TODO: Add your control notification handler code here
  m_eCityCmd = eCityFind;

  m_Code.GetWindowTextW(m_oCity.m_szCode, sizeof(m_oCity.m_szCode)/sizeof(m_oCity.m_szCode[0]));
  m_Name.GetWindowTextW(m_oCity.m_szName, sizeof(m_oCity.m_szName)/sizeof(m_oCity.m_szName[0]));
  m_Area.GetWindowTextW(m_oCity.m_szArea, sizeof(m_oCity.m_szArea)/sizeof(m_oCity.m_szArea[0]));

  CDialog::OnOK();
}
