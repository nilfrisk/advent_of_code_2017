// day_1-inverse_captcha.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

namespace advent_of_code{
    size_t inverse_captcha(const std::vector<size_t>& digits);
    std::vector<size_t> generate_input();
}

int main()
{
    size_t result(0);

#ifdef _TEST_DATA

    result = advent_of_code::inverse_captcha({1,2,1,2});
    assert(6 == result);

    result = advent_of_code::inverse_captcha({1,2,2,1});
    assert(0 == result);

    result = advent_of_code::inverse_captcha({1,2,3,4,2,5});
    assert(4 == result);

    result = advent_of_code::inverse_captcha({1,2,3,1,2,3});
    assert(12 == result);

    result = advent_of_code::inverse_captcha({1,2,1,3,1,4,1,5});
    assert(4 == result);

#endif

    result = advent_of_code::inverse_captcha(advent_of_code::generate_input());
    
    return(EXIT_SUCCESS);
}

namespace advent_of_code{

    //NOTE: alternate would be to save as file and import
    const std::string question(
        "516299281491169512719425276194596424291268712697155863651846937925928"
        "456958813624428156218468331423858422613471962165756423837756856519754"
        "524985759763747559711257977361228357678293572698839754444752898835313"
        "399815748562519958329927911861654784216355489319995566297499836295985"
        "943899373615223375271231128914745273184498915241488393761676799914385"
        "265459983923743146555465177886491979962465918888396664233693243983969"
        "412682561799628789569294374554575677368219724142536789649121758582991"
        "345537639888858113763738518511184439854223386868764189133964543721941"
        "169786274781775658991329331759679943342217578532643519615296424396487"
        "669451453728113114748217177826874953466435436129165295379157226345786"
        "756899935747336785161745487933721527239394118721517195849186676814232"
        "887413175587327214144876898248571248517121796766248817366614333915154"
        "796983612174281237846165129114988453188844745119798643314857871527757"
        "831265298846833327863781341559381238458322786192379487455671563757123"
        "534253463563421716138641611915686247343417126655317378639314168461345"
        "613427262786624689498485599942336813995725145169355942616672812792174"
        "556866436158375938988738721253664772584577384558696477546232189312287"
        "262439452141564522329987139692281984783513691857538335537553448919819"
        "545332125483128878925492334361562192621672993868479566688564752226111"
        "784486619789588318171745995253645886833872665447241245329935643883892"
        "447524286642296955354249478815116517315832179925494818748478164317669"
        "471654464867111924676961162162841232473474394739793968624974397916495"
        "667233337397241933765513777241916359166994384923869741468174653353541"
        "147616645393917694581811193977311981752554551499629219873391493426883"
        "886536219455848354426461562995284162323961773644581815633779762634745"
        "339565196798724847722781666948626231631632144371873154872575615636322"
        "965353254642186897127423352618879431499138418872356116624818733232445"
        "649188793318829748789349813295218673497291134164395739665667255443366"
        "383299669973689528188264386373591424149784473698487315316676637165317"
        "972648916116755224598519934598889627918883283534261513179931798591959"
        "489372165295");

    std::vector<size_t> generate_input(){

        std::vector<size_t> digits;

        std::for_each(question.cbegin(), question.cend(), [&digits]
            (const char item){
                int number = item - '0';
                assert(-1 < number && 10 > number);

                digits.push_back(number);
            }
        );

        return(digits);
    }

    size_t ammount_to_add(const size_t digit, const size_t& last_digit){

        if(digit != last_digit){ return(0); }

        return(digit);
    }

    size_t get_digit_for_comparison(const size_t current_index, const std::vector<size_t>& digits){

        //NOTE: Fortunately, your list has an even number of elements.
        assert(0 == digits.size() % 2);

        auto offset(current_index + (digits.size() / 2));
        if(digits.size() <= offset){
            offset -= digits.size();
        }

        return(digits[offset]);
    }
}


size_t advent_of_code::inverse_captcha(const std::vector<size_t>& digits){

    size_t result(0);

    //Check if calc is required
    if(digits.empty()){ return(result); }

    //Process digits 
    for(size_t index(0); digits.size() != index; ++index){
        result += ammount_to_add(get_digit_for_comparison(index, digits), digits[index]);
    }

    return(result);
}

