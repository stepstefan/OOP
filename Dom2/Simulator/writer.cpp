// 
// writer.h
//
// Created by Stefan Stepanovic on 12/17/2019

#include "./writer.h"

// Empty constructor, it's private anyway
Writer::Writer()
{}

// empty destructor, fields will be destroyed when object goes out of scope
Writer::~Writer()
{}

// returns instance to singleton
Writer& Writer::GetInstance()
{
    // Guaranteed to be destroyed
    static Writer instance;
    return instance;
}

void Writer::SetPath(const std::string& path)
{
    path_ = path;
}

void Writer::WriteOutput(const std::vector<double>& timestamps,
                         const std::vector<std::vector<bool>>& values,
                         const std::vector<Element*>& probes)
{
    for (size_t i = 0; i < probes.size(); i++)
    {
        // previous value for probe;
        bool prev_value = false;

        // postion of dot in path
        size_t dot_pos = 0;
        dot_pos = path_.find('.');
        // if dot exists in path
        if (dot_pos != std::string::npos)
        {
            std::string file_path = path_.substr(0, dot_pos);
            file_path += "_" + std::to_string(probes.at(i)->GetId()) + ".txt";
            std::ofstream file(file_path);
            if (file.is_open())
            {
                for (size_t j = 0; j < timestamps.size(); j++)
                {
                    bool new_value = values.at(j).at(i);
                    if (new_value != prev_value)
                    {
                        file << prev_value << " -> " << new_value << ": " << timestamps.at(j) << "us" << std::endl;
                        prev_value = new_value;
                    }
                }
            }
        }
        else
        {
            std::cout << "Invalid path" << std::endl;
        }
    }
}
