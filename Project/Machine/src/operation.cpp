//
// operation.cpp
//
// Created by Stefan Stepanovic on 01/22/2020

#include "operation.h"

#include <cmath>
#include <iostream>

#include "machine.h"
#include "logger.h"


Operand::Operand()
{}

Constant::Constant(const double value)
    : value_(value)
{}

bool Constant::Ready() const
{
    return true;
}

double Constant::Evaluate() const
{
    return value_;
}

void Constant::SetValue(const double)
{}

Variable::Variable(const char name)
    : name_(name), ready_(false)
{}

const char Variable::Name() const
{
    return name_;
}

bool Variable::Ready() const
{
    return ready_;
}

double Variable::Evaluate() const
{
    return Memory::Instance()->Get(name_);
}

void Variable::SetValue(const double value)
{
    Memory::Instance()->Set(name_, value);
    ready_ = true;
}

Token::Token(const std::string& name)
    : name_(name), ready_(false), value_(std::numeric_limits<double>::quiet_NaN())
{}

std::string Token::Name()
{
    return name_;
}

bool Token::Ready() const
{
    return ready_;
}

double Token::Evaluate() const
{
    return value_;
}

void Token::SetValue(const double value)
{
    value_ = value;
    ready_ = true;
}

Operation::Operation(char operation, double time, int id)
    : operation_(operation), time_(time), id_(id)
{}

void Operation::SetLeft(Operand* left)
{
    left_operand_ = left;
}

void Operation::SetResult(Operand* result)
{
    result_ = result;
}

void Operation::SetRight(Operand* right)
{
    right_operand_ = right;
}

Operand* Operation::GetLeft()
{
    return left_operand_;
}

Operand* Operation::GetRight()
{
    return right_operand_;
}

const double Operation::GetTime() const
{
    return time_;
}

const int Operation::GetId() const
{
    return id_;
}

const char Operation::GetOperation() const
{
    return operation_;
}

bool Operation::Ready() const
{
    if (operation_ == '=')
    {
        return right_operand_->Ready();
    }
    else
    {
        return (left_operand_->Ready() && right_operand_->Ready());
    }
}

void Operation::Evaluate()
{
    if (this->Ready())
    {
        switch (operation_)
        {
        case '+':
            result_->SetValue(left_operand_->Evaluate() + right_operand_->Evaluate());
            break;
        case '*':
            result_->SetValue(left_operand_->Evaluate() * right_operand_->Evaluate());
            break;
        case '^':
            result_->SetValue(std::pow(left_operand_->Evaluate(), right_operand_->Evaluate()));
            break;
        case '=':
            left_operand_->SetValue(right_operand_->Evaluate());
            Memory::Instance()->EndWriteProcess();
            break;
        default:
            break;
        }
    }
}

void Operation::notify(ID id)
{
    this->Evaluate();
    Machine::Instance()->FinishOperation(this);

    std::string line = "";
    line = line + "[" + std::to_string(id_) + "]\t\t(" + std::to_string(Scheduler::Instance()->getCurTime() - time_) + "-" + std::to_string(Scheduler::Instance()->getCurTime()) + ")ns";

    std::cout << line << std::endl;
    Logger::Instance()->Print(line);
    Machine::Instance()->Execute();
}


