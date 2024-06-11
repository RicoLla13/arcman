#include "logger.hpp"

Logger::Logger() {
    this->open(this->log_file, std::ios::out | std::ios::app);

    if(!this->is_open())
        throw CustomException("[!] #Logger()# -> Could not create/access log file!");
}

Logger::~Logger() {
    this->close();
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

std::string Logger::getCurrentTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d-%m-%Y %X", &tstruct);
    return buf;
}
