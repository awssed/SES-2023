#include"LA.h"
#include"stdafx.h"
#include"In.h"
#include"Error.h"
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <vector>

//добавить литералы массивы 
//сделать глобальную область видимости для литералов
//if в ife

namespace LA
{
	
	int countElements(char** arr) {
		int count = 0;
		while (arr != NULL) {
			count++;
			arr++;
		}
		return count;
	};
	LT::LexTable __LexTable = LT::Create(LT_MAXSIZE - 1);
	IT::IdTable __IdTable = IT::Create(TI_MAXSIZE - 1);
	bool stringFlag = false;
	bool byteFlag = false;
	bool boolFlag = false;
	bool falseFlag = false;
	bool trueFlag = false;
	bool literalFlag = false;
	bool intFlag = false;
	char* str = new char[MAX_LEX_SIZE];
	bool declareFlag = false;
	
	void Add_LT(int line, char token)
	{
		LT::Entry entry;
		entry.sn = line;
		memset(entry.lexema, '\0', strlen(entry.lexema) - 1);
		entry.lexema[0] = token;
		LT::Add(__LexTable, entry);
	}
	char FST()
	{
		FST_INT
		FST_BYTE
		FST_BOOL
		FST_STRING
		FST_ARRAY
		FST_FUNC
		FST_RETURN
		FST_MAIN
		FST_LITERAL
		FST_IDENF
		FST_WRITE
		FST_WRITELINE
		FST_READ
		FST_TRUE
		FST_FALSE
		FST_WHILE
		FST_IF
		FST_DUP
		FST_DROP
		FST_SWAP
		FST_OVER
		FST_DEPTH
		FST_CLEAR
		if (FST::Execute(_int))
		{
			intFlag = true;
			return LEX_INTEGER;
		}
		if (FST::Execute(_byte)) 
		{
			byteFlag = true;
			return LEX_BYTE;
		}
		if (FST::Execute(_bool))
		{
			boolFlag = true;
			return LEX_BOOL;
		}
		if (FST::Execute(_string))
		{
			stringFlag = true;
			return LEX_STRING;
		}
		if (FST::Execute(_array))
			return LEX_ARRAY;
		if (FST::Execute(_write))
		{
			return LEX_WRITE;
		}
		if (FST::Execute(_writeline))
		{
			return LEX_WRITELINE;
		}
		if (FST::Execute(_read))
		{
			return LEX_READ;
		}
		if (FST::Execute(_true))
		{
			trueFlag = true;
			return LEX_LITERAL;
		}
		if (FST::Execute(_false))
		{
			falseFlag = true;
			return LEX_LITERAL;
		}
		if (FST::Execute(_while))
		{
			return LEX_WHILE;
		}
		if (FST::Execute(_if))
		{
			return LEX_IF;
		}
		if (FST::Execute(_dup))
		{
			return LEX_DUP;
		}
		if (FST::Execute(_drop))
		{
			return LEX_DROP;
		}
		if (FST::Execute(_swap))
		{
			return LEX_SWAP;
		}
		if (FST::Execute(_over))
		{
			return LEX_OVER;
		}
		if (FST::Execute(_depth))
		{
			return LEX_DEPTH;
		}
		if (FST::Execute(_clear))
		{
			return LEX_CLEAR;
		}
		if (FST::Execute(_function))
			return LEX_FUNCTION;
		if (FST::Execute(_return))
			return LEX_RETURN;
		if (FST::Execute(_main))
		{
			return LEX_MAIN;
		}
		if (FST::Execute(literal_int))
			return LEX_LITERAL;
		if (FST::Execute(idenf))
			return LEX_ID;
		return NULL;
	}
	bool isCharacterInVector(const std::vector<char>& charVector, char character) {
		return std::find(charVector.begin(), charVector.end(), character) != charVector.end();
	}
	LEX LA(Parm::PARM parm,In::IN in,PreProc::lib libraries)
	{
		LEX lexResult;
		int indexIT;
		int col=0;
		int countParms = 0;
		setlocale(LC_ALL, "rus");
		LT::Entry current_entry_LT;
		int bufferIndex = 0;
		current_entry_LT.sn = 0;
		current_entry_LT.idxTI = 0;
		current_entry_LT.lexema[0] = NULL;
		std::stack<IT::Entry*> scope;
		std::vector<char> separators = { ' ','[',']',',','(',')','{','}','$','+','-','*','/','\'','>','<','=','|','\t'};
		scope.push(NULL);
		int number_literal = 0;
		bool addedToITFlag = false;
		bool declareFunctionflag = false;
		bool IndexFlag = true;
		IT::Entry current_entry_IT;
		__LexTable.size = 0;
		int currentLine = 1;
		std::ofstream LT_file;
		std::ofstream IT_file;
		LT_file.open("LT.txt");
		IT_file.open("IT.txt");
		
		for(int i=0;i<libraries.size;i++)
		{
			if (!std::strcmp(libraries.libraries[i].c_str(), " math.lib"))
			{
				MATH_LIB;
			}
			if (!std::strcmp(libraries.libraries[i].c_str(), " string.lib"))
			{
				STRING_LIB;
			}
		}
		for (int i = 0; i < in.size; i++)
		{
			col++;
			if (!isCharacterInVector(separators,in.text[i])||(literalFlag))
			{
					str[bufferIndex] = in.text[i];
					bufferIndex++;
					if (bufferIndex >= MAX_LEX_SIZE)
					{
						throw ERROR_THROW(119);
					}
			}else
			{
				str[bufferIndex ] = '\0';
				current_entry_LT.lexema[0] = FST();
				if (current_entry_LT.lexema[0] == LEX_MAIN)
				{
					current_entry_LT.idxTI = __IdTable.size;
					memcpy(current_entry_IT.id, str, 10);
					current_entry_IT.id[11] = '\0';
					current_entry_IT.iddatatype = IT::INT;
					current_entry_IT.idtype = IT::F;
					current_entry_IT.value.vint = NULL;
					current_entry_IT.idxfirstLE = currentLine;
					current_entry_IT.scope = NULL;
					indexIT = IT::search(__IdTable, current_entry_IT);
					if (indexIT >= 0)
					{
						throw ERROR_THROW_IN(114,currentLine,col);
					}
					if (indexIT == -1)
					{
						current_entry_LT.idxTI = __IdTable.size;
						IT::Add(__IdTable, current_entry_IT);
					}
				}
				if (current_entry_LT.lexema[0] == LEX_LITERAL)
				{
					current_entry_IT.idtype = IT::L;
					current_entry_IT.iddatatype = IT::INT;
					if (in.text[i - strlen(str) - 1] == LEX_MINUS && in.text[i-strlen(str)] != ' ')
					{
						current_entry_IT.value.vint = -atoi(str);
						if(str[0]=='0')
							current_entry_IT.value.vint = -stoi(str,nullptr,8);
						__LexTable.size--;
					}
					else
					{
						current_entry_IT.value.vint = atoi(str);
						if (str[0] == '0')
							current_entry_IT.value.vint = stoi(str, nullptr, 8);
					}
					if (trueFlag)
					{
						current_entry_IT.iddatatype = IT::BOOL;
						current_entry_IT.value.vint = 1;
					}
					if (falseFlag)
					{
						current_entry_IT.iddatatype = IT::BOOL;
						current_entry_IT.value.vint = 0;
					}
					
					indexIT = IT::search(__IdTable, current_entry_IT);
					if (indexIT > 0)
					{
						current_entry_LT.idxTI = indexIT;
						trueFlag = false;
						falseFlag = false;
					}
					else {
						sprintf_s(current_entry_IT.id, "L%d", number_literal);
						if (current_entry_IT.value.vint<127 && current_entry_IT.value.vint>-128)
							current_entry_IT.iddatatype = IT::BYTE;
						else
							current_entry_IT.iddatatype = IT::INT;
						if (trueFlag)
						{
							strcpy_s(current_entry_IT.id, "true");
							current_entry_IT.iddatatype = IT::BOOL;
							current_entry_IT.value.vint = 1;
							trueFlag = false;
						}
						if (falseFlag)
						{
							strcpy_s(current_entry_IT.id, "false");
							current_entry_IT.iddatatype = IT::BOOL;
							current_entry_IT.value.vint = 0;
							falseFlag = false;
						}
						current_entry_IT.idxfirstLE = currentLine;
						current_entry_IT.scope = scope.top();
						current_entry_LT.idxTI = __IdTable.size;
						IT::Add(__IdTable, current_entry_IT);
						number_literal++;
					}
				}
				if (current_entry_LT.lexema[0] == LEX_ID)
				{
					if (scope.empty())
						current_entry_IT.scope = NULL;
					else
					current_entry_IT.scope = scope.top();
					current_entry_LT.idxTI = __IdTable.size;
					memcpy(current_entry_IT.id, str, 10);
					current_entry_IT.id[10] = '\0';
					current_entry_IT.iddatatype = IT::INT;
					current_entry_IT.value.vint = NULL;
					current_entry_IT.idxfirstLE = currentLine;
					current_entry_IT.idtype = IT::V;
					if (__LexTable.table[__LexTable.size - 2].lexema[0] == LEX_FUNCTION)
					{
						current_entry_IT.idtype = IT::F;
						declareFunctionflag = true;
						if (intFlag)
						{
							current_entry_IT.iddatatype = IT::INT;
							intFlag = false;
						}
						if (byteFlag) 
						{
							current_entry_IT.iddatatype = IT::BYTE;
							byteFlag = false;
						}
						if (stringFlag)
						{
							current_entry_IT.iddatatype = IT::STR;
							stringFlag = false;
						}
						if (boolFlag)
						{
							current_entry_IT.iddatatype = IT::BOOL;
							boolFlag = false;
						}
						indexIT = IT::search(__IdTable, current_entry_IT);
						if (indexIT >= 0)
						{
							throw ERROR_THROW_IN(114, currentLine, col);
						}
						if (indexIT == -1)
						{

							current_entry_LT.idxTI = __IdTable.size;
							IT::Add(__IdTable, current_entry_IT);
							addedToITFlag = true;
						}
					}
					if (__LexTable.table[__LexTable.size - 1].lexema[0] == LEX_INTEGER && intFlag && !declareFunctionflag)
					{
						strcpy_s(current_entry_IT.value.vstr->str, "");
						indexIT = IT::search(__IdTable, current_entry_IT);
						if (indexIT >= 0)
						{
							throw ERROR_THROW_IN(114, currentLine, col);
						}
						if (__LexTable.table[__LexTable.size - 2].lexema[0] == LEX_ARRAY)
						{
							current_entry_IT.idtype = IT::A;
						}
						IT::Add(__IdTable, current_entry_IT);
						addedToITFlag = true;
						intFlag = false;
					}
					if (__LexTable.table[__LexTable.size - 1].lexema[0] == LEX_BYTE && byteFlag && !declareFunctionflag)
					{
						current_entry_IT.iddatatype = IT::BYTE;
						strcpy_s(current_entry_IT.value.vstr->str, "");
						indexIT = IT::search(__IdTable, current_entry_IT);
						if (indexIT >= 0)
						{
							throw ERROR_THROW_IN(114, currentLine, col);
						}
						if (__LexTable.table[__LexTable.size - 2].lexema[0] == LEX_ARRAY)
						{
							current_entry_IT.idtype = IT::A;
						}
						IT::Add(__IdTable, current_entry_IT);
						byteFlag = false;
						addedToITFlag = true;
					}
					if (__LexTable.table[__LexTable.size - 1].lexema[0] == LEX_BOOL && boolFlag && !declareFunctionflag)
					{
						current_entry_IT.iddatatype = IT::BOOL;
						strcpy_s(current_entry_IT.value.vstr->str, "");
						indexIT = IT::search(__IdTable, current_entry_IT);
						if (indexIT >= 0)
						{
							throw ERROR_THROW_IN(114, currentLine, col);
						}
						if (__LexTable.table[__LexTable.size - 2].lexema[0] == LEX_ARRAY)
						{
							current_entry_IT.idtype = IT::A;
						}
						IT::Add(__IdTable, current_entry_IT);
						boolFlag = false;
						addedToITFlag = true;
					}
					if (__LexTable.table[__LexTable.size - 1].lexema[0] == LEX_STRING && stringFlag && !declareFunctionflag)
					{
						current_entry_IT.iddatatype = IT::STR;
						current_entry_IT.value.vint = 1;
						strcpy_s(current_entry_IT.value.vstr->str, "");
						indexIT = IT::search(__IdTable, current_entry_IT);
						if (indexIT >= 0)
						{
							throw ERROR_THROW_IN(114, currentLine, col);
						}
						IT::Add(__IdTable, current_entry_IT);
						stringFlag = false;
						addedToITFlag = true;
					}
					if (__LexTable.table[__LexTable.size - 2].lexema[0] == LEX_LEFTTHESIS &&
						__LexTable.table[__LexTable.size - 3].lexema[0] == LEX_ID &&
						__LexTable.table[__LexTable.size - 3].idxTI == __IdTable.size - 1 &&
						__IdTable.table[__IdTable.size-1].idtype==IT::F)
					{
						current_entry_IT.idtype = IT::P;
						if (__LexTable.table[__LexTable.size-1].lexema[0] == LEX_STRING && stringFlag)//был убран declereFunction
						{
							current_entry_IT.iddatatype = IT::STR;
							strcpy_s(current_entry_IT.value.vstr->str, "");
							stringFlag = false;
						}
						if(__LexTable.table[__LexTable.size - 1].lexema[0] == LEX_BYTE && byteFlag)
						{
							current_entry_IT.iddatatype = IT::BYTE;
							strcpy_s(current_entry_IT.value.vstr->str, "");
							byteFlag = false;
						}
						indexIT = IT::search(__IdTable, current_entry_IT);
						if (indexIT >= 0)
						{
							throw ERROR_THROW_IN(114, currentLine, col);
						}
						current_entry_LT.idxTI = __IdTable.size;
						IT::Add(__IdTable, current_entry_IT);
						addedToITFlag = true;
						intFlag = false;
						byteFlag - false;
						boolFlag = false;
						stringFlag = false;
					}
					if(__LexTable.table[__LexTable.size-2].lexema[0]==LEX_COMMA && __IdTable.table[__LexTable.table[__LexTable.size-2].idxTI].idtype==IT::P)
					{
						current_entry_IT.idtype = IT::P;
						countParms++;
						if (countParms > 8)
						{
							throw ERROR_THROW_IN(120, currentLine, col);
						}
						if (__LexTable.table[__LexTable.size - 1].lexema[0] == LEX_STRING && stringFlag)
						{
							current_entry_IT.iddatatype = IT::STR;
							strcpy_s(current_entry_IT.value.vstr->str, "");
							stringFlag = false;
						}
						indexIT = IT::search(__IdTable, current_entry_IT);
						if (indexIT >= 0)
						{
							throw ERROR_THROW_IN(114, currentLine, col);
						}
						IT::Add(__IdTable, current_entry_IT);
						addedToITFlag = true;
						intFlag = false;
						byteFlag - false;
						boolFlag = false;
						stringFlag = false;
					}
					//тут должна быть ещё проверка на параметр
					if (!addedToITFlag) 
					{
						indexIT = IT::search(__IdTable, current_entry_IT);
						if (indexIT < 0)
						{
							throw ERROR_THROW_IN(115, currentLine, col);
						}
						current_entry_LT.idxTI = indexIT;
					}
					std::memset(current_entry_IT.id, NULL, 10);
					current_entry_IT.iddatatype = IT::INT;
					current_entry_IT.value.vint = NULL;
					addedToITFlag = false;
				}
				if (current_entry_LT.lexema[0] == NULL && str[0] != '\0' &&( isCharacterInVector(separators, str[0]) || (!literalFlag)))
				{
					throw ERROR_THROW_IN(113, currentLine, col);
				}
				bufferIndex = 0;
				std::memset(str, NULL, bufferIndex + 1);
			}
			if (current_entry_LT.lexema[0]!=NULL)
			{
				current_entry_LT.sn = currentLine;
				LT::Add(__LexTable, current_entry_LT);
				current_entry_LT.lexema[0] = NULL;

			}
			if (literalFlag && in.text[i] != '\'')
				continue;
			switch (in.text[i])
			{
			case MARK:
				literalFlag = true;
				if (str[0] == '\'' && bufferIndex!=1)
				{
					current_entry_LT.idxTI = __IdTable.size;
					str[bufferIndex] = '\0';
					literalFlag = false;
					current_entry_LT.lexema[0] = LEX_LITERAL;
					number_literal++;
					sprintf_s(current_entry_IT.id, "L%d", number_literal);
					current_entry_IT.iddatatype = IT::STR;
					current_entry_IT.idtype = IT::L;
					current_entry_IT.idxfirstLE = currentLine;
					for (int i = 0; i < strlen(str); i++)
					{
						current_entry_IT.value.vstr->str[i] = str[i];
					}
					current_entry_IT.value.vstr->str[strlen(str)] = '\0';
					current_entry_IT.value.vstr->len = strlen(current_entry_IT.value.vstr->str);
					current_entry_LT.sn = currentLine;
					if (!scope.empty())
						current_entry_IT.scope = scope.top();
					else
						current_entry_IT.scope = NULL;
					number_literal++;
					LT::Add(__LexTable, current_entry_LT);
					IT::Add(__IdTable, current_entry_IT);
					memset(str, 0, strlen(str));
					current_entry_LT.lexema[0] = NULL;
					break;
				}
				str[bufferIndex] = MARK;
				bufferIndex++;
				break;
			case NEW_LINE:
				currentLine++;
				col = 0;
				current_entry_LT.lexema[0] = NULL;	
				break;
			case SEMICOLON:
				current_entry_LT.lexema[0] = LEX_SEMICOLON;
				current_entry_LT.sn = currentLine;
				LT::Add(__LexTable, current_entry_LT);
				current_entry_LT.lexema[0] = NULL;
				break;
			case COMMA:
				current_entry_LT.lexema[0] = LEX_COMMA;
				current_entry_LT.sn = currentLine;
				LT::Add(__LexTable, current_entry_LT);
				current_entry_LT.lexema[0] = NULL;
				break;
			case LEFT_BRACE:
				current_entry_LT.lexema[0] = LEX_LEFTBRACE;
				current_entry_LT.sn = currentLine;
				LT::Add(__LexTable, current_entry_LT);
				current_entry_LT.lexema[0] = NULL;
				for (int j = __IdTable.size-1 ; j >= 0; j--)
				{
					if (__IdTable.table[j].idtype == IT::F)
					{
						scope.push(&__IdTable.table[j]);
						break;
					}
				}
				break;
			case RIGHT_BRACE:
				current_entry_LT.lexema[0] = LEX_BRACELET;
				current_entry_LT.sn = currentLine;
				LT::Add(__LexTable, current_entry_LT);
				current_entry_LT.lexema[0] = NULL;
				if (!scope.empty())
					scope.pop();
				break;
			case LEFTTHESIS:
				current_entry_LT.lexema[0] = LEX_LEFTTHESIS;
				current_entry_LT.sn = currentLine;
				LT::Add(__LexTable, current_entry_LT);
				current_entry_LT.lexema[0] = NULL;
				if (declareFunctionflag) 
				{
					for (int j = __IdTable.size - 1; j >= 0; j--)
					{
						if (__IdTable.table[j].idtype == IT::F)
						{
							scope.push(&__IdTable.table[j]);//область видимости не должна открываться в вызове самой функции
							countParms = 1;
							break;
						}
					}
				}
				break;
			case RIGHTTHESIS:
				current_entry_LT.lexema[0] = LEX_RIGHTTHESIS;
				current_entry_LT.sn = currentLine;
				LT::Add(__LexTable, current_entry_LT);
				current_entry_LT.lexema[0] = NULL;
				if (!scope.empty() && declareFunctionflag)
				{
					scope.pop();
					declareFunctionflag = false;
				}
				break;
			case PLUS:
				current_entry_LT.lexema[0] = LEX_PLUS;
				current_entry_LT.sn = currentLine;
				LT::Add(__LexTable, current_entry_LT);
				current_entry_LT.lexema[0] = NULL;
				break;
			case MINUS:
				current_entry_LT.lexema[0] = LEX_MINUS;
				LT::Add(__LexTable, current_entry_LT);
				current_entry_LT.lexema[0] = NULL;
				break;
			case STAR:
				current_entry_LT.lexema[0] = LEX_STAR;
				current_entry_LT.sn = currentLine;
				LT::Add(__LexTable, current_entry_LT);
				current_entry_LT.lexema[0] = NULL;
				break;
			case DIRSLASH:
				current_entry_LT.lexema[0] = LEX_DIRSLASH;
				current_entry_LT.sn = currentLine;
				LT::Add(__LexTable, current_entry_LT);
				current_entry_LT.lexema[0] = NULL;
				break;
			case LEX_NOT:
				if (in.text[i + 1] == LEX_EQUAL)
				{
					current_entry_LT.lexema[0] = LEX_NE;
					i++;
					current_entry_LT.sn = currentLine;
					LT::Add(__LexTable, current_entry_LT);
					current_entry_LT.lexema[0] = NULL;
					break;
				}
				else
				{
					throw ERROR_THROW_IN(601, currentLine, col);
				}
			case EQUAL:
				current_entry_LT.lexema[0] = LEX_EQUAL;
				current_entry_LT.sn = currentLine;
				LT::Add(__LexTable, current_entry_LT);
				current_entry_LT.lexema[0] = NULL;
				break;
			case LEX_MORE:
				current_entry_LT.lexema[0] = LEX_MORE;
				if (in.text[i + 1] == LEX_EQUAL)
				{
					current_entry_LT.lexema[0] = LEX_ME;
					i++;
				}
				current_entry_LT.sn = currentLine;
				LT::Add(__LexTable, current_entry_LT);
				current_entry_LT.lexema[0] = NULL;
				break;
			case LEX_LESS:
				current_entry_LT.lexema[0] = LEX_LESS;
				if (in.text[i + 1] == LEX_EQUAL)
				{
					current_entry_LT.lexema[0] = LEX_LE;
					i++;
				}
				current_entry_LT.sn = currentLine;
				LT::Add(__LexTable, current_entry_LT);
				current_entry_LT.lexema[0] = NULL;
				break;
			case DOLLAR:
				current_entry_LT.lexema[0] = LEX_GIVE;
				current_entry_LT.sn = currentLine;
				LT::Add(__LexTable, current_entry_LT);
				current_entry_LT.lexema[0] = NULL;
				break;
			case LEFTIND:
				if (__IdTable.table[__LexTable.table[__LexTable.size - 1].idxTI].idtype != IT::A && __IdTable.table[__LexTable.table[__LexTable.size - 1].idxTI].iddatatype!=IT::STR)
					throw ERROR_THROW_IN(116, currentLine, col);
				IndexFlag = true;
				break;
			case RIGHTIND:
				if (IndexFlag && (__LexTable.table[__LexTable.size-2].lexema[0] == LEX_ID || __LexTable.table[__LexTable.size-2].lexema[0] == LEX_LITERAL))
				{
					current_entry_LT.lexema[0] = LEX_INDEX;
					current_entry_LT.sn = currentLine;
					LT::Add(__LexTable, current_entry_LT);
					current_entry_LT.lexema[0] = NULL;
					break;
				}
				else
				{
					throw ERROR_THROW(116, currentLine, col);
				}

			}

		}
		/*for (int i = 0; i < __LexTable.size; i++)
		{
			while(__LexTable)
		}*/
		currentLine = 1;
		LT_file << currentLine;
		LT_file << '\t';
		for (int i = 0; i < __LexTable.size; i++)
		{
			current_entry_LT = LT::GetEntry(__LexTable, i);
			if (currentLine != current_entry_LT.sn)
			{
				currentLine = current_entry_LT.sn;
				LT_file << '\n';
				LT_file << currentLine;
				LT_file << '\t';
			}
			LT_file << current_entry_LT.lexema[0];
		}
		LT_file.close();
		IT_file << std::setw(5) << "id"
			<< std::setw(10) << "datatype"
			<< std::setw(10) << "idtype"
			<< std::setw(10) << "Line"
			<< std::setw(10) << "value"
			<< std::setw(10) << "Scope"
			<< std::setw(10)<<"idTi" << std::endl;

		for (int i = 0; i < __IdTable.size; i++) {
			current_entry_IT = IT::GetEntry(__IdTable, i);
			IT_file << std::setw(5) << current_entry_IT.id;
			if (current_entry_IT.iddatatype == IT::INT)
				IT_file << std::setw(10) << "INT";
			if (current_entry_IT.iddatatype == IT::STR)
				IT_file << std::setw(10) << "STR";
			if (current_entry_IT.iddatatype == IT::BYTE)
				IT_file << std::setw(10) << "BYTE";
			if (current_entry_IT.iddatatype == IT::BOOL)
				IT_file << std::setw(10) << "BOOL";
			if (current_entry_IT.idtype == IT::V)
				IT_file << std::setw(10) << "V";
			if (current_entry_IT.idtype == IT::L)
				IT_file << std::setw(10) << "L";
			if (current_entry_IT.idtype == IT::F)
				IT_file << std::setw(10) << "F";
			if (current_entry_IT.idtype == IT::P)
				IT_file << std::setw(10) << "P";
			if (current_entry_IT.idtype == IT::A)
				IT_file << std::setw(10) << "A";
			IT_file << std::setw(10) << current_entry_IT.idxfirstLE;

			if (current_entry_IT.iddatatype == IT::INT || current_entry_IT.iddatatype == IT::BYTE|| current_entry_IT.iddatatype == IT::BOOL) {
				IT_file << std::setw(10) << current_entry_IT.value.vint;
			}
			if (current_entry_IT.iddatatype == IT::STR) {
				IT_file << std::setw(7);
				for (int j = 0; j < strlen(current_entry_IT.value.vstr->str); j++) {
					IT_file << current_entry_IT.value.vstr->str[j];
				}
				IT_file << std::setw(10);
			}
			IT_file << std::setw(10);
			if (current_entry_IT.scope != NULL) {
				for (int j = 0; j < strlen(current_entry_IT.scope->id); j++)
				{
					IT_file << current_entry_IT.scope->id[j];
				}
			}
			IT_file << std::setw(10);
			IT_file << current_entry_IT.idxfirstLE;
			IT_file << std::endl;
		}
		IT_file.close();
		lexResult.idTable = __IdTable;
		lexResult.lexTable = __LexTable;
		return lexResult;
	}
}