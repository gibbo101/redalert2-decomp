// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/HouseCountryRegistration.hpp"
#include <array>
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("Country registration fixture differs");}
void run(std::istream& in){
 std::array<int,8> f{};for(auto& x:f)require(bool(in>>x));std::string tail;require(!(in>>tail));
 require(f[0]>=0&&f[0]<=6&&f[1]>=0&&f[2]>=0&&f[2]<=255&&f[5]>=0&&f[5]<=1&&f[6]>=-1&&f[6]<=6&&f[7]>=-1&&f[7]<8);
 HouseCountryType record,prior[3];std::array<HouseCountryType*,8> slots{},alt{};for(int i=0;i<8;++i)slots[i]=&prior[i%3];if(f[7]>=0)slots[f[7]]=&record;
 const auto pid=[&](const void* p){if(!p)return 0;if(p==&record)return 1;for(int i=0;i<3;++i)if(p==&prior[i])return i+2;throw std::invalid_argument("Foreign country identity");};
 const auto event=[&](int k,std::uint32_t a=0,std::uint32_t b=0,std::uint32_t c=0,std::uint32_t d=0){std::cout<<k<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<' ';};
 int count=f[0],cap=f[1],increment=f[3],registry=0;std::uint8_t allocated=f[2];std::span<HouseCountryType*> backing{slots};
 HouseCountryRegistration r{&registry,count,cap,allocated,increment,backing};
 r.resize=[&](int size,std::uint32_t zero){require(!zero);event(2,std::uint32_t(size),std::uint32_t(f[4]),f[5],std::uint32_t(f[6]));if(f[5]){std::copy(backing.begin(),backing.end(),alt.begin());backing=alt;}if(f[6]>=0)count=f[6];if(std::uint8_t(f[4]))cap=size;return std::uint32_t(f[4]);};
 r.store=[&](const void* p,std::int64_t off,std::uint32_t v,const void* q){event(1,p==&record?1:2,std::uint32_t(off),v,pid(q));};
 registerHouseCountryType(record,r);
 std::cout<<"F "<<std::uint32_t(record.countryB8)<<' '<<std::uint32_t(record.indexB4)<<' '<<std::uint32_t(count)<<' '<<std::uint32_t(cap)<<' '<<int(backing.data()==alt.data());for(auto p:backing)std::cout<<' '<<pid(p);std::cout<<'\n';
}
void guards(){
 HouseCountryType t;std::array<HouseCountryType*,1> b{};std::span<HouseCountryType*> slots{b};int id=0,n=0,cap=0,inc=1;std::uint8_t allocated=1;HouseCountryRegistration r{&id,n,cap,allocated,inc,slots};bool refused=false;try{registerHouseCountryType(t,r);}catch(const std::invalid_argument&){refused=true;}require(refused&&n==0);n=-1;refused=false;try{registerHouseCountryType(t,r);}catch(const std::invalid_argument&){refused=true;}require(refused);std::cout<<"Country registration guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
