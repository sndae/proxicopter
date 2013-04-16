#pragma once
#include "SubscriberPhoneNumbers.h"
#include "SubscriberPhoneNumbersView.h"
#include "afxwin.h"

// CSubscriberPhoneNumbersDlg dialog
class CSubscriberPhoneNumbersDlg : public CDialog
{
	DECLARE_DYNAMIC(CSubscriberPhoneNumbersDlg)

public:
	CSubscriberPhoneNumbersDlg(const CSubscriberPhoneNumbers &oSubscriberPhoneNumbers, eMenuCmd eCmd, CSubscribersArray *poSubscrArray = 0,
								CPhoneTypesArray *poPhoneTypesArray = 0, CWnd* pParent = NULL);	 
	virtual ~CSubscriberPhoneNumbersDlg();

	// Dialog Data
	enum { IDD = IDD_SUBSCRIBERPHONENUMBERS_EDIT };
protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	eMenuCmd m_eMenuCmd;
	CSubscriberPhoneNumbers m_oSubscriberPhoneNumbers;
	CComboBox m_oSubscriberCode;
	CComboBox m_oPhoneTypeCode;
	CEdit  m_PhoneNumber;
	CSubscribersArray *m_poSubscrArray;
	CPhoneTypesArray *m_poPhoneTypesArray;

public:
	afx_msg void OnBnClickedCityEditUpdate();
	virtual BOOL OnInitDialog();
	CSubscriberPhoneNumbers	 GetCityData(){return m_oSubscriberPhoneNumbers;};
	afx_msg void OnBnClickedOk();
};
