#pragma once
#include "PhoneTypes.h"
#include "PhoneTypesView.h"
#include "afxwin.h"

// CPhoneTypesDlg dialog
class CPhoneTypesDlg : public CDialog
{
  DECLARE_DYNAMIC(CPhoneTypesDlg)

public:
  CPhoneTypesDlg(const CPhoneTypes &oPhoneTypes, eMenuCmd eCmd, CWnd* pParent = NULL);   // standard constructor
  virtual ~CPhoneTypesDlg();

  // Dialog Data
  enum { IDD = IDD_PHONETYPES_EDIT };
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
private:
  eMenuCmd m_eMenuCmd;
  CPhoneTypes m_oPhoneTypes;
  CEdit m_Code;
  CEdit m_PhoneType;
public:
  afx_msg void OnBnClickedCityEditUpdate();
  virtual BOOL OnInitDialog();
  CPhoneTypes   GetCityData(){return m_oPhoneTypes;};
  afx_msg void OnBnClickedOk();
};
