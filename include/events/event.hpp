#pragma once

#include <cstdint>
#include <string>
#include <memory>

namespace backtester {

enum class OrderSide { Buy, Sell };

enum class EventType : uint8_t {
    Trade,
    Quote,
    Bar,
    Order,
    Fill
};


class Event {
public:
    virtual ~Event() = default;
    virtual EventType type() const = 0;
    virtual int64_t timestamp() const = 0;
};


class TradeEvent : public Event {
public:
    TradeEvent(int64_t ts, double price, double size)
        : timestamp_(ts), price_(price), size_(size) {} 

    EventType type() const override { return EventType::Trade; } 
    int64_t timestamp() const override { return timestamp_; }

    double price() const { return price_; }
    double size() const { return size_; }

private:
    int64_t timestamp_;
    double price_;
    double size_;
}; 


class QuoteEvent : public Event {
public:
    QuoteEvent(int64_t ts, double bid_price, double bid_size, double ask_price, double ask_size)
        : timestamp_(ts), bid_price_(bid_price), bid_size_(bid_size), ask_price_(ask_price), ask_size_(ask_size) {}

    EventType type() const override { return EventType::Quote; }
    int64_t timestamp() const override { return timestamp_; }

    double bid_price() const { return bid_price_; }
    double bid_size() const { return bid_size_; }
    double ask_price() const { return ask_price_; }
    double ask_size() const { return ask_size_; }

private:
    int64_t timestamp_;
    double bid_price_;
    double bid_size_;
    double ask_price_;
    double ask_size_;
};


class BarEvent: public Event {
public:
    BarEvent(int64_t ts, double open, double high, double low, double close, double volume)
        : timestamp_(ts), high_(high), low_(low), close_(close), volume_(volume) {}
    
    EventType type() const override { return EventType::Bar; }
    int64_t timestamp() const override { return timestamp_; }
      
    const double open() { return open_; }
    const double high() { return high_; }
    const double low() { return low_; }
    const double close() { return close_; }
    const double volume() { return volume_; }

private:
    int64_t timestamp_;
    double open_;
    double high_;
    double low_;
    double close_;
    double volume_;

};


class OrderEvent : public Event {
public:
    OrderEvent(int64_t ts, std::string sym, OrderSide side, double quantity, double limit_price)
        : timestamp_(ts), symbol_(std::move(sym)), side_(side), quantity_(quantity), limit_price_(limit_price) {}

    EventType type() const override { return EventType::Order; }
    int64_t timestamp() const override { return timestamp_; }

    const std::string& symbol() const { return symbol_; }
    const OrderSide side() const { return side_; }
    const double quantity() const { return quantity_; }
    const double limit_price() const { return limit_price_; }

private:
    int64_t timestamp_;
    std::string symbol_;
    OrderSide side_;
    double quantity_;
    double limit_price_; // 0 if market order
};


class FillEvent : public Event {
public:
    FillEvent(int64_t timestamp, const std::string& symbol, OrderSide side, double quantity, double fill_price)
        : timestamp_(timestamp), symbol_(symbol), side_(side), quantity_(quantity), fill_price_(fill_price) {}

    EventType type() const override { return EventType::Fill; }
    int64_t timestamp() const override { return timestamp_; }

    const std::string& symbol() const { return symbol_; }
    const OrderSide side() const { return side_; }
    const double quantity() const { return quantity_; }
    const double fill_price() const { return fill_price_; }

private:
    int64_t timestamp_;
    std::string symbol_;
    OrderSide side_;
    double quantity_;
    double fill_price_;

};

} // namespace backtester
