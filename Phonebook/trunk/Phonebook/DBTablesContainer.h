#pragma once

#include "DBTableInterface.h"


class CDBTablesContainer
{
  int iTablesCounter;
public:
  CDbTableInterface *GetFirstTable(void);
  CDbTableInterface *GetNextTable(void);
  CDBTablesContainer(void);
  ~CDBTablesContainer(void);
};
