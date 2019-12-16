// 
// circuit.h
//
// Created by Stefan Stepanovic on 12/15/2019

#pragma once

#include <vector>
#include <stack>
#include <queue>

#include "./element.h"
#include "./generator.h"
#include "./logical_circuit.h"

class Circuit
{
 public:
    explicit Circuit(int number_of_elements);

    void AddElement(Element* element);
    void AddConnection(int element_id1, int element_id2, int port);
    void Evaluate(double time_stamp);

    std::vector<Element*> elements_;
    std::vector<Element*> probes_;
    int number_of_elements_;
};
