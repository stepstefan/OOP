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
#include "./exception.h"

class Simulator
{
 public:
    Simulator();
    ~Simulator();

    // Run simulation
    void Simulate(const std::string& filepath);

    // Load Circuit to simulation
    void LoadCircuit(const std::string& filepath);

    // Circuit access
    const Circuit* GetCircuit() const;


 private:
    double duration_;
    Circuit* circuit_;
};
