// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/BuildingDiscovery.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <array>
#include <stdexcept>
using namespace ra2;
namespace {
template<class... T>void event(const T&... v){((std::cout<<v<<' '),...);}
void require(bool v){if(!v)throw std::invalid_argument("Invalid Building discovery fixture");}
void guards(){
    require(!buildingHasRadioLinks(-1,{}));require(!buildingHasRadioLinks(0,{}));
    const std::array<std::uintptr_t,1> first{1};require(buildingHasRadioLinks(8,first));
    bool refused=false;try{buildingHasRadioLinks(1,{});}catch(const std::invalid_argument&){refused=true;}require(refused);
    UnitDiscoveryWorld w;w.houses[0]={};w.currentHouse=0;UnitDiscoveryActor a;
    // Rejected discovery must not require any wrapper child.
    a.current373=1;require(!discoverBuilding(a,0,w,{}));
    a.current373=0;w.loading=1;
    refused=false;try{discoverBuilding(a,0,w,{ {},[]{return false;},{} });}catch(const std::invalid_argument&){refused=true;}require(refused);
    std::cout<<"Building discovery guards PASS\n";
}
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op;int type,count,size;in>>op>>type>>count>>size;require(in&&op=='B'&&size>=0&&size<=8&&count<=size);
        std::vector<std::uintptr_t> links;for(int i=0;i<size;++i){unsigned v;in>>v;require(in&&v<=1);links.push_back(v);}
        UnitDiscoveryActor a;UnitDiscoveryWorld w;int tag,mutation;
        in>>w.mode>>w.loading>>w.tagContext>>w.currentHouse>>a.owner;
        const auto byte=[&](){int v;in>>v;require(in&&v>=0&&v<=255);return std::uint8_t(v);};
        const auto house=[](int v){return v>=-1&&v<=1;};
        a.field372=byte();a.current373=byte();a.other374=byte();in>>a.mission98>>a.queuedA0;a.queuedA4=byte();in>>tag>>mutation;
        require(in&&house(w.currentHouse)&&a.owner>=0&&a.owner<=1&&(tag==0||tag==1)&&(mutation==0||mutation==1));a.hasTag=tag;
        for(int i=0;i<2;++i){auto& h=w.houses[i];for(auto* p:{&h.human134,&h.control135,&h.discovered13c,&h.field13d,&h.field5668,&h.field5669})*p=byte();h.building18d=127;h.building144=255;}
        int calls;in>>calls;require(in&&calls>=1&&calls<=128);
        w.trace=[](char k,int v){event(k,v);};w.store=[](int s,int o,std::uint32_t v){event('W',s,o,v);};
        w.tagEvent=[&](int context){event('t',4,context);if(mutation){a.owner=1-a.owner;event('z',a.owner);}};
        BuildingDiscoveryServices services{[&]{return type;},[&]{event('r');return buildingHasRadioLinks(count,links);},[](std::uint8_t v){event('a',unsigned(v));}};
        for(int i=0;i<calls;++i){int discoverer;in>>discoverer;require(in&&house(discoverer));const bool accepted=discoverBuilding(a,discoverer,w,services);
            event('R',int(accepted),a.owner,unsigned(a.current373),unsigned(a.other374),a.queuedA0,unsigned(a.queuedA4));
            for(int j=0;j<2;++j){const auto& h=w.houses.at(j);event(unsigned(h.discovered13c),unsigned(h.field5668),unsigned(h.field5669));}
            for(int j=0;j<2;++j){const auto& h=w.houses.at(j);event('B',h.buildingType1b4,unsigned(h.building18d),unsigned(h.building144));}
        }
        in>>std::ws;require(in.eof());std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
