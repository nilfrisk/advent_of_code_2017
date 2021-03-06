// day_5_part_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


namespace advent_of_code{
    size_t process_jumps(std::vector<int>& data);
}

int main()
{
#ifdef TEST_DATA
    std::vector<int> data({0,3,0,1,-3});
    auto steps_ = process_jumps(data);
#endif

    auto jump_instructions(advent_of_code::week_5::import_data());
    assert(!jump_instructions.empty());

    auto steps = advent_of_code::process_jumps(jump_instructions);

    return(EXIT_SUCCESS);
}


size_t advent_of_code::process_jumps(std::vector<int>& data){

    //The goal is to follow the jumps until one leads outside the list.
    size_t steps(0);
    for(size_t index(0); data.size() > index && 0 <= index; ++steps){
        //Jumps are relative
        auto& jmp(data[index]);

        //In addition, these instructions are a little strange; after each jump, 
        //the offset of that instruction increases by 1. 
        //So, if you come across an offset of 3, you would move three instructions 
        //forward, but change it to a 4 for the next time it is encountered.

        index += jmp++;
    }
    return(steps);
}
