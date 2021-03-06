// day_3_part_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(){

    //        17  16  15  14  13
    //        18   5   4   3  12
    //        19   6   1   2  11
    //        20   7   8   9  10
    //        21  22  23---> ...  


    std::vector<std::pair<std::pair<int, int>, size_t>> result;

#ifdef TEST_DATA
    result = advent_of_code::spiral_memory::get_position_and_values(1);
    assert(result.size() == 3 && 2 == result[result.size() - 1].second);
    
    result = advent_of_code::spiral_memory::get_position_and_values(2);
    assert(result.size() == 4 && 4 == result[result.size() - 1].second);
    
    result = advent_of_code::spiral_memory::get_position_and_values(3);
    assert(result.size() == 4 && 4 == result[result.size() - 1].second);

    result = advent_of_code::spiral_memory::get_position_and_values(4);
    assert(result.size() == 5 && 5 == result[result.size() - 1].second);

    result = advent_of_code::spiral_memory::get_position_and_values(5);
    assert(result.size() == 6 && 10 == result[result.size() - 1].second);
#endif

    result = advent_of_code::spiral_memory::get_position_and_values(325489);

    size_t answer(0);
    answer = result[result.size() - 1].second;

    return(EXIT_SUCCESS);
}

