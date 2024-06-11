#pragma once

#include "../global.hpp"
#include "../exception/custom_exception.hpp"

#include <fstream>

class Logger : public std::ofstream {
    private:
        std::string log_file = "log.txt";
        static Logger* instance;
        Logger();

        std::string getCurrentTime();

    public:
        static Logger* getInstance();

        Logger(Logger const&) = delete;
        void operator=(Logger const&) = delete;
        ~Logger();

        void log(std::string message);
};
