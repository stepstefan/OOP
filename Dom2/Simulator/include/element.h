// 
// element.h
//
// Created by Stefan Stepanovic on 12/15/2019

#pragma once

#include <stdlib.h>
#include <vector>
#include <iostream>

#include "./exception.h"

typedef enum ElementType
{
    PROBE_TYPE = 0,
    GENERATOR_TYPE = -1,
    LOGICAL_CIRCUIT_TYPE = -2,
} ElementType;

// Parent element class (abstract)
class Element
{
 public:
    explicit Element(const int element_id, const int input_size, const ElementType type);

    // Access object fields
    ElementType GetType() const;
    int GetId() const;
    bool GetOutput() const;
    const std::vector<Element*> GetInput() const;

    // Add connectio to port (excpetion if element is generator!)
    virtual void SetPort(Element* element, const int port);

    // Update output_ value
    void SetOutput(const double timestamp);

    // return timestamps in which element chenges polarity (only for generators!)
    std::vector<double> GetChangeTimestamps(const double duration) const;

    ~Element();

 protected:
    std::vector<Element*> input_;
    bool output_;
    const int element_id_;
    const ElementType type_;

 private:
    // private virtual function for sampling timestamps
    // to enable redefinition in stacked inheritance

    // Run element (update it's output value based on data)
    virtual void Run(const double timestamp) = 0;

    // sample timestamps for Element::GetChangeTimestamps
    virtual std::vector<double> SampleTimestamps(const double duration) const;
};

// Probe class
class Probe : public Element
{
 public:
    explicit Probe(const int element_id);

 private:
    void Run(const double timestamp);
};
