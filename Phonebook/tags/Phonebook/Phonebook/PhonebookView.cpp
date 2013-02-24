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
  ON_BN_CLICKED(IDC_WRITE_ROW,  &CPhonebookView::OnBnClickedWriteRow)  
  ON_BN_CLICKED(IDC_SORTBYCOL1, &CPhonebookView::OnBnClickedSortbycol1)
  ON_BN_CLICKED(IDC_SORTBYCOL3, &CPhonebookView::OnBnClickedSortbycol3)
  ON_BN_CLICKED(IDC_SORTBYCOL2, &CPhonebookView::OnBnClickedSortbycol2)
  ON_BN_CLICKED(IDC_SORTBYCOL4, &CPhonebookView::OnBnClickedSortbycol4)
  ON_BN_CLICKED(IDC_SORTBYCOL5, &CPhonebookView::OnBnClickedSortbycol5)
  ON_BN_CLICKED(IDC_SORTBYCOL6, &CPhonebookView::OnBnClickedSortbycol6)
  ON_BN_CLICKED(IDC_SORTBYCOL7, &CPhonebookView::OnBnClickedSortbycol7)
  ON_EN_CHANGE(IDC_EDIT1, &CPhonebookView::OnEnChangeEdit1)
  ON_EN_CHANGE(IDC_EDIT2, &CPhonebookView::OnEnChangeEdit1)
  ON_EN_CHANGE(IDC_EDIT3, &CPhonebookView::OnEnChangeEdit1)
  ON_EN_CHANGE(IDC_EDIT4, &CPhonebookView::OnEnChangeEdit1)
  ON_EN_CHANGE(IDC_EDIT5, &CPhonebookView::OnEnChangeEdit1)
  ON_EN_CHANGE(IDC_EDIT6, &CPhonebookView::OnEnChangeEdit1)
  ON_EN_CHANGE(IDC_EDIT7, &CPhonebookView::OnEnChangeEdit1)

  ON_EN_CHANGE(IDC_EDIT8, &CPhonebookView::OnEnChangeEdit8)
  ON_EN_CHANGE(IDC_EDIT9, &CPhonebookView::OnEnChangeEdit8)
  ON_EN_CHANGE(IDC_EDIT10, &CPhonebookView::OnEnChangeEdit8)
  ON_EN_CHANGE(IDC_EDIT11, &CPhonebookView::OnEnChangeEdit8)
  ON_EN_CHANGE(IDC_EDIT12, &CPhonebookView::OnEnChangeEdit8)
  ON_EN_CHANGE(IDC_EDIT13, &CPhonebookView::OnEnChangeEdit8)
  ON_EN_CHANGE(IDC_EDIT14, &CPhonebookView::OnEnChangeEdit8)

  ON_EN_CHANGE(IDC_EDIT15, &CPhonebookView::OnEnChangeEdit15)
  ON_EN_CHANGE(IDC_EDIT16, &CPhonebookView::OnEnChangeEdit15)
  ON_EN_CHANGE(IDC_EDIT17, &CPhonebookView::OnEnChangeEdit15)
  ON_EN_CHANGE(IDC_EDIT18, &CPhonebookView::OnEnChangeEdit15)
  ON_EN_CHANGE(IDC_EDIT19, &CPhonebookView::OnEnChangeEdit15)
  ON_EN_CHANGE(IDC_EDIT20, &CPhonebookView::OnEnChangeEdit15)
  ON_EN_CHANGE(IDC_EDIT21, &CPhonebookView::OnEnChangeEdit15)

  ON_EN_CHANGE(IDC_EDIT22, &CPhonebookView::OnEnChangeEdit22)
  ON_EN_CHANGE(IDC_EDIT23, &CPhonebookView::OnEnChangeEdit22)
  ON_EN_CHANGE(IDC_EDIT24, &CPhonebookView::OnEnChangeEdit22)
  ON_EN_CHANGE(IDC_EDIT25, &CPhonebookView::OnEnChangeEdit22)
  ON_EN_CHANGE(IDC_EDIT26, &CPhonebookView::OnEnChangeEdit22)
  ON_EN_CHANGE(IDC_EDIT27, &CPhonebookView::OnEnChangeEdit22)
  ON_EN_CHANGE(IDC_EDIT28, &CPhonebookView::OnEnChangeEdit22)

  ON_BN_CLICKED(IDC_DELETE_ROW, &CPhonebookView::OnBnClickedDeleteRow)
  ON_BN_CLICKED(IDC_SCROLLUP, &CPhonebookView::OnBnClickedScrollup)
  ON_BN_CLICKED(IDC_SCROLLDOWN, &CPhonebookView::OnBnClickedScrolldown)
  ON_BN_CLICKED(IDC_ADDROW, &CPhonebookView::OnBnClickedAddrow)
  ON_BN_CLICKED(IDC_SEARCHROW, &CPhonebookView::OnBnClickedSearchrow)
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
  
  if(m_pTablesFactory)
    delete m_pTablesFactory;
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

  m_pTablesFactory = 0;
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

  for(int i = 0; i < sizeof(m_SortByCol)/sizeof(m_SortByCol[0]); i++)
    m_SortByCol[i].EnableWindow(0);

  m_iRowsOffset = 0;
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
void CPhonebookView::OnBnClickedWriteRow()
{
  CString csMessage;
  if(m_iLastRowClicked >= m_ahRows.GetCount()){
    MessageBox(_T("Invalid row"), MB_OK, MB_ICONSTOP);
    return;
  }

  csMessage.Format(_T("Would you like to write data at row %d ?"), m_iLastRowClicked + 1);
  if(MessageBox(csMessage, 0, MB_OKCANCEL|MB_ICONINFORMATION) == IDOK)
  {
    CDbTableInterface *pcTable = m_apTables[m_RegSelector.GetCurSel()];
    CArray<CString> a_csFieldValues;
    for(int i = 0; i < pcTable->GetColumnsNumber(); i++)
    {
      m_TableFields[m_iLastRowClicked][i].GetWindowTextW(csMessage);
      a_csFieldValues.Add(csMessage);
    }
    if(pcTable->WriteRow(a_csFieldValues, m_ahRows[m_iLastRowClicked]) == FALSE)
    {
      csMessage = _T("");
      csMessage.Format(_T("Problem while trying to write at row %d emerged. \nValidate field values or try table update."),  m_iLastRowClicked + 1); 
      MessageBox(csMessage, 0, MB_OK|MB_ICONWARNING);
    }else{
      RecreateRowsContent();
    }
  }
}

void CPhonebookView::OnBnClickedLoaddb()
{
  // TODO: Add your control notification handler code here
  if(m_pTablesFactory)
    delete m_pTablesFactory;

  CString csDSN;
  m_DSN.GetWindowTextW(csDSN);
  CString csDBPath;
  m_TablePath.GetWindowTextW(csDBPath);
  m_pTablesFactory = new CDBTablesFactory(csDSN, csDBPath);

  RecreateTableSelectorContent();
}

void CPhonebookView::OnCbnSelchangeRegisterSelector()
{
  // TODO: Add your control notification handler code here
  m_iRowsOffset = 0;
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

void CPhonebookView::RecreateSortButtonsLabels()
{
  CDbTableInterface *pcTable = m_apTables[m_RegSelector.GetCurSel()];
  CArray<CString> a_csFieldValues;
  if(pcTable->GetColumnsRepresNames(a_csFieldValues))
  {
    int i = 0;
    for( ; (i < a_csFieldValues.GetCount()) && (i < sizeof(m_SortByCol)/sizeof(m_SortByCol[0])); i++)
    {
      m_SortByCol[i].SetWindowTextW(a_csFieldValues[i]);
      m_SortByCol[i].EnableWindow();
    }
    for( ; i < sizeof(m_SortByCol)/sizeof(m_SortByCol[0]); i++)
    {
      m_SortByCol[i].SetWindowTextW(_T(""));
      m_SortByCol[i].EnableWindow(0);
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


void CPhonebookView::RecreateRowsContent()
{
  ClearAllRowsContent();
  CleanUpRowData();
  CDbTableInterface *pcTable = m_apTables[m_RegSelector.GetCurSel()];

  HANDLE hRow = 0;
  CArray<CString> a_csFieldValues;
  
  RecreateSortButtonsLabels();

  for(int iRow = 0; (hRow = pcTable->ReadRow(a_csFieldValues, iRow + m_iRowsOffset)) && (iRow < ROW_NUMBER); iRow++)
  {
    m_ahRows.Add(hRow);
    
    if(hRow){
      for(int i = 0; i < a_csFieldValues.GetCount() && (i < COLUMN_NUMBER); i++)
      {
          m_TableFields[iRow ][i].SetWindowTextW(a_csFieldValues[i]);
      }
    }
    a_csFieldValues.RemoveAll();
  }
}

void CPhonebookView::RecreateTableSelectorContent()
{
  /* free all tables stored */
  int iTablesCnt = m_apTables.GetCount();
  while(iTablesCnt--)  
    m_RegSelector.DeleteString(iTablesCnt);
 
  CleanUpTablesData();

  CDbTableInterface *pcTable = m_pTablesFactory->GetFirstTable();
  if(pcTable){
    m_apTables.Add(pcTable);
    m_RegSelector.AddString(pcTable->GetTableRepresName());
  }
  while(pcTable = m_pTablesFactory->GetNextTable())
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

  if(pTable->SortTableByColumn(iColNmb, m_SortByCol[iColNmb].eCurrSortType) == TRUE)
    m_SortByCol[iColNmb].InvertSortType();

  RecreateRowsContent();  
}

void CPhonebookView::OnEnChangeEdit1()
{
  // TODO:  If this is a RICHEDIT control, the control will not
  // send this notification unless you override the CFormView::OnInitDialog()
  // function and call CRichEditCtrl().SetEventMask()
  // with the ENM_CHANGE flag ORed into the mask.

  // TODO:  Add your control notification handler code here
  m_iLastRowClicked = 0;
}

void CPhonebookView::OnEnChangeEdit8()
{
  // TODO:  If this is a RICHEDIT control, the control will not
  // send this notification unless you override the CFormView::OnInitDialog()
  // function and call CRichEditCtrl().SetEventMask()
  // with the ENM_CHANGE flag ORed into the mask.

  // TODO:  Add your control notification handler code here
  m_iLastRowClicked = 1;
}

void CPhonebookView::OnEnChangeEdit15()
{
  // TODO:  If this is a RICHEDIT control, the control will not
  // send this notification unless you override the CFormView::OnInitDialog()
  // function and call CRichEditCtrl().SetEventMask()
  // with the ENM_CHANGE flag ORed into the mask.

  // TODO:  Add your control notification handler code here
  m_iLastRowClicked =2;
}

void CPhonebookView::OnEnChangeEdit22()
{
  // TODO:  If this is a RICHEDIT control, the control will not
  // send this notification unless you override the CFormView::OnInitDialog()
  // function and call CRichEditCtrl().SetEventMask()
  // with the ENM_CHANGE flag ORed into the mask.

  // TODO:  Add your control notification handler code here
  m_iLastRowClicked = 3;
}

void CPhonebookView::OnBnClickedDeleteRow()
{
  // TODO: Add your control notification handler code here
  if(m_iLastRowClicked >= m_ahRows.GetCount()){
    MessageBox(_T("Invalid row"), MB_OK, MB_ICONSTOP);
    return;
  }
  CString csMessage;
  csMessage.Format(_T("Are you sure you want to delete row %d ?"), m_iLastRowClicked + 1);
  if(MessageBox(csMessage, 0, MB_OKCANCEL|MB_ICONINFORMATION) == IDOK)
  {
    CDbTableInterface *pTable = m_apTables[m_RegSelector.GetCurSel()];
    pTable->DeleteRow(m_ahRows[m_iLastRowClicked]);
  }else{
    RecreateRowsContent();
  }
}

void CPhonebookView::OnBnClickedScrollup()
{
  // TODO: Add your control notification handler code here
  if(m_iRowsOffset){
    m_iRowsOffset--;
    RecreateRowsContent();
  }
}

void CPhonebookView::OnBnClickedScrolldown()
{
  // TODO: Add your control notification handler code here
  if(m_ahRows.GetCount() > (ROW_NUMBER - 1))
  {
    m_iRowsOffset++;
    RecreateRowsContent();
  }
}

void CPhonebookView::OnBnClickedAddrow()
{
  // TODO: Add your control notification handler code here
  if((m_ahRows.GetCount() == ROW_NUMBER) || (m_iLastRowClicked != m_ahRows.GetCount()))
  {
    MessageBox(_T("Please scroll to an empty row via 'Scroll down' button"), 0, MB_OK|MB_ICONINFORMATION);
  }
  else
  {
    CArray<CString> a_csRowData;
    CDbTableInterface *pTable = m_apTables[m_RegSelector.GetCurSel()];
    CString csWindowText;
    for(int i = 0; i < pTable->GetColumnsNumber(); i++)
    {
      CString csWindowText;
      m_TableFields[m_iLastRowClicked][i].GetWindowTextW(csWindowText);
      a_csRowData.InsertAt(i, csWindowText);
    }

    if(!pTable->AddRow(a_csRowData)){
      MessageBox(_T("Adding row failed. Validate fields values"), 0, MB_OK|MB_ICONEXCLAMATION);    
    }else{
      RecreateRowsContent();
      OnBnClickedScrolldown();
    }
  }
}

void CPhonebookView::OnBnClickedSearchrow()
{
  // TODO: Add your control notification handler code here
  if((m_ahRows.GetCount() == ROW_NUMBER) || (m_iLastRowClicked != m_ahRows.GetCount()))
  {
    MessageBox(_T("Please scroll to an empty row via 'Scroll down' button"), 0, MB_OK|MB_ICONINFORMATION);
  }
  else
  {
    CArray<CString> a_csRowData;
    CDbTableInterface *pTable = m_apTables[m_RegSelector.GetCurSel()];
    CString csWindowText;
    int iColNmb = 0;
    for( ; iColNmb < pTable->GetColumnsNumber(); iColNmb++)
    {
      m_TableFields[m_iLastRowClicked][iColNmb].GetWindowTextW(csWindowText);
      if(csWindowText.GetLength() != 0)
        break;
    }
    pTable->FilterTableByColumnValue(iColNmb, csWindowText, CDbTableInterface::eEquals);
    RecreateRowsContent();
  }
}
