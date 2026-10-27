// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/NearbyCellAdmission.hpp"
#include <cfenv>
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
template<class T>T take(std::istream& in){T v{};if(!(in>>v))throw std::invalid_argument("Missing Cell admission field");return v;}
int number(std::istream& in,int lo,int hi){int v=take<int>(in);if(v<lo||v>hi)throw std::invalid_argument("Cell admission field domain");return v;}
struct Cell {MapCellInput input;std::uint32_t occupation=0,elevated=0;int overlay=-1;};
NearbyAdmissionCell view(const Cell& c){return {c.input,c.occupation,c.elevated,c.overlay};}
void guards(){
 int checks=0;const auto check=[&](bool ok){++checks;if(!ok)throw std::runtime_error("Cell admission guard "+std::to_string(checks));};
 Cell c;NearbyAdmissionServices s;std::vector<std::uint32_t> speeds(18,0xbf800000);s.speedBits=speeds;
 auto admit=[&](int speed,int zone){return nearbyCellAdmits(view(c),speed,0,0,zone,0,-1,0,s);};
 check(admit(1,-1));bool refused=false;try{admit(1,0);}catch(const std::invalid_argument&){refused=true;}check(refused);
 check(admit(4,0));c.overlay=99;refused=false;try{admit(1,-1);}catch(const std::invalid_argument&){refused=true;}check(refused);c.overlay=-1;
 c.input.land=-1;refused=false;try{admit(1,-1);}catch(const std::invalid_argument&){refused=true;}check(refused);c.input.land=0;
 check(nearbyRectangleAdmits({},0,1,1,0,0,0,0,0,{}, {},s));
 MapPermissionShape shape{2,0,0,10,10};c.input.position={5,5};check(nearbyCellPermitted(c.input,1,shape));
 std::vector<MapCellInput*> slots(262144);MapAttributeLookup map{slots,&c.input,{},{}};
 refused=false;try{nearbyRectangleAdmits({},1,1,1,-1,0,-1,0,0,map,{},s);}catch(const std::invalid_argument&){refused=true;}check(refused);
 Cell split;refused=false;try{nearbyRectangleAdmits({},1,1,1,-1,0,-1,0,0,map,[&](auto&){return view(split);},s);}catch(const std::invalid_argument&){refused=true;}check(refused);
 c.input.flags=0x100;c.elevated=0;speeds[1]=0x7fc00001;check(admit(1,-1));c.input.flags=0;check(!admit(1,-1));
 c.occupation=0x100; speeds[1]=0x3f800000;check(admit(1,-1));
 c.input.land=1;check(nearbyCellAdmits(view(c),-1,0,0,-1,0,-1,0,s)); // legal combined speed-table alias
 std::cout<<checks<<" native Cell admission guard checks PASS\n";
}
int main(int argc,char** argv){try{
 if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
 if(argc!=1)return 2;
 const auto event=[](auto... v){((std::cout<<v<<' '),...);};
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);if(take<char>(in)!='A')return 2;
  const int mode=number(in,0,3),op=number(in,0,2);const int modes[]{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};std::fesetround(modes[mode]);
  MapInputPosition origin;origin.x=std::int16_t(number(in,-32768,32767));origin.y=std::int16_t(number(in,-32768,32767));
  const int width=take<int>(in),height=take<int>(in),speed=take<int>(in),zone=take<int>(in),movement=take<int>(in),level=take<int>(in);const auto alternate=take<std::uint32_t>(in);
  const auto byte=[&](){return std::uint8_t(number(in,0,255));};const auto disallow=byte(),low=byte(),middle=byte(),elevation=byte();
  MapPermissionShape shape;shape.dimension0=take<int>(in);shape.originX=take<int>(in);shape.originY=take<int>(in);shape.width=take<int>(in);shape.height=take<int>(in);
  const int zoneResult=take<int>(in),mutation=number(in,0,1),count=number(in,1,128);
  std::vector<Cell> cells(static_cast<std::size_t>(count));std::vector<MapCellInput*> slots(262144);
  for(int i=0;i<count;++i){auto& c=cells[std::size_t(i)];const int slot=number(in,-1,262143);c.input.position.x=std::int16_t(number(in,-32768,32767));c.input.position.y=std::int16_t(number(in,-32768,32767));
   c.input.level=std::int8_t(number(in,-128,127));c.input.slope=byte();c.input.flags=take<std::uint32_t>(in);c.input.land=take<int>(in);c.occupation=take<std::uint32_t>(in);c.elevated=take<std::uint32_t>(in);c.overlay=take<int>(in);
   if((slot==-1)!=(i==count-1))throw std::invalid_argument("Cell admission fallback identity");
   if(slot!=-1){if(slots[std::size_t(slot)])throw std::invalid_argument("Cell admission slot alias");slots[std::size_t(slot)]=&c.input;}
  }
  const int speedCount=number(in,1,4096);std::vector<std::uint32_t> speeds(static_cast<std::size_t>(speedCount));for(auto& b:speeds)b=take<std::uint32_t>(in);
  const int overlayCount=number(in,0,128);std::vector<OverlayTypeInputs> types(static_cast<std::size_t>(overlayCount));std::vector<const OverlayTypeInputs*> typeslots(static_cast<std::size_t>(overlayCount));
  for(int i=0;i<overlayCount;++i){const int present=number(in,0,1);types[std::size_t(i)].wall=byte();types[std::size_t(i)].crushable=byte();if(present)typeslots[std::size_t(i)]=&types[std::size_t(i)];}
  std::string tail;if(in>>tail)throw std::invalid_argument("Trailing Cell admission field");
  const auto id=[&](const MapCellInput& c){for(int i=0;i<count;++i)if(&cells[std::size_t(i)].input==&c)return i;throw std::invalid_argument("Unbound Cell admission identity");};
  MapAttributeLookup map{slots,&cells.back().input,{},[&](auto p){event('W',p.x,p.y);}};
  NearbyAdmissionServices services;services.overlays=typeslots;services.speedBits=speeds;
  services.zone=[&](const auto& p,int m,std::uint32_t alt){
   // Direct Cell calls and rectangle callbacks always forward the saved Cell.
   int n=-1;for(int i=0;i<count;++i)if(&cells[std::size_t(i)].input.position==&p)n=i;if(n<0)throw std::logic_error("Zone position copied");
   event('Z',n,p.x,p.y,m,alt,zoneResult);
   if(mutation){auto& c=cells[std::size_t(n)];c.input.level=-2;c.input.flags^=0x100;c.occupation^=0xe0;c.elevated^=0x1f;c.input.land=1;c.overlay=3;c.input.position.x=std::bit_cast<std::int16_t>(std::uint16_t(unsigned(c.input.position.x)+1u));event('X',n);}
   return zoneResult;
  };
  services.trace=[&](char k,const auto& c,int a,int b,int d,int e,int f,int g,std::uint32_t h){if(k=='C')event(k,id(c),a,b,d,e,f,g,h);else event(k,a);};
  bool result=false;
  if(op==0)result=nearbyCellAdmits(view(cells.front()),speed,low,middle,zone,movement,level,alternate,services);
  else if(op==1){
   MapInputPosition queried;
   map.query=[&](auto p){queried=p;};
   result=nearbyRectangleAdmits(origin,width,height,speed,zone,movement,level,alternate,disallow,map,[&](const auto& input){event('L',queried.x,queried.y,id(input));return view(cells[std::size_t(id(input))]);},services);
  }else{event('P',0,int(elevation));result=nearbyCellPermitted(cells.front().input,elevation,shape);}
  event('R',result);event("state");for(const auto& c:cells)event(c.input.position.x,c.input.position.y,int(c.input.level),c.input.flags,c.input.land,c.occupation,c.elevated,c.overlay);
  if(std::fegetround()!=modes[mode])throw std::runtime_error("Cell admission caller FP mode changed");std::cout<<'\n';
 }return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
