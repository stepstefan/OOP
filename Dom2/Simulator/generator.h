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
    void SetPort(Element* element, const int port);

 protected:
    const GeneratorType gen_type_;

 private:
    virtual std::vector<double> SampleTimestamps(const double duration) = 0;
};

// Constant output generator
class BaseGenerator : public Generator
{
 public:
    explicit BaseGenerator(int element_id, bool value);

 private:
    void Run(const double time_stamp);
    std::vector<double> SampleTimestamps(const double duration);

    bool value_;
};

// Clock generator
class Clock : public Generator
{
 public:
    explicit Clock(int element_id, double frequency);

 private:
    void Run(const double timestamp);
    std::vector<double> SampleTimestamps(const double duration);

    const double frequency_;
};

class ManualGenerator : public Generator
{
 public:
    explicit ManualGenerator(const int element_id, const std::vector<double>& rel_times);

 private:
    std::vector<double> SampleTimestamps(const double duration);
    void Run(const double timestamp);

    const std::vector<double> rel_times_;
};
