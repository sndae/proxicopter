#pragma once
#include "afxcmn.h"


// CNewDocDlg dialog

class CNewDocDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewDocDlg)

public:
	CNewDocDlg(CPtrList *poTemplateList = 0,CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewDocDlg();
  CDocTemplate *GetSelectedDoc();

// Dialog Data
	enum { IDD = IDD_NEWDOCDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  void InitItems();
  void InitIcons();

	DECLARE_MESSAGE_MAP()
private:
  CPtrList      *m_poTemplateList;
  CImageList	  m_cImageListNormal;
  CListCtrl     m_cListCtrl;
  CDocTemplate *m_poSelectedTempl;
public:
  afx_msg void OnNMClickNewdoclistCtrl(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnNMDblclkListCtrl(NMHDR *pNMHDR, LRESULT *pResult);
};
