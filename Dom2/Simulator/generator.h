// 
// generator.h
//
// Created by Stefan Stepanovic on 12/15/2019

#pragma once

#include <vector>

#include "./element.h"

// Constant output generator
class BaseGenerator : public Generator
{
 public:
    explicit BaseGenerator(int element_id, bool value);

 private:
    void Run(double time_stamp);

 private:
    bool value_;
};

// Clock generator
class Clock : public Generator
{
 public:
    explicit Clock(int element_id, double frequency);

 private:
    void Run(int time_stamp) {}

 private:
    const double frequency_;
};

class SignalGenerator : public Generator
{
 public:
    explicit SignalGenerator(int element_id);

 private:
    void Run(int time_stamp) {}
};
