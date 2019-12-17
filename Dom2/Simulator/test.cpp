// 
// test.cpp
//
// Created by Stefan Stepanovic on 12/15/2019

#include "./element.h"
#include "./logical_circuit.h"
#include "./generator.h"
#include "./circuit.h"
#include "./simulator.h"


int main()
{
    Circuit circuit(4);
    Clock* gen1 = new Clock(1, 1);
    Clock* gen2 = new Clock(2, 0.5);
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

    // std::cout << gen1->GetOutput() << std::endl;
    // std::cout << gen2->GetOutput() << std::endl;
    // std::cout << note->GetOutput() << std::endl;
    // std::cout << probe->GetOutput() << std::endl;

    Clock* clock = new Clock(10, 0.3);
    std::vector<double> a = gen1->GetChangeTimestamps(2);
    for (auto& x : a)
    {
        std::cout << x << " , ";
    }
    std::cout << std::endl;
    clock->SetOutput(0.5);
    std::cout << "Val " << clock->GetOutput() << std::endl;

    // Element* man = new ManualGenerator(11, std::vector<double>{1, 0.5, 2});
    // std::vector<double> b = man->GetChangeTimestamps(2);
    // for (auto& x : b)
    // {
    //     std::cout << x << " , ";
    // }
    // std::cout << std::endl;
    // man->SetOutput(1.5);
    // std::cout << "Val " << man->GetOutput() << std::endl;

    Simulator sim;
    // sim.circuit_ = &circuit;
    sim.LoadCircuit("/home/stepstefan/ETF/Druga/OOP/Dom2/Main/test_primeri/test_0.txt");

    sim.Simulate("");



    // circuit.Evaluate(2);



    return 0;
}