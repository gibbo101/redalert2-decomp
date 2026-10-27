// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/BorrowedCellUnitScatterWorld.hpp"
#include "assets/ProcessTerminalScatterWorld.hpp"
#include <memory>

namespace ra2 {
// Explicit bounded scenario inputs. No construction/pathfinding/mission-effect
// claim follows from these supplied type, table, frame and heap-service values.
struct OwnedUnitScatterInputs {
    MapPermissionShape permission;
    int dimension1=0,layerHeight=104,destinationDelay=0;
    // Authored bounded close threshold; not recovered rules initialization.
    int closeEnough=0;
    std::array<std::uint32_t,108> landSpeedBits{};
    std::vector<OverlayTypeInputs> overlays;
    std::vector<std::uint8_t> routeMask;
    OriginalRandomState random;
    std::uint8_t missionControl7=0,missionControl9=0,mission414Result=0,postCell490Result=0;
};
// Additional records on the production owner, not a second movement world.
// All kernel views borrow the existing admission/membership/Drive/timer owners.
class OwnedUnitScatter {
    const OwnedUnitScatterInputs& inputs_;
    PreparedMembershipMap map_;
    PreparedUnitMembership& member_;
    BorrowedPreparedUnitAdmission& admission_;
    std::array<GroundDriveProcessState*,2> drives_;
    std::array<PreparedAdmissionActor,2>& actors_;
    std::array<GroundDriveMovingWaitState,2>& waits_;
    std::array<UnitDestinationProfile,2> profiles_;
    std::array<UnitScatterExtra,2> extras_;
    std::array<std::uint8_t,2> flag76_{},flag7a_{},flag61_{},curve64_{};
    std::array<std::uint32_t,2> references_{1,1};
    std::uint32_t globalReferences_=0;
    std::array<double,2> veterancy_{};
    std::array<int,2> types_{0,0},padding_{};
    std::map<int,CellScatterType> typeRecords_{{0,{}}};
    std::map<int,int> houses_{{0,0}},speedTypes_{{0,1}};
    std::uint8_t rules1431_=1;
    int rules10b4_=0,floorHeight_,layerHeight_,frame_=0;
    OriginalRandomState random_;
    NearbyLocationPoint empty_{};
    std::vector<ScatterWorldCellBinding> cells_;
    std::vector<const OverlayTypeInputs*> overlays_;
    NearbyAdmissionServices nearbyAdmission_;
    std::function<NearbyAdmissionCell(const MapCellInput&)> bindCell_;
    std::array<std::unique_ptr<BorrowedUnitScatterWorldView>,2> units_;
    std::array<BorrowedUnitScatterWorldView*,2> views_{};
    std::array<bool,2> pendingRoutes_{};
    std::array<int,2> counter53c_{};
    int cellId(const MapCellInput* p)const{
        for(const auto& c:cells_)if(c.cell==p)return c.id;
        throw std::invalid_argument("Owned Scatter requires an actual bound Cell target");
    }
public:
    OwnedUnitScatter(const OwnedUnitScatter&)=delete;
    OwnedUnitScatter& operator=(const OwnedUnitScatter&)=delete;
    OwnedUnitScatter(PreparedMembershipMap map,PreparedUnitMembership& member,
        BorrowedPreparedUnitAdmission& admission,std::array<GroundDriveProcessState*,2> drives,
        std::array<PreparedAdmissionActor,2>& actors,std::array<GroundDriveMovingWaitState,2>& waits,
        const OwnedUnitScatterInputs& inputs)
        :inputs_(inputs),map_(map),member_(member),admission_(admission),drives_(drives),actors_(actors),waits_(waits),
         floorHeight_(map.levelHeight),layerHeight_(inputs.layerHeight),random_(inputs.random){
        if(map.levelHeight<=0||inputs.layerHeight<=0||inputs.routeMask.size()!=262144)
            throw std::invalid_argument("Owned Scatter requires explicit height and immutable route mask");
        cells_.reserve(map.cells.size()+1);
        for(std::size_t i=0;i<=map.cells.size();++i)
            cells_.push_back({&(i==map.cells.size()?map.fallback:*map.cells[i]).input,int(i),0});
        for(const auto& o:inputs.overlays)overlays_.push_back(&o);
        nearbyAdmission_.overlays=overlays_;nearbyAdmission_.speedBits=inputs.landSpeedBits;
        bindCell_=[this](const MapCellInput& c){
            const auto i=std::size_t(cellId(&c));
            const auto& a=i==map_.cells.size()?map_.fallback:*map_.cells[i];
            return NearbyAdmissionCell{c,member_.occupation[i].ground,member_.occupation[i].elevated,a.overlay};
        };
        for(int id:{0,1}){
            auto& d=*drives_[id];auto& wait=waits_[id];
            UnitDestinationView u{actors_[id].destination,d,member.actorDiscovery(id),globalReferences_,references_[id],
                GroundDriveTimerView{d.retryStart,d.retryPadding,d.retryRemaining},
                GroundDriveTimerView{wait.start,wait.padding,wait.remaining},
                [this,id](const void* target){pendingRoutes_[id]=target!=nullptr;}};
            units_[id]=std::make_unique<BorrowedUnitScatterWorldView>(BorrowedUnitScatterWorldView{
                u,profiles_[id],extras_[id],admission.world(),id,map.resident.world.cells,map.fallback.input,
                cells_,map.floor,floorHeight_,layerHeight_,inputs.permission,{}});
            views_[id]=units_[id].get();
        }
    }
    const MapCellInput* pendingRoute(int id)const{
        if(!pendingRoutes_.at(std::size_t(id)))return nullptr;
        const auto* p=static_cast<const MapCellInput*>(actors_[id].destination.target494);
        if(p)(void)cellId(p);
        return p;
    }
    void routed(int id){pendingRoutes_.at(std::size_t(id))=false;}
    int preparationCounter(int id)const{return counter53c_.at(std::size_t(id));}
    void clearTarget(int id){actors_.at(std::size_t(id)).destination.target494=nullptr;routed(id);}
    bool routeAllowed(int x,int y)const{
        return x>=0&&y>=0&&x<512&&y<512&&inputs_.routeMask[std::size_t(y)*512+std::size_t(x)];
    }
    // Clone only logical values. Views, target pointers and callbacks are rebound
    // by the enclosing owner, and production retry/wait words stay in that owner.
    void copyStateFrom(const OwnedUnitScatter& from){
        extras_=from.extras_;flag76_=from.flag76_;flag7a_=from.flag7a_;flag61_=from.flag61_;curve64_=from.curve64_;
        references_=from.references_;globalReferences_=from.globalReferences_;veterancy_=from.veterancy_;
        random_=from.random_;pendingRoutes_=from.pendingRoutes_;frame_=from.frame_;counter53c_=from.counter53c_;
    }
    bool process(int id,int speed,int tick,int timerPadding,const DriveData& data,
        const GroundDriveProcessServices& services,const GroundDriveAdmissionServices& admission,
        const std::function<bool(std::int16_t,std::int16_t)>& gate,const GroundDriveResidentRetry& retry,
        const GroundDriveMovingWaitServices& waiting,const GroundStateStore& actorStore,
        const GroundStateStore& rampStore,const ScatterWorldTrace& trace={},const std::function<bool()>& findRoute={}){
        frame_=tick;
        BorrowedCellUnitScatterView world{admission_.world(),views_,veterancy_,types_,{},{},typeRecords_,houses_,
            rules1431_,rules10b4_,&admission_.motion()};
        std::array<ScatterCellPoint,8> neighbors;
        for(int i=0;i<8;++i){const auto [x,y]=directionOffset(i);neighbors[i]={std::int16_t(x),std::int16_t(y)};}
        CellUnitScatterInputs input{data,services.squareRoot,random_,neighbors,padding_,floorHeight_,tick,
            inputs_.destinationDelay,data.stopScale,
            [this](int raw,int offset){
                if(raw!=2||(offset!=7&&offset!=9))throw UnsupportedUnitScatter("Owned Scatter mission control outside supplied Move profile");
                return offset==7?inputs_.missionControl7:inputs_.missionControl9;
            },[](int){return 1u;},[](int){}}; // Named successful host snapshot growth/release.
        CellNearbySearchInputs nearby{speedTypes_,inputs_.dimension1,frame_,empty_,bindCell_,nearbyAdmission_};
        AdvanceTerminalServices effects;effects.notify174=services.advance.notify;
        effects.mission414=[this](int,int){return inputs_.mission414Result;};
        effects.postCell490=[&]{services.advance.postCell();return inputs_.postCell490Result;};
        effects.store=[&](char owner,int off,int,std::uint32_t value){
            const auto& write=owner=='d'?services.advance.driveStore:actorStore;
            if(write)write(off,signed32(value));
        };
        const GroundDriveAdvanceAdmissionServices advanceAdmission{services.cell,services.wordCell,admission.check};
        std::uint32_t scratch=0; // Supplied unused incoming frame high word.
        const ProcessPreparationInputs preparation{inputs_.closeEnough,counter53c_[id],findRoute};
        const bool result=processWithTerminalScatter(id,speed,timerPadding,floorHeight_,services,advanceAdmission,
            gate,retry,waiting,scratch,world,input,nearby,{member_.actorMark(id).onMap,flag76_[id],flag7a_[id]},
            effects,{actors_[id].shortTrack,flag61_[id],curve64_[id]},{},actorStore,rampStore,trace,{},{},
            findRoute?&preparation:nullptr);
        return result;
    }
};
}
