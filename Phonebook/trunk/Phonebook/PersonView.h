// PersonView.h : interface of the CPersonView class
//


#pragma once
#include "PersonDoc.h"

class CPersonView : public CListView
{
protected: // create from serialization only
	CPersonView();
	DECLARE_DYNCREATE(CPersonView)

// Attributes
public:

private:

// Operations
public:

// Overrides
public:

protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint);
// Implementation
public:
	virtual ~CPersonView();
  virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	void UpdateColumnsContent();
	void UpdateColumnsContent(CPersonArray &oPersonsArr);
	void UpdateSingleRow(CPerson &oUpdPerson);
	void InsertNewRow(CPerson &oPerson);
  void ExecuteCntxMenuCmd(eMenuCmd eCmd);
	CPersonDoc* GetDocument() const;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

  // Текущият избран ред от списъка 
  int   m_nCurrRowSelected;
 // Масив указващ начина на сортиране на всяка една от колоните 
  BOOL  m_abAscSorting[CPersonDoc::eCOL_NUMB];
  // Масив от указатели към данни за всеки ред от листът. Необходим е, тъй като ID и rev_numb на всеки 
  // ред, не се визуализират. Т.е. те трябва да се съхваняват, с цел използване в случай на редакция 
  CPersonArray m_PersonsArray;
};

#ifndef _DEBUG  // debug version in PersonView.cpp

#endif

#pragma once
