// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <optional>
#include <span>
#include <vector>
namespace ra2 {
struct MapInputPosition {std::int16_t x=0,y=0;bool operator==(const MapInputPosition&) const=default;};
struct MapCellInput {
    MapInputPosition position{};
    int tile=65535,land=0;
    std::int16_t tube=-1;
    std::uint8_t subTile=0,ice=0,slope=0;
    std::int8_t level=0;
    std::uint32_t flags=0;
};
enum class MapInputField {Position,Tile,Tube,Land,Ice,SubTile,Level,Slope,Flags};
using MapInputStore=std::function<void(const MapCellInput*,MapInputField,std::uint32_t)>;
// Selected Cell constructor fields only; Abstract construction and all other
// Cell fields/registration/ownership are outside this projection.
void resetMapCellInput(MapCellInput&,MapInputPosition invalid,const MapInputStore& store={});
struct MapTileShift {int first=0,delta=0;};
int mapInputTileIndex(int index,std::span<const MapTileShift>);
// Complete IsoMapPack5 reader on a supplied decoded stream and 512*512 pointer
// table. Cell/stream construction, LZO and shift-table construction are separate.
// Returns consumed bytes, including the terminator; refuses truncated streams.
std::size_t loadIsoMapCellInputs(std::span<const std::uint8_t>,
    std::span<MapCellInput* const> cells,MapCellInput& fallback,
    MapInputPosition terminator,MapInputPosition constructorInvalid,
    std::span<const MapTileShift> shifts={},const MapInputStore& store={});
struct MapSubTileInput {
    std::uint8_t land=0,ramp=0;
    bool extra=false;
    int y=0,extraY=0;
};
struct MapTileImageInput {
    int columns=0,rows=0,width=60,height=30;
    std::vector<std::optional<MapSubTileInput>> subTiles;
};
// Resident TMP pointer-header consumers; loading/relocation/lazy image ownership
// is supplied. Negative subscripts and invalid geometry are native safety guards.
int mapTileLand(const MapTileImageInput*,int subTile,std::span<const int> landMap);
int mapTileRamp(const MapTileImageInput*,int subTile);
bool mapTileDimensions(const MapTileImageInput*,int subTile,int& width,int& height);
}
