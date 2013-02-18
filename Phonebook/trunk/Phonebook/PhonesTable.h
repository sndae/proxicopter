#pragma once
#include "PhonebookRecSet.h"

class CPhonesTable :
  public CPhonebookRecSet
{
public:
  CPhonesTable(CDatabase &cDatabase);
  ~CPhonesTable(void);
};
