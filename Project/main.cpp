#include <string>

#include "machine.h"
#include "config.h"
#include "logger.h"

#include "expression.h"
#include "program.h"
#include "compiler.h"



int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid arguments!" << std::endl;
        return 0;
    }

    std::string nametxt = argv[1];
    Config::Instance()->Read("config.txt");
    std::string name = nametxt.substr(0, nametxt.length() - 4);

    Program program;
    program.Read(nametxt);
    Compiler compiler(Config::Instance()->GetType(), program, name+".imf");
    compiler.Compile();

    Logger::Instance()->SetOutput(name+".log");

    Machine::Instance()->Read(name+".imf");
    Machine::Instance()->Execute();

    Memory::Instance()->Print(name+".mem");
}