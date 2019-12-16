// 
// logica_circuit.h
//
// Created by Stefan Stepanovic on 12/15/2019

#pragma once

#include <vector>

#include "./element.h"


class AndElement : public LogicalCircuit
{
 public:
    explicit AndElement(int element_id, int input_size);

 private:
    void Run(double time_stamp);
};

class OrElement : public LogicalCircuit
{
 public:
    explicit OrElement(int element_id, int input_size);

 private:
    void Run(double time_stamp);
};

class NotElement : public LogicalCircuit
{
 public:
    explicit NotElement(int element_id);

 private:
    void Run(double time_stamp);
};
