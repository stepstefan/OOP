// 
// logical_circuit.cpp
//
// Created by Stefan Stepanovic on 12/15/2019

#include "./logical_circuit.h"

// AND ELEMENT
AndElement::AndElement(int element_id, int input_size)
    : LogicalCircuit(element_id, input_size, AND_ELEMENT_TYPE)
{}

void AndElement::Run(double time_stamp)
{
    bool value = input_.at(0)->GetOutput();
    for (int i = 1; i < input_.size(); i++)
    {
        value = value && input_.at(i)->GetOutput();
    }
    output_ = value;
}

// OR ELEMENT
OrElement::OrElement(int element_id, int input_size)
    : LogicalCircuit(element_id, input_size, OR_ELEMENT_TYPE)
{}

void OrElement::Run(double time_stamp)
{
    bool value = input_.at(0)->GetOutput();
    for (int i = 1; i < input_.size(); i++)
    {
        value = value || input_.at(i)->GetOutput();
    }
    output_ = value;
}

// NOT ELEMENT
NotElement::NotElement(int element_id)
    : LogicalCircuit(element_id, 1, NOT_ELEMENT_TYPE)
{}

void NotElement::Run(double time_stamp)
{
    output_ = !(input_.at(0)->GetOutput());
}

