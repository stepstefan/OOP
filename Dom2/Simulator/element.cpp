// 
// element.cpp
//
// Created by Stefan Stepanovic on 12/15/2019

#include "./element.h"

// Element abstract class
Element::Element(const int element_id, const int input_size, const ElementType type)
    : element_id_(element_id), input_(input_size), type_(type)
{}

Element::~Element()
{}

ElementType Element::GetType()
{
    return type_;
}

int Element::GetId()
{
    return element_id_;
}

bool Element::GetOutput()
{
    return output_;
}

void Element::SetOutput(const double timestamp)
{
    this->Run(timestamp);
}

const std::vector<Element*> Element::GetInput()
{
    return input_;
}


void Element::SetPort(Element* element, int port)
{
    if ((port >= input_.size()) || (port < 0))
    {
        std::cout << "Invalid port!" << std::endl;
    }
    else
    {
        if (input_.at(port) != nullptr)
        {
            std::cout << "Port is already assigned!" << std::endl;
        }
        else
        {
            input_.at(port) = element;
        }
    }
}

std::vector<double> Element::SampleTimestamps(const double duration)
{
    if (type_ != ElementType::GENERATOR_TYPE)
    {
        std::cout << "Not generator" << std::endl;
        // TODO(stefan): Exception
    }
    return std::vector<double>();
}

std::vector<double> Element::GetChangeTimestamps(const double duration)
{
    return this->SampleTimestamps(duration);
}

// Probe class
Probe::Probe(const int element_id)
    : Element(element_id, 1, PROBE_TYPE)
{}

void Probe::Run(const double time_stamp)
{
    output_ = input_.at(0)->GetOutput();
}
