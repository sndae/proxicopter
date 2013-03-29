#pragma once
#include "Subscribers.h"
#include "SubscribersView.h"
#include "afxwin.h"

// CSubscribersDlg dialog
class CSubscribersDlg : public CDialog
{
	DECLARE_DYNAMIC(CSubscribersDlg)

public:
	CSubscribersDlg(const CSubscribers &oSubscribers, eMenuCmd eCmd, CCitiesArray *pCitiesArray = 0, CWnd* pParent = NULL);	 // standard constructor
	virtual ~CSubscribersDlg();

	// Dialog Data
	enum { IDD = IDD_SUBSCRIBERS_EDIT };
protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	eMenuCmd m_eMenuCmd;
	CSubscribers m_oSubscribers;
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
	CSubscribers GetCityData(){return m_oSubscribers;};
	afx_msg void OnBnClickedOk();
};
