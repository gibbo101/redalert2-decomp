// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/GroundDriveIdleTarget.hpp"
#include "assets/MapCoordinateCell.hpp"
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
template<class T>T take(std::istream& in){T v{};if(!(in>>v))throw std::invalid_argument("Missing destination input");return v;}
int number(std::istream& in,int lo,int hi){auto v=take<int>(in);if(v<lo||v>hi)throw std::invalid_argument("Destination input domain");return v;}
void guards(){
    UnitDestinationState a;GroundDriveProcessState d;UnitDiscoveryActor m;
    std::uint32_t global=7,refs=3;UnitDestinationView v{a,d,m,global,refs};
    UnitDestinationProfile profile;UnitDestinationInputs input;
    GroundDriveIdleTargetServices s;int target=1,queries=0;
    int checks=0;const auto check=[&](bool ok){++checks;if(!ok)throw std::runtime_error("Idle target guard differs");};
    const auto refused=[&]{try{processOrdinaryIdleTarget(v,profile,input,s);}catch(const std::invalid_argument&){return true;}return false;};
    d.movement.track=2;d.movement.driving=true;a.target494=&target;
    check(refused()&&a.target494==&target);
    d.movement.driving=false;check(refused()&&a.target494==&target);
    s.targetKind=[&](const void*){++queries;return 11;};check(refused()&&queries==1);
    s.targetWord=[&](const void*,int axis){++queries;return std::int16_t(axis?0:1);};
    queries=0;check(processOrdinaryIdleTarget(v,profile,input,s)==GroundDriveIdleTargetResult::continueProcess&&queries==2);
    d.movement.actor.position={256,0,999};a.vectorCount=-1;a.field490=73;
    check(refused()&&a.field490==0&&a.target494==nullptr); // refusal preserves the actual clear prefix
    a.target494=&target;s.mission414=[&](int x,int y){check(x==0&&y==1&&a.field490==0&&!a.target494);return std::uint8_t(255);};
    d.route.fill(7);check(processOrdinaryIdleTarget(v,profile,input,s)==GroundDriveIdleTargetResult::returnFalse&&d.route[0]==7);
    a.target494=nullptr;m.mission98=-1;m.queuedA0=5;d.destination=d.movement.actor.position;
    check(processOrdinaryIdleTarget(v,profile,input,s)==GroundDriveIdleTargetResult::continueProcess);
    m.mission98=5;d.destination.z=998;check(processOrdinaryIdleTarget(v,profile,input,s)==GroundDriveIdleTargetResult::continueProcess);
    d.destination=d.movement.actor.position;a.vectorCount=0;a.forced190=0;
    check(processOrdinaryIdleTarget(v,profile,input,s)==GroundDriveIdleTargetResult::returnFalse&&d.route[0]==7&&d.destination.z==999);
    a.target494=&target;profile.typeAf5=1;
    check(refused()&&a.target494==&target&&d.route[0]==7);
    profile.typeAf5=0;s.destination.targetId=[](const void*){return 1;};
    input.tick=100;input.temporaryPadding=-31;input.delay=5;input.stopScale=.3;
    d.percentage=1.;a.timer530={9,8,7};a.timer558={6,5,4};
    s.destination.trace=[&](char k,int off,int,std::int64_t){if(k=='a'&&off==0x558)check(a.timer558==std::array<int,3>{100,5,4}&&a.timer530==std::array<int,3>{9,8,7});};
    check(processOrdinaryIdleTarget(v,profile,input,s)==GroundDriveIdleTargetResult::returnFalse);
    check(d.route[0]==-1&&d.route[1]==7&&a.timer530==std::array<int,3>{100,-31,0}&&a.timer558==std::array<int,3>{100,-31,5});
    check(d.destination==Coord{}&&d.percentage==.3&&refs==3&&global==7&&d.movement.actor.position.z==999);
    std::cout<<checks<<" native idle target guard checks PASS\n";
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=1)throw std::invalid_argument("Destination vectors read stdin");
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);if(take<char>(in)!='I')return 2;
        const int initialTrack=take<int>(in),driving=number(in,0,1),effect=number(in,0,255);
        const int kinds[2]={number(in,1,11),number(in,1,11)};
        if((initialTrack!=-1&&driving)||(kinds[0]!=1&&kinds[0]!=11)||(kinds[1]!=1&&kinds[1]!=11))throw std::invalid_argument("Idle input domain");
        if(take<char>(in)!='Z')return 2;
        const auto byte=[&](){return std::uint8_t(number(in,0,255));};
        UnitDiscoveryActor mission;mission.mission98=number(in,-1,31);mission.queuedA0=number(in,-1,31);
        UnitDestinationState a;a.forced190=byte();a.suspended598=byte();
        GroundDriveProcessState d;d.movement.reached5a1=byte();a.field490=take<int>(in);
        d.movement.track=initialTrack;d.movement.index=9;d.movement.accumulator=33;d.movement.driving=driving;
        int initialTarget=number(in,0,2),buffer=number(in,0,1);a.vectorOwned=byte();a.vectorCapacity=take<int>(in);a.vectorCount=take<int>(in);
        UnitDestinationProfile p;p.powered=byte();p.field5c8=byte();p.field5c0=take<int>(in);p.field3fc=take<int>(in);p.timer58c=take<int>(in);p.timer594=take<int>(in);p.disabled1bc=byte();p.disabled1c0=byte();
        auto refs=take<std::uint32_t>(in),global=take<std::uint32_t>(in);int height=take<int>(in),delay=take<int>(in);
        const auto fallbackFlags=take<std::uint32_t>(in);const auto percentage=take<std::uint64_t>(in);d.percentage=std::bit_cast<double>(percentage);
        if(!std::isfinite(d.percentage)||!refs||refs>=0x7fffffffu)throw std::invalid_argument("Destination finite percentage/references domain");
        const auto coord=[&](){const auto x=take<int>(in),y=take<int>(in),z=take<int>(in);return Coord{x,y,z};};
        d.movement.actor.position=coord();d.destination=coord();d.movement.head=coord();
        for(auto& q:d.route)q=take<int>(in);
        MapCellInput cells[2],fallback;fallback.position={-7,5};fallback.flags=fallbackFlags;
        std::vector<MapCellInput*> slots(262144);
        for(auto& c:cells){
            const int x=number(in,-32768,32767),y=number(in,-32768,32767);
            c.position={std::int16_t(x),std::int16_t(y)};c.level=std::int8_t(number(in,-128,127));c.slope=std::uint8_t(number(in,0,20));c.flags=take<std::uint32_t>(in);
            const bool present=number(in,0,1);const int index=((y*256+128)/256)*512+(x*256+128)/256;
            if(present&&index>=0&&index<262144)slots[std::size_t(index)]=&c;
        }
        const auto target=[&](int id)->const void*{return id?&cells[id-1]:nullptr;};
        a.target494=target(initialTarget);int heap=0;a.vectorBuffer=buffer?&heap:nullptr;a.timer530=a.timer558={123,-91,17};
        const auto event=[](auto... v){((std::cout<<v<<' '),...);};
        UnitDestinationServices s;s.trace=event;
        s.targetId=[&](const void* t){if(t==&cells[0])return 1;if(t==&cells[1])return 2;throw std::invalid_argument("Destination Cell identity missing");};
        s.dispose=[&](const void* ptr){if(ptr!=&heap)throw std::runtime_error("Wrong vector disposal");event('H',0,0,1);};
        MapFloorHeightState floor;floor.planes[0].x=1.;
        MapFloorHeightWorld world{slots,&fallback,[&](auto pos){event('f',0,0,std::uint32_t(std::uint16_t(pos.x))|(std::uint32_t(std::uint16_t(pos.y))<<16));}};
        s.coordinates=[&](const void* t){const auto point=mapCellCenterHeight(floor,height,*static_cast<const MapCellInput*>(t));event('Q',point.x,point.y,point.z);return point;};
        s.cellFlags=[&](Coord point){event('L',point.x,point.y,point.z);return mapCoordinateCell(point,world,262144).flags;};
        UnitDestinationView v{a,d,mission,global,refs};
        GroundDriveIdleTargetServices idle;idle.destination=s;
        idle.targetKind=[&](const void* ptr){const int kind=kinds[s.targetId(ptr)-1];event('k',0,0,kind);return kind;};
        idle.targetWord=[&](const void* ptr,int axis){const auto& pos=static_cast<const MapCellInput*>(ptr)->position;const auto value=axis?pos.y:pos.x;event('W',axis,s.targetId(ptr),value);return value;};
        idle.mission414=[&](int x,int y){event('B',x,y,effect);return std::uint8_t(effect);};
        const int count=number(in,1,64);std::vector<std::array<int,5>> actions;
        for(int i=0;i<count;++i){const int mode=number(in,0,1),id=number(in,0,2),flag=number(in,0,255),tick=take<int>(in),padding=take<int>(in);if(mode!=1||id!=0||flag!=1)throw std::invalid_argument("Idle action must retain the interior entry");actions.push_back({mode,id,flag,tick,padding});}
        std::string extra;if(in>>extra)throw std::invalid_argument("Extra destination input");
        for(const auto& action:actions){
            UnitDestinationInputs w{action[3],action[4],delay,{},0.30000001192092896};
            const auto result=processOrdinaryIdleTarget(v,p,w,idle);
            event("flow",result==GroundDriveIdleTargetResult::returnFalse?"return-false":"continue");
        }
        if(a.vectorBuffer&&a.vectorBuffer!=&heap)throw std::runtime_error("Retained vector buffer identity differs");
        event("state",int(a.forced190),a.field490,a.target494?s.targetId(a.target494):0,int(a.suspended598),int(d.movement.reached5a1),int(a.vectorBuffer!=nullptr),a.vectorCapacity,a.vectorCount,int(a.vectorOwned),
            d.destination.x,d.destination.y,d.destination.z,std::bit_cast<std::uint64_t>(d.percentage),global,refs);
        for(auto q:d.route)event(q);for(auto q:a.timer530)event(q);for(auto q:a.timer558)event(q);
        event(fallback.position.x,fallback.position.y,int(floor.flags),std::bit_cast<std::uint64_t>(floor.height),std::bit_cast<std::uint64_t>(floor.scale));
        for(const auto& plane:floor.planes)for(double x:{plane.x,plane.y,plane.offset,plane.limit,plane.add})event(std::bit_cast<std::uint64_t>(x));
        event("retained",d.movement.head.x,d.movement.head.y,d.movement.head.z,d.movement.track,d.movement.index,d.movement.accumulator,int(d.movement.driving),d.movement.actor.position.x,d.movement.actor.position.y,d.movement.actor.position.z);
        std::cout<<'\n';
    }return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
