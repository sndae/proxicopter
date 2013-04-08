#pragma once
#include "afxwin.h"


// CPersonDlg dialog

class CPersonDlg : public CDialog
{
	DECLARE_DYNAMIC(CPersonDlg)

public:
	CPersonDlg(const eMenuCmd eCmd, CCitiesArray &oCitiesArr, CPhoneTypesArray &oPhoneTypesArr, CWnd* pParent = NULL);   // standard constructor
	virtual ~CPersonDlg();
	CPerson	*GetPerson(){return &m_oPerson;};
	int      GetPhoneTypeIdx(){return m_iPhoneTypeIdx;};
	int			 GetPhoneNumbIdx(){return m_iPhoneNumbIdx;};
	INT_PTR	 DoModal(const CPerson *poPerson = 0, const int iPersonId = DNC, const int iPhoneNumbId = DNC);
// Dialog Data
	enum { IDD = IDD_PERSON_EDIT };
private:
	virtual INT_PTR DoModal(){return CDialog::DoModal();};
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	CPerson m_oPerson;
	CCitiesArray			*m_poCitiesArr;
	CPhoneTypesArray	*m_poPhoneTypesArr;
	int  m_iPhoneNumbIdx;
	int  m_iPhoneTypeIdx;
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
	afx_msg void OnBnClickedOk();
};
