#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "aoc_day_0.h"
#include "file_utils.h"

AocDay0::AocDay0() : AocDay(day)
{
}

std::vector<double> AocDay0::read_input(const std::string &filename) const
{
    FileUtils fileutils;
    std::vector<std::string> raw_lines;
    std::vector<double> data;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        std::cerr << "Error reading in the data from " << filename << std::endl;
        return data;
    }
    for (const auto &line : raw_lines)
    {
        double l = std::strtod(line.c_str(), nullptr);
        data.push_back(l);
    }
    return data;
}

std::string AocDay0::part1(const std::string &filename, const std::vector<std::string> &extra_args)
{
    std::vector<double> data = read_input(filename);
    double sum = 0;
    for (const auto &value : data)
    {
        sum += value;
    }
    std::ostringstream out;
    out << sum;
    return out.str();
}

std::string AocDay0::part2(const std::string &filename, const std::vector<std::string> &extra_args)
{
    if (extra_args.empty())
    {
        std::cout << "There are " << extra_args.size() << " extra arguments given:" << std::endl;
        std::for_each(extra_args.begin(), extra_args.end(), [](const std::string &s)
                      { std::cout << "[" << s << "]" << std::endl; });
    }

    std::vector<double> data = read_input(filename);
    double sum = 0;

    for (const auto &value : data)
    {
        sum -= value;
    }
    std::ostringstream out;
    out << sum;
    return out.str();
}
