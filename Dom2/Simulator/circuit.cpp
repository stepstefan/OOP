// 
// circuit.cpp
//
// Created by Stefan Stepanovic on 12/15/2019

#include "./circuit.h"
#include "./element.h"
#include "./generator.h"
#include "./logical_circuit.h"

Circuit::Circuit(int number_of_elements)
    : number_of_elements_(number_of_elements)
{
    // just reserve memory
    elements_.reserve(number_of_elements);
}

void Circuit::AddElement(Element* element)
{
    if (elements_.size() < number_of_elements_)
    {
        elements_.push_back(element);
        if (element->GetType() == PROBE_TYPE)
        {
            probes_.push_back(element);
        }
    }
    else
    {
        std::cout << "All elements are already added!" << std::endl;
    }
}

void Circuit::AddConnection(int element_id1, int element_id2, int port)
{
    Element* element1 = nullptr;
    Element* element2 = nullptr;
    for (const auto& element : elements_)
    {
        if (element->GetId() == element_id1)
        {
            element1 = element;
        }
        if (element->GetId() == element_id2)
        {
            element2 = element;
        }
    }

    if (element1 == nullptr || element2 == nullptr)
    {
        std::cout << "Elements do not exist!" << std::endl;
    }
    else
    {
        element2->SetPort(element1, port);
    }
}

void Circuit::Evaluate(double time_stamp)
{
    for (auto& probe : probes_)
    {
        // Create operator stack for specific probe
        std::stack<Element*> stack;
        std::queue<Element*> to_add;
        to_add.push(probe);
        while (!to_add.empty())
        {
            stack.push(to_add.front());
            std::cout << to_add.front()->GetId();
            for (int i = 0; i < to_add.front()->GetInput().size(); i++)
            {
                to_add.push(to_add.front()->GetInput().at(i));
            }
            to_add.pop();
        }
        std::cout << std::endl;

        while (!stack.empty())
        {
            std::cout << "Setting " << stack.top()->GetId();
            Element* elem = stack.top();
            elem->SetOutput(time_stamp);
            std::cout << " to " << stack.top()->GetOutput() << std::endl;
            stack.pop();
        }
        std::cout << "Probe" << probe->GetOutput() << std::endl;
    }
}
