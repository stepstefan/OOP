//
// compiler.cpp
//
// Created by Stefan Stepanovic on 01/30/2019

#include "../include/compiler.h"

#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
#include <unordered_map>

#include "program.h"
#include "expression.h"

#include "util.h"

Compiler::Compiler(CompilationType type, Program& program, const std::string& output_path)
    : compilation_type_(type), program_(program), output_file_(output_path)
{}

std::string Compiler::EvaluateTree(Expression* expression, int& token_cnt, int& operation_cnt, std::fstream& file)
{
    if (!expression->Left() && !expression->Right())
    {
        return expression->Info();
    }
    else
    {
        std::string left_op = EvaluateTree(expression->Left(), token_cnt, operation_cnt, file);
        std::string right_op = EvaluateTree(expression->Right(), token_cnt, operation_cnt, file);
        std::string token = "t" + std::to_string(token_cnt);
        file << "[" << operation_cnt << "] " << expression->Info() << " " << token << " " << left_op << " " << right_op << std::endl;
        token_cnt++;
        operation_cnt++;
        return token;
    }
}

bool EqualComutativeOperators(const std::string& op1, const std::string op2)
{
    return internal::IsOperator(op1) && internal::IsOperator(op2) &&
           (op1[0] == op2[0]) && (op1[0] != '^') && (op1[0] != '/') && (op1[0] != '=');
}


void CreateStack(std::vector<Expression*>& stack, Expression* expression)
{
    if (!internal::IsOperator(expression->Info()))
    {
        stack.push_back(expression);
    }
    else
    {
        if (internal::IsOperator(expression->Left()->Info()))
        {
            if (EqualComutativeOperators(expression->Info(), expression->Left()->Info()))
                CreateStack(stack, expression->Left());
            else
                stack.push_back(expression->Left());
        }
        else
        {
            stack.push_back(expression->Left());
        }

        if (internal::IsOperator(expression->Right()->Info()))
        {
            if (EqualComutativeOperators(expression->Info(), expression->Right()->Info()))
                CreateStack(stack, expression->Right());
            else
                stack.push_back(expression->Right());
        }
        else
        {
            stack.push_back(expression->Right());
        }
    }
}

bool Compiler::OptimizeInstance(Expression* expression)
{
    if (!internal::IsOperator(expression->Info()))
    {
        return false;
    }
    else
    {
        std::vector<Expression* > stack_vector;
        std::string op = expression->Info();

        CreateStack(stack_vector, expression);

        std::unordered_map<std::string, int> occurences;
        for (int i = 0; i < stack_vector.size(); i++)
        {
            if (occurences.find(stack_vector[i]->Info()) != occurences.end())
            {
                occurences[stack_vector[i]->Info()] += 1;
            }
            else
            {
                occurences.insert(std::make_pair(stack_vector[i]->Info(), 1));
            }
        }

        // sort by occurences in this expression
        for (int i = stack_vector.size() - 1; i > 0; i--)
        {
            int id = 0;
            for (int j = 0; j <= i; j++)
            {
                if (occurences[stack_vector[j]->Info()] <= occurences[stack_vector[i]->Info()])
                {
                    id = j;
                }
            }
            Expression* temp = stack_vector[id];
            stack_vector[id] = stack_vector[i];
            stack_vector[i] = temp;
        }

        // if it's meaningful to do it
        if (stack_vector.size() >= 4)
        {
            std::queue<Expression* > queue;
            // add to queue
            for (int i = 0; i < stack_vector.size(); i++)
            {
                queue.push(stack_vector[i]);
            }

            Expression* new_e;
            while (queue.size() > 1)
            {
                std::queue<Expression*> new_queue;
                while (queue.size() > 1)
                {
                    new_e = new Expression(op);
                    new_e->SetLeft(queue.front());
                    queue.pop();
                    new_e->SetRight(queue.front());
                    queue.pop();

                    new_queue.push(new_e);
                }
                if (queue.size() == 1)
                {
                    new_queue.push(queue.front());
                }
                queue = new_queue;
            }
            expression->SetLeft(queue.front()->Left());
            expression->SetRight(queue.front()->Right());
            return true;
        }
        else
        {
            return false;
        }
    }
}

void Compiler::OptimizeTree(Expression* expression)
{
    if (internal::IsOperator(expression->Info()))
    {
        OptimizeTree(expression->Right());
        OptimizeTree(expression->Left());

        OptimizeInstance(expression);
    }
}

void Compiler::SimpleCompilation(Expression* expression, int& token_cnt, int& operation_cnt, std::fstream& file)
{
    // evaluate expression tree on right side of assignment
    std::string value = EvaluateTree(expression->Right(), token_cnt, operation_cnt, file);

    // write assignment operator
    file << "[" << operation_cnt << "] " << expression->Info() << " " << expression->Left()->Info() << " " << value << std::endl;

    operation_cnt++;
}

void Compiler::AdvancedCompilation(Expression* expression, int& token_cnt, int& operation_cnt, std::fstream& file)
{
    // optimize tree for this expression
    OptimizeTree(expression->Right());

    // perform same steps as in simple compilation
    SimpleCompilation(expression, token_cnt, operation_cnt, file);
}

void Compiler::Compile()
{
    int token_cnt = 1;
    int operation_cnt = 1;
    std::fstream file(output_file_, std::ios::out);

    for (Expression* expression : program_.GetExpressions())
    {
        if (expression->Info()[0] != '=' || expression->Info().length() != 1)
        {
            std::cout << "Not an expression" << std::endl;
#ifdef _MSC_VER
            throw NotValidExpression("Invalid Expression!");
#endif
        }
        else
        {
            if (compilation_type_ == CompilationType::ADVANCED_COMPILATION)
            {
                AdvancedCompilation(expression, token_cnt, operation_cnt, file);
            }
            else
            {
                SimpleCompilation(expression, token_cnt, operation_cnt, file);
            }
        }
    }
}