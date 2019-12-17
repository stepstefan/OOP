// 
// generator.cpp
//
// Created by Stefan Stepanovic on 12/15/2019

#include "./generator.h"

// Generator abstract class
Generator::Generator(int element_id, GeneratorType type)
    : Element(element_id, 0, ElementType::GENERATOR_TYPE), gen_type_(type)
{}

void Generator::SetPort(Element* element, const int port)
{
    std::cout << "Cannot set input port of generator!" << std::endl;
}

BaseGenerator::BaseGenerator(int element_id, bool value)
    : Generator(element_id, GeneratorType::BASE_GENERATOR_TYPE), value_(value)
{}

std::vector<double> BaseGenerator::SampleTimestamps(const double duration)
{
    std::vector<double> timestamps;
    timestamps.push_back(0);
    return timestamps;
}

void BaseGenerator::Run(const double timestamp)
{
    output_ = value_;
}

Clock::Clock(int element_id, double frequency)
    : Generator(element_id, GeneratorType::CLOCK_TYPE), frequency_(frequency)
{}

std::vector<double> Clock::SampleTimestamps(const double duration)
{
    double time = 0;
    std::vector<double> timestamps;
    while (time <= duration)
    {
        timestamps.push_back(time);
        time += frequency_;
    }
    return timestamps;
}

void Clock::Run(const double timestamp)
{
    int mul = static_cast<int>(timestamp / frequency_);
    if (mul % 2 == 0)
    {
        output_ = false;
    }
    else
    {
        output_ = true;
    }
}

ManualGenerator::ManualGenerator(const int element_id, const std::vector<double>& rel_times)
    : Generator(element_id, GeneratorType::MANUAL_GENERATOR_TYPE), rel_times_(rel_times)
{}

std::vector<double> ManualGenerator::SampleTimestamps(const double duration)
{
    double time = 0;
    std::vector<double> timestamps;
    int i = 0;
    while (time <= duration && i < rel_times_.size())
    {
        timestamps.push_back(time);
        time += rel_times_.at(i++);
    }
    return timestamps;
}

void ManualGenerator::Run(const double timestamp)
{
    bool value = true;
    double time = 0;
    int i = 0;
    while (time <= timestamp && i < rel_times_.size())
    {
        time += rel_times_.at(i++);
        value = !value;
    }
    output_ = value;
}