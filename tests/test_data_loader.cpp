#include <gtest/gtest.h>
#include "data_loaders/data_loader.hpp"
#include "events/event.hpp"
#include "utils/time_utils.hpp"

TEST(CSVDataLoaderTests, CountRows) {
    std::string path = std::string(PROJECT_ROOT) + "/data/AAPL_data.csv";
    std::cout << "Looking for CSV at: " << path << std::endl;

    backtester::CSVDataLoader loader(path);
    loader.initialize();

    int count = 0;
    ASSERT_EQ(loader.has_next(), true);
    while (loader.has_next()) {
        loader.next_event();
        count++;
    }

    // Count expected rows dynamically
    std::ifstream f(path);
    int expected = 0;
    std::string line;
    while (std::getline(f, line)) expected++;

    ASSERT_EQ(count, expected-3); // exclude the first three rows of dataset which contain labels
}

TEST(CSVDataLoaderTests, FirstEventParsedCorrectly) {
    std::string path = std::string(PROJECT_ROOT) + "/data/AAPL_data.csv";
    backtester::CSVDataLoader loader(path);
    loader.initialize();

    auto event = loader.next_event();
    ASSERT_NE(event, nullptr);

    auto* bar = dynamic_cast<backtester::BarEvent*>(event.get());
    ASSERT_NE(bar, nullptr);

    EXPECT_EQ(bar->timestamp(),
              backtester::to_unix_microseconds("2025-01-02"));

    EXPECT_NEAR(bar->open(), 248.04944371, 1e-6);
    EXPECT_NEAR(bar->high(), 248.21885574, 1e-6);
    EXPECT_NEAR(bar->low(),  240.96460876, 1e-6);
    EXPECT_NEAR(bar->close(),242.98742676, 1e-6);
    EXPECT_NEAR(bar->volume(),55740700.0,  1e-6);
}

TEST(CSVDataLoaderTests, EventsAreSortedByTimestamp) {
    std::string path = std::string(PROJECT_ROOT) + "/data/AAPL_data.csv";
    backtester::CSVDataLoader loader(path);
    loader.initialize();

    auto e1 = loader.next_event();
    auto e2 = loader.next_event();
    auto e3 = loader.next_event();

    ASSERT_NE(e1, nullptr);
    ASSERT_NE(e2, nullptr);
    ASSERT_NE(e3, nullptr);

    EXPECT_LT(e1->timestamp(), e2->timestamp());
    EXPECT_LT(e2->timestamp(), e3->timestamp());
}
