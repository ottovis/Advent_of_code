#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <algorithm>
#include <iostream>
#include <string>

#include "aoc_day_1.h"
#include "commons.h"
#include "file_utils.h"

AocDay1::AocDay1() : AocDay(day)
{
}

std::vector<std::string> AocDay1::read_input(const std::string &filename) const
{
    FileUtils fileutils;
    std::vector<std::string> raw_lines;
    std::vector<std::string> data;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        std::cerr << "Error reading in the data from " << filename << std::endl;
        return data;
    }
    for (const auto &line : raw_lines)
    {
        data.push_back(line);
    }
    return data;
}

std::string AocDay1::part1(const std::string &filename, const std::vector<std::string> &extra_args)
{
    int total = 0;
    auto lines = read_input(filename);
    total = solution_day1_part1(lines);
    return std::to_string(total);
}

std::string AocDay1::part2(const std::string &filename, const std::vector<std::string> &extra_args)
{
    int total = 0;
    auto lines = read_input(filename);
    total = solution_day1_part2(lines);
    return std::to_string(total);
}
