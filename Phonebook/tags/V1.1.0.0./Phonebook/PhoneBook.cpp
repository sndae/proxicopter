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
	ON_COMMAND(ID_FILE_OPEN,OnFileNew)
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
	// visual styles.	Otherwise, any window creation will fail.
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
	LoadStdProfileSettings(4);	// Load standard INI file options (including MRU)

	/* Създаване на инстанции на наличните типове докоменти */
	CCitiesDoc *poCitiesDoc = new CCitiesDoc;
	CPhoneTypesDoc *poCPhnTypesDoc = new CPhoneTypesDoc;
	CSubscribersDoc *poSubscribersDoc = new CSubscribersDoc;
	CSubscriberPhoneNumbersDoc *poSubscrPhnNmbDoc = new CSubscriberPhoneNumbersDoc;

	poCitiesDoc->SetTitle(L"Градове");
	poCPhnTypesDoc->SetTitle(L"Типове телефони");
	poSubscribersDoc->SetTitle(L"Абонати"); 
	poSubscrPhnNmbDoc->SetTitle(L"Телефонни номера на абонати");

	poCitiesDoc->OnNewDocument();
	poCPhnTypesDoc->OnNewDocument();
	poSubscribersDoc->OnNewDocument(); 
	poSubscrPhnNmbDoc->OnNewDocument();	

	// Register the application's document templates.	Document templates
	//	serve as the connection between documents, frame windows and views	
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_CITY_TYPE,
		RUNTIME_CLASS(CCitiesDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CCitiesView));

	if (!pDocTemplate)
		return FALSE;

	/* Добавяне новосъздадената инстанция на CitiesDoc към темплейта */
	pDocTemplate->AddDocument(poCitiesDoc);
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMultiDocTemplate(IDR_PHONES_TYPE,
		RUNTIME_CLASS(CPhoneTypesDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CPhoneTypesView));

	if (!pDocTemplate)
		return FALSE;

	/* Добавяне новосъздадената инстанция на CPhoneTypesDoc към темплейта */
	pDocTemplate->AddDocument(poCPhnTypesDoc);
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMultiDocTemplate(IDR_SUBSCRIBERS_TYPE,
		RUNTIME_CLASS(CSubscribersDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSubscribersView));

	if (!pDocTemplate)
		return FALSE;

	/* Добавяне новосъздадената инстанция на CSubscribersDoc към темплейта */
	pDocTemplate->AddDocument(poSubscribersDoc);
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMultiDocTemplate(IDR_SUBSCRIBER_PHONE_NUMBERS_TYPE,
		RUNTIME_CLASS(CSubscriberPhoneNumbersDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSubscriberPhoneNumbersView));

	if (!pDocTemplate)
		return FALSE;

	/* Добавяне новосъздадената инстанция на CSubscriberPhoneNumbersDoc към темплейта */
	pDocTemplate->AddDocument(poSubscrPhnNmbDoc);
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CPhoneBookApp::ExitInstance()
{	
	return CWinApp::ExitInstance();
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);		// DDX/DDV support

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
	/* Създаване на свързан списък от указатели към съществуващите CDocTemplate обекти */
	CPtrList oTemplateList;
	
	POSITION pDocTemplPos = AfxGetApp()->m_pDocManager->GetFirstDocTemplatePosition();
	
	while(pDocTemplPos){
		CDocTemplate *poDocTemplate	= AfxGetApp()->m_pDocManager->GetNextDocTemplate(pDocTemplPos);
		oTemplateList.AddHead(poDocTemplate);
	}
			
	CNewDocDlg dlg(&oTemplateList);
	if(IDOK != dlg.DoModal())
		return;

	/* Взимане на CDocTemplate-a, който трябва да се ползва за създаване на желаният от потребиителят документ */
	CDocTemplate *pSelectedDocTemplate = dlg.GetSelectedDoc();
	if(!pSelectedDocTemplate)
		return;

	/* Във всеки CDocTemplate трябва да се съдържа само една единствена инстанция на 
		 CDocument - тази която е създадена и добавена във InitInstance */
	POSITION oDocPos = pSelectedDocTemplate->GetFirstDocPosition();
	ASSERT(oDocPos != 0);
	CDocument* poSelectedDoc =	pSelectedDocTemplate->GetNextDoc(oDocPos);

	/* Създаване на рамка за новото CView и инициализирането му */
	CFrameWnd* pFrame = pSelectedDocTemplate->CreateNewFrame(poSelectedDoc, NULL);
	pSelectedDocTemplate->InitialUpdateFrame(pFrame, poSelectedDoc);
}



// CPhoneBookApp message handlers

