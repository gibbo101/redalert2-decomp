// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/CellResidentKind6.hpp"
#include <stdexcept>

namespace ra2 {
struct CellResidentSearchCell {
    const void* const& primaryE4;
    const void* const& secondaryE8;
};
// Complete base471760 on borrowed lists and the existing scenario-loop gate.
// Only the selector's low byte chooses E8; a match returns before reading Next.
inline const void* findCellResident(const CellResidentKind6State& state,
        CellResidentSearchCell cell,std::int32_t requestedKind,std::uint32_t selector,
        const CellResidentKind6Services& services) {
    if(!state.enabled)return nullptr;
    auto resident=std::uint8_t(selector)?cell.secondaryE8:cell.primaryE4;
    while(resident){
        if(!services.kind)throw std::invalid_argument("Cell resident kind query unbound");
        if(services.kind(resident)==requestedKind)return resident;
        if(!services.next)throw std::invalid_argument("Cell resident Next query unbound");
        resident=services.next(resident);
    }
    return nullptr;
}
}
