#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h> // getopt

#include "aoc_days.h"
#include "file_utils.h"

#define DASH_D 0x01
#define DASH_P 0x02
#define DASH_F 0x04
#define DASH_T 0x08
#define DASH_R 0x10

#define OPTS_RUN_FILE (DASH_D | DASH_P | DASH_F)
#define OPTS_RUN_REGRESSION (DASH_R)

void usage(const std::string &prog_name)
{
    std::cerr << "Usage for " << prog_name << std::endl;
    std::cerr << "   Run one file: " << prog_name << " -d day -p part -f filename [extra_args...]" << std::endl;
}

int main(int argc, char *argv[])
{
    AocDays days;

    int day = 0;
    double part = 0;
    bool regression = false;
    std::string filename = "";
    std::string result = "";
    std::vector<std::string> extra_args;

    int given_opts = 0;
    int opt;

    // getopt parsing of command line parameters
    while ((opt = getopt(argc, argv, "d:p:f:t:r:")) != -1)
    {
        switch (opt)
        {
            case 'd':
                day = strtod(optarg, nullptr);
                given_opts |= DASH_D;
                break;
            case 'p':
                part = strtod(optarg, nullptr);
                given_opts |= DASH_P;
                break;
            case 'f':
                filename = std::string(optarg);
                given_opts |= DASH_F;
                break;
            default:
                std::cerr << "Invalid option " << opt << " given" << std::endl;
                usage(argv[0]);
                exit(8);
                break;
        }
    }

    // check for valid option combination and get any extra arguments if running from a file
    if (given_opts == OPTS_RUN_FILE)
    {
        for (int i = optind; i < argc; i++)
        {
            extra_args.emplace_back(argv[i]);
        }
    }
    else
    {
        std::cerr << "Invalid set of options given" << std::endl;
        usage(argv[0]);
        exit(8);
    }

    // Actually do stuff
    if (filename != "")
    {
        auto aoc_day = days.get_day(day);
        if (!aoc_day)
        {
            std::cerr << "Program for day " << day << " not found!!!" << std::endl;
            exit(8);
        }
        if (part == 1)
        {
            result = aoc_day->part1(filename, extra_args);
        }
        else if (part == 2)
        {
            result = aoc_day->part2(filename, extra_args);
        }
        else
        {
            std::cerr << "Invalid part" << part << " specified!!!" << std::endl;
            exit(8);
        }
        std::cout << "***Day " << day << " Part " << part << " for file " << filename << " has result " << result << std::endl;
    }
    return 0;
}
