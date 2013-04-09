#pragma once

#include "CommonDefinitions.h"
#include "Cities.h"
#include "PhoneTypes.h"
#include "SubscriberPhoneNumbers.h"
#include "Subscribers.h"

#define PERSON_TABLE_STRING_MAX_LEN   (64)

struct CPerson
{
	int	m_iId;
	int	m_iSubscriberId;
	int m_iPhoneNumbId;
	
	CPerson(const int iId, const int iSubsrId, const int iPhoneNumbId)
  {
		m_iId = iId;
		m_iSubscriberId = iSubsrId;
		m_iPhoneNumbId = iPhoneNumbId;		
  }
	CPerson & operator=(const CPerson &op)
	{
		m_iId = op.m_iId;
		m_iSubscriberId = op.m_iSubscriberId;
		m_iPhoneNumbId = op.m_iPhoneNumbId;		

		return *this;
	}
};

typedef CRowsPtrArray<CPerson>  CPersonArray;
