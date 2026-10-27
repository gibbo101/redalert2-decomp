// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/TheaterTileFiles.hpp"
#include <iostream>
using namespace ra2;
template<class F>void refused(F f){try{f();}catch(const std::exception&){return;}throw std::runtime_error("Expected safety refusal");}
int main(){try{
    std::array<int,16> numbers{};numbers.fill(-1);std::vector<TheaterTileSetInput> sets(2);sets[0].count=1;
    std::vector<std::string> prefixes{"W-a-","TILE"};const auto absent=[](const std::string&)->std::optional<Data>{return std::nullopt;};
    auto r=prepareLoadedTheaterTiles(numbers,sets,prefixes,0,absent);
    if(r.primary!=std::vector<int>{0}||r.allTypes.size()!=1||r.allTypes[0].image)throw std::runtime_error("Absent primary binding differs");
    for(int theater:{-1,3})refused([&]{prepareLoadedTheaterTiles(numbers,sets,prefixes,theater,absent);});
    for(auto prefix:{"../tile","","12345678901234567"}){prefixes[0]=prefix;refused([&]{prepareLoadedTheaterTiles(numbers,sets,prefixes,0,absent);});}
    prefixes={"TILE"};refused([&]{prepareLoadedTheaterTiles(numbers,sets,prefixes,0,absent);});
    std::cout<<"Loaded theater native domain guards: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
