/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#pragma once
#include "yaml-cpp/yaml.h"
#include "ClassData.hpp"
#include "ConstructorData.hpp"
#include "MemberData.hpp"

class DataFetcher
{
public:
    /**
     * @brief      Fetch a class from YAML node
     *
     * @param      node  The node
     *
     * @return     The class data object
     */
    static ClassData fetchClass(YAML::Node node);

    /**
     * @brief      Fetch a constructor from YAML node
     *
     * @param      node  The node
     *
     * @return     The constructor data object
     */
    static ConstructorData fetchConstructor(YAML::Node node);

    /**
     * @brief      Fetch a member from YAML node
     *
     * @param      node  The node
     *
     * @return     The member data object
     */
    static MemberData fetchMember(YAML::Node node);
};