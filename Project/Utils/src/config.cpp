//
// config.cpp
//
// Created by Stefan Stepanovic on 01/22/2020

#include "config.h"

std::unordered_map<char, double> Config::time_table_;
CompilationType Config::type_;
int Config::parallel_write_;

Config* Config::Instance()
{
    Config* instance = new Config();
    return instance;
}

void Config::Read(const std::string& path)
{
    std::ifstream input(path);

    if (input.is_open())
    {
        std::string line;
        while (std::getline(input, line))
        {
            std::stringstream stream(line);
            char tmp;
            double value;
            std::string name, type;

            switch (line[1])
            {
            case 'a':
                stream >> name >> tmp >> value;
                time_table_.insert(std::make_pair('+', value));
                break;
            case 'm':
                stream >> name >> tmp >> value;
                time_table_.insert(std::make_pair('*', value));
                break;
            case 'e':
                stream >> name >> tmp >> value;
                time_table_.insert(std::make_pair('^', value));
                break;
            case 'w':
                stream >> name >> tmp >> value;
                if (name[0] == 'T')
                    time_table_.insert(std::make_pair('=', value));
                else
                    parallel_write_ = value;
                break;
            case 'o':
                stream >> name >> tmp >> type;
                if (!type.compare("simple"))
                    type_ = CompilationType::SIMPLE_COMPILATION;
                else
                    type_ = CompilationType::ADVANCED_COMPILATION;
                break;
            default:
                break;
            }
        }
    }
    input.close();
}

const double Config::GetTime(char operation) const
{
    return time_table_.at(operation);
}

const int Config::GetWriteThreads() const
{
    return parallel_write_;
}

CompilationType Config::GetType() const
{
    return type_;
}