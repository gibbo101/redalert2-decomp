// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Archive.hpp"
#include "assets/Formats.hpp"
#include "assets/ResidentMapFloor.hpp"
#include "assets/LandCharacteristics.hpp"
#include "assets/TheaterTileInputs.hpp"
#include "assets/PreparedDriveTerrain.hpp"
#include "assets/MutableUnitMap.hpp"
#include "assets/TileSweep.hpp"
#include "assets/OverlayTypeInputs.hpp"
#include "assets/OverlayImage.hpp"
#include <memory>
namespace ra2 {
struct MapRuntimeData {
    std::array<int,16> landMap{};
    std::array<std::uint8_t,9> frames{};
    MapFloorHeightState floor;
};
MapRuntimeData readMapRuntimeData(const Data&);
struct PreparedTerrainMapPolicy {
    bool deferCellTags=false;
    bool resourceValueOverrides=false; // Bounded map Value-only input association.
};
// Opt-in host file/record association around verified preparation. Initial
// fields, primary-image selection, raw overlay placement and empty actor/house
// registries remain adapters. This does not reconstruct scenario startup.
class PreparedTerrainMap {
public:
    std::vector<MapFinalizationCell> cells;
    std::vector<int> lightingLevels; // Captured at original pre-recalculation lighting call.
    std::vector<MapCellInput*> table;
    std::vector<int> slots;
    // Canonical immutable file bytes plus prepared metadata on existing type owners.
    // Primary-only association/variants=1 remain supplied, as before.
    std::vector<TileSweepType> tileImages;
    std::vector<MapTileAttributes> tiles;
    std::vector<std::string> filenames;
    std::vector<MapOverlayType> overlays;
    std::vector<OverlayTypeInputs> overlayInputs; // Retain constructed/INI fields and names.
    std::vector<std::optional<Data>> overlayImages;
    std::vector<std::uint8_t> overlayImageOwned;
    std::array<LandCharacteristic,12> land{};
    TheaterTileInputs theater;
    MapFloorHeightState initialFloor;
    MapCellAttributes initialFallback;
    std::array<int,16> landMap;
    std::array<float,11> wheelSpeeds;
    std::vector<MapResourceType> resourceTypes;
    ResidentCellInputs membershipResident;
    Bytes buffer4,buffer10;
    int width=0,height=0;
    int levelHeight=0,bridgeHeight=0;
    bool cellTagsDeferred=false; // Explicit host binding; MissionDefinition retains tags, no effects execute.
    double uphill=1,downhill=1.2;
    PreparedTerrainMap(const AssetStore&,const Ini& map,const MapRuntimeData&,int levelHeight,int bridgeHeight,PreparedTerrainMapPolicy policy={});
    PreparedTerrainMap(const PreparedTerrainMap&)=delete;
    PreparedTerrainMap& operator=(const PreparedTerrainMap&)=delete;
    const MapCellAttributes* find(int x,int y) const;
    UnitMapSeed unitSeed() const;
    // Explicit demand query only; does not synthesize nonlazy startup images.
    OverlayImageResult demandOverlayImage(const AssetStore&,int type,int requestedTheater);
    // Explicit complete5D7630 policy; original caller/scheduling remains unbound.
    void initializeOverlayImage(const AssetStore&,int type,int requestedTheater);
};
// Each simulation/preview/drawing context owns its lazy floor/fallback state.
// Immutable canonical Cells/images remain shared, with stable pointer identity.
class TerrainMapView {
    std::shared_ptr<const PreparedTerrainMap> map_;
public:
    MapFloorHeightState floorState;
    MapCellAttributes fallback;
    explicit TerrainMapView(std::shared_ptr<const PreparedTerrainMap>);
    MapFloorHeightWorld world();
    const MapCellInput& coordinate(Coord);
    const MapCellAttributes& cell(MapInputPosition);
    int floor(Coord);
    int relative(Coord);
    // Optional validation is outside recovered query tracing.
    GroundDriveProcessServices movementServices(const std::function<void(const MapCellInput&)>& check={});
};
}
