// day_4_part_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

bool process_line(const std::string& line);
int main(){
    //How many passphrases are valid?
    //All lower case?

    auto data = advent_of_code::get_data("..//day_4_part_1_input.txt");
    assert(!data.empty());

    auto lines = std::tokenize(data, "\n");
    assert(!lines.empty());

    data.clear();

    auto valid_count(lines.size());

    std::for_each(lines.cbegin(), lines.cend(), [&valid_count]
        (const std::string& line){

            bool valid = process_line(line);
            if(!valid){ --valid_count; }


        }
    );

    return(EXIT_SUCCESS);
}


bool process_line(const std::string& line){

    bool valid(true);

    auto words = std::tokenize(line, " ");
    assert(!words.empty());

    for(auto index(0); words.size() != index; ++index){

        //Get a copy of the word for sort testing later
        auto this_word(words[index]);
        std::sort(this_word.begin(), this_word.end());

        for(auto inner_index(0); words.size() != inner_index; ++inner_index){
            if(index == inner_index){ continue; }


            if(0 == words[index].compare(words[inner_index])){ valid = false; }
            if(!valid){ break; }

            //Get a copy of the word for sorting
            auto that_word(words[inner_index]);
            std::sort(that_word.begin(), that_word.end());

            if(0 == this_word.compare(that_word)){ valid = false; }
            if(!valid){ break; }

        }
        if(!valid){ break; }

    }

    return(valid);
}