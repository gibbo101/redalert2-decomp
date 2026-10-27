// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/NearbyLocationMap.hpp"
#include "assets/PreparedData.hpp"
#include "render/Lighting.hpp"
#include <cfenv>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
template<class T>T take(std::istream& in){T v{};if(!(in>>v))throw std::invalid_argument("Missing nearby map input");return v;}
int number(std::istream& in,int lo,int hi){const int n=take<int>(in);if(n<lo||n>hi)throw std::invalid_argument("Nearby map field domain");return n;}
struct Cell {MapCellInput input;std::uint32_t occupation=0,elevated=0;int overlay=-1;};
NearbyAdmissionCell view(const Cell& c){return {c.input,c.occupation,c.elevated,c.overlay};}
void guards(){
 int checks=0;const auto check=[&](bool ok){++checks;if(!ok)throw std::runtime_error("Nearby map guard "+std::to_string(checks));};
 std::vector<MapCellInput*> slots(262144);Cell cell;MapPermissionShape shape{2,0,0,100,100};int dimension1=0,frame=1;NearbyLocationPoint empty{},source{50,50};std::vector<std::uint32_t> speeds(108,0x3f800000);NearbyAdmissionServices admission;admission.speedBits=speeds;
 int queries=0;MapAttributeLookup map{slots,&cell.input,[&](auto){++queries;},{}};
 std::function<NearbyAdmissionCell(const MapCellInput&)> bind=[&](auto& c){if(&c!=&cell.input)throw std::logic_error("Unbound guard Cell");return view(cell);};
 const NearbyLocationMapView world{map,shape,dimension1,frame,empty,bind,admission};check(queries==0);NearbyLocationOptions options;
 auto run=[&]{return nearbyLocationOnMap(source,empty,options,world,{});};
 check(run()==source);check(cell.input.position!=MapInputPosition{}&&queries>0);
 // Permission consumes a pointer; no extra lookup between L and B/b.
 int before=0;bool pointerPermission=false;nearbyLocationOnMap(source,empty,options,world,{},[&](char k,auto,const auto* c,int){if(k=='L')before=queries;if(k=='B')pointerPermission=c==&cell.input&&queries==before;});check(pointerPermission);
 options.requireBurrowable=1;bool refused=false;try{run();}catch(const std::invalid_argument& e){refused=std::string(e.what())=="Nearby burrowability unjoined";}check(refused);options.requireBurrowable=0;
 options.zone=0;refused=false;try{run();}catch(const std::invalid_argument& e){refused=std::string(e.what())=="Nearby admission zone resolver unjoined";}check(refused);options.zone=-1;
 Cell split;bind=[&](auto&){return view(split);};refused=false;try{run();}catch(const std::invalid_argument&){refused=true;}check(refused);bind=[&](auto&){return view(cell);};
 frame=-1;refused=false;try{run();}catch(const std::invalid_argument& e){refused=std::string(e.what())=="Nearby location negative frame remainder";}check(refused);frame=1;
 const int old=std::fegetround();std::fesetround(FE_UPWARD);bool exactFault=false;admission.trace=[](auto,const auto&,int,int,int,int,int,int,std::uint32_t){throw std::runtime_error("unrelated");};try{run();}catch(const std::runtime_error& e){exactFault=std::string(e.what())=="unrelated";}check(exactFault&&std::fegetround()==FE_UPWARD);std::fesetround(old);
 std::cout<<checks<<" native nearby map guard checks PASS\n";
}
int main(int argc,char** argv){try{
 if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
 if(argc!=2)throw std::invalid_argument("Expected private render data");std::ifstream input(argv[1],std::ios::binary);Bytes raw(69944);
 if(!input.read(reinterpret_cast<char*>(raw.data()),std::streamsize(raw.size()))||input.peek()!=std::char_traits<char>::eof())throw std::invalid_argument("Render data extent");const auto render=readRenderData(Data(std::move(raw)),PatchedEngineSha);
 const auto event=[](auto... v){((std::cout<<v<<' '),...);};std::string line;
 while(std::getline(std::cin,line)){
  std::istringstream in(line);if(take<char>(in)!='M')return 2;const int mode=number(in,0,3);const int modes[]{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};std::fesetround(modes[mode]);
  const auto point=[&](){const int x=number(in,-32768,32767),y=number(in,-32768,32767);return NearbyLocationPoint{std::int16_t(x),std::int16_t(y)};};const auto source=point(),close=point(),empty=point();
  MapPermissionShape shape;shape.dimension0=take<int>(in);int dimension1=take<int>(in),frame=take<int>(in);NearbyLocationOptions options;options.speedType=take<int>(in);options.zone=take<int>(in);options.movementZone=take<int>(in);options.alternate=take<std::uint32_t>(in);options.width=take<int>(in);options.height=take<int>(in);
  const auto byte=[&](){return std::uint8_t(number(in,0,255));};options.disallowOverlay=byte();options.matchLevel=byte();options.allowBridge=byte();options.skipNorthWest=byte();shape.originX=take<int>(in);shape.originY=take<int>(in);shape.width=take<int>(in);shape.height=take<int>(in);
  const int count=number(in,1,128);std::vector<Cell> cells(static_cast<std::size_t>(count));std::vector<MapCellInput*> slots(262144);
  for(int i=0;i<count;++i){auto& c=cells[std::size_t(i)];const int slot=number(in,-1,262143);c.input.position.x=std::int16_t(number(in,-32768,32767));c.input.position.y=std::int16_t(number(in,-32768,32767));c.input.level=std::int8_t(number(in,-128,127));c.input.slope=byte();c.input.flags=take<std::uint32_t>(in);c.input.land=take<int>(in);c.occupation=take<std::uint32_t>(in);c.elevated=take<std::uint32_t>(in);c.overlay=take<int>(in);
   if((slot==-1)!=(i==count-1))throw std::invalid_argument("Nearby map fallback identity");if(slot!=-1){if(slots[std::size_t(slot)])throw std::invalid_argument("Nearby map slot alias");slots[std::size_t(slot)]=&c.input;}}
  const int speedCount=number(in,1,4096);std::vector<std::uint32_t> speeds(static_cast<std::size_t>(speedCount));for(auto& b:speeds)b=take<std::uint32_t>(in);
  const int overlayCount=number(in,0,128);std::vector<OverlayTypeInputs> types(static_cast<std::size_t>(overlayCount));std::vector<const OverlayTypeInputs*> typeslots(static_cast<std::size_t>(overlayCount));
  for(int i=0;i<overlayCount;++i){const int present=number(in,0,1);types[std::size_t(i)].wall=byte();types[std::size_t(i)].crushable=byte();if(present)typeslots[std::size_t(i)]=&types[std::size_t(i)];}
  std::string tail;if(in>>tail)throw std::invalid_argument("Trailing nearby map input");
  const auto id=[&](const MapCellInput& c){for(int i=0;i<count;++i)if(&cells[std::size_t(i)].input==&c)return i;throw std::logic_error("Missing nearby map identity");};
  MapInputPosition queried;bool projecting=false;MapAttributeLookup map{slots,&cells.back().input,[&](auto p){queried=p;if(projecting)event('G',p.x,p.y);},[&](auto p){event('W',p.x,p.y);}};
  std::function<NearbyAdmissionCell(const MapCellInput&)> bind=[&](auto& c){event('J',queried.x,queried.y,id(c));return view(cells[std::size_t(id(c))]);};
  NearbyAdmissionServices admission;admission.speedBits=speeds;admission.overlays=typeslots;admission.trace=[&](char k,const auto& c,int a,int b,int d,int e,int f,int g,std::uint32_t h){if(k=='C')event(k,id(c),a,b,d,e,f,g,h);else event(k,a);};
  const NearbyLocationMapView world{map,shape,dimension1,frame,empty,bind,admission};
  const auto result=nearbyLocationOnMap(source,close,options,world,[&](double n){const auto r=tableSqrt(render,std::abs(n));event('D',int(n),std::bit_cast<std::uint64_t>(r));return r;},[&](char k,auto p,const auto* c,int n){
   if(k=='L')event(k,p.x,p.y,id(*c));else if(k=='B')event(k,id(*c),p.x,p.y,n);else if(k=='b')event(k,id(*c),n);else if(k=='t')event(k,n);else{event(k,p.x,p.y);if(k=='P')projecting=true;if(k=='p')projecting=false;}
  });
  event('R',result.x,result.y);event("state");for(const auto& c:cells)event(c.input.position.x,c.input.position.y,int(c.input.level),c.input.flags,c.input.land,c.occupation,c.elevated,c.overlay);
  if(std::fegetround()!=modes[mode])throw std::runtime_error("Nearby map caller FP mode changed");std::cout<<'\n';
 }return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
