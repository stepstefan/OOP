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
    
    // denote start of writting process
    void StartWriteProcess();
    // denote end of writting process
    void EndWriteProcess();
    // check if there are available write slots
    bool AvailableWriteProcess(int max);

 private:
    Memory() = default;
    Memory(const Memory& ) = delete;
    Memory& operator =(const Memory& ) = delete;
    Memory(Memory& ) = delete;
    Memory& operator =(Memory& ) = delete;

    static std::unordered_map<char, double> table_;
    static int current_write_;

};