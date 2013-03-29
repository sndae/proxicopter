#pragma once
#include "AfxTempl.h"

/* общи членове на всички таблици */
#define TABLE_HEADER \
  int   m_iId;       \
  int   m_iRevNumb;  \

/* Изброяване на общи за всички команди операции, както и техните имена */
enum eMenuCmd{eCmdUpdate = 0, eCmdInsert, eCmdDelete, eCmdFind};

#define MENU_CMD_DELETE _T("Изтрий")
#define MENU_CMD_INSERT _T("Вмъкни")
#define MENU_CMD_UPDATE _T("Редактирай")
#define MENU_CMD_FIND   _T("Търси")

/* Don't care стойност */
#define DNC (-1)

/* Обвивка на стандартният динамичен масив от указатели, извършващ и освобождаване на
   динамично заетата памет стояща зад тях, при унищожаване на масива */
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