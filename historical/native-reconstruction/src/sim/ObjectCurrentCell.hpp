// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/Drive.hpp"
namespace ra2 {
// Complete5D51E0. The lookup borrows the actual map; both coordinate copies and
// lookups are required even when the first pointer is discarded. Return the
// second borrowed record/view without making another coordinate/map query.
template<class Lookup>
decltype(auto) objectCurrentCell(const Coord& position,const Lookup& lookup){
    const auto first=position;(void)lookup(first);
    const auto second=position;return lookup(second);
}
}
