//
// program.h
//
// Created by Stefan Stepanovic on 01/22/2020

#pragma once

#include <stdlib.h>
#include <vector>
#include <string>
#include <set>

#include "expression.h"

class Program
{
 public:
    Program();
    ~Program();
    void Read(const std::string& path);

    const Expression* GetExpression(const size_t idx) const;
    std::vector<Expression*> GetExpressions();


 private:
    void ConvertToTree();

    int priority(char operation);

    std::set<char> variables_;
    std::vector<std::string> expression_strings_;
    std::vector<Expression*> expressions_;
};
