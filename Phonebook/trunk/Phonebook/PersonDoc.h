// PersonDoc.h : interface of the CPersonDoc class
//


#pragma once
#include "Person.h"

class CPersonDoc : public CDocument
{
public:
  CPersonDoc();
protected: // create from serialization only
  DECLARE_DYNCREATE(CPersonDoc)

// Attributes
public:
  /* »збро€ване имената на колоните и техните номера */
  enum  eColumn{eColSubscrCode = 0, eColCity, eColFirstName, eColSecondName, eColThirdName, eColPhoneNumber, eColPhoneNumberType, eCOL_NUMB};
// Operations
public:

// Overrides
public:
  virtual BOOL OnNewDocument();
  virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CPersonDoc();
  BOOL SelectAll(CPersonArray &oPersonArray);
  BOOL SortByColumn(const eColumn eCol, const BOOL bAsc);

	/*
  BOOL SelectWhereId(const int iId, CPerson &oCity);
  BOOL UpdateWhereId(const int iId, const CPerson &oCity);
  BOOL Insert(const CPerson &oCity);
  BOOL DeleteWhereId(const int iId);
  BOOL SelectByContent(const CPerson &oCity);
  */
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	CCitiesTable		 m_oCityTable;
	CPhoneTypesTable m_oPhoneTypeTable;
	CSubscribersTable m_oSubscrTable;
	CSubscriberPhoneNumbersTable m_oSubscrPhoneNumbsTable;
	
// Generated message map functions
protected:
  DECLARE_MESSAGE_MAP()
};


