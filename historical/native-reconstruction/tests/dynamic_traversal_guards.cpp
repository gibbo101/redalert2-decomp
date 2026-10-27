// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/DynamicTraversal.hpp"
#include "render/UnitVisibility.hpp"
#include "sim/FootCoordinates.hpp"
#include <cfenv>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>
using namespace ra2;
int main(){try{
    int callbacks=0;DynamicTraversalContext c;DynamicTraversalServices s;
    s.inverse=[&](TraversalVector){++callbacks;return TraversalVector{};};
    std::vector<TraversalActor> actors(2);actors[0].visible=255;actors[1].visible=255;
    std::array<int,2> ids{0,1};std::array<std::span<const int>,5> layers{};layers[2]=ids;
    PixelRect bounds{0,0,320,200};
    auto refused=[&]{
        bool rejected=false;
        try{drawDynamicLayers(actors,layers,bounds,c,s);}catch(const std::invalid_argument&){rejected=true;}
        if(!rejected||callbacks||actors[0].visible!=255||actors[1].visible!=255)
            throw std::runtime_error("Invalid profile must be refused before callbacks or mutation");
    };
    actors[1].flags=1;refused(); // Non-Foot Techno requires another branch.
    actors[1].kind=TraversalKind::Terrain;actors[1].flags=7;refused();
    actors[1].kind=static_cast<TraversalKind>(99);refused();
    actors[1]=actors[0];ids[1]=-1;refused();ids[1]=2;refused();ids[1]=1;
    c.auxiliaryCount=1;refused();c.auxiliaryCount=0;
    layers[2]={}; // Test FP restoration on both normal and exceptional exits.
    const int saved=std::fegetround();
    if(std::fesetround(FE_UPWARD))throw std::runtime_error("Cannot set FP test mode");
    drawDynamicLayers(actors,layers,bounds,c,s);
    if(callbacks!=3||std::fegetround()!=FE_UPWARD)throw std::runtime_error("Traversal leaked FP rounding state");
    for(float bad:{std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN(),2147483648.0f}){
        s.inverse=[&](TraversalVector){return TraversalVector{bad,0,0};};
        bool rejected=false;
        try{drawDynamicLayers(actors,layers,bounds,c,s);}catch(const std::invalid_argument&){rejected=true;}
        if(!rejected||std::fegetround()!=FE_UPWARD)throw std::runtime_error("Invalid inverse conversion or FP restoration differs");
    }
    std::fesetround(saved);
    TerrainMarkState unit{1,1,0};UnitVisibilityServices drawing;
    for(std::uint8_t special:{1,255}){
        bool rejected=false;int events=0;
        try{drawOrdinaryUnitIfVisible(unit,bounds,bounds,{0,true,1},special,drawing,
                                     [&](auto){++events;});}catch(const std::invalid_argument&){rejected=true;}
        if(!rejected||events||unit.needsRedraw!=1)throw std::runtime_error("Special Unit state must be refused before mutation");
    }
    FootCoordinateServices foot;
    for(std::int8_t index:{0,-1}){
        bool rejected=false;
        try{(void)footSecondaryCoordinates(index,{},foot);}catch(const std::invalid_argument&){rejected=true;}
        if(!rejected)throw std::runtime_error("Missing Foot coordinate services/entries must be refused");
    }
    std::cout<<"Dynamic traversal domain and FP restoration guards: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
