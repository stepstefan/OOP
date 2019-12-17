// 
// generator.cpp
//
// Created by Stefan Stepanovic on 12/15/2019

#include "./generator.h"

// Generator abstract class
Generator::Generator(const int element_id, const GeneratorType type)
    : Element(element_id, 0, ElementType::GENERATOR_TYPE), gen_type_(type)
{
    // nothing to do
}

// override, so it is impossible to set port on generator
void Generator::SetPort(Element* element, const int port)
{
    std::cout << "Cannot set input port of generator!" << std::endl;
    #ifdef _MSC_VER
        throw InvlaidPortException("Cannot set input port of generator!");
    #endif
}

// BASE GENERATOR
BaseGenerator::BaseGenerator(const int element_id, const bool value)
    : Generator(element_id, GeneratorType::BASE_GENERATOR_TYPE), value_(value)
{}

std::vector<double> BaseGenerator::SampleTimestamps(const double duration) const
{
    std::vector<double> timestamps;
    timestamps.push_back(0);
    return timestamps;
}

void BaseGenerator::Run(const double timestamp)
{
    output_ = value_;
}

// CLOCK
Clock::Clock(const int element_id, const double frequency)
    : Generator(element_id, GeneratorType::CLOCK_TYPE), frequency_(frequency)
{}

std::vector<double> Clock::SampleTimestamps(const double duration) const
{
    double time = 0;
    std::vector<double> timestamps;
    while (time < duration)
    {
        timestamps.push_back(time);
        time += (1 / frequency_) / 2;
    }
    return timestamps;
}

void Clock::Run(const double timestamp)
{
    int mul = static_cast<int>(timestamp / ( (1 / frequency_) / 2));
    if (mul % 2 == 0)
    {
        output_ = false;
    }
    else
    {
        output_ = true;
    }
}

// MANUAL GENERATOR
ManualGenerator::ManualGenerator(const int element_id, const std::vector<double>& rel_times)
    : Generator(element_id, GeneratorType::MANUAL_GENERATOR_TYPE), rel_times_(rel_times)
{}

std::vector<double> ManualGenerator::SampleTimestamps(const double duration) const
{
    double time = 0;
    std::vector<double> timestamps;
    int i = 0;
    while (time < duration && i < rel_times_.size())
    {
        timestamps.push_back(time);
        time += rel_times_.at(i++);
    }
    return timestamps;
}

void ManualGenerator::Run(const double timestamp)
{
    bool value = false;
    double time = 0;
    int i = 0;
    for (const double i : rel_times_)
    {
        time += i;
        if (time <= timestamp)
        {
            value = !value;
        }
        else
        {
            break;
        }
    }
    output_ = value;
}
