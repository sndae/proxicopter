#pragma once

#include "CommonDefinitions.h"
#include "Cities.h"
#include "PhoneTypes.h"
#include "SubscriberPhoneNumbers.h"
#include "Subscribers.h"

#define PERSON_TABLE_STRING_MAX_LEN   (64)

struct CPerson
{
	int	m_nId;
	int	m_nSubscriberId;
	int m_nPhoneNumbId;
	
	CPerson(const int iId = DNC, const int iSubsrId = DNC, const int iPhoneNumbId = DNC)
  {
		m_nId = iId;
		m_nSubscriberId = iSubsrId;
		m_nPhoneNumbId = iPhoneNumbId;		
  }
	CPerson & operator=(const CPerson &op)
	{
		m_nId = op.m_nId;
		m_nSubscriberId = op.m_nSubscriberId;
		m_nPhoneNumbId = op.m_nPhoneNumbId;		

		return *this;
	}
};

typedef CRowsPtrArray<CPerson>  CPersonArray;
