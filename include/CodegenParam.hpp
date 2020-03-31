/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#pragma once
#include <any>
#include <map>
#include <string>
#include "CodegenParamId.hpp"
#include "CodegenParamMacro.hpp"

class CodegenParam
{
public:
    CodegenParam() = default;
    virtual ~CodegenParam() = default;
    CodegenParam(const CodegenParam &rhs) = default;
    CodegenParam &operator=(const CodegenParam &rhs) = default;

    /**
     * @brief      Get the parameter by specific @p id
     *
     * @param      id    The paramter's identifier
     *
     * @return     The parameter.
     */
    std::any getParameter(CodegenParamId id);

    /**
     * @brief      Set the parameter with specific @p id
     *
     * @param      id    The parameter's identifier
     * @param      data  The data
     */
    void setParameter(CodegenParamId id, std::any data);

    /**
     * @brief      Determine whether the mode if 'verify'
     *
     * @return     @c true if mode is 'verify', @c false otherwise.
     */
    bool isModeVerify();

    /**
     * @brief      Get the source code stream
     *
     * @return     The source stream.
     */
    std::ostream *getSourceStream();

    /**
     * @brief      Get the header data stream
     *
     * @return     The header stream
     */
    std::ostream *getHeaderStream();

    /**
     * @brief      Get the source operation code stream
     *
     * @return     The source stream
     */
    std::ostream *getSourceOpStream();

    /**
     * @brief      Get the header operation data stream
     *
     * @return     The header stream
     */
    std::ostream *getHeaderOpStream();

    /**
     * @brief      Set the path where to put the result
     *
     * @param      path  The path, relative or absolute
     */
    void setPath(std::string path);

    /**
     * @brief      Get the path where to put the result
     *
     * @return     The path, relative or absolute.
     */
    std::string getPath() const;

private:
    std::map<CodegenParamId, std::any> _parameters;
    std::string                        _path;
};