#include "sim/ScenarioSpecialFlags.hpp"
// SPDX-License-Identifier: GPL-3.0-or-later
#include "platform/BootCampVisibilityWorld.hpp"
#include "render/Renderer.hpp"
#include "assets/MapOverlayLoading.hpp"
#include "sim/CellVisibilityChange.hpp"
#include "sim/CellVisibilityDiscovery.hpp"
#include "sim/CellVisibilityMask.hpp"
#include "sim/Facing.hpp"
#include "sim/MapVisibility.hpp"
#include "sim/ScenarioWaypoint.hpp"
#include "render/UnitTypeVisibility.hpp"
#include "render/BuildingCellLight.hpp"
#include "render/RadarMap.hpp"
#include "render/RadarRefresh.hpp"
#include "render/RadarStorage.hpp"
#include "render/Redraw.hpp"
#include <cmath>
#include <sstream>
#include <stdexcept>

namespace ra2 {
namespace {
int slot(TerrainCellPoint point){return signed32(std::uint32_t(std::int32_t(point.y))*512u+std::uint32_t(std::int32_t(point.x)));}
}
BootCampVisibilityWorld::BootCampVisibilityWorld(const MissionDefinition& mission,const Ini& source,const Ini& rules,
        MutableUnitMap& map,BootCampMissionWorld& missionWorld,VisibilityData data,
        std::size_t residentCount,std::function<CellClosestResidentServices(int)> residents,
        std::function<bool(int,int)> discoveredBy,std::function<double(double)> squareRoot):map_(map),startup_(initializeVisibilityStartup()),data_(data),
        table_(262144,nullptr),fallback_(map.fallback.input.flags),mission_(missionWorld),mapOrigin_(map.width-1),mapExtent_(map.height),
        heightDivisor_(map.levelHeight),revealByHeight_(rules.boolean("General","RevealByHeight")),
        allyReveal_(rules.boolean("General","AllyReveal")){
    if(!residents||!discoveredBy||!squareRoot||!residentCount)throw std::invalid_argument("Visibility needs actual shared residents");
    residents_=std::move(residents);discoveredBy_=std::move(discoveredBy);squareRoot_=std::move(squareRoot);
    if(map.slots.size()!=table_.size())throw std::invalid_argument("Boot Camp visibility requires complete map slots");
    cells_.reserve(map.cells.size());
    for(auto& cell:map.cells)cells_.emplace_back(cell.attributes.input.flags);
    for(std::size_t i=0;i<cells_.size();++i){
        const auto& input=map.cells[i].attributes.input;auto& output=cells_[i];
        output.point={input.position.x,input.position.y};output.level11b=std::int8_t(input.level);output.identity=int(i);
    }
    for(std::size_t i=0;i<map.slots.size();++i){const int id=map.slots[i];if(id>=0){if(std::size_t(id)>=cells_.size())throw std::invalid_argument("Boot Camp visibility Cell slot differs");table_[i]=&cells_[std::size_t(id)];}}
    fallback_.point={map.fallback.input.position.x,map.fallback.input.position.y};fallback_.level11b=std::int8_t(map.fallback.input.level);fallback_.identity=-1;
    for(const auto& [id,name]:mission.houses){
        if(id<0||id>=32)throw std::invalid_argument("Boot Camp visibility House outside supplied association");
        if(mission_.house(id).indexAlliance.identity!=id)
            throw std::invalid_argument("Boot Camp visibility House association differs");
        if(lower(name)==lower(mission.player)){if(state_.currentHouse!=-1)throw std::invalid_argument("Repeated Boot Camp player House");state_.currentHouse=id;}
    }
    if(state_.currentHouse==-1)throw std::invalid_argument("Missing Boot Camp player House");
    // Bounded content-to-scenario association, not original INI/startup recovery.
    if(rules.get("General","RevealTriggerRadius").empty())throw std::invalid_argument("Missing reveal radius");
    waypointRules_.range54c=rules.integer("General","RevealTriggerRadius");
    if(waypointRules_.range54c<0)throw std::invalid_argument("Negative supplied reveal radius");
    scenario_.resize(0x632+4*702,0xff);
    // The containing allocation/constructor and session association stay supplied.
    // Registry absence is an explicit portable policy, never a host registry read.
    std::uint32_t flags=0;
    ScenarioFlagRegistryServices flagRegistry;
    flagRegistry.open=[](std::uint32_t&){return 2;};
    initializeScenarioSpecialFlags(flags,flagRegistry);
    readScenarioSpecialFlags(flags,0,0,[&source](std::string_view key,std::uint32_t fallback){
        return source.boolean("SpecialFlags",std::string(key),std::uint8_t(fallback));
    });
    for(unsigned i=0;i<4;++i)scenario_[i]=std::uint8_t(flags>>(8*i));
    for(const auto& [key,value]:source.section("Waypoints")){
        std::size_t a=0,b=0;const int index=std::stoi(key,&a),packed=std::stoi(value,&b);
        if(a!=key.size()||b!=value.size()||index<0||index>=702||packed<0||packed%1000>=512||packed/1000>=512||!suppliedWaypoints_.emplace(index,true).second)
            throw std::invalid_argument("Unsupported supplied waypoint record");
        const auto word=std::uint32_t(packed%1000)|(std::uint32_t(packed/1000)<<16);
        for(unsigned i=0;i<4;++i)scenario_[0x632+std::size_t(index)*4+i]=std::uint8_t(word>>(i*8));
    }
    for(const auto& [id,h]:mission_.houses())waypointHouses_.emplace(id,MissionWaypointRevealHouse{});
    state_.residentCount=residentCount;state_.fallbackPoint=fallback_.point;
}
BootCampVisibilityWorld::BootCampVisibilityWorld(const BootCampVisibilityWorld& from,MutableUnitMap& map,
        BootCampMissionWorld& mission,std::function<CellClosestResidentServices(int)> residents,
        std::function<bool(int,int)> discovered,std::function<double(double)> squareRoot):map_(map),startup_(from.startup_),data_(from.data_),
        table_(from.table_.size(),nullptr),fallback_(map.fallback.input.flags),residents_(std::move(residents)),
        discoveredBy_(std::move(discovered)),mission_(mission),state_(from.state_),
        mapOrigin_(from.mapOrigin_),mapExtent_(from.mapExtent_),heightDivisor_(from.heightDivisor_),
        visibilityHeightDivisor_(from.visibilityHeightDivisor_),revealByHeight_(from.revealByHeight_),allyReveal_(from.allyReveal_){
    if(from.redrawEffect_||from.radarNotificationEffect_)throw std::invalid_argument("Cannot clone active Cell redraw scope");
    redrawQueue_=from.redrawQueue_;
    squareRoot_=std::move(squareRoot);
    if(&map==&from.map_||&mission==&from.mission_||!residents_||!discoveredBy_||!squareRoot_||
       map.slots!=from.map_.slots||map.cells.size()!=from.cells_.size()||map.width!=from.map_.width||
       map.height!=from.map_.height||map.levelHeight!=from.map_.levelHeight)
        throw std::invalid_argument("Boot Camp visibility clone requires independent matching map/mission owners");
    scenario_=from.scenario_;suppliedWaypoints_=from.suppliedWaypoints_;waypointHouses_=from.waypointHouses_;
    waypointRules_=from.waypointRules_;waypointHeightScale_=from.waypointHeightScale_;
    cells_.reserve(from.cells_.size());
    for(std::size_t i=0;i<from.cells_.size();++i){
        cells_.emplace_back(map.cells[i].attributes.input.flags);cells_.back()=from.cells_[i];
    }
    fallback_=from.fallback_;
    for(std::size_t i=0;i<map.slots.size();++i){const int id=map.slots[i];
        if(id>=0)table_[i]=&cells_.at(std::size_t(id));
    }
}
std::unique_ptr<BootCampVisibilityWorld> BootCampVisibilityWorld::clone(MutableUnitMap& map,BootCampMissionWorld& mission,
        std::function<CellClosestResidentServices(int)> residents,std::function<bool(int,int)> discovered,std::function<double(double)> squareRoot)const{
    return std::unique_ptr<BootCampVisibilityWorld>(new BootCampVisibilityWorld(*this,map,mission,std::move(residents),std::move(discovered),std::move(squareRoot)));
}
CellVisibilityState& BootCampVisibilityWorld::cell(TerrainCellPoint point){
    return cellAtIndex(slot(point),point);
}
CellVisibilityState& BootCampVisibilityWorld::cellAtIndex(std::int32_t index,TerrainCellPoint point){
    CellVisibilityState* found=nullptr;
    if(index>=0&&index<int(table_.size()))found=table_[std::size_t(index)];
    if(!found){map_.fallback.input.position={point.x,point.y};fallback_.point=point;++state_.fallbackStores;state_.fallbackPoint=point;found=&fallback_;}
    ++state_.mapQueries;state_.lastCell=found->identity;return *found;
}
const CellVisibilityState& BootCampVisibilityWorld::identity(int id)const{
    if(id==-1)return fallback_;if(id<0||std::size_t(id)>=cells_.size())throw std::invalid_argument("Foreign visibility Cell identity");return cells_[std::size_t(id)];
}
const CellVisibilityState& BootCampVisibilityWorld::at(TerrainCellPoint point)const{
    const int index=slot(point);if(index<0||index>=int(table_.size())||!table_[std::size_t(index)])throw std::invalid_argument("Missing actual visibility Cell");return *table_[std::size_t(index)];
}
Coord BootCampVisibilityWorld::redrawCellCenter(int id){
    (void)identity(id); // Refuse foreign identities before touching map backing.
    const auto& input=id==-1?map_.fallback.input:map_.cells.at(std::size_t(id)).attributes.input;
    return mapCellCenterHeight(map_.floor,map_.levelHeight,input);
}
std::int8_t BootCampVisibilityWorld::redrawCellLevel(int id)const{
    (void)identity(id);
    return id==-1?map_.fallback.input.level:map_.cells.at(std::size_t(id)).attributes.input.level;
}
void BootCampVisibilityWorld::redrawCell(int id){
    ++state_.redraws;state_.lastCell=id;
    if(redrawEffect_)redrawEffect_(id); // Otherwise retain the explicit supplied recorder boundary.
}
void BootCampVisibilityWorld::requestMapRedraw(){
    requestMapRedrawZero(&redrawQueue_.dirtyD7D);
}
void BootCampVisibilityWorld::withCellRedraw(const std::int32_t& frame,const CellRedrawView& view,
        const std::function<void()>& operation){
    if(redrawEffect_||!operation)throw std::invalid_argument("Invalid/nested Cell redraw scope");
    redrawEffect_=[this,&frame,&view](int id){
        auto& cell=id==-1?fallback_:cells_.at(std::size_t(id));
        auto& input=id==-1?map_.fallback.input:map_.cells.at(std::size_t(id)).attributes.input;
        CellRedrawServices services;
        services.center475D60=[this,&input]{return mapCellCenterHeight(map_.floor,map_.levelHeight,input);};
        services.height6A2970=[this](auto z){return projectVisibilityHeight(z,startup_.heightProjectionScale);};
        requestCellRedraw({id,cell.redrawFrame5c,cell.flags12c,cell.redraw138},frame,view,redrawQueue_,services);
    };
    try{operation();}catch(...){redrawEffect_={};throw;}
    redrawEffect_={};
}
void BootCampVisibilityWorld::withRadarNotifications(RadarStorage& storage,
        const std::int32_t& originX,const std::int32_t& originY,const std::function<void()>& operation){
    if(radarNotificationEffect_||!operation)throw std::invalid_argument("Invalid/nested radar notification scope");
    radarNotificationEffect_=[this,&storage,&originX,&originY](TerrainCellPoint point){
        storage.notifyCell(point,map_.width,originX,originY);
    };
    try{operation();}catch(...){radarNotificationEffect_={};throw;}
    radarNotificationEffect_={};
}
bool BootCampVisibilityWorld::change(TerrainCellPoint point,int house,std::uint32_t childArgument,std::optional<std::uint32_t> refreshRules){
    if(house!=state_.currentHouse)
        throw std::invalid_argument("Boot Camp visibility supports only the current player House");
    (void)at(point);
    CellVisibilityMaskWorld mask{table_,&fallback_};
    mask.fallbackStore=[this](TerrainCellPoint p){map_.fallback.input.position={p.x,p.y};++state_.fallbackStores;state_.fallbackPoint=p;};
    mask.query=[this](TerrainCellPoint,int id){++state_.mapQueries;state_.lastCell=id;};
    CellVisibilityChangeWorld world{table_,&fallback_};
    world.fallbackStore=mask.fallbackStore;world.query=mask.query;
    CellVisibilityChangeServices services;
    services.visibilityValue=[this,&mask](TerrainCellPoint p,bool mode){++state_.maskCalls;return std::uint8_t(cellVisibilityMask(p,mode,data_.maskResults,mask));};
    services.redraw=[this](int id){redrawCell(id);};
    services.refresh=[this](int id){++state_.refreshes;state_.lastCell=id;};
    services.discover=[this](int starting,int discoverer,bool notify){
        ++state_.discoveryParents;
        CellVisibilityDiscoveryServices discovery;
        discovery.point=[this](int id){return identity(id).point;};
        discovery.cellAt=[this](TerrainCellPoint p){return cell(p).identity;};
        discovery.level=[this](int id){return identity(id).level11b;};
        discovery.notifyCell=[this](TerrainCellPoint p){++state_.cellNotifications;if(radarNotificationEffect_)radarNotificationEffect_(p);};
        discovery.residents=[this](int cellId){return residents_(cellId);};
        discovery.discoveredBy=[this](int resident,int h){
            if(h!=state_.currentHouse)throw std::invalid_argument("Visibility discovery House changed during dispatch");
            if(discoveredBy_(resident,h)){++state_.discoveredResidents;state_.lastResident=resident;}
        };
        discoverVisibleCellResidents(starting,discoverer,notify,discovery);
    };
    ++state_.reveals;
    return changeCellVisibilityWithLiveRefreshFlags(point,house,childArgument,world,
        [this,refreshRules]{return refreshRules?*refreshRules:scenarioFlags();},services);
}
CellVisibilityState& BootCampVisibilityWorld::radarCell(const MapCellInput& input){
    if(&input==&map_.fallback.input)return fallback_;
    // Reuse the map's canonical pointer/slot validation; stored coordinates do
    // not promote a foreign Cell into this world. No visibility query here.
    if(!map_.find(input))throw std::invalid_argument("Foreign Boot Camp radar Cell");
    const int id=map_.slots.at(std::size_t(slot({input.position.x,input.position.y})));
    auto& cell=cells_.at(std::size_t(id));
    if(&cell.flags140!=&input.flags)throw std::invalid_argument("Split Boot Camp radar terrain flags");
    return cell;
}
void BootCampVisibilityWorld::refreshRadar(SurfaceRefreshServices& refresh,RadarPixelServices& radar,
        SurfaceRefreshScratch& scratch,const RadarRefreshBinding& association){
    if(!association.binds(refresh,radar)||radar.currentHouseA35DB4!=house(state_.currentHouse))
        throw std::invalid_argument("Boot Camp radar refresh needs shared services and actual player House");
    MapFloorHeightWorld floor{map_.table,&map_.fallback.input,{}};
    floor.fallbackStore=[this](MapInputPosition p){
        fallback_.point={p.x,p.y};++state_.fallbackStores;state_.fallbackPoint=fallback_.point;
    };
    RadarMapWorld world{floor,[this](const MapCellInput& input){
        const auto& c=radarCell(input);return RadarMapDiscoveryFields{c.flags12c,c.count13c};
    }};
    world.query=[this](char,TerrainCellPoint p){
        ++state_.mapQueries;const int at=slot(p);
        state_.lastCell=at>=0&&at<int(map_.slots.size())?map_.slots[std::size_t(at)]:-1;
    };
    // Same independent stock divisor/mode/override association used by visible().
    // Primary/count predicates do not consume the secondary mode shortcut.
    const MapVisibilityState state{visibilityHeightDivisor_,0,0,mission_.house(state_.currentHouse).field13d};
    RadarMapBinding binding(radar,map_.floor,map_.levelHeight,state,world);
    refreshSurfaces(refresh,scratch);
}
std::uint32_t BootCampVisibilityWorld::scenarioFlags()const{
    std::uint32_t flags=0;for(unsigned i=0;i<4;++i)flags|=std::uint32_t(scenario_.at(i))<<(8*i);
    return flags;
}
std::int16_t BootCampVisibilityWorld::buildingAmbient(std::uint32_t packedCell,
        const std::function<std::int16_t(const CellVisibilityState&)>& ambient){
    return buildingCellLight(packedCell,revealWorld(),ambient);
}
bool BootCampVisibilityWorld::visible(Coord coordinates,bool secondary){
    MapVisibilityWorld world;world.direction3={1,1}; // Independently verified491620 direction3, not spread order.
    world.borrowedCell=[this](TerrainCellPoint point){const auto& c=cell(point);return MapVisibilityCell{c.point,c.flags12c,c.flags140};};
    MapVisibilityState state{visibilityHeightDivisor_,mission_.discoveryMode(),0,mission_.house(state_.currentHouse).field13d}; // Override remains supplied.
    return secondary?mapSecondaryVisibility(coordinates,state,world):mapPrimaryVisibility(coordinates,state,world);
}
bool BootCampVisibilityWorld::reveal(TerrainCellPoint point,int house,std::optional<std::uint32_t> refreshRules){
    return change(point,house,0,refreshRules);
}
const void* BootCampVisibilityWorld::house(int identity)const{
    const auto found=mission_.houses().find(identity);if(found==mission_.houses().end())throw std::invalid_argument("Foreign Boot Camp visibility House");return &found->second.indexAlliance;
}
RevealAreaWorld BootCampVisibilityWorld::revealWorld(){
    RevealAreaWorld world{mapOrigin_,mapExtent_,table_,table_,&fallback_};
    world.fallbackStore=[this](char,TerrainCellPoint p){map_.fallback.input.position={p.x,p.y};++state_.fallbackStores;state_.fallbackPoint=p;};
    world.query=[this](char,TerrainCellPoint,int id){++state_.mapQueries;state_.lastCell=id;};
    return world;
}
void BootCampVisibilityWorld::revealSight(const TechnoSightRequest& request,std::optional<std::uint32_t> refreshRules){applyRevealArea(request,true,refreshRules);}
std::uint8_t BootCampVisibilityWorld::revealWaypoint(std::int32_t index){
    auto* current=&waypointHouses_.at(state_.currentHouse);auto* rules=&waypointRules_;
    MissionWaypointRevealWorld globals{current,rules,waypointHeightScale_};
    MissionWaypointRevealServices services;
    services.waypoint=[this](std::int32_t n){
        if(!suppliedWaypoints_.contains(n))throw std::invalid_argument("Undefined supplied waypoint");
        return scenarioWaypoint(scenario_,n);
    };
    const auto world=revealWorld();
    services.cell=[&world](TerrainCellPoint point){const auto& c=revealAreaMapCell(point,world);return MissionWaypointRevealCell{c.flags140,c.level11b};};
    services.reveal=[this](Coord p,std::int32_t range,MissionWaypointRevealHouse* h,auto a,auto b,auto c,auto d,auto e){
        if(h!=&waypointHouses_.at(state_.currentHouse))throw std::invalid_argument("Foreign waypoint House");
        ++state_.waypointAreaCalls;
        applyRevealArea({p,range,house(state_.currentHouse),a,b,c,d,e},false,std::nullopt);
    };
    ++state_.waypointReveals;return revealMissionWaypoint(index,globals,services);
}
void BootCampVisibilityWorld::applyRevealArea(const TechnoSightRequest& request,bool sight,std::optional<std::uint32_t> refreshRules){
    const auto* requested=static_cast<const RevealAreaHouse*>(request.house);
    const auto current=mission_.houses().find(state_.currentHouse);
    // Validate by address before dereferencing. A House from another world (even
    // with the same logical identity) must never reach this world's Cells.
    bool owned=false;for(const auto& [id,h]:mission_.houses())if(requested==&h.indexAlliance){owned=true;break;}
    if(current==mission_.houses().end()||!owned)
        throw std::invalid_argument("Boot Camp sight composition requires an owned House");
    const auto world=revealWorld();
    RevealAreaTables tables{startup_.radiusCounts,startup_.offsets,startup_.heightOffsets};
    RevealAreaState state{heightDivisor_,startup_.heightProjectionScale,revealByHeight_,allyReveal_,const_cast<RevealAreaHouse*>(&current->second.indexAlliance)};
    RevealAreaServices services;
    services.housePredicate=[](const RevealAreaHouse& a,const RevealAreaHouse& b){
        return unitOwnerAlliedToCurrent(true,&a==&b,a.countryIndex,b.countryIndex,a.allianceMask);
    };
    services.squareRoot=squareRoot_;
    services.fogCell=[](TerrainCellPoint,const RevealAreaHouse&){throw std::invalid_argument("Fog child is outside Boot Camp ordinary sight composition");};
    services.revealCell=[this,refreshRules](TerrainCellPoint point,const RevealAreaHouse& h,std::uint32_t child){(void)change(point,h.identity,child,refreshRules);};
    ++state_.revealAreas;if(sight){if(std::uint8_t(request.fixed2))++state_.sightRemovals;else ++state_.sightAdds;}
    revealArea(request.coordinates,request.range,const_cast<RevealAreaHouse*>(requested),request.forwarded1,
        request.forwarded2,request.fixed0,request.fixed1,request.fixed2,world,tables,state,services);
}
void BootCampVisibilityWorld::drawVisibilityRectangle(Renderer& renderer,const PixelRect& requested,
        const std::function<bool()>& present,const std::function<void(const PixelRect&)>& animation,const FillStoreTrace& stores){
    RectangularVisibilityServices s;
    s.coordinateCell548000=[this](Coord p){
        const auto x=p.x/256,y=p.y/256;
        return cellAtIndex(signed32(std::uint32_t(y)*512u+std::uint32_t(x)),
            {std::bit_cast<std::int16_t>(std::uint16_t(x)),std::bit_cast<std::int16_t>(std::uint16_t(y))}).point;
    };
    s.terrainPresent=present;
    s.permitted54aab0=[this](TerrainCellPoint p){return std::uint8_t(overlayMapPositionPermitted({p.x,p.y},map_.width,map_.height));};
    s.cell548070=[this](TerrainCellPoint p){return cell(p).identity;};
    s.draw475520=[&](int id,const PixelPoint& p,const PixelRect& clip){drawCellVisibility(id,p,clip,renderer,stores);};
    s.animation41f5e0=animation;
    renderer.drawVisibilityRectangle(requested,std::move(s));
}
void BootCampVisibilityWorld::drawCellVisibility(int id,const PixelPoint& point,const PixelRect& clip,
        Renderer& renderer,const FillStoreTrace& stores){
    // Validate logical identity before selecting the existing mutable owner.
    auto& selected=const_cast<CellVisibilityState&>(identity(id));
    CellVisibilityMaskWorld mask{table_,&fallback_};
    mask.fallbackStore=[this](TerrainCellPoint p){map_.fallback.input.position={p.x,p.y};++state_.fallbackStores;state_.fallbackPoint=p;};
    mask.query=[this](TerrainCellPoint,int cellId){++state_.mapQueries;state_.lastCell=cellId;};
    CellVisibilityDrawServices s;
    s.mask6a8d40=[&](const TerrainCellPoint& p,bool secondary){++state_.maskCalls;return cellVisibilityMask(p,secondary,data_.maskResults,mask);};
    s.scenarioFlags=[this]{return scenarioFlags();};s.house13d=[this]{return mission_.house(state_.currentHouse).field13d;};
    s.shroud474260=[&](const PixelPoint& p,const PixelRect& r,int frame){renderer.drawVisibilityMask(false,p,r,frame,s.scenarioFlags,stores);};
    s.fog474510=[&](const PixelPoint& p,const PixelRect& r,int frame){renderer.drawVisibilityMask(true,p,r,frame,s.scenarioFlags,stores);};
    ra2::drawCellVisibility(selected,point,clip,s);
}
void BootCampVisibilityWorld::refreshPostSight(Coord coordinates,std::int32_t innerRadius,
        std::int32_t outerRadius,std::uint32_t disabled){
    CellVisibilityMaskWorld mask{table_,&fallback_};
    mask.fallbackStore=[this](TerrainCellPoint p){map_.fallback.input.position={p.x,p.y};++state_.fallbackStores;state_.fallbackPoint=p;};
    mask.query=[this](TerrainCellPoint,int id){++state_.mapQueries;state_.lastCell=id;};
    PostSightRefreshWorld world{table_,&fallback_};world.fallbackStore=mask.fallbackStore;world.query=mask.query;
    PostSightRefreshServices services;
    services.visibilityMask=[this,&mask](TerrainCellPoint point){++state_.maskCalls;return std::uint8_t(cellVisibilityMask(point,false,data_.maskResults,mask));};
    services.redraw=[this](int id){redrawCell(id);};
    ++state_.postSightCalls;
    refreshPostSightVisibility(coordinates,innerRadius,outerRadius,disabled,world,startup_,services);
}
}
