// 
// generator.h
//
// Created by Stefan Stepanovic on 12/15/2019

#pragma once

#include <vector>

#include "./element.h"
#include "./exception.h"

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
    explicit Generator(const int element_id, const GeneratorType type);
    void SetPort(Element* element, const int port);

 protected:
    const GeneratorType gen_type_;

 private:
    virtual std::vector<double> SampleTimestamps(const double duration) const = 0;
};

// Constant output generator
class BaseGenerator : public Generator
{
 public:
    explicit BaseGenerator(const int element_id, const bool value);

 private:
    void Run(const double time_stamp);
    std::vector<double> SampleTimestamps(const double duration) const;

    bool value_;
};

// Clock generator
class Clock : public Generator
{
 public:
    explicit Clock(const int element_id, const double frequency);

 private:
    void Run(const double timestamp);
    std::vector<double> SampleTimestamps(const double duration) const;

    const double frequency_;
};

class ManualGenerator : public Generator
{
 public:
    explicit ManualGenerator(const int element_id, const std::vector<double>& rel_times);

 private:
    void Run(const double timestamp);
    std::vector<double> SampleTimestamps(const double duration) const;

    const std::vector<double> rel_times_;
};
