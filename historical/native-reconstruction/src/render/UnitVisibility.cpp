// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitVisibility.hpp"
#include <bit>
#include <stdexcept>
namespace ra2 {
namespace {
int add(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}
int sub(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)-std::uint32_t(b));}
}
bool drawOrdinaryUnitIfVisible(TerrainMarkState& state,PixelRect& bounds,const PixelRect& viewport,
                              TerrainDrawGate gate,std::uint8_t specialDrawState,
                              const UnitVisibilityServices& services,const TerrainVisibilityTrace& trace){
    if(specialDrawState)throw std::invalid_argument("Special Unit drawing state is unrecovered");
    if(trace)trace({'g',0}); // Actual Unit wrapper supplies third=0 to Object.
    if(!gate.bypass&&gate.contextPresent){
        if(!gate.force&&!state.needsRedraw)return false;
        if(state.limbo)return false;
    }
    state.needsRedraw=0;if(trace)trace({'r',0});
    const auto [point,success]=services.project(services.coordinates());
    if(!success){if(trace)trace({'t',1});return false;} // Actual Unit type leaf=1.
    bounds=intersectDrawBounds(bounds,viewport);
    if(trace){trace({'x',bounds.x});trace({'y',bounds.y});trace({'w',bounds.width});trace({'h',bounds.height});}
    auto adjusted=point;
    if(bounds.x>viewport.x)adjusted.x=add(adjusted.x,sub(viewport.x,bounds.x));
    if(bounds.y>viewport.y)adjusted.y=add(adjusted.y,sub(viewport.y,bounds.y));
    // Object calls DrawIt even when the intersection is the empty rectangle.
    services.draw(adjusted,bounds);return true;
}
}
