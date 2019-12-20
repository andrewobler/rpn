/**
 * @file rpn_stack.cpp
 * @author Andrew Obler (andrewobler@gmail.com)
 * @brief Implementation of classes in rpn_stack.hpp.
 * @version 0.1
 * @date 2019-12-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "rpn_stack.hpp"

#include <cstdarg>
#include <stack>
#include <string>
#include <vector>

const char* RPNStackException::what() const noexcept {
    return "Insufficient operands on RPN stack";
}

const char* RPNDivByZeroException::what() const noexcept {
    return "Topmost value is 0, cannot divide";
}

RPNStack::RPNStack(unsigned int count, double vals...) : RPNStack() {
    va_list args;
    va_start(args, vals);

    for (unsigned int i = 0; i < count; i++) {
        double nextVal = va_arg(args, double);
        values.push_back(nextVal);
    }

    va_end(args);
}

void RPNStack::push(double val) {
    values.push_back(val);
}

void RPNStack::pop() {
    if (values.empty()) {
        throw RPNStackException();
    }

    values.pop_back();
}

void RPNStack::add() {
    if (values.size() < 2) {
        throw RPNStackException();
    }

    double top = values.back();
    values.pop_back();
    double nextTop = values.back();
    values.pop_back();

    values.push_back(nextTop + top);
}

void RPNStack::subtract() {
    if (values.size() < 2) {
        throw RPNStackException();
    }

    double top = values.back();
    values.pop_back();
    double nextTop = values.back();
    values.pop_back();

    values.push_back(nextTop - top);
}

void RPNStack::multiply() {
    if (values.size() < 2) {
        throw RPNStackException();
    }

    double top = values.back();
    values.pop_back();
    double nextTop = values.back();
    values.pop_back();

    values.push_back(nextTop * top);
}

void RPNStack::divide() {
    if (values.size() < 2) {
        throw RPNStackException();
    }

    double top = values.back();
    if (top == 0) {
        throw RPNDivByZeroException();
    }
    values.pop_back();
    double nextTop = values.back();
    values.pop_back();

    values.push_back(nextTop / top);
}

void RPNStack::duplicate() {
    if (values.empty()) {
        throw RPNStackException();
    }

    double top = values.back();
    values.push_back(top);
}

void RPNStack::swap() {
    if (values.size() < 2) {
        throw RPNStackException();
    }

    double top = values.back();
    values.pop_back();
    double nextTop = values.back();
    values.pop_back();

    values.push_back(top);
    values.push_back(nextTop);
}

void RPNStack::clear() {
    // TODO: does this free memory for original values?
    this->values = std::vector<double>();
}

std::string RPNStack::stringify() {
    if (values.empty()) {
        return "";
    }

    std::string s = "";
    
    for (std::vector<double>::iterator it = values.begin(); it != values.end(); it++) {
        s += std::to_string(*it) + " ";
    }

    return s.substr(0, s.length() - 1); // omit final space
}
