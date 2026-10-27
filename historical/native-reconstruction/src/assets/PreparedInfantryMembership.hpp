// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/PreparedWalkMap.hpp"
#include "sim/BorrowedMembership.hpp"
#include "sim/InfantrySubcell.hpp"
#include "sim/UnitMark.hpp"
#include "assets/OccupiedCellPassability.hpp"
#include <functional>
namespace ra2 {
// Additional actual Cell fields absent from terrain preparation. One enclosing
// world owns these records; admission/head/Mark must borrow the same instances.
struct InfantryMembershipCell {
    int head=-1,alternateHead=-1;
    std::uint32_t ground=0,elevated=0;
    int groundHouse=-1,elevatedHouse=-1;
    std::int16_t registry=-1;
};
struct InfantryMembershipActor {
    ActorGroundState& ground;
    WalkMovementState& walk;
    int& next;
    const std::uint8_t& eligible;
    const std::uint8_t& typeMapFlag;
    FootMarkView mark;
    std::reference_wrapper<const int> houseIndex;
    const int& owner;
    const int& imageValue;
};
// Ordinary Infantry/Walk binding on the existing mutable terrain map. No dummy
// Drive or copied actor/Cell/occupation. Initial associations, visibility,
// notification and special-event effects remain supplied. Recalculation can
// explicitly borrow the same map buffers and current Infantry primary lists.
class PreparedInfantryMembership {
    friend class PreparedInfantryWalk;
    MutableUnitMap& map_;
    std::function<void(MapInputPosition)> assignedFallback_;
    PreparedWalkMap walkMap_;
    std::span<InfantryMembershipCell> cells_;
    std::map<int,InfantryMembershipActor> actors_;
    const int& threshold_;
    std::function<double(double)> squareRoot_;
    BorrowedMembershipWorld world_;
    std::map<const void*,int> cellIds_;
    MapCellInput& input(int id){return id==int(map_.cells.size())?map_.fallback.input:map_.cells.at(std::size_t(id)).attributes.input;}
public:
    InfantryOccupationStore occupationStore;
    std::function<void()> redrawMap;
    std::function<void(int,int)> specialEvent;
    PreparedInfantryMembership(MutableUnitMap& map,std::span<InfantryMembershipCell> cells,
        std::map<int,InfantryMembershipActor> actors,UnitFoundationState& foundation,
        const int& threshold,std::function<double(double)> squareRoot,
        std::function<void(MapInputPosition)> assignedFallback={})
        :map_(map),assignedFallback_(std::move(assignedFallback)),walkMap_(map,assignedFallback_),cells_(cells),actors_(std::move(actors)),
         threshold_(threshold),squareRoot_(std::move(squareRoot)),world_{foundation} {
        if(cells_.size()!=map_.cells.size()+1||actors_.empty()||!squareRoot_)
            throw std::invalid_argument("Infantry membership requires actual map, occupation and numeric owners");
        std::map<const void*,int> coordinates,walks,nexts;
        for(const auto& [id,a]:actors_){
            if(id<0||&a.mark.onMap!=&a.ground.marked74||
               !coordinates.emplace(&a.ground.position,id).second||!walks.emplace(&a.walk,id).second||!nexts.emplace(&a.next,id).second)
                throw std::invalid_argument("Infantry membership requires distinct actual actor/Walk/Next owners");
            world_.actors.emplace(id,MembershipActorView{a.ground.position,a.next,a.ground.bridge79,a.eligible,a.typeMapFlag,15});
        }
        world_.fallbackCell=int(map_.cells.size());
        for(int i=0;i<=world_.fallbackCell;++i){auto& c=cells_[std::size_t(i)];auto& p=input(i).position;
            cellIds_.emplace(&input(i),i);world_.cells.emplace(i,MembershipCellView{{p.x,p.y},c.head,c.alternateHead});
        }
        world_.slotCell=[this](int slot){
            const int id=map_.slots.at(std::size_t(slot));
            if(id==-1){if(map_.table[std::size_t(slot)])throw std::invalid_argument("Split Infantry missing slot");return -1;}
            if(id<0||std::size_t(id)>=map_.cells.size()||map_.table[std::size_t(slot)]!=&input(id))
                throw std::invalid_argument("Split Infantry map slot association");
            return id;
        };
        world_.services.centerFloor=[this](int id){const auto& c=input(id);return cellFloorHeight(map_.floor,map_.levelHeight,c.level,c.slope,128,128);};
    }
    PreparedInfantryMembership(const PreparedInfantryMembership&)=delete;
    PreparedInfantryMembership& operator=(const PreparedInfantryMembership&)=delete;
    PreparedInfantryMembership(PreparedInfantryMembership&&)=delete;
    PreparedInfantryMembership& operator=(PreparedInfantryMembership&&)=delete;
    BorrowedMembershipWorld& world(){return world_;}
    PreparedWalkMap& walkMap(){return walkMap_;}
    const InfantryMembershipActor& actor(int id)const{return actors_.at(id);}
    int cellId(WalkMovementCellView view){return cellIds_.at(&walkMap_.attributes(view).input);}
    int cellId(const void* identity)const{
        const auto found=cellIds_.find(identity);
        if(found==cellIds_.end())throw std::invalid_argument("Foreign Infantry resident Cell identity");
        return found->second;
    }
    MapCellAttributes& attributes(int id){return id==int(map_.cells.size())?map_.fallback:map_.cells.at(std::size_t(id)).attributes;}
    // Complete recovered Cell/LAT/permission/passability chain on the actual
    // late-reloaded identity. Building/Terrain child records remain unbound in
    // this Infantry adapter and refuse only if their kind is actually queried.
    void recalculate(int id,int level,const ResidentCellServices& observers={}){
        auto& c=attributes(id);
        if(map_.buffer4.empty()||map_.buffer4.size()%4||map_.buffer10.size()/10!=map_.buffer4.size()/4||map_.buffer10.size()%10)
            throw std::invalid_argument("Infantry recalculation requires complete shared map buffers");
        auto inputs=map_.resident;inputs.fallback=id==int(map_.cells.size());
        inputs.world={map_.table,&map_.fallback.input,map_.resident.world.query,assignedFallback_};
        auto services=observers;
        if(services.occupiedPassability)throw std::invalid_argument("Infantry recalculation owns its actual-list passability child");
        services.occupiedPassability=[&](MapCellAttributes& cell,bool permitted,const MapOverlayType* overlay){
            OccupiedCellPassabilityWorld occupants;occupants.head=cells_[std::size_t(id)].head;
            for(const auto& [actor,a]:world_.actors){auto& view=occupants.actors[actor];view.kind=a.kind;view.next=a.next;}
            occupants.kindQuery=[](int,int kind){if(kind!=15)throw std::invalid_argument("Infantry recalculation needs resident type/House children for this kind");};
            occupants.store=observers.passabilityStore;
            updateOccupiedCellPassability(cell.passability,cell.input,permitted,overlay,inputs.wheelSpeeds,occupants);
            return cell.passability;
        };
        const int slot=mapAttributeBufferIndex(c.input.position,map_.width,map_.height,int(map_.buffer4.size()/4));
        recalculateResidentCell(c,level,std::span<std::uint8_t,4>{map_.buffer4.data()+slot*4,4},std::span<std::uint8_t,10>{map_.buffer10.data()+slot*10,10},inputs,services);
    }
    InfantryOccupationCell occupation(WalkMovementCellView view){
        auto& c=walkMap_.attributes(view);auto& extra=cells_[std::size_t(cellIds_.at(&c.input))];
        return {extra.ground,extra.elevated,c.input.flags,extra.groundHouse,extra.elevatedHouse};
    }
    // Explicit Walk E8/EC children. Mark/map/Cell membership must not call these:
    // the original Cell parents bypass occupation entirely for Infantry kind15.
    void occupy(int id,const Coord& p){auto s=subcellServices();occupyInfantrySubcell(p,actors_.at(id).houseIndex.get(),threshold_,s,occupationStore);}
    void release(const Coord& p){auto s=subcellServices();releaseInfantrySubcell(p,threshold_,s,occupationStore);}
    bool mark(int id,int mode,const UnitMarkStore& store={}){
        const auto& a=actors_.at(id);UnitMarkServices s;
        s.imageValue=[&a]{return a.imageValue;};s.owner=[&a]{return a.owner;};
        s.coordinates=[&a]{return terrainCellPoint(a.ground.position);};s.layer=[](){return 2;};
        s.redrawMap=redrawMap;s.specialEvent=[this,id](int e){if(!specialEvent)throw std::invalid_argument("Unbound Infantry special event");specialEvent(id,e);};
        s.insert=[this,id](TerrainCellPoint p){world_.mapInsert(id,p);};s.remove=[this,id](TerrainCellPoint p){world_.mapRemove(id,p);};
        return markFoot(a.mark,mode,s,store);
    }
private:
    void rebindHouseIndex(int id,const int& index){actors_.at(id).houseIndex=std::cref(index);}
    InfantrySubcellServices subcellServices(){
        InfantrySubcellServices s;s.squareRoot=squareRoot_;
        s.cell=[this](const Coord& p){return occupation(walkMap_.coordinate(p));};
        s.floor=[this](const Coord& p){return walkMap_.floor(p);};return s;
    }
};
}
