#pragma once
#include <algorithm>
#include <cassert>
#include <ctype.h>
#include <iostream>
#include <map>
#include <string>

using loc_t = int;
using num_t = int;

using locAndNum_t = std::pair<loc_t, num_t>;

static const std::map<std::string, int, std::less<>> strToIntLUT{
    {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

static locAndNum_t getLowestFromPairBasedOnLoc(const locAndNum_t &p1, const locAndNum_t &p2)
{
    if (p1.second <= 0 && p2.second <= 0)
    {
        return {-1, -1};
    }

    if (p1.second <= 0)
    {
        return p2;
    }
    if (p2.second <= 0)
    {
        return p1;
    }

    if (p1.first <= p2.first)
    {
        return p1;
    }
    else
    {
        return p2;
    }
}

static int getTotalValue(int timesTen, int raw)
{
    if (timesTen < 1 || raw < 1 || timesTen > 9 || raw > 9)
    {
        return -1;
    }

    return ((timesTen * 10) + raw);
}

template <typename T1, typename T2>
static locAndNum_t getIntFromString(const T1 &it1, const T2 &it2)
{
    auto it = std::find_if(it1, it2, [](auto &c)
                           {
                            if(isdigit(c)) 
                            {return true;}
                           else 
                            {return false;} });
    if (it == it2)
    {
        return {0, 0};
    }
    return {std::distance(it1, it), *it - '0'};
}

static locAndNum_t getFirstStringNumberFromString(const std::string &line, const bool &inverse)
{
    int loc = -1;
    int num = -1;
    for (const auto &[numStr, numInt] : strToIntLUT)
    {
        int innerLoc = 0;
        if (line.find(numStr) == std::string::npos)
        {
            continue;
        }
        if (!inverse)
        {
            innerLoc = line.find(numStr);
        }
        else
        {
            innerLoc = line.size() - numStr.size() - line.rfind(numStr);
        }
        if (innerLoc >= 0 && innerLoc < loc || loc == -1)
        {
            loc = innerLoc;
            num = numInt;
        }
    }
    if (loc == -1)
    {
        return {-1, -1};
    }
    else
    {
        return {loc, num};
    }
}

static int solution_day1_part1(const std::vector<std::string> &lines)
{
    int total = 0;
    for (const auto &line : lines)
    {
        auto [locStart, numStart] = getIntFromString(line.begin(), line.end());
        auto [locEnd, numEnd] = getIntFromString(line.rbegin(), line.rend());
        (void)locStart;
        (void)locEnd;
        total += (numStart * 10) + numEnd;
    }
    return total;
}

static int solution_day1_part2(const std::vector<std::string> &lines)
{
    int total = 0;
    for (const auto &line : lines)
    {
        auto intStart = getIntFromString(line.begin(), line.end());
        auto intEnd = getIntFromString(line.rbegin(), line.rend());

        auto strStart = getFirstStringNumberFromString(line, false);
        auto strEnd = getFirstStringNumberFromString(line, true);

        auto [bestStart, numBestStart] = getLowestFromPairBasedOnLoc(intStart, strStart);
        auto [bestEnd, numBestEnd] = getLowestFromPairBasedOnLoc(intEnd, strEnd);
        (void)bestStart;
        (void)bestEnd;

        total += getTotalValue(numBestStart, numBestEnd);
    }
    return total;
}

using set_t = struct
{
    int blue = 0;
    int green = 0;
    int red = 0;
};

using game_t = struct
{
    int ID = -1;
    std::vector<set_t> sets = {};
    int highMarkRed = 0;
    int highMarkGreen = 0;
    int highMarkBlue = 0;
};

static set_t getSetFromString(const std::string &stringSet)
{
    set_t set;
    // "3 blue, 4 red"
    if (int loc = stringSet.find(" blue"); loc != std::string::npos)
    {
        std::string innerStringSet = stringSet.substr(0, loc);
        if (int innerLoc = innerStringSet.rfind(", "); innerLoc != std::string::npos)
        {
            set.blue = std::stoi(innerStringSet.substr(innerLoc + 2));
        }
        else
        {
            set.blue = std::stoi(innerStringSet);
        }
    }
    if (int loc = stringSet.find(" green"); loc != std::string::npos)
    {
        std::string innerStringSet = stringSet.substr(0, loc);
        if (int innerLoc = innerStringSet.rfind(", "); innerLoc != std::string::npos)
        {
            set.green = std::stoi(innerStringSet.substr(innerLoc + 2));
        }
        else
        {
            set.green = std::stoi(innerStringSet);
        }
    }
    if (int loc = stringSet.find(" red"); loc != std::string::npos)
    {
        std::string innerStringSet = stringSet.substr(0, loc);
        if (int innerLoc = innerStringSet.rfind(", "); innerLoc != std::string::npos)
        {
            set.red = std::stoi(innerStringSet.substr(innerLoc + 2));
        }
        else
        {
            set.red = std::stoi(innerStringSet);
        }
    }
    return set;
}

static game_t getGameFromString(const std::string &line)
{
    // "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"
    game_t game;

    std::string gameNrStr = line.substr(line.find("Game ") + sizeof("Game ") - 1, line.find(":"));
    try
    {
        game.ID = std::stoi(gameNrStr);
    }
    catch (const std::exception &e)
    {
        std::cout << "INVALID INPUT STRING: " << gameNrStr << std::endl;
        return game;
    }
    std::string sets = line.substr(line.find(":") + 2);
    while (true)
    {

        if (sets.find(";") != std::string::npos)
        {
            std::string set = sets.substr(0, sets.find(";"));
            game.sets.push_back(getSetFromString(set));
            sets = sets.substr(sets.find(";") + 1);
        }
        else
        {
            game.sets.push_back(getSetFromString(sets));
            return game;
        }
    }
}

static void setMaxValuesGame(game_t &game)
{
    for (const auto &set : game.sets)
    {
        if (game.highMarkBlue < set.blue)
        {
            game.highMarkBlue = set.blue;
        }
        if (game.highMarkRed < set.red)
        {
            game.highMarkRed = set.red;
        }
        if (game.highMarkGreen < set.green)
        {
            game.highMarkGreen = set.green;
        }
    }
}

static int solution_day2_part1(const std::vector<std::string> &lines, int max_red, int max_blue, int max_green)
{
    int total = 0;
    for (const auto &line : lines)
    {
        auto game = getGameFromString(line);
        setMaxValuesGame(game);
        if (game.highMarkBlue <= max_blue && game.highMarkGreen <= max_green && game.highMarkRed <= max_red)
        {
            total += game.ID;
        }
    }
    return total;
}

static int getPowerOfGame(const game_t &game)
{
    int total = 0;
    total += game.highMarkBlue * game.highMarkGreen * game.highMarkRed;
    return total;
}

static int solution_day2_part2(const std::vector<std::string> &lines)
{
    int total = 0;
    for (const auto &line : lines)
    {
        auto game = getGameFromString(line);
        setMaxValuesGame(game);
        total += getPowerOfGame(game);
    }
    return total;
}
