// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/PreparedFootDepth.hpp"
#include <map>
#include <stdexcept>
namespace ra2 {
PreparedFootDepthResult preparedFootDepth(const PreparedFootDepthInputs& in,const PreparedFootDepthWorld& w){
    if(in.unit.dimensionHeight!=0)throw std::invalid_argument("Prepared Foot depth does not supply nested caller scratch");
    if(!w.unit.cell)throw std::invalid_argument("Prepared Foot depth requires shared Cells");
    const auto trace=[&](int n){if(w.trace)w.trace(n);};
    // Key by original record identity, not requested coordinates. All absent
    // positions share and mutate the same fallback Cell in the original map.
    std::map<const MapCellAttributes*,FootDepthCell> views;
    FootDepthWorld foot;foot.tileBase=in.tileBase;foot.invalid=in.invalid;
    foot.trace=[&](int n){trace(410+n);};
    foot.coordinates=[&]{if(w.unit.query)w.unit.query(1);return footDepthCoordinates(in.unit.location.x,in.unit.location.y);};
    foot.cell=[&](UnitLightCell p)->const FootDepthCell*{
        const auto& cell=w.unit.cell({p.x,p.y});const auto& v=cell.input;auto& out=views[&cell];
        out={{v.position.x,v.position.y},v.flags,v.tile,v.land,v.tube,v.level};return &out;
    };
    foot.cellPredicate=[&](const FootDepthCell& c){if(w.cellPredicate)w.cellPredicate(c.position);return footDepthCellPredicate(c,0);};
    FootDepthServices s;
    s.locomotorDepth=[&]{trace(421);return 0;};
    s.locomotorGradient=[&]{trace(422);return 2;};
    s.type=[&]{trace(420);return in.type;};
    s.predicate0=[&]{return footDepthPredicate0(foot);};
    s.predicate1=[&]{return footDepthPredicate1(foot);};
    s.predicate2=[&]{return footDepthPredicate2(foot);};
    s.predicate3=[&]{return std::uint8_t(footDepthFlag(foot));};
    s.baseDepth=[&]{
        trace(424);auto base=w.unit;
        base.dimensions=[&](int tile,int sub){
            if(tile<0||std::size_t(tile)>=w.unit.tiles.size()||!w.unit.tiles[std::size_t(tile)].image)
                throw std::invalid_argument("Prepared Foot depth requires an available TMP image");
            if(w.unit.dimensions)w.unit.dimensions(tile,sub);
        };
        return ordinaryUnitBaseDepth(in.unit,base).depth;
    };
    const int depth=footDepthAdjustment(in.drive,s);
    return {depth,footDepthGradient(in.drive,s)};
}
}
