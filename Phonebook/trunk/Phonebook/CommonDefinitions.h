#pragma once
#include "AfxTempl.h"

// общи членове на всички таблици 
#define TABLE_HEADER	\
	int	 m_nId;			\
	int	 m_nRevNumb;	\

// Изброяване на общи за всички команди операции, както и техните имена 
enum eMenuCmd{eCmdUpdate = 0, eCmdInsert, eCmdDelete, eCmdFind, eCmdInsertSubscr, eCmdInsertNumb, eCmdDelSubscr, eCmdDelNumb};

#define MENU_CMD_DELETE				_T("Изтрий")
#define MENU_CMD_INSERT				_T("Вмъкни")
#define MENU_CMD_UPDATE				_T("Редактирай")
#define MENU_CMD_FIND				_T("Търси")
#define MENU_CMD_INSERT_SUBSCRIBER	_T("Вмъкни нов абонат")
#define MENU_CMD_INSERT_NUMBER		_T("Вмъкни нов номер")
#define MENU_CMD_DELETE_SUBSCRIBER	_T("Изтрий нов абонат")
#define MENU_CMD_DELETE_NUMBER		_T("Изтрий нов номер")


// Don't care стойност 
#define DNC (-1)
#define EMPTY_STRING	_T("")
// Обвивка на стандартният динамичен масив от указатели, извършващ и освобождаване на
//	динамично заетата памет стояща зад тях, при унищожаване на масива 
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

class CPhoneBookErr
{
public:
	enum eErrorType{eGenError = 0, eDBWriteFailed, eDBWReadFailed};
	static void IndicateUser(eErrorType eErr)
	{
		switch(eErr)
		{
		case eGenError:
			MessageBox(0, _T("Грешка в базата данни"), 0, MB_OK|MB_ICONWARNING);
			break;
		case eDBWReadFailed:
			MessageBox(0, _T("Грешка при четене"), 0, MB_OK|MB_ICONWARNING);
			break;
		case eDBWriteFailed:
			MessageBox(0, _T("Грешка при запис.\nВалидарайте записа или го опреснете"), 0, MB_OK|MB_ICONWARNING);
			break;
		}
	};
};