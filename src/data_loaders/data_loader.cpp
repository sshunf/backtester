#include "data_loaders/data_loader.hpp"
#include "utils/time_utils.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <filesystem>

namespace backtester {

CSVDataLoader::CSVDataLoader(std::string fname)
    : filename_(std::move(fname)) 
{
    std::filesystem::path filepath(filename_);
    if (filepath.extension() != ".csv") {
        std::cerr << "File is not a csv file..." << std::endl;
        return;
    }
}

bool CSVDataLoader::initialize() {
    std::ifstream csv_file(filename_);
    if (!csv_file.is_open()) {
        std::cerr << "Error opening csv file..." << std::endl;
        return false;
    }

    std::string row;

    while (std::getline(csv_file, row)) {
        if (auto event = parse_row(row)) {
            events_.push_back(std::move(event));
        }
    }
    cursor_ = 0;

    std::sort(events_.begin(), events_.end(),
        [](const std::unique_ptr<Event>& event_a, const std::unique_ptr<Event>& event_b) {
            return event_a->timestamp() < event_b->timestamp();
        });

    return true;
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
    // 1: Close
    // 2: High
    // 3: Low
    // 4: Open
    // 5: Volume

    if (fields.size() < 6) {
        return nullptr;
    }

    int64_t timestamp = 0;

    const std::string& datetime = fields[0];
    if (datetime.find_first_not_of("0123456789-: +T") != std::string::npos) {
        return nullptr;
    }

    try { 
        int64_t timestamp = to_unix_microseconds(fields[0]);
        double close = std::stod(fields[1]);
        double high  = std::stod(fields[2]);
        double low   = std::stod(fields[3]);
        double open  = std::stod(fields[4]);
        double volume = std::stod(fields[5]);

        return std::make_unique<BarEvent>(timestamp, close, high, low, open, volume);
    } 
    catch (...) {
        std::cerr << "Could not parse row..." << std::endl;
        return nullptr;
    }
}

} // namespace backtester
