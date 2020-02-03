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

 private:
    // Optimize from node
    bool OptimizeInstance(Expression* expression);

    // Evaluate tree and generate machine operations
    std::string EvaluateTree(Expression* expression, int& token_cnt, int& operation_cnt, std::fstream& file);

    // Optimize tree recursively
    void OptimizeTree(Expression* expression);

    // Compilations
    void SimpleCompilation(Expression* expression, int& token_cnt, int& operation_cnt, std::fstream& file);
    void AdvancedCompilation(Expression* expression, int& token_cnt, int& operation_cnt, std::fstream& file);

    CompilationType compilation_type_;
    Program program_;
    const std::string output_file_;
};
