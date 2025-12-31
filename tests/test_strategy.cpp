#include <algorithm>
#include <fstream>
#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "core/backtest_engine.hpp"
#include "core/event_queue.hpp"
#include "data_loaders/data_loader.hpp"
#include "strategy/strategy.hpp"

class CountingStrategy : public backtester::Strategy {
  public:
    void on_event(const backtester::Event& event, backtester::EventQueue&) override {
        timestamps.push_back(event.timestamp());
    }

    std::vector<int64_t> timestamps;
};

TEST(BacktestEngineTests, ProcessesEventsInOrder) {
    std::string path = std::string(PROJECT_ROOT) + "/data/AAPL_data_1d.csv";

    backtester::CSVDataLoader loader(path);
    CountingStrategy strategy;
    backtester::BacktestEngine engine(loader, strategy);

    ASSERT_TRUE(engine.initialize());
    ASSERT_TRUE(engine.run());

    std::ifstream file(path);
    int expected_rows = 0;
    std::string line;
    while (std::getline(file, line)) {
        expected_rows++;
    }

    ASSERT_EQ(strategy.timestamps.size(), static_cast<size_t>(expected_rows - 3));
    ASSERT_TRUE(std::is_sorted(strategy.timestamps.begin(), strategy.timestamps.end()));
}
