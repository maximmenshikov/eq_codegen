/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#pragma once
#include <map>
#include <string>
#include <vector>

class ConstructorData
{
public:
    ConstructorData() = default;
    virtual ~ConstructorData() = default;
    ConstructorData(const ConstructorData &rhs) = default;
    ConstructorData &operator=(const ConstructorData &rhs) = default;

    /**
     * @brief      Get the directly assigned parameters of the constructor
     *
     * @return     The members.
     */
    std::vector<std::string> getParameters() const;


    /**
     * @brief      Add a parameter to the constructor
     *
     * @param[in]  parameterName  The parameter name that should match
     *                            internal name of the member.
     */
    void addParameter(std::string parameterName);

    /**
     * @brief      Get the assignments done within the constructor
     *
     * @return     The members.
     */
    std::map<std::string, std::string> getAssignments() const;

    /**
     * @brief      Add a parameter to the constructor
     *
     * @param[in]  memberName  The member name
     * @param[in]  value       The value in target language
     */
    void addAssignment(std::string memberName, std::string value);


private:
    std::vector<std::string>           _parameters;
    std::map<std::string, std::string> _assignments;
};