#include <map>

#include "aoc_day.h"
#include "aoc_days.h"
// includes for each day will go here
#include "aoc_day_0.h"
#include "aoc_day_1.h"
#include "aoc_day_2.h"

AocDays::AocDays()
{
    // adding each member to the map goes here
    m_days[0] = std::make_shared<AocDay0>(AocDay0());
    m_days[1] = std::make_shared<AocDay1>(AocDay1());
    m_days[2] = std::make_shared<AocDay2>(AocDay2());
}

AocDays::~AocDays()
{
    // delete all of the days solutions
    m_days.clear();
}

std::shared_ptr<AocDay> AocDays::get_day(const int &day)
{
    return m_days[day];
}
