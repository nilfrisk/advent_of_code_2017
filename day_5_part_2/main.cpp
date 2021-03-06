
#include "stdafx.h"


namespace advent_of_code{
    std::vector<int> import_data();
    size_t process_jumps(std::vector<int>& data);
}

int main(){

#ifdef TEST_DATA
    std::vector<int> data({0,3,0,1,-3});
    auto steps_ = advent_of_code::process_jumps(data);
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
        
        //Now, the jumps are even stranger: after each jump, if the offset was three or more, 
        //instead decrease it by 1. Otherwise, increase it by 1 as before.

        if(2 < jmp){
            index += jmp--;
            continue;
        } 

        index += jmp++;
    }
    return(steps);
}
