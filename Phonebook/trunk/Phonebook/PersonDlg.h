#pragma once
#include "afxwin.h"


// CPersonDlg dialog

class CPersonDlg : public CDialog
{
	DECLARE_DYNAMIC(CPersonDlg)

public:
	CPersonDlg(eMenuCmd eCmd, CPerson *poPerson = 0, CCitiesArray *poCitiesArr = 0, CPhoneTypesArray *poPhoneTypesArr = 0, CWnd* pParent = NULL);   // standard constructor
	virtual ~CPersonDlg();

// Dialog Data
	enum { IDD = IDD_PERSON_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	CPerson m_oPerson;
	CCitiesArray *m_poCitiesArr;
	CPhoneTypesArray *m_poPhoneTypesArr;
	eMenuCmd m_eMenuCmd;
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_oSubscrCode;
	CComboBox m_oCities;
	CEdit m_oFirstName;
	CEdit m_SecName;
	CEdit m_oThirdName;
	CEdit m_SubscrId;
	CEdit m_oAddress;
	CEdit m_oPhoneNumber;
	CComboBox m_oPhoneType;
};
