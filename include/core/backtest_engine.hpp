#pragma once

#include "core/event_queue.hpp"
#include "data_loaders/data_loader.hpp"
#include "strategy/strategy.hpp"

namespace backtester {

class BacktestEngine {
  public:
    BacktestEngine(DataLoader& loader, Strategy& strategy);

    bool initialize();
    bool run();

    EventQueue& event_queue();

  private:
    DataLoader& data_loader_;
    Strategy& strategy_;
    EventQueue event_queue_;
    bool initialized_ = false;
};

} // namespace backtester
