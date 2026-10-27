// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TechnoSight.hpp"
#include <bit>
#include <cstdint>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Techno sight fixture outside domain");}
template<class T>T take(std::istream& in){T v{};require(bool(in>>v));return v;}
const void* token(std::uintptr_t n){return reinterpret_cast<const void*>(n);}
void run(std::istream& in){
 require(take<char>(in)=='S');const int enabled=take<int>(in),country=take<int>(in);
 TechnoSightPoint current{take<std::int32_t>(in),take<std::int32_t>(in),take<std::int32_t>(in)};
 std::int32_t divisor=take<std::int32_t>(in);int increaseValue=take<int>(in);std::int32_t sight=take<std::int32_t>(in);
 const auto timerBits=take<std::uint64_t>(in);int veteranValue=take<int>(in),eliteValue=take<int>(in);const auto multiplierBits=take<std::uint64_t>(in);
 int activeValue=take<int>(in);TechnoSightPoint last{take<std::int32_t>(in),take<std::int32_t>(in),take<std::int32_t>(in)};std::int32_t lastRange=take<std::int32_t>(in);
 const auto arg1=take<std::uint32_t>(in),arg2=take<std::uint32_t>(in),arg3=take<std::uint32_t>(in);const int house=take<int>(in);std::string extra;require(!(in>>extra));
 require((enabled==0||enabled==1)&&(country==0||country==1)&&increaseValue>=-128&&increaseValue<=127&&(veteranValue==0||veteranValue==1)&&(eliteValue==0||eliteValue==1)&&(activeValue==0||activeValue==1)&&(house==0||house==1));
 std::uint8_t enabledByte=enabled,countryByte=country,veteranByte=veteranValue,eliteByte=eliteValue,activeByte=activeValue;std::int8_t increase=std::int8_t(increaseValue);
 const double timer=std::bit_cast<double>(timerBits),multiplier=std::bit_cast<double>(multiplierBits);
 TechnoSightServices services;
 services.type=[&]{return TechnoSightType{veteranByte,eliteByte,sight};};services.heightDivisor1324=[&]() -> const std::int32_t& {return divisor;};services.veteranSight5a0=[&]() -> const double& {return multiplier;};
 services.trace=[](char kind,std::int32_t value){std::cout<<kind;if(kind!='T'&&kind!='V'&&kind!='E'&&kind!='M')std::cout<<' '<<value;std::cout<<' ';};
 services.revealArea=[&](const TechnoSightRequest& q){const auto hid=q.house==token(1)?1:q.house==token(2)?2:0;require(hid);std::cout<<"C "<<q.coordinates.x<<' '<<q.coordinates.y<<' '<<q.coordinates.z<<' '<<q.range<<' '<<hid<<' '<<q.forwarded1<<' '<<q.forwarded2<<' '<<q.fixed0<<' '<<q.fixed1<<' '<<q.fixed2<<' ';};
 TechnoSightActor actor{enabledByte,countryByte,current,timer,increase,activeByte,last,lastRange,token(1)};
 updateTechnoSight(actor,arg1,arg2,arg3,house?token(2):nullptr,services);
 std::cout<<"S "<<int(increase)<<' '<<unsigned(activeByte)<<' '<<last.x<<' '<<last.y<<' '<<last.z<<' '<<lastRange<<'\n';
}
void guards(){
 std::uint8_t enabled=1,country=0,active=0;std::int8_t inc=0;TechnoSightPoint current{},last{};double timer=0.;std::int32_t range=0,divisor=0,sight=1;TechnoSightActor actor{enabled,country,current,timer,inc,active,last,range,token(1)};TechnoSightServices services;std::uint8_t typeFlag=0;double multiplier=1.;services.type=[&]{return TechnoSightType{typeFlag,typeFlag,sight};};services.heightDivisor1324=[&]() -> const auto& {return divisor;};services.veteranSight5a0=[&]() -> const auto& {return multiplier;};
 bool refused=false;try{updateTechnoSight(actor,0,0,0,nullptr,services);}catch(const std::invalid_argument&){refused=true;}require(refused);
 divisor=1;services.veteranSight5a0={};active=1;timer=0.;updateTechnoSight(actor,0,0,0,nullptr,services);require(active==1);
 enabled=0;updateTechnoSight(actor,0,0,0,nullptr,{});require(inc==0&&active==1);
 std::cout<<"Techno sight guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
