// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/UnitOccupation.hpp"
#include <stdexcept>
namespace ra2 {
namespace {
void change(const Coord& position,const UnitOccupationServices& s,bool mark,const UnitOccupationStore& store) {
    if(!s.cell||!s.floor)throw std::invalid_argument("Unit occupation requires Cell and floor services");
    auto& cell=s.cell(position);
    const int floor=s.floor(position);
    const int boundary=signed32(std::uint32_t(floor)+std::uint32_t(s.heightThreshold));
    // Unmark deliberately does not test the bridge flag.
    const bool elevated=boundary<=position.z&&(!mark||(cell.flags&0x100));
    auto& value=elevated?cell.elevated:cell.ground;
    value=mark?value|0x20u:value&~0x20u;
    if(store)store(cell,elevated?0x128:0x124,value);
}
}
void markUnitOccupation(const Coord& p,const UnitOccupationServices& s,const UnitOccupationStore& w){change(p,s,true,w);}
void unmarkUnitOccupation(const Coord& p,const UnitOccupationServices& s,const UnitOccupationStore& w){change(p,s,false,w);}
}
