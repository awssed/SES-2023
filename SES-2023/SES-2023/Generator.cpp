#include"Generator.h"
#include <locale>
#include <codecvt>
namespace GEN
{
	unsigned char bytes[4];
	IT::Entry* currentFunction;
	bool parmflag = false;
	bool trueflag = false;
	bool falseflag = false;
	bool flagMain = false;
	bool IfFlag = false;
	bool WhileFlag = false;
	int countParm;
	int currentString = 0;
	CONSTR currentConstr;
	stack<GEN::CONSTR> construct;
	void GenerateMemory(IT::IdTable& idtable, ofstream& writeCode)
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (idtable.table[i].idtype == IT::F)
			{
				writeCode << "stk";
				for (int j = 0; j < strlen(idtable.table[i].id); j++)
					writeCode << idtable.table[i].id[j];
				writeCode << "\tdb\t 1, 0,4 dup(0)";
				writeCode << NEW;
			}
			if (idtable.table[i].idtype == IT::V || idtable.table[i].idtype == IT::A)
			{
				for (int j = 0; j < strlen(idtable.table[i].id); j++)
					writeCode << idtable.table[i].id[j];
				writeCode << '_';
				for (int j = 0; j < strlen(idtable.table[i].scope->id); j++)
					writeCode << idtable.table[i].scope->id[j];
				writeCode << TAB;
				writeCode << BYTE_TYPE;
				writeCode << TAB;
				if (idtable.table[i].idtype == IT::V) {
					if (idtable.table[i].iddatatype == IT::BYTE)
					{
						writeCode << BYTE_DECLARE;
						writeCode << NEW;
					}
					if (idtable.table[i].iddatatype == IT::INT)
					{
						writeCode << INT_DECLARE;
						writeCode << NEW;
					}
					if (idtable.table[i].iddatatype == IT::BOOL)
					{
						writeCode << BOOL_DECLARE;
						writeCode << NEW;
					}
					if (idtable.table[i].iddatatype == IT::STR)
					{
						writeCode << STRING_LABEL;
						writeCode << idtable.table[i].value.vint;
						writeCode << " dup(-1)";
						writeCode << NULL_SYM;
						writeCode << NEW;
					}
				}
				if (idtable.table[i].idtype == IT::A)
				{
					if (idtable.table[i].iddatatype == IT::BYTE)
					{
						writeCode << BYTE_LABEL;
						writeCode << idtable.table[i].value.vint;
						writeCode << BYTE_ARRAY_DECLARE;
						writeCode << NEW;
					}
					if (idtable.table[i].iddatatype == IT::INT)
					{
						writeCode << INT_LABEL;
						writeCode << idtable.table[i].value.vint;
						writeCode << INT_ARRAY_DECLARE;
						writeCode << NEW;
					}
					if (idtable.table[i].iddatatype == IT::BOOL)
					{
						writeCode << BOOL_LABEL;
						writeCode << idtable.table[i].value.vint;
						writeCode << BYTE_ARRAY_DECLARE;
						writeCode << NEW;
					}
				}
			}
		}
		writeCode << HEADER_CONST;
		writeCode << NEW;
		for (int i = 0; i < idtable.size; i++)
		{
			if (idtable.table[i].idtype == IT::L)
			{
				for (int j = 0; j < strlen(idtable.table[i].id); j++)
					writeCode << idtable.table[i].id[j];
				writeCode << TAB;
				if (idtable.table[i].iddatatype == IT::INT)
				{
					writeCode << BYTE_TYPE;
					writeCode << TAB;
					writeCode << INT_LABEL;
					bytes[0] = (idtable.table[i].value.vint >> 0) & 0xFF;
					bytes[1] = (idtable.table[i].value.vint >> 8) & 0xFF;
					bytes[2] = (idtable.table[i].value.vint >> 16) & 0xFF;
					bytes[3] = (idtable.table[i].value.vint >> 24) & 0xFF;	
					for (int j = 0; j < 4; j++)
					{
						if(j!=0)
						writeCode << COM;
						writeCode << std::dec << static_cast<int>(bytes[j]);
					}
				}
				if (idtable.table[i].iddatatype == IT::BYTE)
				{
					writeCode << BYTE_TYPE;
					writeCode << TAB;
					writeCode << BYTE_LABEL;
					bytes[0] = (idtable.table[i].value.vint >> 0) & 0xFF;
					writeCode << std::dec << static_cast<int>(bytes[0]);
				}
				if (idtable.table[i].iddatatype == IT::BOOL)
				{
					writeCode << BYTE_TYPE;
					writeCode << TAB;
					writeCode << BOOL_LABEL;
					bytes[0] = (idtable.table[i].value.vint >> 0) & 0xFF;
					if (idtable.table[i].value.vint == 1)
						trueflag = true;
					if (idtable.table[i].value.vint == 0)
						falseflag = true;
					writeCode << std::dec << static_cast<int>(bytes[0]);
				}
				if (idtable.table[i].iddatatype == IT::STR)
				{
					writeCode << BYTE_TYPE;
					writeCode << TAB;
					writeCode << STRING_LABEL;
					for (int j = 0; j < strlen(idtable.table[i].value.vstr->str); j++)
					{
						writeCode << (char)idtable.table[i].value.vstr->str[j];
					}
					writeCode << NULL_SYM;
				}
				writeCode << NEW;
			}
		}
		if (!trueflag)
			writeCode << "true\tdb\t3,1\n";
		if(!falseflag)
			writeCode << "false\tdb\t3,0\n";
	}
	void Generator(LT::LexTable& lextable, IT::IdTable& idtable, Parm::PARM parms,PreProc::lib libraries)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring wideString = parms.out;
		size_t dotPosition = wideString.find('.');
		if (dotPosition != std::string::npos) {
			wideString = wideString.substr(0, dotPosition);
		}
		std::string asm_file = converter.to_bytes(wideString)+".asm";
		ofstream writeCode(asm_file);
		writeCode << HEADER;
		for (int i = 0; i < libraries.size; i++)
		{
			if (std::strcmp(libraries.libraries[i].c_str(), "math.lib"))
			{
				writeCode << MATH_LIB;
			}
			if (std::strcmp(libraries.libraries[i].c_str(), "string.lib"))
			{
				writeCode << STRING_LIB;
			}
		}
		writeCode << HEEDER_DATA;
		writeCode << '\n';
		writeCode << ERROR_DATA;
		writeCode << BUFFER;
		TITLE_CONSOLE(parms.in);
		writeCode << "\n;VARS\n";
		GenerateMemory(idtable,writeCode);
		writeCode << CODE;
		writeCode << INT_TO_CHAR_FUN;
		writeCode << SHOW_ERROR_MESSAGEBOX_FUN;
		writeCode << SHOW_ERROR_TYPE_MESSAGEBOX_FUN;
		writeCode << SHOW_ERROR_EMPTY_STK_MESSAGEBOX_FUN;
		writeCode << SHOW_ERROR_OVERFLOW_STK_MESSAGEBOX_FUN;
		writeCode << SHOW_ERROR_INDEX_STK_MESSAGEBOX_FUN;
		writeCode << ASSIGN_FUN;
		writeCode << PLUS_FUN;
		writeCode << MINUS_FUN;
		writeCode << MULT_FUN;
		writeCode << DIV_FUN;
		writeCode << MORE_FUN;
		writeCode << LESS_FUN;
		writeCode << MORE_EQUAL_FUN;
		writeCode << LESS_EQUAL_FUN;
		writeCode << CALL_ERROR;
		writeCode << CALL_ERROR_TYPE;
		writeCode << CALL_ERROR_EMPTY_STK;
		writeCode << CALL_ERROR_OVER_STK;
		writeCode << CALL_ERROR_INDEX;
		writeCode << EQUAL_FUN;
		for (int i = 0; i < lextable.size; i++)
		{
			if (currentString != lextable.table[i].sn) {
				currentString = lextable.table[i].sn;
				PL_STRING(currentString);
			}
			if (lextable.table[i].lexema[0] == LEX_MAIN)
			{
				flagMain = true;
				writeCode << MAIN;
				writeCode << SET_CONOSLE_TITLE;
				PL_STRING(currentString);
				writeCode << "mov dword ptr stkmain+2, esp\n";

			}
			if ((lextable.table[i].lexema[0] == LEX_ID  || lextable.table[i].lexema[0] == LEX_LITERAL) && lextable.table[i - 1].lexema[0] != LEX_INTEGER)//помещение в стек
			{
				if (idtable.table[lextable.table[i].idxTI].idtype == IT::F && lextable.table[i].lexema[0]==LEX_ID)
				{
					countParm = 0;
					for (int j = 0; j < idtable.size; j++)
					{
						if (idtable.table[j].scope == &idtable.table[lextable.table[i].idxTI] && idtable.table[j].idtype==IT::P)
						{
							countParm++;
						}
					}
					if (countParm == 0)
					{
						countParm = idtable.table[lextable.table[i].idxTI].value.vint;
					}
					MINUS_STK(countParm, currentFunction);
					writeCode << "call ";
					for (int j = 0; j < strlen(idtable.table[lextable.table[i].idxTI].id); j++)
					{
						writeCode << idtable.table[lextable.table[i].idxTI].id[j];
					}
					writeCode << "_fun";
					writeCode << NEW;
					if (idtable.table[lextable.table[i].idxTI].idxfirstLE == 0)
					{
						for (int j = 0; j < idtable.table[lextable.table[i].idxTI].value.vint;j++)
						{
							writeCode << "pop edx\npop edx\n";
						}
					}
					if (idtable.table[lextable.table[i].idxTI].iddatatype != IT::VOID)
					{
						writeCode << "add eax, 1\n push eax\n sub eax,1\n push eax\n";
						PLUS_STK(currentFunction);
					}
				}
				if (lextable.table[i + 2].lexema[0] == LEX_INDEX)//помещение элемента массива по индексу
				{
					PLUS_STK(currentFunction);
					if (idtable.table[lextable.table[i + 1].idxTI].idtype == IT::V)
					{
						if (currentFunction != NULL)
						{
							writeCode << "mov eax, OFFSET ";
							for (int j = 0; j < strlen(idtable.table[lextable.table[i].idxTI].id); j++)
							{
								writeCode << idtable.table[lextable.table[i].idxTI].id[j];
							}
							writeCode << '_';
							for (int j = 0; j < strlen(currentFunction->id); j++)
							{
								writeCode << currentFunction->id[j];
							}
							writeCode << NEW;
							writeCode << "add eax,1\n";
							if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::INT)
							{
								writeCode << "mov ebx, OFFSET ";
								for (int j = 0; j < strlen(idtable.table[lextable.table[i + 1].idxTI].id); j++)
								{
									writeCode << idtable.table[lextable.table[i + 1].idxTI].id[j];
								}
								writeCode << "_";
								for (int j = 0; j < strlen(currentFunction->id); j++)
								{
									writeCode << currentFunction->id[j];
								}
								writeCode << NEW;
								if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::INT)
									writeCode << "add ebx,1\nmov edx,0\n mov edx, [ebx]\n shl edx, 2\nadd eax, edx\npush eax\n";
								if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::BYTE)
									writeCode << "add ebx,1\nmov edx,0\n mov dl, [ebx]\n shl edx, 2\nadd eax, edx\npush eax\n";
								writeCode << "shr edx,2\n";
								writeCode << "cmp edx, ";
								writeCode << idtable.table[lextable.table[i].idxTI].value.vint;
								writeCode << "\nje callErrorIncorInd\n";
								writeCode << "jg callErrorIncorInd\n";
							}
							if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::BYTE|| idtable.table[lextable.table[i].idxTI].iddatatype == IT::STR)
							{
								writeCode << "mov ebx, OFFSET ";
								for (int j = 0; j < strlen(idtable.table[lextable.table[i + 2].idxTI].id); j++)
								{
									writeCode << idtable.table[lextable.table[i + 2].idxTI].id[j];
								}
								writeCode << "_";
								for (int j = 0; j < strlen(currentFunction->id); j++)
								{
									writeCode << currentFunction->id[j];
								}
								writeCode << NEW;
								if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::INT)
									writeCode << "add ebx,1\nmov edx,0\n mov edx, [ebx]\nadd eax, edx\npush eax\n";
								if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::BYTE)
									writeCode << "add ebx,1\nmov edx,0\n mov dl, [ebx]\nadd eax, edx\npush eax\n";
								writeCode << "cmp edx, ";
								writeCode << idtable.table[lextable.table[i].idxTI].value.vint;
								writeCode << "\nje callErrorIncorInd\n";
								writeCode << "jg callErrorIncorInd\n";
							}
							writeCode << "push OFFSET ";
							for (int j = 0; j < strlen(idtable.table[lextable.table[i].idxTI].id); j++)
							{
								writeCode << idtable.table[lextable.table[i].idxTI].id[j];
							}
							writeCode << "_";
							for (int j = 0; j < strlen(currentFunction->id); j++)
							{
								writeCode << currentFunction->id[j];
							}
						}
						else
						{
							writeCode << "mov eax, OFFSET ";
							for (int j = 0; j < strlen(idtable.table[lextable.table[i].idxTI].id); j++)
							{
								writeCode << idtable.table[lextable.table[i].idxTI].id[j];
							}
							writeCode << "_main";
							writeCode << NEW;
							writeCode << "add eax,1\n";
							if (idtable.table[lextable.table[i ].idxTI].iddatatype == IT::INT)
							{
								writeCode << "mov ebx, OFFSET ";
								for (int j = 0; j < strlen(idtable.table[lextable.table[i + 1].idxTI].id); j++)
								{
									writeCode << idtable.table[lextable.table[i + 1].idxTI].id[j];
								}
								writeCode << "_main";
								writeCode << NEW;
								if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::INT)
									writeCode << "add ebx,1\nmov edx,0\n mov edx, [ebx]\n shl edx, 2\nadd eax, edx\npush eax\n";
								if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::BYTE)
									writeCode << "add ebx,1\nmov edx,0\n mov dl, [ebx]\n shl edx, 2\nadd eax, edx\npush eax\n";
								writeCode << "shr edx,2\n";
								writeCode << "cmp edx, ";
								writeCode << idtable.table[lextable.table[i].idxTI].value.vint;
								writeCode << "\nje callErrorIncorInd\n";
								writeCode << "jg callErrorIncorInd\n";
							}
							if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::BYTE|| idtable.table[lextable.table[i].idxTI].iddatatype == IT::STR)
							{
								writeCode << "mov ebx, OFFSET ";
								for (int j = 0; j < strlen(idtable.table[lextable.table[i + 1].idxTI].id); j++)
								{
									writeCode << idtable.table[lextable.table[i + 1].idxTI].id[j];
								}
								writeCode << "_main";
								writeCode << NEW;
								if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::INT)
									writeCode << "add ebx,1\nmov edx,0\n mov edx, [ebx]\nadd eax, edx\npush eax\n";
								if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::BYTE)
									writeCode << "add ebx,1\nmov edx,0\n mov dl, [ebx]\nadd eax, edx\npush eax\n";
								writeCode << "cmp edx, ";
								writeCode << idtable.table[lextable.table[i].idxTI].value.vint;
								writeCode << "\nje callErrorIncorInd\n";
								writeCode << "jg callErrorIncorInd\n";
							}
							writeCode << "push OFFSET ";
							for (int j = 0; j < strlen(idtable.table[lextable.table[i].idxTI].id); j++)
							{
								writeCode << idtable.table[lextable.table[i].idxTI].id[j];
							}
							writeCode << "_main";

							writeCode << NEW;
						}
					}
					if (idtable.table[lextable.table[i + 1].idxTI].idtype == IT::L)
					{
						if (currentFunction != NULL)
						{
							writeCode << "mov eax, OFFSET ";
							for (int j = 0; j < strlen(idtable.table[lextable.table[i].idxTI].id); j++)
							{
								writeCode << idtable.table[lextable.table[i].idxTI].id[j];
							}
							writeCode << '_';
							for (int j = 0; j < strlen(currentFunction->id); j++)
							{
								writeCode << currentFunction->id[j];
							}
							writeCode << NEW;
							writeCode << "add eax,1\n";
							if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::INT)
							{
								writeCode << "mov ebx, OFFSET ";
								for (int j = 0; j < strlen(idtable.table[lextable.table[i + 1].idxTI].id); j++)
								{
									writeCode << idtable.table[lextable.table[i + 1].idxTI].id[j];
								}
								writeCode << NEW;
								if (idtable.table[lextable.table[i+1].idxTI].iddatatype == IT::INT)
									writeCode << "add ebx,1\nmov edx,0\n mov edx, [ebx]\n shl edx, 2\nadd eax, edx\npush eax\n";
								if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::BYTE)
									writeCode << "add ebx,1\nmov edx,0\n mov dl, [ebx]\n shl edx, 2\nadd eax, edx\npush eax\n";
							}
							if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::BYTE|| idtable.table[lextable.table[i].idxTI].iddatatype == IT::STR)
							{
								writeCode << "mov ebx, OFFSET ";
								for (int j = 0; j < strlen(idtable.table[lextable.table[i + 2].idxTI].id); j++)
								{
									writeCode << idtable.table[lextable.table[i + 1].idxTI].id[j];
								}
								if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::INT)
									writeCode << "add ebx,1\nmov edx,0\n mov edx, [ebx]\nadd eax, edx\npush eax\n";
								if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::BYTE)
									writeCode << "add ebx,1\nmov edx,0\n mov dl, [ebx]\nadd eax, edx\npush eax\n";
							}
							writeCode << "push OFFSET ";
							for (int j = 0; j < strlen(idtable.table[lextable.table[i].idxTI].id); j++)
							{
								writeCode << idtable.table[lextable.table[i].idxTI].id[j];
							}
							writeCode << "_";
							for (int j = 0; j < strlen(currentFunction->id); j++)
							{
								writeCode << currentFunction->id[j];
							}
							writeCode << NEW;
						}
						else
						{
							writeCode << "mov eax, OFFSET ";
							for (int j = 0; j < strlen(idtable.table[lextable.table[i].idxTI].id); j++)
							{
								writeCode << idtable.table[lextable.table[i].idxTI].id[j];
							}
							writeCode << "_main";
							writeCode << NEW;
							writeCode << "add eax,1\n";
							if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::INT)
							{
								writeCode << "mov ebx, OFFSET ";
								for (int j = 0; j < strlen(idtable.table[lextable.table[i + 1].idxTI].id); j++)
								{
									writeCode << idtable.table[lextable.table[i + 1].idxTI].id[j];
								}
								writeCode << NEW;
								if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::INT)
									writeCode << "add ebx,1\nmov edx,0\n mov edx, [ebx]\n shl edx, 2\nadd eax, edx\npush eax\n";
								if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::BYTE)
									writeCode << "add ebx,1\nmov edx,0\n mov dl, [ebx]\n shl edx, 2\nadd eax, edx\npush eax\n";
							}
							if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::BYTE|| idtable.table[lextable.table[i].idxTI].iddatatype == IT::STR)
							{
								writeCode << "mov ebx, OFFSET ";
								for (int j = 0; j < strlen(idtable.table[lextable.table[i + 1].idxTI].id); j++)
								{
									writeCode << idtable.table[lextable.table[i + 1].idxTI].id[j];
								}
								writeCode << NEW;
								if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::INT)
									writeCode << "add ebx,1\nmov edx,0\n mov edx, [ebx]\nadd eax, edx\npush eax\n";
								if (idtable.table[lextable.table[i + 2].idxTI].iddatatype == IT::BYTE)
									writeCode << "add ebx,1\nmov edx,0\n mov dl, [ebx]\nadd eax, edx\npush eax\n";
							}
							writeCode << "push OFFSET ";
							for (int j = 0; j < strlen(idtable.table[lextable.table[i].idxTI].id); j++)
							{
								writeCode << idtable.table[lextable.table[i].idxTI].id[j];
							}
							writeCode << "_main";
							writeCode << NEW;
						}
					}
					
					writeCode << NEW;
					i++;
					continue;
				}
				if (idtable.table[lextable.table[i].idxTI].idtype == IT::P && idtable.table[lextable.table[i].idxTI].scope == currentFunction)
				{
					PLUS_STK(currentFunction);
					writeCode << PUSH;
					for (int j = 0; j < strlen(idtable.table[lextable.table[i].idxTI].id); j++)//помещение обычной переменной
					{
						writeCode << idtable.table[lextable.table[i].idxTI].id[j];
					}
					writeCode << '_';
					for (int j = 0; j < strlen(currentFunction->id); j++)
					{
						writeCode << currentFunction->id[j];
					}
					writeCode << NEW;
					writeCode << PUSH;
					for (int j = 0; j < strlen(idtable.table[lextable.table[i].idxTI].id); j++)//помещение обычной переменной
					{
						writeCode << idtable.table[lextable.table[i].idxTI].id[j];
					}
					writeCode << '_';
					for (int j = 0; j < strlen(currentFunction->id); j++)
					{
						writeCode << currentFunction->id[j];
					}
					writeCode << "_type\n";
				}

				if ((idtable.table[lextable.table[i].idxTI].idtype == IT::V|| idtable.table[lextable.table[i].idxTI].idtype == IT::L)&&lextable.table[i+1].lexema[0]!=LEX_INDEX) {
					PLUS_STK(currentFunction);
					writeCode << PUSH;
					writeCode << OFFSET;
					for (int j = 0; j < strlen(idtable.table[lextable.table[i].idxTI].id); j++)//помещение обычной переменной
					{
						writeCode << idtable.table[lextable.table[i].idxTI].id[j];
					}
					if (idtable.table[lextable.table[i].idxTI].idtype == IT::V)
					{
						writeCode << "_";
						for (int j = 0; j < strlen(idtable.table[lextable.table[i].idxTI].scope->id); j++)//помещение обычной переменной
						{
							writeCode << idtable.table[lextable.table[i].idxTI].scope->id[j];
						}
					}
					writeCode << "+1\n";
					writeCode << PUSH;
					writeCode << OFFSET;
					for (int j = 0; j < strlen(idtable.table[lextable.table[i].idxTI].id); j++)
					{
						writeCode << idtable.table[lextable.table[i].idxTI].id[j];
					}
					if (idtable.table[lextable.table[i].idxTI].idtype == IT::V)
					{
						writeCode << "_";
						for (int j = 0; j < strlen(idtable.table[lextable.table[i].idxTI].scope->id); j++)//помещение обычной переменной
						{
							writeCode << idtable.table[lextable.table[i].idxTI].scope->id[j];
						}
					}
					writeCode << NEW;
				}

			}
			if (lextable.table[i].lexema[0] == LEX_ID && lextable.table[i - 2].lexema[0] == LEX_FUNCTION)//создание функций "шапки функции с парамтерами"
			{
				currentFunction = &idtable.table[lextable.table[i].idxTI];
				for (int j = 0; j < strlen(idtable.table[lextable.table[i].idxTI].id); j++)
				{
					writeCode << idtable.table[lextable.table[i].idxTI].id[j];
				}
				writeCode << "_fun ";
				writeCode << PROC;
				for (int j = 0; j < idtable.size; j++)
				{
					if (idtable.table[j].idtype == IT::P && idtable.table[j].scope==currentFunction)
					{
						idtable.table[i].value.vint++;
						if (parmflag)
							writeCode << COM;
						parmflag = true;
						for (int q = 0; q < strlen(idtable.table[j].id); q++)
						{
							writeCode << idtable.table[j].id[q];
						}
						writeCode << '_';
						for (int q = 0; q < strlen(currentFunction->id); q++)
						{
							writeCode << currentFunction->id[q];
						}
						writeCode << "_type";
						writeCode << PTR_BYTE;
						writeCode << COM;
						for (int q = 0; q < strlen(idtable.table[j].id); q++)
						{
							writeCode << idtable.table[j].id[q];
						}
						writeCode << '_';
						for (int q = 0; q < strlen(currentFunction->id); q++)
						{
							writeCode << currentFunction->id[q];
						}
						writeCode << PTR_BYTE;
					}
				}
				writeCode << NEW;
				writeCode << START;
				for (int j = 0; j < idtable.size; j++)//создание проверки на типы парамтеров
				{
					if (idtable.table[j].idtype == IT::P && idtable.table[j].scope == currentFunction)
					{
						writeCode << "mov eax, ";
						for (int q = 0; q < strlen(idtable.table[j].id); q++)
						{
							writeCode << idtable.table[j].id[q];
						}
						writeCode << '_';
						for (int q = 0; q < strlen(currentFunction->id); q++)
						{
							writeCode << currentFunction->id[q];
						}
						writeCode << "_type\n";
						writeCode << "mov al, [eax]\n";
						writeCode << "cmp al, ";
						if (idtable.table[j].iddatatype == IT::BYTE)
							writeCode << "1\n";
						if (idtable.table[j].iddatatype == IT::INT)
						{
							writeCode << "2\n";
							writeCode << NEW;
							writeCode << "je go_next";
							writeCode << NEW;
							writeCode << "cmp al, 1\n";

						}
						if (idtable.table[j].iddatatype == IT::BOOL)
							writeCode << "3\n";
						if (idtable.table[j].iddatatype == IT::STR)
							writeCode << "7\n";
						writeCode << "jne CallErrorType\n";
					}
				}
				writeCode << "go_next:";
				writeCode << NEW;
				writeCode << "mov dword ptr stk";
				for (int j = 0; j < strlen(currentFunction->id); j++)//сохраняем указатель стека для выхода из функции
				{
					writeCode << currentFunction->id[j];
				}
				writeCode << "+2, esp\n";
			}
			if (lextable.table[i].lexema[0] == LEX_BRACELET && (lextable.table[i + 1].lexema[0] == LEX_FUNCTION || lextable.table[i + 1].lexema[0] == LEX_MAIN))//footer для функции
			{
				writeCode << NEW;
				writeCode << "mov esp,dword ptr stk";
				for (int j = 0; j < strlen(currentFunction->id); j++)//возращаем указатель стэка на место чтобы выйти
				{
					writeCode << currentFunction->id[j];
				}
				writeCode<<"+2";
				writeCode << NEW;
				writeCode << "ret\n";
				for (int j = 0; j < strlen(currentFunction->id); j++)
				{
					writeCode << currentFunction->id[j];
				}
				writeCode << "_fun ";
				writeCode << ENDP;
				currentFunction = NULL;
			}
			if (lextable.table[i].lexema[0] == LEX_GIVE)
			{
				MINUS_STK(2,currentFunction);
				writeCode << "call Assign\n";
			}
			if (lextable.table[i].lexema[0] == LEX_READ)
			{
				MINUS_STK(1, currentFunction);
				writeCode << "INVOKE int_to_char, OFFSET caption, current_string\n push OFFSET caption\n"; \
				writeCode << "call readCon\n";
				writeCode << "pop eax\n pop eax\npop eax\n";
				writeCode << "mov eax,0\n";
			}
			if (lextable.table[i].lexema[0] == LEX_PLUS)
			{
				MINUS_STK(2,currentFunction);
				writeCode << "call PLUS\n push ebx\npush eax\n";
				PLUS_STK(currentFunction);
			}

			if (lextable.table[i].lexema[0] == LEX_MINUS)
			{
				MINUS_STK(2,currentFunction);
				writeCode << "call MINUS\n push ebx\npush eax\n";
				PLUS_STK(currentFunction);
			}
			if (lextable.table[i].lexema[0] == LEX_STAR)
			{
				MINUS_STK(2,currentFunction);
				writeCode << "call MULT\n push ebx\npush eax\n";
				PLUS_STK(currentFunction);
			}
			if (lextable.table[i].lexema[0] == LEX_DIRSLASH)
			{
				MINUS_STK(2,currentFunction);
				writeCode << "call DIVIDE\n push ebx\npush eax\n";
				PLUS_STK(currentFunction);
			}
			if (lextable.table[i].lexema[0] == LEX_ME)
			{
				MINUS_STK(2,currentFunction);
				writeCode << "call MOREEQUAL\n push ebx\npush eax\n";
				PLUS_STK(currentFunction);
				i++;
			}
			if (lextable.table[i].lexema[0] == LEX_LE)
			{
				MINUS_STK(2,currentFunction);
				writeCode << "call LESEQUAL\n push ebx\npush eax\n";
				PLUS_STK(currentFunction);
				i++;
			}
			if (lextable.table[i].lexema[0] == LEX_MORE)
			{
				MINUS_STK(2,currentFunction);
				writeCode << "call MORE\n push ebx\npush eax\n";
				PLUS_STK(currentFunction);
			}
			if (lextable.table[i].lexema[0] == LEX_LESS)
			{
				MINUS_STK(2,currentFunction);
				writeCode << "call LESSFUN\n push ebx\npush eax\n";
				PLUS_STK(currentFunction);
			}
			if (lextable.table[i].lexema[0] == LEX_EQUAL)
			{
				MINUS_STK(2,currentFunction);
				writeCode << "call EQUAL\n push ebx\npush eax\n";
				PLUS_STK(currentFunction);
			}
			if (lextable.table[i].lexema[0] == LEX_NE)
			{
				MINUS_STK(2, currentFunction);
				writeCode << "call NOTEQUAL\n push ebx\npush eax\n";
				PLUS_STK(currentFunction);
			}
			if (lextable.table[i].lexema[0] == LEX_DUP)
			{
				PLUS_STK(currentFunction);
				writeCode << DUPLICATE;
			}
			if (lextable.table[i].lexema[0] == LEX_DROP)
			{
				CHECK_STK(1,currentFunction)
				MINUS_STK(1,currentFunction);
				writeCode << G_DROP;
			}
			if (lextable.table[i].lexema[0] == LEX_SWAP)
			{
				CHECK_STK(2,currentFunction);
				writeCode << G_SWAP;
			}
			if (lextable.table[i].lexema[0] == LEX_OVER)
			{
				CHECK_STK(2,currentFunction);
				PLUS_STK(currentFunction);
				writeCode << G_OVER;
			}
			if (lextable.table[i].lexema[0] == LEX_DEPTH)
			{
				DEAPTH_STK(currentFunction);
				PLUS_STK(currentFunction);
			}
			if (lextable.table[i].lexema[0] == LEX_CLEAR)
			{
				if (currentFunction != NULL)
				{
					writeCode << "mov esp, dword ptr stk";
					for (int j = 0; j < strlen(currentFunction->id); j++)//сохраняем указатель стека для выхода из функции
					{
						writeCode << currentFunction->id[j];
					}
					writeCode << "+2";
					writeCode << NEW;
					writeCode << "mov stk";
					for (int j = 0; j < strlen(currentFunction->id); j++)//сохраняем указатель стека для выхода из функции
					{
						writeCode << currentFunction->id[j];
					}
					writeCode << "+1,0\n";//перевод глубины на ноль
				}
				else
				{
					writeCode << "mov esp, dword ptr stkmain+1\n mov stkmain+1, 0\n";

				}
			}
			if (lextable.table[i].lexema[0] == LEX_WHILE)
			{
				currentConstr.number++;
				currentConstr.type = GEN::WHILE;
				WhileFlag = true;
				construct.push(currentConstr);
				writeCode << "while";
				writeCode << currentConstr.number;
				writeCode << ":\n";
			}
			if (lextable.table[i].lexema[0] == LEX_RIGHTTHESIS && lextable.table[i + 1].lexema[0] == LEX_LEFTBRACE && WhileFlag)
			{
				i++;
				MINUS_STK(1, currentFunction);
				writeCode << "pop eax\npop eax\n mov al, [eax]\n cmp al,[byte ptr true+1]\n jne endWhile";
				writeCode << currentConstr.number;
				writeCode << NEW;
				WhileFlag = false;
			}
			if (lextable.table[i].lexema[0] == LEX_IF)
			{

				currentConstr.number++;
				currentConstr.type = GEN::IF;
				IfFlag = true;
				construct.push(currentConstr);
			}
			if (lextable.table[i].lexema[0] == LEX_RIGHTTHESIS && lextable.table[i + 1].lexema[0] == LEX_LEFTBRACE && IfFlag)
			{
				i++;
				MINUS_STK(1, currentFunction);
				writeCode << "pop eax\npop eax\n mov al, [eax]\n cmp al,[byte ptr true+1]\njne goIf";
				writeCode << currentConstr.number;
				writeCode << NEW;
				IfFlag = false;
			}
			if (lextable.table[i].lexema[0] == LEX_BRACELET && !construct.empty())
			{
				if (!construct.empty() && construct.top().type == GEN::IF)
				{
					
					writeCode << "goIf";
					writeCode << construct.top().number;
					writeCode << ":\n";
					construct.pop();
					continue;
				}
				if (!construct.empty() && construct.top().type == GEN::WHILE )
				{
					writeCode << "jmp while";
					writeCode << construct.top().number;
					writeCode << NEW;
					writeCode << "endWhile";
					writeCode << construct.top().number;
					writeCode << ":\n";
					construct.pop();
					continue;
				}
			}

			if (lextable.table[i].lexema[0] == LEX_RETURN && currentFunction!=NULL)
			{
				writeCode << "pop eax";
				writeCode << NEW;
				writeCode << "pop ebx";
				writeCode << NEW;
				writeCode << "ret";
				writeCode << NEW;
			}if (lextable.table[i].lexema[0] == LEX_RETURN && currentFunction == NULL)
			{
				writeCode << "pop eax\n";
				writeCode << "pop eax\n";
				if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::BYTE ||
					idtable.table[lextable.table[i].idxTI].iddatatype == IT::BOOL ||
					idtable.table[lextable.table[i].idxTI].iddatatype == IT::STR)
				{
					writeCode << "mov al,[eax]\n";
					writeCode << "mov bl, al\n";
					writeCode << "mov eax,0\n mov al, bl\n mov bl,0\n";
					writeCode << "push eax\n";
					writeCode << "call ExitProcess\n";
				}
				if (idtable.table[lextable.table[i].idxTI].iddatatype == IT::INT)
				{
					writeCode << "mov eax,[dword ptr eax]\n";
					writeCode << "push eax\n";
					writeCode << "call ExitProcess\n";
				}

			}
			if (lextable.table[i].lexema[0] == LEX_WRITE)
			{
				CHECK_STK(1, currentFunction);
				writeCode << "call writeString\n";
				MINUS_STK(1, currentFunction);
				writeCode << "pop eax\n pop eax\n";
				writeCode << "mov eax,0\n";
			}
			if (lextable.table[i].lexema[0] == LEX_WRITELINE)
			{
				CHECK_STK(1, currentFunction);
				writeCode << "call writeLineString\n";
				MINUS_STK(1, currentFunction);
				writeCode << "pop eax\n pop eax\n";
				writeCode << "mov eax,0\n";
				
			}		}
			if (!construct.empty())
			{
				throw ERROR_THROW(126, currentString, 0);
			}
		writeCode << MAKEPAUSE;
		writeCode << "mov esp,dword ptr stkmain+2\n";
		writeCode << FOOTER;
		string command_ml = "@echo off\n call vcvarsall.bat x86 \nml /c " + asm_file;
		dotPosition = asm_file.find('.');
		if (dotPosition != std::string::npos) {
			asm_file = asm_file.substr(0, dotPosition);
		}
		string command_link = "\nlink " + asm_file+".obj"+" /SUBSYSTEM:CONSOLE";
		string executeString = "\ncall "+asm_file + ".exe";
		std::ofstream file_comp("comp.bat");
		file_comp << command_ml;
		file_comp << command_link;
		file_comp << executeString;
		/*system("call callTranslation.bat");*/
		file_comp.close();
	}
}