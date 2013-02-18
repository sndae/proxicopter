#pragma once
#include "PhonebookRecSet.h"

class CCitiesTable :
  public  CPhonebookRecSet
{
public:
  CCitiesTable(CDatabase &cDatabase);
  ~CCitiesTable(void);
};
