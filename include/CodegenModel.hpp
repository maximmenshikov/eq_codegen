/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#pragma once
#include <string>
#include "yaml-cpp/yaml.h"
#include "CodegenParam.hpp"

class CodegenModel
{
public:
    CodegenModel() = default;
    virtual ~CodegenModel() = default;
    CodegenModel(const CodegenModel &rhs) = default;
    CodegenModel &operator=(const CodegenModel &rhs) = default;

    /**
     * @brief      Get model's name
     *
     * @return     The name.
     */
    virtual std::string getName() = 0;

    /**
     * @brief      Process the @p node data according to parameters in @p param
     *
     * @param      param  The parameter
     * @param      node   The node
     */
    virtual void process(CodegenParam &param, YAML::Node node) = 0;

    /**
     * @brief      Verify the @p node data according to parameters in @p param
     *
     * @param      param  The parameter
     * @param      node   The node
     */
    virtual void verify(CodegenParam &param, YAML::Node node)
    {
    }
};