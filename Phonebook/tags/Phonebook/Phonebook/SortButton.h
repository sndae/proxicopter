#pragma once
#include "DBTableInterface.h"

// CSortButton

class CSortButton : public CButton
{
	DECLARE_DYNAMIC(CSortButton)
 
public:
	CSortButton();
	virtual ~CSortButton();
  void InvertSortType(){eCurrSortType == CDbTableInterface::eAsc ? eCurrSortType = CDbTableInterface::eDesc : eCurrSortType = CDbTableInterface::eAsc; }
  CDbTableInterface::eSortType eCurrSortType;
protected:
	DECLARE_MESSAGE_MAP()
};


