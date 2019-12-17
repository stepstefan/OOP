// 
// writer.h
//
// Created by Stefan Stepanovic on 12/17/2019

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "./element.h"

// singleton class for writing oututdataa
class Writer
{
 public:
    static Writer& GetInstance();
    ~Writer();

    // Write data to file
    void WriteOutput(const std::vector<double>& timestamps,
                     const std::vector<std::vector<bool>>& values,
                     const std::vector<Element*>& probes) const;

    // set base form of output file path
    void SetPath(const std::string& path);

    // delete unwanted methods and constructors
    Writer(Writer const&) = delete;
    void operator=(Writer const&) = delete;

 private:
    std::string path_;
    Writer();
};
