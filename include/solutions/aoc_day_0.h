#ifndef __AOC_DAY_0__
#define __AOC_DAY_0__

#include "aoc_day.h"

class AocDay0 : public AocDay
{
private:
    int day = 0;
    std::vector<double> read_input(const std::string &filename) const;

public:
    AocDay0();
    ~AocDay0() final = default;
    std::string part1(const std::string &filename, const std::vector<std::string> &extra_args) override;
    std::string part2(const std::string &filename, const std::vector<std::string> &extra_args) override;
};

#endif
