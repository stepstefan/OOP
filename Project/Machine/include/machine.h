//
// operation.h
//
// Created by Stefan Stepanovic on 01/22/2020

#pragma once

#include <vector>
#include <set>
#include <string>
#include <unordered_map>

#include "operation.h"
#include "config.h"
class Machine
{
 public:
    static Machine* Instance();
    void Read(const std::string& path);

    void FinishOperation(Operation*);

    void Execute();

 private:
    Machine();
    Machine(const Machine& ) = delete;
    Machine& operator =(const Machine& ) = delete;
    Machine(Machine& ) = delete;
    Machine& operator =(Machine& ) = delete;

    Operand* CreateOperand(std::string&);


    std::set<Operation* > waiting_;
    std::set<Operation* > executing_;
    std::set<Operation* > finished_;

    std::vector<Token*> cache_;
    std::vector<Variable*> variables_;
};