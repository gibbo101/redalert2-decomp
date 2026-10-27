// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/SpriteConverterSelection.hpp"
#include <array>
#include <iostream>
#include <sstream>
using namespace ra2;
int main(){try{std::string line;while(std::getline(std::cin,line)){
 std::istringstream in(line);int over,own,pred,first,second,alt,mutation,nullConverter;
 if(!(in>>over>>own>>pred>>first>>second>>alt>>mutation>>nullConverter))return 2;
 if(over<0||over>1||pred<0||pred>255||first<0||first>2||second<0||second>2||mutation<0||mutation>4||nullConverter<0||nullConverter>1)return 2;
 std::array<int,24> ids{};auto id=[&](int n)->const void*{return n?&ids.at(n):nullptr;};auto n=[&](const void* p){if(!p)return 0;for(int i=1;i<24;++i)if(p==id(i))return i;throw std::invalid_argument("Foreign selection identity");};
 auto event=[&](int kind,int key,int value){std::cout<<kind<<' '<<key<<' '<<value<<' ';};
 int owner=1,calls=0,global=4;std::array<int,3> indexes{own,alt,2};int table=over?3:0;
 SpriteConverterSelectionServices s;
 s.type80=[&]{event(2,0x80,1);if(mutation==1){owner=2;table=3;}return id(7);};
 s.owner1b4=[&]{event(1,0x1b4,owner);return id(owner);};
 s.schemesB8c=[&](auto p){if(p!=id(7))throw std::invalid_argument("Type");event(1,0xb8c,table);return id(table);};
 s.index15f40=[&](auto p){int i=n(p);if(i<1||i>3)throw std::invalid_argument("House");event(1,0x15f40,indexes.at(i-1));return indexes.at(i-1);};
 s.typeBacking4=[&](auto p){if(p!=id(3))throw std::invalid_argument("Type table");event(1,4,5);return id(5);};
 s.currentHouseA35db4=[&]{event(1,0xa35db4,2);return id(2);};
 s.ownerPredicate3d4=[&](auto p){if(p!=id(2))throw std::invalid_argument("Current House");event(2,0x3d4,pred);if(mutation==2){indexes[0]=2;global=6;}return std::uint8_t(pred);};
 s.houseCC=[&](int a){if(a!=1)throw std::invalid_argument("CC ABI");int h=calls++?second:first;event(2,0xcc,h);if(mutation==3&&calls==1){indexes[0]=2;global=6;}if(mutation==4&&calls==2){indexes[1]=0;global=6;}return id(h);};
 s.globalBackingAB6EFC=[&]{event(1,0xab6efc,global);return id(global);};
 s.schemeAtOffset=[&](auto p,std::uint32_t offset){auto i=offset/4;int b=n(p);if(i>=3||(b!=4&&b!=5&&b!=6))throw std::invalid_argument("Scheme table domain");int scheme=8+(b-4)*3+int(i);event(1,b*100+int(i),scheme);return id(scheme);};
 s.converter30c=[&](auto p){int scheme=n(p);if(scheme<8||scheme>16)throw std::invalid_argument("Scheme");int result=nullConverter?0:scheme+7;event(1,0x30c,result);return id(result);};
 const auto result=selectSpriteConverter(s);std::cout<<"F "<<n(result)<<' '<<calls<<' '<<owner<<' '<<indexes[0]<<' '<<indexes[1]<<' '<<global<<'\n';
 }}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
