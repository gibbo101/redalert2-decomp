// SPDX-License-Identifier: GPL-3.0-or-later
#include "borrowed_admission_fixture.hpp"
#include "assets/BorrowedCellUnitScatterWorld.hpp"
#include <iostream>
using namespace ra2;
int main(){try{
    int checks=0;const auto check=[&](bool value){if(!value)throw std::runtime_error("Borrowed Cell ownership check "+std::to_string(checks));++checks;};
    const auto refuses=[&](const auto& f){bool caught=false;try{f();}catch(const std::invalid_argument&){caught=true;}check(caught);};
    std::vector<int> slots(262144,-1);slots[513]=0;slots[514]=1;
    UnitAdmissionWorld source;source.gates.slots=slots;source.gates.fallbackCell=2;
    source.gates.houses[0]={0,0};source.speedBits.fill(0x3f800000);
    source.directions={{{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}}};
    for(int i=0;i<3;++i){source.cells[i]={};source.gates.cells[i]={{std::int16_t(1+i),1},-1};}
    for(int i=0;i<2;++i){source.objects[i]={};source.gates.objects[i].owner=0;source.gates.objects[i].mission.mission98=0;}
    source.gates.cells[0].head=0;source.gates.objects[0].next=1;
    DriveData data;data.directionsToTargets.slopeStep=1.;UnitAdmissionMotionWorld motion;motion.data=&data;motion.squareRoot=[](double n){return n;};
    for(int i=0;i<2;++i){motion.actors[i].position={384+256*i,384,0};motion.actors[i].eligibility5a0=1;}
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
    std::array<double,2> ranks{};std::array<int,2> typeIds{},padding{};std::map<int,CellScatterType> types{{0,{}}};
    std::map<int,int> houses{{0,0}},speeds{{0,1}};std::uint8_t rule=1;int threshold=0;
    BorrowedCellUnitScatterView world{w,views,ranks,typeIds,{},{},types,houses,rule,threshold,&f.admission->motion()};
    OriginalRandomState random;random.next1=9;random.next2=17;random.table.fill(37);const auto initial=random;
    int grows=0,releases=0,dispatches=0,observed=0;
    w.trace=[&](char,int,int,int){++observed;};w.gates.trace=[&](char,int){++observed;};
    CellUnitScatterInputs input{data,f.squareRoot,random,{},padding,104,100,5,0.3,[](int,int off){return off==9;},[&](int){++grows;return 1;},[&](int){++releases;}};
    const auto call=[&](const ScatterWorldTrace& trace=ScatterWorldTrace{}){scatterCellUnitsOnMap(0,{1,0,0},0,0,0,world,input,trace);};
    check(!f.queries&&!f.stores&&!f.floor.flags);call([&](char g,char k,auto,auto,auto){if(g=='c'&&k=='S')++dispatches;});
    check(dispatches==2&&grows==1&&releases==1&&refs[0]==3&&refs[1]==5&&global==7&&!f.floor.flags);
    w.trace('?',0,0,0);w.gates.trace('?',0);check(observed==2&&!units[0].admissionMotion&&!units[1].admissionMotion);
    // Borrowed paths reject value refresh spans and split target/Drive owners.
    std::array<std::uint8_t,2> copiedEligibility{1,1};world.eligibility5a0=copiedEligibility;refuses(call);world.eligibility5a0={};
    const auto* live=world.liveMotion;world.liveMotion=nullptr;refuses(call);world.liveMotion=live;
    GroundDriveProcessState mirror;UnitDestinationState mirroredTarget;
    BorrowedUnitScatterWorldView splitDrive{{f.actors[1].destination,mirror,f.mission1,global,refs[1]},profiles[1],extras[1],w,1,f.table,f.attributes[2].input,bindings,f.floor,height,layerHeight,shape,{}};
    views[1]=&splitDrive;refuses(call);views[1]=&units[1];
    BorrowedUnitScatterWorldView splitTarget{{mirroredTarget,f.drives[1],f.mission1,global,refs[1]},profiles[1],extras[1],w,1,f.table,f.attributes[2].input,bindings,f.floor,height,layerHeight,shape,{}};
    views[1]=&splitTarget;refuses(call);views[1]=&units[1];check(grows==1);
    // Mutate only actual owners at the supplied snapshot allocation boundary.
    // The later original-style admission consumes these live fields directly.
    input.grow=[&](int){++grows;f.drives[1].route[0]=3;f.drives[1].destination={900,384,0};f.actors[1].destination.target494=&f.attributes[1].input;return 1;};
    call();check(f.admission->motion().actors.at(1).queueHead==3&&f.admission->motion().actors.at(1).destination==Coord{900,384,0}&&w.objects.at(1).targetIdentity()==-2);
    f.member->membership.cells.at(1000).head=1;check(f.admission->admit(0,0,2,0,1,1)==2);
    f.drives[1].destination={};f.actors[1].destination.target494=nullptr;check(f.admission->admit(0,0,2,0,1,1)==6);
    f.member->membership.cells.at(1000).head=0;
    int dimension1=-64,frame=1,overlay=-1;NearbyLocationPoint empty{};std::array<std::uint32_t,108> speed;speed.fill(0x3f800000);
    NearbyAdmissionServices admission;admission.speedBits=speed;
    std::function<NearbyAdmissionCell(const MapCellInput&)> bind=[&](const auto& c){
        int id=0;while(id<3&&&c!=&f.attributes[id].input)++id;
        if(id==3)throw std::runtime_error("Unknown prepared nearby Cell");
        return NearbyAdmissionCell{c,f.member->occupation[id].ground,f.member->occupation[id].elevated,overlay};
    };
    CellNearbySearchInputs nearby{speeds,dimension1,frame,empty,bind,admission};
    f.member->discovery.mission98=2;f.mission1.mission98=7;
    input.grow=[&](int){++grows;return 1;};int fallbackEvents=0;
    const auto trace=[&](char g,char k,auto packed,auto,auto){if(g!='w'||k!='W')return;++fallbackEvents;
        const auto p=f.attributes[2].input.position;
        check(std::uint32_t(packed)==(std::uint16_t(p.x)|(std::uint32_t(std::uint16_t(p.y))<<16))&&
            f.member->cellMembership(2).point==TerrainCellPoint{p.x,p.y}&&f.member->visibilityCells.back().point==TerrainCellPoint{p.x,p.y});
    };
    const int storesBefore=f.fallbackStores;
    // Missing source Cell forces the actual map root's physical store and one
    // immediate membership/visibility forward, before the read-only trace.
    f.drives[0].movement.actor.position={-257,-511,0};f.drives[1].movement.actor.position={-513,-767,0};
    scatterCellUnitsWithNearbyOnMap(0,{},1,1,0,world,input,nearby,trace);
    check(fallbackEvents>0&&f.fallbackStores-storesBefore==fallbackEvents&&random.next1==initial.next1&&random.next2==initial.next2&&random.table==initial.table);
    refuses([&]{f.member->forwardAssignedFallback({123,456});});
    const int releaseBefore=releases,observersBefore=observed;bool fault=false;
    try{scatterCellUnitsWithNearbyOnMap(0,{},1,1,0,world,input,nearby,[](char g,char k,auto,auto,auto){if(g=='w'&&k=='W')throw std::runtime_error("observer fault");});}
    catch(const std::runtime_error& e){fault=std::string(e.what())=="observer fault";}
    w.trace('?',0,0,0);w.gates.trace('?',0);check(fault&&releases==releaseBefore&&observed==observersBefore+2&&refs[0]==3&&refs[1]==5&&global==7&&!units[0].admissionMotion);
    std::cout<<checks<<" borrowed Cell/Unit/nearby ownership and refusal checks PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
