// 
// simulator.h
//
// Created by Stefan Stepanovic on 12/15/2019

#pragma once

#include "element.h"
#include "circuit.h"

class Simulator
{
 public:
    explicit Simulator(int duration);

 private:
    int duration_;
};
