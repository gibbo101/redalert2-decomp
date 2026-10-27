// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/PreparedUnitDepth.hpp"
#include <stdexcept>
namespace ra2 {
PreparedUnitDepth::PreparedUnitDepth(const PreparedFootDepthInputs& input,const PreparedFootDepthWorld& services)
    :input_(input),services_(services){
    if(input.unit.dimensionHeight!=0||!services.unit.cell)
        throw std::invalid_argument("Prepared Unit depth requires shared Cells and no supplied nested scratch");
    // This join feeds the existing flat Drive shadow consumer. Check the actual
    // prepared current Cell before any draw state changes; neighbors may be ramps.
    const auto p=input.unit.location;
    if(p.x<0||p.y<0||p.x>=512*256||p.y>=512*256||
       services.unit.cell({std::int16_t(p.x/256),std::int16_t(p.y/256)}).input.slope!=0)
        throw std::invalid_argument("Prepared Unit world requires a flat current Cell for the Drive shadow pose");
}
FootDepthWorld PreparedUnitDepth::world(){
    FootDepthWorld out;out.tileBase=input_.tileBase;out.invalid=input_.invalid;
    out.coordinates=[this]{
        if(services_.unit.query)services_.unit.query(1);
        return footDepthCoordinates(input_.unit.location.x,input_.unit.location.y);
    };
    out.cell=[this](UnitLightCell p)->const FootDepthCell*{
        const auto& cell=services_.unit.cell({p.x,p.y});const auto& v=cell.input;
        auto& view=views_[&cell];view={{v.position.x,v.position.y},v.flags,v.tile,v.land,v.tube,v.level};return &view;
    };
    out.cellPredicate=[this](const FootDepthCell& c){
        if(services_.cellPredicate)services_.cellPredicate(c.position);
        return footDepthCellPredicate(c,0);
    };
    out.trace=[this](int n){if(services_.trace)services_.trace(410+n);};
    return out;
}
int PreparedUnitDepth::baseDepth() const{
    auto base=services_.unit;
    base.dimensions=[this](int tile,int sub){
        const auto& w=services_.unit;
        if(tile<0||std::size_t(tile)>=w.tiles.size()||!w.tiles[std::size_t(tile)].image)
            throw std::invalid_argument("Prepared Unit depth requires an available TMP image");
        if(w.dimensions)w.dimensions(tile,sub);
    };
    return ordinaryUnitBaseDepth(input_.unit,base).depth;
}
}
