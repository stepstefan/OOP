//
// memory.cpp
//
// Created by Stefan Stepanovic on 01/22/2020

#include "memory.h"
#include <limits>
#include <iostream>
#include <fstream>
#include <unordered_map>

std::unordered_map<char, double> Memory::table_;
int Memory::current_write_ = 0;

Memory* Memory::Instance()
{
    Memory* instance = new Memory();
    return instance;
}

void Memory::Set(char name, double value)
{
    bool found = false;
    for (auto& elem : table_)
    {
        if (elem.first == name)
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        table_.insert(std::make_pair(name, value));
    }
    else
    {
        table_.at(name) = value;
    }
}

double Memory::Get(char name)
{
    bool found = false;
    for (auto& elem : table_)
    {
        if (elem.first == name)
        {
            found = true;
            break;
        }
    }
    if (found)
    {
        return table_.at(name);
    }
    else
    {
#ifdef _MSC_VER
        throw VarNotAvailable(std::string(1, name) + " does not exist!");
#endif

    }
}

void Memory::Print(const std::string& path) const
{
    std::ofstream file(path);

    if (file)
    {
        for (const auto& elem : table_)
        {
            file << elem.first << " = " << elem.second << std::endl;
        }
    }
}

void Memory::StartWriteProcess()
{
    current_write_++;
}

void Memory::EndWriteProcess()
{
    current_write_--;
}

bool Memory::AvailableWriteProcess(int max)
{
    return current_write_ < max;
}