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
    GENERATOR_TYPE,
    LOGICAL_CIRCUIT_TYPE,
    PROBE_TYPE
} ElementType;

// Parent element class (abstract)
class Element
{
 public:
    explicit Element(int element_id, int input_size, ElementType type);

    ElementType GetType();
    int GetId();
    bool GetOutput();
    const std::vector<Element*> GetInput();

    virtual void SetPort(Element* element, int port);
    void SetOutput(double time_stamp);

    ~Element();

 protected:
    std::vector<Element*> input_;
    bool output_;
    const int element_id_;
    const ElementType type_;

 private:
    virtual void Run(double time_stamp) = 0;
};

// Probe class
class Probe : public Element
{
 public:
    explicit Probe(int element_id);

 private:
    virtual void Run(double time_stamp);
};
