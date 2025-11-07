#pragma once

#include <cstdint>
#include <string>

namespace backtester {

enum class Action : uint8_t {
    BUY,
    SELL
};

enum class EventType : uint8_t {
    MARKET,
    SIGNAL,
    ORDER,
    FILL
};

class Event {
public:
    virtual ~Event() = default;
    virtual EventType type() const = 0;
};

class MarketEvent : public Event {
public:
    EventType type() const override { return EventType::MARKET; }
};

class SignalEvent : public Event {
public:
    std::string symbol;
    Action action;

    SignalEvent(std::string sym, Action act)
        : symbol(std::move(sym)), action(act) {}

    EventType type() const override { return EventType::SIGNAL; }
};

class OrderEvent : public Event {
public:
    std::string symbol;
    Action action;
    int quantity;

    OrderEvent(std::string sym, Action act, int qty)
        : symbol(std::move(sym)), action(act), quantity(qty) {}

    EventType type() const override { return EventType::ORDER; }
};

class FillEvent : public Event {
public:
    Action action;
    double price;
    int quantity;

    FillEvent(Action act, double price_, int qty)
        : action(act), price(price_), quantity(qty) {}

    EventType type() const override { return EventType::FILL; }
};

} // namespace backtester
