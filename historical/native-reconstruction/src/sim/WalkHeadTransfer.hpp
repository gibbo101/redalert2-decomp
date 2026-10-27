// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/Drive.hpp"

namespace ra2::detail {
// Shared71F590 transfer order. Nonempty selection is supplied by the full
// ordinary caller; the older arrival facade enters only the empty-request path.
// Object coordinates are copied at each original snapshot boundary. Existing
// heads stay borrowed, and the requested point is read only after release.
template<class Release,class Assign,class Nonempty,class Claim>
std::uint8_t transferWalkHead(Coord& head,const Coord& position,const Coord& request,
    Coord empty,Release release,Assign assign,Nonempty nonempty,Claim claim) {
    if(head==empty) {
        const Coord old=position;
        release(old);
    } else release(head);
    const Coord point=request;
    if(request==empty)assign(point);
    else nonempty(point);
    if(head!=empty) { claim(head);return 1; }
    const Coord current=position;
    claim(current);return 0;
}
}
