// PhonebookView.cpp : implementation of the CPhonebookView class
//

#include "stdafx.h"
#include "Phonebook.h"

#include "PhonebookDoc.h"
#include "PhonebookView.h"
#include "Cities.h"
#include "PhonesTable.h"
#include "PhoneBookDBException.h"
#include "DbTableInterface.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPhonebookView
const CPhonebookView::RegnameToTablenameMapping CPhonebookView::m_stRegnameToTablenameMapping[4] = 
{  
  {_T("Градове"), _T("phonebook.dbo.cities")},
  {_T("Типове телефони"), _T("phonebook.dbo.phones")},
  {_T("Абонати"), _T("phonebook.dbo.subscribers")},
  {_T("Телефонни номера"), _T("phonebook.dbo.subscriber_phone_numbers")},
};

IMPLEMENT_DYNCREATE(CPhonebookView, CFormView)

BEGIN_MESSAGE_MAP(CPhonebookView, CFormView)
  ON_BN_CLICKED(IDC_LOADDB, &CPhonebookView::OnBnClickedLoaddb)
  ON_CBN_SELCHANGE(IDC_REGISTER_SELECTOR, &CPhonebookView::OnCbnSelchangeRegisterSelector)
END_MESSAGE_MAP()

// CPhonebookView construction/destruction

CPhonebookView::CPhonebookView()
	: CFormView(CPhonebookView::IDD)
{
	// TODO: add construction code here

}

CPhonebookView::~CPhonebookView()
{
}

void CPhonebookView::DoDataExchange(CDataExchange* pDX)
{
  CFormView::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_REGISTER_SELECTOR, m_RegSelector);
  DDX_Control(pDX, IDC_REGISTER_CONTENT, m_RegContentList);
}

BOOL CPhonebookView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CPhonebookView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

  if(m_Database.Open(_T("SQLEXPRESS")) != 0)
  {
    CCities cCitiesTable(&m_Database, _T("phonebook.dbo"));
    CDbTableInterface *pc = static_cast<CDbTableInterface*>(&cCitiesTable);

    //BOOL bRes = pc->SortTableByColumn(_T("grad"), CDbTableInterface::eAlphabeticallyRev);
    BOOL bRes = pc->FilterTableByColumnValue(_T("Oblast"), _T("Varnenska"), CDbTableInterface::eEquals);  

    CArray<CString> acsRowData;
    CString *csTableName = pc->GetTableRepresName();
    CString ccTable;
    
    CArray<CString> csFieldNames;
    bRes = pc->GetColumnsRepresNames(csFieldNames);
    for(int i = 0; i<csFieldNames.GetCount(); i++)
    {
      ccTable = csFieldNames.GetAt(i);
    }
    int iRow = 0;
    HANDLE hRow = 0;
    csFieldNames.RemoveAll();
    csFieldNames.Add(_T("33"));
    csFieldNames.Add(_T("Аксаково"));
    csFieldNames.Add(_T("Варненска"));
    
    pc->AddRow(csFieldNames);
    return;
    while(hRow = pc->ReadRow(csFieldNames,iRow++))
    {
      pc->WriteRow(csFieldNames, hRow); 
      for(int c = 0; c < csFieldNames.GetCount(); c++)
      {
        ccTable = csFieldNames.GetAt(c);
      }
      csFieldNames.RemoveAll();
      delete hRow;
    } 
  }
}


// CPhonebookView diagnostics

#ifdef _DEBUG
void CPhonebookView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPhonebookView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CPhonebookDoc* CPhonebookView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhonebookDoc)));
	return (CPhonebookDoc*)m_pDocument;
}
#endif //_DEBUG


// CPhonebookView message handlers

void CPhonebookView::OnBnClickedLoaddb()
{
  // TODO: Add your control notification handler code here

}

void CPhonebookView::OnCbnSelchangeRegisterSelector()
{
  // TODO: Add your control notification handler code here
  int iCurrSel = m_RegSelector.GetCurSel();
  try{
//    CCitiesTable cRecordSet(m_Database); 
  }
  catch(CPhoneBookDBException cException)
  {
    MessageBox(cException.GetErrorMsg());
  }
}
