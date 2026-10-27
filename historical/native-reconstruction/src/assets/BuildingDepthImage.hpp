// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Archive.hpp"
#include "assets/Shp.hpp"
#include <functional>
#include <span>
namespace ra2 {
struct BuildingDepthImageState { std::shared_ptr<Bytes> raw; };
struct BuildingDepthImageServices {
    std::function<void(const std::shared_ptr<Bytes>&)> release781d3b;
    std::function<void(std::string_view)> construct468f50;
    std::function<std::uint32_t()> size2c;
    std::function<void()> destroy438410,destroy42f350;
    std::function<std::shared_ptr<Bytes>(std::uint32_t)> allocate782017;
    std::function<std::span<const std::uint8_t>(std::string_view)> source5956c0;
    // Read-only logical observers after the actual store, unused by runtime.
    std::function<void(const std::shared_ptr<Bytes>&)> globalStore;
    std::function<void(const Bytes&,std::uint32_t,std::uint32_t,std::uint32_t)> memoryStore;
};
// Complete458510 parent with explicit file/heap children. No file is modified.
// Initializer copies the entire file, then transforms first-frame canvas bytes.
void initializeBuildingDepthImage(BuildingDepthImageState&,const BuildingDepthImageServices&);
// Host AssetStore/heap adapter; source installation remains read-only. The SHP
// reader is the existing authored bounded parser, not original decoder recovery.
ShpImage loadBuildingDepthImage(const AssetStore&,BuildingDepthImageState&);
}
