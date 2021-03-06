// day_2-corruption_checksum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


namespace advent_of_code{
    size_t get_checksum(const std::vector<std::vector<size_t>>& spread_sheet);
}
int main(){
    size_t result(0);

#ifdef TEST_DATA
    std::vector<std::vector<size_t>> spread_sheet_test;
    spread_sheet_test.push_back({5, 9, 2, 8});
    spread_sheet_test.push_back({9, 4, 7, 3});
    spread_sheet_test.push_back({3, 8, 6, 5});

    result = advent_of_code::get_checksum(spread_sheet_test);
    assert(9 == result);

#endif

    std::vector<std::vector<size_t>>spread_sheet;
    spread_sheet.push_back({1364,461,1438,1456,818,999,105,1065,314,99,1353,148,837,590,404,123});
    spread_sheet.push_back({204,99,235,2281,2848,3307,1447,3848,3681,963,3525,525,288,278,3059,821});
    spread_sheet.push_back({280,311,100,287,265,383,204,380,90,377,398,99,194,297,399,87});
    spread_sheet.push_back({7698,2334,7693,218,7344,3887,3423,7287,7700,2447,7412,6147,231,1066,248,208});
    spread_sheet.push_back({3740,837,4144,123,155,2494,1706,4150,183,4198,1221,4061,95,148,3460,550});
    spread_sheet.push_back({1376,1462,73,968,95,1721,544,982,829,1868,1683,618,82,1660,83,1778});
    spread_sheet.push_back({197,2295,5475,2886,2646,186,5925,237,3034,5897,1477,196,1778,3496,5041,3314});
    spread_sheet.push_back({179,2949,3197,2745,1341,3128,1580,184,1026,147,2692,212,2487,2947,3547,1120});
    spread_sheet.push_back({460,73,52,373,41,133,671,61,634,62,715,644,182,524,648,320});
    spread_sheet.push_back({169,207,5529,4820,248,6210,255,6342,4366,5775,5472,3954,3791,1311,7074,5729});
    spread_sheet.push_back({5965,7445,2317,196,1886,3638,266,6068,6179,6333,229,230,1791,6900,3108,5827});
    spread_sheet.push_back({212,249,226,129,196,245,187,332,111,126,184,99,276,93,222,56});
    spread_sheet.push_back({51,592,426,66,594,406,577,25,265,578,522,57,547,65,564,622});
    spread_sheet.push_back({215,2092,1603,1001,940,2054,245,2685,206,1043,2808,208,194,2339,2028,2580});
    spread_sheet.push_back({378,171,155,1100,184,937,792,1436,1734,179,1611,1349,647,1778,1723,1709});
    spread_sheet.push_back({4463,4757,201,186,3812,2413,2085,4685,5294,5755,2898,200,5536,5226,1028,180});

    result = advent_of_code::get_checksum(spread_sheet);

    return 0;
}


size_t advent_of_code::get_checksum(const std::vector<std::vector<size_t>>& spread_sheet){

    std::vector<size_t> results;
    std::for_each(spread_sheet.cbegin(), spread_sheet.cend(), [&results]
        (const std::vector<size_t>& spread_sheet_row){

            size_t result(0);

            for(size_t index(0); spread_sheet_row.size() != index; ++index){

                auto result_found(false);
                auto numerator(spread_sheet_row[index]);

                for(size_t sub_index(0); spread_sheet_row.size() != sub_index; ++sub_index){

                    if(sub_index == index){ continue; }

                    auto divisor(spread_sheet_row[sub_index]);

                    if(0 != numerator % divisor){ continue; }

                    result_found = true;
                    result = numerator / divisor;
                    break;
                }
                if(result_found){ break; }
            }

            results.push_back(result);
        }
    );

    assert(results.size() == spread_sheet.size());

    size_t result(0);
    std::for_each(results.cbegin(), results.cend(), [&result]
        (const size_t difference){
            result += difference;
        }
    );

    return(result);
}