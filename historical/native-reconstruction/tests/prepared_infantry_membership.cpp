// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/PreparedInfantryMembership.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::runtime_error("Prepared Infantry membership ownership check failed");}
template<class F>void refuses(F f){bool caught=false;try{f();}catch(const std::invalid_argument&){caught=true;}require(caught);}
struct Actor {
    ActorGroundState ground{{128,128,0}};WalkMovementState walk;
    int next=-1,house=3,owner=7,image=17;
    std::uint8_t eligible=255,typeMap=1,redraw=0,limbo=0,special=0;
    InfantryMembershipActor view(){return {ground,walk,next,eligible,typeMap,{ground.marked74,redraw,limbo,special},house,owner,image};}
};
}
int main(){try{
    std::array<MapFinalizationCell,2> seed{};
    seed[0].attributes.input.position={0,0};seed[1].attributes.input.position={1,0};
    std::vector<int> slots(262144,-1);slots[0]=0;slots[1]=1;
    MapCellAttributes fallback;fallback.input.position={-31,17};MapFloorHeightState cold;
    std::array<int,16> land{};std::array<float,11> speeds{};ResidentCellInputs resident;
    resident.landMap=land;resident.wheelSpeeds=speeds;Bytes b4(4*4*4),b10(4*4*10);
    MutableUnitMap map({seed,slots,fallback,cold,resident,b4,b10,2,1,104});
    std::array<InfantryMembershipCell,3> cells;Actor a,b;
    cells[0].ground=0xaabbcc00;cells[0].elevated=0x11223300;
    UnitFoundationState foundation;int threshold=128;int numeric=0;
    const auto squareRoot=[&](double x){++numeric;return std::sqrt(x);};
    PreparedInfantryMembership member(map,cells,{{0,a.view()},{1,b.view()}},foundation,threshold,squareRoot);
    require(!map.floor.flags&&!numeric&&cells[0].head==-1&&foundation.objectFlag==0&&foundation.unitFlag==0);
    auto& w=member.world();int visible=0,notified=0,recalculated=0,redraws=0,lastCell=-1;
    w.services.visible=[&](const Coord& p){++visible;require(p==Coord{128,128,0});return 1;};
    w.services.notify=[&](int,int){++notified;};w.services.recalculate=[&](int id,int arg){require(arg==-1);++recalculated;lastCell=id;};
    w.services.occupation=[](int,const Coord&,bool){throw std::logic_error("Infantry membership entered occupation");};
    member.redrawMap=[&]{++redraws;};
    require(member.mark(0,1)&&a.ground.marked74&&a.redraw&&cells[0].head==0&&a.next==-1);
    require(member.mark(1,1)&&b.ground.marked74&&cells[0].head==1&&b.next==0);
    require(member.mark(0,0)&&!a.ground.marked74&&cells[0].head==1&&b.next==-1&&a.next==-1);
    require(visible==2&&!notified&&recalculated==3&&lastCell==0&&redraws==2&&!numeric);
    require(cells[0].ground==0xaabbcc00&&cells[0].elevated==0x11223300&&cells[0].groundHouse==-1);
    // Explicit Walk occupation children consume those same Cell/House owners;
    // they are separate from Mark and preserve the upper occupation bytes.
    member.occupy(0,a.ground.position);require(cells[0].ground==0xaabbcc01&&cells[0].groundHouse==3&&numeric==1);
    a.house=9;member.occupy(0,{192,192,0});require(cells[0].ground==0xaabbcc11&&cells[0].groundHouse==9);
    member.release({192,192,0});require(cells[0].ground==0xaabbcc01&&cells[0].groundHouse==-1);
    // Notification mutates the actual actor and removes the saved slot. The
    // list stays on the original Cell; recalculation reloads into the fallback.
    w.services.visibilityGate=1;
    w.services.notify=[&](int id,int){require(id==0);++notified;a.ground.position={384,128,37};a.eligible=0;map.slots[0]=-1;map.table[0]=nullptr;};
    require(member.mark(0,1)&&cells[0].head==0&&a.next==1&&b.next==-1);
    require(a.ground.position==Coord{384,128,37}&&!a.eligible&&lastCell==2&&map.fallback.input.position==MapInputPosition{0,0});
    require(cells[0].ground==0xaabbcc01&&cells[1].head==-1&&numeric==3);
    // A split map association refuses instead of silently selecting a second
    // source of membership truth. No list mutation occurs before this refusal.
    map.slots[0]=0;map.table[0]=&map.cells[1].attributes.input;
    refuses([&]{w.mapInsert(0,{0,0});});require(cells[0].head==0&&a.next==1);
    map.table[0]=&map.cells[0].attributes.input;
    // Borrowed Cell centers snapshot point words before the floor callback.
    // The second visibility center is independently recomputed from live words.
    w.services.visibilityGate=0;int centers=0;std::vector<Coord> points;
    w.services.centerFloor=[&](int){if(++centers==1)map.cells[0].attributes.input.position={1,0};return centers;};
    w.services.visible=[&](const Coord& p){points.push_back(p);return 0;};
    w.services.visibleSecondary=[&](const Coord& p){points.push_back(p);return 1;};
    w.cellInsert(1,0);require(points==std::vector<Coord>{{128,128,1},{384,128,2}});
    // Clones must create fresh associations. No source Cell, Walk, Next or
    // Mark reference can be reused as a hidden mutable projection.
    auto clone=map.clone();auto copiedCells=cells;Actor copyA=a,copyB=b;UnitFoundationState copiedFoundation=foundation;
    PreparedInfantryMembership copied(*clone,copiedCells,{{0,copyA.view()},{1,copyB.view()}},copiedFoundation,threshold,squareRoot);
    copied.world().actors.at(0).next=-1;copiedCells[0].head=-1;clone->cells[0].attributes.input.level=7;
    require(a.next==1&&cells[0].head==0&&map.cells[0].attributes.input.level==0&&&copied.world().actors.at(0).position!=&a.ground.position);
    refuses([&]{member.walkMap().attributes(copied.walkMap().word({0,0}));});
    refuses([&]{PreparedInfantryMembership bad(map,cells,{{0,a.view()},{1,a.view()}},foundation,threshold,squareRoot);});
    InfantryMembershipActor wrong{a.ground,a.walk,a.next,a.eligible,a.typeMap,{b.ground.marked74,a.redraw,a.limbo,a.special},a.house,a.owner,a.image};
    refuses([&]{PreparedInfantryMembership bad(map,cells,{{0,wrong}},foundation,threshold,squareRoot);});
    // Original473C58 reads the mode after visibility;473C61 loads the House
    // only on the notify path. Scalar diagnostic fields must not shadow owners.
    int liveGate=0,liveHouse=3,gateReads=0,houseReads=0,notifications=0;
    w.services.visibilityGate=0;w.services.notificationArgument=-777;
    w.services.liveVisibilityGate=[&]{++gateReads;return liveGate;};
    w.services.liveNotificationArgument=[&]{++houseReads;return liveHouse;};
    w.services.visible=[&](const Coord&){liveGate=-1;liveHouse=9;return 1;};
    w.services.notify=[&](int id,int house){require(id==0&&house==liveHouse);++notifications;};
    cells[0].head=-1;a.next=-1;w.cellInsert(0,0);
    require(gateReads==1&&houseReads==1&&notifications==1);
    liveGate=0;w.services.visibilityGate=-1;w.services.visible=[](const Coord&){return 1;};
    cells[0].head=-1;a.next=-1;w.cellInsert(0,0);
    require(gateReads==2&&houseReads==1&&notifications==1);
    w.services.visible=[](const Coord&){return 0;};w.services.visibleSecondary=[](const Coord&){return 0;};liveHouse=7;
    cells[0].head=-1;a.next=-1;w.cellInsert(0,0);
    require(gateReads==2&&houseReads==2&&notifications==2);
    w.services.liveVisibilityGate={};w.services.liveNotificationArgument={};
    // Recalculation must consume the current actual primary list and write
    // only the selected buffer bytes. No copied empty-occupant shortcut.
    map.cells[0].attributes.input.position={0,0};map.resident.permission={-1,-1,0,2,2};
    std::array<float,11> fast;fast.fill(1.f);map.resident.wheelSpeeds=fast;
    cells[0].head=0;a.next=1;b.next=-1;
    auto& attribute=map.cells[0].attributes;attribute.passability=17;attribute.input.level=0;
    std::fill(map.buffer4.begin(),map.buffer4.end(),0xa5);std::fill(map.buffer10.begin(),map.buffer10.end(),0x5a);
    int passStores=0;ResidentCellServices observed;
    observed.passabilityStore=[&](int value){++passStores;require(value==0&&attribute.passability==0&&cells[0].head==0&&a.next==1);};
    member.recalculate(0,-1,observed);require(passStores==1&&attribute.passability==0);
    for(std::size_t i=0;i<map.buffer4.size();++i)require(map.buffer4[i]==(i<2?0:0xa5));
    for(std::size_t i=0;i<map.buffer10.size();++i)require(map.buffer10[i]==(i==8?0:0x5a));
    // A changed live Next must be seen, and a cycle must refuse. Permission's
    // early return still bypasses that cycle, matching the complete original.
    b.next=0;refuses([&]{member.recalculate(0,-1);});
    map.resident.permission={};member.recalculate(0,-1);require(attribute.passability==7&&map.buffer4[0]==7);
    map.resident.permission={-1,-1,0,2,2};b.next=-1;
    w.actors.at(0).kind=6;refuses([&]{member.recalculate(0,-1);});w.actors.at(0).kind=15;
    // Fallback root returns without touching its passability or buffer tails.
    const auto saved4=map.buffer4,saved10=map.buffer10;map.fallback.passability=93;
    member.recalculate(2,-1);require(map.fallback.passability==93&&map.buffer4==saved4&&map.buffer10==saved10);
    // Warm clone recalculates its own buffers/list/Cell and keeps source bytes.
    auto recalculatedClone=map.clone();auto recalcCells=cells;Actor recalcA=a,recalcB=b;UnitFoundationState recalcFoundation=foundation;
    PreparedInfantryMembership recalculatedMember(*recalculatedClone,recalcCells,{{0,recalcA.view()},{1,recalcB.view()}},recalcFoundation,threshold,squareRoot);
    recalculatedMember.recalculate(0,-1);require(recalculatedClone->buffer4[0]==0&&map.buffer4==saved4&&map.buffer10==saved10);
    std::cout<<"Actual Infantry recalculation: live primary list, ordered buffer bytes/tails, fallback, cycles, kind refusal and warm clone PASS\n";
    std::cout<<"Prepared Infantry membership, occupation separation, late owners, clones and refusal guards PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
