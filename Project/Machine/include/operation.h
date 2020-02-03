//
// operation.h
//
// Created by Stefan Stepanovic on 01/22/2020

#pragma once

#include <vector>
#include <string>
#include <limits>

#include "memory.h"

#include "Interfaces.h"
#include "Event.h"
#include "Sched.h"

// Operand class (can be const, variable, or temporary token (product of operation))
class Operand
{
 public:
    Operand();
    virtual double Evaluate() const = 0;
    virtual bool Ready() const = 0;
    virtual void SetValue(const double) = 0;
};

class Constant : public Operand
{
 public:
    explicit Constant(double value);
    bool Ready() const override;
    double Evaluate() const override;
    void SetValue(const double) override;
 private:
    const double value_;
};

class Variable : public Operand
{
 public:
    explicit Variable(char name);
    bool Ready() const override;
    double Evaluate() const override;
    void SetValue(const double) override;
    const char Name() const;
 private:
    const char name_;
    bool ready_;
};

class Token : public Operand
{
 public:
    explicit Token(const std::string& name);
    bool Ready() const override;
    double Evaluate() const override;
    void SetValue(const double) override;
    std::string Name();
 private:
    std::string name_;
    bool ready_;
    double value_;
};

// Operation class
class Operation : public ITimedElement
{
 public:
    Operation(char operation, double time, int id);
    void SetResult(Operand*);
    void SetLeft(Operand*);
    void SetRight(Operand*);

    Operand* GetLeft();
    Operand* GetRight();
    const double GetTime() const;
    const char GetOperation() const;
    const int GetId() const;

    void notify(ID id) override;
    void Evaluate();
    bool Ready() const;


 private:
    const char operation_;
    const double time_;
    const int id_;

    Operand* result_;
    Operand* left_operand_;
    Operand* right_operand_;
};