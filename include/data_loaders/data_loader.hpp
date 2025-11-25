#pragma once

#include "events/event.hpp"
#include <fstream>
#include <memory>
#include <queue>
#include <string>

namespace backtester
{

class DataLoader
{
  public:
    virtual ~DataLoader() = default;
    virtual void initialize() = 0;
    virtual std::unique_ptr<Event> next_event() = 0;
    virtual bool has_next() const = 0;
};

class CSVDataLoader : public DataLoader
{
  private:
    std::string filename_;
    std::vector<std::unique_ptr<Event>> events_;
    size_t cursor_ = 0;

  public:
    explicit CSVDataLoader(std::string fname);

    void initialize() override;
    std::unique_ptr<Event> next_event() override;
    bool has_next() const override;
  
  private:
    std::unique_ptr<Event> parse_row(const std::string& row);
};

} // namespace backtester
