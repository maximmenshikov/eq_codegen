/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#pragma once
#include "CodegenModel.hpp"

class CodegenModel_VMIRMapping : public CodegenModel
{
public:
    virtual std::string getName() override;
    virtual void        process(CodegenParam &param, YAML::Node node) override;

private:
    void internalProcess(CodegenParam &param, YAML::Node node);
};
