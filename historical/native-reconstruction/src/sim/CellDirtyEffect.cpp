// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/CellDirtyEffect.hpp"
#include <stdexcept>
namespace ra2 {
CellDirtyEffectExit applyCellDirtyEffectPrefix(const CellDirtyEffectInput& c){
    if(c.overlay44!=0x7e)return CellDirtyEffectExit::Overlay;
    if(c.overlayData11e<0x30)return CellDirtyEffectExit::OverlayData;
    if(c.slope11c)return CellDirtyEffectExit::Slope;
    if(c.flags140&0x20000u)return CellDirtyEffectExit::Flags;
    if(!c.hasPrimaryResident)return CellDirtyEffectExit::Empty;
    throw std::invalid_argument("Cell dirty resident effect unsupported");
}
}
