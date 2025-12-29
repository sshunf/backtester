#include <gtest/gtest.h>
#include <fstream>
#include "data_loaders/data_loader.hpp"
#include "events/event.hpp"
#include "utils/time_utils.hpp"

namespace {

int count_data_rows(const std::string& path) {
    std::ifstream f(path);
    int lines = 0;
    std::string line;
    while (std::getline(f, line)) {
        ++lines;
    }
    return lines >= 3 ? lines - 3 : 0; // skip headers
}

void expect_first_bar(const std::string& path,
                      const std::string& expected_timestamp,
                      double expected_open,
                      double expected_high,
                      double expected_low,
                      double expected_close,
                      double expected_volume) {
    backtester::CSVDataLoader loader(path);
    ASSERT_TRUE(loader.initialize());

    auto event = loader.next_event();
    ASSERT_NE(event, nullptr);

    auto* bar = dynamic_cast<backtester::BarEvent*>(event.get());
    ASSERT_NE(bar, nullptr);

    EXPECT_EQ(bar->timestamp(),
              backtester::to_unix_microseconds(expected_timestamp));

    EXPECT_NEAR(bar->open(),   expected_open,   1e-6);
    EXPECT_NEAR(bar->high(),   expected_high,   1e-6);
    EXPECT_NEAR(bar->low(),    expected_low,    1e-6);
    EXPECT_NEAR(bar->close(),  expected_close,  1e-6);
    EXPECT_NEAR(bar->volume(), expected_volume, 1e-6);
}

void expect_sorted(const std::string& path) {
    backtester::CSVDataLoader loader(path);
    ASSERT_TRUE(loader.initialize());
    ASSERT_TRUE(loader.has_next());

    auto prev = loader.next_event();
    while (loader.has_next()) {
        auto current = loader.next_event();
        ASSERT_NE(current, nullptr);
        EXPECT_LT(prev->timestamp(), current->timestamp());
        prev = std::move(current);
    }
}

} // namespace

TEST(CSVDataLoaderTests, CountsDailyRows) {
    std::string path = std::string(PROJECT_ROOT) + "/data/AAPL_data_1d.csv";

    backtester::CSVDataLoader loader(path);
    ASSERT_TRUE(loader.initialize());
    ASSERT_TRUE(loader.has_next());

    int count = 0;
    while (loader.has_next()) {
        loader.next_event();
        ++count;
    }

    EXPECT_EQ(count, count_data_rows(path));
}

TEST(CSVDataLoaderTests, CountsIntradayRows) {
    std::string path = std::string(PROJECT_ROOT) + "/data/AAPL_data_15m.csv";

    backtester::CSVDataLoader loader(path);
    ASSERT_TRUE(loader.initialize());

    int count = 0;
    while (loader.has_next()) {
        loader.next_event();
        ++count;
    }

    EXPECT_EQ(count, count_data_rows(path));
}

TEST(CSVDataLoaderTests, FirstDailyEventParsedCorrectly) {
    expect_first_bar(
        std::string(PROJECT_ROOT) + "/data/AAPL_data_1d.csv",
        "2025-11-03",
        270.15812755648943,
        270.5877038096653,
        265.9921525413924,
        268.7894287109375,
        50194600.0);
}

TEST(CSVDataLoaderTests, FirstIntradayEventParsedCorrectly) {
    expect_first_bar(
        std::string(PROJECT_ROOT) + "/data/AAPL_data_15m.csv",
        "2025-12-01 14:30:00+00:00",
        278.1499938964844,
        278.7699890136719,
        276.45001220703125,
        276.4801025390625,
        2290946.0);
}

TEST(CSVDataLoaderTests, DailyEventsAreSortedByTimestamp) {
    expect_sorted(std::string(PROJECT_ROOT) + "/data/AAPL_data_1d.csv");
}

TEST(CSVDataLoaderTests, IntradayEventsAreSortedByTimestamp) {
    expect_sorted(std::string(PROJECT_ROOT) + "/data/AAPL_data_15m.csv");
}
