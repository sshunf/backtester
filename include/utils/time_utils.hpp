#pragma once
#include <string>

namespace backtester {

int64_t to_unix_microseconds(const std::string& datetime);

} // namespace backtester