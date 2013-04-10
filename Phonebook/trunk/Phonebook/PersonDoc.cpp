// PersonDoc.cpp : implementation of the CPersonDoc class
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "Person.h"
#include "PersonDoc.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPersonDoc

IMPLEMENT_DYNCREATE(CPersonDoc, CDocument)

BEGIN_MESSAGE_MAP(CPersonDoc, CDocument)
END_MESSAGE_MAP()


// CPersonDoc construction/destruction

CPersonDoc::CPersonDoc()
{
  // TODO: add one-time construction code here
	m_bAutoDelete = FALSE;
}

CPersonDoc::~CPersonDoc()
{
}

BOOL CPersonDoc::OnNewDocument()
{
  if (!CDocument::OnNewDocument())
    return FALSE;

  // TODO: add reinitialization code here
  // (SDI documents will reuse this document)

  return TRUE;
}




// CPersonDoc serialization

void CPersonDoc::Serialize(CArchive& ar)
{
  if (ar.IsStoring())
  {
    // TODO: add storing code here
  }
  else
  {
    // TODO: add loading code here
  }
}

BOOL CPersonDoc::SelectAll(CPersonArray &oPersonArray, eColumn eCol, BOOL bAsc)
{
	m_oSubscrTable.SelectByContent(CSubscribers());
	if(eCol == eColPhoneNumberType)
	{
		if(!m_oPhoneTypeTable.SortByColumn(CPhoneTypesTable::eColType, bAsc))
			return FALSE;
		
		CPhoneTypesArray oPhoneTypesArr;
		if(!m_oPhoneTypeTable.SelectAll(oPhoneTypesArr))
			return FALSE;

		for(int i = 0; i < oPhoneTypesArr.GetCount(); i++)
		{
			if(!m_oSubscrPhoneNumbsTable.SelectByContent(CSubscriberPhoneNumbers(DNC, 0, DNC, oPhoneTypesArr[i]->m_iId)))
				continue;

			CSubscriberPhoneNumbersArray oSubscrPhoneNumbs;
			if(!m_oSubscrPhoneNumbsTable.SelectAll(oSubscrPhoneNumbs))
				continue;

			for(int c = 0; c < oSubscrPhoneNumbs.GetCount(); c++)
			{		
				CSubscribers oSubscriber;
				if(!m_oSubscrTable.SelectWhereId(oSubscrPhoneNumbs[c]->m_iSubscrId, oSubscriber))
					continue;

				oPersonArray.Add(new CPerson(i + c, oSubscriber.m_iId, oSubscrPhoneNumbs[c]->m_iId));
			}							
		}
	}
	else if(eCol == eColPhoneNumber)
	{
		if(!m_oSubscrPhoneNumbsTable.SortByColumn(CSubscriberPhoneNumbersTable::eColPhoneNumber, bAsc))
			return FALSE;

		CSubscriberPhoneNumbersArray oPhoneNumbersArr;
		if(!m_oSubscrPhoneNumbsTable.SelectAll(oPhoneNumbersArr))
			return FALSE;

		int iPrevSubscrId = DNC;
		for(int i = 0; i < oPhoneNumbersArr.GetCount(); i++)
		{
			if(iPrevSubscrId != oPhoneNumbersArr[i]->m_iSubscrId)
			{
				CSubscribers oSubscrber;
				if(!m_oSubscrTable.SelectWhereId(oPhoneNumbersArr[i]->m_iSubscrId, oSubscrber))
					continue;
				
				oPersonArray.Add(new CPerson(i, oSubscrber.m_iId, oPhoneNumbersArr[i]->m_iId));
			}
		}
	}
	else if(eCol == eColCity)
	{
		if(!m_oCityTable.SortByColumn(CCitiesTable::eColName, bAsc))
			return FALSE;

		CCitiesArray oCitiesArr;
		if(!m_oCityTable.SelectAll(oCitiesArr))
			return FALSE;

		for(int i = 0; i < oCitiesArr.GetCount(); i++)
		{
			if(!m_oSubscrTable.SelectByContent(CSubscribers(DNC, 0, DNC, oCitiesArr[i]->m_iId)))
				continue;
				
			if(!SelectAll(oPersonArray))
				continue;
		}
	}
	else
	{
		switch(eCol)
		{
			case eColSubscrCode:
				if(m_oSubscrTable.SortByColumn(CSubscribersTable::eColCode, bAsc);
				break;
			case eColFirstName: 
				m_oSubscrTable.SortByColumn(CSubscribersTable::eColFirstName, bAsc);
				break;
			case eColSecondName: 
				m_oSubscrTable.SortByColumn(CSubscribersTable::eColSecondName, bAsc);
				break;
			case eColThirdName: 
				m_oSubscrTable.SortByColumn(CSubscribersTable::eColThirdName, bAsc);
				break;
			case eColIdNumb: 
				m_oSubscrTable.SortByColumn(CSubscribersTable::eColIDNumb, bAsc);
				break;
			case eColAddress:
				m_oSubscrTable.SortByColumn(CSubscribersTable::eColAddress, bAsc);
				break;
			default:
				ASSERT(0);
		}
		if(!SelectAll(oPersonArray))
			return FALSE;
	}

	return TRUE;
}

BOOL CPersonDoc::SelectAll(CPersonArray &oPersonArray, BOOL bApplyFilter)
{
	CSubscribersArray oSubscrArr;
	if(!m_oSubscrTable.SelectAll(oSubscrArr))
		return FALSE;

	for(int i = 0; i < oSubscrArr.GetCount(); i++)
	{
		if(!m_oSubscrPhoneNumbsTable.SelectByContent(CSubscriberPhoneNumbers(DNC, 0,  oSubscrArr[i]->m_iId)))
			continue;

		CSubscriberPhoneNumbersArray oPhoneNumbersArr;
		if(!m_oSubscrPhoneNumbsTable.SelectAll(oPhoneNumbersArr))
			continue;

		for(int c = 0; c < oPhoneNumbersArr.GetCount(); c++)
		{
			CPerson *poPerson = new CPerson(i, oSubscrArr[i]->m_iId, oPhoneNumbersArr[c]->m_iId);
			oPersonArray.Add(poPerson);
		}
	}

	return TRUE;
}

BOOL CPersonDoc::SelectByContent(CSubscribers &oUpdSubscriber, CSubscriberPhoneNumbers &oUpdPhoneNumb)
{
	
	if(!m_oSubscrTable.SelectByContent(oUpdSubscriber))
		return FALSE;
	
	if(!m_oSubscrPhoneNumbsTable.SelectByContent(oUpdPhoneNumb))
		return FALSE;
	
	return TRUE;
}

BOOL CPersonDoc::UpdateWhereId(const CPerson &oPerson, CSubscribers &oUpdSubscriber, CSubscriberPhoneNumbers &oUpdPhoneNumb)
{
	if(!m_oSubscrTable.UpdateWhereId(oUpdSubscriber.m_iId, oUpdSubscriber))
		return FALSE;

	if(!m_oSubscrPhoneNumbsTable.UpdateWhereId(oUpdPhoneNumb.m_iId, oUpdPhoneNumb))
		return FALSE;

  /* индициране за извършени промени по съдържанието на таблицата */
  
  UpdateAllViews(0, (LPARAM)&oPerson);

	return TRUE;
}

BOOL CPersonDoc::DeleteSubscrPhoneNumb(const int iId)
{
	if(!m_oSubscrPhoneNumbsTable.DeleteWhereId(iId))
		return FALSE;
	
	UpdateAllViews(0);

	return TRUE;
}

BOOL CPersonDoc::Insert(CSubscribers &oNewSubscriber, CSubscriberPhoneNumbers &oNewPhoneNumb)
{
	if(oNewSubscriber.m_iId == DNC)
	{
		if(!m_oSubscrTable.Insert(oNewSubscriber))
			return FALSE;
	}

	if(oNewPhoneNumb.m_iId == DNC)
	{
		oNewPhoneNumb.m_iSubscrId = oNewSubscriber.m_iId;
		if(!m_oSubscrPhoneNumbsTable.Insert(oNewPhoneNumb))
			return FALSE;
	}

	UpdateAllViews(0);

	return FALSE;
}

BOOL CPersonDoc::DeleteWhereId(const int iId)
{
	CSubscribers oSubscriber;
	if(!m_oSubscrTable.SelectWhereId(iId, oSubscriber))
		return FALSE;
	
	if(!m_oSubscrPhoneNumbsTable.SelectByContent(CSubscriberPhoneNumbers(DNC, 0, oSubscriber.m_iId)))
		return FALSE;

	CSubscriberPhoneNumbersArray oPhoneNumbArr;
	if(!m_oSubscrPhoneNumbsTable.SelectAll(oPhoneNumbArr))
		return FALSE;

	for(int i = 0; i < oPhoneNumbArr.GetCount(); i++)
	{
		if(!m_oSubscrPhoneNumbsTable.DeleteWhereId(oPhoneNumbArr[i]->m_iId))
			return FALSE;
	}

	if(!m_oSubscrTable.DeleteWhereId(iId))
		return FALSE;

  /* индициране за извършени промени по съдържанието на таблицата */
  
  UpdateAllViews(0);

	return TRUE;
}

// CPersonDoc diagnostics

#ifdef _DEBUG
void CPersonDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void CPersonDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG


// CPersonDoc commands
