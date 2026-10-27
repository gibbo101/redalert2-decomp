// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/HouseInfantryAccounting.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("House Infantry fixture differs");}
void run(std::istream& in){
 std::array<int,12> f{};for(auto& n:f)require(bool(in>>n));std::string extra;require(!(in>>extra));
 require(f[0]>=0&&f[0]<=5&&f[3]>=0&&f[3]<16&&f[4]>=0&&f[4]<=32&&f[9]>=-1&&f[9]<=32&&f[10]>=0&&f[10]<=3);
 std::array<std::uint32_t,32> data,alt,history;for(std::size_t i=0;i<32;++i){data[i]=std::uint32_t(f[8])+std::uint32_t(i);alt[i]=~data[i];history[i]=data[i];}
 int house=0,actor=0,type=0,active=0,registered=0,index=f[3],capacity=f[4],historyCount=f[9];auto total=std::uint32_t(f[7]);auto flag=std::uint8_t(f[1]),hidden=std::uint8_t(f[2]),on=std::uint8_t(f[11]);std::span<std::uint32_t> slots=data;bool swapped=false,mutated=false;const int counterId=f[0]<2?4:3;
 const auto event=[&](int k,std::uint32_t a=0,std::uint32_t b=0,std::uint32_t c=0,std::uint32_t d=0){std::cout<<k<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<' ';};
 const auto id=[&](const void* p){if(p==&house)return 1;if(p==&actor)return 2;if(p==&active)return 3;if(p==&registered)return 4;throw std::invalid_argument("Foreign House accounting store");};
 const HouseInfantryStore store=[&](const void* p,std::int64_t off,std::uint32_t value){event(1,id(p),std::uint32_t(off),value);};
 HouseInfantryCounter counter{f[0]<2?static_cast<const void*>(&registered):&active,capacity,slots,{}};
 counter.resize8=[&](int size,std::uint32_t zero){require(zero==0&&size==index+10&&size<=32);event(6,size,0,std::uint32_t(f[5]));if(std::uint8_t(f[5])||f[10]==3){capacity=size;swapped=f[10]==3;slots=swapped?std::span<std::uint32_t>(alt):std::span<std::uint32_t>(data);event(9,counterId,8,size);event(9,counterId,4,swapped);}return std::uint32_t(f[5]);};
 HouseInfantryOwner h{&house,total,counter,counter,historyCount,history};
 HouseInfantryActor a{&actor,on,hidden,[&]{event(3);if(f[10]==1&&!mutated){flag=1;event(9,5,0x202,1);mutated=true;}return HouseInfantryType{flag,[&]{event(4,index);return index;}};},[&]{event(5);if(f[10]==2&&!mutated){index=(f[3]+1)%16;event(9,5,0x40,index);total=0xffffffff;event(9,1,0x234,total);mutated=true;}return 15u;}};
 std::uint32_t result=0;
 switch(f[0]){case 0:removeRegisteredHouseInfantry(h,a,[&]{event(2);},store);break;case 1:addRegisteredHouseInfantry(h,a,store);break;case 2:removeActiveHouseInfantry(h,a,store);break;case 3:addActiveHouseInfantry(h,a,store);break;default:result=changeHouseInfantryCounter(counter,index,f[0]==4,store);}
 std::cout<<"F "<<unsigned(on)<<' '<<total<<' '<<capacity<<' '<<swapped<<' '<<index<<' '<<unsigned(flag)<<' ';for(const auto* array:{&data,&alt,&history})for(auto v:*array)std::cout<<v<<' ';if(f[0]>=4)std::cout<<"R "<<result;std::cout<<'\n';
}
void guards(){
 int token=0,cap=0;std::array<std::uint32_t,1> data{};std::span<std::uint32_t> slots=data;HouseInfantryCounter c{&token,cap,slots,{}};
 const auto refused=[&](auto fn){bool failed=false;try{fn();}catch(const std::invalid_argument&){failed=true;}require(failed);};
 refused([&]{changeHouseInfantryCounter(c,-1,true);});refused([&]{changeHouseInfantryCounter(c,0,true);});refused([&]{changeHouseInfantryCounter(c,0x7fffffff,true);});
 cap=2;refused([&]{changeHouseInfantryCounter(c,1,true);});
 cap=0;c.resize8=[](auto,auto){return 0x100u;};require(changeHouseInfantryCounter(c,0,true)==0&&data[0]==0);
 c.resize8=[](auto,auto){return 1u;};refused([&]{changeHouseInfantryCounter(c,1,true);});
 HouseInfantryAccountingState s;withHouseInfantryAccounting(s,&token,[&](auto& h){require(changeHouseInfantryCounter(h.active5440,1,true)==1);});auto clone=s;clone.active5440[1]=9;require(s.active5440[1]==1);
 std::cout<<"House Infantry accounting guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
