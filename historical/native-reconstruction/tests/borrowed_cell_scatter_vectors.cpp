// SPDX-License-Identifier: GPL-3.0-or-later
#include "borrowed_cell_scatter_fixture.hpp"
#include "render/Lighting.hpp"
#include "assets/MovementData.hpp"
#include "assets/PreparedData.hpp"
#include <cmath>
#include <cfenv>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
template<class T>T take(std::istream& in){T v{};if(!(in>>v))throw std::invalid_argument("Missing Scatter world input");return v;}
int number(std::istream& in,int lo,int hi){auto v=take<int>(in);if(v<lo||v>hi)throw std::invalid_argument("Scatter world input domain");return v;}
Data load(const char* path){std::ifstream f(path,std::ios::binary|std::ios::ate);if(!f)throw std::invalid_argument("Missing private input");const auto n=f.tellg();if(n<0||n>16000000)throw std::invalid_argument("Private input size");Bytes b(static_cast<std::size_t>(n));f.seekg(0);if(!f.read(reinterpret_cast<char*>(b.data()),std::streamsize(b.size())))throw std::invalid_argument("Private input read");return Data(std::move(b));}
int main(int argc,char** argv){try{
    if(argc!=4)throw std::invalid_argument("Expected private engine, direction and render data");
    const auto data=readDriveData(load(argv[1]),load(argv[2]));
    const auto render=readRenderData(load(argv[3]),PatchedEngineSha);
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char mode=take<char>(in);const bool withNearby=mode=='N';
        int dimension1=0,fpMode=0;const int fpModes[]{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};
        std::map<int,int> speedTypes;std::array<int,5> typeIds{0,1,2,3,4};
        std::array<std::uint32_t,108> nearbySpeeds;nearbySpeeds.fill(0x3f800000);
        if(withNearby){
            dimension1=take<int>(in);fpMode=number(in,0,3);
            for(int i=0;i<5;++i)speedTypes[i]=number(in,0,8);
            for(auto& n:typeIds)n=number(in,0,4);
            for(auto& n:nearbySpeeds)n=take<std::uint32_t>(in);
            mode=take<char>(in);
        }
        std::fesetround(fpModes[fpMode]);if(mode!='J')return 2;
        std::array<UnitDestinationState,5> actors;std::array<GroundDriveProcessState,5> drives;
        std::array<UnitDestinationProfile,5> profiles;std::array<UnitScatterExtra,5> extras;
        std::array<std::uint32_t,5> references;std::array<int,5> paddings{};
        const auto byte=[&](){return std::uint8_t(number(in,0,255));};
        const int queued=number(in,-1,31);const auto queuedByte=byte();
        auto& a=actors[0];a.forced190=byte();a.suspended598=byte();
        auto& extra=extras[0];extra.field5b9=byte();extra.field599=byte();extra.target228=number(in,0,1);
        auto& drive=drives[0];drive.movement.actor.bridge79=byte();extra.registry574=std::int8_t(number(in,-128,127));
        const auto poolx=std::int16_t(number(in,-32768,32767)),pooly=std::int16_t(number(in,-32768,32767));
        auto& refs=references[0];refs=take<std::uint32_t>(in);auto global=take<std::uint32_t>(in);const int initialTarget=number(in,0,10),buffer=number(in,0,1);
        a.vectorOwned=byte();a.vectorCapacity=take<int>(in);a.vectorCount=take<int>(in);a.field490=take<int>(in);
        auto& p=profiles[0];p.powered=byte();p.field5c8=byte();p.field5c0=take<int>(in);p.field3fc=take<int>(in);p.timer58c=take<int>(in);p.timer594=take<int>(in);p.disabled1bc=byte();p.disabled1c0=byte();
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
        if(take<char>(in)!='X')throw std::invalid_argument("Missing Cell join records");
        const int cell=number(in,0,9);const auto elevated=byte();auto rule=byte();int threshold=take<int>(in);
        const int growthCount=number(in,1,8);std::vector<std::uint32_t> growth;for(int i=0;i<growthCount;++i)growth.push_back(take<std::uint32_t>(in));
        std::map<int,int> house194;for(int i=0;i<3;++i)house194[i]=take<int>(in);
        std::map<int,CellScatterType> types;for(int i=0;i<5;++i)types[i]={byte(),byte()};
        std::array<double,5> ranks;for(auto& n:ranks)n=std::bit_cast<double>(take<std::uint64_t>(in));
        std::array<std::uint8_t,5> eligibility,shortTracks;for(auto& n:eligibility)n=byte();for(auto& n:shortTracks)n=byte();
        for(auto& d:drives)d.movement.track=number(in,0,63);for(auto& d:drives)d.movement.index=take<int>(in);
        for(int i=1;i<5;++i){
            auto& state=actors[i];auto& d=drives[i];auto& profile=profiles[i];auto& x=extras[i];auto& mission=admission.gates.objects.at(i).mission;
            mission.queuedA0=number(in,-1,31);mission.queuedA4=byte();state.forced190=byte();state.suspended598=byte();x.field5b9=byte();x.field599=byte();x.target228=number(in,0,1);
            d.movement.actor.bridge79=byte();x.registry574=std::int8_t(number(in,-128,127));references[i]=take<std::uint32_t>(in);
            const int target=number(in,0,10),hasBuffer=number(in,0,1);state.target494=target?&cells[target-1]:nullptr;state.vectorBuffer=hasBuffer?&state:nullptr;
            state.vectorOwned=byte();state.vectorCapacity=take<int>(in);state.vectorCount=take<int>(in);state.field490=take<int>(in);
            profile.powered=byte();profile.field5c8=byte();profile.field5c0=take<int>(in);profile.field3fc=take<int>(in);profile.timer58c=take<int>(in);profile.timer594=take<int>(in);profile.disabled1bc=byte();profile.disabled1c0=byte();
            auto& f=d.movement.body;f.desired=std::uint16_t(number(in,0,65535));f.start=std::uint16_t(number(in,0,65535));f.timerStart=take<int>(in);f.duration=take<int>(in);f.rate=std::uint16_t(number(in,0,65535));paddings[i]=take<int>(in);
            d.movement.actor.position=coord();d.movement.head=coord();d.destination=coord();for(auto& q:d.route)q=take<int>(in);
            d.percentage=1.;d.movement.accumulator=33;d.movement.driving=true;d.movement.reached5a1=173;state.timer530=state.timer558={123,-91,17};
            profile.isTrain=admission.objects.at(i).train;
        }
        paddings[0]=padding;
        std::string tail;if(in>>tail)throw std::invalid_argument("Extra Cell join input");
        int heap=0;a.vectorBuffer=buffer?&heap:nullptr;a.target494=initialTarget?&cells[initialTarget-1]:nullptr;a.timer530=a.timer558={123,-91,17};drive.movement.reached5a1=173;
        MapFloorHeightState floor;floor.planes[0].x=1.;std::array<TerrainCellPoint,128> pool;pool.fill({poolx,pooly});
        test::BorrowedCellScatterFixture fixture(admission,actors,drives,eligibility,shortTracks,
            cells,bindings,floor,*data,[&](double n){return tableSqrt(render,n);});
        auto& borrowed=fixture.admission->world();
        std::vector<BorrowedUnitScatterWorldView> worlds;worlds.reserve(2);
        std::array<BorrowedUnitScatterWorldView*,2> views;
        for(int i=0;i<2;++i){
            UnitDestinationView unit{fixture.actors[i].destination,drives[i],borrowed.gates.objects.at(i).mission,global,references[i]};
            worlds.push_back({unit,profiles[i],extras[i],borrowed,i,fixture.table,fixture.attributes[9].input,
                fixture.cellBindings,floor,floorHeight,layerHeight,shape,pool});views[i]=&worlds.back();
        }
        const auto event=[](auto... v){((std::cout<<v<<' '),...);};ScatterWorldTrace trace=event;
        BorrowedCellUnitScatterView world{borrowed,views,std::span(ranks).first<2>(),std::span(typeIds).first<2>(),
            {},{},types,house194,rule,threshold,&fixture.admission->motion()};
        const auto cellId=[&](const MapCellInput& c){for(int i=0;i<10;++i)if(&c==&fixture.attributes[i].input)return i;throw std::logic_error("Unknown nearby Cell");};
        int overlay=-1,frame=0;NearbyLocationPoint empty{};
        std::function<NearbyAdmissionCell(const MapCellInput&)> bind=[&](const auto& c){const auto& ac=borrowed.cells.at(cellId(c));return NearbyAdmissionCell{c,ac.occupation,ac.elevatedOccupation,overlay};};
        NearbyAdmissionServices nearbyAdmission;nearbyAdmission.speedBits=nearbySpeeds;
        nearbyAdmission.trace=[&](char k,const auto& c,int a,int b,int d,int e,int f,int g,std::uint32_t h){if(k=='C')event('n',k,cellId(c),a,b,d,e,f,g,h);else event('n',k,a);};
        CellNearbySearchInputs nearby{speedTypes,dimension1,frame,empty,bind,nearbyAdmission};
        NearbyLocationMapTrace nearbyTrace=[&](char k,auto q,const auto* c,int n){
            if(k=='L')event('n',k,q.x,q.y,cellId(*c));else if(k=='B')event('n',k,cellId(*c),q.x,q.y,n);else if(k=='b')event('n',k,cellId(*c),n);
            else if(k=='t')event('n',k,n);else if(k=='S'||k=='A')event('n',k,q.x,q.y,n);else event('n',k,q.x,q.y);
        };
        for(const auto& action:actions){
            const Coord point{action[0],action[1],action[2]};fixture.shared.tick=action[5];frame=action[5];std::size_t grows=0;
            CellUnitScatterInputs input{*data,fixture.squareRoot,random,neighbors,std::span(paddings).first<2>(),projectHeight,action[5],delay,0.30000001192092896,
                [&](int,int off){return off==9?control9:control7;},[&](int){return growth[grows++%growth.size()];},[](int){}};
            if(withNearby)scatterCellUnitsWithNearbyOnMap(cell,point,std::uint8_t(action[3]),std::uint8_t(action[4]),elevated,world,input,nearby,trace,nearbyTrace);
            else scatterCellUnitsOnMap(cell,point,std::uint8_t(action[3]),std::uint8_t(action[4]),elevated,world,input,trace);
        }
        fixture.exportObservations(admission,actors,cells);
        int target=0;for(int i=0;i<10;++i)if(a.target494==&cells[i])target=i+1;
        event("state",admission.gates.objects.at(0).mission.queuedA0,int(admission.gates.objects.at(0).mission.queuedA4),global,refs,int(a.forced190),a.field490,target,int(a.suspended598),int(drive.movement.reached5a1),int(a.vectorBuffer!=nullptr),a.vectorCapacity,a.vectorCount,int(a.vectorOwned));
        event(drive.destination.x,drive.destination.y,drive.destination.z);for(auto q:drive.route)event(q);for(auto q:a.timer530)event(q);for(auto q:a.timer558)event(q);
        event(cells[9].position.x,cells[9].position.y,int(floor.flags),std::bit_cast<std::uint64_t>(floor.height),std::bit_cast<std::uint64_t>(floor.scale));for(const auto& plane:floor.planes)for(double x:{plane.x,plane.y,plane.offset,plane.limit,plane.add})event(std::bit_cast<std::uint64_t>(x));
        event(random.next1,random.next2);for(auto n:random.table)event(n);event("retained",drive.movement.actor.position.x,drive.movement.actor.position.y,drive.movement.actor.position.z,drive.movement.head.x,drive.movement.head.y,drive.movement.head.z,drive.movement.track,drive.movement.index,drive.movement.accumulator,int(drive.movement.driving),std::bit_cast<std::uint64_t>(drive.percentage));
        for(int i=1;i<5;++i){const auto& state=actors[i];const auto& d=drives[i];const auto& mission=admission.gates.objects.at(i).mission;int targetId=0;
            for(int j=0;j<10;++j)if(state.target494==&cells[j])targetId=j+1;
            event("actor",i,mission.queuedA0,int(mission.queuedA4),references[i],int(state.forced190),state.field490,targetId,int(state.suspended598),int(d.movement.reached5a1),int(state.vectorBuffer!=nullptr),state.vectorCapacity,state.vectorCount,int(state.vectorOwned));
            event(d.destination.x,d.destination.y,d.destination.z);for(auto q:d.route)event(q);for(auto q:state.timer530)event(q);for(auto q:state.timer558)event(q);
            event(d.movement.actor.position.x,d.movement.actor.position.y,d.movement.actor.position.z,d.movement.head.x,d.movement.head.y,d.movement.head.z,d.movement.track,d.movement.index,d.movement.accumulator,int(d.movement.driving),std::bit_cast<std::uint64_t>(d.percentage));
        }
        event("cell",admission.gates.cells.at(cell).head,admission.cells.at(cell).elevatedHead);
        for(int i=0;i<5;++i)event(i,admission.gates.objects.at(i).next,std::bit_cast<std::uint64_t>(ranks[i]));
        if(withNearby){
            event("nearby-retained",dimension1);for(int i=0;i<5;++i)event(speedTypes[i],typeIds[i]);
            for(int i=0;i<10;++i){const auto& c=cells[i];const auto& ac=borrowed.cells.at(i);event(c.position.x,c.position.y,int(c.level),int(c.slope),c.flags,c.land,ac.occupation,ac.elevatedOccupation);}
        }
        if(std::fegetround()!=fpModes[fpMode])throw std::runtime_error("Borrowed Cell caller FP mode changed");
        std::cout<<'\n';
    }return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
