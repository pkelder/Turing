#include <axe.h>
#include <iostream>
#include "Simulation.h"

using namespace axe;

void parseTuring(std::string const& input, Simulation* sim) {

    std::string sourceState;
    std::string targetState;
    vector<char> readings;
    vector<char> writings;
    vector<int> moves;

    //states
    auto source = r_alnumstr() >> sourceState;
    auto final = r_alnumstr() >> targetState;

    //read
    auto rd = r_any() >> e_push_back(readings);
    auto loopr = ',' & rd;
    auto read = ('{' & rd & *loopr & '}') | rd;

    //write
    auto wr = r_any() >> e_push_back(writings);
    auto loopw = ',' & wr;
    auto write = ('{' & wr & *loopw & '}') | wr;

    //move
    auto mv = ("-1" | r_any("01")) >> e_push_back(moves);
    auto loopmv = ',' & mv;
    auto move = ('{' & mv & *loopmv & '}') | mv;

    //trailing spaces
    auto space = r_any(" \t");
    auto endl = *space & r_lit('\n');

    //full line
    auto line = (source & "->" & read & ',' & write & ',' & move & "--" & final) >> e_ref([&](const char* i1, const char* i2)
    {
    std::cout << "Source : " << sourceState << std::endl << "Read : ";
    for (char c : readings) {
    std::cout << c;
    }
    std::cout << std::endl << "Write : ";
    for (char c : writings) {
        std::cout << c;
    }
    std::cout << std::endl << "Moves : ";
    for (int i : moves) {
        std::cout << i;
    }
    std::cout << std::endl << "Target : " << targetState << std::endl;
    sim->addTransition(readings,writings,moves,sourceState,targetState);
    })
    | r_fail([](const char* i1, const char* i2)
    {
        std::cout << "Error : Couldn't parse line : " << std::string(i1,i2);
    });

    //full file
    auto clear = e_ref([&](const char* i1, const char* i2)
    {
        readings.clear();
        writings.clear();
        moves.clear();
    });

    auto file = +(line & endl >> clear) & r_end();

    //now, go for it
    file(input.c_str(), input.c_str() + input.length());

}

