// CitiesView.h : interface of the CCitiesView class
//


#pragma once


class CCitiesView : public CListView
{
protected: // create from serialization only
	CCitiesView();
	DECLARE_DYNCREATE(CCitiesView)

// Attributes
public:
	CCitiesDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CCitiesView();
  void UpdateColumnsContent();
private:
  enum eColPos{eCode = 0, eName, eArea};

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CitiesView.cpp
inline CCitiesDoc* CCitiesView::GetDocument() const
   { return reinterpret_cast<CCitiesDoc*>(m_pDocument); }
#endif

