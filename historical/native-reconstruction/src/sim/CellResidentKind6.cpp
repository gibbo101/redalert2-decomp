// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/CellResidentKind6.hpp"
#include <stdexcept>

namespace ra2 {
void initializeCellResidentKind6(CellResidentKind6State& state){state.enabled=1;}

const void* findCellResidentKind6(const CellResidentKind6State& state,
        CellResidentKind6Cell cell,const CellResidentKind6Services& services) {
    if(!state.enabled)return nullptr;
    auto resident=cell.primaryE4;
    while(resident){
        if(!services.kind)throw std::invalid_argument("Cell resident kind query unbound");
        if(services.kind(resident)==6)return resident;
        if(!services.next)throw std::invalid_argument("Cell resident Next query unbound");
        resident=services.next(resident);
    }
    return nullptr;
}
}
