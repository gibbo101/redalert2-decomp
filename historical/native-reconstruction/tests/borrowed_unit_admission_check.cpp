// SPDX-License-Identifier: GPL-3.0-or-later
#include "borrowed_admission_fixture.hpp"
#include <iostream>
#include <type_traits>
using namespace ra2;
namespace {
void require(bool ok,const char* why){if(!ok)throw std::runtime_error(why);}
template<class F> void refuses(F f){bool caught=false;try{f();}catch(const std::invalid_argument&){caught=true;}require(caught,"Expected borrowed-owner refusal");}
UnitAdmissionWorld initial(std::vector<int>& slots){
    UnitAdmissionWorld w;w.gates.slots=slots;w.gates.fallbackCell=2;
    w.gates.houses[0]={0,0};w.gates.houses[1]={1,0};
    w.speedBits.fill(0x3f800000);
    w.directions={{{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}}};
    for(int i=0;i<3;++i){w.cells[i]={};w.gates.cells[i]={{std::int16_t(1+i),1},-1};}
    for(int i=0;i<2;++i){w.objects[i]={};w.gates.objects[i].owner=0;w.gates.objects[i].mission.mission98=2;}
    w.gates.cells[0].head=1;return w;
}
}
int main(){try{
    static_assert(!std::is_copy_constructible_v<BorrowedPreparedUnitAdmission> && !std::is_move_constructible_v<BorrowedPreparedUnitAdmission>);
    std::vector<int> slots(262144,-1);slots[513]=0;slots[514]=1;
    auto input=initial(slots);DriveData data;data.directionsToTargets.slopeStep=1.;
    UnitAdmissionMotionWorld motion;motion.data=&data;motion.squareRoot=[](double x){return x;};
    for(int id:{0,1}){auto& m=motion.actors[id];m.position={384+256*id,384,0};m.body.rate=1792;}
    test::BorrowedAdmissionFixture f(input,motion);auto& binding=*f.admission;auto& w=binding.world();
    require(f.queries==0&&f.stores==0&&f.floor.flags==0,"Binding made world queries or warmed floors");
    require(&w.gates.objects.at(0).mission==&f.member->discovery&&&w.gates.objects.at(1).mission==&f.mission1&&
        &w.gates.objects.at(1).next==&f.member->membership.actors.at(1).next&&
        &w.gates.cells.at(0).head==&f.member->membership.cells.at(1000).head&&
        &w.cells.at(0).elevatedHead==&f.member->membership.cells.at(1000).alternateHead&&
        &w.cells.at(0).occupation==&f.member->occupation[0].ground&&
        &w.cells.at(0).flags==&f.attributes[0].input.flags&&
        &binding.motion().actors.at(1).body==&f.drives[1].movement.body&&
        &binding.motion().actors.at(1).queueHead==&f.drives[1].route[0],"Admission does not borrow actual owners");
    const auto admit=[&](){return binding.admit(0,0,2,0,1,1);};
    require(admit()==6,"Stationary actual Unit not admitted as result6");
    f.drives[1].destination={900,384,0};require(admit()==2,"Live Drive destination was snapshotted");
    f.drives[1].destination={};f.actors[1].destination.target494=&f.attributes[0].input;
    require(w.objects.at(1).targetIdentity()==-2&&admit()==2,"Cell target lost non-actor identity or live activity");
    f.actors[1].destination.target494=nullptr;require(admit()==6,"Cleared target remained active");
    f.member->discovery.mission98=7;f.actors[0].destination.target494=&f.drives[1];
    require(admit()==0,"Mission and actual actor target were not borrowed");
    f.actors[0].destination.target494=&f.attributes[0].input;
    require(admit()==6,"Cell identity aliased a Unit identity");
    f.member->discovery.mission98=2;f.actors[0].destination.target494=nullptr;
    f.mission1.owner=1;f.actors[1].state1b8=2;require(admit()==1,"Live House/state fields were snapshotted");
    f.mission1.owner=0;
    f.member->membership.cells.at(1000).head=-1;f.member->occupation[0].ground=32;
    require(admit()==2,"Live whole occupation word was snapshotted");
    f.member->occupation[0].ground=0x80000000u;require(admit()==0,"Upper occupation bits altered admission");
    f.shared.speedBits[0]=0;require(admit()==7,"Shared speed table was snapshotted");f.shared.speedBits[0]=0x3f800000;
    f.attributes[0].input.level=1;require(admit()==7,"Live signed Cell level was snapshotted");
    f.attributes[1].input.slope=1;require(admit()==0,"Live previous ramp was snapshotted");
    f.attributes[0].input.level=0;f.attributes[1].input.slope=0;
    f.member->membership.cells.at(1000).head=0;f.member->membership.actors.at(0).next=1;
    require(admit()==6,"Live Next list was snapshotted");
    f.member->membership.actors.at(0).next=-1;require(admit()==0,"Cleared Next list was snapshotted");
    // Actual missing-slot query forwards one store, before its read-only event,
    // updating the shared map, membership and visibility fallback immediately.
    int events=0;w.trace=[&](char k,int x,int y,int){if(k!='F')return;++events;
        require(f.attributes[2].input.position==MapInputPosition{std::int16_t(x),std::int16_t(y)}&&
            f.member->cellMembership(2).point==TerrainCellPoint{std::int16_t(x),std::int16_t(y)}&&
            f.member->visibilityCells.back().point==TerrainCellPoint{std::int16_t(x),std::int16_t(y)},"Fallback observer saw stale associated owners");};
    const int before=f.fallbackStores;
    require(unit_admission_policy::lookup({-7,9},w)==2&&events==1&&f.fallbackStores==before+1,"Fallback forwarded duplicate or missing stores");
    int level=-1;std::uint8_t elevated=255;binding.terrain(2,-1,level,elevated,-1);
    require(f.fallbackStores==before+2&&events==2&&level==-1&&elevated==255,"Repeated fallback or retained outputs differ");
    const int after=f.fallbackStores;binding.gates(0,{-11,-13});require(f.fallbackStores==after+1,"Gate fallback forwarded twice");
    binding.nextCell(0,{-15,-17},1);require(f.fallbackStores==after+2,"Next-Cell fallback forwarded twice");
    require(f.queries==0&&f.floor.flags==0,"Admission warmed lazy floors or queried membership world");
    int guardCount=0;const auto bad=[&](auto alter){auto associations=f.bindings();auto map=f.map();auto numeric=f.squareRoot;
        alter(associations,map,numeric);refuses([&]{BorrowedPreparedUnitAdmission reject(map,*f.member,associations,f.admissionCells,f.shared,data,numeric);});++guardCount;};
    GroundDriveProcessState other;UnitDiscoveryActor otherMission;
    bad([&](auto& a,auto&,auto&){a.erase(1);});
    bad([&](auto& a,auto&,auto&){a.erase(0);a.emplace(0,PreparedAdmissionActorBinding{other,f.member->discovery,f.actors[0]});});
    bad([&](auto& a,auto&,auto&){a.erase(1);a.emplace(1,PreparedAdmissionActorBinding{f.drives[1],otherMission,f.actors[1]});});
    bad([](auto&,auto& m,auto&){m.slots={};});bad([](auto&,auto&,auto& n){n={};});
    require(guardCount==5&&f.floor.flags==0,"Owner refusal altered lazy floor");
    std::cout<<"Actual borrowed mission/target/Drive/list/occupation/terrain/speed owners; no-query binding; single ordered fallback; five association refusals: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
