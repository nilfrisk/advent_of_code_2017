#include "advent_of_code.h"

#include <cassert>
#include <fstream>
#include <sstream>
#include <algorithm>


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