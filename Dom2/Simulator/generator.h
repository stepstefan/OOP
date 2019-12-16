// 
// generator.h
//
// Created by Stefan Stepanovic on 12/15/2019

#pragma once

#include <vector>

#include "./element.h"

typedef enum GeneratorType
{
   BASE_GENERATOR_TYPE = 0,
   CLOCK_TYPE,
   MANUAL_GENERATOR_TYPE
} GeneratorType;

// Parent class for all generator types (abstract)
class Generator : public Element
{
 public:
    explicit Generator(int element_id, GeneratorType type);
    void SetPort(Element* element, int port);
    std::vector<double> GetChangeTimestamps(double duration);

 protected:
    const GeneratorType gen_type_;

 private:
    virtual std::vector<double> SampleTimestamps(double duration);
};

// Constant output generator
class BaseGenerator : public Generator
{
 public:
    explicit BaseGenerator(int element_id, bool value);

 private:
    void Run(double time_stamp);

 private:
    virtual std::vector<double> SampleTimestamps(double duration);
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
    virtual std::vector<double> SampleTimestamps(double duration);
    const double frequency_;
};

class SignalGenerator : public Generator
{
 public:
    explicit SignalGenerator(int element_id);

 private:
    virtual std::vector<double> SampleTimestamps(double duration);
    void Run(int time_stamp) {}
};
