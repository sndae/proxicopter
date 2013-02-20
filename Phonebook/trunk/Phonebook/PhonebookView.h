// PhonebookView.h : interface of the CPhonebookView class
//

#pragma once
#include "afxwin.h"

class CPhonebookView : public CFormView
{
protected: // create from serialization only
	CPhonebookView();
	DECLARE_DYNCREATE(CPhonebookView)
public:
	enum{ IDD = IDD_PHONEBOOK_FORM };

// Attributes
public:
	CPhonebookDoc* GetDocument() const;
// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CPhonebookView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedLoaddb();
  CComboBox m_RegSelector;
  CListBox  m_RegContentList;
  CDatabase m_Database;

  afx_msg void OnCbnSelchangeRegisterSelector();
};

#ifndef _DEBUG  // debug version in PhonebookView.cpp
inline CPhonebookDoc* CPhonebookView::GetDocument() const
   { return reinterpret_cast<CPhonebookDoc*>(m_pDocument); }
#endif

