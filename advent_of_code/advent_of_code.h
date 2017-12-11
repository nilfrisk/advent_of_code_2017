#pragma once



#include <vector>
#include <sstream>


namespace std{
    void reset(std::stringstream& string_stream);
    std::vector<std::string> tokenize(std::string value, const std::string& delims);
}
namespace advent_of_code{

    std::string get_data(const char* file_path);

    namespace week_9{

        struct Group{
            std::vector<Group> groups;
            std::vector<std::string> garbage;
            size_t score = 0;
        };
        Group on_group(std::stringstream& string_stream, const size_t score);
        std::string on_garbage(std::stringstream& string_stream);

        size_t get_score(const Group& group);
        size_t get_garbage_count(const Group& group);

    }

    namespace week_8{
        std::vector<std::string> import_data();

        class JumpInstruction{
        public:
            JumpInstruction(const std::string& jump_instruction);

        public:

            struct Modify{
                enum class Direction{ unknown, increase, decrease };

                std::string register_to_modify;
                Direction direction = Direction::unknown;
                int amount = 0;
        }modify;

            struct Condition{
                enum class Operation{
                    unknown,
                    greater_than,
                    less_than,
                    greater_than_or_equal_to,
                    less_than_or_equal_to,
                    equal_to,
                    not_equal_to
                };
                std::string register_to_compare;
                Operation operation = Operation::unknown;
                int amount = 0;
            }condition;
        private:
            void ProcessToken0(const std::string& token);
            void ProcessCondition(const std::string& condition_string);

            std::stringstream m_string_stream;

            const std::string if_string = " if ";
    };

        struct Register{
            Register(const std::string& name) :
                name(name){
            }
            std::string name;
            int value = 0;
        };
        void process_jump_instruction(std::vector<Register>& registers, const JumpInstruction& jump_instruction);
        void process_jump_instruction(int& highest_value_held, std::vector<Register>& registers, const JumpInstruction& jump_instruction);
        bool get_process_instruction(const int register_value, const JumpInstruction::Condition::Operation operation, const int condition_amount);

    }
    namespace week_7{
        struct Program{

#ifdef TEST_DATA
            Program(const std::string& name = std::string(), const size_t weight = 0, const bool holding_disc = false, const std::vector<std::string>& tops = std::vector<std::string>()):
                name(name), weight(weight), holding_disc(holding_disc), tops(tops)
            {}
#endif

            std::string name;
            size_t weight = 0;
            bool holding_disc = false;
            std::vector<std::string> tops;

            void Clear(){
                name.clear();
                weight = 0;
                holding_disc = false;
                tops.clear();
            }
        };
        std::vector<Program> import_data();

        struct ProgramTree :
            public Program{
            std::vector<ProgramTree> program_trees;
        };
        void copy(advent_of_code::week_7::Program& this_program, const advent_of_code::week_7::Program& that_program);
        bool process_program_trees(ProgramTree& this_program_tree, std::vector<ProgramTree>& program_trees);

        size_t get_weight_required_to_balance_tower(const ProgramTree& program_tree);
        size_t get_tower_weight(const ProgramTree& program_tree);
    }
    namespace week_6{
        std::vector<size_t> import_data();
    }
    namespace week_5{
        std::vector<int> import_data();
    }
    size_t get_manhattan_distance(const std::pair<int, int> this_item, const std::pair<int, int> that_item);

    namespace spiral_memory{
        std::pair<int, int> get_position(const size_t number);
        std::vector<std::pair<std::pair<int, int>, size_t>> get_position_and_values(const size_t number);
    }
}

inline void std::reset(std::stringstream& string_stream){
    string_stream.clear();
    string_stream.str("");
}
inline void advent_of_code::week_7::copy(advent_of_code::week_7::Program& this_program, const advent_of_code::week_7::Program& that_program){
    this_program = that_program;
}

