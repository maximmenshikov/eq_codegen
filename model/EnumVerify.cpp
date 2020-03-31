/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include "EnumVerify.hpp"

std::string
CodegenModel_EnumVerify::getName()
{
    return "enum_verify";
}

void
CodegenModel_EnumVerify::process(CodegenParam &param, YAML::Node node)
{
}

void
CodegenModel_EnumVerify::verify(CodegenParam &param, YAML::Node node)
{
    std::map<std::string, int> cases;
    std::string              name = node["type"].as<std::string>();
    std::string              line;
    std::ifstream            is(param.getPath());
    bool isIn = false;
    auto field = node["field"];
    bool verifyAll = false;
    int  lineCounter = 0;

    if (field.IsSequence())
    {
        for (size_t i = 0; i < field.size(); ++i)
        {
            cases[field[i]["name"].as<std::string>()] = false;
        }
    }

    while (std::getline(is, line, '\n'))
    {
        lineCounter++;
        if (line.find(std::string("end_core_indicate_use(" + name + ")")) !=
            std::string::npos)
        {
            assert(isIn == true);

            isIn = false;

            if (verifyAll)
            {
                for (auto &cs : cases)
                {
                    if (cs.second == -1)
                    {
                        std::cerr << "Unhandled use case: " << cs.first
                                  << std::endl;
                    }
                    else
                    {
                        std::cout << "Handled enum use case: "<< cs.first
                                  << " (at line " << cs.second << ")"
                                  << std::endl;
                    }
                }
            }
        }
        else if (line.find(std::string("core_indicate_use(") + name) !=
            std::string::npos)
        {
            std::string use;

            assert(isIn == false);

            /* Disable all found cases - it is a new start */
            for (auto &cs : cases)
            {
                cs.second = -1;
            }

            isIn = true;
            use = line.substr(line.find(",") + 2);
            use = use.substr(0, use.find(")"));

            verifyAll = use == "CoreEnumUse::AllVariants";
        }
        else if (isIn)
        {
            if (line.find(std::string("case ") + name + "::") !=
                std::string::npos)
            {
                std::string cs;

                cs = line.substr(line.find("::") + 2);
                cs = cs.substr(0, cs.find(":"));

                cases[cs] = lineCounter;
            }
        }
    }
    is.close();
}
