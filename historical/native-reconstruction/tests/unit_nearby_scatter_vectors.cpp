// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/UnitNearbyScatterWorld.hpp"
#include "render/Lighting.hpp"
#include <cfenv>
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
    int checks=0;const auto check=[&](bool ok){++checks;if(!ok)throw std::runtime_error("Unit nearby guard "+std::to_string(checks));};
    UnitDestinationState actor;GroundDriveProcessState drive;UnitDestinationProfile profile;
    UnitScatterExtra extra;UnitAdmissionWorld admission;admission.gates.objects[0].mission.mission98=2;
    std::uint32_t global=7,refs=3;std::vector<MapCellInput*> slots(262144);std::vector<int> ids(262144,-1);admission.gates.slots=ids;admission.gates.fallbackCell=0;admission.gates.cells[0]={};admission.cells[0]={};
    MapCellInput cell;cell.land=1;std::array<ScatterWorldCellBinding,1> bindings{{{&cell,0,0}}};
    MapFloorHeightState floor;int floorHeight=104,layerHeight=104;MapPermissionShape shape{2,0,0,100,100};
    UnitDestinationView unit{actor,drive,admission.gates.objects[0].mission,global,refs};
    UnitScatterWorldView world{unit,profile,extra,admission,0,slots,cell,bindings,floor,floorHeight,layerHeight,shape,{}};
    int speed=1,dimension1=-2,frame=1,overlay=-1;NearbyLocationPoint empty{};NearbyAdmissionServices a;
    std::array<std::uint32_t,108> speeds;speeds.fill(0x3f800000);a.speedBits=speeds;
    std::function<NearbyAdmissionCell(const MapCellInput&)> bind=[&](const auto& c){return NearbyAdmissionCell{c,admission.cells[0].occupation,admission.cells[0].elevatedOccupation,overlay};};
    std::function<double(double)> sqrt;
    UnitNearbySearchInputs nearby{speed,dimension1,frame,empty,bind,a,sqrt};
    DirectionData directions;OriginalRandomState random;random.table.fill(37);random.next1=9;random.next2=17;const auto initial=random;
    std::array<ScatterCellPoint,8> neighbors{};int queries=0,requests=0,seenSpeed=0,alternate=0;
    NearbyLocationMapTrace trace=[&](char k,auto,const auto*,int n){if(k=='S'){++requests;seenSpeed=n;}if(k=='A')alternate=n;};
    ScatterWorldTrace observe=[&](char g,char k,auto,auto,auto){if(g=='w'&&k=='L')++queries;};
    drive.movement.actor.position={-257,-65537,33};drive.route.fill(27);
    const auto call=[&]{scatterUnitWithNearbyOnMap(world,{},1,1,directions,random,neighbors,104,100,-31,5,0.3,[](int,int){return 1;},nearby,observe,trace);};
    check(queries==0&&requests==0&&refs==3&&global==7);call();
    check(requests==1&&seenSpeed==1&&alternate==-256&&queries>0&&refs==3&&global==7&&!floor.flags);
    speed=4;call();check(seenSpeed==4&&requests==2); // borrowed input, not a captured value
    check(random.next1==initial.next1&&random.next2==initial.next2&&random.table==initial.table);
    check(admission.gates.objects[0].mission.queuedA0==-1&&std::all_of(drive.route.begin(),drive.route.end(),[](int n){return n==27;}));
    int restored=0;admission.trace=[&](char,int,int,int){++restored;};admission.gates.trace=[&](char,int){++restored;};
    a.trace=[](auto,const auto&,int,int,int,int,int,int,std::uint32_t){throw std::runtime_error("unrelated");};
    drive.movement.actor.position={12928,12928,0};dimension1=0;
    bool fault=false;try{call();}catch(const std::runtime_error& e){fault=std::string(e.what())=="unrelated";}
    admission.trace('?',0,0,0);admission.gates.trace('?',0);check(fault&&restored==2&&refs==3&&global==7);a.trace={};
    bind={};bool refused=false;try{call();}catch(const std::invalid_argument&){refused=true;}check(refused&&refs==3&&global==7);
    // Legacy runtime-facing entry must retain its zero-point refusal.
    refused=false;try{scatterOrdinaryUnitOnMap(world,{},1,1,directions,random,neighbors,104,100,-31,5,0.3,[](int,int){return 1;});}catch(const UnsupportedUnitScatter&){refused=true;}check(refused&&refs==3&&global==7);
    bind=[&](const auto& c){return NearbyAdmissionCell{c,admission.cells[0].occupation,admission.cells[0].elevatedOccupation,overlay};};
    directions.slopeStep=1.;refused=false;
    try{scatterUnitWithNearbyOnMap(world,{1,0,0},1,1,directions,random,neighbors,104,100,-31,5,0.3,[](int,int off){return off==9;},nearby);}
    catch(const UnsupportedUnitScatter& e){refused=std::string(e.what()).find("speed")!=std::string::npos;}
    check(refused&&refs==3&&global==7);
    std::cout<<checks<<" native Unit nearby guard checks PASS\n";
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=3)throw std::invalid_argument("Expected private direction data");
    std::ifstream prepared(argv[1],std::ios::binary);Bytes raw(16464);
    if(!prepared.read(reinterpret_cast<char*>(raw.data()),std::streamsize(raw.size()))||prepared.peek()!=std::char_traits<char>::eof())throw std::invalid_argument("Private direction data size");
    const auto directions=readDirectionData(Data(std::move(raw)),PatchedEngineSha);
    std::ifstream renderInput(argv[2],std::ios::binary);Bytes renderRaw(69944);
    if(!renderInput.read(reinterpret_cast<char*>(renderRaw.data()),std::streamsize(renderRaw.size()))||renderInput.peek()!=std::char_traits<char>::eof())throw std::invalid_argument("Private render data extent");
    const auto render=readRenderData(Data(std::move(renderRaw)),PatchedEngineSha);
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);if(take<char>(in)!='N')return 2;
        const int speedType=number(in,0,8),dimension1=take<int>(in),fpMode=number(in,0,3);
        const int fpModes[]{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};std::fesetround(fpModes[fpMode]);
        const char mode=take<char>(in);if(mode!='J'&&mode!='P')return 2;
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
        const auto cellId=[&](const MapCellInput& c){for(int i=0;i<10;++i)if(&c==&cells[i])return i;throw std::logic_error("Unknown nearby Cell");};
        const int overlay=-1;NearbyLocationPoint empty{};int frame=0;
        std::function<NearbyAdmissionCell(const MapCellInput&)> bind=[&](const auto& c){const auto& a=admission.cells[cellId(c)];return NearbyAdmissionCell{c,a.occupation,a.elevatedOccupation,overlay};};
        std::array<std::uint32_t,108> speedBits{};for(int i=0;i<12;++i)speedBits[i*9+speedType]=admission.speedBits[i];
        NearbyAdmissionServices nearbyAdmission;nearbyAdmission.speedBits=speedBits;
        nearbyAdmission.trace=[&](char k,const auto& c,int a,int b,int d,int e,int f,int g,std::uint32_t h){if(k=='C')event('n',k,cellId(c),a,b,d,e,f,g,h);else event('n',k,a);};
        std::function<double(double)> squareRoot=[&](double n){const auto r=tableSqrt(render,std::abs(n));event('n','D',int(n),std::bit_cast<std::uint64_t>(r));return r;};
        UnitNearbySearchInputs nearby{speedType,dimension1,frame,empty,bind,nearbyAdmission,squareRoot};
        NearbyLocationMapTrace nearbyTrace=[&](char k,auto q,const auto* c,int n){
            if(k=='L')event('n',k,q.x,q.y,cellId(*c));else if(k=='B')event('n',k,cellId(*c),q.x,q.y,n);else if(k=='b')event('n',k,cellId(*c),n);
            else if(k=='t')event('n',k,n);else if(k=='S'||k=='A')event('n',k,q.x,q.y,n);else event('n',k,q.x,q.y);
        };

        for(const auto& action:actions){
            const Coord point{action[0],action[1],action[2]};admission.gates.tick=action[5];frame=action[5];
            if(mode=='P'){
                MapAttributeLookup map{slots,&cells[9],[&](auto q){event('w','L',q.x,q.y,0);},[&](auto q){event('w','W',std::uint32_t(std::uint16_t(q.x))|(std::uint32_t(std::uint16_t(q.y))<<16),0,0);}};
                event('w','P',point.x,point.y,point.z);const auto q=scatterProjectedCell(point,map);event('w','p',q.x,q.y,0);
            }else scatterUnitWithNearbyOnMap(world,point,std::uint8_t(action[3]),std::uint8_t(action[4]),directions,random,neighbors,projectHeight,action[5],padding,delay,0.30000001192092896,[&](int,int off){return off==9?control9:control7;},nearby,trace,nearbyTrace);
        }
        int target=0;for(int i=0;i<10;++i)if(a.target494==&cells[i])target=i+1;
        event("state",admission.gates.objects.at(0).mission.queuedA0,int(admission.gates.objects.at(0).mission.queuedA4),global,refs,int(a.forced190),a.field490,target,int(a.suspended598),int(drive.movement.reached5a1),int(a.vectorBuffer!=nullptr),a.vectorCapacity,a.vectorCount,int(a.vectorOwned));
        event(drive.destination.x,drive.destination.y,drive.destination.z);for(auto q:drive.route)event(q);for(auto q:a.timer530)event(q);for(auto q:a.timer558)event(q);
        event(cells[9].position.x,cells[9].position.y,int(floor.flags),std::bit_cast<std::uint64_t>(floor.height),std::bit_cast<std::uint64_t>(floor.scale));for(const auto& plane:floor.planes)for(double x:{plane.x,plane.y,plane.offset,plane.limit,plane.add})event(std::bit_cast<std::uint64_t>(x));
        event(random.next1,random.next2);for(auto n:random.table)event(n);event("retained",drive.movement.actor.position.x,drive.movement.actor.position.y,drive.movement.actor.position.z,drive.movement.head.x,drive.movement.head.y,drive.movement.head.z,drive.movement.track,drive.movement.index,drive.movement.accumulator,int(drive.movement.driving),std::bit_cast<std::uint64_t>(drive.percentage));event("nearby-retained",speedType,dimension1);for(int i=0;i<10;++i){const auto& c=cells[i];const auto& ac=admission.cells[i];event(c.position.x,c.position.y,int(c.level),int(c.slope),c.flags,c.land,ac.occupation,ac.elevatedOccupation);}if(std::fegetround()!=fpModes[fpMode])throw std::runtime_error("Nearby caller FP mode changed");std::cout<<'\n';
    }return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
