//
// logger.h
//
// Created by Stefan Stepanovic on 01/22/2020

#pragma once

#include <fstream>
#include <iostream>
#include <stdlib.h>

class Logger
{
 public:
    static Logger* Instance();

    bool SetOutput(const std::string& path);
    void Print(const std::string& line);

 private:
    Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator =(const Logger&) = delete;

    static std::ofstream output_;
};