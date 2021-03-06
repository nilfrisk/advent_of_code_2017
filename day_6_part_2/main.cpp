// day_6_part_2.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

namespace advent_of_code{
    using memory_banks = std::vector<size_t>;
    using history = std::vector<memory_banks>;
    size_t get_memory_bank_with_most_blocks(const memory_banks& memory_banks);
    size_t get_next_index(const size_t current_index, const memory_banks& memory_banks);
    bool has_been_seen_before(const memory_banks& memory_banks, const history::const_iterator begin, const history::const_iterator end);
}
int main(){

#ifdef TEST_DATA
    advent_of_code::memory_banks memory_banks = {0,2, 7, 0};
#else
    auto memory_banks = advent_of_code::week_6::import_data();
#endif

    std::vector<size_t> infinite_loop_indexes;
    advent_of_code::history history;

    while(2 > infinite_loop_indexes.size()){

        history.push_back(memory_banks);

        auto memory_bank_with_most_blocks_index(advent_of_code::get_memory_bank_with_most_blocks(memory_banks));
        auto& memory_bank_with_most_blocks = memory_banks[memory_bank_with_most_blocks_index];

        //Get blocks to Redistribute
        auto blocks_to_distribute = memory_bank_with_most_blocks;
        memory_bank_with_most_blocks = 0;

        //Redistribute blocks
        for(auto next_index(advent_of_code::get_next_index(memory_bank_with_most_blocks_index, memory_banks));
            0 != blocks_to_distribute;
            next_index = advent_of_code::get_next_index(next_index, memory_banks), --blocks_to_distribute){

            auto& next_memory_bank = memory_banks[next_index];
            ++next_memory_bank;
        }

        auto offset(0);
        if(!infinite_loop_indexes.empty()){
            offset = infinite_loop_indexes[0];
        }
        if(advent_of_code::has_been_seen_before(memory_banks, history.begin() + offset, history.cend())){
            infinite_loop_indexes.push_back(history.size());
        }
    }

    assert(2 == infinite_loop_indexes.size());
    auto answer(infinite_loop_indexes[1] - infinite_loop_indexes[0]);
    return(EXIT_SUCCESS);
}
bool advent_of_code::has_been_seen_before(const memory_banks& memory_banks, const history::const_iterator begin, const history::const_iterator end){
    auto it = std::find(begin, end, memory_banks);
    return(end != it);
}
size_t advent_of_code::get_next_index(const size_t current_index, const advent_of_code::memory_banks& memory_banks){
    return(memory_banks.size() == current_index + 1 ? 0 : current_index + 1);
}
size_t advent_of_code::get_memory_bank_with_most_blocks(const advent_of_code::memory_banks& memory_banks){

    size_t index(0);
    size_t most_blocks(0);

    std::for_each(memory_banks.cbegin(), memory_banks.cend(), [&memory_banks, &index, &most_blocks](const size_t this_block_count){
        assert(memory_banks.size() > index);
        auto& that_block_count(memory_banks[most_blocks]);

        if(this_block_count > that_block_count){
            most_blocks = index;
        } else if(this_block_count == that_block_count){
            //NOTE: ties won by the lowest-numbered memory bank
            most_blocks = (index < most_blocks ? index : most_blocks);
        }
        ++index;
    });

    return(most_blocks);
}

