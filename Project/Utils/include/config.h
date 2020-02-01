//
// config.h
//
// Created by Stefan Stepanovic on 01/22/2020

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>

#include "compiler.h"

class Config
{
 public:
    static Config* Instance();

    void Read(const std::string& path);
    const double GetTime(char operation) const;
    const int GetWriteThreads() const;
    CompilationType GetType() const;

 private:
    Config() = default;
    Config(const Config&) = delete;
    Config& operator =(const Config&) = delete;
    Config(Config&) = delete;
    Config& operator =(Config&) = delete;

    static std::unordered_map<char, double> time_table_;
    static CompilationType type_;
    static int parallel_write_;
};