/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#pragma once
#include <fstream>
#include <ostream>
#include "yaml-cpp/yaml.h"
#include "Syntax.hpp"

/**
 * @brief      Create a module.
 *
 * @param      ns            The namespace
 * @param      module        The module name
 * @param      isHeader      Indicates if the module is a header
 * @param      headers       The node with header list
 * @param      extraHeaders  The vector of extra headers
 * @param      deps          The dependency node
 *
 * @return     A created module node
 */
extern std::shared_ptr<Syntax>
createModule(const std::string &      ns,
             const std::string &      module,
             bool                     isHeader,
             YAML::Node               headers,
             std::vector<std::string> extraHeaders,
             YAML::Node               deps);

/**
 * @brief      Create a class.
 *
 * @param      cls    The class
 * @param      bases  The node with class's superclasses
 *
 * @return     A created class node
 */
extern std::shared_ptr<Syntax>
createClass(const std::string &cls, YAML::Node bases);

/**
 * @brief      Create a class function.
 *
 * @param      type  The return type of the function
 * @param      cls   The class name
 * @param      func  The function name
 *
 * @return     A created function node
 */
extern std::shared_ptr<Syntax>
createClassFunction(const std::string &type,
                    const std::string &cls,
                    const std::string &func);

/**
 * @brief      Create a regular function
 *
 * @param      type  The return type of the function
 * @param      func  The function name
 *
 * @return     A created function node
 */
extern std::shared_ptr<Syntax>
createFunction(const std::string &type, const std::string &func);