// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapCellInputs.hpp"
#include <array>
#include <span>
namespace ra2 {
// The fifteen LAT globals' existing order, followed by Foot's BridgeSet base.
// These are set numbers read from General, not already converted tile indices.
inline constexpr std::array<const char*,16> theaterDepthKeys{
    "WaterBridge","ShorePieces","ClearToRoughLat","ClearToSandLat","ClearToGreenLat",
    "ClearToPaveLat","MiscPaveTile","PavedRoads","Medians","RampSmooth",
    "RampBase","RoughTile","SandTile","GreenTile","PaveTile","BridgeSet"};
struct TheaterTileSetInput {
    int count=-1,lastCount=-1,marble=65535,nonMarble=65535,toSnow=-1,toTemperate=-1;
    bool morphable=false,allowPlace=true,allowBurrowing=true,allowTiberium=false;
    bool requiredForRMG=false,shadowCaster=false;
    int shadowTiles=0;
};
struct TheaterTileTypeInput {
    int index=0,setBase=0,marble=65535,nonMarble=65535,toSnow=-1,toTemperate=-1;
    bool morphable=false,shadowCaster=false,allowPlace=true,requiredForRMG=false;
    bool allowBurrowing=true,allowTiberium=false;
};
struct TheaterTileInputs {
    std::array<int,16> depthBases{};
    std::vector<int> setStarts;
    std::vector<MapTileShift> shifts;
    std::vector<TheaterTileTypeInput> types;
};
// Selected projection of the complete original theater loader, with supplied INI
// results and every TMP/alternate image absent. No file/heap/INI parser/graphics
// reset/animation/loaded-image or full type construction claim. Include the final
// count=-1 entry: its set base is stored before the termination test.
TheaterTileInputs prepareTheaterTileInputs(const std::array<int,16>& setNumbers,
    std::span<const TheaterTileSetInput>);
}
