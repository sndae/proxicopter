#pragma once

// CPhoneTypesDoc document
#include "PhoneTypesTable.h"

class CPhoneTypesDoc : public CDocument
{
protected: // create from serialization only
	CPhoneTypesDoc();
	DECLARE_DYNCREATE(CPhoneTypesDoc)

// Attributes
public:
  enum  eColumn{eColCode, eColType, eCOL_NUMB};
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CPhoneTypesDoc();
  BOOL SelectAll(CPhoneTypesArray &oCitiesArray);
  BOOL SelectWhereId(const int iId, CPhoneTypes &oCity);
  BOOL UpdateWhereId(const int iId, const CPhoneTypes &oCity);
  BOOL Insert(const CPhoneTypes &oCity);
  BOOL DeleteWhereId(const int iId);
  BOOL SortByColumn(const eColumn eCol, const BOOL bAsc);
  BOOL SelectByContent(const CPhoneTypes &oCity);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  CPhoneTypesTable m_oCityTable;
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

