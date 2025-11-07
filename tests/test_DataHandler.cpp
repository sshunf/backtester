#include "gtest/gtest.h"
#include "../include/DataHandler.hpp"

TEST(DataHandlerTests, example) {
    backtester::CSVDataHandler data_handler("../data/AAPL_data.csv");
}
