#include "CitiesTable.h"

CCitiesTable::CCitiesTable(CDatabase &cDatabase):
CPhonebookRecSet(&cDatabase)
{
  LoadDB(_T("cities"), 0, 0);
}

CCitiesTable::~CCitiesTable(void)
{
}

TCHAR *CCitiesTable::GetCurrAttrName()
{
  return 0;
}


