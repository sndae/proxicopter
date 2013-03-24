// PhoneBook.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "NewDocDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPhoneBookApp

BEGIN_MESSAGE_MAP(CPhoneBookApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CPhoneBookApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CPhoneBookApp construction

CPhoneBookApp::CPhoneBookApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CPhoneBookApp object

CPhoneBookApp theApp;


// CPhoneBookApp initialization

BOOL CPhoneBookApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_CITY_TYPE,
		RUNTIME_CLASS(CCitiesDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CCitiesView));

	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

  pDocTemplate = new CMultiDocTemplate(IDR_PHONES_TYPE,
		RUNTIME_CLASS(CPhoneTypesDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CPhoneTypesView));

	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

  pDocTemplate = new CMultiDocTemplate(IDR_SUBSCRIBERS_TYPE,
		RUNTIME_CLASS(CSubscribersDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSubscribersView));

	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

  pDocTemplate = new CMultiDocTemplate(IDR_SUBSCRIBER_PHONE_NUMBERS_TYPE,
    RUNTIME_CLASS(CSubscriberPhoneNumbersDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSubscriberPhoneNumbersView));

	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

  CMainFrame* pMainFrame = new CMainFrame;

  m_poCitiesDoc = new CCitiesDoc;

  m_poCitiesDoc->SetTitle(L"Just a demo");
  CCreateContext context;
  context.m_pCurrentDoc = m_poCitiesDoc;
  context.m_pNewViewClass = NULL;
  context.m_pNewDocTemplate = NULL;
  context.m_pLastView = NULL;
  context.m_pCurrentFrame = NULL;
  if (!pMainFrame->LoadFrame(IDR_MAINFRAME,WS_OVERLAPPEDWINDOW |
  FWS_ADDTOTITLE,NULL, &context ))
    return FALSE;
  
  m_pMainWnd = pMainFrame;

#if 0
	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// call DragAcceptFiles only if there's a suffix
	//  In an MDI app, this should occur immediately after setting m_pMainWnd


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
#endif
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CPhoneBookApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


void CPhoneBookApp::OnFileNew()
{
  CPtrList oTemplateList;
  
  CDocManager *poAppDocManager = AfxGetApp()->m_pDocManager;
  
  POSITION pDocTemplPos = poAppDocManager->GetFirstDocTemplatePosition();
  
  while(pDocTemplPos){
    CDocTemplate *poDocTemplate  = poAppDocManager->GetNextDocTemplate(pDocTemplPos);
    oTemplateList.AddHead(poDocTemplate);
  }

	if (oTemplateList.GetCount() > 1)
	{
//#include "NewDocDlg.h"
    CNewDocDlg dlg(&oTemplateList);
    dlg.DoModal();
		// more than one document template to choose from
		// bring up dialog prompting user

    //CNewTypeDlg dlg(&oTemplateList);
		//INT_PTR nID = dlg.DoModal();
		//if (nID == IDOK)
	//		poDocTemplate = dlg.m_pSelectedTemplate;
	//	else
	//		return;     // none - cancel operation
	}

	//ASSERT(poDocTemplate != NULL);
	//ASSERT_KINDOF(CDocTemplate, poDocTemplate);

	//poDocTemplate->OpenDocumentFile(NULL);
}


// CPhoneBookApp message handlers

