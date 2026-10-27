// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "platform/OwnedUnitMoveCommand.hpp"
#include "platform/TerrainScenario.hpp"
#include "assets/UnitMovementRestriction.hpp"
#include "assets/PreparedData.hpp"
#include "assets/MapGeometry.hpp"
namespace ra2 {
// Bounded SDL-free two-Unit host. The world is the sole simulation owner; there
// is no Simulation/Drive mirror. Timing, controls and failed-route effects are
// supplied policies. The renderer receives borrowed actors plus an explicit tick.
class OwnedTerrainRuntime {
    std::unique_ptr<OwnedUnitWorld> world_;
    OwnedUnitClearance clearance_;
    OwnedUnitMovePolicy policy_;
    double stopScale_;
    int tick_=0;
    bool stepping_=false;
public:
    bool paused=false;
    std::string status="SELECT EITHER RHINO";
    static std::array<OwnedUnitWorldCall,2> calls(OwnedUnitWorld&){
        OwnedUnitWorldCall c;c.notify=[](int){};c.postCell=[]{ };c.noRoute=[]{ };c.failedRoute=[](int){};
        return {c,c};
    }
    OwnedTerrainRuntime(std::unique_ptr<OwnedUnitWorld> world,OwnedUnitClearance clearance,
        OwnedUnitMovePolicy policy,double stopScale,int tick=0)
        :world_(std::move(world)),clearance_(std::move(clearance)),policy_(policy),stopScale_(stopScale),tick_(tick){
        if(!world_)throw std::invalid_argument("Owned runtime requires a world");
        OwnedUnitSchedule::validate(policy_.step,calls(*world_));
        (void)OwnedUnitOrders(*world_,stopScale_);
        if(policy_.maxTicks<1||policy_.maxTicks>4096)throw std::invalid_argument("Owned runtime preview limit outside domain");
    }
    OwnedTerrainRuntime(const OwnedTerrainRuntime&)=delete;
    OwnedTerrainRuntime& operator=(const OwnedTerrainRuntime&)=delete;
    OwnedUnitWorld& world(){return *world_;}
    const OwnedUnitWorld& world()const{return *world_;}
    int tick()const{return tick_;}
    int selected()const{return world_->selected();}
    void select(int id){world_->select(id);status=id<0?"NO UNIT SELECTED":"RHINO "+std::to_string(id)+" SELECTED";}
    bool moving(int id){const auto& s=world_->actor(id).state;return s.movement.driving||s.route.front()!=-1||s.destination!=Coord{};}
    std::optional<OwnedUnitMoveResult> move(int x,int y,bool append=false){
        if(selected()<0)return {};
        auto result=commandOwnedUnitMove(*world_,selected(),x,y,append,stopScale_,policy_.step,clearance_,calls);
        if(result.status==OwnedUnitMoveStatus::accepted)status=append?"WAYPOINT APPENDED":"DIRECT ROUTE ACCEPTED";
        else if(result.status==OwnedUnitMoveStatus::unsupportedAdmission)status="UNSUPPORTED ADVANCE ADMISSION "+std::to_string(result.admission);
        else status="MOVEMENT REFUSED / NO DETOUR SEARCH";
        return result;
    }
    void stop(){if(selected()<0)return;OwnedUnitOrders(*world_,stopScale_).stop(selected());status="STOP / COMMITTED TRACK FINISHES";}
    void turnBody(int delta){if(selected()<0)return;OwnedUnitOrders(*world_,stopScale_).turnBody(selected(),delta,tick_);status="BODY TURN / COMMITTED TRACK FINISHES";}
    void turnTurret(int delta){if(selected()<0)return;world_->turnTurret(selected(),delta,tick_);status="MANUAL TURRET TURN";}
    void aim(Coord target,const DriveData& data){
        if(selected()<0||target.x<0||target.y<0||target.x>=512*256||target.y>=512*256)return;
        auto a=world_->actor(selected());const auto wanted=destinationDirection(data.directionsToTargets,a.state.movement.actor.position,target);
        world_->turnTurret(selected(),int(wanted)-int(a.turret.desired),tick_);status="MANUAL TURRET AIM";
    }
    void step(const std::array<OwnedUnitWorldCall,2>& effects,const std::function<void(int,bool)>& observer={}){
        if(stepping_)throw std::logic_error("Owned runtime cannot reenter");
        if(paused)return;
        OwnedUnitSchedule::validate(policy_.step,effects);
        struct Scope{bool& value;explicit Scope(bool& v):value(v){value=true;}~Scope(){value=false;}} scope(stepping_);
        tick_=signed32(std::uint32_t(tick_)+1u);
        OwnedUnitSchedule(*world_,stopScale_).step(tick_,policy_.step,effects,observer);
    }
    void step(){step(calls(*world_));}
};

inline std::unique_ptr<OwnedTerrainRuntime> ownedTerrainRuntime(const GameAssets& assets,
    OwnedUnitAdvancePolicy advancePolicy=OwnedUnitAdvancePolicy::guarded){
    if(advancePolicy!=OwnedUnitAdvancePolicy::guarded&&advancePolicy!=OwnedUnitAdvancePolicy::ordinaryAdmission&&
       advancePolicy!=OwnedUnitAdvancePolicy::ordinaryScatter)
        throw std::invalid_argument("Unknown owned runtime Advance policy");
    if(!assets.preparedTerrain||assets.engineDataSource!=PatchedEngineSha||assets.passive)
        throw std::invalid_argument("Owned runtime requires prepared ordinary base terrain");
    const Ini rules(assets.store.require("rules.ini").text());
    (void)readUnitMovementRestriction(rules,"HTNK");
    if(!rules.section("HTNK").contains("crusher")||!rules.boolean("HTNK","Crusher"))
        throw std::invalid_argument("Owned runtime requires explicit stock HTNK Crusher input");
    const auto prepared=assets.preparedTerrain;
    auto numeric=std::make_shared<const RenderData>(assets.renderData);
    GroundDriveProcessServices supplied;
    supplied.advance.notify=[](int){};supplied.advance.postCell=[]{ };supplied.noRoute=[]{ };
    supplied.uphill=prepared->uphill;supplied.downhill=prepared->downhill;
    for(unsigned i=0;i<12;++i)supplied.trackSpeed[i]=prepared->land[i].speed[unsigned(LandSpeed::Track)];
    supplied.squareRoot=[numeric](double n){return tableSqrt(*numeric,n);};
    GroundDriveProcessState first;first.movement.actor.position=cellCenter(86,101);first.movement.reached5a0=1;
    first.movement.body.setRate(assets.rot);first.movement.body.setCurrent(16384,0);
    auto context=std::make_unique<TerrainUnitContext>(std::make_shared<MutableUnitMap>(prepared->unitSeed(),prepared),supplied,first);
    GroundDriveProcessState second=first;second.movement.actor.position=cellCenter(90,101);
    UnitDiscoveryActor discovery;discovery.owner=0;discovery.mission98=2;discovery.queuedA0=-1;discovery.queuedA4=255;
    Facing turret0;turret0.setRate(assets.rot);turret0.setCurrent(16384,0);
    Facing turret1=turret0;turret1.setCurrent(32768,0);
    context->bindParked(second,{},discovery,{},turret1);
    // Preserve separate actors and the existing parked-before-mover Mark order.
    for(int id:{1,0}){
        auto& s=id?context->parked->state:context->state;
        const auto& v=id?context->parked->services:context->services;
        setActorRelativeHeight(s.movement.actor,0,416,v.advance.ground);
        unlimboDriveRamp(s.ramps,[&]{(void)v.cell(s.movement.actor.position);return v.cell(s.movement.actor.position).ramp;},0,0);
        v.advance.ground.mark(1);
    }
    OwnedUnitProcessesInputs inputs{5,1,0,0,8,
        std::array<OwnedUnitProcessActorInputs,2>{OwnedUnitProcessActorInputs{{0,0},0},OwnedUnitProcessActorInputs{{0,0},0}}};
    inputs.advancePolicy=advancePolicy;
    Bytes allowed(262144,0);
    for(int y=0;y<512;++y)for(int x=0;x<512;++x)allowed[std::size_t(y)*512+std::size_t(x)]=std::uint8_t(terrainCommandCell(assets,x,y));
    if(advancePolicy==OwnedUnitAdvancePolicy::ordinaryScatter){
        auto scatter=std::make_shared<OwnedUnitScatterInputs>();
        scatter->permission=mapPermissionShape({0,0,prepared->width,prepared->height},{0,0,prepared->width,prepared->height});
        scatter->dimension1=prepared->height;scatter->layerHeight=prepared->levelHeight;scatter->routeMask=allowed;
        // Explicit supplied timer input, matching the original-backed encounter.
        scatter->destinationDelay=inputs.waitDuration;
        for(unsigned land=0;land<12;++land){
            for(unsigned speed=0;speed<8;++speed)scatter->landSpeedBits[land*9+speed]=std::bit_cast<std::uint32_t>(prepared->land[land].speed[speed]);
            // Buildable occupies the ninth dword's low byte; retained upper
            // bytes are supplied zero. This Track-only caller never reads it.
            scatter->landSpeedBits[land*9+8]=prepared->land[land].buildable;
        }
        scatter->overlays.resize(prepared->overlays.size());
        for(std::size_t i=0;i<prepared->overlays.size();++i)scatter->overlays[i].wall=prepared->overlays[i].wall;
        inputs.scatter=std::move(scatter);
    }
    auto world=std::make_unique<OwnedUnitWorld>(std::move(context),assets.driveData,
        OwnedUnitWorldNumerics{numeric,[numeric](double n){return tableSqrt(*numeric,n);}},inputs,turret0);
    return std::make_unique<OwnedTerrainRuntime>(std::move(world),OwnedUnitClearance(allowed),
        OwnedUnitMovePolicy{{{assets.speed,assets.speed},{0,0}},4096},assets.driveData->stopScale);
}
}
