#pragma once
#include "afxwin.h"


// CPersonDlg dialog

class CPersonDlg : public CDialog
{
	DECLARE_DYNAMIC(CPersonDlg)

public:
	CPersonDlg(const eMenuCmd eCmd, const CPerson &oPerson , const CSubscriberPhoneNumbers &oPhoneNumb, const CPhoneTypes &oPhoneType, 
						 CCitiesArray &oCitiesArr, CPhoneTypesArray &oPhoneTypesArr, CWnd* pParent = NULL);   // standard constructor
	virtual ~CPersonDlg();

// Dialog Data
	enum { IDD = IDD_PERSON_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	CPerson m_oPerson;
	CCitiesArray			*m_poCitiesArr;
	CPhoneTypesArray	*m_poPhoneTypesArr;
	CSubscriberPhoneNumbers m_oPhoneNumb;
	CPhoneTypes m_oPhoneType;
	eMenuCmd m_eMenuCmd;
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_cSubscrCode;
	CComboBox m_cCities;
	CEdit m_cFirstName;
	CEdit m_cSecName;
	CEdit m_cThirdName;
	CEdit m_cSubscrId;
	CEdit m_cAddress;
	CEdit m_cPhoneNumber;
	CComboBox m_cPhoneType;
};
