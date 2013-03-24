#pragma once
#include "afxcmn.h"


// CNewDocDlg dialog

class CNewDocDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewDocDlg)

public:
	CNewDocDlg(CPtrList *poTemplateList = 0,CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewDocDlg();

// Dialog Data
	enum { IDD = IDD_NEWDOCDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog();
  void InitItems();
  void InitIcons();

  CPtrList *m_poTemplateList;
  CImageList	m_cImageListNormal, m_cImageListSmall;

	DECLARE_MESSAGE_MAP()
public:
  CListCtrl m_cListCtrl;
};
