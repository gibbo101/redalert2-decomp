// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/UnitScatterWorld.hpp"
#include "assets/MovementData.hpp"
#include "assets/PreparedData.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
template<class T>T take(std::istream& in){T v{};if(!(in>>v))throw std::invalid_argument("Missing Scatter world input");return v;}
int number(std::istream& in,int lo,int hi){auto v=take<int>(in);if(v<lo||v>hi)throw std::invalid_argument("Scatter world input domain");return v;}
void guards(){
    int checkIndex=0;const auto check=[&](bool ok){++checkIndex;if(!ok)throw std::runtime_error("Scatter world native guard failed at "+std::to_string(checkIndex));};
    UnitDestinationState actor;GroundDriveProcessState drive;UnitDestinationProfile profile;
    UnitScatterExtra extra;UnitAdmissionWorld admission;admission.gates.objects[0].mission.mission98=2;
    std::uint32_t global=7,refs=3;std::vector<MapCellInput*> slots(262144);MapCellInput fallback;
    MapFloorHeightState floor;int floorHeight=104,layerHeight=104;MapPermissionShape shape;
    UnitDestinationView unit{actor,drive,admission.gates.objects[0].mission,global,refs};
    UnitScatterWorldView world{unit,profile,extra,admission,0,slots,fallback,{},floor,floorHeight,layerHeight,shape,{}};
    DirectionData direction;OriginalRandomState random;std::array<ScatterCellPoint,8> neighbors{};
    const auto call=[&](Coord away){scatterOrdinaryUnitOnMap(world,away,0,0,direction,random,neighbors,104,100,-31,5,0.3,[](int,int){return 1;});};
    // Reject noncanonical association before touching the borrowed actor/map.
    bool refused=false;try{call({1,0,0});}catch(const std::invalid_argument&){refused=true;}
    check(refused&&refs==3&&global==7&&!floor.flags);
    std::vector<int> ids(262144,-1);admission.gates.slots=ids;
    int observed=0;admission.trace=[&](char,int,int,int){++observed;};admission.gates.trace=[&](char,int){++observed;};
    refused=false;try{call({});}catch(const UnsupportedUnitScatter&){refused=true;}
    admission.trace('?',0,0,0);admission.gates.trace('?',0);
    check(refused&&observed==2&&refs==3&&global==7&&!floor.flags); // scoped observers and retained lifetime
    UnitDiscoveryActor wrongMission;UnitDestinationView wrongUnit{actor,drive,wrongMission,global,refs};
    UnitScatterWorldView mismatch{wrongUnit,profile,extra,admission,0,slots,fallback,{},floor,floorHeight,layerHeight,shape,{}};
    refused=false;try{scatterOrdinaryUnitOnMap(mismatch,{1,0,0},0,0,direction,random,neighbors,104,100,-31,5,0.3,{});}catch(const std::invalid_argument&){refused=true;}
    check(refused&&refs==3&&global==7&&!floor.flags);
    drive.route.fill(27);actor.forced190=1;int target=0;
    admission.gates.objects[0].mission.mission98=7;
    UnitDestinationServices services;services.targetId=[](const void*){return 1;};services.coordinates=[](const void*){return Coord{128,384,0};};services.cellFlags=[](Coord){return 0;};
    setOrdinaryUnitCellDestination(unit,&target,1,profile,{100,-31,5,{},0.3},services,[](const void*){return 0;});
    check(std::all_of(drive.route.begin(),drive.route.end(),[](int n){return n==27;})&&drive.destination==Coord{128,384,0}&&refs==3&&global==7&&actor.timer530[1]==384);
    actor.forced190=1;refused=false;try{setOrdinaryUnitCellDestination(unit,&target,1,profile,{100,-31,5,{},0.3},services,[](const void*){return 1;});}catch(const UnsupportedUnitDestination&){refused=true;}
    check(refused&&drive.route[0]==27&&refs==3&&global==7);
    MapAttributeLookup map{slots,&fallback,{},{}};fallback.level=0;fallback.flags=0;
    // Every signed-word diagonal origin terminates in <=211 lookups; origins
    // near +32767 return the first wrapped candidate. Native bound check only.
    std::size_t queries=0;map.query=[&](auto){++queries;};
    for(int n=-32768;n<=32767;++n){queries=0;const auto p=scatterProjectedCell({n*256,n*256,2147483647},map);const auto expected=std::bit_cast<std::int16_t>(std::uint16_t(n>32761?n+6:n));check(p==MapInputPosition{expected,expected}&&queries<=211);}
    std::cout<<"6 native Scatter world guard checks PASS\n";
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=2)throw std::invalid_argument("Expected private direction data");
    std::ifstream prepared(argv[1],std::ios::binary);Bytes raw(16464);
    if(!prepared.read(reinterpret_cast<char*>(raw.data()),std::streamsize(raw.size()))||prepared.peek()!=std::char_traits<char>::eof())throw std::invalid_argument("Private direction data size");
    const auto directions=readDirectionData(Data(std::move(raw)),PatchedEngineSha);
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);const char mode=take<char>(in);if(mode!='J'&&mode!='P')return 2;
        const auto byte=[&](){return std::uint8_t(number(in,0,255));};
        const int queued=number(in,-1,31);const auto queuedByte=byte();
        UnitDestinationState a;a.forced190=byte();a.suspended598=byte();
        UnitScatterExtra extra;extra.field5b9=byte();extra.field599=byte();extra.target228=number(in,0,1);
        GroundDriveProcessState drive;drive.movement.actor.bridge79=byte();extra.registry574=std::int8_t(number(in,-128,127));
        const auto poolx=std::int16_t(number(in,-32768,32767)),pooly=std::int16_t(number(in,-32768,32767));
        auto refs=take<std::uint32_t>(in),global=take<std::uint32_t>(in);const int initialTarget=number(in,0,10),buffer=number(in,0,1);
        a.vectorOwned=byte();a.vectorCapacity=take<int>(in);a.vectorCount=take<int>(in);a.field490=take<int>(in);
        UnitDestinationProfile p;p.powered=byte();p.field5c8=byte();p.field5c0=take<int>(in);p.field3fc=take<int>(in);p.timer58c=take<int>(in);p.timer594=take<int>(in);p.disabled1bc=byte();p.disabled1c0=byte();
        int floorHeight=take<int>(in),layerHeight=take<int>(in),projectHeight=take<int>(in),delay=take<int>(in),padding=take<int>(in);const auto control9=byte(),control7=byte();
        auto& facing=drive.movement.body;facing.desired=std::uint16_t(number(in,0,65535));facing.start=std::uint16_t(number(in,0,65535));facing.timerStart=take<int>(in);facing.duration=take<int>(in);facing.rate=std::uint16_t(number(in,0,65535));
        OriginalRandomState random;random.disabled=byte();random.next1=number(in,0,249);random.next2=number(in,0,249);
        const auto coord=[&](){const int x=take<int>(in),y=take<int>(in),z=take<int>(in);return Coord{x,y,z};};
        drive.movement.actor.position=coord();drive.movement.head=coord();drive.destination=coord();for(auto& q:drive.route)q=take<int>(in);
        drive.percentage=1.;drive.movement.track=2;drive.movement.index=9;drive.movement.accumulator=33;drive.movement.driving=true;
        MapPermissionShape shape;shape.dimension0=take<int>(in);shape.originX=take<int>(in);shape.originY=take<int>(in);shape.width=take<int>(in);shape.height=take<int>(in);
        UnitAdmissionWorld admission;for(auto& bits:admission.speedBits)bits=take<std::uint32_t>(in);for(auto& n:random.table)n=take<std::uint32_t>(in);
        std::array<MapCellInput,10> cells;std::array<ScatterWorldCellBinding,10> bindings;
        std::vector<MapCellInput*> slots(262144);std::vector<int> ids(262144,-1);admission.gates.slots=ids;admission.gates.fallbackCell=9;
        for(int i=0;i<10;++i){
            const int slot=number(in,-1,262143),x=number(in,-32768,32767),y=number(in,-32768,32767);auto& c=cells[i];c.position={std::int16_t(x),std::int16_t(y)};c.level=std::int8_t(number(in,-128,127));c.slope=byte();c.flags=take<std::uint32_t>(in);c.land=number(in,0,11);
            auto& gate=admission.gates.cells[i];gate.point={c.position.x,c.position.y};gate.head=number(in,-1,4);
            auto& ac=admission.cells[i];ac.elevatedHead=number(in,-1,4);ac.occupation=take<std::uint32_t>(in);ac.elevatedOccupation=take<std::uint32_t>(in);ac.owner=take<int>(in);ac.elevatedOwner=take<int>(in);
            ac.level=c.level;ac.ramp=c.slope;ac.flags=c.flags;ac.land=c.land;bindings[i]={&c,i,byte()};
            if(slot!=-1){if(i==9||slots[slot])throw std::invalid_argument("Noncanonical Scatter slot");slots[slot]=&c;ids[slot]=i;}
        }
        for(int i=0;i<5;++i){
            auto& g=admission.gates.objects[i];auto& o=admission.objects[i];g.kind=take<int>(in);g.next=number(in,-1,4);g.owner=number(in,0,2);g.gate=byte();g.mission.mission98=number(in,-1,31);g.animation18=byte();g.animation19=byte();o.flags=byte();o.crushable=byte();o.crusher=byte();o.train=byte();o.building1350=byte();o.state1b8=take<int>(in);o.target=number(in,-1,4);o.destination=number(in,-1,4);o.weapon=number(in,0,1);o.projectile275=number(in,0,1);
            g.mission.queuedA0=i?7:queued;g.mission.queuedA4=i?0:queuedByte;
        }
        p.isTrain=admission.objects.at(0).train;
        admission.gates.houses[0]={0,1};admission.gates.houses[1]={1,2};admission.gates.houses[2]={33,0};
        std::array<ScatterCellPoint,8> neighbors;for(int i=0;i<8;++i){constexpr std::array<ScatterCellPoint,8> offsets{{{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}}};neighbors[i]=offsets[i];admission.directions[i]={neighbors[i].x,neighbors[i].y};}
        const int count=number(in,1,64);std::vector<std::array<int,6>> actions;for(int i=0;i<count;++i){const auto at=coord();const int ignoreMission=number(in,0,255),ignoreDestination=number(in,0,255),tick=take<int>(in);actions.push_back({at.x,at.y,at.z,ignoreMission,ignoreDestination,tick});}
        std::string tail;if(in>>tail)throw std::invalid_argument("Extra Scatter world input");
        int heap=0;a.vectorBuffer=buffer?&heap:nullptr;a.target494=initialTarget?&cells[initialTarget-1]:nullptr;a.timer530=a.timer558={123,-91,17};drive.movement.reached5a1=173;
        MapFloorHeightState floor;floor.planes[0].x=1.;std::array<TerrainCellPoint,128> pool;pool.fill({poolx,pooly});
        UnitDestinationView unit{a,drive,admission.gates.objects.at(0).mission,global,refs};
        UnitScatterWorldView world{unit,p,extra,admission,0,slots,cells[9],bindings,floor,floorHeight,layerHeight,shape,pool};
        const auto event=[](auto... v){((std::cout<<v<<' '),...);};
        ScatterWorldTrace trace=event;
        for(const auto& action:actions){
            const Coord point{action[0],action[1],action[2]};admission.gates.tick=action[5];
            if(mode=='P'){
                MapAttributeLookup map{slots,&cells[9],[&](auto q){event('w','L',q.x,q.y,0);},[&](auto q){event('w','W',std::uint32_t(std::uint16_t(q.x))|(std::uint32_t(std::uint16_t(q.y))<<16),0,0);}};
                event('w','P',point.x,point.y,point.z);const auto q=scatterProjectedCell(point,map);event('w','p',q.x,q.y,0);
            }else scatterOrdinaryUnitOnMap(world,point,std::uint8_t(action[3]),std::uint8_t(action[4]),directions,random,neighbors,projectHeight,action[5],padding,delay,0.30000001192092896,[&](int,int off){return off==9?control9:control7;},trace);
        }
        int target=0;for(int i=0;i<10;++i)if(a.target494==&cells[i])target=i+1;
        event("state",admission.gates.objects.at(0).mission.queuedA0,int(admission.gates.objects.at(0).mission.queuedA4),global,refs,int(a.forced190),a.field490,target,int(a.suspended598),int(drive.movement.reached5a1),int(a.vectorBuffer!=nullptr),a.vectorCapacity,a.vectorCount,int(a.vectorOwned));
        event(drive.destination.x,drive.destination.y,drive.destination.z);for(auto q:drive.route)event(q);for(auto q:a.timer530)event(q);for(auto q:a.timer558)event(q);
        event(cells[9].position.x,cells[9].position.y,int(floor.flags),std::bit_cast<std::uint64_t>(floor.height),std::bit_cast<std::uint64_t>(floor.scale));for(const auto& plane:floor.planes)for(double x:{plane.x,plane.y,plane.offset,plane.limit,plane.add})event(std::bit_cast<std::uint64_t>(x));
        event(random.next1,random.next2);for(auto n:random.table)event(n);event("retained",drive.movement.actor.position.x,drive.movement.actor.position.y,drive.movement.actor.position.z,drive.movement.head.x,drive.movement.head.y,drive.movement.head.z,drive.movement.track,drive.movement.index,drive.movement.accumulator,int(drive.movement.driving),std::bit_cast<std::uint64_t>(drive.percentage));std::cout<<'\n';
    }return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
