#include"IT.h"
#include "Error.h"
#include"stdafx.h"


namespace IT
{
	IdTable Create(int size)
	{
		IdTable* tabl = new IdTable;
		if (size > TI_MAXSIZE)
		{
			throw ERROR_THROW(116);
		}
		tabl->maxsize = size;
		tabl->size = 0;
		tabl->table = new Entry[size];
		return *tabl;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		bool ident = false;
		if (idtable.size + 1 > idtable.maxsize)
		{
			throw ERROR_THROW(117);
		}
		/*for (int i = 0; i < idtable.size - 1; i++)
		{
			if (strcmp(entry.id,idtable.table[i].id))
			{
				if (entry.iddatatype == idtable.table[i].iddatatype)
				{
					if (entry.idtype == idtable.table[i].idtype)
					{
						throw ERROR_THROW(105);
					}
				}
			}
		}*/
		idtable.table[idtable.size] = entry;
		idtable.size += 1;
	}
	Entry GetEntry(IdTable& idtable, int n)
	{
		return idtable.table[n];
	}
	int search(IdTable& idtable, IT::Entry entry)
	{
		if (entry.idtype == IT::L)
		{
			if (entry.iddatatype == IT::BOOL)
				for (int i = 0; i <= idtable.size; i++)
				{
					if (entry.value.vint == idtable.table[i].value.vint && idtable.table[i].iddatatype==IT::BOOL)
						return i;
				}
			if(entry.iddatatype==IT::INT)
			for (int i = 0; i <= idtable.size; i++)
			{
				if (entry.value.vint == idtable.table[i].value.vint && idtable.table[i].iddatatype != IT::BOOL &&  idtable.table[i].idtype ==IT::L && idtable.table[i].iddatatype!=IT::STR) {
					return i;
				}
			}
			if(entry.iddatatype=IT::STR)
				for (int i = 0; i <= idtable.size; i++)
				{
					if (strcmp(entry.value.vstr->str, idtable.table[i].value.vstr->str))
						return i;
				}
			return -1;
		}
	for (int i = 0; i <= idtable.size; i++)
		{
		if (strcmp(entry.id, idtable.table[i].id) == NULL && (entry.scope==idtable.table[i].scope||idtable.table[i].scope==NULL))
		{
			return i;
		}
		else if (strcmp(entry.id, idtable.table[i].id) == NULL && idtable.table[i].idtype == IT::F)
		{
			return i;
		}
		else
			continue;
		}
		return -1;
	}
	int IsId(IdTable& idtable, char id[ID_MAXSIZE * 2])
	{
		int n = 0;
		bool flag = false;
		while (n < idtable.size - 1)
		{
			if (idtable.table[n].id == id)
			{
				flag = true;
				break;
			}
			n += 1;
		}
		if (flag)
			return n + 1;
		else
			return TI_NULLIDX;
	}
}