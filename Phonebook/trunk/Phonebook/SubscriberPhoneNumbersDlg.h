#pragma once
#include "SubscriberPhoneNumbers.h"
#include "SubscriberPhoneNumbersView.h"
#include "afxwin.h"

// CSubscriberPhoneNumbersDlg dialog
class CSubscriberPhoneNumbersDlg : public CDialog
{
  DECLARE_DYNAMIC(CSubscriberPhoneNumbersDlg)

public:
  CSubscriberPhoneNumbersDlg(const CSubscriberPhoneNumbers &oSubscriberPhoneNumbers, eMenuCmd eCmd, CCitiesArray *pCitiesArray = 0, CWnd* pParent = NULL);   // standard constructor
  virtual ~CSubscriberPhoneNumbersDlg();

  // Dialog Data
  enum { IDD = IDD_SUBSCRIBERPHONENUMBERS_EDIT };
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
private:
  eMenuCmd m_eMenuCmd;
  CSubscriberPhoneNumbers m_oSubscriberPhoneNumbers;
  CEdit m_Code;
  CEdit m_FirstName;
  CEdit m_SecondName;
  CEdit m_ThirdName;
  CEdit m_IDNumber;
  CComboBox m_CityCode;
  CCitiesArray *m_pCitiesArray;
  CEdit m_Address;
public:
  afx_msg void OnBnClickedCityEditUpdate();
  virtual BOOL OnInitDialog();
  CSubscriberPhoneNumbers   GetCityData(){return m_oSubscriberPhoneNumbers;};
  afx_msg void OnBnClickedOk();
};
