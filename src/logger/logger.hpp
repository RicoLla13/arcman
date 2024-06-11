#pragma once

#include "../global.hpp"
#include "../exception/custom_exception.hpp"

#include <fstream>

class Logger : public std::ofstream {
    private:
        std::string log_file = "log.txt";
        Logger();

    public:
        static Logger& getInstance();

        Logger(Logger const&) = delete;
        void operator=(Logger const&) = delete;
        ~Logger();

        std::string getCurrentTime();
};
