#include "advent_of_code.h"

#include <cassert>
#include <fstream>
#include <sstream>
#include <algorithm>


size_t advent_of_code::week_7::get_tower_weight(const ProgramTree& program_tree){

    size_t weight(program_tree.weight);

    for(const auto& top_program_tree : program_tree.program_trees){
        weight += get_tower_weight(top_program_tree);
    }

    return(weight);
}

size_t advent_of_code::week_7::get_weight_required_to_balance_tower(const advent_of_code::week_7::ProgramTree& program_tree){

    //NOTE: weight_required_to_balance_tower must be !0 to be a valid number
    size_t weight_required_to_balance_tower(0);

    for(const auto& top_program_tree : program_tree.program_trees){
        weight_required_to_balance_tower = get_weight_required_to_balance_tower(top_program_tree);
        if(0 != weight_required_to_balance_tower){ break; }
    }
    if(0 != weight_required_to_balance_tower){ return(weight_required_to_balance_tower); }

    if(program_tree.program_trees.empty()){ assert(!program_tree.holding_disc); return(weight_required_to_balance_tower); }

    assert(program_tree.holding_disc);
    assert(2 < program_tree.program_trees.size());

    //Are the weights balanced?
    std::vector<size_t> first_weights;
    std::vector<size_t> other_weights;
    const auto first_weight(get_tower_weight(program_tree.program_trees[0]));
    first_weights.push_back(0);

    for(size_t index(1); program_tree.program_trees.size() != index; ++index){
        auto tower_weight(get_tower_weight(program_tree.program_trees[index]));
        if(first_weight == tower_weight){
            first_weights.push_back(index);
            continue;
        }

        other_weights.push_back(index);
    }
    if(other_weights.empty()){ return(weight_required_to_balance_tower); }

    //Which weight is not balanced (NOTE: We are told there is only one in the entire set)

    if(1 == first_weights.size()){
        //index 0 is the unbalanced
        assert(1 == first_weights.size());
        assert(!other_weights.empty());

        const auto& program_tree_balanced = program_tree.program_trees[other_weights[0]];
        const auto& program_tree_unbalanced = program_tree.program_trees[first_weights[0]];

        weight_required_to_balance_tower = get_tower_weight(program_tree_balanced) - (get_tower_weight(program_tree_unbalanced) - program_tree_unbalanced.weight);


    } else{
        assert(1 == other_weights.size());
        assert(!first_weights.empty());

        const auto& program_tree_balanced = program_tree.program_trees[first_weights[0]];
        const auto& program_tree_unbalanced = program_tree.program_trees[other_weights[0]];

        weight_required_to_balance_tower = get_tower_weight(program_tree_balanced) - (get_tower_weight(program_tree_unbalanced) - program_tree_unbalanced.weight);

    }
    assert(0 != weight_required_to_balance_tower);
    if(0 != weight_required_to_balance_tower){ return(weight_required_to_balance_tower); }

    return(weight_required_to_balance_tower);
}
std::vector<std::string> advent_of_code::week_8::import_data(){

    auto data = advent_of_code::get_data("..//input.txt");
    assert(!data.empty());

    auto strings = std::tokenize(data, "\n");
    assert(!strings.empty());

    data.clear();

    return(strings);

}
namespace advent_of_code{
    namespace week_7{
        struct NameAndWeight{
            std::string name;
            size_t weight = 0;

            void Clear(){
                name.clear();
                weight = 0;
            }
        };
        NameAndWeight parse_name_and_weight(std::stringstream& string_stream, const std::string& name_and_weight_string){

            assert(!name_and_weight_string.empty());

            auto tokens = std::tokenize(name_and_weight_string, "(");
            assert(2 == tokens.size());

            NameAndWeight name_and_weight;

            name_and_weight.name = tokens[0];
            assert(!name_and_weight.name.empty());

            auto weight_string(tokens[1]);
            assert(!weight_string.empty() && 1 < weight_string.size() && ')' == weight_string[weight_string.size() - 1]);

            //remove the trailing )
            weight_string.resize(weight_string.size() - 1);

            string_stream << weight_string;
            string_stream >> name_and_weight.weight;
            assert(!string_stream.fail());

            return(name_and_weight);
        }
        std::vector<std::string> parse_tops(const std::string& tops_string){
            std::vector<std::string> tops;
            if(tops_string.empty()){ return(tops); }

            tops = std::tokenize(tops_string, ",");
            assert(!tops.empty());

            return(tops);
        }
    }
}

bool advent_of_code::week_7::process_program_trees(ProgramTree& this_program_tree, std::vector<ProgramTree>& program_trees){

    bool found(false);

    for(auto& program_tree : this_program_tree.program_trees){
        found = process_program_trees(program_tree, program_trees);
        if(found){ break; }
    }
    if(found){ return(found); }

    //add any existinig program_trees to program_tree 
    for(auto index(0); program_trees.size() != index; ++index){

        const auto& that_program_tree(program_trees[index]);

        if(0 == this_program_tree.name.compare(that_program_tree.name)){ continue; }

        //check if it_program_tree is a top of this_program_tree
        for(const auto& top : this_program_tree.tops){
            if(0 != top.compare(that_program_tree.name)){ continue; }

            found = true;

            this_program_tree.program_trees.push_back(that_program_tree);
            program_trees.erase(program_trees.begin() + index);

            //reset iterator
            index = -1;
            break;
        }
        if(found){ break; }
    }
    if(found){ return(found); }

    return(found);
}
std::vector<advent_of_code::week_7::Program> advent_of_code::week_7::import_data(){

    auto data = advent_of_code::get_data("..//day_7_input.txt");
    assert(!data.empty());

    auto program_strings = std::tokenize(data, "\n");
    assert(!program_strings.empty());

    data.clear();

    NameAndWeight name_and_weight;
    Program program;
    std::vector<Program> programs;
    std::stringstream string_stream;

    std::for_each(program_strings.cbegin(), program_strings.cend(), [&programs, &program, &name_and_weight, &string_stream](std::string program_string){
        assert(!program_string.empty());

        //Scrap the spaces     
        auto end = std::remove(program_string.begin(), program_string.end(), ' ');

        program_string.resize(program_string.size() - (program_string.end() - end));

        //Get holding_disc
        auto tokens = std::tokenize(program_string, "->");
        assert(!tokens.empty());

        program.holding_disc = 1 != tokens.size();

        //Get name and weight
        name_and_weight = parse_name_and_weight(string_stream, tokens[0]);
        program.name = name_and_weight.name;
        program.weight = name_and_weight.weight;

        if(program.holding_disc){
            program.tops = parse_tops(tokens[1]);
        }

        programs.push_back(program);

        //reset vars
        std::reset(string_stream);
        program.Clear();
        name_and_weight.Clear();
    });
    return(programs);

}
std::vector<size_t> advent_of_code::week_6::import_data(){
    auto data = advent_of_code::get_data("..//day_6_part_1_input.txt");
    assert(!data.empty());

    auto memory_bank_strings = std::tokenize(data, "\t");
    assert(!memory_bank_strings.empty());

    data.clear();

    std::vector<size_t> memory_banks;
    std::stringstream string_stream;
    size_t temp(0);
    std::for_each(memory_bank_strings.cbegin(), memory_bank_strings.cend(), [&memory_banks, &string_stream, &temp](const std::string line){
        string_stream << line;
        string_stream >> temp;
        assert(!string_stream.fail());

        memory_banks.push_back(temp);

        //reset vars
        temp = 0;
        std::reset(string_stream);
    });
    return(memory_banks);
}
std::vector<int> advent_of_code::week_5::import_data(){

    auto data = advent_of_code::get_data("..//day_5_part_1_input.txt");
    assert(!data.empty());

    auto lines = std::tokenize(data, "\n");
    assert(!lines.empty());

    data.clear();

    std::vector<int> jump_instructions;
    std::stringstream string_stream;
    int temp(0);
    std::for_each(lines.cbegin(), lines.cend(), [&jump_instructions, &string_stream, &temp](const std::string line){
        string_stream << line;
        string_stream >> temp;
        assert(!string_stream.fail());

        jump_instructions.push_back(temp);

        //reset vars
        temp = 0;
        std::reset(string_stream);
    });
    return(jump_instructions);
}
std::vector<std::pair<std::pair<int, int>, size_t>> advent_of_code::spiral_memory::get_position_and_values(const size_t number){

    assert(0 != number);

    enum class Direction{ right, up, left, down };
    class SpiralMemory{
    public:
        Direction direction = Direction::right;
        //NOTE: starting move is 1 block
        size_t x_count = 1;
        size_t y_count = 1;

    public:
        std::vector<std::pair<std::pair<int, int>, size_t>> GetPositionAndValues(const size_t number){
            m_cord_values.clear();

            //Prime with position 0,0 with a value of 1
            std::pair<std::pair<int, int>, size_t> zero_zero;
            zero_zero.first.first = 0;
            zero_zero.first.second = 0;
            zero_zero.second = 1;
            m_cord_values.push_back(zero_zero);

            bool complete(false);
            for(size_t index(0); !complete;){

                switch(direction){
                case Direction::right:
                    complete = this->MoveRight(index, number);
                    break;
                case Direction::up:
                    complete = this->MoveUp(index, number);
                    break;
                case Direction::left:
                    complete = this->MoveLeft(index, number);
                    break;
                case Direction::down:
                    complete = this->MoveDown(index, number);
                    break;
                }

            }

            return(m_cord_values);
        }

    private:
        //        17  16  15  14  13
        //        18   5   4   3  12
        //        19   6   1   2  11
        //        20   7   8   9  10
        //        21  22  23---> ...  

        //     37 36  35  34  33  32 31
        //     38 17  16  15  14  13 30
        //     39 18   5   4   3  12 29
        //     40 19   6  (1)  2  11 28
        //     41 20   7   8  (9) 10 27
        //     42 21  22  23  24 (25)26           
        //     43 44  45  46  47  48 (49)


        size_t GetValueFromOffset(const std::pair<int, int> cords, const int x_offset, const int y_offset){

            auto it_cord_value = std::find_if(m_cord_values.cbegin(), m_cord_values.cend(), [&cords, x_offset, y_offset]
            (const std::pair<std::pair<int, int>, size_t>& that_cord_value){
                return(
                    that_cord_value.first.first == cords.first + x_offset &&
                    that_cord_value.first.second == cords.second + y_offset
                    );
            }
            );

            size_t value(0);
            if(m_cord_values.cend() != it_cord_value){
                value = it_cord_value->second;
            }
            return(value);
        }
        size_t CalcValue(){
            //(x -1, y - 1) +  (x, y - 1) + (x + 1, y - 1) 
            //(x -1, y)            +        (x + 1, y) 
            //(x -1, y + 1) +  (x, y + 1) + (x + 1, y + 1) 

            size_t result(0);

            //get (x -1, y - 1) 
            result += this->GetValueFromOffset(m_cords, -1, -1);
            //get (x, y - 1)
            result += this->GetValueFromOffset(m_cords, 0, -1);
            //get (x + 1, y - 1)
            result += this->GetValueFromOffset(m_cords, 1, -1);

            //get (x -1, y)  
            result += this->GetValueFromOffset(m_cords, -1, 0);
            //get (x + 1, y) 
            result += this->GetValueFromOffset(m_cords, 1, 0);

            //get (x -1, y + 1)  
            result += this->GetValueFromOffset(m_cords, -1, 1);
            //get  (x, y + 1)
            result += this->GetValueFromOffset(m_cords, 0, 1);
            //get (x + 1, y + 1) 
            result += this->GetValueFromOffset(m_cords, 1, 1);

            return(result);
        }
        bool MoveRight(size_t& current_number, const size_t number){

            std::pair<std::pair<int, int>, size_t> cord_value;

            for(size_t index(0); x_count != index && number >= cord_value.second; ++index, ++current_number){

                //update position
                ++m_cords.first;

                //update vars
                cord_value.first = m_cords;
                cord_value.second = this->CalcValue();

                //add to list
                m_cord_values.push_back(cord_value);
            }

            if(number < cord_value.second){ return(true); }//task complete

            //Update move count
            ++x_count;

            //update direction
            direction = Direction::up;

            return(false);
        }
        bool MoveLeft(size_t& current_number, const size_t number){
            std::pair<std::pair<int, int>, size_t> cord_value;
            //Move
            for(size_t index(0); x_count != index && number >= cord_value.second; ++index, ++current_number){
                --m_cords.first;

                //update vars
                cord_value.first = m_cords;
                cord_value.second = this->CalcValue();

                //add to list
                m_cord_values.push_back(cord_value);
            }

            if(number < cord_value.second){ return(true); }//task complete

            //Update move count
            ++x_count;

            //update direction
            direction = Direction::down;

            return(false);
        }
        bool MoveUp(size_t& current_number, const size_t number){
            std::pair<std::pair<int, int>, size_t> cord_value;
            //Move
            for(size_t index(0); y_count != index && number >= cord_value.second; ++index, ++current_number){
                --m_cords.second;

                //update vars
                cord_value.first = m_cords;
                cord_value.second = this->CalcValue();

                //add to list
                m_cord_values.push_back(cord_value);
            }

            if(number < cord_value.second){ return(true); }//task complete

            //Update move count
            ++y_count;

            //update direction
            direction = Direction::left;

            return(false);
        }
        bool MoveDown(size_t& current_number, const size_t number){
            std::pair<std::pair<int, int>, size_t> cord_value;
            //Move
            for(size_t index(0); y_count != index && number >= cord_value.second; ++index, ++current_number){
                ++m_cords.second;

                //update vars
                cord_value.first = m_cords;
                cord_value.second = this->CalcValue();

                //add to list
                m_cord_values.push_back(cord_value);
            }

            if(number < cord_value.second){ return(true); }//task complete

            //Update move count
            ++y_count;

            //update direction
            direction = Direction::right;

            return(false);
        }

    private:
        //NOTE: position, value
        std::vector<std::pair<std::pair<int, int>, size_t>> m_cord_values;

    private:
        std::pair<int, int> m_cords;

    };
    SpiralMemory spiral_memory;
    return(spiral_memory.GetPositionAndValues(number));

}
std::pair<int, int> advent_of_code::spiral_memory::get_position(const size_t number){

    assert(0 != number);

    enum class Direction{ right, up, left, down };
    class SpiralMemory{
    public:
        Direction direction = Direction::right;
        //NOTE: starting move is 1 block
        size_t x_count = 1;
        size_t y_count = 1;

    public:
        std::pair<int, int> GetPosition(const size_t number){

            assert(0 != number);

            m_cords.first = 0;
            m_cords.second = 0;

            for(size_t index(1); number != index;){

                assert(number > index);

                switch(direction){
                case Direction::right:
                    this->MoveRight(index, number);
                    break;
                case Direction::up:
                    this->MoveUp(index, number);
                    break;
                case Direction::left:
                    this->MoveLeft(index, number);
                    break;
                case Direction::down:
                    this->MoveDown(index, number);
                    break;
                }
            }

            return(m_cords);
        }

    private:
        //        17  16  15  14  13
        //        18   5   4   3  12
        //        19   6   1   2  11
        //        20   7   8   9  10
        //        21  22  23---> ...  

        //     37 36  35  34  33  32 31
        //     38 17  16  15  14  13 30
        //     39 18   5   4   3  12 29
        //     40 19   6  (1)  2  11 28
        //     41 20   7   8  (9) 10 27
        //     42 21  22  23  24 (25)26           
        //     43 44  45  46  47  48 (49)
        void MoveRight(size_t& current_number, const size_t number){
            //Move
            for(size_t index(0); x_count != index && current_number != number; ++index, ++current_number){
                ++m_cords.first;
            }

            if(current_number == number){ return; }//task complete

            //Update move count
            ++x_count;

            //update direction
            direction = Direction::up;
        }
        void MoveLeft(size_t& current_number, const size_t number){
            //Move
            for(size_t index(0); x_count != index && current_number != number; ++index, ++current_number){
                --m_cords.first;
            }

            if(current_number == number){ return; }//task complete

            //Update move count
            ++x_count;

            //update direction
            direction = Direction::down;
        }
        void MoveUp(size_t& current_number, const size_t number){
            //Move
            for(size_t index(0); y_count != index && current_number != number; ++index, ++current_number){
                --m_cords.second;
            }

            if(current_number == number){ return; }//task complete
            
            //Update move count
            ++y_count;

            //update direction
            direction = Direction::left;
        }
        void MoveDown(size_t& current_number, const size_t number){
            //Move
            for(size_t index(0); y_count != index && current_number != number; ++index, ++current_number){
                ++m_cords.second;
            }

            if(current_number == number){ return; }//task complete

            //Update move count
            ++y_count;

            //update direction
            direction = Direction::right;
        }

    private:

    private:
        std::pair<int, int> m_cords;

    };

    SpiralMemory spiral_memory;
    return(spiral_memory.GetPosition(number));

}


size_t advent_of_code::get_manhattan_distance(const std::pair<int, int> this_item, const std::pair<int, int> that_item){

    //https://en.wikipedia.org/wiki/Taxicab_geometry
    //   | p 1 − q 1 | + | p 2 − q 2 |

    return(
        (std::abs(this_item.first) - std::abs(that_item.first)) + 
        (std::abs(this_item.second) - std::abs(that_item.second))
    );
}

std::string advent_of_code::get_data(const char* file_path){
    std::ifstream file(file_path);
    if(!file){ throw(std::exception("Open file error")); }

    std::stringstream string_stream;
    string_stream << file.rdbuf();
    file.close();

    return(string_stream.str());
}

std::vector<std::string> std::tokenize(std::string value, const std::string& delims){

    if(value.empty()){ return(std::vector<std::string>()); }

    std::vector<std::string> tokens;

    char* token = strtok(&value[0], delims.c_str());
    while(nullptr != token){
        tokens.push_back(token);
        token = strtok(nullptr, delims.c_str());
    }
    return(tokens);
}



void advent_of_code::week_8::JumpInstruction::ProcessToken0(const std::string& token){

    //i.e. b inc 580
    auto tokens = std::tokenize(token, " ");
    assert(3 == tokens.size());

    //register_to_modify
    this->modify.register_to_modify = tokens[0];

    //modify.direction
    if(0 == tokens[1].compare("inc")){
        this->modify.direction = Modify::Direction::increase;
    } else if(0 == tokens[1].compare("dec")){
        this->modify.direction = Modify::Direction::decrease;
    } else{
        assert(false);
    }

    //modify.amount
    std::reset(m_string_stream);
    m_string_stream << tokens[2];
    m_string_stream >> this->modify.amount;
    assert(!m_string_stream.fail());
}
void advent_of_code::week_8::JumpInstruction::ProcessCondition(const std::string& condition_string){

    //i.e. bkd > -1
    auto tokens = std::tokenize(condition_string, " ");
    assert(3 == tokens.size());

    //condition.operation
    condition.register_to_compare = tokens[0];

    //condition.operation
    if(0 == tokens[1].compare("==")){
        this->condition.operation = Condition::Operation::equal_to;
    } else if(0 == tokens[1].compare(">")){
        this->condition.operation = Condition::Operation::greater_than;
    } else if(0 == tokens[1].compare(">=")){
        this->condition.operation = Condition::Operation::greater_than_or_equal_to;
    } else if(0 == tokens[1].compare("<")){
        this->condition.operation = Condition::Operation::less_than;
    } else if(0 == tokens[1].compare("<=")){
        this->condition.operation = Condition::Operation::less_than_or_equal_to;
    } else if(0 == tokens[1].compare("!=")){
        this->condition.operation = Condition::Operation::not_equal_to;
    } else{
        assert(false);
    }

    //condition.amount
    std::reset(m_string_stream);
    m_string_stream << tokens[2];
    m_string_stream >> this->condition.amount;
    assert(!m_string_stream.fail());
}
advent_of_code::week_8::JumpInstruction::JumpInstruction(const std::string& jump_instruction){
    //parse jump_instruction string

    //i.e. b inc 580 if bkd > -1
    auto pos = jump_instruction.find(if_string);
    assert(jump_instruction.npos != pos);

    this->ProcessToken0(jump_instruction.substr(0, pos));
    this->ProcessCondition(jump_instruction.substr(pos + if_string.size()));

    //auto tokens = std::tokenize(jump_instruction, "if");
    //assert(2 == tokens.size());
    //
    //this->ProcessToken0(tokens[0]);
    //this->ProcessCondition(tokens[1]);
}
bool advent_of_code::week_8::get_process_instruction(const int register_value, const JumpInstruction::Condition::Operation operation, const int condition_amount){
    bool process_instruction(false);
    switch(operation){
    case JumpInstruction::Condition::Operation::equal_to:
        process_instruction = register_value == condition_amount;
        break;
    case JumpInstruction::Condition::Operation::greater_than:
        process_instruction = register_value > condition_amount;
        break;
    case JumpInstruction::Condition::Operation::greater_than_or_equal_to:
        process_instruction = register_value >= condition_amount;
        break;
    case JumpInstruction::Condition::Operation::less_than:
        process_instruction = register_value < condition_amount;
        break;
    case JumpInstruction::Condition::Operation::less_than_or_equal_to:
        process_instruction = register_value <= condition_amount;
        break;
    case JumpInstruction::Condition::Operation::not_equal_to:
        process_instruction = register_value != condition_amount;
        break;
    default:
        assert(false);
        break;
    };
    return(process_instruction);
}
void advent_of_code::week_8::process_jump_instruction(std::vector<Register>& registers, const JumpInstruction& jump_instruction){

    //Get the register to compare
    auto it_register_to_compare = std::find_if(registers.cbegin(), registers.cend(), [&jump_instruction](const Register& the_register){
        return(0 == jump_instruction.condition.register_to_compare.compare(the_register.name));
    });
    if(it_register_to_compare == registers.cend()){
        //initialize register
        registers.push_back(jump_instruction.condition.register_to_compare);
        it_register_to_compare = registers.end() - 1;
    }
    assert(registers.cend() != it_register_to_compare);

    bool process_instruction(get_process_instruction(it_register_to_compare->value, jump_instruction.condition.operation, jump_instruction.condition.amount));
    if(!process_instruction){ return; }

    //Get the register to modify
    auto it_register_to_modify = std::find_if(registers.begin(), registers.end(), [&jump_instruction](const Register& the_register){
        return(0 == jump_instruction.modify.register_to_modify.compare(the_register.name));
    });
    if(it_register_to_modify == registers.cend()){
        //initialize register
        registers.push_back(jump_instruction.modify.register_to_modify);
        it_register_to_modify = registers.end() - 1;
    }
    assert(registers.cend() != it_register_to_modify);


    switch(jump_instruction.modify.direction){
    case JumpInstruction::Modify::Direction::decrease:
        it_register_to_modify->value -= jump_instruction.modify.amount;
        break;
    case JumpInstruction::Modify::Direction::increase:
        it_register_to_modify->value += jump_instruction.modify.amount;
        break;
    default:
        assert(false);
        break;
    }
}

void advent_of_code::week_8::process_jump_instruction(int& highest_value_held, std::vector<Register>& registers, const JumpInstruction& jump_instruction){

    //Get the register to compare
    auto it_register_to_compare = std::find_if(registers.cbegin(), registers.cend(), [&jump_instruction](const Register& the_register){
        return(0 == jump_instruction.condition.register_to_compare.compare(the_register.name));
    });
    if(it_register_to_compare == registers.cend()){
        //initialize register
        registers.push_back(jump_instruction.condition.register_to_compare);
        it_register_to_compare = registers.end() - 1;
    }
    assert(registers.cend() != it_register_to_compare);

    bool process_instruction(get_process_instruction(it_register_to_compare->value, jump_instruction.condition.operation, jump_instruction.condition.amount));
    if(!process_instruction){ return; }

    //Get the register to modify
    auto it_register_to_modify = std::find_if(registers.begin(), registers.end(), [&jump_instruction](const Register& the_register){
        return(0 == jump_instruction.modify.register_to_modify.compare(the_register.name));
    });
    if(it_register_to_modify == registers.cend()){
        //initialize register
        registers.push_back(jump_instruction.modify.register_to_modify);
        it_register_to_modify = registers.end() - 1;
    }
    assert(registers.cend() != it_register_to_modify);


    switch(jump_instruction.modify.direction){
    case JumpInstruction::Modify::Direction::decrease:
        it_register_to_modify->value -= jump_instruction.modify.amount;
        break;
    case JumpInstruction::Modify::Direction::increase:
        it_register_to_modify->value += jump_instruction.modify.amount;
        break;
    default:
        assert(false);
        break;
    }

    if(highest_value_held < std::abs(it_register_to_modify->value)){ highest_value_held = std::abs(it_register_to_modify->value); }
}

size_t advent_of_code::week_9::get_garbage_count(const advent_of_code::week_9::Group& group){

    size_t garbage_count(0);

    for(const auto& child_group : group.groups){
        garbage_count += advent_of_code::week_9::get_garbage_count(child_group);
    }
    for(const auto& garbage : group.garbage){
        garbage_count += garbage.size();
    }

    return(garbage_count);
}
size_t advent_of_code::week_9::get_score(const advent_of_code::week_9::Group& group){

    size_t score(0);

    for(const auto& child_group : group.groups){
        score += advent_of_code::week_9::get_score(child_group);
    }
    score += group.score;

    return(score);
}

advent_of_code::week_9::Group advent_of_code::week_9::on_group(std::stringstream& string_stream, const size_t score){
    //group{}

    Group group;
    group.score = score;

    std::string line;
    for(auto current_char(string_stream.get()); '}' != current_char; current_char = string_stream.get()){

        switch(current_char){
        case '{':
            group.groups.push_back(on_group(string_stream, score + 1));
            break;
        case '<':
            group.garbage.push_back(on_garbage(string_stream));
            break;
        case ',':
            //new item
            break;
        default:
            assert(false);
            break;
        }
    }

    return(group);
}

std::string advent_of_code::week_9::on_garbage(std::stringstream& string_stream){
    //garbage<>
    //within garbage canceled ! (ignore the char after !)

    std::stringstream local_string_stream;

    for(auto current_char(string_stream.get()); '>' != current_char; current_char = string_stream.get()){

        switch(current_char){
        case '!':
            //ignore the char after !
            //local_string_stream << current_char;
            current_char = string_stream.get();
            break;
        default:
            local_string_stream << static_cast<char>(current_char);
            break;
        }
    }

    std::string garbage(local_string_stream.str());
    return(garbage);
}