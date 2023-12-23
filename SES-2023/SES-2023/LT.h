#pragma once
#define LEXEMA_FIXSIZE 1
#define	LT_MAXSIZE 4096
#define LT_TI_NULLIDX 0XFFFFFFFF
#define LEX_INTEGER 't'
#define LEX_BYTE 't'
#define LEX_STRING 't'
#define LEX_BOOL 't'
#define LEX_ARRAY 'a'
#define LEX_ID 'i'
#define LEX_LITERAL 'l'
#define LEX_TRUE 'v'
#define LEX_FALSE 'u'
#define LEX_FUNCTION 'f'
#define LEX_MAIN 'm'
#define LEX_WRITE 'w'
#define LEX_WRITELINE 'x'
#define LEX_READ 'n'
#define LEX_WHILE 'h'
#define LEX_IF 'z'
#define LEX_DUP 'd'
#define LEX_DROP 'r'
#define LEX_SWAP 's'
#define LEX_OVER 'o'
#define LEX_DEPTH 'e'
#define LEX_CLEAR 'c'
#define LEX_SEMICOLON ';'
#define LEX_COMMA ','
#define LEX_LEFTBRACE '{'
#define LEX_BRACELET '}'
#define LEX_LEFTTHESIS '('
#define LEX_RIGHTTHESIS ')'
#define LEX_PLUS '+'
#define LEX_MINUS '-'
#define LEX_STAR '*'
#define LEX_DIRSLASH '/'
#define LEX_EQUAL '='
#define LEX_MORE '>'
#define LEX_LESS '<'
#define LEX_NOT '!'
#define LEX_ME 'p'
#define LEX_LE 'k'
#define LEX_NE 'j'
#define LEX_GIVE '$'
#define LEX_INDEX '@'
#define LEX_RETURN 'q'

namespace LT
{
	struct Entry
	{
		char lexema[LEXEMA_FIXSIZE];
		int sn;//номер строки в исходном коде
		int idxTI;// строки в IT
	};
	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
	};
	LexTable Create(int size);
	void Add(LexTable& lextable, Entry entry);
	Entry GetEntry(LexTable& lextable, int n);
	void Delete(LexTable& lextable);
}
