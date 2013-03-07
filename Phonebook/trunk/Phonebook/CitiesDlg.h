#pragma once
#include "Cities.h"
#include "afxwin.h"

// CCitiesDlg dialog

class CCitiesDlg : public CDialog
{
	DECLARE_DYNAMIC(CCitiesDlg)

public:
	CCitiesDlg(const CCities &oCities, CWnd* pParent = NULL);   // standard constructor
	virtual ~CCitiesDlg();

// Dialog Data
	enum { IDD = IDD_CITIES_EDIT };
  enum eCityCmd{eCityUpdate = 0, eCityInsert, eCityDelete, eCityFind};
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
  eCityCmd m_eCityCmd;
  CCities m_oCity;
  CEdit m_Name;
  CEdit m_Area;
  CEdit m_Code;
public:
  afx_msg void OnBnClickedCityEditUpdate();
  virtual BOOL OnInitDialog();
  CCities   GetCityData(){return m_oCity;};
  eCityCmd  GetCityCmd(){return m_eCityCmd;};

  afx_msg void OnBnClickedCityEdiInsert();
  afx_msg void OnBnClickedCityEditDelete();
  afx_msg void OnBnClickedCityEditFind();
};
