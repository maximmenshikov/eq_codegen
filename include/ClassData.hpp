/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#pragma once
#include <map>
#include <string>
#include <vector>
#include "ConstructorData.hpp"
#include "MemberData.hpp"

class ClassData
{
public:
    ClassData() = default;
    virtual ~ClassData() = default;
    ClassData(const ClassData &rhs) = default;
    ClassData &operator=(const ClassData &rhs) = default;

    /**
     * @brief      Set the name of the class
     *
     * @param      name  The name
     */
    void setName(std::string name);

    /**
     * @brief      Get the name of the class
     *
     * @return     The name.
     */
    std::string getName() const;

    /**
     * @brief      Add a class constructor
     *
     * @param      constructorData  The constructor data
     */
    void addConstructor(ConstructorData constructorData);

    /**
     * @brief      Get the vector of class constructors.
     *
     * @return     The constructor vector.
     */
    std::vector<ConstructorData> getConstructors() const;

    /**
     * @brief      Add a class member
     *
     * @param      name        The name
     * @param      memberData  The member data
     */
    void addMember(std::string name, MemberData memberData);

    /**
     * @brief      Get the members of the class
     *
     * @return     The members.
     */
    std::map<std::string, MemberData> getMembers() const;

private:
    std::vector<ConstructorData>      _constructors;
    std::map<std::string, MemberData> _members;
    std::string                       _name;
};