#pragma once

#include <vector>

namespace std{
    std::vector<std::string> tokenize(std::string value, const std::string& delims);
}
namespace advent_of_code{
    std::string get_data(const char* file_path);

    size_t get_manhattan_distance(const std::pair<int, int> this_item, const std::pair<int, int> that_item);

    namespace spiral_memory{
        std::pair<int, int> get_position(const size_t number);
        std::vector<std::pair<std::pair<int, int>, size_t>> get_position_and_values(const size_t number);
    }
}