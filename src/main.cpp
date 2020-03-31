/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#include <algorithm>
#include <any>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "yaml-cpp/yaml.h"

#ifdef ENABLE_DEPRECATED
#include "Enum.hpp"
#include "Expression.hpp"
#endif

#include "EnumVerify.hpp"
#include "Command.hpp"
#include "VMIRMapping.hpp"

static std::shared_ptr<CodegenModel> codegenModels[] = {
#ifdef ENABLE_DEPRECATED
    std::dynamic_pointer_cast<CodegenModel>(
        std::make_shared<CodegenModel_Expression>()),
    std::dynamic_pointer_cast<CodegenModel>(
        std::make_shared<CodegenModel_Enum>()),
#endif
    std::dynamic_pointer_cast<CodegenModel>(
        std::make_shared<CodegenModel_Command>()),
    std::dynamic_pointer_cast<CodegenModel>(
        std::make_shared<CodegenModel_VMIRMapping>()),
    std::dynamic_pointer_cast<CodegenModel>(
        std::make_shared<CodegenModel_EnumVerify>()),
};

/** Execute arbitrary model of the given name */
static bool
executeModel(CodegenParam &param, YAML::Node data, std::string modelName)
{
    for (size_t i = 0; i < sizeof(codegenModels) / sizeof(*codegenModels); ++i)
    {
        if (codegenModels[i]->getName() == modelName)
        {
            std::cout << "Execute " << modelName << " model" << std::endl;
            if (param.isModeVerify())
                codegenModels[i]->verify(param, data);
            else
                codegenModels[i]->process(param, data);
            return true;
        }
    }

    return false;
}


/** Process the input file */
static int
process(CodegenParam &param, const std::string &fileName)
{
    YAML::Node config = YAML::LoadFile(fileName);
    auto       data = config["data"];
    auto       md = config["model"];

    if (!md.IsDefined())
    {
        std::cerr << "Model is not defined" << std::endl;
        return 1;
    }

    if (md.IsSequence())
    {
        for (size_t i = 0; i < md.size(); ++i)
        {
            auto name = md[i].as<std::string>();
            if (!executeModel(param, data, name))
            {
                std::cerr << "Unknown model: " << name << std::endl;
                return 3;
            }
        }
    }
    else if (md.IsScalar())
    {
        if (!executeModel(param, data, md.as<std::string>()))
        {
            std::cerr << "Unknown model: " << md.as<std::string>() << std::endl;
            return 3;
        }
    }
    else
    {

        std::cerr << "Model is of incorrect type" << std::endl;
        return 2;
    }

    return 0;
}

int
main(int argc, const char *argv[])
{
    CodegenParam param;
    std::string  file;
    std::string  output;

    if (argc != 3 && argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " definition_file out_path "
                  << "[verify]" << std::endl;
        return -1;
    }
    else
    {
        file = std::string(argv[1]);
        output = std::string(argv[2]);
        if (argc == 4)
        {
            std::string verify = std::string(argv[3]);

            if (verify != "verify")
            {
                std::cerr << "Invalid input parameters" << std::endl;
                return -2;
            }

            param.setParameter(CodegenParamId::Verify, true);
        }
    }

    param.setPath(output);
    return process(param, file);
}