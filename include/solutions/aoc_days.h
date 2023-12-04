#ifndef __AOC_DAYS_H__
#define __AOC_DAYS_H__

#include <map>
#include <memory>

#include "aoc_day.h"

class AocDays
{
protected:
    std::map<int, std::shared_ptr<AocDay>> m_days;

public:
    AocDays();
    ~AocDays();
    std::shared_ptr<AocDay> get_day(const int &day);
};

#endif
