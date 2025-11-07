#pragma once

#include "Events.hpp"
#include <fstream>
#include <memory>
#include <queue>
#include <string>

namespace backtester
{

class DataHandler
{
  public:
    virtual ~DataHandler() = default;
    virtual void initialize() = 0;
    virtual void stream_next_event(std::queue<std::unique_ptr<Event>>& event_queue) = 0;
    virtual bool has_next() const = 0;
};

class CSVDataHandler : public DataHandler
{
  private:
    std::string filename_;
    std::ifstream file_;
    bool initialized_ = false;

  public:
    explicit CSVDataHandler(std::string fname);

    void initialize() override;
    void stream_next_event(std::queue<std::unique_ptr<Event>>& event_queue) override;
    bool has_next() const override;
};

} // namespace backtester
