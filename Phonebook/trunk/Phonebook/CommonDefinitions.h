#pragma once
#include "AfxTempl.h"

enum eMenuCmd{eCmdUpdate = 0, eCmdInsert, eCmdDelete, eCmdFind};

#define TABLE_HEADER \
  int   m_iId;       \
  int   m_iRevNumb;  \

template <class ROW_TYPE> class CRowsPtrArray: public CTypedPtrArray<CPtrArray, ROW_TYPE*>
{
public:
  ~CRowsPtrArray(void)
  {
    RemoveAndFreeAll();
  };
  void RemoveAndFreeAll()
  {
    for(int i = 0; i < GetCount(); i++)
    {
      delete GetAt(i);
    }
    RemoveAll();
  };
};