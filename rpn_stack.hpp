/**
 * @file rpn_stack.hpp
 * @author Andrew Obler (andrewobler@gmail.com)
 * @brief A model for a simple RPN calculator.
 * @version 0.1
 * @date 2019-12-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

#include <exception>
#include <string>
#include <vector>

/**
 * Thrown when an operation is attempted on an RPNStack with insufficient
 * operands, e.g. trying to add on a stack with less than two values.
 */
class RPNStackException : public std::exception {
    public:
        /**
         * Produce a descriptive message.
         * @return the message as a char pointer
         */
        const char* what() const noexcept;
};

/**
 * Thrown when RPNStack::divide() is attempted on a stack with 0 as the top
 * value.
 */
class RPNDivByZeroException : public std::exception {
    public:
        /**
         * Produce a descriptive message.
         * 
         * @return the message as a char pointer
         */
        const char* what() const noexcept;
};

/**
 * Represents a stack of numbers in an RPN calculator.
 */
class RPNStack {
    private:
        /**
         * The core stack of numerical values.
         */
        std::vector<double> values;
    
    public:
        /**
         * Default constructor. Produces an empty internal stack.
         */
        RPNStack() = default;

        /**
         * Create a stack with given initial values.
         * 
         * @param count the number of values in the vals parameter
         * @param ... the initial values for the stack, pushed in order from
         *            first to last; values must be explicit doubles
         */
        RPNStack(unsigned int count, ...);

        /**
         * Default destructor. No special behavior.
         */
        ~RPNStack() = default;

        /**
         * Push a new value onto the stack.
         * 
         * @param val the value to push
         */
        void push(double val);

        /**
         * Pop the top value from the stack.
         * 
         * @throw RPNStackException if there are no values on the stack
         */
        void pop();

        /**
         * Add the two top values on the stack and push the result.
         * 
         * @throw RPNStackException if there are less than two values on the stack
         */
        void add();

        /**
         * Subtract the topmost value on the stack from the second-topmost and
         * push the result.
         * 
         * @throw RPNStackException if there are less than two values on the stack
         */
        void subtract();

        /**
         * Multiply the two top values on the stack and push the result.
         * 
         * @throw RPNStackException if there are less than two values on the stack
         */
        void multiply();

        /**
         * Divide the topmost value on the stack from the second-topmost and
         * push the result.
         * 
         * @throw RPNStackException if there are less than two values on the stack
         * @throw RPNDivByZeroException if the topmost value is 0
         */
        void divide();

        /**
         * Duplicate the topmost element of the stack.
         * 
         * @throw RPNStackException if there are no values on the stack
         */
        void duplicate();

        /**
         * Swap the top two elements of the stack.
         * 
         * @throw RPNStackException if there are less than two values on the stack
         */
        void swap();

        /**
         * Clear all values from the stack.
         */
        void clear();

        /**
         * Render the stack as a string, in the form <val1> <val2> ...
         * 
         * @return a string, e.g. "10 43 -3"
         */
        std::string stringify();
};
