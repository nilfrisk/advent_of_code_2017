// day_7_part_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main()
{
    //Get data
    std::vector<advent_of_code::week_7::Program> programs;
#ifdef TEST_DATA
    programs.push_back(advent_of_code::week_7::Program("pbga", 66));
    programs.push_back(advent_of_code::week_7::Program("xhth", 57));
    programs.push_back(advent_of_code::week_7::Program("ebii", 61));
    programs.push_back(advent_of_code::week_7::Program("havc", 66));
    programs.push_back(advent_of_code::week_7::Program("ktlj", 57));
    programs.push_back(advent_of_code::week_7::Program("fwft", 72, true, {"ktlj", "cntj", "xhth"}));
    programs.push_back(advent_of_code::week_7::Program("qoyq", 66));
    programs.push_back(advent_of_code::week_7::Program("padx", 45, true, {"pbga", "havc", "qoyq"}));
    programs.push_back(advent_of_code::week_7::Program("tknk", 41, true, {"ugml", "padx", "fwft"}));
    programs.push_back(advent_of_code::week_7::Program("jptl", 61));
    programs.push_back(advent_of_code::week_7::Program("ugml", 68, true, {"gyxo", "ebii", "jptl"}));
    programs.push_back(advent_of_code::week_7::Program("gyxo", 61));
    programs.push_back(advent_of_code::week_7::Program("cntj", 57));
#else
    programs = advent_of_code::week_7::import_data();
#endif
        
    //convert to ProgramTree
    std::vector<advent_of_code::week_7::ProgramTree> program_trees;
    std::for_each(programs.cbegin(), programs.cend(), [&program_trees](const advent_of_code::week_7::Program& program){
        advent_of_code::week_7::ProgramTree this_program_tree;
        copy(this_program_tree, program);

        program_trees.push_back(this_program_tree);
    });

    //sort programs into a tree
    for(auto index(0); program_trees.size() != index; ++index){

        auto& this_program_tree(program_trees[index]);

        bool found(false);
        found = process_program_trees(this_program_tree, program_trees);
        if(found){ index = -1; }

    };


    assert(1 == program_trees.size());
    auto answer = program_trees[0].name;
    return(EXIT_SUCCESS);
}

