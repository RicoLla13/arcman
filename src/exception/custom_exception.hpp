#pragma once

#include <exception>

class CustomException : public std::exception {
    private:
        std::string message;

    public:
        CustomException(std::string message) : message(message) {}

        const char* what() const noexcept override {
            return message.c_str();
        }
};
