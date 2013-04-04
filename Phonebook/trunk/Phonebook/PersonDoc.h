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
  enum  eColumn{eColSubscrCode = 0, eColCity, eColFirstName, eColSecondName, eColThirdName, eColIdNumb, eColAddress, eColPhoneNumber, eColPhoneNumberType, eCOL_NUMB};
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
	BOOL SelectAllCities(CCitiesArray &oCitiesArr);
	BOOL SelectAllPhoneTypes(CPhoneTypesArray &oPhoneTypesArr);
	BOOL SelectPhoneTypeWhereId(const int iIdx, CPhoneTypes &oPhoneType);
	BOOL UpdateWhereId(const int iId, const CPerson &oPerson);
	BOOL SelectWhereId(const int iId, CPerson &oPerson);
	BOOL DeleteWhereId(const int iId);
	BOOL DeleteSubscrPhoneNumb(const int iId);
  BOOL Insert(CPerson &oCity);
	BOOL InsertPhoneNumber(CSubscriberPhoneNumbers &oPhoneNumb);
	/*  
  BOOL Insert(const CPerson &oCity);
  
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


