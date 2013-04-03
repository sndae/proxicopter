#pragma once

#include "CommonDefinitions.h"
#include "Cities.h"
#include "PhoneTypes.h"
#include "SubscriberPhoneNumbers.h"
#include "Subscribers.h"

#define PERSON_TABLE_STRING_MAX_LEN   (64)

struct CPerson
{
	int								m_iId;
	CCities						m_tCity;
	CSubscribers			m_tSubscriber;
  CSubscriberPhoneNumbersArray	m_oPhoneNumbsArr;
	
	CPerson(CCities *ptCity = 0, CSubscribers *ptSubscriber = 0)
  {
    if(ptCity) m_tCity = *ptCity;  
    if(ptSubscriber) m_tSubscriber = *ptSubscriber;  
  }
	CPerson & operator=(const CPerson &op)
	{
		for(int i = 0; i < op.m_oPhoneNumbsArr.GetCount(); i++)
		{
			CSubscriberPhoneNumbers *poPhoneNume = new CSubscriberPhoneNumbers;
			*poPhoneNume = *op.m_oPhoneNumbsArr[i];
			m_oPhoneNumbsArr.InsertAt(i, poPhoneNume);
		}
		
		m_iId = op.m_tSubscriber.m_iId;
		m_tCity = op.m_tCity;
		m_tSubscriber = op.m_tSubscriber;

		return *this;
	}
};

typedef CRowsPtrArray<CPerson>  CPersonArray;
