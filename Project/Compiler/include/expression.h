//
// expression.h
//
// Created by Stefan Stepanovic on 01/23/2020

#pragma once

#include <stdlib.h>
#include <string>
#include <vector>

class Expression
{
 public:
    explicit Expression(const std::string& info);
    virtual ~Expression();

    const std::string Info() const;

    const Expression* Left() const;
    Expression* Left();
    void SetLeft(Expression* left_node);

    const Expression* Right() const;
    Expression* Right();
    void SetRight(Expression* right_node);

    void Print(int start_level = 0) const;

   //  virtual std::string Evaluate();

 protected:
    Expression* left_node_;
    Expression* right_node_;

    const std::string info_;
};

class ConstantExp :public Expression
{
 public:
    explicit ConstantExp(const double value);
    ~ConstantExp();

 private:
    const double value_;
};

class VariableExp : public Expression
{
 public:
    explicit VariableExp(const char name);
    ~VariableExp();

 private:
    const char name_;
};

class OperationExp : public Expression
{
 public:
    explicit OperationExp(const char OperationExp);
    ~OperationExp();

 private:
    const char OperationExp_;
};
