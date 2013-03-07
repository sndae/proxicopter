// CitiesView.h : interface of the CPhoneTypesView class
//


#pragma once


class CPhoneTypesView : public CListView
{
protected: // create from serialization only
	CPhoneTypesView();
	DECLARE_DYNCREATE(CPhoneTypesView)

// Attributes
public:
	CPhoneTypesDoc* GetDocument() const;
private:
  int   m_iCurrRowSelected;
  BOOL  m_abAscSorting[CPhoneTypesDoc::eCOL_NUMB];
  CPhoneTypesArray m_PhoneTypesArray;
// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CPhoneTypesView();
  void UpdateColumnsContent();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
  virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

public:
  void OnRowDbClicked();
};

#ifndef _DEBUG  // debug version in CitiesView.cpp
inline CPhoneTypesDoc* CPhoneTypesView::GetDocument() const
   { return reinterpret_cast<CPhoneTypesDoc*>(m_pDocument); }
#endif

