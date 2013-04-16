// NewDocDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "NewDocDlg.h"


// CNewDocDlg dialog

IMPLEMENT_DYNAMIC(CNewDocDlg, CDialog)

CNewDocDlg::CNewDocDlg(CPtrList *poTemplateList, CWnd* pParent /*=NULL*/)
	: CDialog(CNewDocDlg::IDD, pParent)
{
	m_poSelectedTempl = 0;
	m_poTemplateList = poTemplateList;
}

CNewDocDlg::~CNewDocDlg()
{
}

void CNewDocDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, LSB_NEWDOC_LIST, m_cListCtrl);
}

BOOL CNewDocDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	if(m_poTemplateList)
	{	
		InitIcons();
		InitItems();
	}

	return TRUE;
}

void CNewDocDlg::InitItems()
{
	// Изтриване на всички вече вмъкнати обекти
	m_cListCtrl.DeleteAllItems();

	LVITEM lvi;

	POSITION oPos = m_poTemplateList->GetTailPosition();
	CString	strClassName;
	int iCntr = 0;
	while(oPos)
	{
	 ((CDocTemplate*)m_poTemplateList->GetAt(oPos))->GetDocString(strClassName, CDocTemplate::fileNewName);
 
		// Вмъкване на първият обект
		lvi.mask =	LVIF_IMAGE | LVIF_TEXT;

		lvi.iItem = iCntr;
		lvi.iSubItem = 0;
		lvi.pszText = (LPTSTR)(LPCTSTR)(strClassName.GetBuffer());
		lvi.iImage = iCntr;		// Налични са 8 изображения в листа с иконите
		m_cListCtrl.InsertItem(&lvi);
#if 0
		// Вмъкване на подобкет 1
		lvi.iSubItem = 1;
		lvi.pszText = (LPTSTR)(LPCTSTR)(strClassName.GetBuffer());
		m_cListCtrl.SetItem(&lvi);

		// Вмъкване на подобект 2
		lvi.iSubItem = 2;
		lvi.pszText = (LPTSTR)(LPCTSTR)(strClassName.GetBuffer());
		m_cListCtrl.SetItem(&lvi);
#endif
		iCntr++;
		m_poTemplateList->GetPrev(oPos);
	}
	
}

void CNewDocDlg::InitIcons()
{
	// Създаване на лист за иконите
	HIMAGELIST hList = ImageList_Create(32,32, ILC_COLOR8 |ILC_MASK , 8, 1);
	m_cImageListNormal.Attach(hList);

	// Зареждане на иконите
	CBitmap cBmp;
	cBmp.LoadBitmap(IDB_IMAGES_NORMAL);
	m_cImageListNormal.Add(&cBmp, RGB(255,0, 255));
	cBmp.DeleteObject();

	// Прикачване на списъка с иконик към контролата
	m_cListCtrl.SetImageList(&m_cImageListNormal, LVSIL_NORMAL);
}

void CNewDocDlg::OnOK()
{
	LVHITTESTINFO	oHitInfo;
	m_cListCtrl.SubItemHitTest(&oHitInfo);

	CDialog::OnOK();
}

CDocTemplate *CNewDocDlg::GetSelectedDoc()
{
	return m_poSelectedTempl;
}

BEGIN_MESSAGE_MAP(CNewDocDlg, CDialog)
	ON_NOTIFY(NM_CLICK, LSB_NEWDOC_LIST, &CNewDocDlg::OnNMClickNewdoclistCtrl)
	ON_NOTIFY(NM_DBLCLK, LSB_NEWDOC_LIST, &CNewDocDlg::OnNMDblclkListCtrl)
END_MESSAGE_MAP()

void CNewDocDlg::OnNMClickNewdoclistCtrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMITEMACTIVATE *pNMItemActivate = (NMITEMACTIVATE*)pNMHDR;
	// TODO: Add your control notification handler code here
	POSITION oPos = m_poTemplateList->GetTailPosition();
	int iItemSelected = pNMItemActivate->iItem;
	if(iItemSelected >= 0)
	{
	//	iItemSelected = (m_poTemplateList->GetCount() - 1) - iItemSelected ;
		while(iItemSelected--)
			m_poTemplateList->GetPrev(oPos);
	}

	m_poSelectedTempl = (CDocTemplate*)m_poTemplateList->GetAt(oPos);

	*pResult = 0;
}

void CNewDocDlg::OnNMDblclkListCtrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	OnNMClickNewdoclistCtrl(pNMHDR, pResult);
	OnOK();

	*pResult = 0;
}
