//
// memory.h
//
// Created by Stefan Stepanovic on 01/22/2020

#pragma once

#include <string>
#include <unordered_map>

#include "exceptions.h"

class Memory
{
 public:
    static Memory* Instance();

    double Get(char name);
    void Set(char name, double value);
    void Print(const std::string& path) const;

 private:
    Memory() = default;
    Memory(const Memory& ) = delete;
    Memory& operator =(const Memory& ) = delete;
    Memory(Memory& ) = delete;
    Memory& operator =(Memory& ) = delete;

    static std::unordered_map<char, double> table_;

};