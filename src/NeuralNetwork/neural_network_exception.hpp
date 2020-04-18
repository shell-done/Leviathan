/*
 * File: neural_network_exception.hpp
 * Project: Leviathan
 * Version: 0.1
 * File Created: 11/04/2020 19:02
 * Author: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Last Modified: 18/04/2020 16:10
 * Modified By: Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * -----
 * Copyright (c) 2020 - Alexandre THOMAS
 */

#ifndef NEURAL_NETWORK_EXCEPTION
#define NEURAL_NETWORK_EXCEPTION

#include <exception>
#include <string>

class NeuralNetworkException : public std::exception {
public:
    inline NeuralNetworkException(std::string what) noexcept {
        m_what = what;
    }

	inline virtual const char* what() const noexcept {
    	return m_what.c_str();
    }

private:
    std::string m_what;
};

#endif // NEURAL_NETWORK_EXCEPTION