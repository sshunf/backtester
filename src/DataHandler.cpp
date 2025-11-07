#include "../include/DataHandler.hpp"
#include <iostream>

namespace backtester {

CSVDataHandler::CSVDataHandler(std::string fname)
    : filename_(std::move(fname)), file_(filename_) {
        if (!file_.is_open()) {
            std::cerr << "Failed to open file: " << filename_ << "\n"; 
        }
    }

void CSVDataHandler::initialize() {
    // TODO    
    initialized_ = true;
}

void CSVDataHandler::stream_next_event(std::queue<std::unique_ptr<Event>>& event_queue) {
    // TODO
}

bool CSVDataHandler::has_next() const {
    return !file_.eof();
}

} // namespace backtester
