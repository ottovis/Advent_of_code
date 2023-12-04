#ifndef __AOC_DAY_2__
#define __AOC_DAY_2__

#include "aoc_day.h"

class AocDay2 : public AocDay
{
private:
    int day = 1;
    std::vector<std::string> read_input(const std::string &filename) const;

public:
    AocDay2();
    ~AocDay2() final = default;
    std::string part1(const std::string &filename, const std::vector<std::string> &extra_args) override;
    std::string part2(const std::string &filename, const std::vector<std::string> &extra_args) override;
};

#endif
