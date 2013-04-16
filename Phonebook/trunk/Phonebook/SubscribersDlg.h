#pragma once
#include "Subscribers.h"
#include "SubscribersView.h"
#include "afxwin.h"

// CSubscribersDlg dialog
class CSubscribersDlg : public CDialog
{
	DECLARE_DYNAMIC(CSubscribersDlg)

public:
	CSubscribersDlg(const CSubscribers &oSubscribers, eMenuCmd eCmd, CCities oCity, CCitiesArray *pCitiesArray = 0, CWnd* pParent = NULL);	 
	virtual ~CSubscribersDlg();

	// Dialog Data
	enum { IDD = IDD_SUBSCRIBERS_EDIT };
protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	eMenuCmd m_eMenuCmd;
	CSubscribers m_oSubscribers;
	CCities m_oCity;
	CEdit m_oCode;
	CEdit m_oFirstName;
	CEdit m_oSecondName;
	CEdit m_oThirdName;
	CEdit m_oIDNumber;
	CComboBox m_CityCode;
	CCitiesArray *m_pCitiesArray;
	CEdit m_Address;
public:
	afx_msg void OnBnClickedCityEditUpdate();
	virtual BOOL OnInitDialog();
	CSubscribers GetSubscriberData(){return m_oSubscribers;};
	afx_msg void OnBnClickedOk();
};
