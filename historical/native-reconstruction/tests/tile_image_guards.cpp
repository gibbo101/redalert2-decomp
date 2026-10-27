// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/TileImagePreparation.hpp"
#include <cfenv>
#include <iostream>
using namespace ra2;
template<class F> void refused(F f){try{f();}catch(const std::exception&){return;}throw std::runtime_error("Expected native safety refusal");}
void word(Bytes& b,std::size_t p,std::uint32_t n){for(int i=0;i<4;++i)b[p+std::size_t(i)]=std::uint8_t(n>>(i*8));}
int main(){try{
    refused([]{prepareTileImage(Data{Bytes(15)});});
    for(auto dimensions:std::array<std::array<unsigned,2>,4>{{{256,1},{1,256},{255,255},{0xffffffffu,1}}}){
        Bytes b(20);word(b,0,dimensions[0]);word(b,4,dimensions[1]);refused([&]{prepareTileImage(Data{b});});
    }
    Bytes b(20);word(b,0,1);word(b,4,1);word(b,16,4);refused([&]{prepareTileImage(Data{b});});
    const int previous=std::fegetround();if(std::fesetround(FE_UPWARD))throw std::runtime_error("FP setup unavailable");
    word(b,16,20);refused([&]{prepareTileImage(Data{b});});
    if(std::fegetround()!=FE_UPWARD)throw std::runtime_error("Throw changed caller rounding");
    word(b,16,0);prepareTileImage(Data{b});
    if(std::fegetround()!=FE_UPWARD)throw std::runtime_error("Preparation changed caller rounding");
    if(std::fesetround(previous))throw std::runtime_error("FP restoration unavailable");
    std::cout<<"Tile image native domain and FP guards: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
