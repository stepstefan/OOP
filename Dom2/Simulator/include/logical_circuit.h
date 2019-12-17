// 
// logical_circuit.h
//
// Created by Stefan Stepanovic on 12/15/2019

#pragma once

#include <vector>

#include "./element.h"

typedef enum LogicalCircuitType
{
   NOT_ELEMENT_TYPE = 3,
   AND_ELEMENT_TYPE,
   OR_ELEMENT_TYPE
} LogicalCircuitType;

// Parent class for all logical circuit types (abstract)
class LogicalCircuit : public Element
{
 public:
    explicit LogicalCircuit(int element_id, int input_size, LogicalCircuitType type);

 protected:
    const LogicalCircuitType log_type_;
 };

class AndElement : public LogicalCircuit
{
 public:
    explicit AndElement(int element_id, int input_size);

 private:
    void Run(const double time_stamp);
};

class OrElement : public LogicalCircuit
{
 public:
    explicit OrElement(int element_id, int input_size);

 private:
    void Run(const double time_stamp);
};

class NotElement : public LogicalCircuit
{
 public:
    explicit NotElement(int element_id);

 private:
    void Run(const double time_stamp);
};
