// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TechnoTypeCost.hpp"
#include <array>
#include <bit>
#include <cfenv>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("Type cost fixture differs");}
void run(std::istream& in){
 int present=0,kind=0,speed=0,base=0;require(bool(in>>present>>kind>>speed>>base)&&present>=0&&present<=1);std::array<std::uint32_t,5> bits{};for(auto& v:bits)require(bool(in>>v));std::string extra;require(!(in>>extra));
 int type=0,house=0,kindCalls=0,baseCalls=0;std::uint32_t factor=0;
 const auto event=[&](int k,std::uint32_t v=0){std::cout<<k<<' '<<v<<' ';};
 TechnoTypeCostServices s;
 s.kind2C=[&](const void* p){require(p==&type);++kindCalls;event(3,std::uint32_t(kind));return kind;};s.speedTypeBA0=[&](const void* p){require(p==&type);return speed;};
 s.countryFactor=[&](const void* p,std::int64_t off){require(p==&house&&off>=0x114&&off<=0x124&&(off-0x114)%4==0);return std::bit_cast<float>(bits.at(std::size_t((off-0x114)/4)));};s.baseCostAC=[&](const void* p){require(p==&type);++baseCalls;event(4,std::uint32_t(base));return base;};
 s.trace=[&](char k,std::uint32_t v){if(k=='f'){factor=v;event(5,v);}else{require(k=='c');event(6);}};
 // House4F5960 entry is a pure observation of the actual kernel call, not a
 // separate replacement multiplier; observe immediately before its kind read.
 const auto kindQuery=s.kind2C;s.kind2C=[&](const void* p){event(2);return kindQuery(p);};
 const auto result=technoTypeCost(&type,present?&house:nullptr,s);
 std::cout<<"F "<<result<<' '<<factor<<' '<<kindCalls<<' '<<baseCalls<<'\n';
}
void guards(){
 const auto refused=[&](auto fn){bool failed=false;try{fn();}catch(const std::invalid_argument&){failed=true;}require(failed);};
 int type=0,house=0;TechnoTypeCostServices s;s.baseCostAC=[](auto){return -1;};require(technoTypeCost(&type,nullptr,s)==~0u);refused([&]{technoTypeCost(&type,&house,s);});
 s.kind2C=[](auto){return 16;};refused([&]{technoTypeCost(&type,&house,s);});s.kind2C=[](auto){return 7;};refused([&]{technoTypeCost(&type,&house,s);});
 s.kind2C=[](auto){return 0;};require(technoTypeCost(&type,&house,s)==~0u);s.kind2C=[](auto){return 16;};s.countryFactor=[](auto,auto){return 1.f;};
 const int prior=std::fegetround();require(std::fesetround(FE_UPWARD)==0);require(technoTypeCost(&type,&house,s)==~0u&&std::fegetround()==FE_UPWARD);s.baseCostAC=[](auto)->int{throw std::invalid_argument("late cost fault");};refused([&]{technoTypeCost(&type,&house,s);});require(std::fegetround()==FE_UPWARD);require(std::fesetround(prior)==0);
 std::cout<<"Techno Type cost guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
