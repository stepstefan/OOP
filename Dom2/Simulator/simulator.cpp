// 
// simulator.cpp
//
// Created by Stefan Stepanovic on 12/16/2019

#include "./simulator.h"
#include "./reader.h"

bool DoubleEqual(const double a, const double b)
{
    if (std::abs(a-b) < EPSILON)
    {
        return true;
    }
    return false;
}

Simulator::Simulator()
{}

void Simulator::LoadCircuit(const std::string& filepath)
{
    Reader::GetInstance().SetPath(filepath);
    circuit_ = Reader::GetInstance().ReadCircuit();
    duration_ = Reader::GetInstance().GetDuration();
}

void Simulator::Simulate(const std::string& filepath)
{
    std::vector<double> timestamps;
    // get timestamps from generator data
    for (const auto& generator : circuit_->GetGenerators())
    {
        std::vector<double> gen_timestamps = generator->GetChangeTimestamps(duration_);
        for (double timestamp : gen_timestamps)
        {
            timestamps.push_back(timestamp);
        }
    }
    // sort timestamps
    std::sort(timestamps.begin(), timestamps.end());

    // erase duplicates
    for (size_t i = 0; i < timestamps.size() - 1;)
    {
        if (DoubleEqual(timestamps.at(i), timestamps.at(i+1)))
        {
            timestamps.erase(timestamps.begin() + i);
        }
        else
        {
            i++;
        }
    }

    // run simulation
    std::vector<std::vector<bool>> outputs;
    for (const double timestamp : timestamps)
    {
        outputs.push_back(circuit_->Evaluate(timestamp));
    }
}
