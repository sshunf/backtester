#pragma once
#include <string>

enum class Action : uint8_t
{
    SELL,
    BUY
};

enum class EventType : uint8_t
{
    MARKET,
    SIGNAL,
    ORDER,
    FILL
};
struct Event
{
    virtual ~Event() = default;
    virtual EventType type() const = 0;
};

struct MarketEvent : Event
{
    EventType type() const override { return EventType::MARKET; }
};

struct SignalEvent : Event
{
    std::string symbol;
    Action action;
    EventType type() const override { return EventType::SIGNAL; }

    SignalEvent(std::string sym, Action act) : symbol(std::move(sym)), action(act) {}
};

struct OrderEvent : Event
{
    std::string symbol;
    Action action;
    int quantity;
    EventType type() const override { return EventType::ORDER; }

    OrderEvent(std::string sym, Action act, int qty)
        : symbol(std::move(sym)), action(act), quantity(qty)
    {
    }
};

struct FillOrder : Event
{
    std::string symbol;
    Action action;
    int quantity;
    double fill_price;

    EventType type() const override { return EventType::FILL; }
};
