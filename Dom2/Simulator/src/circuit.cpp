//
// circuit.cpp
//
// Created by Stefan Stepanovic on 12/15/2019

#include "./circuit.h"
#include "./element.h"
#include "./generator.h"
#include "./logical_circuit.h"

Circuit::Circuit(const int number_of_elements)
    : number_of_elements_(number_of_elements)
{
    // just reserve memory
    elements_.reserve(number_of_elements);
}

Circuit::~Circuit()
{
    for (auto& elem : elements_)
    {
        free(elem);
    }
    // rest will self-destruct
}

const std::vector<Element*> Circuit::GetGenerators() const
{
    return generators_;
}

const std::vector<Element*> Circuit::GetProbes() const
{
    return probes_;
}

void Circuit::AddElement(Element* element)
{
    // check if all elements have been added
    if (elements_.size() < number_of_elements_)
    {
        elements_.push_back(element);
        // add pointer to vector of probes
        if (element->GetType() == ElementType::PROBE_TYPE)
        {
            probes_.push_back(element);
        }
        // add pointer to vector of generators
        if (element->GetType() == ElementType::GENERATOR_TYPE)
        {
            generators_.push_back(element);
        }
    }
    else
    {
        std::cout << "All elements are already added!" << std::endl;
        #ifdef _MSC_VER
            throw AllElementsAddedException("All elements have been added to circuit");
        #endif
    }
}

void Circuit::AddConnection(const int element_id1, const int element_id2, const int port)
{
    Element* element1 = nullptr;
    Element* element2 = nullptr;
    // find elements by their id
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
        std::string error = "Elements " + std::to_string(element_id1) + " and " + std::to_string(element_id2) + "do not exist!";
        std::cout << error << std::endl;
        #ifdef _MSC_VER
            throw InvalidElementsException(error.c_str());
        #endif
    }
    else
    {
        element2->SetPort(element1, port);
    }
}

std::vector<bool> Circuit::Evaluate(const double timestamp)
{
    std::vector<bool> outputs;

    // Evaluate for all probes
    for (auto& probe : probes_)
    {
        // Create operator stack for specific probe
        std::stack<Element*> stack;
        std::queue<Element*> to_add;
        to_add.push(probe);
        while (!to_add.empty())
        {
            stack.push(to_add.front());
            for (int i = 0; i < to_add.front()->GetInput().size(); i++)
            {
                to_add.push(to_add.front()->GetInput().at(i));
            }
            to_add.pop();
        }

        // iterative evaluation of stack
        while (!stack.empty())
        {
            Element* elem = stack.top();
            elem->SetOutput(timestamp);
            stack.pop();
        }
        outputs.push_back(probe->GetOutput());
    }
    return outputs;
}
