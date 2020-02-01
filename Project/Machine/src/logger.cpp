#include "logger.h"

std::ofstream Logger::output_;

Logger* Logger::Instance()
{
    static Logger* instance = new Logger();
    return instance;
}

bool Logger::SetOutput(const std::string& path)
{
    output_.open(path);
    return output_.is_open();
}

void Logger::Print(const std::string& line)
{
    output_ << line << std::endl;
}