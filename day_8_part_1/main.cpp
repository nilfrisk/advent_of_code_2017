// day_8_part_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{

    //Parse input file
#ifdef TEST_DATA
    std::vector<std::string> jump_instruction_strings = {
        {"b inc 5 if a > 1"},
        {"a inc 1 if b < 5"},
        {"c dec -10 if a >= 1"},
        {"c inc -20 if c == 10"}
    };
#else
    auto jump_instruction_strings = advent_of_code::week_8::import_data();
#endif
    std::vector<advent_of_code::week_8::JumpInstruction> jump_instructions;
    for(const auto& jump_instruction_string : jump_instruction_strings){
        jump_instructions.push_back(jump_instruction_string);
    }

    //Process instructions

    std::vector<advent_of_code::week_8::Register> registers;
    for(const auto& jump_instruction : jump_instructions){
        advent_of_code::week_8::process_jump_instruction(registers, jump_instruction);
    }

    //What is the largest value in any register?

    int largest_value(0);
    for(const auto& current_register : registers){
        if(largest_value > current_register.value){ continue; }

        largest_value = current_register.value;
    }
    return(EXIT_SUCCESS);
}
