// SubscribersDoc.h : interface of the CSubscribersDoc class
//


#pragma once
#include "SubscribersTable.h"

class CSubscribersDoc : public CDocument
{
protected: // create from serialization only
  CSubscribersDoc();
  DECLARE_DYNCREATE(CSubscribersDoc)

// Attributes
public:
  /* »збро€ване имената на колоните и техните номера */
  enum  eColumn{eColCode = 0, eColFirstName, eColSecondName, eColThirdName, eColIDNumb, eColCityCode, eColAddress, eCOL_NUMB};
// Operations
public:

// Overrides
public:
  virtual BOOL OnNewDocument();
  virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CSubscribersDoc();
  BOOL SelectAll(CSubscribersArray &oSubscribersArray);
  BOOL SelectWhereId(const int iId, CSubscribers &oSubscriber);
  BOOL UpdateWhereId(const int iId, const CSubscribers &oSubscriber);
  BOOL Insert(const CSubscribers &oSubscriber);
  BOOL DeleteWhereId(const int iId);
  BOOL SortByColumn(const eColumn eCol, const BOOL bAsc);
  BOOL SelectByContent(const CSubscribers &oSubscriber);
  BOOL SelectAllCityCodes(CCitiesArray &oCitiesArray);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  CSubscribersTable m_oSubscribersTable;

// Generated message map functions
protected:
  DECLARE_MESSAGE_MAP()
};


