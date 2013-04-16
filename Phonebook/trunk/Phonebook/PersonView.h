// PersonView.h : interface of the CPersonView class
//


#pragma once
#include "PersonDoc.h"

class CPersonView : public CListView
{
protected: // create from serialization only
	CPersonView();
	DECLARE_DYNCREATE(CPersonView)

// Attributes
public:

private:

// Operations
public:

// Overrides
public:

protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint);
// Implementation
public:
	virtual ~CPersonView();
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	void RecreateColumnsContent(CPersonDoc::eColumn eColumn = CPersonDoc::eColFirstName, const BOOL bResetFilter = TRUE);
	void RecreateColumnsContent(CPersonArray &oPersonsArr);
	void UpdateSingleRow(CPerson &oUpdPerson);
	void InsertNewRow(CPerson &oPerson);
	void UpdateRow(int iRowIdx, CSubscribers &oSubscriber, CCities &oCity, CSubscriberPhoneNumbers &oPhoneNumb);
	void ExecuteCntxMenuCmd(eMenuCmd eCmd);
	CPersonDoc* GetDocument() const;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

	// �������� ������ ��� �� ������� 
	int	 m_nCurrRowSelected;
 // ����� ������� ������ �� ��������� �� ����� ���� �� �������� 
	BOOL	m_abAscSorting[CPersonDoc::eCOL_NUMB];
	// ����� �� ��������� ��� ����� �� ����� ��� �� ������. ��������� �, ��� ���� ID � rev_numb �� ����� 
	// ���, �� �� ������������. �.�. �� ������ �� �� ����������, � ��� ���������� � ������ �� �������� 
	CPersonArray m_PersonsArray;
};

#ifndef _DEBUG	// debug version in PersonView.cpp

#endif

#pragma once
