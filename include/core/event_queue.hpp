#pragma once

#include "events/event.hpp"
#include <memory>
#include <deque>

namespace backtester {

class EventQueue {
  public:
    void push(std::unique_ptr<Event> event);
    std::unique_ptr<Event> pop();

    const Event* peek() const;
    bool empty() const;
    std::size_t size() const;

  private:
    // Note: currently assumes events are pushed in order (maybe later use heap instead)
    std::deque<std::unique_ptr<Event>> queue_;
};

} // namespace backtester
