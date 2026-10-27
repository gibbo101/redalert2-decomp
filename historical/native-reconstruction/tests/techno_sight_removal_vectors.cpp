// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TechnoSightRemoval.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace ra2;
namespace {
void require(bool value){if(!value)throw std::invalid_argument("Techno sight removal fixture outside domain");}
template<class T>T take(std::istream& in){T value{};require(bool(in>>value));return value;}
const void* token(std::uintptr_t n){return reinterpret_cast<const void*>(n);}
void run(std::istream& in){
    require(take<char>(in)=='R');const int enabled=take<int>(in),country=take<int>(in),activeValue=take<int>(in);
    TechnoSightPoint last{take<std::int32_t>(in),take<std::int32_t>(in),take<std::int32_t>(in)};const auto range=take<std::int32_t>(in);
    const auto arg1=take<std::uint32_t>(in),arg2=take<std::uint32_t>(in),arg3=take<std::uint32_t>(in);const int house=take<int>(in);std::string extra;require(!(in>>extra));
    require((enabled==0||enabled==1)&&(country==0||country==1)&&(activeValue==0||activeValue==1)&&(house==0||house==1));
    std::uint8_t enabledByte=enabled,countryByte=country,active=activeValue;TechnoSightRemovalServices services;
    services.trace=[](char kind,std::int32_t value){std::cout<<kind<<' '<<value<<' ';};
    services.revealArea=[&](const TechnoSightRequest& q){const int hid=q.house==token(1)?1:q.house==token(2)?2:0;require(hid);
        std::cout<<"C "<<q.coordinates.x<<' '<<q.coordinates.y<<' '<<q.coordinates.z<<' '<<q.range<<' '<<hid<<' '<<q.forwarded1<<' '<<q.forwarded2<<' '<<q.fixed0<<' '<<q.fixed1<<' '<<q.fixed2<<' ';};
    removeTechnoSight({enabledByte,countryByte,active,last,range,token(1)},arg1,arg2,arg3,house?token(2):nullptr,services);
    std::cout<<"S "<<unsigned(active)<<'\n';
}
void guards(){
    std::uint8_t enabled=1,country=0,active=1;TechnoSightPoint last{};std::int32_t range=1;bool refused=false;
    try{removeTechnoSight({enabled,country,active,last,range,token(1)},0,0,0,nullptr,{});}catch(const std::invalid_argument&){refused=true;}
    require(refused&&active==0);enabled=0;active=1;removeTechnoSight({enabled,country,active,last,range,token(1)},0,0,0,nullptr,{});require(active==1);
    std::cout<<"Techno sight removal guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
