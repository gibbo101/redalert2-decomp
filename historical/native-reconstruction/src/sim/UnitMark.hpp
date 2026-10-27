// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TerrainOccupation.hpp"
namespace ra2 {
struct UnitMarkState {
    std::uint8_t onMap=0,needsRedraw=0,limbo=0,special=0;
};
struct FootMarkView {
    std::uint8_t& onMap;
    std::uint8_t& needsRedraw;
    const std::uint8_t& limbo;
    const std::uint8_t& special;
};
struct UnitMarkServices {
    std::function<int()> imageValue,owner,layer;
    std::function<TerrainCellPoint()> coordinates;
    std::function<void()> redrawMap;
    std::function<void(int)> specialEvent;
    std::function<void(TerrainCellPoint)> insert,remove;
};
using UnitMarkStore=std::function<void(int,std::uint8_t)>;
using UnitMarkRedraw=std::function<void()>;
// Same Object/Techno/Foot kernels over actual fields. Infantry kind15 and
// nonnull Walk layer2 dispatch are independently verified; the callbacks retain
// their exact named boundaries. Membership/event/initialization stay separate.
bool markFootObject(FootMarkView,int,const UnitMarkServices&,
    const UnitMarkStore& = {},const UnitMarkRedraw& = {});
bool markFootTechno(FootMarkView,int,const UnitMarkServices&,
    const UnitMarkStore& = {},const UnitMarkRedraw& = {});
bool markFoot(FootMarkView,int,const UnitMarkServices&,
    const UnitMarkStore& = {},const UnitMarkRedraw& = {});
// Complete Object/Techno/Foot Mark for Unit kind 1. Queries/services must retain
// their order, including unused image/owner results and repeated coordinates.
// Unit kind/cast are fixed; construction/type/house/locomotor association, event
// effects and map membership are supplied. The redraw hook observes virtual entry,
// including an already-dirty request. Callbacks are required only when reached.
bool markUnitObject(UnitMarkState&,int,const UnitMarkServices&,
    const UnitMarkStore& = {},const UnitMarkRedraw& = {});
bool markUnitTechno(UnitMarkState&,int,const UnitMarkServices&,
    const UnitMarkStore& = {},const UnitMarkRedraw& = {});
bool markUnitFoot(UnitMarkState&,int,const UnitMarkServices&,
    const UnitMarkStore& = {},const UnitMarkRedraw& = {});
}
