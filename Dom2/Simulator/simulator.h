// 
// simulator.h
//
// Created by Stefan Stepanovic on 12/15/2019

#pragma once

#define EPSILON 1e-10

#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

#include "./element.h"
#include "./generator.h"
#include "./logical_circuit.h"
#include "./circuit.h"
#include "./reader.h"
#include "./writer.h"

class Simulator
{
 public:
    Simulator();

    void Simulate(const std::string& filepath);
    void LoadCircuit(const std::string& filepath);

    Circuit* circuit_;

 private:
    double duration_;
};
