// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/TheaterTileInputs.hpp"
#include "assets/TileImagePreparation.hpp"
#include <functional>
namespace ra2 {
struct LoadedTheaterTile {
    TheaterTileTypeInput type;
    int next=-1,variants=1;
    std::string source; // Host provenance, not the original lazy filename buffer.
    std::optional<PreparedTileImage> image;
};
struct LoadedTheaterTiles {
    TheaterTileInputs inputs;
    std::vector<LoadedTheaterTile> allTypes;
    std::vector<int> primary;
};
// Nonlazy, nonanimated theater 0/1/2 with supplied INI values and file-cache
// responses. Does not own the original heap/file cache or select cell variants.
// Relative TMP references and native safety guards follow prepareTileImage.
LoadedTheaterTiles prepareLoadedTheaterTiles(const std::array<int,16>& setNumbers,
    std::span<const TheaterTileSetInput>,std::span<const std::string> prefixes,int theater,
    const std::function<std::optional<Data>(const std::string&)>& find);
}
