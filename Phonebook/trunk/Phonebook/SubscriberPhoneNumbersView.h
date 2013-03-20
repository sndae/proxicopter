// SubscriberPhoneNumbersViewView.h : interface of the CSubscriberPhoneNumbersView class
//


#pragma once
#include "SubscriberPhoneNumbersDoc.h"

class CSubscriberPhoneNumbersView : public CListView
{
protected: // create from serialization only
	CSubscriberPhoneNumbersView();
	DECLARE_DYNCREATE(CSubscriberPhoneNumbersView)

// Attributes
public:
	CSubscriberPhoneNumbersDoc* GetDocument() const;

private:
  /* Текущият избран ред от списъка */
  int   m_iCurrRowSelected;
 /* Масив указващ начина на сортиране на всяка една от колоните */
  BOOL  m_abAscSorting[CSubscriberPhoneNumbersDoc::eCOL_NUMB];
  /* Масив от указатели към данни за всеки ред от листът. Необходим е, тъй като ID и rev_numb на всеки 
     ред, не се визуализират. Т.е. те трябва да се съхваняват, с цел използване в случай на редакция */
  CSubscriberPhoneNumbersArray m_SubscriberPhoneNumbersArray;
// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
  virtual void OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint);
// Implementation
public:
	virtual ~CSubscriberPhoneNumbersView();
  void UpdateColumnsContent();
  void UpdateSingleRow(int iRecId);
  void SetRowData(int iRowIdx, CSubscriberPhoneNumbers &oSubscriber);
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
  void ExecuteCntxMenuCmd(eMenuCmd eCmd);
};

#ifndef _DEBUG  // debug version in SubscriberPhoneNumbersViewView.cpp
inline CSubscriberPhoneNumbersViewDoc* CSubscriberPhoneNumbersView::GetDocument() const
   { return reinterpret_cast<CSubscriberPhoneNumbersDoc*>(m_pDocument); }
#endif

