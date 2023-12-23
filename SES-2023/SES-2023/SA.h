#pragma once
#include "stdafx.h"
#include"IT.h"
#include"LT.h"
#include"Error.h"

namespace SA
{
	void addVars(int i, LT::LexTable& lextable, IT::IdTable& idtable);
	int checkIfWhile(int i, LT::LexTable& lextable, IT::IdTable& idtable);
	void checkVars();
	void Semantic_Analyzer(LT::LexTable& lextable, IT::IdTable& idtable);
	void addSizeToArray(int i, LT::LexTable& lextable, IT::IdTable& idtable);
	void checkSizeofArray(int i, LT::LexTable& lextable, IT::IdTable& idtable);
}