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
  m_poTemplateList = poTemplateList;
}

CNewDocDlg::~CNewDocDlg()
{
}

void CNewDocDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_NEWDOCLIST_CTRL, m_cListCtrl);
}

BOOL CNewDocDlg::OnInitDialog()
{
  CDialog::OnInitDialog();
  
  if(!m_poTemplateList)
    return TRUE;
  
  InitIcons();
  InitItems();

  return TRUE;
}

void CNewDocDlg::InitItems()
{
	// Delete the current contents
	m_cListCtrl.DeleteAllItems();

	// Use the LV_ITEM structure to insert the items
	LVITEM lvi;

  POSITION oPos = m_poTemplateList->GetHeadPosition();
  CString  csClassName;
  int iCntr = 0;
  while(oPos)
  {
   ((CDocTemplate*)m_poTemplateList->GetAt(oPos))->GetDocString(csClassName, CDocTemplate::fileNewName);
 
		// Insert the first item
		lvi.mask =  LVIF_IMAGE | LVIF_TEXT;

		lvi.iItem = iCntr;
		lvi.iSubItem = 0;
    lvi.pszText = (LPTSTR)(LPCTSTR)(csClassName.GetBuffer());
		lvi.iImage = iCntr%8;		// There are 8 images in the image list
		m_cListCtrl.InsertItem(&lvi);

		// Set subitem 1
		lvi.iSubItem = 1;
		lvi.pszText = (LPTSTR)(LPCTSTR)(csClassName.GetBuffer());
		m_cListCtrl.SetItem(&lvi);

		// Set subitem 2
		lvi.iSubItem = 2;
		lvi.pszText = (LPTSTR)(LPCTSTR)(csClassName.GetBuffer());
		m_cListCtrl.SetItem(&lvi);

    iCntr++;
    m_poTemplateList->GetNext(oPos);
  }
  
}

void CNewDocDlg::InitIcons()
{
	// Create 256 color image lists
	HIMAGELIST hList = ImageList_Create(32,32, ILC_COLOR8 |ILC_MASK , 8, 1);
	m_cImageListNormal.Attach(hList);

	hList = ImageList_Create(16, 16, ILC_COLOR8 | ILC_MASK, 8, 1);
	m_cImageListSmall.Attach(hList);


	// Load the large icons
	CBitmap cBmp;
	cBmp.LoadBitmap(IDB_IMAGES_NORMAL);
	m_cImageListNormal.Add(&cBmp, RGB(255,0, 255));
	cBmp.DeleteObject();

	// Load the small icons
	cBmp.LoadBitmap(IDB_IMAGES_SMALL);
	m_cImageListSmall.Add(&cBmp, RGB(255,0, 255));

	// Attach them
	m_cListCtrl.SetImageList(&m_cImageListNormal, LVSIL_NORMAL);
	m_cListCtrl.SetImageList(&m_cImageListSmall, LVSIL_SMALL);
}


BEGIN_MESSAGE_MAP(CNewDocDlg, CDialog)
END_MESSAGE_MAP()


// CNewDocDlg message handlers
