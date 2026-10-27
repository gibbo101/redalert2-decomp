// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/CellUnitScatterWorld.hpp"
#include "render/Lighting.hpp"
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
Data load(const char* path){std::ifstream f(path,std::ios::binary|std::ios::ate);if(!f)throw std::invalid_argument("Missing private input");const auto n=f.tellg();if(n<0||n>16000000)throw std::invalid_argument("Private input size");Bytes b(static_cast<std::size_t>(n));f.seekg(0);if(!f.read(reinterpret_cast<char*>(b.data()),std::streamsize(b.size())))throw std::invalid_argument("Private input read");return Data(std::move(b));}
void guards(){
    std::array<UnitDestinationState,2> a;std::array<GroundDriveProcessState,2> d;
    std::array<UnitDestinationProfile,2> p;std::array<UnitScatterExtra,2> x;
    std::array<std::uint32_t,2> refs{3,5};std::uint32_t global=7;
    UnitAdmissionWorld admission;std::vector<int> ids(262144,-1);admission.gates.slots=ids;admission.gates.fallbackCell=0;
    admission.cells[0];admission.gates.cells[0].head=0;admission.gates.cells[0].point={7,9};
    admission.gates.objects[0].next=1;admission.gates.objects[1].next=-1;
    for(int i=0;i<2;++i){admission.gates.objects[i].mission.mission98=0;admission.objects[i];}
    std::vector<MapCellInput*> slots(262144);MapCellInput fallback;fallback.position={7,9};MapFloorHeightState floor;
    int h=104,layer=104;MapPermissionShape permission;DriveData data;OriginalRandomState random;
    std::array<ScatterWorldCellBinding,1> bindings{{{&fallback,0,0}}};
    std::array<UnitScatterWorldView,2> units{{
        {{a[0],d[0],admission.gates.objects[0].mission,global,refs[0]},p[0],x[0],admission,0,slots,fallback,bindings,floor,h,layer,permission,{}},
        {{a[1],d[1],admission.gates.objects[1].mission,global,refs[1]},p[1],x[1],admission,1,slots,fallback,bindings,floor,h,layer,permission,{}}
    }};
    std::array<UnitScatterWorldView*,2> views{&units[0],&units[1]};std::array<double,2> rank{};std::array<int,2> types{0,0},padding{};
    std::array<std::uint8_t,2> eligible{1,1},shortTrack{};std::map<int,CellScatterType> type{{0,{}}};std::map<int,int> houses{{0,0}};std::uint8_t rule=1;int threshold=0;
    CellUnitScatterView world{admission,views,rank,types,eligible,shortTrack,type,houses,rule,threshold};
    int grows=0,releases=0,dispatches=0,oldObservers=0;
    admission.trace=[&](char,int,int,int){++oldObservers;};admission.gates.trace=[&](char,int){++oldObservers;};
    CellUnitScatterInputs input{data,[](double n){return n;},random,{},padding,104,100,5,0.3,[](int,int){return 1;},[&](int n){if(n!=10)throw std::runtime_error("growth amount");++grows;return 1;},[&](int n){if(n!=10)throw std::runtime_error("release amount");++releases;}};
    int checks=0;const auto check=[&](bool ok){if(!ok)throw std::runtime_error("Cell Scatter guard "+std::to_string(checks));++checks;};
    const auto trace=[&](char g,char k,auto,auto,auto){if(g=='c'&&k=='S')++dispatches;};
    const auto call=[&](){scatterCellUnitsOnMap(0,{1,0,0},0,0,0,world,input,trace);};
    call();check(dispatches==2&&grows==1&&releases==1&&!floor.flags&&fallback.position.x==7&&refs[0]==3&&refs[1]==5&&global==7&&!units[0].admissionMotion&&!units[1].admissionMotion);
    admission.trace('?',0,0,0);admission.gates.trace('?',0);check(oldObservers==2);
    admission.gates.objects[1].kind=6;bool refused=false;try{call();}catch(const std::invalid_argument&){refused=true;}check(refused&&grows==1);admission.gates.objects[1].kind=1;
    views[1]=nullptr;refused=false;try{call();}catch(const std::invalid_argument&){refused=true;}check(refused&&grows==1);views[1]=&units[1];
    UnitDestinationView mirrored{a[1],d[0],admission.gates.objects[1].mission,global,refs[1]};
    UnitScatterWorldView bad{mirrored,p[1],x[1],admission,1,slots,fallback,bindings,floor,h,layer,permission,{}};
    views[1]=&bad;refused=false;try{call();}catch(const std::invalid_argument&){refused=true;}check(refused&&grows==1);views[1]=&units[1];
    MapFloorHeightState otherFloor;UnitScatterWorldView split{units[1].unit,p[1],x[1],admission,1,slots,fallback,bindings,otherFloor,h,layer,permission,{}};
    views[1]=&split;refused=false;try{call();}catch(const std::invalid_argument&){refused=true;}check(refused&&grows==1);views[1]=&units[1];
    input.grow=[&](int){++grows;admission.gates.objects[0].next=-1;return 1;};dispatches=0;call();check(dispatches==1&&releases==2);admission.gates.objects[0].next=1;
    input.grow=[&](int){++grows;return 256;};dispatches=0;call();check(dispatches==0&&releases==2);
    input.grow=[&](int){++grows;return 1;};admission.gates.objects[0].mission.mission98=2;
    refused=false;try{scatterCellUnitsOnMap(0,{},0,0,0,world,input);}catch(const UnsupportedUnitScatter&){refused=true;}
    admission.trace('?',0,0,0);admission.gates.trace('?',0);check(refused&&oldObservers==4&&global==7&&refs[0]==3&&!floor.flags&&!units[0].admissionMotion);
    data.directionsToTargets.slopeStep=1.; // supplied numeric input for this native-only refusal check
    rank[0]=1.;d[0].movement.actor.position={12928,12928,0};permission={64,0,0,64,64};
    input.missionControl=[](int,int off){return off==9?1:0;};for(auto& [id,g]:admission.gates.objects){(void)id;g.owner=0;}
    admission.gates.houses[0]={0,1};admission.speedBits.fill(0x3f800000);admission.cells.at(0).occupation=1;
    input.grow=[&](int){admission.gates.cells.at(0).head=-1;return 1;};
    refused=false;try{call();}catch(const UnsupportedUnitScatter& e){refused=std::string(e.what()).find("ability17")!=std::string::npos;}
    admission.trace('?',0,0,0);admission.gates.trace('?',0);check(refused&&oldObservers==6&&global==7&&refs[0]==3&&!units[0].admissionMotion);
    std::cout<<checks<<" native Cell Unit Scatter ownership/refusal checks PASS\n";
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=4)throw std::invalid_argument("Expected private engine, direction and render data");
    const auto data=readDriveData(load(argv[1]),load(argv[2]));
    const auto render=readRenderData(load(argv[3]),PatchedEngineSha);
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);const char mode=take<char>(in);if(mode!='J')return 2;
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
        std::array<int,5> typeIds{0,1,2,3,4};
        std::vector<UnitScatterWorldView> worlds;worlds.reserve(5);std::array<UnitScatterWorldView*,5> views;
        for(int i=0;i<5;++i){
            UnitDestinationView unit{actors[i],drives[i],admission.gates.objects.at(i).mission,global,references[i]};
            worlds.push_back({unit,profiles[i],extras[i],admission,i,slots,cells[9],bindings,floor,floorHeight,layerHeight,shape,pool});views[i]=&worlds.back();
        }
        const auto event=[](auto... v){((std::cout<<v<<' '),...);};ScatterWorldTrace trace=event;
        CellUnitScatterView world{admission,views,ranks,typeIds,eligibility,shortTracks,types,house194,rule,threshold};
        for(const auto& action:actions){
            const Coord point{action[0],action[1],action[2]};admission.gates.tick=action[5];std::size_t grows=0;
            CellUnitScatterInputs input{*data,[&](double n){return tableSqrt(render,n);},random,neighbors,paddings,projectHeight,action[5],delay,0.30000001192092896,
                [&](int,int off){return off==9?control9:control7;},[&](int){return growth[grows++%growth.size()];},[](int){}};
            scatterCellUnitsOnMap(cell,point,std::uint8_t(action[3]),std::uint8_t(action[4]),elevated,world,input,trace);
        }
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
        for(int i=0;i<5;++i)event(i,admission.gates.objects.at(i).next,std::bit_cast<std::uint64_t>(ranks[i]));std::cout<<'\n';
    }return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
