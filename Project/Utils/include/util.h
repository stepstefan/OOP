//
// util.h
//
// Created by Stefan Stepanovic on 01/22/2019

#pragma once

#include <string>
#include <stdlib.h>

namespace internal
{
bool IsVariableExp(char s);

bool IsVariable(const std::string& s);

bool IsOperator(char s);

bool IsOperator(const std::string& s);

bool IsParenthesis(char s);

bool IsDigit(char s);

bool IsConst(std::string s);
}