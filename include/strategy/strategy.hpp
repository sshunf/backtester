#pragma once

#include "events/event.hpp"

namespace backtester {

class EventQueue;

class Strategy {
  public:
    virtual ~Strategy() = default;
    virtual void on_event(const Event& event, EventQueue& queue) = 0;
};

} // namespace backtester
