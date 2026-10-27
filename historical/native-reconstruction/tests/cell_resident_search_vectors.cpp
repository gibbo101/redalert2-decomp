// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/CellResidentSearch.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace ra2;
namespace {
struct Resident {std::int32_t kind=0;const Resident* next=nullptr;};
void require(bool value){if(!value)throw std::invalid_argument("Cell resident search fixture outside domain");}
template<class T>T take(std::istream& in){T value{};require(bool(in>>value));return value;}
void run(std::istream& in){
    require(take<char>(in)=='R');const int initial=take<int>(in);const auto selector=take<std::uint32_t>(in);
    const auto requested=take<std::int32_t>(in);const int split=take<int>(in),count=take<int>(in);
    require(initial>=0&&initial<=255&&split>=0&&split<=count&&count<=32);
    std::vector<Resident> residents(static_cast<std::size_t>(count),Resident{});
    for(auto& resident:residents)resident.kind=take<std::int32_t>(in);
    std::string extra;require(!(in>>extra));
    for(int i=0;i<count;++i)residents[std::size_t(i)].next=i+1<count&&i+1!=split?&residents[std::size_t(i+1)]:nullptr;
    CellResidentKind6State state{std::uint8_t(initial)};
    const void* primary=split?&residents[0]:nullptr;
    const void* secondary=split<count?&residents[std::size_t(split)]:nullptr;
    CellResidentKind6Services services;
    const auto id=[&](const void* p){return p?int(static_cast<const Resident*>(p)-residents.data()):-1;};
    services.kind=[&](const void* p){const int i=id(p);require(i>=0&&i<count);std::cout<<"K "<<i<<' '<<residents[std::size_t(i)].kind<<' ';return residents[std::size_t(i)].kind;};
    services.next=[&](const void* p){const int i=id(p);require(i>=0&&i<count);const auto next=residents[std::size_t(i)].next;std::cout<<"N "<<i<<' '<<id(next)<<' ';return next;};
    std::cout<<"S "<<unsigned(state.enabled)<<' ';
    const auto found=findCellResident(state,{primary,secondary},requested,selector,services);
    std::cout<<"R "<<id(found)<<'\n';
}
void guards(){
    const void* primary=reinterpret_cast<const void*>(1);const void* secondary=nullptr;
    CellResidentKind6State state{};
    require(findCellResident(state,{primary,secondary},36,0,{})==nullptr);
    state.enabled=255;
    require(findCellResident(state,{primary,secondary},36,1,{})==nullptr);
    bool refused=false;try{(void)findCellResident(state,{primary,secondary},36,256,{});}catch(const std::invalid_argument&){refused=true;}
    require(refused);
    CellResidentKind6Services services;services.kind=[](const void*){return 36;};
    require(findCellResident(state,{primary,secondary},36,0,services)==primary);
    services.kind=[](const void*){return 6;};refused=false;
    try{(void)findCellResident(state,{primary,secondary},36,0,services);}catch(const std::invalid_argument&){refused=true;}
    require(refused);std::cout<<"Cell resident search guards PASS\n";
}
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);
    std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;
}catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}}
