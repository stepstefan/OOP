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
                         const std::vector<Element*>& probes) const
{
    // iterate trough all probes whose output needs to be saved
    for (size_t i = 0; i < probes.size(); i++)
    {
        // previous value for probe;
        bool prev_value = false;

        // parse base path form and create sufficient file name for specific probe
        // postion of dot in path
        size_t dot_pos = 0;
        dot_pos = path_.find('.');
        // if dot exists in path
        if (dot_pos != std::string::npos)
        {
            // create file name for specific probe
            std::string file_path = path_.substr(0, dot_pos);
            file_path += "_" + std::to_string(probes.at(i)->GetId()) + ".txt";

            std::ofstream file(file_path);
            if (file.is_open())
            {
                // iterate through all timestamps
                for (size_t j = 0; j < timestamps.size(); j++)
                {
                    bool new_value = values.at(j).at(i);
                    // if value has changed with respect to previous value
                    // write that event
                    if (new_value != prev_value)
                    {
                        file << prev_value << " -> " << new_value << ": " << timestamps.at(j) << "us" << std::endl;
                        prev_value = new_value;
                    }
                }
            }
            else
            {
                std::string error  = "Writer: Could not open file " + file_path;
                std::cout << error << std::endl;
                #ifdef _MSC_VER
                    throw FileOpenException(error.c_str());
                #endif
            }
        }
        else
        {
            std::string error = "Writer: Invalid path form " + path_;
            std::cout << error << std::endl;
            #ifdef _MSC_VER
                throw InvalidPathException(error.c_str());
            #endif
        }
    }
}
