// 
// element.h
//
// Created by Stefan Stepanovic on 12/15/2019

#pragma once

#include <stdlib.h>
#include <vector>
#include <iostream>

typedef enum ElementType
{
    PROBE_TYPE = 0,
    GENERATOR_TYPE,
    LOGICAL_CIRCUIT_TYPE,
} ElementType;

// Parent element class (abstract)
class Element
{
 public:
    explicit Element(const int element_id, const int input_size, const ElementType type);

    ElementType GetType();
    int GetId();
    bool GetOutput();
    const std::vector<Element*> GetInput();

    // Add connectio to port (excpetion if element is generator!)
    virtual void SetPort(Element* element, const int port);

    // Update output_ value
    void SetOutput(const double timestamp);

    // return timestamps in which element chenges polarity (only for generators!)
    std::vector<double> GetChangeTimestamps(const double duration);

    ~Element();

 protected:
    std::vector<Element*> input_;
    bool output_;
    const int element_id_;
    const ElementType type_;

 private:
    // Run element (update it's output value based on data)
    virtual void Run(const double timestamp) = 0;

    // private virtual function for sampling timestamps
    // to enable redefinition in stacked inheritance
    virtual std::vector<double> SampleTimestamps(const double duration);
};

// Probe class
class Probe : public Element
{
 public:
    explicit Probe(const int element_id);

 private:
    void Run(const double timestamp);
};
