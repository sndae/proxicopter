// SortButton.cpp : implementation file
//

#include "stdafx.h"
#include "Phonebook.h"
#include "SortButton.h"


// CSortButton

IMPLEMENT_DYNAMIC(CSortButton, CButton)

CSortButton::CSortButton()
{
  eCurrSortType = CDbTableInterface::eDesc;
}

CSortButton::~CSortButton()
{
}


BEGIN_MESSAGE_MAP(CSortButton, CButton)
END_MESSAGE_MAP()



// CSortButton message handlers


