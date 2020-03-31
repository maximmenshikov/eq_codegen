/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#include "DataFetcher.hpp"
#include <iostream>
#include "yaml-cpp/yaml.h"
#include "ClassData.hpp"
#include "ConstructorData.hpp"
#include "MemberData.hpp"

/* See the description in DataFetcher.hpp */
ClassData
DataFetcher::fetchClass(YAML::Node node)
{
    auto res = ClassData();
    auto constructors = node["constructor"];
    auto members = node["member"];

    if (constructors.IsSequence())
    {
        for (size_t i = 0; i < constructors.size(); ++i)
        {
            res.addConstructor(fetchConstructor(constructors[i]));
        }
    }

    if (members.IsSequence())
    {
        for (size_t i = 0; i < members.size(); ++i)
        {
            auto m = fetchMember(members[i]);
            res.addMember(m.getName(), m);
        }
    }

    if (node["name"].IsScalar())
        res.setName(node["name"].as<std::string>());
    return res;
}

/* See the description in DataFetcher.hpp */
ConstructorData
DataFetcher::fetchConstructor(YAML::Node node)
{
    auto params = node["parameter"];
    auto assignments = node["assignment"];
    auto res = ConstructorData();

    if (params.IsSequence())
    {
        for (size_t i = 0; i < params.size(); ++i)
        {
            if (!params[i].IsScalar())
            {
                std::cerr << "Parameter is not string: " << i << std::endl;
                continue;
            }
            res.addParameter(params[i].as<std::string>());
        }
    }

    if (assignments.IsSequence())
    {
        for (size_t i = 0; i < assignments.size(); ++i)
        {
            auto name = assignments[i]["name"];
            auto value = assignments[i]["value"];

            if (!name.IsScalar() || !value.IsScalar())
            {
                std::cerr << "Malformed assignment: " << i << std::endl;
                continue;
            }
            res.addAssignment(name.as<std::string>(), value.as<std::string>());
        }
    }
    return res;
}

/* See the description in DataFetcher.hpp */
MemberData
DataFetcher::fetchMember(YAML::Node node)
{
    auto type = node["type"].as<std::string>();
    auto name = node["name"].as<std::string>();
    auto memberName = node["member_name"].as<std::string>();
    auto isPure = node["pure"].IsDefined() ? node["pure"].as<bool>() : false;
    auto isReadOnly =
        node["read_only"].IsDefined() ? node["read_only"].as<bool>() : false;
    auto res = MemberData();

    res.setType(type);
    res.setName(name);
    res.setMemberName(memberName);
    res.setIsPure(isPure);
    res.setIsReadOnly(isReadOnly);
    return res;
}
