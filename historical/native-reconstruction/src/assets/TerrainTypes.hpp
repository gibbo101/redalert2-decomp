// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <optional>
#include <string>
#include <vector>
namespace ra2 {
int terrainStrengthDefault(int current,int rulesTreeStrength);
const std::vector<std::string>& stockStaticPropTypes();
struct TerrainImageReload {std::string filename;bool releasePrevious=false;};
// Exact-base theater reload decisions, with resource storage supplied by the host.
// Only base Temperate/Snow/Urban ordinals; other theaters are not established.
std::optional<TerrainImageReload> terrainImageReload(const std::string& id,bool theaterImage,
    bool ownsImage,std::uint32_t image,bool force,int requestedTheater,int previousTheater);
}
