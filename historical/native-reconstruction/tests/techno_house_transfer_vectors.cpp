// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TechnoHouseTransfer.hpp"
#include "sim/HouseInfantryAccounting.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("Techno House transfer fixture differs");}
void run(std::istream& in){
 std::array<std::int32_t,13> f{};for(auto& n:f)require(bool(in>>n));std::string extra;require(!(in>>extra));
 require(f[0]>=0&&f[0]<=1&&f[1]>=1&&f[1]<=2&&f[4]>=0&&f[4]<=255&&f[5]>=0&&f[5]<=255&&f[6]>=0&&f[6]<=1&&f[7]>=0&&f[7]<=2&&f[11]>=0&&f[11]<=1);
 struct House {HouseInfantryAccountingState accounting;std::uint32_t value;std::int32_t previous=-777,country;std::array<std::uint32_t,32> indexed;};
 std::array<House,2> houses;
 for(int i=0;i<2;++i){auto& h=houses[i];h.value=std::uint32_t(f[10]);h.country=13+i;h.accounting.count234=std::uint32_t(f[10]);h.accounting.activeCapacity=h.accounting.registeredCapacity=h.accounting.historyCount1270=32;h.accounting.active5440.resize(32);h.accounting.registered5480.resize(32);for(int j=0;j<32;++j){const auto v=std::uint32_t(f[10])+std::uint32_t(j);h.indexed[j]=h.accounting.active5440[j]=h.accounting.registered5480[j]=h.accounting.historyA70[j]=v;}}
 int actor=0,type=0,cell=0;const void* owner=&houses[0];const void* local=f[7]?&houses[f[7]-1]:nullptr;auto flag=std::uint8_t(f[4]),flags=std::uint8_t(f[5]),field=std::uint8_t(255),registered=std::uint8_t(1),hidden=std::uint8_t(0),type202=std::uint8_t(0);auto threat=std::uint32_t(f[3]),point=0x0059003fu;Coord position{256,512,104};
 const auto event=[&](int k,std::uint32_t a=0,std::uint32_t b=0,std::uint32_t c=0,std::uint32_t d=0,std::uint32_t e=0){std::cout<<k<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<e<<' ';};
 const auto hid=[&](const void* p)->std::uint32_t{if(!p)return 0;for(int i=0;i<2;++i)if(p==&houses[i])return i+1;throw std::invalid_argument("Foreign transfer House");};
 const auto get=[&](const void* p)->House&{const auto i=hid(p);require(i);return houses[i-1];};
 const HouseInfantryStore accountingStore=[&](const void* p,std::int64_t off,std::uint32_t value){if(p==&actor){event(1,10,std::uint32_t(off),value);return;}for(auto& h:houses){for(int k=0;k<2;++k)if(p==(k?&h.accounting.registered5480:&h.accounting.active5440)){event(1,hid(&h),k?0x5480:0x5440,value,std::uint32_t(off/4));return;}}event(1,hid(p),std::uint32_t(off),value);};
 HouseInfantryActor accountingActor{&actor,registered,hidden,[&]{event(3);return HouseInfantryType{type202,[&]{event(4);return 3;}};},[&]{event(5);return 15u;}};
 const auto accounting=[&](const void* p,int which,std::uint32_t argument){event(10,which,hid(p),which<2?argument:0);withHouseInfantryAccounting(get(p).accounting,p,[&](auto& h){switch(which){case 0:require(argument==0);removeRegisteredHouseInfantry(h,accountingActor,[&]{event(10,5);checkHouseTransferMapRemoval(0);},accountingStore);break;case 1:require(argument==1);addRegisteredHouseInfantry(h,accountingActor,accountingStore);break;case 2:removeActiveHouseInfantry(h,accountingActor,accountingStore);break;case 3:addActiveHouseInfantry(h,accountingActor,accountingStore);break;default:require(false);}});};
 TechnoHouseTransferActor a{&actor,flag,flags,position,threat,field,[&]{return owner;},[&](const void* p){(void)get(p);owner=p;}};
 TechnoHouseTransferServices s{local};
 s.house=[&](const void* p){auto& h=get(p);return TechnoHouseTransferHouse{h.value,h.indexed,h.previous,h.country};};
 s.clear370=[&](const void* p){require(!p);event(16,0x370);};s.destination410=[&](const void* p,std::uint32_t v){require(!p&&v==1);event(16,0x410,0,1);};
 s.detach6155E0=[&]{event(10,4);detachNullTechnoController(nullptr);};s.remove4ED440=[&](const void* p,auto v){accounting(p,0,v);};s.notifyDC=[&](const void* p){require(!p);event(16,0xdc);};
 s.type80=[&]()->const void*{event(3);return &type;};s.cost84=[&](const void* p,const void* h){require(p==&type);event(12,hid(h));return std::uint32_t(f[2]);};
 s.remove4EA800=[&](const void* p){accounting(p,2,0);};s.add4EA970=[&](const void* p){accounting(p,3,0);};s.kind2C=[&]{event(5);return 15;};s.country38=[&]{const auto i=hid(owner);event(7,i);return std::int32_t(i-1);};
 s.draw11C=[&](auto v){event(16,0x11c,std::uint32_t(v));};s.clearReferences6D7C80=[&]{event(13);if(f[11]){flag=f[4]?0:255;event(9,10,0x76,flag);}};
 s.coordinate548000=[&](Coord p)->const void*{require(p.x==256&&p.y==512&&p.z==104);event(14,0,256,512,104);return f[6]?&cell:nullptr;};s.point454=[&]{return point;};s.cell548070=[&](auto p)->const void*{require(p==0x0059003f);event(14,1,p);return f[6]?&cell:nullptr;};
 s.threat476B20=[&](const void* p,auto country,auto value){require(p==&cell);event(15,std::uint32_t(country),value);};s.threat2A0=[&]{event(16,0x2a0);return std::uint32_t(f[9]);};s.add4ED610=[&](const void* p,auto v){accounting(p,1,v);};s.radio636E10=[&](auto v)->const void*{require(v==0);event(8);const std::array<const void*,1> links{};return houseTransferRadioSlot(links,v);};
 s.sight414=[&](const void* p,auto v){require(!p&&v==1);event(16,0x414,0,1);};s.sight424=[&]{event(16,0x424);};s.sight420=[&]{event(16,0x420);};s.store=[&](const void* p,auto off,auto value,const void* ptr){event(1,p==&actor?10:hid(p),std::uint32_t(off),ptr?hid(ptr):value);};
 const auto base=[&](const void* next,auto arg){event(11,arg);return std::uint32_t(transferTechnoHouse(a,next,s));};
 InfantryHouseTransferServices wrapper{base,[&]{event(16,0x54);return std::uint32_t(f[8]);},[&]{event(16,0x1a0);return 0x1234fedcu;},[&](auto v){point=v;event(1,10,0x454,v);}};
 const auto next=&houses[f[1]-1];const bool result=f[0]?transferInfantryHouse(next,std::uint32_t(f[12]),wrapper):base(next,std::uint32_t(f[12]));
 std::cout<<"F "<<result<<' '<<hid(owner)<<' '<<unsigned(field)<<' '<<threat<<' '<<unsigned(registered)<<' '<<point<<' '<<unsigned(flag)<<' ';
 for(const auto& h:houses){std::cout<<h.value<<' '<<std::uint32_t(h.previous)<<' ';for(auto v:h.indexed)std::cout<<v<<' ';for(auto v:h.accounting.active5440)std::cout<<v<<' ';for(auto v:h.accounting.registered5480)std::cout<<v<<' ';for(int j=0;j<32;++j)std::cout<<h.accounting.historyA70[j]<<' ';}std::cout<<'\n';
}
void guards(){
 const auto refused=[&](auto fn){bool fail=false;try{fn();}catch(const std::invalid_argument&){fail=true;}require(fail);};
 int token=0;std::array<const void*,2> slots{&token,nullptr};require(houseTransferRadioSlot(slots,0)==&token&&!houseTransferRadioSlot(slots,1));refused([&]{houseTransferRadioSlot(slots,-1);});refused([&]{houseTransferRadioSlot(slots,2);});
 refused([&]{detachNullTechnoController(&token);});refused([&]{checkHouseTransferMapRemoval(255);});detachNullTechnoController(nullptr);checkHouseTransferMapRemoval(0);
 const void* local=&token;std::uint8_t flag=0,field=9;std::uint32_t threat=7;Coord position{};TechnoHouseTransferActor a{&token,flag,flag,position,threat,field,[&]{return &token;},{}};TechnoHouseTransferServices s{local};
 require(!transferTechnoHouse(a,&token,s));refused([&]{transferTechnoHouse(a,nullptr,s);});int other=0;refused([&]{transferTechnoHouse(a,&other,s);});require(field==9&&threat==7);
 int calls=0;InfantryHouseTransferServices w{[&](const void* p,auto arg){require(p==&token&&arg==1);++calls;return 0x100u;},{},{}};require(!transferInfantryHouse(&token,0,w)&&calls==1);
 w.base6CD940=[&](const void*,auto arg){require(arg==1);return 0x101u;};w.query54=[] {return 0x100u;};w.point1A0=[] {return 0xabcdef01u;};w.set454=[&](auto v){require(v==0xabcdef01);++calls;};require(transferInfantryHouse(&token,~0u,w)&&calls==2);w.query54=[]{return 255u;};require(transferInfantryHouse(&token,0,w)&&calls==2);
 std::cout<<"Techno House transfer guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
