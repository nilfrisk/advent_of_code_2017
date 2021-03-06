// day_9_part_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main()
{

    std::stringstream string_stream;

#ifdef TEST_DATA
    //string_stream << "{}";
    //string_stream << "{{{}}}";
    //string_stream << "{{},{}}";
    //string_stream << "{{{},{},{{}}}}";
    //string_stream << "{<a>,<a>,<a>,<a>}";
    //string_stream << "{{<ab>},{<ab>},{<ab>},{<ab>}}";
    //string_stream << "{{<!!>},{<!!>},{<!!>},{<!!>}}";
    string_stream << "{{<a!>},{<a!>},{<a!>},{<ab>}}";
#else
    std::ifstream file("..//input.txt");
    if(!file){ throw(std::exception("Open file error")); }

    string_stream << file.rdbuf();
    file.close();
#endif

    //Dump the opening bracket
    (void)string_stream.get();

    advent_of_code::week_9::Group group(advent_of_code::week_9::on_group(string_stream, 1));
    assert(!string_stream.fail());

    //Get the score
    size_t score(advent_of_code::week_9::get_score(group));

    return(EXIT_SUCCESS);
}
