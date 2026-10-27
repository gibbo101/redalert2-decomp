// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/PreparedUnitDepth.hpp"
#include "assets/MapCoordinateCell.hpp"
#include <stdexcept>
using namespace ra2;
namespace {void require(bool v){if(!v)throw std::runtime_error("Prepared Unit depth guard failed");}}
int main(){
    PreparedFootDepthInputs in;in.unit.heightScale=.125;
    PreparedFootDepthWorld services;MapCellAttributes fallback;
    services.unit.cell=[&](MapInputPosition p)->const MapCellAttributes&{fallback.input.position=p;return fallback;};
    PreparedUnitDepth binding(in,services);auto world=binding.world();
    auto first=world.cell({-1,2});auto second=world.cell({7,-8});
    require(first==second&&first->position==UnitLightCell{7,-8});
    // A requested absent image must not inherit arbitrary nested caller scratch.
    std::array<MapTileAttributes,1> tiles{};services.unit.tiles=tiles;int dimensions=0;
    services.unit.dimensions=[&](int,int){++dimensions;};
    bool caught=false;try{binding.baseDepth();}catch(const std::invalid_argument&){caught=true;}
    require(caught&&!dimensions);
    in.unit.dimensionHeight=37;caught=false;
    try{PreparedUnitDepth refused(in,services);}catch(const std::invalid_argument&){caught=true;}require(caught);
    in.unit.dimensionHeight=0;fallback.input.slope=1;caught=false;
    try{PreparedUnitDepth refused(in,services);}catch(const std::invalid_argument&){caught=true;}require(caught);
    fallback.input.slope=0;in.unit.location.x=-1;caught=false;
    try{PreparedUnitDepth refused(in,services);}catch(const std::invalid_argument&){caught=true;}require(caught);
    std::vector<MapCellInput*> slots(262144);MapCellInput live;live.position={19,23};MapCellInput invalid;
    slots[511]=&live;slots[65536]=&live;int stores=0;
    MapFloorHeightWorld map{slots,&invalid,[&](MapInputPosition){++stores;}};
    require(&mapCoordinateCell({-256,256,0},map,262144)==&live&&!stores);
    require(&mapCoordinateCell({16777216,0,0},map,262144)==&live&&!stores);
    require(&mapCoordinateCell({-257,0,0},map,262144)==&invalid&&invalid.position==MapInputPosition{-1,0}&&stores==1);
    for(int count:{-1,262145}){caught=false;try{mapCoordinateCell({},map,count);}catch(const std::invalid_argument&){caught=true;}require(caught&&stores==1);}
}
