/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#pragma once

/**
 * @brief      This class describes kinds of trivial syntax
 */
enum class SyntaxKind
{
    Root, /** Root element - should be clear */
    Header, /** #include definition */
    Dependency, /** Module dependency or superclass */
    Module, /** Module in project's terms */
    Exact, /** Random string which may have large syntax meaning */
    Declaration, /** Variable declaration */
    FunctionProto, /** Function prototype in header file */
    SourceFunctionProto, /** Function prototype in source file */
    Block, /** {} block */
    Wrap, /** Some way to wrap the line - statement or new line */
    Class, /** Class definition */
};
