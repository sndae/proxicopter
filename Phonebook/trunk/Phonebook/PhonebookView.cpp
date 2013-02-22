// PhonebookView.cpp : implementation of the CPhonebookView class
//

#include "stdafx.h"
#include "Phonebook.h"

#include "PhonebookDoc.h"
#include "PhonebookView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CPhonebookView, CFormView)

BEGIN_MESSAGE_MAP(CPhonebookView, CFormView)
  ON_BN_CLICKED(IDC_LOADDB, &CPhonebookView::OnBnClickedLoaddb)
  ON_CBN_SELCHANGE(IDC_REGISTER_SELECTOR, &CPhonebookView::OnCbnSelchangeRegisterSelector)
  ON_BN_CLICKED(IDC_SORTBYCOL1, &CPhonebookView::OnBnClickedSortbycol1)
  ON_BN_CLICKED(IDC_SORTBYCOL3, &CPhonebookView::OnBnClickedSortbycol3)
  ON_BN_CLICKED(IDC_SORTBYCOL2, &CPhonebookView::OnBnClickedSortbycol2)
  ON_BN_CLICKED(IDC_SORTBYCOL4, &CPhonebookView::OnBnClickedSortbycol4)
  ON_BN_CLICKED(IDC_SORTBYCOL5, &CPhonebookView::OnBnClickedSortbycol5)
  ON_BN_CLICKED(IDC_SORTBYCOL6, &CPhonebookView::OnBnClickedSortbycol6)
  ON_BN_CLICKED(IDC_SORTBYCOL7, &CPhonebookView::OnBnClickedSortbycol7)
END_MESSAGE_MAP()

// CPhonebookView construction/destruction

CPhonebookView::CPhonebookView()
	: CFormView(CPhonebookView::IDD)
{
	// TODO: add construction code here

}

CPhonebookView::~CPhonebookView()
{
  CleanUpTablesData();
  
  if(m_pTablesContainer)
    delete m_pTablesContainer;
}

void CPhonebookView::DoDataExchange(CDataExchange* pDX)
{
  CFormView::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_REGISTER_SELECTOR, m_RegSelector);
  DDX_Control(pDX, IDC_SORTBYCOL1, m_SortByCol[0]);
  DDX_Control(pDX, IDC_SORTBYCOL2, m_SortByCol[1]);
  DDX_Control(pDX, IDC_SORTBYCOL3, m_SortByCol[2]);
  DDX_Control(pDX, IDC_SORTBYCOL4, m_SortByCol[3]);
  DDX_Control(pDX, IDC_SORTBYCOL5, m_SortByCol[4]);
  DDX_Control(pDX, IDC_SORTBYCOL6, m_SortByCol[5]);
  DDX_Control(pDX, IDC_SORTBYCOL7, m_SortByCol[6]);

  m_pTablesContainer = 0;
  /* row 1 */
  DDX_Control(pDX, IDC_EDIT1, m_TableFields[0][0]);
  DDX_Control(pDX, IDC_EDIT2, m_TableFields[0][1]);
  DDX_Control(pDX, IDC_EDIT3, m_TableFields[0][2]);
  DDX_Control(pDX, IDC_EDIT4, m_TableFields[0][3]);
  DDX_Control(pDX, IDC_EDIT5, m_TableFields[0][4]);
  DDX_Control(pDX, IDC_EDIT6, m_TableFields[0][5]);
  DDX_Control(pDX, IDC_EDIT7, m_TableFields[0][6]);
  /* row 2 */
  DDX_Control(pDX, IDC_EDIT8, m_TableFields[1][0]);
  DDX_Control(pDX, IDC_EDIT9, m_TableFields[1][1]);
  DDX_Control(pDX, IDC_EDIT10, m_TableFields[1][2]);
  DDX_Control(pDX, IDC_EDIT11, m_TableFields[1][3]);
  DDX_Control(pDX, IDC_EDIT12, m_TableFields[1][4]);
  DDX_Control(pDX, IDC_EDIT13, m_TableFields[1][5]);
  DDX_Control(pDX, IDC_EDIT14, m_TableFields[1][6]);

  /* row 3 */
  DDX_Control(pDX, IDC_EDIT15, m_TableFields[2][0]);
  DDX_Control(pDX, IDC_EDIT16, m_TableFields[2][1]);
  DDX_Control(pDX, IDC_EDIT17, m_TableFields[2][2]);
  DDX_Control(pDX, IDC_EDIT18, m_TableFields[2][3]);
  DDX_Control(pDX, IDC_EDIT19, m_TableFields[2][4]);
  DDX_Control(pDX, IDC_EDIT20, m_TableFields[2][5]);
  DDX_Control(pDX, IDC_EDIT21, m_TableFields[2][6]);

  /* row 4 */
  DDX_Control(pDX, IDC_EDIT22, m_TableFields[3][0]);
  DDX_Control(pDX, IDC_EDIT23, m_TableFields[3][1]);
  DDX_Control(pDX, IDC_EDIT24, m_TableFields[3][2]);
  DDX_Control(pDX, IDC_EDIT25, m_TableFields[3][3]);
  DDX_Control(pDX, IDC_EDIT26, m_TableFields[3][4]);
  DDX_Control(pDX, IDC_EDIT27, m_TableFields[3][5]);
  DDX_Control(pDX, IDC_EDIT28, m_TableFields[3][6]);

  DDX_Control(pDX, IDC_TABLES_PATH, m_TablePath);
  DDX_Control(pDX, IDC_DSN, m_DSN);

  ClearSortButtonsLabels();
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

  m_TablePath.SetWindowTextW(L"phonebook.dbo");
  m_DSN.SetWindowTextW(L"SQLEXPRESS");

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
  if(m_pTablesContainer)
    delete m_pTablesContainer;

  CString csDSN;
  m_DSN.GetWindowTextW(csDSN);
  CString csDBPath;
  m_TablePath.GetWindowTextW(csDBPath);
  m_pTablesContainer = new CDBTablesContainer(csDSN, csDBPath);

  RecreateTableSelectorContent();
}

void CPhonebookView::OnCbnSelchangeRegisterSelector()
{
  // TODO: Add your control notification handler code here
  RecreateRowsContent();
}

void CPhonebookView::OnBnClickedSortbycol1()
{
  // TODO: Add your control notification handler code here
  SortByCol(0);
}

void CPhonebookView::OnBnClickedSortbycol2()
{
  // TODO: Add your control notification handler code here
  SortByCol(1);
}
void CPhonebookView::OnBnClickedSortbycol3()
{
  // TODO: Add your control notification handler code here
  SortByCol(2);
}


void CPhonebookView::OnBnClickedSortbycol4()
{
  // TODO: Add your control notification handler code here
  SortByCol(3);
}

void CPhonebookView::OnBnClickedSortbycol5()
{
  // TODO: Add your control notification handler code here
  SortByCol(4);
}

void CPhonebookView::OnBnClickedSortbycol6()
{
  // TODO: Add your control notification handler code here
  SortByCol(5);
}

void CPhonebookView::OnBnClickedSortbycol7()
{
  // TODO: Add your control notification handler code here
  SortByCol(6);
}

void CPhonebookView::ClearSortButtonsLabels()
{
  for(int i = 0; i < sizeof(m_SortByCol)/sizeof(m_SortByCol[0]); i++)
  {
    m_SortByCol[i].SetWindowTextW(L"");
  }
}

void CPhonebookView::RecreateSortButtonsLabels()
{
  ClearSortButtonsLabels();

  CDbTableInterface *pcTable = m_apTables[m_RegSelector.GetCurSel()];
  CArray<CString> a_csFieldValues;
  if(pcTable->GetColumnsRepresNames(a_csFieldValues))
  {
    for(int i = 0; (i < a_csFieldValues.GetCount()) && (i < COLUMN_NUMBER); i++)
    {
      m_SortByCol[i].SetWindowTextW(a_csFieldValues[i]);
    }
  }  

}

void CPhonebookView::ClearRowContent(int iRow)
{
  for(int i = 0; i < COLUMN_NUMBER; i++)
  {
    m_TableFields[iRow][i].SetWindowTextW(L"");
  }
}

void CPhonebookView::ClearAllRowsContent()
{
  for(int i = 0; i < ROW_NUMBER; i++)
  {
    ClearRowContent(i);
  }
}

void CPhonebookView::DisableSortButtonsAndRows()
{

}

void CPhonebookView::EnableSortButtonsAndRows()
{

}

void CPhonebookView::RecreateRowsContent()
{
  ClearAllRowsContent();

  CDbTableInterface *pcTable = m_apTables[m_RegSelector.GetCurSel()];

  HANDLE hRow = 0;
  CArray<CString> a_csFieldValues;

  for(int iRow = 0; hRow = pcTable->ReadRow(a_csFieldValues, iRow); iRow++)
  {
    m_ahRows.Add(hRow);
    
    if(hRow){
      for(int i = 0; i < a_csFieldValues.GetCount() && (i < COLUMN_NUMBER); i++)
      {
        m_TableFields[iRow][i].SetWindowTextW(a_csFieldValues[i]);
      }
    }
    a_csFieldValues.RemoveAll();
  }

  RecreateSortButtonsLabels();
}

void CPhonebookView::RecreateTableSelectorContent()
{
  /* free all tables stored */
  int iTablesCnt = m_apTables.GetCount();
  while(iTablesCnt--)  
    m_RegSelector.DeleteString(iTablesCnt);
 
  CleanUpTablesData();

  CDbTableInterface *pcTable = m_pTablesContainer->GetFirstTable();
  if(pcTable){
    m_apTables.Add(pcTable);
    m_RegSelector.AddString(pcTable->GetTableRepresName());
  }
  while(pcTable = m_pTablesContainer->GetNextTable())
  {
    m_apTables.Add(pcTable);
    m_RegSelector.AddString(pcTable->GetTableRepresName());
  }
  
  m_RegSelector.SetCurSel(0);
  
  RecreateRowsContent();
}

void CPhonebookView::CleanUpTablesData()
{
  int iTablesCnt = m_apTables.GetCount();
  while(iTablesCnt--)
  {
    delete m_apTables.GetAt(iTablesCnt);
  }
  m_apTables.RemoveAll();

  CleanUpRowData();
}

void CPhonebookView::CleanUpRowData()
{
  int iRowCnt = m_ahRows.GetCount();
  while(iRowCnt--)
  {
    delete m_ahRows.GetAt(iRowCnt);
  }
  m_ahRows.RemoveAll();
}

void CPhonebookView::SortByCol(int iColNmb)
{
  CDbTableInterface *pTable = m_apTables[m_RegSelector.GetCurSel()];

  if(pTable->SortTableByColumn(0, m_SortByCol[iColNmb].eCurrSortType) == TRUE)
    m_SortByCol[iColNmb].InvertSortType();

  RecreateRowsContent();  
}