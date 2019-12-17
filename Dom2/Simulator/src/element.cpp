// 
// element.cpp
//
// Created by Stefan Stepanovic on 12/15/2019

#include "./element.h"

// Element abstract class
Element::Element(const int element_id, const int input_size, const ElementType type)
    : element_id_(element_id), input_(input_size), type_(type)
{
    // nothing to do
}

Element::~Element()
{
    // nothing to do
}

ElementType Element::GetType() const
{
    return type_;
}

int Element::GetId() const
{
    return element_id_;
}

bool Element::GetOutput() const
{
    return output_;
}

void Element::SetOutput(const double timestamp)
{
    this->Run(timestamp);
}

const std::vector<Element*> Element::GetInput() const
{
    return input_;
}


void Element::SetPort(Element* element, int port)
{
    if ((port >= input_.size()) || (port < 0))
    {
        std::string error = "Port out of bounds on element " + std::to_string(element->GetId()) + ", port " + std::to_string(port);
        #ifdef _MSC_VER
            throw InvalidPortException(error.c_str());
        #endif
        std::cout << error << std::endl;
    }
    else
    {
        if (input_.at(port) != nullptr)
        {
            std::string error = "Port already assigned on element " + std::to_string(element->GetId()) + ", port " + std::to_string(port);
            #ifdef _MSC_VER
                throw InvalidPortException(error.c_str());
            #endif
            std::cout << error << std::endl;
        }
        else
        {
            input_.at(port) = element;
        }
    }
}

std::vector<double> Element::SampleTimestamps(const double duration) const
{
    // in case it's not specialized to generator, return empty vector/throw exception
    if (type_ != ElementType::GENERATOR_TYPE)
    {
        std::string error = "Element " + std::to_string(this->GetId()) + " is not a generator";
        #ifdef _MSC_VER
            throw NotGeneratorException(error.c_str());
        #endif
        std::cout << error << std::endl;
    }
    return std::vector<double>();
}

std::vector<double> Element::GetChangeTimestamps(const double duration) const
{
    // will propaget exception onn Element::SampleTimestamps
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
