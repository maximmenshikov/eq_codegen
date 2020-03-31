/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#include "MemberData.hpp"

/* See the description in MemberData.hpp */
bool
MemberData::isReadOnly() const
{
    return _isReadOnly;
}

/* See the description in MemberData.hpp */
void
MemberData::setIsReadOnly(bool ro)
{
    _isReadOnly = ro;
}

/* See the description in MemberData.hpp */
bool
MemberData::isPure() const
{
    return _isPure;
}

/* See the description in MemberData.hpp */
void
MemberData::setIsPure(bool pure)
{
    _isPure = pure;
}

/* See the description in MemberData.hpp */
std::string
MemberData::getType() const
{
    return _type;
}

/* See the description in MemberData.hpp */
void
MemberData::setType(std::string type)
{
    _type = type;
}

/* See the description in MemberData.hpp */
std::string
MemberData::getName() const
{
    return _name;
}

/* See the description in MemberData.hpp */
void
MemberData::setName(std::string name)
{
    _name = name;
}

/* See the description in MemberData.hpp */
std::string
MemberData::getMemberName() const
{
    return _memberName;
}

/* See the description in MemberData.hpp */
void
MemberData::setMemberName(std::string name)
{
    _memberName = name;
}
