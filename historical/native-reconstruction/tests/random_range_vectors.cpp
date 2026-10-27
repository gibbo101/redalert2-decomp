// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/OriginalRandomRange.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace ra2;
template<class T>T take(std::istream& in){T v{};if(!(in>>v))throw std::invalid_argument("Missing random-range input");return v;}
void guards(){
    OriginalRandomState state;state.next1=-1;state.next2=999;
    if(rangedOriginalRandom(state,17,17)!=17||rangedOriginalRandom(state,0,2147483647)!=(-2147483647-1))throw std::runtime_error("Bypass touched invalid RNG");
    bool refused=false;try{(void)rangedOriginalRandom(state,0,2);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Active invalid RNG accepted");
    refused=false;try{(void)rangedOriginalRandom(state,-2147483647-1,2147483647);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Nonterminating span accepted");
    state.disabled=255;
    if(rangedOriginalRandom(state,4,1)!=1||state.next1!=-1||state.next2!=999)throw std::runtime_error("Disabled RNG changed");
    state={};state.next1=0;state.next2=103;state.table[0]=3;
    unsigned calls=0;refused=false;
    try{(void)rangedOriginalRandom(state,0,2,[&](auto raw,const auto&){if(raw!=3)throw std::logic_error("Unexpected guard raw");++calls;},1);}
    catch(const std::runtime_error&){refused=true;}
    if(!refused||calls!=1||state.next1!=1||state.next2!=104||state.table[0]!=3)throw std::runtime_error("Draw-bound prefix lost");
    if(rangedOriginalRandom(state,5,5,{},0)!=5)throw std::runtime_error("Equal range needs draw budget");
    std::cout<<"6 native guard checks PASS\n";
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=1)return 2;
    std::string line;
    while(std::getline(std::cin,line)){
        std::istringstream in(line);if(take<char>(in)!='R')return 2;
        const int disabled=take<int>(in);OriginalRandomState state;
        if(disabled<0||disabled>255)throw std::invalid_argument("Random-range disabled byte");
        state.disabled=std::uint8_t(disabled);state.next1=take<int>(in);state.next2=take<int>(in);
        const int count=take<int>(in);if(count<1||count>1024)throw std::invalid_argument("Random-range call count");
        std::vector<std::pair<std::int32_t,std::int32_t>> ranges;
        for(int i=0;i<count;++i){const auto low=take<std::int32_t>(in),high=take<std::int32_t>(in);ranges.emplace_back(low,high);}
        for(auto& word:state.table)word=take<std::uint32_t>(in);
        std::string extra;if(in>>extra)throw std::invalid_argument("Extra random-range input");
        for(const auto& [low,high]:ranges){
            const auto value=rangedOriginalRandom(state,low,high,[&](auto raw,const auto& after){std::cout<<"D "<<raw<<' '<<after.next1<<' '<<after.next2<<' ';});
            std::cout<<"R "<<value<<' ';
        }
        std::cout<<"state "<<unsigned(state.disabled)<<' '<<state.next1<<' '<<state.next2<<' ';
        for(auto word:state.table)std::cout<<word<<' ';
        std::cout<<'\n';
    }
    return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
