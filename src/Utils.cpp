/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#include <fstream>
#include <ostream>
#include "yaml-cpp/yaml.h"
#include "Syntax.hpp"

/* See the description in Utils.hpp */
std::shared_ptr<Syntax>
createModule(const std::string &      ns,
             const std::string &      module,
             bool                     isHeader,
             YAML::Node               headers,
             std::vector<std::string> extraHeaders,
             YAML::Node               deps)
{
    auto root = Syntax::create(SyntaxKind::Root);

    if (isHeader)
    {
        root->add(
            Syntax::nl(Syntax::create(SyntaxKind::Exact, "#pragma once")));
    }

    root->add(Syntax::create(SyntaxKind::Header, "\"core.hpp\""));

    if (headers.IsSequence())
    {
        for (size_t i = 0; i < headers.size(); ++i)
        {
            root->add(Syntax::create(SyntaxKind::Header,
                                     headers[i].as<std::string>()));
        }
    }
    for (auto &eh : extraHeaders)
    {
        root->add(Syntax::create(SyntaxKind::Header, eh));
    }

    auto mod = Syntax::create(SyntaxKind::Module, Syntax::text(ns),
                              Syntax::text(module));
    root->add(mod);

    if (deps.IsSequence())
    {
        for (size_t i = 0; i < deps.size(); ++i)
        {
            mod->add(Syntax::create(
                SyntaxKind::Dependency,
                Syntax::text(deps[i]["namespace"].as<std::string>()),
                Syntax::text(deps[i]["why"].as<std::string>())));
        }
    }
    return root;
}

/* See the description in Utils.hpp */
std::shared_ptr<Syntax>
createClass(const std::string &cls, YAML::Node bases)
{
    auto root = Syntax::create(SyntaxKind::Class, cls);

    if (bases.IsSequence())
    {
        for (size_t i = 0; i < bases.size(); ++i)
        {
            root->add(Syntax::create(SyntaxKind::Dependency,
                                     bases[i].as<std::string>()));
        }
    }

    return root;
}

/* See the description in Utils.hpp */
std::shared_ptr<Syntax>
createClassFunction(const std::string &type,
                    const std::string &cls,
                    const std::string &func)
{
    return Syntax::create(SyntaxKind::SourceFunctionProto, Syntax::text(type),
                          Syntax::text(cls), Syntax::text(func));
}

/* See the description in Utils.hpp */
std::shared_ptr<Syntax>
createFunction(const std::string &type, const std::string &func)
{
    return Syntax::create(SyntaxKind::FunctionProto, Syntax::text(type),
                          Syntax::text(func));
}
