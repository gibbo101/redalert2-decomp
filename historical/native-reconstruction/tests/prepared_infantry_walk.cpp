// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/PreparedInfantryWalk.hpp"
#include <cmath>
#include <iostream>
using namespace ra2;
namespace {
void require(bool value){if(!value)throw std::runtime_error("Infantry Walk owner check failed");}
template<class F>void refuses(F f){bool caught=false;try{f();}catch(const std::invalid_argument&){caught=true;}require(caught);}
}
int main(){try{
    std::array<MapFinalizationCell,4> seed{};std::vector<int> slots(262144,-1);
    for(int i=0;i<4;++i){auto& p=seed[std::size_t(i)].attributes.input.position;
        p={std::int16_t(i%2),std::int16_t(i/2)};slots[std::size_t(p.y*512+p.x)]=i;}
    MapCellAttributes fallback;fallback.input.position={-31,17};MapFloorHeightState cold;
    std::array<int,16> land{};std::array<float,11> wheels{};ResidentCellInputs resident;
    resident.landMap=land;resident.wheelSpeeds=wheels;Bytes b4(16*4),b10(16*10);
    MutableUnitMap map({seed,slots,fallback,cold,resident,b4,b10,2,1,104});
    std::array<InfantryMembershipCell,5> cells;InfantryWalkState a,b;
    a.ground.position={128,128,0};b.ground.position={128,384,0};
    a.object.mission.owner=b.object.mission.owner=7;a.object.mission.mission98=b.object.mission.mission98=2;
    a.route[23]=71;b.route[23]=83;a.wait558={11,13,17};b.wait558={19,23,29};
    InfantryWalkType type;type.speed5a0=32;InfantryWalkGlobals globals;globals.tick=41;
    std::map<int,MovementGateHouse> houses{{7,{3,8}}};float country=1;std::uint8_t human=1,other=0;
    std::vector<std::optional<UnitAdmissionRegistry>> registry;std::array<std::uint32_t,108> speeds{};
    InfantrySubcellData subcells;OriginalRandomState random{};DirectionData direction;int numeric=0;
    // These checks stop before trigonometry/head selection. This deliberately
    // supplied numeric service is not used as original fidelity evidence.
    WalkMovementNumerics numbers{direction,0,[&](double x){++numeric;return std::sqrt(x);},{},{}};
    UnitFoundationState foundation;
    const auto binding=[&](InfantryWalkState& actor){return InfantryWalkBinding{actor,type,houses.at(7).index,country,human,other};};
    PreparedInfantryWalk world(map,cells,{{0,binding(a)},{1,binding(b)}},foundation,houses,registry,globals,subcells,random,numbers,speeds);
    require(!numeric&&!map.floor.flags&&!foundation.unitFlag&&cells[0].head==-1&&a.route[23]==71&&b.route[23]==83);
    auto& member=world.membership();auto& membership=member.world();
    membership.services.visible=[](const Coord&){return 1;};membership.services.recalculate=[](int,int){};
    member.redrawMap=[]{};world.animation=[](int,int,int,int){};
    require(world.mark(0,1)&&world.mark(1,1)&&cells[0].head==0&&cells[2].head==1&&a.object.next==-1&&b.object.next==-1);
    CellResidentKind6State residentState;const auto cell0=world.cellIdentity(a.ground.position);
    cells[0].head=99;const auto disabled=world.findKind6(cell0,residentState);
    require(!disabled.resident&&!disabled.kindQueries&&!disabled.nextReads);cells[0].head=0;
    initializeCellResidentKind6(residentState);const auto ordinary=world.findKind6(cell0,residentState);
    require(!ordinary.resident&&ordinary.kindQueries==1&&ordinary.nextReads==1);
    cells[0].head=99;refuses([&]{(void)world.findKind6(cell0,residentState);});cells[0].head=0;
    a.object.kind=6;const auto first=world.findKind6(cell0,residentState);
    require(first.resident==&a&&first.kindQueries==1&&!first.nextReads);a.object.kind=15;
    a.object.next=1;b.object.kind=6;const auto second=world.findKind6(cell0,residentState);
    require(second.resident==&b&&second.kindQueries==2&&second.nextReads==1);a.object.next=-1;b.object.kind=15;
    a.object.next=99;refuses([&]{(void)world.findKind6(cell0,residentState);});a.object.next=-1;
    refuses([&]{(void)world.findKind6(0x12345678,residentState);});
    // A real kind6 owner supplies only actor fields/identity. It has no Walk,
    // Drive, command state or admission object. Binding performs no queries.
    Coord buildingPosition{128,128,0};int buildingNext=0,buildingIdentity=0;
    std::uint8_t alternate=0,eligible=0,mapFlag=0;
    const auto buildingView=[&]{return MembershipActorView{buildingPosition,buildingNext,alternate,eligible,mapFlag,6};};
    world.registerBuildingResident(100,&buildingIdentity,buildingView());
    refuses([&]{world.registerBuildingResident(100,&buildingIdentity,buildingView());});
    refuses([&]{world.registerBuildingResident(101,&a,buildingView());});
    cells[0].head=100;
    const auto buildingHead=world.findKind6(cell0,residentState);
    require(buildingHead.resident==&buildingIdentity&&buildingHead.kindQueries==1&&!buildingHead.nextReads);
    membership.cellRemove(0,0);require(cells[0].head==100&&buildingNext==-1&&a.object.next==-1);
    membership.cellInsert(0,0);require(cells[0].head==0&&a.object.next==100&&buildingNext==-1);
    const auto behind=world.findKind6(cell0,residentState);
    require(behind.resident==&buildingIdentity&&behind.kindQueries==2&&behind.nextReads==1);
    membership.cellRemove(0,0);require(cells[0].head==100&&a.object.next==-1);
    refuses([&]{membership.cellInsert(100,0);});
    cells[0].head=0;
    require(!cells[0].ground&&!cells[2].ground&&!numeric);
    member.occupy(0,a.ground.position);member.occupy(1,b.ground.position);
    require(cells[0].ground==1&&cells[2].ground==1&&cells[0].groundHouse==3&&numeric==2);
    houses.at(7).index=9;member.occupy(0,a.ground.position);require(cells[0].groundHouse==9);
    // Rebind on these same actors/Cells. Refusals preserve all old bindings;
    // occupation consumes the new index while independent actor1 keeps its House.
    houses.emplace(9,MovementGateHouse{27,0});float nextSpeed=.5f;std::uint8_t nextHuman=0,nextControl=0;
    int foreignIndex=27;const auto savedRoute=a.route;const auto savedWait=a.wait558;
    refuses([&]{world.rebindHouse(0,9,foreignIndex,nextSpeed,nextHuman,nextControl);});
    refuses([&]{world.rebindHouse(0,99,houses.at(9).index,nextSpeed,nextHuman,nextControl);});
    require(a.object.mission.owner==7&&&member.actor(0).houseIndex.get()==&houses.at(7).index);
    const auto floorFlags=map.floor.flags;const auto head0=cells[0].head;const int queries=numeric;
    world.rebindHouse(0,9,houses.at(9).index,nextSpeed,nextHuman,nextControl);
    require(a.object.mission.owner==9&&b.object.mission.owner==7&&a.route==savedRoute&&a.wait558==savedWait&&
        cells[0].head==head0&&map.floor.flags==floorFlags&&numeric==queries);
    member.occupy(0,a.ground.position);require(cells[0].groundHouse==27&&cells[2].groundHouse==3);
    houses.at(9).index=29;member.occupy(0,a.ground.position);require(cells[0].groundHouse==29);
    // New human/control bytes affect the existing command kernel immediately.
    int rebindTarget=0;world.targetIdentity=[&](const void* p){require(p==&rebindTarget);return 1;};
    world.targetCoordinates=[&](const void* p){require(p==&rebindTarget);return Coord{384,128,0};};
    a.state5ac=27;globals.session=0;nextControl=1;world.order(0,&rebindTarget);require(!a.target494);
    nextControl=0;world.order(0,&rebindTarget);require(a.target494==&rebindTarget);
    world.order(0,nullptr);a.state5ac=0;globals.session=1;world.rebindHouse(0,7,houses.at(7).index,country,human,other);
    member.occupy(0,a.ground.position);require(cells[0].groundHouse==9);
    int target=0;world.targetIdentity=[&](const void* p){require(p==&target);return 1;};
    world.targetCoordinates=[&](const void* p){require(p==&target);return Coord{384,128,0};};
    world.order(0,&target);require(a.walk.destination==Coord{384,128,0}&&a.target494==&target&&a.walk.moving34);
    require(b.walk.destination==Coord{}&&!b.target494&&b.route[23]==83&&b.wait558==std::array{19,23,29});
    // Stop retains a committed head. The independent actor and actual shared
    // occupation are not replaced by a copied command-state representation.
    a.walk.head={384,128,0};world.order(0,nullptr);
    require(a.walk.head==Coord{384,128,0}&&a.walk.destination==Coord{}&&a.walk.moving34&&cells[0].ground==1);
    a.walk.head={};world.order(0,nullptr);require(!a.walk.moving34);
    world.process(1);require(!b.walk.inProcessing35&&b.route[23]==83&&a.route[23]==71);
    // Actual Cell views reject a foreign map even when its logical Cell number
    // is equal. A clone must bind every actor, timer, callback and Cell anew.
    auto copy=map.clone();auto copiedCells=cells;auto copiedA=a,copiedB=b;auto copiedFoundation=foundation;
    auto copiedGlobals=globals;auto copiedRandom=random;
    PreparedInfantryWalk cloned(*copy,copiedCells,{{0,binding(copiedA)},{1,binding(copiedB)}},copiedFoundation,
        houses,registry,copiedGlobals,subcells,copiedRandom,numbers,speeds);
    cloned.membership().walkMap().word({-7,5});require(copy->fallback.input.position==MapInputPosition{-7,5}&&map.fallback.input.position==MapInputPosition{-31,17});
    refuses([&]{member.cellId(cloned.membership().walkMap().word({0,0}));});
    cloned.membership().world().actors.at(0).next=1;copiedCells[0].ground=31;copiedA.route[23]=99;
    require(a.object.next==-1&&cells[0].ground==1&&a.route[23]==71);
    refuses([&]{PreparedInfantryWalk bad(map,cells,{{0,binding(a)},{1,binding(a)}},foundation,houses,registry,globals,subcells,random,numbers,speeds);});
    int copiedHouse=houses.at(7).index;
    refuses([&]{PreparedInfantryWalk bad(map,cells,{{0,{a,type,copiedHouse,country,human,other}}},foundation,houses,registry,globals,subcells,random,numbers,speeds);});
    // Entered nonzero admission remains a refusal. Route/timer/processing writes
    // before the unsupported child are retained; no low-level rollback claim.
    speeds.fill(0x3f800000);cells[1].ground=32;world.order(0,&target);
    world.route=[&](int id,TerrainCellPoint,int,int){require(id==0);a.route[0]=2;a.route[1]=-1;return std::uint8_t(1);};
    refuses([&]{world.process(0);});require(a.walk.inProcessing35==1&&a.retry530[0]==41&&a.counter53c==10&&a.walk.head==Coord{});
    require(b.ground.position==Coord{128,384,0}&&cells[2].head==1&&cells[2].ground==1&&b.route[23]==83);
    std::cout<<"Prepared Infantry Walk cold binding, actual owners, commands, clones and refusal guards PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
