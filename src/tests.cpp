#include "commons.h"
#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST(getLowestFromPairBasedOnLoc_test, BasicAssertions)
{
    locAndNum_t higher = {10, 5};
    locAndNum_t lower = {2, 8};
    locAndNum_t invalid = {0, 0};
    locAndNum_t invalid2 = {-1, 0};

    auto [locResult, numResult] = getLowestFromPairBasedOnLoc(higher, lower);
    auto [locResultInvalid, numResultInvalid] = getLowestFromPairBasedOnLoc(invalid, lower);
    auto [locResultInvalid2, numResultInvalid2] = getLowestFromPairBasedOnLoc(higher, invalid);
    auto [locResultInvalid3, numResultInvalid3] = getLowestFromPairBasedOnLoc(invalid2, invalid);
    EXPECT_EQ(locResult, 2);
    EXPECT_EQ(numResult, 8);
    EXPECT_EQ(locResultInvalid, 2);
    EXPECT_EQ(numResultInvalid, 8);
    EXPECT_EQ(locResultInvalid2, 10);
    EXPECT_EQ(numResultInvalid2, 5);
    EXPECT_EQ(locResultInvalid3, -1);
    EXPECT_EQ(numResultInvalid3, -1);
}

TEST(getIntFromString_test, BasicAssertions)
{
    std::string line1 = "ad141aab23c2caa";
    auto [locResult1, numResult1] = getIntFromString(line1.begin(), line1.end());
    auto [locResult2, numResult2] = getIntFromString(line1.rbegin(), line1.rend());
    EXPECT_EQ(locResult1, 2);
    EXPECT_EQ(numResult1, 1);
    EXPECT_EQ(locResult2, 3);
    EXPECT_EQ(numResult2, 2);
}

TEST(getFirstStringNumberFromString_test, BasicAssertions)
{
    std::string line1 = "two1nine3";
    std::string line2 = "rwe132fad23";
    auto [locResult1, numResult1] = getFirstStringNumberFromString(line1, false);
    auto [locResult2, numResult2] = getFirstStringNumberFromString(line1, true);
    auto [locResult3, numResult3] = getFirstStringNumberFromString(line2, false);
    auto [locResult4, numResult4] = getFirstStringNumberFromString(line2, true);
    EXPECT_EQ(locResult1, 0);
    EXPECT_EQ(numResult1, 2);
    EXPECT_EQ(locResult2, 1);
    EXPECT_EQ(numResult2, 9);
    EXPECT_EQ(numResult3, -1);
    EXPECT_EQ(locResult3, -1);
    EXPECT_EQ(numResult4, -1);
    EXPECT_EQ(locResult4, -1);
}

TEST(getTotalValue_test, BasicAssertions)
{
    std::string line1 = "two1nine";
    auto i1 = getTotalValue(4, 3);
    auto i2 = getTotalValue(9, 1);
    auto i3 = getTotalValue(0, 1);
    auto i4 = getTotalValue(10, 1);
    auto i5 = getTotalValue(3, 10);
    auto i6 = getTotalValue(3, 0);
    EXPECT_EQ(i1, 43);
    EXPECT_EQ(i2, 91);
    EXPECT_EQ(i3, -1);
    EXPECT_EQ(i4, -1);
    EXPECT_EQ(i5, -1);
    EXPECT_EQ(i6, -1);
}

TEST(day1_part1_test, BasicAssertions)
{
    std::vector<std::string> lines = {"1abc2",
                                      "pqr3stu8vwx",
                                      "a1b2c3d4e5f",
                                      "treb7uchet"};
    int total = solution_day1_part1(lines);
    EXPECT_EQ(total, 142);
}

TEST(day1_part2_test, BasicAssertions)
{
    std::vector<std::string> lines = {"two1nine",
                                      "eightwothree",
                                      "abcone2threexyz",
                                      "xtwone3four",
                                      "4nineeightseven2",
                                      "zoneight234",
                                      "7pqrstsixteen"};
    int total = solution_day1_part2(lines);
    EXPECT_EQ(total, 281);
}

TEST(getSetFromString_test, BasicAssertions)
{
    std::string stringSet1 = "3 blue, 4 red";
    std::string stringSet2 = " 1 red, 2 green";
    std::string stringSet3 = "2 green";
    auto set1 = getSetFromString(stringSet1);
    auto set2 = getSetFromString(stringSet2);
    auto set3 = getSetFromString(stringSet3);
    EXPECT_EQ(set1.blue, 3);
    EXPECT_EQ(set1.green, 0);
    EXPECT_EQ(set1.red, 4);
    EXPECT_EQ(set2.blue, 0);
    EXPECT_EQ(set2.green, 2);
    EXPECT_EQ(set2.red, 1);
    EXPECT_EQ(set3.blue, 0);
    EXPECT_EQ(set3.green, 2);
    EXPECT_EQ(set3.red, 0);
}

TEST(getGameFromString_test, BasicAssertions)
{
    std::string line = "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green";
    auto game = getGameFromString(line);
    EXPECT_EQ(game.ID, 1);
    EXPECT_EQ(game.sets.size(), 3);
    EXPECT_EQ(game.sets[0].blue, 3);
    EXPECT_EQ(game.sets[0].green, 0);
    EXPECT_EQ(game.sets[0].red, 4);
    EXPECT_EQ(game.sets[1].blue, 6);
    EXPECT_EQ(game.sets[1].green, 2);
    EXPECT_EQ(game.sets[1].red, 1);
    EXPECT_EQ(game.sets[2].blue, 0);
    EXPECT_EQ(game.sets[2].green, 2);
    EXPECT_EQ(game.sets[2].red, 0);
}

TEST(setMaxValuesGame_test, BasicAssertions)
{
    game_t game;
    game.ID = 1;
    set_t set1 = {4, 5, 6};
    set_t set2 = {4, 2, 9};
    set_t set3 = {1, 7, 3};
    game.sets.push_back(set1);
    game.sets.push_back(set2);
    game.sets.push_back(set3);
    setMaxValuesGame(game);
    EXPECT_EQ(game.highMarkBlue, 4);
    EXPECT_EQ(game.highMarkGreen, 7);
    EXPECT_EQ(game.highMarkRed, 9);
}

TEST(getPowerOfGame_test, BasicAssertions)
{   
    std::string line1 = "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green";
    std::string line2 = "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue";

    auto game1 = getGameFromString(line1);
    auto game2 = getGameFromString(line2);

    setMaxValuesGame(game1);
    setMaxValuesGame(game2);

    int power1 = getPowerOfGame(game1);
    int power2 = getPowerOfGame(game2);

    EXPECT_EQ(power1, 48);
    EXPECT_EQ(power2, 12);
}

TEST(day2_part1_test, BasicAssertions)
{
    std::vector<std::string> lines = {"Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green",
                                      "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue",
                                      "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red",
                                      "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red",
                                      "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green"};
    int total = solution_day2_part1(lines, 12, 14, 13);
    EXPECT_EQ(total, 8);
}

TEST(day2_part2_test, BasicAssertions)
{
    std::vector<std::string> lines = {"Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green",
                                      "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue",
                                      "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red",
                                      "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red",
                                      "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green"};
    int total = solution_day2_part2(lines);
    EXPECT_EQ(total, 2286);
}
