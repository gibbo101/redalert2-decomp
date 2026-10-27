// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/CellVisibilityDiscovery.hpp"
#include <stdexcept>

namespace ra2 {
void discoverVisibleCellResidents(int startingCell,int house,bool notify,
    const CellVisibilityDiscoveryServices& s){
    if(!s.point||!s.cellAt||!s.level||!s.residents||!s.discoveredBy||
       (notify&&!s.notifyCell))
        throw std::invalid_argument("Cell visibility discovery services are incomplete");
    auto point=s.point(startingCell);
    for(int upper=1;upper<15;upper+=2){
        const int cell=s.cellAt(point),cellLevel=s.level(cell);
        if(cellLevel>=upper-2&&cellLevel<=upper){
            if(notify)s.notifyCell(s.point(cell));
            const int resident=closestCellResident(0,0,false,-1,s.residents(cell));
            if(resident!=-1)s.discoveredBy(resident,house);
        }
        point.x=std::int16_t(signed16(std::uint16_t(std::uint16_t(point.x)+1u)));
        point.y=std::int16_t(signed16(std::uint16_t(std::uint16_t(point.y)+1u)));
    }
}
}
