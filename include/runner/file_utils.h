#ifndef __FILE_UTILS_H__
#define __FILE_UTILS_H__

#include <string>
#include <vector>

class FileUtils
{
private:
    std::vector<std::string> split_line_to_strings(const std::string &input, char delimiter, char quote_char, char comment_char) const;

public:
    bool read_as_list_of_strings(const std::string &filename, std::vector<std::string> &lines) const;
    bool read_as_list_of_split_strings(const std::string &filename, std::vector<std::vector<std::string>> &split_strings, char delimiter, char quote_char, char comment_char) const;
    bool read_as_list_of_split_doubles(const std::string &filename, std::vector<std::vector<double>> &split_doubles, char delimiter, char quote_char, char comment) const;
};

#endif
