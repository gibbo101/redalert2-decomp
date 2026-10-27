// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/RadarActorPlacement.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool v){if(!v)throw std::invalid_argument("Placement fixture domain");}
void run(std::istream& in){
 char tag;int kind,arg,discovery,loading,permission,status,allowed,reg,x,y,px,py,flags,secondary,owner,start,remaining,frame,divisor,mutation,visible;
 need(bool(in>>tag>>kind>>arg>>discovery>>loading>>permission>>status>>allowed>>reg>>x>>y>>px>>py>>flags>>secondary>>owner>>start>>remaining>>frame>>divisor>>mutation>>visible)&&tag=='L');
 need((kind==6||kind==15)&&arg>=0&&arg<=511&&discovery>=0&&discovery<=255&&permission>=0&&permission<=511&&allowed>=0&&allowed<=511&&reg>=0&&reg<=255&&flags>=0&&flags<=255&&secondary>=-128&&secondary<=127&&owner>=0&&owner<=1&&divisor!=0&&mutation>=0&&mutation<=6&&visible>=0&&visible<=511);
 std::string extra;need(!(in>>extra));Coord coords{-513,1025,208};std::uint8_t discovered=std::uint8_t(discovery),registered=std::uint8_t(reg),actorFlags=std::uint8_t(flags);std::int8_t sec=std::int8_t(secondary);
 int houses[2]{},cell;const void* current=&houses[0];const void* actualOwner=&houses[unsigned(owner)];
 RadarActorPlacementServices s;
 s.coordinates48=[&]{std::cout<<"A "<<coords.x<<' '<<coords.y<<' '<<coords.z<<' ';return coords;};
 s.discovery568140=[&](auto p){std::cout<<"V "<<p.x<<' '<<p.y<<' '<<p.z<<' '<<visible<<' ';return unsigned(visible);};
 s.kind2C=[&]{std::cout<<"K "<<kind<<' ';return kind;};
 s.project631BA0=[&](auto p,auto clamp){int a=px,b=py;if(clamp){a=std::min(std::max(a,0),15);b=std::min(std::max(b,0),11);}std::cout<<"P "<<unsigned(clamp)<<' '<<p.x<<' '<<p.y<<' '<<p.z<<' '<<a<<' '<<b<<' ';return RadarShapePoint{a,b};};
 s.permission2F8=[&](auto& v){need(v==0);v=status;std::cout<<"E "<<status<<' '<<permission<<' ';if(mutation==1){coords={-65537,65535,312};std::cout<<"M 1 ";}return unsigned(permission);};
 s.rectangle78=[&]{std::cout<<"G ";if(mutation==2){registered=0;std::cout<<"M 2 ";}return RefreshRect{0,0,16,12};};
 s.radarEvent63B5B0=[](auto mode,auto point){need(mode==5);std::cout<<"B "<<point<<' ';};
 s.cell1AC=[&](auto n)->const void*{need(n==1);std::cout<<"C 1 ";return &cell;};
 s.permitted55A740=[&](auto p){need(p==&cell);std::cout<<"U "<<allowed<<' ';return unsigned(allowed);};
 s.insert420=[&]{std::cout<<"I "<<x<<' '<<y<<' '<<unsigned(registered)<<' ';registered=1;
  if(mutation==3){actualOwner=&houses[1];std::cout<<"M 3 ";}if(mutation==6){start=-1;remaining=6;std::cout<<"M 6 ";}};
 s.remove424=[&]{std::cout<<"R "<<x<<' '<<y<<' '<<unsigned(registered)<<' ';if(mutation!=4)registered=0;};
 s.dirty428=[&]{std::cout<<"D "<<x<<' '<<y<<' '<<unsigned(registered)<<' ';};
 s.flashDivisor90=[&]{return divisor;};
 s.store=[&](auto off,auto n,auto v){std::cout<<"W "<<off<<' '<<n<<' '<<v<<' ';if(off==0x1a0&&mutation==5){registered=255;std::cout<<"M 5 ";}};
 placeActorRadar(unsigned(arg),{coords,discovered,{x,y,registered},actorFlags,sec,[&]{return actualOwner;},start,remaining},{loading,frame,current},s);
 std::cout<<"F "<<x<<' '<<y<<' '<<unsigned(registered)<<' '<<unsigned(discovered)<<' '<<(actualOwner!=current)<<'\n';
}
void guards(){
 Coord coords;std::uint8_t discovery=1,reg=7,flags=0;std::int8_t secondary=-1;int x=0,y=0,loading=0,frame=0,start=-1,remaining=0;const void* house=nullptr;
 RadarActorPlacementServices s;bool refused=false;
 try{placeActorRadar(0,{coords,discovery,{x,y,reg},flags,secondary,[&]{return house;},start,remaining},{loading,frame,house},s);}catch(const std::invalid_argument&){refused=true;}
 need(refused&&reg==7);
 reg=0;remaining=6;bool divisorRead=false;
 s.kind2C=[] {return 6;};s.permission2F8=[](auto&){return 0u;};s.rectangle78=[] {return RefreshRect{0,0,16,12};};
 s.flashDivisor90=[&]{divisorRead=true;return 0;};refused=false;
 try{placeActorRadar(0,{coords,discovery,{x,y,reg},flags,secondary,[&]{return house;},start,remaining},{loading,frame,house},s);}
 catch(const std::invalid_argument&){refused=true;}need(refused&&divisorRead);
 // Offscreen status0/permission0 needs no cell or projection service; a missing
 // entered visibility child must refuse rather than becoming a silent no-op.
 s.permission2F8=[](auto& status){status=1;return 1u;};divisorRead=false;refused=false;
 try{placeActorRadar(0,{coords,discovery,{x,y,reg},flags,secondary,[&]{return house;},start,remaining},{loading,frame,house},s);}
 catch(const std::invalid_argument&){refused=true;}need(refused&&!divisorRead);
 std::cout<<"Placement guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}}
 catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}return 0;}
