#include "gtest/gtest.h"
#include "data/data_loader.hpp"

TEST(DataHandlerTests, example) {
    backtester::CSVDataLoader data_handler("../data/AAPL_data.csv");
}
