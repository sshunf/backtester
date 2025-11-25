#include "utils/time_utils.hpp"
#include <chrono>
#include <sstream>
#include <iomanip>
#include <stdexcept>

namespace backtester {

int64_t to_unix_microseconds(const std::string& datetime) {
    std::tm tm = {};
    std::stringstream ss(datetime);

    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    
    if (ss.fail()) {
        ss.clear();
        ss.str(datetime);
        ss >> std::get_time(&tm, "%Y-%m-%d");

        if (ss.fail()) {
            throw std::runtime_error("Failed to parse timestamp: " + datetime);
        }
    }

    std::time_t time_sec = std::mktime(&tm);
    auto tp = std::chrono::system_clock::from_time_t(time_sec);

    return std::chrono::duration_cast<std::chrono::microseconds>(
        tp.time_since_epoch()
    ).count();
}

}