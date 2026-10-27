// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>

namespace ra2 {
struct CellResidentKind6State {
    std::uint8_t enabled=0;
};
struct CellResidentKind6Cell {
    const void* const& primaryE4;
};
struct CellResidentKind6Services {
    std::function<std::int32_t(const void*)> kind;
    std::function<const void*(const void*)> next;
};

// Selected base513624 scenario-loop store. Calls and all sibling startup state
// around this store remain separate; this is not a complete scenario startup.
void initializeCellResidentKind6(CellResidentKind6State&);

// Complete base4717B0 primary-list traversal. The disabled and empty paths do
// not require resident services; a kind-6 hit returns before reading Next.
const void* findCellResidentKind6(const CellResidentKind6State&,
    CellResidentKind6Cell,const CellResidentKind6Services&);
}
