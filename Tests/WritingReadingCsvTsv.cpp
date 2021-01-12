//
// Created by Admin on 12.01.2021.
//

#include <gtest/gtest.h>
#include "../ServiceCsvTsv.h"

#include "../tests.h"

using testing::Eq;

namespace
{
    class TsvCsvTest : public ::testing::Test
    {
    public:
        ServiceCsvTsv s1;
        TsvCsvTest()
        {
            s1;
        }
    };
}

TEST_F(TsvCsvTest,joinString)
{
    std::vector<std::string> inp = {"Moj","string","ktory","jest","laczony"};
    std::string delimiter = "AABBCC";
    std::string out = s1.join(inp,delimiter);

    EXPECT_EQ("MojAABBCCstringAABBCCktoryAABBCCjestAABBCClaczony",out);
}