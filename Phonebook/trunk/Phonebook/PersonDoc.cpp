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
	if(eCol == eColCity)
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
				
			SelectAll(oPersonArray);			
		}
	}
	else if(eCol == eColPhoneNumberType)
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
				if(!m_oSubscrTable.SelectWhereId(oSubscrPhoneNumbs[c]->m_iSubscrId, CSubscribers()))
					continue;
				
				SelectAll(oPersonArray, TRUE);
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

			SelectAll(oPersonArray);	
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
				if(!m_oSubscrTable.SelectWhereId(oPhoneNumbersArr[i]->m_iSubscrId, CSubscribers()))
					continue;

				SelectAll(oPersonArray);
				iPrevSubscrId = oPhoneNumbersArr[i]->m_iSubscrId;
			}
		}
	}
	else
	{
		switch(eCol)
		{
			case eColSubscrCode:
				m_oSubscrTable.SortByColumn(CSubscribersTable::eColCode, bAsc);
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
		SelectAll(oPersonArray);
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
		CPerson *poPerson = new CPerson;
		poPerson->m_tSubscriber = *oSubscrArr[i];
		poPerson->m_iId = poPerson->m_tSubscriber.m_iId;

		m_oCityTable.SelectWhereId(oSubscrArr[i]->m_iCityId, poPerson->m_tCity);

		if(m_oSubscrPhoneNumbsTable.SelectByContent(CSubscriberPhoneNumbers(DNC, 0,  oSubscrArr[i]->m_iId), !bApplyFilter))
		{
			if(m_oSubscrPhoneNumbsTable.SelectAll(poPerson->m_oPhoneNumbsArr))
				oPersonArray.Add(poPerson);
		}
	}

	return TRUE;
}

BOOL CPersonDoc::SelectByContent(const CPerson &oPerson)
{
	if(!m_oSubscrTable.SelectByContent(oPerson.m_tSubscriber))
		return FALSE;
	
	if(!m_oSubscrPhoneNumbsTable.SelectByContent(*oPerson.m_oPhoneNumbsArr[0]))
		return FALSE;

	return TRUE;
}

BOOL CPersonDoc::SelectAllCities(CCitiesArray &oCitiesArr)
{
	m_oCityTable.SelectByContent(CCities());
	return m_oCityTable.SelectAll(oCitiesArr);
}

BOOL CPersonDoc::SelectAllPhoneTypes(CPhoneTypesArray &oPhoneTypesArr)
{
	m_oPhoneTypeTable.SelectByContent(CPhoneTypes());
	return m_oPhoneTypeTable.SelectAll(oPhoneTypesArr);
}

BOOL CPersonDoc::SelectPhoneTypeWhereId(const int iIdx, CPhoneTypes &oPhoneType)
{
	return m_oPhoneTypeTable.SelectWhereId(iIdx, oPhoneType);
}

BOOL CPersonDoc::UpdateWhereId(const int iId, const CPerson &oPerson)
{
	CSubscribers oSubscr;
	if(!m_oSubscrTable.SelectWhereId(oPerson.m_tSubscriber.m_iId, oSubscr))
		return FALSE;

	if(oSubscr != oPerson.m_tSubscriber)
	{
		if(oSubscr.m_iRevNumb != oPerson.m_tSubscriber.m_iRevNumb)
			return FALSE;

		if(!m_oSubscrTable.UpdateWhereId(oSubscr.m_iId, oPerson.m_tSubscriber))
			return FALSE;
	}
	
	CSubscriberPhoneNumbersArray oSubscrPhoneNumbs;
	m_oSubscrPhoneNumbsTable.SelectByContent(CSubscriberPhoneNumbers(DNC, 0, oPerson.m_tSubscriber.m_iCode));
	if(!m_oSubscrPhoneNumbsTable.SelectAll(oSubscrPhoneNumbs))
		return FALSE;

	for(int i = 0; i < min(oSubscrPhoneNumbs.GetCount(), oPerson.m_oPhoneNumbsArr.GetCount()); i++)
	{
		if(*oSubscrPhoneNumbs[i] != *oPerson.m_oPhoneNumbsArr[i])
		{
			if(!m_oSubscrPhoneNumbsTable.UpdateWhereId(oPerson.m_oPhoneNumbsArr[i]->m_iId, *oPerson.m_oPhoneNumbsArr[i]))
				return FALSE;
		}
	}

  /* индициране за извършени промени по съдържанието на таблицата */
  
  UpdateAllViews(0, (LPARAM)&oPerson);

	return TRUE;
}

BOOL CPersonDoc::DeleteSubscrPhoneNumb(const int iId)
{
	if(!m_oSubscrPhoneNumbsTable.DeleteWhereId(iId))
		return FALSE;

	CPerson oPerson;
	if(!SelectWhereId(iId, oPerson))
		return FALSE;
	
	UpdateAllViews(0);

	return TRUE;
}

BOOL CPersonDoc::Insert(CPerson &oPerson)
{
	if(oPerson.m_tSubscriber.m_iId == DNC)
	{
		if(m_oSubscrTable.Insert(oPerson.m_tSubscriber))
		{	
			CSubscriberPhoneNumbers *poNewPhoneNumb = oPerson.m_oPhoneNumbsArr[oPerson.m_oPhoneNumbsArr.GetCount() - 1];
			poNewPhoneNumb->m_iSubscrId = oPerson.m_tSubscriber.m_iId;
			return InsertPhoneNumber(*poNewPhoneNumb);
		}
	}
	
	UpdateAllViews(0);

	return FALSE;
}

BOOL CPersonDoc::InsertPhoneNumber(CSubscriberPhoneNumbers &oPhoneNumb)
{
	if(!m_oSubscrPhoneNumbsTable.Insert(oPhoneNumb))
		return FALSE;

	CPerson oPerson;
	if(!SelectWhereId(oPhoneNumb.m_iSubscrId, oPerson))
		return FALSE;
	
	UpdateAllViews(0);

	return TRUE;
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
BOOL CPersonDoc::SelectWhereId(const int iId, CPerson &oPerson)
{
	if(!m_oSubscrTable.SelectWhereId(iId, oPerson.m_tSubscriber))
		return FALSE;

	oPerson.m_iId = oPerson.m_tSubscriber.m_iId;

	if(!m_oCityTable.SelectByContent(CCities(oPerson.m_tSubscriber.m_iId)))
		return FALSE;

	if(!m_oSubscrPhoneNumbsTable.SelectByContent(CSubscriberPhoneNumbers(DNC, 0,  oPerson.m_tSubscriber.m_iCode)))
		return FALSE;

	if(!m_oSubscrPhoneNumbsTable.SelectAll(oPerson.m_oPhoneNumbsArr))
		return FALSE;

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
