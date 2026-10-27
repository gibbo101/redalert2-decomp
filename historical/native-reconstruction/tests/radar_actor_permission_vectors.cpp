// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/RadarActorPermission.hpp"
#include "render/UnitTypeVisibility.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool b){if(!b)throw std::invalid_argument("Permission fixture domain");}
void run(std::istream& in){
 char tag;int kind,aa6,aa7,flag325,discovered,houseMode,owner,human,control,alliance,mode,session,mission,height,v277,e289,p1,p2,secondary,eligible,width,heightDim,b5bd,b5b7,status,mutation;std::uint64_t bits;
 need(bool(in>>tag>>kind>>aa6>>aa7>>flag325>>discovered>>bits>>houseMode>>owner>>human>>control>>alliance>>mode>>session>>mission>>height>>v277>>e289>>p1>>p2>>secondary>>eligible>>width>>heightDim>>b5bd>>b5b7>>status>>mutation)&&tag=='Q');
 need(kind>=0&&kind<=1&&owner>=0&&owner<=1&&mutation>=0&&mutation<=5);std::string extra;need(!(in>>extra));
 for(auto n:{aa6,aa7,flag325,discovered,human,control,v277,e289,b5bd,b5b7})need(n>=0&&n<=255);
 for(auto n:{p1,p2,secondary,eligible})need(n>=0&&n<=511);
 std::uint8_t fAA6=std::uint8_t(aa6),fAA7=std::uint8_t(aa7),f325=std::uint8_t(flag325),f373=std::uint8_t(discovered),f277=std::uint8_t(v277),f289=std::uint8_t(e289),f5bd=std::uint8_t(b5bd),f5b7=std::uint8_t(b5b7);
 double veterancy=std::bit_cast<double>(bits);Coord coord{-513,1025,208};int type=0,calls=0,primaryCalls=0;int houses[2]{};const void* current=&houses[0];std::uint32_t sessionFlags=std::uint32_t(session);
 const auto mutate=[&](char stage){
  if(mutation==1&&stage=='P'){coord={2147483600,-2147483600,312};std::cout<<"M 1 ";}
  if(mutation==2&&stage=='F'){owner=0;std::cout<<"M 2 ";}
  if(mutation==3&&stage=='P'){f5b7=255;std::cout<<"M 3 ";}
  if(mutation==4&&stage=='H'){type=1;std::cout<<"M 4 ";}
  if(mutation==5&&stage=='T'&&calls==1){veterancy=2.;std::cout<<"M 5 ";}
 };
 RadarPermissionServices s;
 s.type80=[&]{if(!kind){++calls;std::cout<<"T "<<type<<' ';mutate('T');}return RadarPermissionType{fAA6,fAA7,f277,f289};};
 s.owner1B4=[&]()->const void*{return &houses[unsigned(owner)];};
 s.local4F52B0=[&](auto p){const int at=p==&houses[0]?0:1;std::cout<<"L "<<at<<' ';return unsigned(unitOwnerTypeVisible(houseMode,std::uint8_t(human),std::uint8_t(control),at==0));};
 s.height1B0=[&]{std::cout<<"H "<<height<<' ';mutate('H');return height;};
 s.primary568140=[&](auto p){const int value=primaryCalls++?p2:p1;std::cout<<"P "<<p.x<<' '<<p.y<<' '<<p.z<<' '<<value<<' ';mutate('P');return unsigned(value);};
 s.secondary5683C0=[&](auto p){std::cout<<"S "<<p.x<<' '<<p.y<<' '<<p.z<<' '<<secondary<<' ';return unsigned(secondary);};
 s.eligible2FC=[&]{std::cout<<"F "<<eligible<<' ';mutate('F');return unsigned(eligible);};
 s.allied4E5540=[&](auto a,auto b){need(a==current);const int at=b==current?0:1;std::cout<<"B "<<at<<' ';return unitOwnerAlliedToCurrent(true,at==0,0,at,std::uint32_t(alliance));};
 s.foundationHeight458940=[&](auto arg){need(!arg);const int value=fillAdd(heightDim,type);std::cout<<"Y "<<type<<" 0 "<<value<<' ';mutate('H');return value;};
 s.foundationWidth458930=[&]{const int value=fillAdd(width,type);std::cout<<"X "<<type<<' '<<value<<' ';return value;};
 s.probe=[](char c){std::cout<<c<<' ';};s.statusStore=[](auto v){std::cout<<"W "<<std::uint32_t(v)<<' ';};
 RadarPermissionActor a{coord,f325,f373,veterancy,mission,f5bd,f5b7};RadarPermissionWorld w{mode,sessionFlags,current};
 const auto result=kind?buildingRadarPermission(status,a,w,s):infantryRadarPermission(status,a,w,s);
 std::cout<<"R "<<result<<' '<<std::uint32_t(status)<<'\n';
}
void guards(){
 Coord coord;std::uint8_t zero=0,one=1;double vet=0;int mission=0,mode=0,status=0x12345;std::uint32_t session=0;const void* current=nullptr;
 RadarPermissionActor a{coord,zero,zero,vet,mission,zero,zero};RadarPermissionServices s;bool refused=false;
 try{infantryRadarPermission(status,a,{mode,session,current},s);}catch(const std::invalid_argument&){refused=true;}need(refused&&status==0x12345);
 s.type80=[&]{return RadarPermissionType{one,zero,zero,zero};};need(!infantryRadarPermission(status,a,{mode,session,current},s)&&status==0x12345);
 need(!buildingRadarPermission(status,a,{mode,session,current},s)&&status==0x12345);
 std::cout<<"Permission guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}}
 catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}return 0;}
