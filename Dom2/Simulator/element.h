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
    BASE_GENERATOR_TYPE = 0,
    CLOCK_TYPE = 1,
    SIGNAL_GENERATOR_TYPE,
    NOT_ELEMENT_TYPE,
    AND_ELEMENT_TYPE,
    OR_ELEMENT_TYPE,
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

// Parent class for all logical circuit types (abstract)
class LogicalCircuit : public Element
{
 public:
    explicit LogicalCircuit(int element_id, int input_size, ElementType type);
};

// Probe class
class Probe : public Element
{
 public:
    explicit Probe(int element_id);

 private:
    virtual void Run(double time_stamp);
};

// Parent class for all generator types (abstract)
class Generator : public Element
{
 public:
    explicit Generator(int element_id, ElementType type);
    void SetPort(Element* element, int port);
};


