// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MissionDefinition.hpp"
#include "render/CellRedraw.hpp"
#include "render/SurfaceFill.hpp"
#include "assets/MutableUnitMap.hpp"
#include "assets/VisibilityData.hpp"
#include "platform/BootCampMissionWorld.hpp"
#include "sim/CellVisibilityState.hpp"
#include "sim/CellClosestResident.hpp"
#include "sim/RevealArea.hpp"
#include "sim/PostSightRefresh.hpp"
#include "sim/TechnoSight.hpp"
#include "sim/VisibilityStartup.hpp"
#include "sim/MissionWaypointReveal.hpp"
#include <map>
#include <optional>

namespace ra2 {
struct SurfaceRefreshServices;struct RadarPixelServices;struct SurfaceRefreshScratch;
class RadarRefreshBinding;class RadarStorage;
class Renderer;
// Bounded shared owner for actual Day1 Cells and the two objective structures.
// It composes recovered mask/change/discovery kernels. Initial visibility bytes,
// redraw/refresh effects and invocation scheduling remain explicit adapters.
class BootCampVisibilityWorld {
    friend struct BootCampWalkWorldInspection;
public:
    struct State {
        std::size_t residentCount=0,reveals=0,revealAreas=0,sightAdds=0,sightRemovals=0,postSightCalls=0;
        std::size_t waypointReveals=0,waypointAreaCalls=0;
        std::size_t maskCalls=0,mapQueries=0,fallbackStores=0;
        std::size_t redraws=0,discoveryParents=0,cellNotifications=0,discoveredResidents=0,refreshes=0;
        int lastCell=-1,lastResident=-1,currentHouse=-1;
        TerrainCellPoint fallbackPoint{};
    };
private:
    MutableUnitMap& map_;
    VisibilityStartup startup_;
    VisibilityData data_;
    std::vector<CellVisibilityState> cells_;
    std::vector<CellVisibilityState*> table_;
    CellVisibilityState fallback_;
    std::function<CellClosestResidentServices(int)> residents_;
    std::function<bool(int,int)> discoveredBy_;
    BootCampMissionWorld& mission_;
    State state_;
    CellRedrawQueue redrawQueue_;
    std::function<void(int)> redrawEffect_; // Synchronous scoped binding; never cloned.
    void redrawCell(int);
    std::function<void(TerrainCellPoint)> radarNotificationEffect_; // Scoped, never cloned.
    std::function<double(double)> squareRoot_;
    // Authored scenario/rules startup, distinct from the reveal-area divisor.
    std::vector<std::uint8_t> scenario_;
    std::map<int,bool> suppliedWaypoints_;
    std::map<int,MissionWaypointRevealHouse> waypointHouses_;
    MissionWaypointRevealRules waypointRules_;
    std::int32_t waypointHeightScale_=104;
    RevealAreaWorld revealWorld();
    void applyRevealArea(const TechnoSightRequest&,bool sight,std::optional<std::uint32_t> refreshRules);

    int mapOrigin_=0,mapExtent_=0,heightDivisor_=0;
    int visibilityHeightDivisor_=104; // Separate verified5440D0 stock value, not a global alias.
    std::uint8_t revealByHeight_=0,allyReveal_=0;
    BootCampVisibilityWorld(const BootCampVisibilityWorld&,MutableUnitMap&,BootCampMissionWorld&,
        std::function<CellClosestResidentServices(int)>,std::function<bool(int,int)>,std::function<double(double)>);
    CellVisibilityState& cell(TerrainCellPoint);
    CellVisibilityState& cellAtIndex(std::int32_t,TerrainCellPoint);
    const CellVisibilityState& identity(int) const;
    CellVisibilityState& radarCell(const MapCellInput&);
    bool change(TerrainCellPoint,int house,std::uint32_t childArgument,std::optional<std::uint32_t> refreshRules);
public:
    BootCampVisibilityWorld(const MissionDefinition&,const Ini& mapIni,const Ini& rules,
        MutableUnitMap&,BootCampMissionWorld&,VisibilityData,
        std::size_t residentCount,std::function<CellClosestResidentServices(int)>,
        std::function<bool(int,int)> discoveredBy,std::function<double(double)> squareRoot);
    BootCampVisibilityWorld(const BootCampVisibilityWorld&)=delete;
    BootCampVisibilityWorld& operator=(const BootCampVisibilityWorld&)=delete;
    // Value snapshot with fresh borrowed terrain flags and resident callbacks.
    std::unique_ptr<BootCampVisibilityWorld> clone(MutableUnitMap&,BootCampMissionWorld&,
        std::function<CellClosestResidentServices(int)>,std::function<bool(int,int)>,std::function<double(double)>) const;
    // Explicit unscheduled refresh on this world's actual map/floor/visibility.
    // The caller must already bind shared surfaces/actors through association.
    void refreshRadar(SurfaceRefreshServices&,RadarPixelServices&,SurfaceRefreshScratch&,const RadarRefreshBinding&);
    // Explicit viewport association for existing sight/waypoint/post-sight calls.
    // Queue and frame5C persist; scope is synchronous and cannot be nested/cloned.
    void withCellRedraw(const std::int32_t& frame,const CellRedrawView&,const std::function<void()>&);
    void withRadarNotifications(RadarStorage&,const std::int32_t& originX,
        const std::int32_t& originY,const std::function<void()>&);
    const CellRedrawQueue& redrawQueue()const{return redrawQueue_;}
    TerrainCellPoint redrawCellPoint(int id)const{return identity(id).point;}
    Coord redrawCellCenter(int id); // Same actual Cell/floor owner as redraw production.
    std::int8_t redrawCellLevel(int id)const;
    // Object Mark and Cell redraw share one actual Tactical+D7D owner.
    void requestMapRedraw();
    std::uint32_t scenarioFlags() const; // Live first dword of the existing scenario owner.
    // Complete475520 with shared mask/Cell owners and Renderer alpha effects.
    // Explicit only: does not produce discovery, schedule a frame or clear queues.
    void drawCellVisibility(int identity,const PixelPoint&,const PixelRect&,Renderer&,
        const FillStoreTrace& stores={});
    void drawVisibilityRectangle(Renderer&,const PixelRect&,const std::function<bool()>& terrainPresent,
        const std::function<void(const PixelRect&)>& animation,const FillStoreTrace& stores={});
    // Explicit ordinary Building query over the existing table/shared fallback.
    // Numeric light state is borrowed from the receiving renderer, not copied.
    std::int16_t buildingAmbient(std::uint32_t packedCell,
        const std::function<std::int16_t(const CellVisibilityState&)>&);
    bool visible(Coord,bool secondary);
    bool reveal(TerrainCellPoint,int house,std::optional<std::uint32_t> refreshRules=std::nullopt);
    std::uint8_t revealWaypoint(std::int32_t);
    void revealSight(const TechnoSightRequest&,std::optional<std::uint32_t> refreshRules=std::nullopt);
    void refreshPostSight(Coord,std::int32_t innerRadius,std::int32_t outerRadius,std::uint32_t disabled);
    const void* house(int identity)const;
    int currentHouse()const{return state_.currentHouse;}
    const std::uint8_t& alliedVision()const{return allyReveal_;}
    const VisibilityStartup& startup()const{return startup_;}
    const CellVisibilityState& at(TerrainCellPoint point)const;
    const CellVisibilityState& fallback()const{return fallback_;}
    State state()const{return state_;}
};
}
