// day_3_part_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(){

    //NOTES: 325489
    //
    //        17  16  15  14  13
    //        18   5   4   3  12
    //        19   6   1   2  11
    //        20   7   8   9  10
    //        21  22  23---> ...  
    //
    //
    //
    //
    //     37 36  35  34  33  32 31
    //     38 17  16  15  14  13 30
    //     39 18   5   4   3  12 29
    //     40 19   6  (1)  2  11 28
    //     41 20   7   8  (9) 10 27
    //     42 21  22  23  24 (25)26           
    //     43 44  45  46  47  48 (49)
    //

    const std::pair<int, int> target_cords({0,0});
    std::pair<int, int> cords;
    size_t manhattan_distance(0);

#ifdef TEST_DATA
    cords = advent_of_code::spiral_memory::get_position(1);
    assert(0 == cords.first && 0 == cords.second);

    manhattan_distance = advent_of_code::get_manhattan_distance(cords, target_cords);
    assert(0 == manhattan_distance);

    cords = advent_of_code::spiral_memory::get_position(12);
    assert(2 == cords.first && -1 == cords.second);

    manhattan_distance = advent_of_code::get_manhattan_distance(cords, target_cords);
    assert(3 == manhattan_distance);

    cords = advent_of_code::spiral_memory::get_position(23);
    assert(0 == cords.first && 2 == cords.second);

    manhattan_distance = advent_of_code::get_manhattan_distance(cords, target_cords);
    assert(2 == manhattan_distance);

    cords = advent_of_code::spiral_memory::get_position(1024);
    manhattan_distance = advent_of_code::get_manhattan_distance(cords, target_cords);
    assert(31 == manhattan_distance);
#endif

    cords = advent_of_code::spiral_memory::get_position(325489);
    manhattan_distance = advent_of_code::get_manhattan_distance(cords, target_cords);

    return(EXIT_SUCCESS);
}

