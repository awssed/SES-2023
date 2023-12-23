#pragma once
#include<iostream>
#include<stack>
#include"stdafx.h"
#include"LA.h"
#include"IT.h"
#include"LT.h"
#include"Preproc.h"
#define MAX_LEX_SIZE 4096
#define MARK '\''
#define NEW_LINE '|'
#define SEMICOLON ';'
#define COMMA ','
#define LEFT_BRACE '{'
#define RIGHT_BRACE '}'
#define LEFTTHESIS '('
#define RIGHTTHESIS ')'
#define LEFTIND '['
#define RIGHTIND ']'
#define PLUS '+'
#define MINUS '-'
#define STAR '*'
#define EQUAL '='
#define DIRSLASH '/'
#define DOLLAR '$'
#define FST_INT FST::FST _int(str,\
	4,\
	FST::NODE(1, FST::RELATION('i', 1)),\
	FST::NODE(1, FST::RELATION('n', 2)),\
	FST::NODE(1, FST::RELATION('t', 3)),\
	FST::NODE()\
);
#define FST_BYTE FST::FST _byte(str,\
	5,\
	FST::NODE(1,FST::RELATION('b',1)),\
	FST::NODE(1,FST::RELATION('y',2)),\
	FST::NODE(1,FST::RELATION('t',3)),\
	FST::NODE(1,FST::RELATION('e',4)),\
	FST::NODE()\
);
#define FST_BOOL FST::FST _bool(str,\
	5,\
	FST::NODE(1,FST::RELATION('b',1)),\
	FST::NODE(1,FST::RELATION('o',2)),\
	FST::NODE(1,FST::RELATION('o',3)),\
	FST::NODE(1,FST::RELATION('l',4)),\
	FST::NODE()\
);
#define FST_STRING FST::FST _string(str,\
	7,\
	FST::NODE(1, FST::RELATION('s', 1)),\
	FST::NODE(1, FST::RELATION('t', 2)),\
	FST::NODE(1, FST::RELATION('r', 3)),\
	FST::NODE(1, FST::RELATION('i', 4)),\
	FST::NODE(1, FST::RELATION('n', 5)),\
	FST::NODE(1, FST::RELATION('g', 6)),\
	FST::NODE()\
);
#define FST_ARRAY FST::FST _array(str,\
	6,\
	FST::NODE(1,FST::RELATION('a',1)),\
	FST::NODE(1,FST::RELATION('r',2)),\
	FST::NODE(1,FST::RELATION('r',3)),\
	FST::NODE(1,FST::RELATION('a',4)),\
	FST::NODE(1,FST::RELATION('y',5)),\
	FST::NODE()\
);
#define FST_FUNC FST::FST _function(str,\
	9,\
	FST::NODE(1, FST::RELATION('f', 1)),\
	FST::NODE(1, FST::RELATION('u', 2)),\
	FST::NODE(1, FST::RELATION('n', 3)),\
	FST::NODE(1, FST::RELATION('c', 4)),\
	FST::NODE(1, FST::RELATION('t', 5)),\
	FST::NODE(1, FST::RELATION('i', 6)),\
	FST::NODE(1, FST::RELATION('o', 7)),\
	FST::NODE(1, FST::RELATION('n', 8)),\
	FST::NODE()\
);
#define FST_RETURN FST::FST _return(str,\
	7,\
	FST::NODE(1,FST::RELATION('r',1)),\
	FST::NODE(1,FST::RELATION('e',2)),\
	FST::NODE(1,FST::RELATION('t',3)),\
	FST::NODE(1,FST::RELATION('u',4)),\
	FST::NODE(1,FST::RELATION('r',5)),\
	FST::NODE(1,FST::RELATION('n',6)),\
	FST::NODE()\
);
#define FST_MAIN FST::FST _main(str,\
	5,\
	FST::NODE(1, FST::RELATION('m', 1)),\
	FST::NODE(1, FST::RELATION('a', 2)),\
	FST::NODE(1, FST::RELATION('i', 3)),\
	FST::NODE(1, FST::RELATION('n', 4)),\
	FST::NODE()\
);
#define FST_WRITE FST::FST _write(str,\
	6,\
	FST::NODE(1,FST::RELATION('w',1)),\
	FST::NODE(1,FST::RELATION('r',2)),\
	FST::NODE(1,FST::RELATION('i',3)),\
	FST::NODE(1,FST::RELATION('t',4)),\
	FST::NODE(1,FST::RELATION('e',5)),\
	FST::NODE()\
);
#define FST_WRITELINE FST::FST _writeline(str,\
	10,\
	FST::NODE(1,FST::RELATION('w',1)),\
	FST::NODE(1,FST::RELATION('r',2)),\
	FST::NODE(1,FST::RELATION('i',3)),\
	FST::NODE(1,FST::RELATION('t',4)),\
	FST::NODE(1,FST::RELATION('e',5)),\
	FST::NODE(1,FST::RELATION('l',6)),\
	FST::NODE(1,FST::RELATION('i',7)),\
	FST::NODE(1,FST::RELATION('n',8)),\
	FST::NODE(1,FST::RELATION('e',9)),\
	FST::NODE()\
);
#define FST_READ FST::FST _read(str,\
	5,\
	FST::NODE(1,FST::RELATION('r',1)),\
	FST::NODE(1,FST::RELATION('e',2)),\
	FST::NODE(1,FST::RELATION('a',3)),\
	FST::NODE(1,FST::RELATION('d',4)),\
	FST::NODE()\
);
#define FST_TRUE FST::FST _true(str,\
5,\
	FST::NODE(1,FST::RELATION('t',1)),\
	FST::NODE(1,FST::RELATION('r',2)),\
	FST::NODE(1,FST::RELATION('u',3)),\
	FST::NODE(1,FST::RELATION('e',4)),\
	FST::NODE()\
);
#define FST_FALSE FST::FST _false(str,\
6,\
	FST::NODE(1,FST::RELATION('f',1)),\
	FST::NODE(1,FST::RELATION('a',2)),\
	FST::NODE(1,FST::RELATION('l',3)),\
	FST::NODE(1,FST::RELATION('s',4)),\
	FST::NODE(1,FST::RELATION('e',5)),\
	FST::NODE()\
);
#define FST_WHILE FST::FST _while(str, \
    6, \
    FST::NODE(1, FST::RELATION('w', 1)), \
    FST::NODE(1, FST::RELATION('h', 2)), \
    FST::NODE(1, FST::RELATION('i', 3)), \
    FST::NODE(1, FST::RELATION('l', 4)), \
    FST::NODE(1, FST::RELATION('e', 5)), \
    FST::NODE() \
);
#define FST_IF FST::FST _if(str, \
    3, \
    FST::NODE(1, FST::RELATION('i', 1)), \
    FST::NODE(1, FST::RELATION('f', 2)), \
    FST::NODE() \
);
#define FST_DUP FST::FST _dup(str, \
    4, \
    FST::NODE(1, FST::RELATION('d', 1)), \
    FST::NODE(1, FST::RELATION('u', 2)), \
    FST::NODE(1, FST::RELATION('p', 3)), \
    FST::NODE() \
);

#define FST_DROP FST::FST _drop(str, \
    5, \
    FST::NODE(1, FST::RELATION('d', 1)), \
    FST::NODE(1, FST::RELATION('r', 2)), \
    FST::NODE(1, FST::RELATION('o', 3)), \
    FST::NODE(1, FST::RELATION('p', 4)), \
    FST::NODE() \
);

#define FST_SWAP FST::FST _swap(str, \
    5, \
    FST::NODE(1, FST::RELATION('s', 1)), \
    FST::NODE(1, FST::RELATION('w', 2)), \
    FST::NODE(1, FST::RELATION('a', 3)), \
    FST::NODE(1, FST::RELATION('p', 4)), \
    FST::NODE() \
);

#define FST_OVER FST::FST _over(str, \
    5, \
    FST::NODE(1, FST::RELATION('o', 1)), \
    FST::NODE(1, FST::RELATION('v', 2)), \
    FST::NODE(1, FST::RELATION('e', 3)), \
    FST::NODE(1, FST::RELATION('r', 4)), \
    FST::NODE() \
);



#define FST_DEPTH FST::FST _depth(str, \
    6, \
    FST::NODE(1, FST::RELATION('d', 1)), \
    FST::NODE(1, FST::RELATION('e', 2)), \
    FST::NODE(1, FST::RELATION('p', 3)), \
    FST::NODE(1, FST::RELATION('t', 4)), \
    FST::NODE(1, FST::RELATION('h', 5)), \
    FST::NODE() \
);

#define FST_CLEAR FST::FST _clear(str, \
    6, \
    FST::NODE(1, FST::RELATION('c', 1)), \
    FST::NODE(1, FST::RELATION('l', 2)), \
    FST::NODE(1, FST::RELATION('e', 3)), \
    FST::NODE(1, FST::RELATION('a', 4)), \
    FST::NODE(1, FST::RELATION('r', 5)), \
    FST::NODE() \
);

#define FST_LITERAL FST::FST literal_int(str,\
	2,\
	FST::NODE(20,\
		FST::RELATION('0', 0), FST::RELATION('1', 0), FST::RELATION('2', 0),\
		FST::RELATION('3', 0), FST::RELATION('4', 0), FST::RELATION('5', 0),\
		FST::RELATION('6', 0), FST::RELATION('7', 0), FST::RELATION('8', 0),\
		FST::RELATION('9', 0), FST::RELATION('0', 1), FST::RELATION('1', 1),\
		FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1),\
		FST::RELATION('5', 1), FST::RELATION('6', 1), FST::RELATION('7', 1),\
		FST::RELATION('8', 1), FST::RELATION('9', 1)),\
	FST::NODE()\
);
#define FST_IDENF FST::FST idenf(str,\
	2,\
	FST::NODE(118,\
		FST::RELATION('a', 1), FST::RELATION('a', 0), FST::RELATION('b', 1), FST::RELATION('b', 0),\
		FST::RELATION('c', 1), FST::RELATION('c', 0), FST::RELATION('d', 1), FST::RELATION('d', 0), FST::RELATION('e', 1), FST::RELATION('e', 0),\
		FST::RELATION('f', 1), FST::RELATION('f', 0), FST::RELATION('g', 1), FST::RELATION('g', 0), FST::RELATION('h', 0), FST::RELATION('h', 1), FST::RELATION('i', 0), FST::RELATION('i', 1),\
		FST::RELATION('j', 0), FST::RELATION('j', 1), FST::RELATION('k', 0), FST::RELATION('k', 1), FST::RELATION('l', 0), FST::RELATION('l', 1),\
		FST::RELATION('m', 0), FST::RELATION('m', 1), FST::RELATION('n', 0), FST::RELATION('n', 1), FST::RELATION('o', 0), FST::RELATION('o', 1),\
		FST::RELATION('p', 0), FST::RELATION('p', 1), FST::RELATION('q', 0), FST::RELATION('q', 1), FST::RELATION('r', 0), FST::RELATION('r', 1),\
		FST::RELATION('s', 0), FST::RELATION('s', 1), FST::RELATION('t', 0), FST::RELATION('t', 1), FST::RELATION('u', 0), FST::RELATION('u', 1),\
		FST::RELATION('v', 0), FST::RELATION('v', 1), FST::RELATION('w', 0), FST::RELATION('w', 1), FST::RELATION('x', 0), FST::RELATION('x', 1),\
		FST::RELATION('y', 0), FST::RELATION('y', 1), FST::RELATION('z', 0), FST::RELATION('z', 1),FST::RELATION('A', 1), FST::RELATION('A', 0), FST::RELATION('B', 1), FST::RELATION('B', 0),\
		FST::RELATION('C', 1), FST::RELATION('C', 0), FST::RELATION('D', 1), FST::RELATION('D', 0), FST::RELATION('E', 1), FST::RELATION('E', 0),\
		FST::RELATION('F', 1), FST::RELATION('F', 0), FST::RELATION('G', 1), FST::RELATION('G', 0), FST::RELATION('H', 0), FST::RELATION('H', 1), FST::RELATION('I', 0), FST::RELATION('I', 1),\
		FST::RELATION('J', 0), FST::RELATION('J', 1), FST::RELATION('K', 0), FST::RELATION('K', 1), FST::RELATION('L', 0), FST::RELATION('L', 1),\
		FST::RELATION('M', 0), FST::RELATION('M', 1), FST::RELATION('N', 0), FST::RELATION('N', 1), FST::RELATION('O', 0), FST::RELATION('O', 1),\
		FST::RELATION('P', 0), FST::RELATION('P', 1), FST::RELATION('Q', 0), FST::RELATION('Q', 1), FST::RELATION('R', 0), FST::RELATION('R', 1),\
		FST::RELATION('S', 0), FST::RELATION('S', 1), FST::RELATION('T', 0), FST::RELATION('T', 1), FST::RELATION('U', 0), FST::RELATION('U', 1),\
		FST::RELATION('V', 0), FST::RELATION('V', 1), FST::RELATION('W', 0), FST::RELATION('W', 1), FST::RELATION('X', 0), FST::RELATION('X', 1),\
		FST::RELATION('Y', 0), FST::RELATION('Y', 1), FST::RELATION('Z', 0), FST::RELATION('Z', 1), FST::RELATION('0', 1), FST::RELATION('1', 1),\
		FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1),\
		FST::RELATION('5', 1), FST::RELATION('6', 1), FST::RELATION('7', 1),\
		FST::RELATION('8', 1), FST::RELATION('9', 1)),\
	FST::NODE()\
);

#define MATH_LIB \
	const char* power="power";\
	const char* factor="factor";\
	IT::Add(__IdTable,*(new IT::Entry (0,power,IT::INT,IT::F,NULL,2)));\
	IT::Add(__IdTable,*(new IT::Entry (0,factor,IT::INT,IT::F,NULL,1)));

#define STRING_LIB \
	const char* length="length";\
	const char* compare="compare";\
	const char* compareSymb="compS";\
	const char* print="print";\
	IT::Add(__IdTable,*(new IT::Entry (0,length,IT::INT,IT::F,NULL,1)));\
	IT::Add(__IdTable,*(new IT::Entry (0,compare,IT::BOOL,IT::F,NULL,2)));\
	IT::Add(__IdTable,*(new IT::Entry (0,compareSymb,IT::BOOL,IT::F,NULL,2)));\
	IT::Add(__IdTable,*(new IT::Entry (0,print,IT::VOID,IT::F,NULL,1)));
namespace LA
{
	struct LEX
	{
		IT::IdTable idTable;
		LT::LexTable lexTable;
	};
	char FST(char* str);
	void Add_LT(int line, char token);
	LEX LA(Parm::PARM parm, In::IN in,PreProc::lib);
	bool isCharacterInVector(const std::vector<char>& charVector, char character);
} 