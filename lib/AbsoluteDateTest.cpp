//
// Created by Admin on 02.09.2020.
//
#include "catch.hpp"
#include "Book.h"
#include "../Book.h"

using namespace shop;

TEST_CASE("Check amount", "[IsEqual]")
{
    Book *ks = new Book("Tytul");
    REQUIRE(ks->title == "Tytul");
}

TEST_CASE("Przybory","[ol.amount]")
{
    REQUIRE(ol.amount==5);]
    SECTION("HELO")
    {

    }
}
