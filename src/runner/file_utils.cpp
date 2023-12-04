#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "file_utils.h"

// Really basic way to parse a line based on delimiters.
// parameters:
//  input = the input std::string to split. assume newline is removed, or else it will be addded to the last item
//  delimiter = the value to split on
//  quote = an optional parameter - a quote character to indicate a that quoted sections will be used and ignore delimiters
//  comment_char = an optional parameter - if this is the first character in a line, that line is treated as a comment and skipped.
std::vector<std::string> FileUtils::split_line_to_strings(const std::string &input, char delimiter, char quote_char, char comment_char) const
{
#ifdef DEBUG_RUNNER
    cout << "original input is [" << input << "]" << endl;
#endif

    std::vector<std::string> splits;

    char *pos = (char *)input.c_str();

    if (comment_char && *pos == comment_char)
    {
#ifdef DEBUG_RUNNER
        cout << "Comment line found" << endl;
#endif
        return splits;
    }

    bool in_quote = false;
    std::ostringstream current;
    while (*pos != '\0')
    {
        if (quote_char && in_quote)
        {
            if (*pos == quote_char)
            {
                in_quote = false;
#ifdef DEBUG_RUNNER
                cout << "Leaving quotes" << endl;
#endif
            }
            else
            {
                current << (*pos);
            }
        }
        else
        {
            if (quote_char && *pos == quote_char)
            {
                in_quote = true;
#ifdef DEBUG_RUNNER
                cout << "In quotes" << endl;
#endif
            }
            else if (*pos == delimiter)
            {
                // ABCDE,ABCDE,ABCDE
                // first std::string goes from 0 to 4...construct as std::string(0,5). pos will be 5 for the comma. so 5-0=5
                // second std::string goes from 6 to 10...construct as std::string(6,5)...pos wil be 11 for the comma. so 11-6=5
                // third std::string goes from 12 to 16...construct as std::string(12,5) but need to do this out of loop as its the last std::string
#ifdef DEBUG_RUNNER
                cout << "appending [" << current.str() << "] as a std::string" << endl;
#endif
                splits.push_back(current.str());
                current = std::ostringstream();
            }
            else
            {
                current << (*pos);
            }
        }
        pos++;
    }
    // append the last std::string. pos will be pointed to the null terminator at 17, so std::string(12,5) would be pos(17)-start(12)
#ifdef DEBUG_RUNNER
    cout << "appending [" << current.str() << "] as the last std::string" << endl;
#endif
    splits.push_back(current.str());
    return splits;
}

bool FileUtils::read_as_list_of_strings(const std::string &filename, std::vector<std::string> &lines) const
{
    std::ifstream infile(filename);
    if (!infile)
    {
        std::cerr << "*****Error opening file " << filename << std::endl;
        return false;
    }
    std::string line;
    while (getline(infile, line))
    {
#ifdef DEBUG_RUNNER
        cout << "Read line [" << line << "] from file" << endl;
#endif
        lines.push_back(line);
    }
    infile.close();
    return true;
}

bool FileUtils::read_as_list_of_split_strings(const std::string &filename, std::vector<std::vector<std::string>> &split_strings, char delimiter, char quote_char, char comment_char) const
{
    std::vector<std::string> lines;
    if (!read_as_list_of_strings(filename, lines))
    {
        return false;
    }
    for (auto iter = lines.begin(); iter != lines.end(); ++iter)
    {
        std::vector<std::string> results = split_line_to_strings(*iter, delimiter, quote_char, comment_char);
        if (results.empty())
            split_strings.push_back(results);
    }
    return true;
}

bool FileUtils::read_as_list_of_split_doubles(const std::string &filename, std::vector<std::vector<double>> &split_longs, char delimiter, char quote_char, char comment_char) const
{
    std::vector<std::string> lines;
    if (!read_as_list_of_strings(filename, lines))
    {
        return false;
    }
    for (auto iter = lines.begin(); iter != lines.end(); ++iter)
    {
        std::vector<std::string> long_strings = split_line_to_strings(*iter, delimiter, quote_char, comment_char);
        std::vector<double> longs;
        for (auto str_long_iter = long_strings.begin(); str_long_iter != long_strings.end(); ++str_long_iter)
        {
            std::string str_long = *str_long_iter;
            longs.push_back(strtol(str_long.c_str(), nullptr, 10));
        }
        split_longs.push_back(longs);
    }
    return true;
}
