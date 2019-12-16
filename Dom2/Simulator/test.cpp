// 
// test.cpp
//
// Created by Stefan Stepanovic on 12/15/2019

#include "./element.h"
#include "./logical_circuit.h"
#include "./generator.h"
#include "./circuit.h"


int main()
{
    Circuit circuit(4);
    BaseGenerator* gen1 = new BaseGenerator(1, 0);
    BaseGenerator* gen2 = new BaseGenerator(2, 1);
    OrElement* note = new OrElement(3, 2);
    Probe* probe = new Probe(4);
    circuit.AddElement(note);
    circuit.AddElement(gen1);
    circuit.AddElement(gen2);
    circuit.AddElement(probe);

    circuit.AddConnection(1, 3, 0);
    circuit.AddConnection(2, 3, 1);
    circuit.AddConnection(3, 4, 0);

    // circuit.elements_.at(1)->SetOutput(1);
    // circuit.elements_.at(2)->SetOutput(1);
    // circuit.elements_.at(0)->SetOutput(1);
    // circuit.elements_.at(3)->SetOutput(1);

    std::cout << gen1->GetOutput() << std::endl;
    std::cout << gen2->GetOutput() << std::endl;
    std::cout << note->GetOutput() << std::endl;
    std::cout << probe->GetOutput() << std::endl;

    circuit.Evaluate(2);



    return 0;
}