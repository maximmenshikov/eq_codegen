/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#pragma once
#include "ClassData.hpp"
#include "CodegenModel.hpp"
#include "Syntax.hpp"

class CodegenModel_Command : public CodegenModel
{
public:
    virtual std::string getName() override;
    virtual void        process(CodegenParam &param, YAML::Node node) override;

private:
    /**
     * @brief      Process public members of class
     *
     * @param      param     Code generator parameters
     * @param      cd        Class data to process
     * @param      isHeader  Indicate if the output is header unit
     * @param      base      The base syntax node
     */
    void processPublicMembers(CodegenParam &          param,
                              ClassData &             classData,
                              bool                    isHeader,
                              std::shared_ptr<Syntax> base);
    /**
     * @brief      Process private members of class
     *
     * @param      param     Code generator parameters
     * @param      cd        Class data to process
     * @param      base      The base syntax node
     */
    void processPrivateMembers(CodegenParam &          param,
                               ClassData &             classData,
                               std::shared_ptr<Syntax> base);
    void internalProcess(CodegenParam &param, YAML::Node node);
};
