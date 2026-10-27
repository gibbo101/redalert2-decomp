// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapCellInputs.hpp"
#include "assets/TileImagePreparation.hpp"
#include "assets/TileVariants.hpp"
namespace ra2 {
struct TileSweepType {
    int next=-1,variants=1;
    std::uint32_t usage=0;
    std::uint8_t lazy=0,requiredForRMG=0,owned=0;
    std::string filename;
    std::optional<Data> image;
    // Metadata/color ramps survive an image release in the original sweep.
    std::optional<PreparedTileImage> prepared;
};
struct TileSweepCell {MapInputPosition position;int tile=65535;std::uint8_t sub=0;std::uint32_t flags=0;};
struct TileSweepCursor {int x=0,y=0,remaining=0;std::uint32_t index=0;};
TileSweepCursor resetTileSweepCursor(int width);
int advanceTileSweepCursor(TileSweepCursor&,int width,std::span<const int> slots);
struct TileSweepObserver {
    std::function<void(int)> visit; // Includes the terminal null member (-1).
    std::function<void(int,std::uint32_t)> usage;
    std::function<void(int)> release;
};
struct TileSweepResult {std::uint32_t loaded=0,bytes=0;int kibibytes=0;TileSweepCursor cursor;};
// Complete bounded usage/load sequence. Stable positive-count type chains,
// resident or successfully supplied lazy TMP files and width>=2 geometry.
// Original heap ownership/timers/logging and construction remain separate.
TileSweepResult sweepTileImages(int width,std::span<const int> slots,
    std::span<const TileSweepCell>,std::span<const int> primary,
    std::span<TileSweepType>,int clearTile,TileSweepCursor initialCursor,std::uint8_t force,std::uint8_t keepRMG,
    TileVariantCache&,const TileVariantTables&,const std::function<std::uint32_t()>& next,
    const std::function<Data(const std::string&)>& read,const TileSweepObserver& observer={});
}
