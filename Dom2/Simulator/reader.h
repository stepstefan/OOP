// 
// simulator.h
//
// Created by Stefan Stepanovic on 12/15/2019

#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "./element.h"
#include "./generator.h"
#include "./logical_circuit.h"
#include "./circuit.h"

class Reader
{
 public:
    static Reader& GetInstance();
    ~Reader();

    double GetDuration();
    int GetNumberOfElements();
    Circuit* ReadCircuit();
    void SetPath(const std::string& path);

    Reader(Reader const&) = delete;
    void operator=(Reader const&) = delete;

 private:
    std::string path_;
    double duration_;
    int number_of_elements_;
    Reader();
};
