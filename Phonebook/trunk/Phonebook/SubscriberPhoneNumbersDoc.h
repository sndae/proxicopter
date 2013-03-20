// SubscriberPhoneNumbersDoc.h : interface of the CSubscriberPhoneNumbersDoc class
//


#pragma once
#include "SubscriberPhoneNumbersTable.h"

class CSubscriberPhoneNumbersDoc : public CDocument
{
protected: // create from serialization only
  CSubscriberPhoneNumbersDoc();
  DECLARE_DYNCREATE(CSubscriberPhoneNumbersDoc)

// Attributes
public:
  /* »збро€ване имената на колоните и техните номера */
  enum  eColumn{eColSubscrCode, eColPhoneCode, eColPhoneNumber, eCOL_NUMB};
// Operations
public:

// Overrides
public:
  virtual BOOL OnNewDocument();
  virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CSubscriberPhoneNumbersDoc();
  BOOL SelectAll(CSubscriberPhoneNumbersArray &oSubscriberPhoneNumbersArray);
  BOOL SelectWhereId(const int iId, CSubscriberPhoneNumbers &oSubscriber);
  BOOL UpdateWhereId(const int iId, const CSubscriberPhoneNumbers &oSubscriber);
  BOOL Insert(const CSubscriberPhoneNumbers &oSubscriber);
  BOOL DeleteWhereId(const int iId);
  BOOL SortByColumn(const eColumn eCol, const BOOL bAsc);
  BOOL SelectByContent(const CSubscriberPhoneNumbers &oSubscriber);
  BOOL SelectAllSubscribersCodes(CSubscribersArray &oSubscribersArray);
  BOOL SelectAllPhoneTypesCodes(CPhoneTypesArray &oPhoneTypesArray);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  CSubscriberPhoneNumbersTable m_oSubscriberPhoneNumbersTable;

// Generated message map functions
protected:
  DECLARE_MESSAGE_MAP()
};


