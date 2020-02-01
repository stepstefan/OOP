//
// exceptions.h
//
// Created by Stefan Stepanovic on 01/22/2020

#pragma once

// Microsoft compiler settings
#ifdef _MSC_VER

#include <exception>

using namespace std;

class VarNotAvailable : public exception {
public:
	VarNotAvailable(const char* msg) : exception(msg) {}
};

class NotValidExpression : public exception {
public:
	NotValidExpression(const char* msg) : exception(msg) {}
};

#endif