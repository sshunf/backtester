#include "utils/time_utils.hpp"
#include <chrono>
#include <sstream>
#include <iomanip>
#include <stdexcept>

namespace backtester {

static std::time_t timegm_portable(std::tm* utc_tm) {
#if defined(_WIN32)
    return _mkgmtime(utc_tm);
#else
    return timegm(utc_tm);
#endif
}

int64_t to_unix_microseconds(const std::string& datetime) {
    std::string datetime_str = datetime;

    int tz_offset_seconds = 0;
    bool has_tz_offset = false;

    if (datetime_str.size() >= 6) {
        char sign  = datetime_str[datetime_str.size() - 6];
        char colon = datetime_str[datetime_str.size() - 3];
        if ((sign == '+' || sign == '-') && colon == ':') {
            int offset_hours   = std::stoi(datetime_str.substr(datetime_str.size() - 5, 2));
            int offset_minutes = std::stoi(datetime_str.substr(datetime_str.size() - 2, 2));

            tz_offset_seconds = offset_hours * 3600 + offset_minutes * 60;
            if (sign == '-') tz_offset_seconds = -tz_offset_seconds;

            datetime_str.resize(datetime_str.size() - 6);
            has_tz_offset = true;
        }
    }

    std::tm utc_tm = {};
    std::istringstream parser(datetime_str);

    parser >> std::get_time(&utc_tm, "%Y-%m-%d %H:%M:%S");
    if (parser.fail()) {
        parser.clear();
        parser.str(datetime_str);
        parser >> std::get_time(&utc_tm, "%Y-%m-%d");
        if (parser.fail()) {
            throw std::runtime_error("Failed to parse timestamp: " + datetime);
        }
    }

    std::time_t epoch_seconds = timegm_portable(&utc_tm);

    if (has_tz_offset) {
        epoch_seconds -= tz_offset_seconds;
    }

    return static_cast<int64_t>(epoch_seconds) * 1'000'000;
}

} // namespace backtester
