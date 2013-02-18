#include "stdafx.h"
#include "CitiesTable.h"
#include "PhonebookDBException.h"

CCitiesTable::CCitiesTable(CDatabase &cDatabase):
CPhonebookRecSet(&cDatabase)
{
  CDispnameToAttrname a_tDispToAttrName[] = 
  {
    CDispnameToAttrname(_T("Код на град"), _T("code")),
    CDispnameToAttrname(_T("Град"),        _T("name")),
    CDispnameToAttrname(_T("Област"),      _T("area")),
    CDispnameToAttrname(_T(""),            _T("")),
  };
  if(LoadDB(CDispnameToAttrname(_T("Градове"), _T("phonebook.dbo.cities")), &a_tDispToAttrName[0], 0) != TRUE)
  {
    throw CPhoneBookDBException(_T("Unable to load 'city' table"));
  }
}

CCitiesTable::~CCitiesTable(void)
{
}





