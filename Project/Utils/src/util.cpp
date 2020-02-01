//
// util.cpp
//
// Created by Stefan Stepanovic on 01/22/2019

#include "util.h"

namespace internal
{
bool IsVariableExp(char s)
{
    return ('a' <= s) && (s <= 'z');
}

bool IsVariable(const std::string& s)
{
    return (s.length() == 1) && IsVariableExp(s[0]);
}

bool IsOperator(char s)
{
    return (s == '+') || (s == '*') || (s == '=') || (s == '^');
}

bool IsOperator(const std::string& s)
{
    return (s.length() == 1) && IsOperator(s[0]);
}

bool IsParenthesis(char s)
{
    return (s == ')') || (s == '(');
}

bool IsDigit(char s)
{
    return ('0' <= s) && ('9' >= s);
}

bool IsConst(std::string s)
{
    bool res = true;
    for (size_t i = 0; i < s.length(); i++)
    {
        res = res && (IsDigit(s[i]) || s[i] == '.' || s[i] == '-');
    }
    return res;
}
}