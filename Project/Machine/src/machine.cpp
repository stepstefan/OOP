//
// machine.cpp
//
// Created by Stefan Stepanovic on 01/22/2020

#include "machine.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

Machine::Machine()
{}

Machine* Machine::Instance()
{
    static Machine* instance = new Machine();
    return instance;
}

bool IsConst(const std::string& s)
{
    for (size_t i = 0; i < s.length(); i++)
    {
        if (!(s[i] == '.' || s[i] == '-' || (s[i] <= '9' && s[i] >= '0')))
        {
            return false;
        }
    }
    return true;
}

Operand* Machine::CreateOperand(std::string& op_string)
{
    if (IsConst(op_string))
    {
        return new Constant(std::stod(op_string));
    }
    else if (op_string.length() == 1 && op_string[0] >= 'a' && op_string[0] <= 'z')
    {
        for (auto& elem : variables_)
        {
            if (elem->Name() == op_string[0])
            {
                return elem;
                break;
            }
        }
        Variable* var = new Variable(op_string[0]);
        variables_.push_back(var);
        return var;
    }
    else if (op_string.length() > 1)
    {
        for (auto& elem : cache_)
        {
            if (!elem->Name().compare(op_string))
            {
                return elem;
                break;
            }
        }
        Token* token = new Token(op_string);
        cache_.push_back(token);
        return token;
    }
}

void Machine::Read(const std::string& path)
{
    std::ifstream input(path);

    if (input.is_open())
    {
        std::string line;
        while (std::getline(input, line))
        {
            std::stringstream stream(line);
            char tmp;
            int id;
            char op;
            std::string operand1, operand2, result;
            stream >> tmp >> id >> tmp >> op;
            if (op != '=')
            {
                stream >> result >> operand1 >> operand2;
                Operation* operation = new Operation(op, Config::Instance()->GetTime(op), id);

                // add result operand
                Operand* result_op = CreateOperand(result);
                operation->SetResult(result_op);
                // add left operand
                Operand* left_op = CreateOperand(operand1);
                operation->SetLeft(left_op);
                // add right operand'
                Operand* right_op = CreateOperand(operand2);
                operation->SetRight(right_op);

                waiting_.insert(operation);
            }
            else
            {
                stream >> operand1 >> operand2;
                Operation* operation = new Operation(op, Config::Instance()->GetTime(op), id);

                // add left operand
                Operand* left_op = CreateOperand(operand1);
                operation->SetLeft(left_op);
                // add right operand'
                Operand* right_op = CreateOperand(operand2);
                operation->SetRight(right_op);

                waiting_.insert(operation);
            }
        }
    }
}

void Machine::FinishOperation(Operation* operation)
{
    bool found = false;
    for (auto& elem : executing_)
    {
        if (elem == operation)
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        finished_.insert(operation);
        executing_.insert(operation);
    }
    else
    {
        std::cout << "No such operation is executing!" << std::endl;
    }
}

void Machine::Execute()
{
    int cnt_w = 0;
    for (auto& operation : waiting_)
    {
        if (operation->Ready())
        {
            if (operation->GetOperation() == '=' && cnt_w < Config::Instance()->GetWriteThreads())
            {
                Event::create(operation, operation->GetTime());
                executing_.insert(operation);
                waiting_.erase(operation);
                // std::cout << operation->GetId() << std::endl;
                cnt_w++;
            }
            else if (operation->GetOperation() != '=')
            {
                Event::create(operation, operation->GetTime());
                executing_.insert(operation);
                waiting_.erase(operation);
            }
        }
    }
    Scheduler::Instance()->processNow();
}