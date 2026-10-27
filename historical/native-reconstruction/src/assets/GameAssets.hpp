// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Archive.hpp"
#include "assets/Formats.hpp"
#include "assets/MovementData.hpp"
#include "assets/RenderData.hpp"
#include "assets/RasterData.hpp"
#include "assets/Shp.hpp"
#include "assets/TerrainTypes.hpp"
#include "assets/UnitDrawMetadata.hpp"
#include "assets/PreparedTerrainMap.hpp"
#include "sim/TerrainLifecycle.hpp"
#include <set>
#include <optional>

namespace ra2 {
int unitSpeedTypeDefault(int current,bool crusher);
struct VehiclePart { VoxelModel voxels; Animation animation; };
struct SceneryPlacement {int x=0,y=0;std::string type;};
struct StaticLightAsset {
    int radius=0;
    double intensity=0;
    std::array<double,3> tint{};
};
class GameAssets {
public:
    AssetStore store;
    std::string engineDataSource; // verified data profile; no original execution
    std::shared_ptr<const DriveData> driveData;
    RenderData renderData;
    RasterData rasterData;
    VoxelPalette voxelPalette;
    MapData map;
    std::shared_ptr<const PreparedTerrainMap> preparedTerrain; // Explicit opt-in; immutable shared records.
    Palette terrainPalette,unitPalette,stagingPalette;
    std::map<std::string,HsvColor> playerColors; // named [Colors] inputs, no house-ID assumptions
    std::map<std::uint32_t,std::vector<TileImage>> tiles;
    VehiclePart body,turret,barrel;
    UnitDrawMetadata unitDrawMetadata; // Patched healthy drawing fields only.
    int rot=0,speed=0;
    double extraUnitLight=0; // explicit rules value; quantized by render recovery
    bool passive=false;
    bool noShadow=false,disableShadowCache=false,disableVoxelCache=false;
    bool hasPlacedLights=false; // only the bounded placedLight profile is accepted
    std::optional<StaticLightAsset> invisibleLight; // bounded stock INGALITE, complete explicit keys
    std::optional<std::pair<int,int>> placedLight;
    std::string mapName;
    std::map<std::pair<int,int>,std::size_t> cellIndex;
    std::set<std::pair<int,int>> occupied;
    std::map<std::string,ShpImage> sceneryImages; // Verified healthy static trees/props only.
    std::vector<SceneryPlacement> scenery;
    TerrainLifecycle sceneryLifecycle; // Prepared healthy ordinary actors; SDL-free state.
    GameAssets(const std::filesystem::path& root,const std::string& mapFile,
               const std::filesystem::path& directionFile={},
               const std::filesystem::path& renderFile={},
               const std::filesystem::path& rasterFile={});
    const MapCell* cell(int x,int y) const;
    void prepareSceneryLifecycle(const TerrainLifeServices&);
    const TileImage& tile(const MapCell& c) const;
    bool clearCell(int x,int y,int z) const;
    void prepareTerrainMap(int levelHeight,int bridgeHeight);
    bool clearTerrainCell(int x,int y) const;
    std::pair<int,int> spawn() const;
};
}
