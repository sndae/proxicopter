#pragma once
#include "afxwin.h"


// CPersonDlg dialog

class CPersonDlg : public CDialog
{
	DECLARE_DYNAMIC(CPersonDlg)

public:
	CPersonDlg(eMenuCmd eCmd, CCitiesArray &oCitiesArr, CPhoneTypesArray &oPhoneTypesArr, 
						 CSubscribers &oSubscriber, CSubscriberPhoneNumbers &oSubscrPhoneNumb, CWnd* pParent = NULL);   // standard constructor
	virtual ~CPersonDlg();
	CPerson									&GetPerson(){return m_oPerson;};
	CSubscribers						&GetSubscriber(){return m_oSubscriberTab;};
	CSubscriberPhoneNumbers	&GetPhoneNumber(){return m_oPhoneNumberTab;};
	INT_PTR	 DoModal(const CPerson *poPerson);
// Dialog Data
	enum { IDD = IDD_PERSON_EDIT };
private:
	virtual INT_PTR DoModal(){return CDialog::DoModal();};
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	CPerson m_oPerson;
	CSubscribers						m_oSubscriberTab;
	CSubscriberPhoneNumbers m_oPhoneNumberTab;
	CCitiesArray						*m_poCitiesArr;
	CPhoneTypesArray				*m_poPhoneTypesArr;
	int  m_nPhoneNumbIdx;
	int  m_nPhoneTypeIdx;
	eMenuCmd m_eMenuCmd;
	DECLARE_MESSAGE_MAP()

	CEdit m_oSubscrCode;
	CComboBox m_oCities;
	CEdit m_oFirstName;
	CEdit m_oSecName;
	CEdit m_oThirdName;
	CEdit m_oSubscrId;
	CEdit m_oAddress;
	CEdit m_oPhoneNumber;
	CComboBox m_oPhoneType;
	afx_msg void OnBnClickedOk();
};
