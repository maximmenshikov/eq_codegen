/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#include "ClassData.hpp"

/* See the description in ClassData.hpp */
void
ClassData::setName(std::string name)
{
    _name = name;
}

/* See the description in ClassData.hpp */
std::string
ClassData::getName() const
{
    return _name;
}

/* See the description in ClassData.hpp */
void
ClassData::addConstructor(ConstructorData constructorData)
{
    _constructors.push_back(constructorData);
}

/* See the description in ClassData.hpp */
std::vector<ConstructorData>
ClassData::getConstructors() const
{
    return _constructors;
}

/* See the description in ClassData.hpp */
void
ClassData::addMember(std::string name, MemberData memberData)
{
    _members[name] = memberData;
}

/* See the description in ClassData.hpp */
std::map<std::string, MemberData>
ClassData::getMembers() const
{
    return _members;
}
