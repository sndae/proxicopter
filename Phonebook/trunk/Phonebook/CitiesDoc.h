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
  /* »збро€ване имената на колоните и техните номера */
  enum  eColumn{eColCode = 0, eColName, eColArea, eCOL_NUMB};
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
  BOOL SelectWhereId(const int iId, CCities &oCity);
  BOOL UpdateWhereId(const int iId, const CCities &oCity);
  BOOL Insert(const CCities &oCity);
  BOOL DeleteWhereId(const int iId);
  BOOL SortByColumn(const eColumn eCol, const BOOL bAsc);
  BOOL SelectByContent(const CCities &oCity);
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


