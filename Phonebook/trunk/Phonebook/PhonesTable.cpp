#include "StdAfx.h"
#include "PhonesTable.h"
#include "PhonebookDBException.h"

CPhonesTable::CPhonesTable(CDatabase &cDatabase)
:CPhonebookRecSet(&cDatabase)
{
  CDispnameToAttrname a_tDispToAttrName[] = 
  {
    CDispnameToAttrname(_T("Код на тип телефон"), _T("code")),
    CDispnameToAttrname(_T("Тип телефон"),        _T("phone_type")),
    CDispnameToAttrname(_T(""),            _T("")),
  };
  if(LoadDB(CDispnameToAttrname(_T("Типове телефони"), _T("phonebook.dbo.phones")), &a_tDispToAttrName[0], 0) != TRUE)
  {
    throw CPhoneBookDBException(_T("Unable to load 'phones' table"));
  }
}

CPhonesTable::~CPhonesTable(void)
{
}
