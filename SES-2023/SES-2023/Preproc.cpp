#include"stdafx.h"

namespace PreProc
{
    int str = 1;
    int col = 0;
    std::vector<std::string> operators = { OPERATIONS};
    std::vector<std::string> useablelibs = { " string.lib"," math.lib" };
    bool searchInVector(const std::vector<std::string>& useablelibs, char* searchTerm)
    {
        for (const std::string& lib : useablelibs)
        {
            if (lib == string(searchTerm))
            {
                return true;
            }
        }

        return false;
    }
    std::vector<std::string> tokenizeExpression(const std::string& expression) {
        std::vector<std::string> tokens;
        std::string currentToken;
        bool NullParm = true;
        char s;
        int i = 0;
        int countOfParms = 0;
        for (char c : expression) {
            if (c == ',') {
                tokens.push_back(currentToken);
                currentToken.clear();
                continue;
            }
            if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '<' || c == '>') {
                if (!currentToken.empty() && c == '(')
                {
                    currentToken += FUNC_TOKEN;
                    for (int j = i; j < expression.size(); j++)
                    {
                        if (expression[j] == ',') {
                            countOfParms++;
                            NullParm = false;
                        }
                        if (expression[j] == ')')
                            break;
                    }
                    if (NullParm)
                    {
                        countOfParms--;
                    }
                    NullParm = true;
                    currentToken += to_string(countOfParms+1);
                    countOfParms = 0;
                    tokens.push_back(currentToken);
                    currentToken.clear();
                }
                if (!currentToken.empty()) {
                    tokens.push_back(currentToken);
                    currentToken.clear();
                }
                tokens.push_back(std::string(1, c));
            }
            else if (c == '=' && currentToken.empty()) {
                if (tokens.back() == "<" || tokens.back() == ">")
                {
                    currentToken = tokens.back();
                    tokens.pop_back();
                    currentToken += c;
                    tokens.push_back(currentToken);
                    currentToken.clear();
                    continue;
                }
                currentToken += c;
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            else if (c != ' ') {
                currentToken += c;
            }
            i++;
        }

        if (!currentToken.empty()) {
            tokens.push_back(currentToken);
        }

        return tokens;
    }
    int getPriority(string token)
    {
        if (token == "+" || token == "-")
            return 1;
        if (token == "*" || token == "/")
            return 2;
        if (token == "<" || token == ">" || token == "<=" || token == ">=")
            return 3;
    }
    string infixToPostfix(vector<string> tokens)
    {
        stack<string> stack;
        string currentToken;
        std::string result;
        int position;
        for (int i = 0; i < tokens.size(); i++)
        {
            currentToken = tokens[i];
            if (find(operators.begin(), operators.end(), currentToken)!=operators.end())
            {
                if (currentToken == "(")
                {
                    stack.push(currentToken);
                    continue;
                }
                if (currentToken == ")")
                {
                    while (stack.top() != "(")
                    {
                        result += stack.top();
                        result += " ";
                        stack.pop();
                        if (stack.empty()) {
                            position = 0;
                            for (int j = 0; j < tokens.size(); j++)
                            {
                                position += tokens[j].length();
                            }
                            throw ERROR_THROW_IN(2, str, position+8);
                        }
                    }
                    stack.pop();
                    continue;
                }
                if (stack.empty() || stack.top() == "(")
                {
                    
                    stack.push(currentToken);
                }
                else if (getPriority(currentToken) < getPriority(stack.top()))
                {
                    while ((getPriority(currentToken) < getPriority(stack.top())))
                    {
                        result += stack.top();
                        result += " ";
                        stack.pop();
                        if (stack.empty())
                            break;
                    }
                    stack.push(currentToken);
                }
                else
                {
                    stack.push(currentToken);
                }
               
            }
            else
            {
                if (currentToken.find('@') != std::string::npos)
                {
                    stack.push(currentToken);
                    i++;
                    //пропускаем открывающеюся скобку
                    i++;
                    currentToken = tokens[i];
                    while(currentToken!=")")
                    { 
                        stack.push(currentToken);
                        i++;
                        currentToken = tokens[i];
                    }
                    while (stack.top().find('@') == std::string::npos)
                    {
                        result += stack.top();
                        result += " ";
                        stack.pop();
                    }
                    stack.top().pop_back();
                    stack.top().pop_back();
                    result += stack.top();
                    result += " ";
                    stack.pop();
                    //убрать оставшиеся скобку
                    currentToken = "";
                }
                result += currentToken;
                result += " ";
            }
        }
        while (!stack.empty())
        {
            if (find(operators.begin(), operators.end(), stack.top()) == operators.end() || stack.top()=="("||stack.top()==")")
            {
                position = 0;
                for (int j = 0; j < tokens.size(); j++)
                {
                    position += tokens[j].length();
                }
                throw ERROR_THROW_IN(2,str,position+8);
            }
            result += stack.top();
            result += " ";
            stack.pop();
        }
        return result;
    }
    lib Preproc(In::IN& in_result)
    {
        char** libraries = nullptr;
        int endPosName = 0;
        int LibraryLen;
        char* libraryName = nullptr;
        int libCount = 0;
        char* expr;
        std::vector<std::string> tokens;
        std::string postfix;
        lib result;
        std::ofstream after("AfterPreproc.txt");
        char* tempBuffer = new char[in_result.size];
        for (int i = 0; i < in_result.size; i++)
        {
            col++;
            if (in_result.text[i] == '|') {
                str++;
                col = 1;
            }
            if (in_result.text[i] == '#')
            {
                if (!strncmp(reinterpret_cast<const char*>(in_result.text + i + 1), DIR_INCLUDE, 7))
                {
                    i += 8;
                    endPosName = i;
                    while (endPosName < in_result.size && in_result.text[endPosName] != NEW_LINE)
                    {
                        endPosName++;
                    }
                    LibraryLen = endPosName - i;
                    libraryName = new char[LibraryLen + 1];
                    strncpy_s(libraryName, LibraryLen + 1, reinterpret_cast<const char*>(in_result.text + i), LibraryLen);
                    libraryName[LibraryLen] = '\0';
                    if (searchInVector(useablelibs, libraryName)) {
                        result.libraries[result.size] = string(libraryName);
                            result.size++;
                    }
                    else {
                        throw ERROR_THROW_IN(3, str, col+9);
                    }
                    //удаляем директиву из исзодного кода
                    memmove(in_result.text + i - 8, in_result.text +endPosName, in_result.size-endPosName);
                    in_result.size = in_result.size - 9 - LibraryLen+1;
                    in_result.text[in_result.size] = '\0';
                    i = i - 9;//возращаем итератор на нужное положение после удаления
                }
                if (!strncmp(reinterpret_cast<const char*>(in_result.text + i + 1), DIR_POLISH, 6))
                {
                    tempBuffer = new char[in_result.size+100];
                    i += 7;
                    endPosName = i;
                    while (endPosName < in_result.size && in_result.text[endPosName] != NEW_LINE)
                    {
                        endPosName++;
                    }
                    expr = new char[endPosName - i];
                    strncpy_s(expr, endPosName-i+1, reinterpret_cast<const char*>(in_result.text + i), endPosName - i);
                    string STR_expr(expr);
                    tokens = tokenizeExpression(STR_expr);
                    postfix=infixToPostfix(tokens);
                    memcpy(tempBuffer, in_result.text , i );
                    memcpy(tempBuffer + i - 7, postfix.c_str(), postfix.size());
                    memcpy(tempBuffer + i - 7 + postfix.size(), (char*)in_result.text + endPosName,in_result.size-endPosName);
                    tempBuffer[i-7+postfix.size()+ in_result.size - endPosName] = '\0';
                    delete[] in_result.text;
                    in_result.text = new unsigned char[strlen(tempBuffer)];
                    memcpy(in_result.text, tempBuffer, strlen(tempBuffer));
                    in_result.size = strlen(tempBuffer);
                    //delete[] tempBuffer;

                }
            }
        }
        for (int q = 0; q < in_result.size; q++)
        {
            if (in_result.text[q] == '|')
            {
                after << endl;
                continue;
            }
            after << in_result.text[q];
        }
        after << endl;
        for (int i = 0; i < result.size; i++)
        {
            after<< "Library " << i << ": " << result.libraries[i] << std::endl;
        }
        after.close();
        lib copy = result;
        return copy;
    }
}