#include "core/backtest_engine.hpp"

namespace backtester {

BacktestEngine::BacktestEngine(DataLoader& loader, Strategy& strategy)
    : data_loader_(loader), strategy_(strategy) {}

bool BacktestEngine::initialize() {
    if (!data_loader_.initialize()) {
        return false;
    }

    while (data_loader_.has_next()) {
        event_queue_.push(data_loader_.next_event());
    }

    initialized_ = true;
    return true;
}

bool BacktestEngine::run() {
    if (!initialized_ && !initialize()) {
        return false;
    }

    while (!event_queue_.empty()) {
        auto event = event_queue_.pop();
        if (!event) {
            continue;
        }
        strategy_.on_event(*event, event_queue_);
    }

    return true;
}

EventQueue& BacktestEngine::event_queue() {
    return event_queue_;
}

} // namespace backtester
