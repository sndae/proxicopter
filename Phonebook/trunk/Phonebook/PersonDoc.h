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
  // »збро€ване имената на колоните и техните номера 
  enum  eColumn{eColSubscrCode = 0, eColCity, eColFirstName, eColSecondName, eColThirdName, eColIdNumb, eColAddress, eColPhoneNumber, eColPhoneNumberType, eCOL_NUMB};
// Operations
public:

// Overrides
public:
  virtual BOOL OnNewDocument();
  virtual void Serialize(CArchive& ar);

// Implementation
public:
	BOOL SelectAll(CPersonArray &oPersonArray, BOOL bApplyFilter = FALSE);
public:
	virtual ~CPersonDoc();
	BOOL SelectAll(CPersonArray &oPersonArray, eColumn eCol, BOOL bAsc = TRUE);
	BOOL SelectByContent(CSubscribers &oUpdSubscriber, CSubscriberPhoneNumbers &oUpdPhoneNumb);
	BOOL UpdateWhereId(const CPerson &oPerson, CSubscribers &oUpdSubscriber, CSubscriberPhoneNumbers &oUpdPhoneNumb);
	BOOL Insert(CSubscribers &oNewSubscriber, CSubscriberPhoneNumbers &oNewPhoneNumb);
	BOOL DeleteWhereId(const int iId);
	BOOL DeleteSubscrPhoneNumb(const int iId);
	BOOL SelectAllCities(CCitiesArray &oCitiesArr)
	{
		m_oCityTable.SelectByContent(CCities()); 
		return m_oCityTable.SelectAll(oCitiesArr);
	};
	BOOL SelectAllPhoneTypes(CPhoneTypesArray &oPhoneTypesArr)
	{
		m_oPhoneTypeTable.SelectByContent(CPhoneTypes());
		return m_oPhoneTypeTable.SelectAll(oPhoneTypesArr);
	};
	BOOL SelectAllSubscriberPhoneNumbers(CSubscriberPhoneNumbersArray &oPhoneNumbersArr)
	{
		m_oSubscrPhoneNumbsTable.SelectByContent(CSubscriberPhoneNumbers());
		return m_oSubscrPhoneNumbsTable.SelectAll(oPhoneNumbersArr);
	};
	BOOL SelectAllSubscribers(CSubscribersArray &oSubscribersArr)
	{
		m_oSubscrTable.SelectByContent(CSubscribers());
		return m_oSubscrTable.SelectAll(oSubscribersArr);
	};
	BOOL SelectCityWhereId(int iId, CCities &oCity){return m_oCityTable.SelectWhereId(iId, oCity);};
	BOOL SelectPhoneNumberWhereId(int iId, CSubscriberPhoneNumbers &oPhoneNumber){return m_oSubscrPhoneNumbsTable.SelectWhereId(iId, oPhoneNumber);};
	BOOL SelectPhoneTypeWhereId(int iId, CPhoneTypes &oPhoneType){return m_oPhoneTypeTable.SelectWhereId(iId, oPhoneType);};
	BOOL SelectSubscriberWhereId(int iId, CSubscribers &oSubscriber){return m_oSubscrTable.SelectWhereId(iId, oSubscriber);};

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


