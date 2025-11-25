#include "data/data_loader.hpp"
#include "utils/time_utils.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>

namespace backtester {

CSVDataLoader::CSVDataLoader(std::string fname)
    : filename_(std::move(fname)) 
{}

void CSVDataLoader::initialize() {
    std::ifstream csv_file(filename_);
    if (!csv_file.is_open()) {
        std::cerr << "Error opening csv file..." << std::endl;
        return;
    }

    std::string row;
    std::getline(csv_file, row);

    while (std::getline(csv_file, row)) {
        if (auto event = parse_row(row)) {
            events_.push_back(std::move(events_[cursor_++]));
        }
    }

    std::sort(events_.begin(), events_.end(),
        [](auto& event_a, auto& event_b) {
            return event_a->timestamp() < event_b->timestamp();
        });
}

std::unique_ptr<Event> CSVDataLoader::next_event() {
    if (cursor_ < events_.size()) {
        return std::move(events_[cursor_++]);
    }
    return nullptr;
}

bool CSVDataLoader::has_next() const {
    return cursor_ < events_.size();
}

std::unique_ptr<Event> CSVDataLoader::parse_row(const std::string& row) {
    std::stringstream ss(row);
    std::string token;
    std::vector<std::string> fields;

    while (std::getline(ss, token, ',')) {
        fields.push_back(token);
    }

    // yfinance format
    // 0: Datetime
    // 1: Open
    // 2: High
    // 3: Low
    // 4: Close
    // 5: Adj Close
    // 6: Volume

    if (fields.size() < 7) {
        return nullptr;
    }

    int64_t timestamp = to_unix_microseconds(fields[0]);
    double open  = std::stod(fields[1]);
    double high  = std::stod(fields[2]);
    double low   = std::stod(fields[3]);
    double close = std::stod(fields[4]);
    double volume = std::stod(fields[6]);

    return std::make_unique<BarEvent>(timestamp, open, high, low, close, volume);
}

} // namespace backtester
