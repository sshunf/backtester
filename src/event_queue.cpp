#include "core/event_queue.hpp"

namespace backtester {

void EventQueue::push(std::unique_ptr<Event> event) {
    if (!event) {
        return;
    }

    // const auto ts = event->timestamp();
    queue_.push_back(std::move(event));
}

std::unique_ptr<Event> EventQueue::pop() {
    if (queue_.empty()) {
        return nullptr;
    }

    auto event = std::move(queue_.front());
    queue_.pop_front();
    return event;
}

const Event* EventQueue::peek() const {
    if (queue_.empty()) {
        return nullptr;
    }
    return queue_.front().get();
}

bool EventQueue::empty() const {
    return queue_.empty();
}

std::size_t EventQueue::size() const {
    return queue_.size();
}

} // namespace backtester
