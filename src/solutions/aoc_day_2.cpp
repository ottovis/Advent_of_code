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
#include "aoc_day_2.h"
#include "commons.h"
#include "file_utils.h"

AocDay2::AocDay2() : AocDay(day)
{
}

std::vector<std::string> AocDay2::read_input(const std::string &filename) const
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

std::string AocDay2::part1(const std::string &filename, const std::vector<std::string> &extra_args)
{
    int total = 0;
    auto lines = read_input(filename);
    total = solution_day2_part1(lines, 12, 14, 13);
    return std::to_string(total);
}

std::string AocDay2::part2(const std::string &filename, const std::vector<std::string> &extra_args)
{
    int total = 0;
    auto lines = read_input(filename);
    total = solution_day2_part2(lines);
    return std::to_string(total);
}
