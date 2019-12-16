// 
// generator.cpp
//
// Created by Stefan Stepanovic on 12/15/2019

#include "./generator.h"

// Generator abstract class
Generator::Generator(int element_id, GeneratorType type)
    : Element(element_id, 0, ElementType::GENERATOR_TYPE), gen_type_(type)
{}

std::vector<double> Generator::GetChangeTimestamps(double duration)
{
    return this->SampleTimestamps(duration);
}

void Generator::SetPort(Element* element, int port)
{
    std::cout << "Cannot set input port of generator!" << std::endl;
}

BaseGenerator::BaseGenerator(int element_id, bool value)
    : Generator(element_id, GeneratorType::BASE_GENERATOR_TYPE), value_(value)
{}

std::vector<double> BaseGenerator::SampleTimestamps(double duration)
{
    std::vector<double> timestamps(0);
    timestamps.push_back(0);
}

void BaseGenerator::Run(double time_stamp)
{
    output_ = value_;
}

Clock::Clock(int element_id, double frequency)
    : Generator(element_id, GeneratorType::CLOCK_TYPE), frequency_(frequency)
{}

SignalGenerator::SignalGenerator(int element_id)
    : Generator(element_id, GeneratorType::MANUAL_GENERATOR_TYPE)
{}
