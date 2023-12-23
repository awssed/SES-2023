#pragma once
#include<string>
#include"stdafx.h"
#include"Error.h"
#include"Out.h"
#include<cstring>
#define DIR_INCLUDE "include"
#define DIR_POLISH "polish"
#define OPERATIONS "+", "-", "*", "/", "<", ">", "<=", ">=","=","(",")"
#define FUNC_TOKEN "@"
#define NEW_LINE '|'
using namespace std;
namespace PreProc
{
	struct lib
	{
		string libraries[2];
		int size = 0;
	};
	std::vector<std::string> tokenizeExpression(const std::string& expression);
	int getPriority(string token);
	string infixToPostfix(vector<string> tokens);
	lib Preproc(In::IN &in_result);
}