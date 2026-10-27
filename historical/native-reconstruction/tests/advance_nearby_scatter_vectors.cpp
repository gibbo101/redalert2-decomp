// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/AdvanceNearbyScatterWorld.hpp"
#ifdef RA2_ADVANCE_TERMINAL
#include "assets/AdvanceTerminalScatterWorld.hpp"
#endif
#include "render/RampGeometry.hpp"
#include <cfenv>
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
    std::array<UnitDestinationState,2> actors;std::array<GroundDriveProcessState,2> drives;
    std::array<UnitDestinationProfile,2> profiles;std::array<UnitScatterExtra,2> extras;
    std::array<std::uint32_t,2> refs{3,5};std::uint32_t global=7;
    UnitAdmissionWorld admission;std::vector<int> ids(262144,-1);admission.gates.slots=ids;admission.gates.fallbackCell=0;
    admission.cells[0];admission.gates.cells[0].head=0;admission.gates.objects[0].next=1;
    for(int i=0;i<2;++i){admission.objects[i];admission.gates.objects[i].mission.mission98=i?7:2;drives[i].movement.actor.position={12928+i*256,12928,0};drives[i].route.fill(27);}
    std::vector<MapCellInput*> slots(262144);MapCellInput fallback;fallback.position={7,9};fallback.land=1;MapFloorHeightState floor;floor.planes[0].x=1.;
    int h=104,layer=104;MapPermissionShape permission{64,0,0,64,64};DriveData data;data.directionsToTargets.slopeStep=1.;OriginalRandomState random;
    random.table.fill(37);random.next1=9;random.next2=17;const auto initial=random;
    std::array<ScatterWorldCellBinding,1> bindings{{{&fallback,0,0}}};
    std::array<UnitScatterWorldView,2> units{{
        {{actors[0],drives[0],admission.gates.objects[0].mission,global,refs[0]},profiles[0],extras[0],admission,0,slots,fallback,bindings,floor,h,layer,permission,{}},
        {{actors[1],drives[1],admission.gates.objects[1].mission,global,refs[1]},profiles[1],extras[1],admission,1,slots,fallback,bindings,floor,h,layer,permission,{}}
    }};
    std::array<UnitScatterWorldView*,2> views{&units[0],&units[1]};std::array<double,2> ranks{};std::array<int,2> typeIds{0,0},padding{};
    std::array<std::uint8_t,2> eligibility{1,1},shortTrack{};std::map<int,CellScatterType> types{{0,{}}};std::map<int,int> houses{{0,0}},speeds{{0,1}};
    std::uint8_t rule=1;int threshold=0,dimension1=-64,frame=1,overlay=-1;NearbyLocationPoint empty{};
    CellUnitScatterView world{admission,views,ranks,typeIds,eligibility,shortTrack,types,houses,rule,threshold};
    int queries=0,grows=0,releases=0,requests=0,observed=0,checks=0;const auto check=[&](bool ok){++checks;if(!ok)throw std::runtime_error("Cell nearby guard "+std::to_string(checks));};
    admission.trace=[&](char,int,int,int){++observed;};admission.gates.trace=[&](char,int){++observed;};
    std::array<std::uint32_t,108> bits;bits.fill(0x3f800000);NearbyAdmissionServices nearbyAdmission;nearbyAdmission.speedBits=bits;
    std::function<NearbyAdmissionCell(const MapCellInput&)> bind=[&](const auto& c){return NearbyAdmissionCell{c,admission.cells[0].occupation,admission.cells[0].elevatedOccupation,overlay};};
    CellNearbySearchInputs nearby{speeds,dimension1,frame,empty,bind,nearbyAdmission};
    CellUnitScatterInputs input{data,[](double n){return n;},random,{},padding,104,100,5,0.3,[](int,int off){return off==9;},[&](int){++grows;return 1;},[&](int){++releases;}};
    const auto trace=[&](char g,char k,auto,auto,auto){if(g=='w'&&k=='L')++queries;};
    const auto nearTrace=[&](char k,auto,const auto*,int n){if(k=='S'){++requests;if(n!=speeds.at(0))throw std::runtime_error("Captured type speed");}};
    const auto call=[&](){scatterCellUnitsWithNearbyOnMap(0,{},1,1,0,world,input,nearby,trace,nearTrace);};
    check(!queries&&!requests&&!grows&&!floor.flags);call();
    check(requests==2&&grows==1&&releases==1&&queries==2&&!floor.flags&&refs[0]==3&&refs[1]==5&&global==7);
    admission.trace('?',0,0,0);admission.gates.trace('?',0);check(observed==2&&!units[0].admissionMotion&&!units[1].admissionMotion);
    speeds.clear();bool refused=false;try{call();}catch(const std::invalid_argument&){refused=true;}check(refused&&grows==1);speeds[0]=1;
    views[1]=nullptr;refused=false;try{call();}catch(const std::invalid_argument&){refused=true;}check(refused&&grows==1);views[1]=&units[1];
    UnitDestinationView mirrored{actors[1],drives[0],admission.gates.objects[1].mission,global,refs[1]};
    UnitScatterWorldView bad{mirrored,profiles[1],extras[1],admission,1,slots,fallback,bindings,floor,h,layer,permission,{}};
    views[1]=&bad;refused=false;try{call();}catch(const std::invalid_argument&){refused=true;}check(refused&&grows==1);views[1]=&units[1];
    dimension1=0;input.grow=[&](int){++grows;speeds[0]=4;return 1;};call();
    check(requests==4&&drives[0].destination==Coord{12928,12928,0}&&drives[1].destination==Coord{13184,12928,0}&&refs[0]==3&&refs[1]==5&&global==7);
    check(drives[0].route[0]==-1&&std::all_of(drives[0].route.begin()+1,drives[0].route.end(),[](int n){return n==27;})&&std::all_of(drives[1].route.begin(),drives[1].route.end(),[](int n){return n==27;}));
    check(random.next1==initial.next1&&random.next2==initial.next2&&random.table==initial.table);
    nearbyAdmission.trace=[](auto,const auto&,int,int,int,int,int,int,std::uint32_t){throw std::runtime_error("unrelated");};
    const int beforeRelease=releases;bool fault=false;try{call();}catch(const std::runtime_error& e){fault=std::string(e.what())=="unrelated";}
    admission.trace('?',0,0,0);admission.gates.trace('?',0);check(fault&&releases==beforeRelease&&observed==4&&refs[0]==3&&refs[1]==5&&global==7&&!units[0].admissionMotion);nearbyAdmission.trace={};
    refused=false;try{scatterCellUnitsOnMap(0,{},1,1,0,world,input);}catch(const UnsupportedUnitScatter&){refused=true;}check(refused&&refs[0]==3&&refs[1]==5&&global==7);
    std::uint32_t scratch=0xaabbccddu;std::vector<Coord> blockQueries;bool dispatched=false;
    const Coord candidate{27,-517,4};
    const auto blockTrace=[&](char g,char k,std::int64_t x,std::int64_t y,std::int64_t z){
        if(g=='g'&&k=='S')dispatched=true;
        if(g=='w'&&k=='K'&&!dispatched){
            blockQueries.push_back({int(x),int(y),int(z)});
            if(blockQueries.size()==2&&fallback.flags){
                drives[0].movement.actor.position.z=-312;
                drives[0].movement.head={321,654,9};
            }
        }
    };
    const auto block=[&](int divisor){scatterAdvanceCellOnMap(candidate,
        drives[0].movement.actor.position,drives[0].movement.head,divisor,scratch,
        world,input,nearby,blockTrace,nearTrace);};
    refused=false;try{block(0);}catch(const std::invalid_argument&){refused=true;}
    check(refused&&scratch==0xaabbccddu&&blockQueries.empty());
    fallback.flags=0x100;fallback.level=-1;admission.cells[0].elevatedHead=1;
    drives[0].movement.actor.position.z=312;drives[0].movement.head={123,456,7};block(104);
    check(scratch==0xaabbcc01u&&blockQueries==std::vector<Coord>{candidate,candidate,{321,654,9}});
    check(refs[0]==3&&refs[1]==5&&global==7&&!units[0].admissionMotion);
    blockQueries.clear();dispatched=false;fallback.flags=0;scratch=0xffffff01u;block(104);
    check(scratch==0xffffff00u&&blockQueries==std::vector<Coord>{candidate,{321,654,9}});
    fallback.flags=0x100;fallback.level=0;drives[0].movement.actor.position.z=-207;
    blockQueries.clear();dispatched=false;scratch=0x123456ffu;block(104);
    check(scratch==0x12345600u&&blockQueries.size()==3);
    data.transitions[0]={1,0,27,0};data.transitions[2]={2,0,0,0};
    data.tracks[0].points={{0,0,0},{1,1,0},{2,2,0},{0,0,0}};
    data.tracks[0].jumpIndex=1;data.tracks[1].entryIndex=1;
    fallback.flags=0;fallback.level=0;admission.gates.cells[0].head=-1;
    speeds[0]=1;input.grow=[](int){return 1;};
    GroundDriveAdvanceServices svc;int identity=0;
    svc.ground.floor=[](Coord){return 0;};svc.ground.mark=[](int){};
    svc.coordinateCell=[&](Coord)->const void*{return &identity;};svc.wordCell=[](std::int16_t,std::int16_t){};
    svc.unmarkOccupation=[](Coord){};svc.notify=[](int){};svc.postCell=[]{};
    GroundDriveAdvanceAdmissionServices admit;
    admit.cell=[&](Coord){GroundDriveCell c;c.level=0;return c;};
    admit.wordCell=[&](std::int16_t,std::int16_t){GroundDriveCell c;c.identity=&identity;return c;};
    for(int code:{0,2,6,7,1,3,4,5,-1,8}){
        auto& state=drives[0].movement;state={};state.actor.position={128,128,0};state.head={128,128,0};state.driving=true;state.track=0;state.index=1;state.accumulator=8;
        drives[0].route.fill(23);drives[0].route[0]=2;scratch=0xabcd1234;bool checked=false;int indexStores=0;
        svc.driveStore=[&](int off,int){if(off==0x5c)++indexStores;};
        admit.check=[&](const auto&,int direction,int level){check(direction==2&&level==0&&state.index==1&&scratch==0xabcd1b00);checked=true;return code;};
        refused=false;try{advanceWithNearbyScatter(0,0,1.,false,svc,admit,104,scratch,world,input,nearby);}
        catch(const UnsupportedGroundAdmission& e){refused=true;check(e.result==code);}
        const bool supported=code==0||code==2||code==6||code==7;
        check(checked&&refused!=supported&&state.index==(supported?2:1)&&indexStores==int(supported));
        check(std::all_of(drives[0].route.begin()+1,drives[0].route.end(),[](int n){return n==23;}));
    }
    const auto oldPosition=drives[0].movement.actor.position;scratch=0xaabbccdd;
    refused=false;try{advanceWithNearbyScatter(0,0,1.,false,svc,{},104,scratch,world,input,nearby);}catch(const std::invalid_argument&){refused=true;}
    check(refused&&scratch==0xaabbccdd&&drives[0].movement.actor.position==oldPosition);
    admit.check=[](const auto&,int,int)->int{throw std::runtime_error("root-unrelated");};
    drives[0].movement.index=1;drives[0].movement.accumulator=8;
    fault=false;try{advanceWithNearbyScatter(0,0,1.,false,svc,admit,104,scratch,world,input,nearby);}catch(const std::runtime_error& e){fault=std::string(e.what())=="root-unrelated";}
    check(fault&&drives[0].movement.index==1&&refs[0]==3&&refs[1]==5&&global==7);
    drives[0].movement.index=3;drives[0].movement.accumulator=8;actors[0].target494=&fallback;
    refused=false;try{advanceWithNearbyScatter(0,0,1.,false,svc,admit,104,scratch,world,input,nearby);}catch(const UnsupportedUnitScatter&){refused=true;}
    check(refused&&actors[0].target494==&fallback&&drives[0].movement.track==-1&&drives[0].movement.index==0);
    actors[0].target494=nullptr;
#ifdef RA2_ADVANCE_TERMINAL
    std::uint8_t onMap=1,flag76=0,flag7a=0;AdvanceTerminalFlags flags{onMap,flag76,flag7a};
    AdvanceTerminalServices effects;effects.notify174=svc.notify;effects.postCell490=[]{return 0;};
    const auto resetTerminal=[&]{fallback.position={7,9};admission.gates.objects[0].mission.mission98=2;drives[0].destination={1920,2432,0};auto& m=drives[0].movement;m={};m.actor.position={1920+14,2432,0};m.head={1920,2432,0};m.track=0;m.index=3;m.accumulator=8;m.driving=true;drives[0].route.fill(23);drives[0].route[0]=-1;actors[0].target494=&fallback;};
    resetTerminal();refused=false;try{advanceWithTerminalScatter(0,0,1.,false,svc,admit,104,scratch,world,input,nearby,flags,effects);}catch(const UnsupportedAdvanceTerminal&){refused=true;}
    check(refused&&!actors[0].target494&&drives[0].route[0]==-1&&drives[0].route[23]==23);
    resetTerminal();effects.mission414=[](int a,int b){if(a||b!=1)throw std::logic_error("Mission arguments");return 255;};
    check(advanceWithTerminalScatter(0,0,1.,false,svc,admit,104,scratch,world,input,nearby,flags,effects)&&drives[0].movement.accumulator==8);
    resetTerminal();effects.mission414=[](int,int){return 0;};
    check(!advanceWithTerminalScatter(0,0,1.,false,svc,admit,104,scratch,world,input,nearby,flags,effects)&&drives[0].movement.accumulator==0);
    resetTerminal();effects.notify174=[&](int){onMap=0;};
    check(advanceWithTerminalScatter(0,0,1.,false,svc,admit,104,scratch,world,input,nearby,flags,effects)&&actors[0].target494==&fallback);
    std::cout<<checks<<" complete terminal Advance and legacy ownership/order/refusal checks PASS\n";
#else
    std::cout<<checks<<" native complete Advance and child ownership/order/refusal checks PASS\n";
#endif
}

int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=6)throw std::invalid_argument("Expected private engine, direction and render data");
    const auto data=readDriveData(load(argv[1]),load(argv[2]));
    const auto render=readRenderData(load(argv[3]),PatchedEngineSha);
    const auto raster=readRasterData(load(argv[4]),PatchedEngineSha);
    const auto geometry=readRampGeometryData(load(argv[5]),PatchedEngineSha);
    const auto stock=stockRampGeometry(render,raster,data->directionsToTargets,geometry);
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char rootTag=take<char>(in);
#ifdef RA2_ADVANCE_TERMINAL
        const bool terminalRecord=rootTag=='T';std::array<std::uint8_t,3> terminalFlags{1,0,0};
        int terminalMissionReturn=0,terminalPostReturn=0;std::array<int,3> terminalNotify{-1,-1,-1},terminalPost{-1,-1,-1};
        if(terminalRecord){for(auto& n:terminalFlags)n=std::uint8_t(number(in,0,255));terminalMissionReturn=number(in,0,255);terminalPostReturn=number(in,0,255);
            for(auto* flags:{&terminalNotify,&terminalPost}){for(auto& n:*flags)n=number(in,-1,255);if((*flags)[0]<0&&*flags!=std::array<int,3>{-1,-1,-1})throw std::invalid_argument("Malformed terminal effects");if((*flags)[0]>=0&&((*flags)[1]<0||(*flags)[2]<0))throw std::invalid_argument("Malformed terminal effects");}
            rootTag=take<char>(in);
        }
#endif
        if(rootTag!='F')throw std::invalid_argument("Expected complete Advance input");
        const int speed=number(in,0,255),acc=take<int>(in),driving=number(in,0,1),suppress=number(in,0,1),marked=number(in,0,255),markEffect=number(in,0,1);
        const double percentage=std::bit_cast<double>(take<std::uint64_t>(in));
        auto scratch=take<std::uint32_t>(in);const auto entryScratch=scratch;
        if(take<char>(in)!='N')return 2;
        const int dimension1=take<int>(in),fpMode=number(in,0,3);const int fpModes[]{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};std::fesetround(fpModes[fpMode]);
        std::map<int,int> speedTypes;for(int i=0;i<5;++i)speedTypes[i]=number(in,0,8);
        std::array<int,5> typeIds;for(auto& n:typeIds)n=number(in,0,4);
        std::array<std::uint32_t,108> nearbySpeeds;for(auto& n:nearbySpeeds)n=take<std::uint32_t>(in);
        const char mode=take<char>(in);if(mode!='J')return 2;
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
        paddings[0]=padding;for(int i=0;i<5;++i)drives[i].movement.reached5a0=eligibility[i];
        std::string tail;if(in>>tail)throw std::invalid_argument("Extra Cell join input");
        int heap=0;a.vectorBuffer=buffer?&heap:nullptr;a.target494=initialTarget?&cells[initialTarget-1]:nullptr;a.timer530=a.timer558={123,-91,17};drive.movement.reached5a1=173;
        drive.movement.actor.marked74=std::uint8_t(marked);drive.movement.accumulator=acc;drive.movement.driving=driving;drive.percentage=percentage;
        MapFloorHeightState floor;floor.planes[0].x=1.;std::array<TerrainCellPoint,128> pool;pool.fill({poolx,pooly});

        std::vector<UnitScatterWorldView> worlds;worlds.reserve(5);std::array<UnitScatterWorldView*,5> views;
        for(int i=0;i<5;++i){
            UnitDestinationView unit{actors[i],drives[i],admission.gates.objects.at(i).mission,global,references[i]};
            worlds.push_back({unit,profiles[i],extras[i],admission,i,slots,cells[9],bindings,floor,floorHeight,layerHeight,shape,pool});views[i]=&worlds.back();
        }
        const auto event=[](auto... v){((std::cout<<v<<' '),...);};ScatterWorldTrace trace=event;
        CellUnitScatterView world{admission,views,ranks,typeIds,eligibility,shortTracks,types,house194,rule,threshold};
        const auto cellId=[&](const MapCellInput& c){for(int i=0;i<10;++i)if(&c==&cells[i])return i;throw std::logic_error("Unknown nearby Cell");};
        int overlay=-1,frame=0;NearbyLocationPoint empty{};
        std::function<NearbyAdmissionCell(const MapCellInput&)> bind=[&](const auto& c){const auto& ac=admission.cells[cellId(c)];return NearbyAdmissionCell{c,ac.occupation,ac.elevatedOccupation,overlay};};
        NearbyAdmissionServices nearbyAdmission;nearbyAdmission.speedBits=nearbySpeeds;
        nearbyAdmission.trace=[&](char k,const auto& c,int a,int b,int d,int e,int f,int g,std::uint32_t h){if(k=='C')event('n',k,cellId(c),a,b,d,e,f,g,h);else event('n',k,a);};
        CellNearbySearchInputs nearby{speedTypes,dimension1,frame,empty,bind,nearbyAdmission};
        NearbyLocationMapTrace nearbyTrace=[&](char k,auto q,const auto* c,int n){
            if(k=='L')event('n',k,q.x,q.y,cellId(*c));else if(k=='B')event('n',k,cellId(*c),q.x,q.y,n);else if(k=='b')event('n',k,cellId(*c),n);
            else if(k=='t')event('n',k,n);else if(k=='S'||k=='A')event('n',k,q.x,q.y,n);else event('n',k,q.x,q.y);
        };
        for(const auto& action:actions){
            scratch=entryScratch;
            const Coord point{action[0],action[1],action[2]};admission.gates.tick=action[5];frame=action[5];std::size_t grows=0;
            CellUnitScatterInputs input{*data,[&](double n){return tableSqrt(render,n);},random,neighbors,paddings,projectHeight,action[5],delay,0.30000001192092896,
                [&](int,int off){return off==9?control9:control7;},[&](int){return growth[grows++%growth.size()];},[](int){}};
            if(point!=Coord{}||action[3]!=1||action[4]!=1)throw std::invalid_argument("Advance block requires its actual zero away/flags");
            (void)elevated;(void)cell;
            event("geometry");
            for(double value:{stock.diagonal,stock.diagonalPer60,stock.inverseDiagonalPer60,stock.angle45,stock.angle60,stock.angle90})event(std::bit_cast<std::uint64_t>(value));
            event(stock.levelHeight,std::bit_cast<std::uint64_t>(stock.diagonalTilt),std::bit_cast<std::uint64_t>(stock.axisTilt),stock.quadrupleHeight);
            event("directions");for(int i=0;i<8;++i){const auto [x,y]=directionOffset(i);event(x*256,y*256);}
            const auto fallback=[&](MapInputPosition q){
                cells[9].position=q;admission.gates.cells.at(9).point={q.x,q.y};
                event('w','W',std::uint32_t(std::uint16_t(q.x))|(std::uint32_t(std::uint16_t(q.y))<<16),0,0);
            };
            MapFloorHeightWorld map{slots,&cells[9],fallback};
            MapAttributeLookup words{slots,&cells[9],{},fallback};
            const auto coordinate=[&](Coord q)->MapCellInput&{event('w','K',q.x,q.y,q.z);return mapCoordinateCell(q,map,262144);};
            const auto word=[&](std::int16_t x,std::int16_t y)->MapCellInput&{event('w','L',x,y,0);return mapAttributeCell({x,y},words);};
            GroundDriveAdvanceServices services;
            services.ground.floor=[&](Coord q){event('w','F',q.x,q.y,q.z);const int h=mapFloorHeight(floor,floorHeight,q,map);event('w','f',h,0,0);return h;};
            services.ground.mark=[&](int kind){event('v','M',kind,int(drive.movement.actor.marked74),0);if(markEffect)drive.movement.actor.marked74=std::uint8_t(kind);};
            services.coordinateCell=[&](Coord q)->const void*{return &coordinate(q);};
            services.wordCell=[&](std::int16_t x,std::int16_t y){(void)word(x,y);};
            services.unmarkOccupation=[&](Coord q){event('v','U',q.x,q.y,q.z);};
            services.occupationEligible=[&]{return drive.movement.reached5a0;};
            services.notify=[&](int n){event('v','N',n,0,0);};services.postCell=[&]{event('v','P',0,0,0);};
            services.driveStore=[&](int off,int value){event('v','L',off,std::uint32_t(value),0);};
            const auto record=[](const MapCellInput& c){return GroundDriveCell{c.position.x,c.position.y,c.level,c.slope,c.land,&c};};
            GroundDriveAdvanceAdmissionServices admit;
            admit.cell=[&](Coord q){return record(coordinate(q));};
            admit.wordCell=[&](std::int16_t x,std::int16_t y){return record(word(x,y));};
            const auto oldTrace=admission.trace;const auto oldGate=admission.gates.trace;
            admission.trace=[&](char k,int a,int b,int c){if(k=='L')event('w','L',a,b,0);else if(k=='F')fallback({std::int16_t(a),std::int16_t(b)});else event('a',k,a,b,c);};
            admission.gates.trace=[&](char k,int a){event('a',k,a,0,0);};
            admit.check=[&](const GroundDriveCell& c,int direction,int level){
                const int id=cellId(*static_cast<const MapCellInput*>(c.identity));event('w','A',id,direction,level);
                UnitAdmissionMotionWorld motion;motion.data=data.get();motion.squareRoot=[&](double n){return tableSqrt(render,n);};
                for(int i=0;i<5;++i){const auto& d=drives[i];motion.actors[i]={d.movement.actor.position,d.destination,d.movement.head,d.movement.body,d.movement.reached5a0,d.route[0],d.movement.track,d.movement.index,shortTracks[i]};admission.objects.at(i).target=actors[i].target494?-2:-1;}
                const int result=movingUnitAdmission(0,id,direction,level,-1,1,admission,motion);event('w','a',result,0,0);return result;
            };
#ifdef RA2_ADVANCE_TERMINAL
            const auto effect=[&](const auto& values){if(values[0]>=0){for(int i=0;i<3;++i)terminalFlags[i]=std::uint8_t(values[i]);event('t','E',values[0],values[1],values[2]);}};
            AdvanceTerminalServices effects;
            effects.notify174=[&](int n){services.notify(n);effect(terminalNotify);};
            effects.postCell490=[&]{services.postCell();if(terminalRecord)event('t','P',terminalPostReturn,0,0);effect(terminalPost);return std::uint8_t(terminalPostReturn);};
            effects.mission414=[&](int a,int b){event('t','B',a,b,terminalMissionReturn);return std::uint8_t(terminalMissionReturn);};
            effects.missionQuery=[&](int n){event('t','M',n,0,0);};
            effects.store=[&](char owner,int off,int,std::uint32_t n){event('v',owner=='a'?'A':'L',off,n,0);};
            const bool returned=advanceWithTerminalScatter(0,speed,percentage,suppress,services,admit,stock.levelHeight,
                scratch,world,input,nearby,{terminalFlags[0],terminalFlags[1],terminalFlags[2]},effects,
                [&](int off,int value){event('v','A',off,std::uint32_t(value),0);},trace,nearbyTrace,
                [&](char k,int a,int b,int c){event('t',k,a,b,c);});
            if(terminalRecord)event("return",int(returned),int(terminalFlags[0]),int(terminalFlags[1]),int(terminalFlags[2]));
#else
            advanceWithNearbyScatter(0,speed,percentage,suppress,services,admit,stock.levelHeight,
                scratch,world,input,nearby,[&](int off,int value){event('v','A',off,std::uint32_t(value),0);},trace,nearbyTrace);
#endif
            admission.trace=oldTrace;admission.gates.trace=oldGate;
            event("scratch",scratch);
            const auto& f=drive.movement.body;
            event("moving",int(drive.movement.actor.marked74),int(drive.movement.reached5a0),f.desired,f.start,f.timerStart,f.duration,f.rate,std::bit_cast<std::uint64_t>(1.));
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
        for(int i=0;i<5;++i)event(i,admission.gates.objects.at(i).next,std::bit_cast<std::uint64_t>(ranks[i]));
        event("nearby-retained",dimension1);for(int i=0;i<5;++i)event(speedTypes[i],typeIds[i]);
        for(int i=0;i<10;++i){const auto& c=cells[i];const auto& ac=admission.cells[i];event(c.position.x,c.position.y,int(c.level),int(c.slope),c.flags,c.land,ac.occupation,ac.elevatedOccupation);}
        if(std::fegetround()!=fpModes[fpMode])throw std::runtime_error("Cell nearby caller FP mode changed");std::cout<<'\n';
    }return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
