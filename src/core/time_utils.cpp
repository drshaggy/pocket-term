#include "time_utils.h"

#include <ctime>
#include <iomanip>
#include <sstream>

std::string getCurrentTime() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(&tm, "%H:%M");
    return ss.str();
}

std::string getCurrentDate() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(&tm, "%d %b");
    return ss.str();
}
