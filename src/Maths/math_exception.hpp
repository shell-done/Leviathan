/*
 * File: math_exception.hpp
 * Project: Leviathan
 * Version: 0.1
 * File Created: 07/04/2020 21:47
 * Author: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Last Modified: 18/04/2020 16:10
 * Modified By: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Copyright (c) 2020 - Alexandre THOMAS
 */

#ifndef MATH_EXCEPTION
#define MATH_EXCEPTION

#include <exception>
#include <string>

class MathException : public std::exception {
public:
    inline MathException(std::string what) noexcept {
        m_what = what;
    }

	inline virtual const char* what() const noexcept {
    	return m_what.c_str();
    }

private:
    std::string m_what;
};

#endif // MATH_EXCEPTION