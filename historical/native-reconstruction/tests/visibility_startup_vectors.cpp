// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/VisibilityStartup.hpp"
#include <bit>
#include <cstdint>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>

using namespace ra2;
namespace {
void require(bool value){if(!value)throw std::invalid_argument("Visibility startup fixture outside domain");}
void emit(){
    const auto state=initializeVisibilityStartup();
    std::cout<<"V";
    for(auto value:state.radiusCounts)std::cout<<' '<<value;
    for(auto point:state.offsets)std::cout<<' '<<point.x<<' '<<point.y;
    for(auto point:state.heightOffsets)std::cout<<' '<<point.x<<' '<<point.y;
    std::cout<<' '<<std::bit_cast<std::uint64_t>(state.heightProjectionScale)<<'\n';
}
void guards(){
    const auto state=initializeVisibilityStartup();
    require(state.radiusCounts.front()==1&&state.radiusCounts.back()==309);
    for(std::size_t i=0;i<state.heightOffsets.size();++i){
        if(i==101)continue;
        const auto p=state.offsets[i];const int ax=p.x<0?-int(p.x):int(p.x),ay=p.y<0?-int(p.y):int(p.y);
        const auto opposite=[](std::int16_t value){return std::int16_t(value<0?1:value>0?-1:0);};
        require(state.heightOffsets[i].x==(ax*2<ay?0:opposite(p.x)));
        require(state.heightOffsets[i].y==(ay*2<ax?0:opposite(p.y)));
    }
    require(state.offsets[101].x==5&&state.offsets[101].y==-2);
    require(state.heightOffsets[101].x==1&&state.heightOffsets[101].y==0);
    std::set<std::pair<std::int16_t,std::int16_t>> unique;
    for(auto point:state.offsets)unique.emplace(point.x,point.y);
    require(unique.size()==368);
    require(state.offsets[319].x==-3&&state.offsets[319].y==11);
    require(state.offsets[322].x==-3&&state.offsets[322].y==11);
    require(std::bit_cast<std::uint64_t>(state.heightProjectionScale)==0x3fc25e5374344960ULL);
    std::cout<<"Visibility startup guards PASS\n";
}
}
int main(int argc,char** argv){
    try{
        if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
        require(argc==1);
        std::string line;
        while(std::getline(std::cin,line)){require(line=="V");emit();}
        return 0;
    }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
