// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapPreparation.hpp"
#include <stdexcept>

namespace ra2 {
TileSweepCursor prepareMapCells(int width, std::span<const int> slots,
    std::span<MapPreparationCell> cells, const MapPreparationServices& services) {
    if (!services.initializeLighting || !services.recalculate)
        throw std::invalid_argument("Map preparation requires lighting and Cell services");
    for (const auto& cell : cells)
        if (cell.attachedTag || cell.attributes.overlay != -1)
            throw std::invalid_argument("Map preparation tag/overlay profile is unrecovered");

    auto cursor = resetTileSweepCursor(width);
    const auto visit = [&]() {
        const int index = advanceTileSweepCursor(cursor, width, slots);
        if (services.visit) services.visit(index);
        if (index < -1 || (index >= 0 && std::size_t(index) >= cells.size()))
            throw std::invalid_argument("Missing map preparation cell");
        return index;
    };
    const auto store = [&](int index, MapPreparationField field, std::uint32_t value) {
        if (services.store) services.store(index, field, value);
    };
    // Complete first pass precedes lighting/recalculation of any cell.
    for (int index; (index = visit()) != -1;) {
        auto& flags = cells[std::size_t(index)].attributes.input.flags;
        flags &= 0xFFCFFFFFu;
        store(index, MapPreparationField::Flags, flags);
    }
    cursor = resetTileSweepCursor(width);
    for (int index; (index = visit()) != -1;) {
        auto& cell = cells[std::size_t(index)];
        cell.field30 = 0;
        store(index, MapPreparationField::Field30, 0);
        services.initializeLighting(index);
        cell.attributes.input.flags &= 0xFFFDFFFFu;
        store(index, MapPreparationField::Flags, cell.attributes.input.flags);
        // The actual resource child returns zero for overlay==-1. Tags and
        // wall-owner work are absent in this supported ordinary initial state.
        services.recalculate(index, -1);
    }
    return cursor;
}

TileSweepCursor prepareResidentMapCells(const ResidentMapPreparationInputs& input,
    std::span<MapPreparationCell> cells, MapCellInput& fallback,
    std::span<std::uint8_t> buffer4, std::span<std::uint8_t> buffer10,
    const ResidentMapPreparationServices& services) {
    if (input.width<2 || input.width>255 || input.height<1 || input.height>254 ||
        input.width+input.height>256 || input.slots.size()!=512u*512u ||
        input.permission.dimension0!=input.width || input.cliffMode>2 || !services.initializeLighting)
        throw std::invalid_argument("Unsupported resident map preparation inputs");
    const auto side=std::size_t(input.width+input.height+1);
    const auto capacity=side*side;
    if (buffer4.size()!=capacity*4 || buffer10.size()!=capacity*10)
        throw std::invalid_argument("Resident map preparation buffer size differs");

    // Pointer-table storage is a host binding. Validate it before guest-like stores.
    for (auto& cell:cells)
        if (&cell.attributes.input==&fallback)
            throw std::invalid_argument("Resident map fallback aliases Cell storage");
    std::vector<MapCellInput*> table(input.slots.size());
    for (std::size_t slot=0;slot<input.slots.size();++slot) {
        const int member=input.slots[slot];
        if (member==-1) continue;
        if (member<0 || std::size_t(member)>=cells.size())
            throw std::invalid_argument("Missing resident map Cell");
        auto& cell=cells[std::size_t(member)].attributes.input;
        if (int(cell.position.x)!=int(slot%512) || int(cell.position.y)!=int(slot/512))
            throw std::invalid_argument("Resident map Cell position/fallback differs");
        table[slot]=&cell;
    }
    std::array<float,11> wheel;
    for (unsigned i=0;i<wheel.size();++i)
        wheel[i]=input.land[i].speed[unsigned(LandSpeed::Wheel)];
    const MapAttributeLookup world{table,&fallback,services.query,services.fallbackStore};
    MapPreparationServices parent;
    parent.initializeLighting=services.initializeLighting;
    parent.visit=services.visit;
    parent.store=services.parentStore;
    parent.recalculate=[&](int id,int level) {
        if (services.beforeRecalculation) services.beforeRecalculation(id);
        auto& cell=cells[std::size_t(id)].attributes;
        const auto index=std::size_t(mapAttributeBufferIndex(cell.input.position,
            input.width,input.height,int(capacity)));
        MapAttributeServices child;
        child.tiles=input.tiles;
        child.landMap=input.landMap;
        child.cliffMode=input.cliffMode;
        child.neighborLevel=[&](MapInputPosition p) {return mapAttributeCell(p,world).level;};
        child.setupLAT=[&](const MapCellAttributes& state) {
            if (services.beforeLAT) services.beforeLAT(id);
            auto copy=state.input;
            setupMapLAT(copy,input.lat,input.directions,world,int(input.tiles.size()),
                [&](int tile) {if(services.attributeStore)
                    services.attributeStore(id,MapAttributeField::Tile,std::uint32_t(tile));});
            return copy.tile;
        };
        child.updatePassability=[&](const MapCellAttributes& state) {
            if (services.beforePassability) services.beforePassability(id);
            const bool permitted=mapCellPermitted(state.input.position,true,input.permission,world);
            const int result=emptyCellPassability(state.input,permitted,wheel);
            if (services.passabilityStore) services.passabilityStore(id,result);
            return result;
        };
        child.store=[&](MapAttributeField field,std::uint32_t value) {
            if (services.attributeStore) services.attributeStore(id,field,value);
        };
        recalculateMapCellAttributes(cell,level,
            std::span<std::uint8_t,4>(buffer4.data()+index*4,4),
            std::span<std::uint8_t,10>(buffer10.data()+index*10,10),child);
    };
    return prepareMapCells(input.width,input.slots,cells,parent);
}
}
