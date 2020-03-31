/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#pragma once
#include "CodegenModel.hpp"

class CodegenModel_EnumVerify : public CodegenModel
{
public:
    virtual std::string getName() override;
    virtual void        process(CodegenParam &param, YAML::Node node) override;
    virtual void        verify(CodegenParam &param, YAML::Node node) override;
};
