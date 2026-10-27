// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Bytes.hpp"
#include "assets/MapCellInputs.hpp"
#include <array>
namespace ra2 {
struct TileColorPacking {
    unsigned redLeft=11,redRight=3,blueLeft=0,blueRight=3,greenLeft=5,greenRight=2;
};
using TileColorRamp=std::array<std::uint16_t,26>;
struct PreparedTileImage {
    MapTileImageInput image;
    int typeColumns=0,typeRows=0;
    // File-relative references replace original relocated 32-bit pointers.
    std::vector<std::uint32_t> subTileOffsets;
    std::vector<std::optional<TileColorRamp>> colorRamps;
};
// Ordinary local TMP bytes, dimensions <=255 and at most 16384 sub-tiles.
// Recover selected image/type metadata and the original 13-pair color ramps.
// Heap/file/vector ownership, archive registration and variant selection are
// separate. The pixel/depth decoder remains readTmp; this does not replace it.
PreparedTileImage prepareTileImage(const Data&,TileColorPacking packing={});
}
