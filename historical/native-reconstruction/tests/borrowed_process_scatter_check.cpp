// SPDX-License-Identifier: GPL-3.0-or-later
#include "borrowed_admission_fixture.hpp"
#include "assets/BorrowedCellUnitScatterWorld.hpp"
#include "assets/ProcessTerminalScatterWorld.hpp"
#include <iostream>
using namespace ra2;
int main(){try{
    int checks=0;const auto check=[&](bool value){++checks;if(!value)throw std::runtime_error("Borrowed Process check "+std::to_string(checks));};
    const auto refuses=[&](const auto& f){bool caught=false;try{f();}catch(const std::invalid_argument&){caught=true;}check(caught);};
    std::vector<int> slots(262144,-1);slots[513]=0;slots[514]=1;
    UnitAdmissionWorld source;source.gates.slots=slots;source.gates.fallbackCell=2;
    source.gates.houses[0]={0,0};source.speedBits.fill(0x3f800000);
    for(int i=0;i<3;++i){source.cells[i]={};source.gates.cells[i]={{std::int16_t(1+i),1},-1};}
    for(int i=0;i<2;++i){source.objects[i]={};source.gates.objects[i].owner=0;source.gates.objects[i].mission.mission98=2;}
    DriveData data;data.directionsToTargets.slopeStep=1.;UnitAdmissionMotionWorld motion;motion.data=&data;motion.squareRoot=[](double n){return n;};
    for(int i=0;i<2;++i){motion.actors[i].position={384+256*i,384,0};motion.actors[i].eligibility5a0=1;motion.actors[i].track=-1;motion.actors[i].queueHead=-1;}
    test::BorrowedAdmissionFixture f(source,motion);auto& w=f.admission->world();
    std::array<UnitDestinationProfile,2> profiles;std::array<UnitScatterExtra,2> extras;
    std::array<std::uint32_t,2> refs{3,5};std::uint32_t global=7;
    int height=104,layerHeight=104;MapPermissionShape shape{8,0,0,8,8};
    std::array<ScatterWorldCellBinding,3> bindings{{{&f.attributes[0].input,0,0},{&f.attributes[1].input,1,0},{&f.attributes[2].input,2,0}}};
    std::array<BorrowedUnitScatterWorldView,2> units{{
        {{f.actors[0].destination,f.drives[0],f.member->discovery,global,refs[0]},profiles[0],extras[0],w,0,f.table,f.attributes[2].input,bindings,f.floor,height,layerHeight,shape,{}},
        {{f.actors[1].destination,f.drives[1],f.mission1,global,refs[1]},profiles[1],extras[1],w,1,f.table,f.attributes[2].input,bindings,f.floor,height,layerHeight,shape,{}}
    }};
    std::array<BorrowedUnitScatterWorldView*,2> views{&units[0],&units[1]};
    std::array<double,2> ranks{};std::array<int,2> typeIds{},padding{};
    std::map<int,CellScatterType> types{{0,{}}};std::map<int,int> houses{{0,0}},speeds{{0,1}};std::uint8_t rule=1;int threshold=0;
    BorrowedCellUnitScatterView world{w,views,ranks,typeIds,{},{},types,houses,rule,threshold,&f.admission->motion()};
    OriginalRandomState random;
    CellUnitScatterInputs input{data,f.squareRoot,random,{},padding,104,100,5,0.3,[](int,int){return 0;},[](int){return 1;},[](int){}};
    int dimension1=0,frame=100,overlay=-1;NearbyLocationPoint empty{};NearbyAdmissionServices nearbyAdmission;
    std::function<NearbyAdmissionCell(const MapCellInput&)> bind=[&](const auto& c){return NearbyAdmissionCell{c,f.member->occupation[2].ground,f.member->occupation[2].elevated,overlay};};
    CellNearbySearchInputs nearby{speeds,dimension1,frame,empty,bind,nearbyAdmission};
    std::array<std::uint8_t,2> onMap{1,1},flag76{},flag7a{},flag61{},curve{};
    int queryCount=0,effects=0;GroundDriveProcessServices services;
    const auto record=[&](Coord){++queryCount;const auto& c=f.attributes[0].input;return GroundDriveCell{c.position.x,c.position.y,c.level,c.slope,c.land,&c};};
    services.cell=record;services.wordCell=[&](std::int16_t,std::int16_t){return record({});};
    services.liveCell=[&](const void*){return record({});};services.center=[](const GroundDriveCell&){return Coord{};};
    services.markNext=[](auto,auto){};services.markOccupation=[](auto){};services.noRoute=[]{};services.squareRoot=f.squareRoot;
    services.advance.ground.floor=[](Coord){return 0;};services.advance.ground.mark=[](int){};
    services.advance.coordinateCell=[&](Coord)->const void*{return &f.attributes[0].input;};
    services.advance.wordCell=[](auto,auto){};services.advance.unmarkOccupation=[](Coord){};
    services.advance.notify=[](int){};services.advance.postCell=[]{};
    GroundDriveAdvanceAdmissionServices admission;admission.cell=services.cell;admission.wordCell=services.wordCell;admission.check=[](const auto&,int,int){return 0;};
    AdvanceTerminalServices effect;effect.mission414=[&](int,int){++effects;return std::uint8_t(0);};
    GroundDriveMovingWaitServices wait;wait.failedRoute=[](int){};std::uint32_t scratch=0xabcddcba;
    const auto call=[&](int i,std::uint8_t& shortTrack){return processWithTerminalScatter(i,0,7,104,services,admission,
        [&](auto x,auto y){return f.admission->gates(i,{x,y});},{11,13},wait,scratch,world,input,nearby,
        {onMap[i],flag76[i],flag7a[i]},effect,{shortTrack,flag61[i],curve[i]},{});};
    check(!f.queries&&!f.stores&&!queryCount);
    // Actual prepared records for both native entries. This is deliberately
    // not presented as original Process1 or drawing evidence.
    for(int i:{0,1,0}){
        const auto other=f.drives[1-i].movement.actor.position;
        const auto target=f.actors[1-i].destination.target494;
        f.actors[i].destination.target494=&f.attributes[i].input;
        f.actors[i].destination.vectorCount=1;f.actors[i].destination.field490=17;
        check(!call(i,f.actors[i].shortTrack)&&!f.actors[i].destination.target494&&!f.actors[i].destination.field490);
        check(f.drives[1-i].movement.actor.position==other&&f.actors[1-i].destination.target494==target);
    }
    check(effects==3&&refs[0]==3&&refs[1]==5&&global==7&&scratch==0xabcddcba);
    // The actual production timer owners replace, rather than synchronize with,
    // the legacy destination arrays. Poison those arrays and retain both actors.
    std::array<GroundDriveMovingWaitState,2> waits;
    std::array<int,2> targetStores{};
    for(int i:{0,1}){
        auto& d=f.drives[i];auto& u=units[i].unit;
        u.retry530.emplace(GroundDriveTimerView{d.retryStart,d.retryPadding,d.retryRemaining});
        u.wait558.emplace(GroundDriveTimerView{waits[i].start,waits[i].padding,waits[i].remaining});
        u.targetStore=[&,i](const void* target){check(!target);++targetStores[i];};
        f.actors[i].destination.timer530=f.actors[i].destination.timer558={-171,391,811};
        f.actors[i].destination.target494=&f.attributes[i].input;
        f.actors[i].destination.vectorCount=0;
        check(!call(i,f.actors[i].shortTrack));
        check(d.retryStart==100&&d.retryPadding==0&&d.retryRemaining==0&&
            waits[i].start==100&&waits[i].padding==0&&waits[i].remaining==5);
        check(f.actors[i].destination.timer530==std::array<int,3>{-171,391,811}&&
            f.actors[i].destination.timer558==std::array<int,3>{-171,391,811});
    }
    check(targetStores==std::array<int,2>{1,1});
    // Reissuing an identical target is still a command. Queue consumption
    // alone must never request a fresh supplied route.
    UnitDestinationServices dest;
    dest.targetId=[](const void*){return 1;};dest.coordinates=[](const void*){return Coord{384,384,0};};
    dest.cellFlags=[](Coord){return 0u;};
    int assigned=0;auto u=units[0].unit;const auto* target=&f.attributes[0].input;
    u.targetStore=[&](const void* p){check(p==target);++assigned;};
    for(int n=0;n<2;++n)setOrdinaryFootDestination(u,target,profiles[0],{100,7,5,{},.3},dest);
    check(assigned==2);
    const int before=queryCount;std::uint8_t copy=0;refuses([&]{call(0,copy);});
    f.actors[0].shortTrack=1;refuses([&]{call(0,f.actors[0].shortTrack);});f.actors[0].shortTrack=0;
    const auto* live=world.liveMotion;world.liveMotion=nullptr;refuses([&]{call(0,f.actors[0].shortTrack);});world.liveMotion=live;
    std::array<std::uint8_t,2> copied{};world.shortTrack=copied;refuses([&]{call(0,f.actors[0].shortTrack);});world.shortTrack={};
    world.eligibility5a0=copied;refuses([&]{call(0,f.actors[0].shortTrack);});world.eligibility5a0={};
    UnitDestinationState mirror;BorrowedUnitScatterWorldView split{{mirror,f.drives[0],f.member->discovery,global,refs[0]},profiles[0],extras[0],w,0,f.table,f.attributes[2].input,bindings,f.floor,height,layerHeight,shape,{}};
    views[0]=&split;refuses([&]{call(0,f.actors[0].shortTrack);});views[0]=&units[0];
    GroundDriveProcessState mirrorDrive;
    BorrowedUnitScatterWorldView splitDrive{{f.actors[0].destination,mirrorDrive,f.member->discovery,global,refs[0]},profiles[0],extras[0],w,0,f.table,f.attributes[2].input,bindings,f.floor,height,layerHeight,shape,{}};
    views[0]=&splitDrive;refuses([&]{call(0,f.actors[0].shortTrack);});views[0]=&units[0];
    check(queryCount==before&&effects==3);
    int forwards=0;const int prior=f.fallbackStores;const auto trace=[&](char g,char k,auto,auto,auto){if(g=='w'&&k=='W'){
        ++forwards;const auto p=f.attributes[2].input.position;
        check(f.member->cellMembership(2).point==TerrainCellPoint{p.x,p.y}&&f.member->visibilityCells.back().point==TerrainCellPoint{p.x,p.y});
    }};
    scatterAdvanceCellOnMap({-257,-511,0},{-257,-511,0},{-513,-767,0},104,scratch,world,input,nearby,trace);
    check(forwards==2&&f.fallbackStores-prior==forwards&&scratch==0xabcddc00);
    std::cout<<checks<<" borrowed Process/Advance ownership and refusal checks PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
