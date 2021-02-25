//
// Created by Admin on 06.02.2021.
//

#include <gtest/gtest.h>
#include "../ServiceCsvTsv.h"



using testing::Eq;

namespace
{
    class TsvCsvTest : public ::testing::Test
    {
    public:
        base::ServiceCsvTsv s1;
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

TEST_F(TsvCsvTest, splitString)
{
    std::string inp = "Ciag,81znakow,81do,81rozdzielenia,81na,8,inne,,81,";
    std::string delimiter = ",81";
    std::vector<std::string>out = s1.split(inp,delimiter);
    std::vector<std::string>refOut = {"Ciag","znakow","do","rozdzielenia","na,8,inne,",","};

    EXPECT_EQ(refOut,out);
}

TEST_F(TsvCsvTest, splitString2)
{
    std::string inp = ",81Ciag,81znakow,81do,81rozdzielenia,81na,8,inne,,81,,81";
    std::string delimiter = ",81";
    std::vector<std::string>out = s1.split(inp,delimiter);
    std::vector<std::string>refOut = {"Ciag","znakow","do","rozdzielenia","na,8,inne,",","};

    EXPECT_EQ(refOut,out);
}