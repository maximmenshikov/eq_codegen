/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#include "Command.hpp"
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include "yaml-cpp/yaml.h"
#include "DataFetcher.hpp"
#include "Syntax.hpp"
#include "Utils.hpp"

std::string
CodegenModel_Command::getName()
{
    return "command";
}

void
CodegenModel_Command::processPublicMembers(CodegenParam &          param,
                                           ClassData &             cd,
                                           bool                    isHeader,
                                           std::shared_ptr<Syntax> base)
{
    auto cls = cd.getName();
    auto members = cd.getMembers();

    if (members.size() > 0)
    {
        if (isHeader)
            base->add(Syntax::nl(Syntax::create(SyntaxKind::Exact, "public:")));

        for (auto &member : members)
        {
            auto type = member.second.getType();
            auto name = member.second.getName();
            auto memberName = member.second.getMemberName();
            auto isPure = member.second.isPure();
            auto ro = member.second.isReadOnly();

            if (isHeader)
            {
                auto func = createFunction((isPure ? "virtual " : "") + type,
                                           "get" + name);
                base->add(func);
                base->add(Syntax::create(SyntaxKind::Exact, "const"));
                if (isPure)
                {
                    base->add(Syntax::create(SyntaxKind::Exact, " = 0"));
                }
                base->add(Syntax::stmtEnd());
                if (!ro)
                {
                    auto func = createFunction("void", "set" + name);
                    base->add(Syntax::stmt(func));
                    func->add(Syntax::create(SyntaxKind::Exact,
                                             type + " " + memberName));
                }
            }
            else
            {
                if (isPure)
                    continue;
                base->add(createClassFunction(type, cls, "get" + name));
                base->add(Syntax::create(SyntaxKind::Exact, "const"));
                base->add(Syntax::create(
                    SyntaxKind::Block,
                    Syntax::stmt(Syntax::create(SyntaxKind::Exact,
                                                "return _" + memberName))));
                if (!ro)
                {
                    auto func = createClassFunction("void", cls, "set" + name);
                    base->add(func);
                    func->add(Syntax::create(SyntaxKind::Exact,
                                             type + " " + memberName));
                    base->add(Syntax::create(
                        SyntaxKind::Block,
                        Syntax::stmt(Syntax::create(SyntaxKind::Exact,
                                                    "_" + memberName + " = " +
                                                        memberName))));
                }
            }
        }
    }
}

void
CodegenModel_Command::processPrivateMembers(CodegenParam &          param,
                                            ClassData &             cd,
                                            std::shared_ptr<Syntax> base)
{
    auto cls = cd.getName();
    auto members = cd.getMembers();

    if (members.size() > 0)
    {
        base->add(Syntax::nl(Syntax::create(SyntaxKind::Exact, "private:")));

        for (auto &member : members)
        {
            auto type = member.second.getType();
            auto memberName = member.second.getMemberName();
            auto isPure = member.second.isPure();

            if (isPure)
                continue;

            base->add(Syntax::stmt(
                Syntax::create(SyntaxKind::Declaration, Syntax::text(type),
                               Syntax::text("_" + memberName))));
        }
    }
}

void
CodegenModel_Command::internalProcess(CodegenParam &param, YAML::Node node)
{
    auto name = node["name"].as<std::string>();
    auto headerRoot =
        createModule("VirtualMachine", name, true, node["header"],
                     std::vector<std::string>({}), node["dependency"]);
    auto headerMod = headerRoot->children().back();
    auto sourceRoot = createModule(
        "VirtualMachine", name, false, node["header"],
        std::vector<std::string>(
            { std::string("\"VirtualMachine/") + name + ".hpp\"" }),
        node["dependency"]);
    auto sourceMod = sourceRoot->children().back();
    auto classData = DataFetcher::fetchClass(node);

    if (name == "VmCommand_Base")
    {
        auto children = headerRoot->children();
        for (int i = 0; i < children.size(); ++i)
        {
            if (children[i]->getKind() == SyntaxKind::Module)
            {
                headerRoot->insert(i,
                                   Syntax::nl(Syntax::create(
                                       SyntaxKind::Exact,
                                       "core_define_shared_ptr(VirtualMachine, "
                                       "VMIR, VmCommand_Base);")));
                headerRoot->insert(
                    i, Syntax::nl(Syntax::create(SyntaxKind::Exact, "")));
                break;
            }
        }
    }

    auto cls = createClass(name, node["base"]);
    headerMod->add(cls);

    headerRoot->insert(
        0,
        Syntax::nl(Syntax::create(SyntaxKind::Exact,
                                  "/* This file is autogenerated. "
                                  "Please don't edit it directly */")));
    processPublicMembers(param, classData, true, cls);
    processPublicMembers(param, classData, false, sourceMod);
    processPrivateMembers(param, classData, cls);

    SOURCE(sourceRoot->toString());
    HEADER(headerRoot->toString());
}

void
CodegenModel_Command::process(CodegenParam &param, YAML::Node data)
{
    auto set = data["command"];
    if (set.IsSequence())
    {
        for (size_t i = 0; i < set.size(); i++)
        {
            auto s = set[i];
            auto name = s["name"].as<std::string>();

            param.setParameter(
                CodegenParamId::HeaderStream,
                new std::ofstream(
                    std::string("tmp/codegen-staging/include/VirtualMachine/") +
                    name + ".hpp"));
            param.setParameter(
                CodegenParamId::SourceStream,
                new std::ofstream(
                    std::string("tmp/codegen-staging/src/VirtualMachine/") +
                    name + ".cpp"));
            internalProcess(param, s);
            delete param.getSourceStream();
            delete param.getHeaderStream();
        }
    }
}