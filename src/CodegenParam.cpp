/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#include "CodegenParam.hpp"
#include <any>
#include <string>

/* See the description in CodegenParam.hpp */
std::any
CodegenParam::getParameter(CodegenParamId id)
{
    return _parameters[id];
}

/* See the description in CodegenParam.hpp */
void
CodegenParam::setParameter(CodegenParamId id, std::any data)
{
    _parameters[id] = data;
}

/* See the description in CodegenParam.hpp */
bool
CodegenParam::isModeVerify()
{
    if (_parameters.find(CodegenParamId::Verify) == _parameters.end())
        return false;
    return std::any_cast<bool>(_parameters[CodegenParamId::Verify]);
}

/* See the description in CodegenParam.hpp */
std::ostream *
CodegenParam::getSourceStream()
{
    return (std::ostream *)std::any_cast<std::ofstream *>(
        _parameters[CodegenParamId::SourceStream]);
}

/* See the description in CodegenParam.hpp */
std::ostream *
CodegenParam::getHeaderStream()
{
    return (std::ostream *)std::any_cast<std::ofstream *>(
        _parameters[CodegenParamId::HeaderStream]);
}

/* See the description in CodegenParam.hpp */
std::ostream *
CodegenParam::getSourceOpStream()
{
    return (std::ostream *)std::any_cast<std::ofstream *>(
        _parameters[CodegenParamId::SourceOpStream]);
}

/* See the description in CodegenParam.hpp */
std::ostream *
CodegenParam::getHeaderOpStream()
{
    return (std::ostream *)std::any_cast<std::ofstream *>(
        _parameters[CodegenParamId::HeaderOpStream]);
}

/* See the description in CodegenParam.hpp */
void
CodegenParam::setPath(std::string path)
{
    _path = path;
}

/* See the description in CodegenParam.hpp */
std::string
CodegenParam::getPath() const
{
    return _path;
}