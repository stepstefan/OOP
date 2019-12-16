// 
// generator.cpp
//
// Created by Stefan Stepanovic on 12/15/2019

#include "./generator.h"

BaseGenerator::BaseGenerator(int element_id, bool value)
    : Generator(element_id, BASE_GENERATOR_TYPE), value_(value)
{}

void BaseGenerator::Run(double time_stamp)
{
    output_ = value_;
}

Clock::Clock(int element_id, double frequency)
    : Generator(element_id, CLOCK_TYPE), frequency_(frequency)
{}

SignalGenerator::SignalGenerator(int element_id)
    : Generator(element_id, SIGNAL_GENERATOR_TYPE)
{}