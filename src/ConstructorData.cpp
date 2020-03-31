/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#include "ConstructorData.hpp"

/* See the description in ConstructorData.hpp */
std::vector<std::string>
ConstructorData::getParameters() const
{
    return _parameters;
}

/* See the description in ConstructorData.hpp */
void
ConstructorData::addParameter(std::string parameterName)
{
    _parameters.push_back(parameterName);
}

/* See the description in ConstructorData.hpp */
std::map<std::string, std::string>
ConstructorData::getAssignments() const
{
    return _assignments;
}

/* See the description in ConstructorData.hpp */
void
ConstructorData::addAssignment(std::string memberName, std::string value)
{
    _assignments[memberName] = value;
}
