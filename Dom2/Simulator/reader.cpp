// 
// simulator.h
//
// Created by Stefan Stepanovic on 12/15/2019

#include "./reader.h"

Reader::Reader()
{}

Reader::~Reader()
{}

Reader& Reader::GetInstance()
{
    // Guaranteed to be destroyed
    static Reader instance;
    return instance;
}

void Reader::SetPath(const std::string& path)
{
    path_ = path;
}

double Reader::GetDuration()
{
    return duration_;
}

int Reader::GetNumberOfElements()
{
    return number_of_elements_;
}

Circuit* Reader::ReadCircuit()
{
    std::ifstream input(path_);
    if (input.is_open())
    {
        input >> duration_;
        input >> number_of_elements_;
        std::cout << duration_ << " " << number_of_elements_ << std::endl;

        Circuit* circuit = new Circuit(number_of_elements_);

        std::string line;
        // finish reading first line
        std::getline(input, line);
        // read elements
        for (int i = 0; i < number_of_elements_; i++)
        {
            std::getline(input, line);
            std::istringstream string_stream(line);
            int type, id;
            string_stream >> id >> type;

            // helper values for switch
            int input_size;
            double frequency;
            double time;
            std::vector<double> rel_times(0);
            switch (type)
            {
                case GeneratorType::CLOCK_TYPE:
                    string_stream >> frequency;
                    circuit->AddElement(new Clock(id, frequency));
                    break;

                case GeneratorType::MANUAL_GENERATOR_TYPE:
                    while (string_stream >> time)
                    {
                        rel_times.push_back(time);
                    }
                    circuit->AddElement(new ManualGenerator(id, rel_times));
                    break;

                case LogicalCircuitType::OR_ELEMENT_TYPE:
                    string_stream >> input_size;
                    circuit->AddElement(new OrElement(id, input_size));
                    break;

                case LogicalCircuitType::AND_ELEMENT_TYPE:
                    string_stream >> input_size;
                    circuit->AddElement(new AndElement(id, input_size));
                    break;

                case LogicalCircuitType::NOT_ELEMENT_TYPE:
                    circuit->AddElement(new NotElement(id));
                    break;

                case ElementType::PROBE_TYPE:
                    circuit->AddElement(new Probe(id));
                    break;
            }
        }

        // load connections
        while (std::getline(input, line))
        {
            int element_id1, element_id2, port;
            std::istringstream string_stream(line);
            string_stream >> element_id1 >> element_id2 >> port;
            circuit->AddConnection(element_id1, element_id2, port);
        }

        return circuit;
    }
}
