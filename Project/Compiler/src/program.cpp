//
// program.cpp
//
// Created by Stefan Stepanovic on 01/23/2020

#include "../include/program.h"

#include <iostream>
#include <fstream>
#include <stack>

#include "util.h"

Program::Program()
{}

Program::~Program()
{}

void Program::Read(const std::string& path)
{
    std::ifstream input(path);

    if (input.is_open())
    {
        std::string line;
        while (std::getline(input, line))
        {
            expression_strings_.push_back(line);
            variables_.insert(line[0]);
            std::cout << line << std::endl;
        }

        ConvertToTree();
    }
}

const Expression* Program::GetExpression(const size_t idx) const
{
    return expressions_.at(idx);
}

std::vector<Expression*> Program::GetExpressions()
{
    return expressions_;
}


int Program::priority(char OperationExp)
{
    switch (OperationExp)
    {
        case '+' :
            return 1;
            break;
        case '-':
            return 1;
            break;
        case '*':
            return 2;
            break;
        case '/':
            return 2;
            break;
        case '^':
            return 3;
            break;
        case '=':
            return 0;
            break;
    }
}

void Program::ConvertToTree()
{
    for (std::string& infix : expression_strings_)
    {
        std::stack<std::string> input;

        // add elements on stack
        for (size_t i = 0; i < infix.length();)
        {
            std::string elem;
            if (infix[i] != ' ')
            {
                if (internal::IsOperator(infix[i]) || internal::IsParenthesis(infix[i]) || internal::IsVariableExp(infix[i]))
                {
                    elem += infix[i];
                    input.push(elem);
                    i++;
                }
                else
                {
                    while (internal::IsDigit(infix[i]) || infix[i] == '.' || infix[i] == '-')
                    {
                        elem += infix[i++];
                    }
                    input.push(elem);
                }
            }
            else
            {
                i++;
            }
        }

        // bild a tree
        std::string tmp;
        std::stack<Expression*> tree_nodes;
        std::stack<Expression*> operator_nodes;

        while (!input.empty())
        {
            tmp = input.top();
            input.pop();

            if (internal::IsConst(tmp))
            {
                tree_nodes.push(new ConstantExp(std::stod(tmp)));
            }

            if (internal::IsVariableExp(tmp[0]) && (tmp.length() == 1))
            {
                tree_nodes.push(new VariableExp(tmp[0]));
            }

            if (tmp[0] == ')')
            {
                operator_nodes.push(new OperationExp(tmp[0]));
            }

            if (internal::IsOperator(tmp[0]) && (tmp.length() == 1))
            {
                bool pushed = false;
                while (!pushed)
                {
                    if (operator_nodes.empty())
                    {
                        operator_nodes.push(new OperationExp(tmp[0]));
                        pushed = true;
                    }
                    else if (operator_nodes.top()->Info()[0] == ')')
                    {
                        operator_nodes.push(new OperationExp(tmp[0]));
                        pushed = true;
                    }
                    else if (priority(tmp[0]) >= priority(operator_nodes.top()->Info()[0]) && tmp[0] != '^')
                    {
                        operator_nodes.push(new OperationExp(tmp[0]));
                        pushed = true;
                    }
                    else
                    {
                        Expression* op_node = operator_nodes.top();
                        operator_nodes.pop();
                        op_node->SetLeft(tree_nodes.top());
                        tree_nodes.pop();

                        op_node->SetRight(tree_nodes.top());
                        tree_nodes.pop();
                        tree_nodes.push(op_node);
                    }
                }
            }
            if (tmp[0] == '(')
            {
                while (operator_nodes.top()->Info()[0] != ')')
                {
                    Expression* op_node = operator_nodes.top();
                    operator_nodes.pop();
                    op_node->SetLeft(tree_nodes.top());
                    tree_nodes.pop();

                    op_node->SetRight(tree_nodes.top());
                    tree_nodes.pop();
                    tree_nodes.push(op_node);
                }
                operator_nodes.pop();
            }
        }

        while (!operator_nodes.empty())
        {
            Expression* op_node = operator_nodes.top();
            operator_nodes.pop();
            op_node->SetLeft(tree_nodes.top());
            tree_nodes.pop();
            op_node->SetRight(tree_nodes.top());
            tree_nodes.pop();
            tree_nodes.push(op_node);
        }
        expressions_.push_back(tree_nodes.top());
    }
}