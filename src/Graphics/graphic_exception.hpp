/*
 * File: graphic_exception.hpp
 * Project: Leviathan
 * Version: 0.1
 * File Created: 09/04/2020 17:48
 * Author: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Last Modified: 18/04/2020 16:10
 * Modified By: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Copyright (c) 2020 - Alexandre THOMAS
 */

#ifndef GRAPHIC_EXCEPTION
#define GRAPHIC_EXCEPTION

#include <exception>
#include <string>

class GraphicException : public std::exception {
public:
    inline GraphicException(std::string what) noexcept {
        m_what = what;
    }

	inline virtual const char* what() const noexcept {
    	return m_what.c_str();
    }

private:
    std::string m_what;
};

#endif // GRAPHIC_EXCEPTION