// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/InfantryWeaponSelection.hpp"
#include <bit>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Infantry weapon-selection fixture outside domain");}
template<class T>T take(std::istream& in){T v{};require(bool(in>>v));return v;}
void run(std::istream& in){
 require(take<char>(in)=='S');int state=take<int>(in);const auto rankBits=take<std::uint64_t>(in);int mission=take<int>(in);
 int np=take<int>(in),ns=take<int>(in),ep=take<int>(in),es=take<int>(in),nn=take<int>(in),na=take<int>(in),en=take<int>(in),ea=take<int>(in);std::string extra;
 require(!(in>>extra)&&!(state>=27&&state<=30)&&mission>=-1&&mission<=30);
 for(int v:{np,ns,ep,es,nn,na,en,ea})require(v==0||v==1);
 const int primary=1,secondary=2;InfantryWeaponSelectionType type;
 type.weapons={InfantryWeaponSelectionWeapon{np?&primary:nullptr},InfantryWeaponSelectionWeapon{ns?&secondary:nullptr,std::uint8_t(nn),std::uint8_t(na)}};
 type.eliteWeapons={InfantryWeaponSelectionWeapon{ep?&primary:nullptr},InfantryWeaponSelectionWeapon{es?&secondary:nullptr,std::uint8_t(en),std::uint8_t(ea)}};
 const double rank=std::bit_cast<double>(rankBits);int turret=-1,kind=15;
 InfantryWeaponSelectionServices services;
 services.type=[&]() -> const auto& {std::cout<<"T ";return type;};
 services.mission=[&]{std::cout<<"M "<<mission<<' ';return mission;};
 const auto result=selectInfantryWeaponForNullTarget({state,turret,rank,kind},nullptr,services);
 std::cout<<"R "<<result<<'\n';
}
void guards(){
 int state=0,turret=-1,kind=15;double rank=0.;InfantryWeaponSelectionType type;InfantryWeaponSelectionServices services;
 bool refused=false;try{(void)selectInfantryWeaponForNullTarget({state,turret,rank,kind},nullptr,services);}catch(const std::invalid_argument&){refused=true;}require(refused);
 services.type=[&]() -> const auto& {return type;};services.mission=[] {return 2;};type.weapons[0].identity=&type;type.weapons[1].identity=&type;
 state=27;refused=false;try{(void)selectInfantryWeaponForNullTarget({state,turret,rank,kind},nullptr,services);}catch(const std::invalid_argument&){refused=true;}require(refused);
 state=0;refused=false;try{(void)selectInfantryWeaponForNullTarget({state,turret,rank,kind},&type,services);}catch(const std::invalid_argument&){refused=true;}require(refused);
 type.turretCount704=1;refused=false;try{(void)selectInfantryWeaponForNullTarget({state,turret,rank,kind},nullptr,services);}catch(const std::invalid_argument&){refused=true;}require(refused);type.turretCount704=0;
 std::cout<<"Infantry weapon-selection guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
