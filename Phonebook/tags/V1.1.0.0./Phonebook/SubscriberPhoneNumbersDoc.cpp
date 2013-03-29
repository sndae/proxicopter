// SubscriberPhoneNumbersDoc.cpp : implementation of the CSubscriberPhoneNumbersDoc class
//

#include "stdafx.h"
#include "PhoneBook.h"

#include "SubscriberPhoneNumbersDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSubscriberPhoneNumbersDoc

IMPLEMENT_DYNCREATE(CSubscriberPhoneNumbersDoc, CDocument)

BEGIN_MESSAGE_MAP(CSubscriberPhoneNumbersDoc, CDocument)
END_MESSAGE_MAP()


// CSubscriberPhoneNumbersDoc construction/destruction

CSubscriberPhoneNumbersDoc::CSubscriberPhoneNumbersDoc()
{
	// TODO: add one-time construction code here

}

CSubscriberPhoneNumbersDoc::~CSubscriberPhoneNumbersDoc()
{
}

BOOL CSubscriberPhoneNumbersDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CSubscriberPhoneNumbersDoc serialization

void CSubscriberPhoneNumbersDoc::Serialize(CArchive& ar)
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

BOOL CSubscriberPhoneNumbersDoc::SelectAll(CSubscriberPhoneNumbersArray &oSubscriberPhoneNumbersArray)
{
	return m_oSubscriberPhoneNumbersTable.SelectAll(oSubscriberPhoneNumbersArray);
}

BOOL CSubscriberPhoneNumbersDoc::SelectWhereId(const int iId, CSubscriberPhoneNumbers &oSubscriber)
{
	return m_oSubscriberPhoneNumbersTable.SelectWhereId(iId, oSubscriber);
}
BOOL CSubscriberPhoneNumbersDoc::UpdateWhereId(const int iId, const CSubscriberPhoneNumbers &oSubscriber)
{
	BOOL bRes = m_oSubscriberPhoneNumbersTable.UpdateWhereId(iId, oSubscriber);
	if(!bRes)
		return FALSE;

	/* индициране за извършени промени по съдържанието на таблицата */
	
	UpdateAllViews(0, (LPARAM)&oSubscriber);
		
	return bRes;
}

BOOL CSubscriberPhoneNumbersDoc::Insert(const CSubscriberPhoneNumbers &oSubscriber)
{
	BOOL bRes = m_oSubscriberPhoneNumbersTable.Insert(oSubscriber);
	if(!bRes)
		return FALSE;

	/* индициране за извършени промени по съдържанието на таблицата */
	
	UpdateAllViews(0);
	
	return bRes;
}

BOOL CSubscriberPhoneNumbersDoc::DeleteWhereId(const int iId)
{
	BOOL bRes = m_oSubscriberPhoneNumbersTable.DeleteWhereId(iId);
	if(!bRes)
		return FALSE;

	/* индициране за извършени промени по съдържанието на таблицата */
	
	UpdateAllViews(0);
	
	return bRes;
}

BOOL CSubscriberPhoneNumbersDoc::SortByColumn(const eColumn eCol, const BOOL bAsc)
{
	/* номерът на избраната колона се превежда в такъв, с начало първата потребителска колона от таблицата */
	int iTableCol = (int)eCol + (int)CSubscriberPhoneNumbersTable::eColSubscrCode ;
	return m_oSubscriberPhoneNumbersTable.SortByColumn((CSubscriberPhoneNumbersTable::eColumn)iTableCol , bAsc);
}

BOOL CSubscriberPhoneNumbersDoc::SelectByContent(const CSubscriberPhoneNumbers &oSubscriber)
{
	CSubscriberPhoneNumbers oModCity = oSubscriber;
	/* търсенето да включи всички записи */ 
	oModCity.m_iId = DNC;
	return m_oSubscriberPhoneNumbersTable.SelectByContent(oModCity);
}

BOOL CSubscriberPhoneNumbersDoc::SelectAllSubscribersCodes(CSubscribersArray &oSubscribersArray)
{
	return m_oSubscriberPhoneNumbersTable.SelectAllSubscribersCodes(oSubscribersArray);
}

BOOL CSubscriberPhoneNumbersDoc::SelectAllPhoneTypesCodes(CPhoneTypesArray &oPhoneTypesArray)
{
	return m_oSubscriberPhoneNumbersTable.SelectAllPhoneTypesCodes(oPhoneTypesArray);
}

// CSubscriberPhoneNumbersDoc diagnostics

#ifdef _DEBUG
void CSubscriberPhoneNumbersDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSubscriberPhoneNumbersDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSubscriberPhoneNumbersDoc commands
