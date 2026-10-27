// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/AdvanceTerminalWorld.hpp"
#include <bit>
#include <cfenv>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
using namespace ra2;
template<class T> T take(std::istream& in){long long n;if(!(in>>n)||n<std::numeric_limits<T>::min()||n>std::numeric_limits<T>::max())throw std::invalid_argument("Terminal integer outside domain");return T(n);}
int bounded(std::istream& in,int lo,int hi){const int n=take<int>(in);if(n<lo||n>hi)throw std::invalid_argument("Terminal input outside domain");return n;}
int guards(){
    UnitDestinationState actor;GroundDriveProcessState drive;UnitDiscoveryActor mission;
    std::uint32_t global=0,refs=1;std::uint8_t map=1,f76=0,f7a=0;
    UnitDestinationView v{actor,drive,mission,global,refs};AdvanceTerminalFlags flags{map,f76,f7a};
    drive.movement.track=-1;drive.movement.index=0;
    AdvanceTerminalServices s;s.notify174=[](int){};s.postCell490=[]{return 0;};
    int checks=0;const auto refusal=[&](auto f){try{f();}catch(const UnsupportedAdvanceTerminal&){++checks;return;}throw std::logic_error("Missing terminal refusal");};
    refusal([&]{finishOrdinaryAdvanceTerminal(v,flags,0,17,s);});
    drive.movement.track=1;refusal([&]{finishOrdinaryAdvanceTerminal(v,flags,104,17,s);});drive.movement.track=-1;
    actor.target494=&actor;refusal([&]{finishOrdinaryAdvanceTerminal(v,flags,104,17,s);});
    s.targetCoordinates=[](const void*){return Coord{};};s.actorCell=[]{return std::pair<std::int16_t,std::int16_t>{0,0};};
    refusal([&]{finishOrdinaryAdvanceTerminal(v,flags,104,17,s);});
    s.actorCoordinates=[]{return Coord{};};mission.mission98=2;drive.route.fill(7);
    refusal([&]{finishOrdinaryAdvanceTerminal(v,flags,104,17,s);});
    if(actor.target494||drive.route[0]!=-1||drive.route[23]!=7)throw std::logic_error("Refusal lost committed prefix or queue tail");++checks;
    s.notify174=[&](int){map=0;};if(!finishOrdinaryAdvanceTerminal(v,flags,104,17,s))throw std::logic_error("Late flags not read");++checks;
    map=1;s.notify174=[](int){};s.postCell490=[&]{map=0;return 0;};drive.movement.accumulator=91;
    if(finishOrdinaryAdvanceTerminal(v,flags,104,17,s)||drive.movement.accumulator!=91)throw std::logic_error("Late off-map residual suppression lost");++checks;
    map=1;s.postCell490=[&]{drive.movement.track=2;return 0;};refusal([&]{finishOrdinaryAdvanceTerminal(v,flags,104,17,s);});
    if(drive.movement.accumulator!=17)throw std::logic_error("Resumed track prefix lost");++checks;
    std::cout<<checks<<" terminal order/refusal/borrowed-state checks PASS\n";return 0;
}
int main(int argc,char** argv)try{
    if(argc==2&&std::string(argv[1])=="--guards")return guards();
    if(argc!=1)throw std::invalid_argument("Terminal runner takes stdin or --guards");
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char tag;if(!(in>>tag)||tag!='T')throw std::invalid_argument("Missing terminal tag");
        const int target=bounded(in,0,1);UnitDestinationState actor;actor.field490=take<int>(in);
        const auto registry=std::int8_t(bounded(in,-128,127));UnitDiscoveryActor mission;mission.mission98=bounded(in,-1,31);mission.queuedA0=bounded(in,-1,31);
        const int divisor=bounded(in,1,2147483647),residual=take<int>(in);GroundDriveProcessState drive;drive.movement.track=-1;drive.movement.index=0;
        drive.movement.accumulator=take<int>(in);drive.movement.driving=bounded(in,0,1);
        const auto missionReturn=take<std::uint8_t>(in),postReturn=take<std::uint8_t>(in);const int height=take<int>(in),fp=bounded(in,0,3);
        std::array<std::uint8_t,3> flags;for(auto& n:flags)n=take<std::uint8_t>(in);
        std::array<int,3> notify,post;for(auto* p:{&notify,&post}){for(auto& n:*p)n=bounded(in,-1,255);if((*p)[0]<0&&*p!=std::array<int,3>{-1,-1,-1})throw std::invalid_argument("Malformed effect");if((*p)[0]>=0&&((*p)[1]<0||(*p)[2]<0))throw std::invalid_argument("Malformed effect");}
        const auto coord=[&]{const int x=take<int>(in),y=take<int>(in),z=take<int>(in);return Coord{x,y,z};};
        drive.movement.actor.position=coord();drive.movement.head=coord();drive.destination=coord();
        const auto px=take<std::int16_t>(in),py=take<std::int16_t>(in);std::array<TerrainCellPoint,128> pool;pool.fill({px,py});
        MapCellInput cell;cell.position.x=take<std::int16_t>(in);cell.position.y=take<std::int16_t>(in);cell.level=take<std::int8_t>(in);cell.slope=std::uint8_t(bounded(in,0,20));
        for(auto& n:drive.route)n=take<int>(in);std::string extra;if(in>>extra)throw std::invalid_argument("Extra terminal input");
        actor.target494=target?&cell:nullptr;std::uint32_t global=0,refs=1;
        MapFloorHeightState floor;floor.planes[0].x=1.;std::array<MapCellInput*,1> targets{&cell};
        UnitDestinationView unit{actor,drive,mission,global,refs};AdvanceTerminalFlags live{flags[0],flags[1],flags[2]};
        AdvanceTerminalWorld world{unit,live,registry,pool,targets,floor,height};
        const auto event=[](auto... n){((std::cout<<n<<' '),...);};
        const auto effect=[&](const auto& values){if(values[0]>=0){for(int i=0;i<3;++i)flags[i]=std::uint8_t(values[i]);event("effect",values[0],values[1],values[2]);}};
        AdvanceTerminalServices s;s.notify174=[&](int n){event('N',n);effect(notify);};
        s.mission414=[&](int a,int b){event('B',a,b,int(missionReturn));return missionReturn;};
        s.postCell490=[&]{event('P',int(postReturn));effect(post);return postReturn;};
        s.missionQuery=[&](int n){event('M',n);};s.store=[&](char c,int off,int width,std::uint32_t n){event(c,off,width,n);};
        const int modes[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};if(std::fesetround(modes[fp]))throw std::runtime_error("Cannot set FP mode");
        const bool result=finishAdvanceTerminalOnMap(world,divisor,residual,s,[&](char k,int a,int b,int c){if(k=='U')event(k);else if(k=='Q')event(k,a);else event(k,a,b,c);});
        event("return",int(result));const auto& m=drive.movement;
        event("state",drive.destination.x,drive.destination.y,drive.destination.z,m.head.x,m.head.y,m.head.z,m.accumulator,int(m.driving),actor.field490,int(actor.target494!=nullptr));
        for(auto q:drive.route)event(q);event(int(flags[1]),int(flags[2]),int(flags[0]));
        event("floor",int(floor.flags),std::bit_cast<std::uint64_t>(floor.height),std::bit_cast<std::uint64_t>(floor.scale));
        for(const auto& p:floor.planes)for(double n:{p.x,p.y,p.offset,p.limit,p.add})event(std::bit_cast<std::uint64_t>(n));
        if(std::fegetround()!=modes[fp])throw std::runtime_error("Terminal changed caller FP mode");std::cout<<'\n';
    }return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
