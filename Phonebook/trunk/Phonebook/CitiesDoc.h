// CitiesDoc.h : interface of the CCitiesDoc class
//


#pragma once
#include "CitiesTable.h"

class CCitiesDoc : public CDocument
{
protected: // create from serialization only
	CCitiesDoc();
	DECLARE_DYNCREATE(CCitiesDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CCitiesDoc();
  BOOL SelectAll(CCitiesArray &oCitiesArray);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  CCitiesTable m_oCityTable;
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


