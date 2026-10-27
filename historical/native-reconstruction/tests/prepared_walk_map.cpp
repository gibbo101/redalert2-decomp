// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/PreparedWalkMap.hpp"
#include <iostream>
#include <stdexcept>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::runtime_error("Prepared Walk map ownership check failed");}
template<class F>void refuses(F f){bool caught=false;try{f();}catch(const std::invalid_argument&){caught=true;}require(caught);}
}
int main(){try{
    std::array<MapFinalizationCell,2> cells{};
    cells[0].attributes.input.position={0,0};cells[1].attributes.input.position={1,0};
    cells[0].attributes.input.level=4;cells[1].attributes.input.level=0;
    std::vector<int> slots(262144,-1);slots[0]=0;slots[1]=1;
    MapCellAttributes fallback;fallback.input.position={-31,17};MapFloorHeightState cold;
    std::array<int,16> land{};std::array<float,11> speeds{};
    ResidentCellInputs resident;resident.landMap=land;resident.wheelSpeeds=speeds;
    Bytes b4(4*4*4),b10(4*4*10);
    MutableUnitMap map({cells,slots,fallback,cold,resident,b4,b10,2,1,104});
    int fallbacks=0;MapInputPosition last;
    PreparedWalkMap walk(map,[&](MapInputPosition p){
        require(map.fallback.input.position==p);last=p;++fallbacks;
    });
    require(!map.floor.flags&&map.fallback.input.position==fallback.input.position&&!fallbacks);
    auto first=walk.coordinate({128,128,0});auto second=walk.word({1,0});
    require(first.identity==&map.cells[0].attributes.input&&second.identity==&map.cells[1].attributes.input);
    require(&walk.attributes(first)==&map.cells[0].attributes&&&first.level==&map.cells[0].attributes.input.level);
    // Later writes are visible through already returned views. No refresh or
    // map/floor query is needed, including when both views name one fallback.
    map.cells[0].attributes.input.level=7;map.cells[1].attributes.input.flags=256;
    require(first.level==7&&second.flags==256&&!map.floor.flags&&!fallbacks);
    auto missing=walk.coordinate({-257,0,0});require(last==MapInputPosition{-1,0}&&fallbacks==1);
    auto missing2=walk.word({-2,-3});require(last==MapInputPosition{-2,-3}&&fallbacks==2);
    require(missing.identity==missing2.identity&&&walk.attributes(missing)==&map.fallback);
    map.fallback.input.level=-4;map.fallback.input.flags=513;
    require(missing.level==-4&&missing2.flags==513&&!map.floor.flags);
    // The coordinate root uses full signed quotients and a wrapped combined
    // index; it must not truncate to words or reject X and Y independently.
    map.table[511]=&map.cells[0].attributes.input;
    require(walk.coordinate({-256,256,0}).identity==first.identity&&fallbacks==2);
    require(walk.coordinate({16777216,0,0}).identity==missing.identity&&last==MapInputPosition{0,0}&&fallbacks==3);
    require(walk.word({0,0}).identity==first.identity&&!map.floor.flags&&fallbacks==3);
    require(walk.floor({128,128,0})==728&&map.floor.flags==7);
    // A clone owns independent fields/cache/fallback; its binding cannot
    // consume source views or a mixed-Cell view under a valid identity.
    auto copy=map.clone();PreparedWalkMap cloned(*copy);
    auto clonedFirst=cloned.coordinate({128,128,0});
    require(clonedFirst.identity!=first.identity&&&clonedFirst.level!=&first.level);
    refuses([&]{cloned.attributes(first);});refuses([&]{walk.attributes(clonedFirst);});
    refuses([&]{walk.attributes({first.level,second.flags,first.identity});});
    copy->cells[0].attributes.input.level=1;copy->fallback.input.flags=0;
    require(first.level==7&&missing.flags==513&&clonedFirst.level==1&&fallbacks==3);
    // The actual movement kernel retains live references across its two
    // crossing lookups. Mutating the old owner during the new lookup changes
    // the bridge decision; a value snapshot would incorrectly select bridge1.
    DirectionData direction;direction.slopeStep=1;direction.angleScale=1;
    ActorGroundState actor{{128,128,0},1,0};Facing facing;int frozen=0;double percentage=1;
    std::uint8_t a=0,b=0;WalkMovementState movement{{},{384,128,0},1,0,0};
    WalkMovementNumerics numbers{direction,0,[](double){return 256.;},[](double){return 0.f;},[](double){return 1.f;}};
    WalkMovementServices services;services.speed=[](){return 256;};
    services.placement.floor=[&](Coord p){return walk.floor(p);};
    services.placement.mark=[&](int mode){actor.marked74=std::uint8_t(mode);};
    int lookups=0,dirty=0;
    map.cells[0].attributes.input.level=4;map.cells[1].attributes.input.flags=256;
    services.lookup=[&](TerrainCellPoint p){
        if(++lookups==2)map.cells[0].attributes.input.level=5;
        return walk.word(p);
    };
    services.currentCell=[&](Coord p){return walk.coordinate(p);};
    services.dirty=[&](WalkMovementCellView c){require(&walk.attributes(c)==&map.cells[1].attributes);++dirty;};
    processCommittedWalk(movement,{actor,facing,frozen,percentage,a,b},numbers,services,0,416);
    require(actor.position==Coord{384,128,0}&&!actor.bridge79&&lookups==2&&dirty==1);
    std::cout<<"Prepared Walk map live fields, fallback, cold binding, clone isolation and movement crossing PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
