#include"SA.h"

namespace SA
{
	//проверка все переменные инициализируетс€ 
	//bool в while и if
	//должен быть main
	//сделать проверку на массив индекса 
	//проверку на типы функций
	//можно сделать проверку на выход за длину массива и строки
	//проверь что вообще в индекс кладЄтс€
	//сделать так чтобы нельз€ было измен€ть параметры
	vector<pair<string, bool>> vars;
	stack<IT::Entry*> stk;
	int column = 0;
	int countParms;
	bool flagMain = false;
	bool flagNotInit = false;
	bool parmFlag = false;
	bool addedFun = false;
	int buffer;
	void addVars(int i, LT::LexTable& lextable, IT::IdTable& idtable)
	{
		for (int j = 0; j < vars.size(); j++)
		{
			if (vars[j].first==string(idtable.table[lextable.table[i - 1].idxTI].id)+string(idtable.table[lextable.table[i - 1].idxTI].scope->id))
			{
				// ”становим второй элемент пары в true
				vars[j].second = true;
				break;
			}
		}
	}
	int checkIfWhile(int i, LT::LexTable& lextable, IT::IdTable& idtable)
	{
		buffer = i;
		while (lextable.table[i].lexema[0] != LEX_RIGHTTHESIS)
			i++;
		i--;
		if (lextable.table[i].lexema[0] != LEX_EQUAL && lextable.table[i].lexema[0] != LEX_MORE && lextable.table[i].lexema[0] != LEX_LESS &&
			lextable.table[i].lexema[0] != LEX_NE && lextable.table[i].lexema[0] != LEX_ME && lextable.table[i].lexema[0] != LEX_LE &&
			(idtable.table[lextable.table[i].idxTI].iddatatype != IT::BOOL))
		{
			throw ERROR_THROW_IN(122, lextable.table[i].sn, -1);
		}
		i = buffer;
		return i;
	}
	void addSizeToArray(int i, LT::LexTable& lextable, IT::IdTable& idtable)
	{
		if (idtable.table[lextable.table[i - 1].idxTI].value.vint > 128|| idtable.table[lextable.table[i - 1].idxTI].value.vint <0)
		{
			throw ERROR_THROW_IN(129,lextable.table[i].sn,-1)
		}
		idtable.table[lextable.table[i - 2].idxTI].value.vint = idtable.table[lextable.table[i-1].idxTI].value.vint;
	}
	void checkSizeofArray(int i, LT::LexTable& lextable, IT::IdTable& idtable)
	{
		int current_index = idtable.table[lextable.table[i - 1].idxTI].value.vint;
		int size = idtable.table[lextable.table[i - 2].idxTI].value.vint;
		if (current_index >= size)
		{
			throw ERROR_THROW_IN(124, lextable.table[i].sn, -1);
		}
	}
	void checkVars()
	{
		for (int i = 0; i < vars.size(); i++)
		{
			if (vars[i].second == false)
			{
				for (int j = 0; j < strlen(vars[i].first.c_str()); j++)
				{
					cout << vars[i].first[j];
				}
				cout << endl;
				flagNotInit = true;
			}
			if (flagNotInit)
				throw ERROR_THROW(123);
		}
	}
	void Semantic_Analyzer(LT::LexTable& lextable, IT::IdTable& idtable)
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (idtable.table[i].idtype == IT::V || idtable.table[i].idtype == IT::A)
			{
				vars.push_back(pair<string, bool>(string(idtable.table[i].id)+string(idtable.table[i].scope->id), false));
			}
		}
		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i - 1].sn != lextable.table[i].sn)
			{
				column = 0;
			}
			column++;
			if (lextable.table[i].lexema[0] == LEX_GIVE || lextable.table[i].lexema[0] == LEX_READ)
			{
				if (lextable.table[i - 1].lexema[0] == LEX_ID) {
					addVars(i, lextable, idtable);
				}
				if (lextable.table[i - 1].lexema[0] == LEX_INDEX)
				{
					addVars(i - 2, lextable, idtable);
				}
			}
			if (lextable.table[i].lexema[0] == LEX_INDEX)
			{
				if (lextable.table[i - 4].lexema[0] == LEX_ARRAY ||
					(lextable.table[i-3].lexema[0] == LEX_STRING && idtable.table[lextable.table[i - 2].idxTI].iddatatype==IT::STR))
					addSizeToArray(i, lextable, idtable);
				else
					checkSizeofArray(i, lextable, idtable);
			}
			if (lextable.table[i].lexema[0] == LEX_LEFTBRACE && lextable.table[i - 1].lexema[0] == LEX_MAIN)
			{
				stk.push(&idtable.table[lextable.table[i - 1].idxTI]);
				continue;
			}
			if (lextable.table[i].lexema[0] == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype == IT::F && lextable.table[i-2].lexema[0]==LEX_FUNCTION)
			{
				stk.push(&idtable.table[lextable.table[i].idxTI]);
				addedFun = true;
				continue;
			}
			if (lextable.table[i].lexema[0] == LEX_LEFTBRACE &&  parmFlag)
			{
				parmFlag = false;
				stk.push(stk.top());
				continue;
			}
			if (lextable.table[i].lexema[0] == LEX_LEFTBRACE)
			{
				if (addedFun)
				{
					addedFun = false;
					continue;
				}
				stk.push(stk.top());
				continue;
			}
			if (lextable.table[i].lexema[0] == LEX_BRACELET)
			{
				if(stk.empty())
					throw ERROR_THROW_IN(126, lextable.table[i].sn, -1);
				stk.pop();
			}
			if (lextable.table[i].lexema[0] == LEX_RETURN)
			{
				if (idtable.table[lextable.table[i - 1].idxTI].iddatatype == IT::BYTE && stk.top()->iddatatype == IT::INT)
					continue;
				if (idtable.table[lextable.table[i - 1].idxTI].iddatatype != stk.top()->iddatatype)
					throw ERROR_THROW_IN(125, lextable.table[i].sn, -1);
			}
			if (idtable.table[lextable.table[i].idxTI].idtype == IT::P && lextable.table[i - 1].lexema[0] == LEX_LEFTTHESIS && &idtable.table[lextable.table[i - 2].idxTI] == stk.top())
			{
				parmFlag = true;
			}
			if (idtable.table[lextable.table[i].idxTI].idtype == IT::P && !parmFlag && lextable.table[i + 1].lexema[0] == LEX_GIVE)
				throw ERROR_THROW_IN(127, lextable.table[i].sn, -1);
			if (idtable.table[lextable.table[i].idxTI].idtype == IT::P && !parmFlag && lextable.table[i + 1].lexema[0] == LEX_READ)
				throw ERROR_THROW_IN(128, lextable.table[i].sn, -1);
			if (lextable.table[i].lexema[0] == LEX_IF || lextable.table[i].lexema[0] == LEX_WHILE)
			{
				/*buffer = i;
				while (lextable.table[i].lexema[0] != LEX_RIGHTTHESIS)
					i++;
				i--;
				if (lextable.table[i].lexema[0] != LEX_EQUAL && lextable.table[i].lexema[0] != LEX_MORE && lextable.table[i].lexema[0] != LEX_LESS &&
					(idtable.table[lextable.table[i].idxTI].iddatatype != IT::BOOL))
				{
					throw ERROR_THROW_IN(122, lextable.table[i].sn, column);
				}*/
				i = checkIfWhile(i, lextable, idtable);
			}
			if (lextable.table[i].lexema[0] == LEX_MAIN)
			{
				if (flagMain)
					throw ERROR_THROW_IN(114, lextable.table[i].sn, -1);
				flagMain = true;
			}
			if (lextable.table[i].lexema[0] == LEX_GIVE &&
				(idtable.table[lextable.table[i - 1].idxTI].idtype == IT::P || idtable.table[lextable.table[i - 1].idxTI].idtype == IT::F))
			{
				throw ERROR_THROW_IN(127, lextable.table[i].sn, -1);
			}
			if (lextable.table[i].lexema[0] == LEX_READ &&
				(idtable.table[lextable.table[i - 1].idxTI].idtype == IT::P || idtable.table[lextable.table[i - 1].idxTI].idtype == IT::F))
			{
				throw ERROR_THROW_IN(128, lextable.table[i].sn, -1);
			}

			
		}

		checkVars();
		
		if (!stk.empty())
			throw ERROR_THROW(126);
	}
}
//int findMain(LT::LexTable& lextable)
//	{
//		int i = -1;
//		while (lextable.table[i].lexema[0] != LEX_MAIN)
//			i++;
//		return i;
//	}
//	int findFunction(LT::Entry entry, IT::IdTable& idtable)
//	{
//		return idtable.table[entry.idxTI].idxfirstLE;
//	}
//	stack<IT::IDDATATYPE> getParms(int f,IT::IdTable& idtable)
//	{
//		stack<IT::IDDATATYPE> params;
//		for (int i = 0; i < idtable.size; i++)
//		{
//			if (&idtable.table[f] == idtable.table[i].scope)
//			{
//				params.push(idtable.table[i].iddatatype);
//			}
//
//		}
//		return params;
//	}
//	void SA(LT::LexTable& lextable, IT::IdTable& idtable)
//	{
//		int column = 0;
//		stack<IT::IDDATATYPE> stk;
//		stack<IT::IDDATATYPE>parms;
//		IT::IDDATATYPE buffer1;
//		IT::IDDATATYPE buffer2;
//		std::stack<IT::IDDATATYPE> tempStack;
//		bool funcFlag = false;
//		IT::IDDATATYPE currentFunc;
//		for (int i = 0; i < lextable.size; i++)
//		{
//			if (lextable.table[i].sn != lextable.table[i - 1].sn)
//				column = 0;
//			if (lextable.table[i].lexema[0] == LEX_ID && lextable.table[i - 1].lexema[0] == LEX_FUNCTION)
//			{
//				while (lextable.table[i].lexema[0] == LEX_LEFTBRACE)
//				{
//					i++;
//				}
//				i++;
//				funcFlag = true;
//				currentFunc = idtable.table[lextable.table[i - 1].idxTI].iddatatype;
//			}
//			if ((lextable.table[i].lexema[0] == LEX_ID && lextable.table[i-1].lexema[0] != 't')|| lextable.table[i].lexema[i]==LEX_LITERAL)
//			{
//				stk.push(idtable.table[lextable.table[i].idxTI].iddatatype);
//			}
//			if (lextable.table[i].lexema[0] == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype == IT::F)
//			{
//				parms = getParms(lextable.table[i].idxTI, idtable);
//				while (parms.empty())
//				{
//					if (parms.top() == stk.top())
//					{
//						if(stk.empty())
//							throw ERROR_THROW_IN(120, lextable.table[i].sn, column);
//						parms.pop();
//						stk.pop();
//					}
//					else
//						throw ERROR_THROW_IN(121, lextable.table[i].sn, column);
//				}
//			
//			}
//			if (lextable.table[i].lexema[0] == LEX_PLUS ||
//				lextable.table[i].lexema[0] == LEX_MINUS ||
//				lextable.table[i].lexema[0] == LEX_STAR ||
//				lextable.table[i].lexema[0] == LEX_DIRSLASH
//				)
//			{
//				if (stk.empty())
//					throw ERROR_THROW_IN(120, lextable.table[i].sn, column);
//				if (stk.top() == IT::INT || stk.top() == IT::BYTE)
//					stk.pop();
//				else
//					throw ERROR_THROW_IN(124, lextable.table[i].sn, column);
//				if (stk.empty())
//					throw ERROR_THROW_IN(120, lextable.table[i].sn, column);
//				if (stk.top() == IT::INT || stk.top() == IT::BYTE)
//					stk.pop();
//				else
//					throw ERROR_THROW_IN(124, lextable.table[i].sn, column);
//			}
//			if (lextable.table[i].lexema[0] == LEX_DUP)
//			{
//				CHECK_STACK
//				buffer1 = stk.top();
//				stk.push(buffer1);
//			}
//			if (lextable.table[i].lexema[0] == LEX_DROP)
//			{
//				CHECK_STACK
//				stk.pop();
//			}
//			if (lextable.table[i].lexema[0] == LEX_SWAP)
//			{
//				if(stk.size()<2)
//					throw ERROR_THROW_IN(120, lextable.table[i].sn, column);
//				buffer1 = stk.top();
//				stk.pop();
//				buffer2 = stk.top();
//				stk.pop();
//				stk.push(buffer1);
//				stk.push(buffer2);
//			}
//			if (lextable.table[i].lexema[0] == LEX_OVER)
//			{
//				if (stk.size() < 2)
//					throw ERROR_THROW_IN(120, lextable.table[i].sn, column);
//				buffer1 = stk.top();
//				stk.pop();
//				buffer2 = stk.top();
//				stk.push(buffer1);
//				stk.push(buffer2);
//			}
//			if (lextable.table[i].lexema[0] == LEX_ROT)
//			{
//				if (stk.empty()) {
//					// ≈сли стек пуст, сдвиг не имеет смысла
//					return;
//				}
//
//				// ѕереносим все элементы из исходного стека во временный стек
//				while (!stk.empty()) {
//					tempStack.push(stk.top());
//					stk.pop();
//				}
//
//				// ѕереносим все элементы из временного стека обратно в исходный стек
//				while (!tempStack.empty()) {
//					stk.push(tempStack.top());
//					tempStack.pop();
//				}
//			}
//			if (lextable.table[i].lexema[0] == LEX_DEPTH)
//				stk.push(IT::INT);
//			if (lextable.table[i].lexema[0] == LEX_CLEAR)
//			{
//				while (!stk.empty())
//					stk.pop();
//			}
//			/*if(lextable.table[i].lexema[0]==LEX_
// )
//				if(stk.top()!=IT::INT||stk.top()!=IT::BYTE)
//					throw ERROR_THROW_IN(124, lextable.table[i].sn, column);
//			if (lextable.table[i].lexema[0] == LEX_ROLL)
//				if (stk.top() != IT::INT || stk.top() != IT::BYTE)
//					throw ERROR_THROW_IN(124, lextable.table[i].sn, column);*/
//			if (lextable.table[i].lexema[0] == LEX_BRACELET)
//			{
//				if (stk.top() != currentFunc)
//					throw ERROR_THROW_IN(123, lextable.table[i].sn, column);
//				while (!stk.empty())
//					stk.pop();
//			}
//		}
//	}