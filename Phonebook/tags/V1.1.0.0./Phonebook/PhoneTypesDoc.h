// PhoneTypesDoc.h : interface of the CPhoneTypesDoc class
//


#pragma once
#include "PhoneTypesTable.h"

class CPhoneTypesDoc : public CDocument
{
public:
	CPhoneTypesDoc();
protected: // create from serialization only
	DECLARE_DYNCREATE(CPhoneTypesDoc)

// Attributes
public:
	/* »збро€ване имената на колоните и техните номера */
	enum	eColumn{eColCode = 0, eColType, eCOL_NUMB};
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CPhoneTypesDoc();
	BOOL SelectAll(CPhoneTypesArray &oPhoneTypesArray);
	BOOL SelectWhereId(const int iId, CPhoneTypes &oPhoneTypes);
	BOOL UpdateWhereId(const int iId, const CPhoneTypes &oPhoneTypes);
	BOOL Insert(const CPhoneTypes &oPhoneTypes);
	BOOL DeleteWhereId(const int iId);
	BOOL SortByColumn(const eColumn eCol, const BOOL bAsc);
	BOOL SelectByContent(const CPhoneTypes &oPhoneTypes);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CPhoneTypesTable m_oPhoneTypesTable;
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


