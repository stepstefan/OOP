//
// expression.cpp
//
// Created by Stefan Stepanovic on 01/23/2020

#include "expression.h"

#include <stdio.h>
#include <iostream>

Expression::Expression(const std::string& info)
    : info_(info)
{}

Expression::~Expression()
{}

const std::string Expression::Info() const
{
    return info_;
}

const Expression* Expression::Left() const
{
    return left_node_;
}

Expression* Expression::Left()
{
    return left_node_;
}

Expression* Expression::Right()
{
    return right_node_;
}

const Expression* Expression::Right() const
{
    return right_node_;
}

void Expression::SetLeft(Expression* left)
{
    left_node_ = left;
}

void Expression::SetRight(Expression* right)
{
    right_node_ = right;
}

void Expression::Print(int start_level) const
{
    start_level += 10;
    if (right_node_)
    {
        right_node_->Print(start_level);
        start_level++;
    }
    std::cout << std::endl;
    for (int i = 10; i < start_level; ++i) std::cout << ' ';
    std::cout << info_ << std::endl;
    if (left_node_)
    {
        left_node_->Print(start_level);
        start_level++;
    }
}

ConstantExp::ConstantExp(const double value)
    : Expression(std::to_string(value)), value_(value)
{}

ConstantExp::~ConstantExp()
{}

VariableExp::VariableExp(const char name)
    : Expression(std::string(1, name)), name_(name)
{}

VariableExp::~VariableExp()
{}

OperationExp::OperationExp(const char OperationExp)
    : Expression(std::string(1, OperationExp)), OperationExp_(OperationExp)
{}

OperationExp::~OperationExp()
{}