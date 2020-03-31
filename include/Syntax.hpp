/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#pragma once
#include <any>
#include <cassert>
#include <memory>
#include <string>
#include <vector>
#include "SyntaxKind.hpp"

class Syntax
{
public:
    Syntax() = default;

    Syntax(SyntaxKind newKind) : Syntax()
    {
        _kind = newKind;
    }

    Syntax(SyntaxKind                                     newKind,
           std::initializer_list<std::shared_ptr<Syntax>> l) :
      Syntax(newKind)
    {
        for (auto &obj : l)
        {
            _children.push_back(obj);
        }
    }

    Syntax(SyntaxKind newKind, std::string newValue) : Syntax(newKind)
    {
        _value = newValue;
    }

    virtual ~Syntax() = default;
    Syntax(const Syntax &rhs) = default;
    Syntax &operator=(const Syntax &rhs) = default;

    /**
     * @brief      Get the kind of syntax
     *
     * @return     The syntax kind
     */
    SyntaxKind getKind() const
    {
        return _kind;
    }

    /**
     * @brief      Add a new child syntax node
     *
     * @param      syntax  The syntax node
     */
    void add(std::shared_ptr<Syntax> syntax)
    {
        _children.push_back(syntax);
    }

    /**
     * @brief      Insert a new child syntax node at specified position
     *
     * @param      index   The index where to insert the syntax node
     * @param      syntax  The syntax node
     */
    void insert(size_t index, std::shared_ptr<Syntax> syntax)
    {
        _children.insert(_children.begin() + index, syntax);
    }

    /**
     * @brief      Get a copy of children syntax node vector
     *
     * @return     Vector of children syntax nodes
     */
    std::vector<std::shared_ptr<Syntax>> children()
    {
        return _children;
    }

    /**
     * @brief      Set the string used for immediate values
     *
     * @param      value  The string value
     */
    void setValue(const std::string &value)
    {
        _value = value;
    }

    /**
     * @brief      Ensure the line is ending with something appropriate
     *             (new line, end of statement)
     *
     * @param      s     The string to end
     *
     * @return     The properly ended string
     */
    static std::string ensureEOL(std::string s)
    {
        if (s.size() == 0)
            return ";";
        if (s[s.size() - 1] != ';' && s[s.size() - 1] != '}')
            return s + ";";
        return s;
    }

    /**
     * @brief      Get string representation of syntax node
     *
     * @return     String representation of the object.
     */
    virtual std::string toString() const
    {
        switch (_kind)
        {
            case SyntaxKind::Exact:
            {
                return _value;
            }
            case SyntaxKind::Header:
            {
                return std::string("#include ") + _value + "\n";
            }
            case SyntaxKind::Class:
            {
                std::string s = std::string("class ") + _value;
                bool        depsEnded = false;

                if (_children.size() == 0)
                {
                    s += "\n{\n";
                }
                else
                {
                    for (size_t i = 0; i < _children.size(); ++i)
                    {
                        if (!depsEnded &&
                            _children[i]->getKind() == SyntaxKind::Dependency)
                        {
                            if (i == 0)
                                s += " : ";
                            else if (i != 0)
                                s += ", ";
                            s += "public " + _children[i]->toString();
                            continue;
                        }
                        else if (!depsEnded)
                        {
                            depsEnded = true;
                            s += "\n{\n";
                        }
                        s += _children[i]->toString() + "\n";
                    }

                    if (!depsEnded)
                    {
                        s += "\n{\n";
                    }
                }

                s += "};\n";
                return s;
            }
            case SyntaxKind::Dependency:
            {
                assert(_children.size() == 0 || _children.size() == 2);

                if (_children.size() == 2)
                {
                    return std::string("core_module_depends(") +
                        _children[0]->toString() + ", " +
                        _children[1]->toString() + ");\n";
                }
                else
                {
                    return _value;
                }
            }
            case SyntaxKind::Module:
            {
                std::string s;

                assert(_children.size() >= 2);
                s += std::string("\ncore_module(") + _children[0]->toString() +
                    ", " + _children[1]->toString() + ", \"generic\");\n\n";
                for (size_t i = 2; i < _children.size(); ++i)
                {
                    s += _children[i]->toString() + "\n";
                }
                s += std::string("\nend_core_module();\n");
                return s;
            }
            case SyntaxKind::Declaration:
            {
                std::string result;

                assert(_children.size() >= 2);
                result =
                    _children[0]->toString() + " " + _children[1]->toString();
                if (_children.size() == 3)
                    result += " = " + _children[2]->toString();
                return result;
            }
            case SyntaxKind::FunctionProto:
            {
                std::string result;

                assert(_children.size() >= 2);

                result = _children[0]->toString() + " " +
                    _children[1]->toString() + "(";
                for (int i = 2; i < _children.size(); ++i)
                {
                    if (i != 2)
                        result += ", ";
                    result += _children[i]->toString();
                }
                result += ")";

                return result;
            }
            case SyntaxKind::SourceFunctionProto:
            {
                std::string result;

                assert(_children.size() >= 3);
                result = _children[0]->toString() + " " +
                    _children[1]->toString() + "::" + _children[2]->toString() +
                    "(";
                for (int i = 3; i < _children.size(); ++i)
                {
                    if (i != 3)
                        result += ", ";
                    result += _children[i]->toString();
                }
                result += ")";
                return result;
            }
            case SyntaxKind::Root:
            case SyntaxKind::Block:
            {
                std::string result;

                if (_kind == SyntaxKind::Block)
                    result += "{";
                for (auto &ch : _children)
                {
                    if (_kind == SyntaxKind::Block)
                        result = ensureEOL(result + ch->toString());
                    else
                        result += ch->toString();
                }
                if (_kind == SyntaxKind::Block)
                    result += "}";
                return result;
            }
            case SyntaxKind::Wrap:
            {
                assert(_children.size() == 1);
                if (_value == ";")
                    return ensureEOL(_children[0]->toString());
                else
                    return _children[0]->toString() + _value;
            }
            default:
            {
                return "";
            }
        }
        return "";
    }

    /**
     * @brief      Create a new empty syntax node
     *
     * @param      kind  The syntax node kind
     *
     * @return     A shared pointer to created syntax node
     */
    static std::shared_ptr<Syntax> create(SyntaxKind kind)
    {
        return std::make_shared<Syntax>(kind);
    }


    /**
     * @brief      Create a new syntax node with immediate string alue
     *
     * @param      kind   The syntax node kind
     * @param      value  The immediate string value
     *
     * @return     A shared pointer to created syntax node
     */
    static std::shared_ptr<Syntax> create(SyntaxKind kind, const char *value)
    {
        return std::make_shared<Syntax>(kind, std::string(value));
    }

    /**
     * @brief      Create a new syntax node with immediate string alue
     *
     * @param      kind   The syntax node kind
     * @param      value  The immediate string value
     *
     * @return     A shared pointer to created syntax node
     */
    static std::shared_ptr<Syntax> create(SyntaxKind kind, std::string value)
    {
        return std::make_shared<Syntax>(kind, std::string(value));
    }

    /**
     * @brief      Create a new syntax node with variadic arguments
     *
     * @param      kind  The syntax node kind
     * @param      args  The variadic arguments (shared pointers to Syntax)
     *
     * @tparam     Type  Type of nodes - automatically deduced.
     *
     * @return     A shared pointer to created syntax node
     */
    template <typename... Type>
    static std::shared_ptr<Syntax> create(SyntaxKind kind, Type... args)
    {
        auto result = std::make_shared<Syntax>(kind);
        auto vec = { args... };

        for (auto &obj : vec)
        {
            result->_children.push_back(obj);
        }

        return result;
    }

    /**
     * @brief      Create a new syntax node with variadic arguments and
     *             immediate string value
     *
     * @param      kind   The syntax node kind
     * @param      value  The immediate string value
     * @param      args   The variadic arguments (shared pointers to Syntax)
     *
     * @tparam     Type   Type of nodes - automatically deduced.
     *
     * @return     A shared pointer to created syntax node
     */
    template <typename... Type>
    static std::shared_ptr<Syntax> create(SyntaxKind  kind,
                                          const char *value,
                                          Type... args)
    {
        auto result = std::make_shared<Syntax>(kind);
        auto vec = { args... };

        result->_value = std::string(value);
        for (auto &obj : vec)
        {
            result->_children.push_back(obj);
        }

        return result;
    }

    /**
     * @brief      Create a new syntax node with variadic arguments and
     *             immediate string value
     *
     * @param      kind   The syntax node kind
     * @param      value  The immediate string value
     * @param      args   The variadic arguments (shared pointers to Syntax)
     *
     * @tparam     Type   Type of nodes - automatically deduced.
     *
     * @return     A shared pointer to created syntax node
     */
    template <typename... Type>
    static std::shared_ptr<Syntax> create(SyntaxKind  kind,
                                          std::string value,
                                          Type... args)
    {
        auto result = std::make_shared<Syntax>(kind);
        auto vec = { args... };

        result->_value = value;
        for (auto &obj : vec)
        {
            result->_children.push_back(obj);
        }

        return result;
    }

    /**
     * @brief      Wrap a syntax node to statement
     *
     * @param      inner  The inner statement
     *
     * @return     Wrapped syntax node
     */
    static std::shared_ptr<Syntax> stmt(std::shared_ptr<Syntax> inner)
    {
        return Syntax::create(SyntaxKind::Wrap, ";", inner);
    }

    /**
     * @brief      Create a statement-ending syntax node
     *
     * @return     Syntax node ending a statement
     */
    static std::shared_ptr<Syntax> stmtEnd()
    {
        return Syntax::create(SyntaxKind::Exact, ";");
    }

    /**
     * @brief      Create a new line syntax node
     *
     * @param      inner  The inner statement
     *
     * @return     Syntax node - new line
     */
    static std::shared_ptr<Syntax> nl(std::shared_ptr<Syntax> inner)
    {
        return Syntax::create(SyntaxKind::Wrap, "\n", inner);
    }

    /**
     * @brief      Create a new text-based syntax node
     *
     * @param      text  The text
     *
     * @return     Text-based syntax node
     */
    static std::shared_ptr<Syntax> text(std::string text)
    {
        return Syntax::create(SyntaxKind::Exact, text);
    }

private:
    SyntaxKind                           _kind;
    std::vector<std::shared_ptr<Syntax>> _children;
    std::string                          _value;
};
