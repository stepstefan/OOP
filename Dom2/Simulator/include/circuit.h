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
    explicit Circuit(const int number_of_elements);
    ~Circuit();

    // Add element to circuit
    void AddElement(Element* element);

    // Add connection to circuit.
    // Output element_id1 to input of element_id2 on port port
    void AddConnection(const int element_id1, const int element_id2, const int port);

    // Evaluate circuit (find all probe values) in given timestamp
    std::vector<bool> Evaluate(const double time_stamp);

    // return list of generators and probes
    const std::vector<Element*> GetGenerators() const;
    const std::vector<Element*> GetProbes() const;

 private:
    std::vector<Element*> elements_;
    std::vector<Element*> probes_;
    std::vector<Element*> generators_;
    const int number_of_elements_;
};
