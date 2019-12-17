// 
// excdption.h
//
// Created by Stefan Stepanovic on 12/15/2019

#pragma once

#include <exception>

using namespace std;

// Microsoft compiler settings
#ifdef _MSC_VER

class InvalidPortException : public exception
{
 public:
    explicit InvalidPortException(const char* msg)
        : exception(msg)
    {}
};

class InvalidPathException : public exception
{
 public:
    explicit InvalidPathException(const char* msg)
        : exception(msg)
    {}
};

class FileOpenException : public exception
{
 public:
    explicit FileOpenException(const char* msg)
        : exception(msg)
    {}
};

class InvalidCircuitParamsException : public exception
{
 public:
    explicit InvalidCircuitParamsException(const char* msg)
        : exception(msg)
    {}
};

class NotGeneratorException : public exception
{
 public:
    explicit NotGeneratorException(const char* msg)
        : exception(msg)
    {}
};

class AllElementsAddedException : public exception
{
 public:
    explicit AllElementsAddedException(const char* msg)
        : exception(msg)
    {}
};

class InvalidElementsException : public exception
{
 public:
    explicit InvalidElementsException(const char* msg)
        : exception(msg)
    {}
};
#endif
