//
// compiler.h
//
// Created by Stefan Stepanovic on 01/22/2019

#pragma once

#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "program.h"

enum class CompilationType
{
    SIMPLE_COMPILATION = 0,
    ADVANCED_COMPILATION
};

class Compiler
{
 public:
    explicit Compiler(CompilationType compilation_type, Program& program, const std::string& output_path);
    void Compile();

    std::string EvaluateTree(Expression* expression, int& token_cnt, int& operation_cnt, std::fstream& file);

    void OptimizeTree(Expression* expression);

 private:
    bool IsCalculable(std::string& expression);
    bool OptimizeInstance(Expression* expression);

    CompilationType compilation_type_;
    Program program_;
    const std::string output_file_;
    std::set<char> calculated_variables_;
};
