#pragma once

#include "CommonDefinitions.h"
#include "Cities.h"
#include "PhoneTypes.h"
#include "SubscriberPhoneNumbers.h"
#include "Subscribers.h"

#define PERSON_TABLE_STRING_MAX_LEN   (64)

struct CPerson
{
	CCities						m_tCity;
	CSubscribers			m_tSubscriber;
  CSubscriberPhoneNumbersArray	m_oPhoneNumbsArr;
	
	CPerson(CCities *ptCity = 0, CSubscribers *ptSubscriber = 0)
  {
    if(ptCity) m_tCity = *ptCity;  
    if(ptSubscriber) m_tSubscriber = *ptSubscriber;  
  }
};

typedef CRowsPtrArray<CPerson>  CPersonArray;
