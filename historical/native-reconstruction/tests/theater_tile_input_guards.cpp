// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/TheaterTileInputs.hpp"
#include <stdexcept>
using namespace ra2;
template<class F>void refused(F f){bool caught=false;try{f();}catch(const std::invalid_argument&){caught=true;}
    if(!caught)throw std::runtime_error("Theater input domain accepted");}
int main(){
    std::array<int,16> numbers{};numbers.fill(-1);
    refused([&]{prepareTheaterTileInputs(numbers,{});});
    std::array<TheaterTileSetInput,2> sets{};sets[0].count=1;
    sets[0].marble=-2;refused([&]{prepareTheaterTileInputs(numbers,sets);});
    sets[0].marble=2;refused([&]{prepareTheaterTileInputs(numbers,sets);});
    sets[0].marble=65535;sets[0].count=65537;refused([&]{prepareTheaterTileInputs(numbers,sets);});
    sets[0].count=-1;refused([&]{prepareTheaterTileInputs(numbers,sets);});
    sets[0].count=0;sets[1].count=0;refused([&]{prepareTheaterTileInputs(numbers,sets);});
}
