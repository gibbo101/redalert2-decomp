// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/HouseAlliance.hpp"
#include <array>
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
namespace {
void require(bool b){if(!b)throw std::invalid_argument("House alliance fixture outside domain");}
template<class T>T take(std::istream& in){T v{};require(bool(in>>v));return v;}
struct Type {int country=0,parent=0;std::uint8_t passive=0;int comparison=0;std::string name;};
struct House {int index=0;const void* type=nullptr;std::uint8_t field=0;std::uint32_t allies=0;};
void run(std::istream& in){
 require(take<char>(in)=='H');int root=take<int>(in),current=take<int>(in),target=take<int>(in),country=take<int>(in),mode=take<int>(in),unrestricted=take<int>(in),houseCount=take<int>(in),typeCount=take<int>(in),mutation=take<int>(in);
 require(root>=0&&root<=2&&current>=1&&current<=5&&target>=1&&target<=5&&houseCount>=-2&&houseCount<=8&&typeCount>=-2&&typeCount<=4&&mutation>=0&&mutation<=4);
 std::array<Type,4> types;std::array<House,5> houses;std::array<const void*,8> houseSlots{},altHouses{};std::array<const void*,4> typeSlots{},altTypes{};
 const auto hp=[&](int id)->const void*{require(id>=0&&id<=5);return id?&houses[std::size_t(id-1)]:nullptr;};
 const auto tp=[&](int id)->const void*{require(id>=0&&id<=4);return id?&types[std::size_t(id-1)]:nullptr;};
 const auto hid=[&](const void* p){for(int i=0;i<=5;++i)if(hp(i)==p)return i;throw std::invalid_argument("Foreign House");};
 const auto tid=[&](const void* p){for(int i=0;i<=4;++i)if(tp(i)==p)return i;throw std::invalid_argument("Foreign type");};
 for(auto& p:houseSlots)p=hp(take<int>(in));for(auto& p:typeSlots)p=tp(take<int>(in));
 for(std::size_t i=0;i<4;++i){auto& t=types[i];t.country=take<int>(in);t.parent=take<int>(in);const auto flag=take<unsigned>(in);require(flag<=255);t.passive=std::uint8_t(flag);t.comparison=take<int>(in);t.name="Type"+std::to_string(i);altTypes[i]=tp(4-int(i));}
 for(auto& h:houses){h.index=take<int>(in);h.type=tp(take<int>(in));const auto field=take<unsigned>(in);require(field<=255);h.field=std::uint8_t(field);h.allies=take<std::uint32_t>(in);}
 std::string extra;require(!(in>>extra));for(std::size_t i=0;i<8;++i)altHouses[i]=hp(5-int(i%5));
 std::span<const void*> hs=houseSlots,ts=typeSlots;HouseAllianceWorld w{mode,unrestricted,houseCount,hs,typeCount,ts};
 w.house=[&](const void* p){const auto& h=houses.at(std::size_t(hid(p)-1));return HouseAllianceRecord{p,h.index,h.type,h.field,h.allies};};
 w.type=[&](const void* p){const auto& t=types.at(std::size_t(tid(p)-1));return HouseAllianceType{t.country,t.parent,t.passive,t.name};};
 int calls=0;w.compareNames=[&](std::string_view name,std::string_view wanted){require(wanted=="Civilian");int i=0;while(i<4&&types[std::size_t(i)].name!=name)++i;require(i<4);const int result=types[std::size_t(i)].comparison;std::cout<<" C "<<i+1<<' '<<result;
  if(!calls++){
   auto& self=houses[std::size_t(current-1)];auto& other=houses[std::size_t(target-1)];
   if(mutation==1){types[std::size_t(tid(other.type)-1)].parent=-1;mode=1;unrestricted=1;self.field=0;}
   if(mutation==2){ts=altTypes;typeCount=4;houseCount=2;self.allies^=0xffffffffu;other.type=tp(4);mode=0;unrestricted=0;}
   if(mutation==3){typeCount=-1;self.index=other.index;}
   if(mutation==4){hs=altHouses;houseCount=5;self.index=-32;types[std::size_t(tid(other.type)-1)].passive^=1;}
  }return result;};
 int result=0;
 if(root==0)result=canMakeHouseAlliance(hp(current),hp(target),w);
 else if(root==1)result=hid(findHouseAllianceCountry(country,w));
 else result=findHouseAllianceType("Civilian",w);
 std::cout<<" R "<<result;
 std::cout<<" S "<<mode<<' '<<unrestricted<<' '<<houseCount<<' '<<typeCount<<' '<<(hs.data()==altHouses.data())<<' '<<(ts.data()==altTypes.data());
 for(const auto& h:houses)std::cout<<' '<<h.index<<' '<<tid(h.type)<<' '<<unsigned(h.field)<<' '<<h.allies;
 for(const auto& t:types)std::cout<<' '<<t.parent<<' '<<unsigned(t.passive);std::cout<<'\n';
}
void guards(){
 int mode=0,flag=0,count=0,types=0;std::span<const void*> empty;HouseAllianceWorld w{mode,flag,count,empty,types,empty};
 require(!findHouseAllianceCountry(13,w)&&findHouseAllianceType("Civilian",w)==-1);
 bool caught=false;try{canMakeHouseAlliance(nullptr,nullptr,w);}catch(const std::invalid_argument&){caught=true;}require(caught);
 count=1;caught=false;try{findHouseAllianceCountry(0,w);}catch(const std::invalid_argument&){caught=true;}require(caught);
 std::cout<<"House alliance guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
