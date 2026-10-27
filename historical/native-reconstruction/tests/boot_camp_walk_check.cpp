// SPDX-License-Identifier: GPL-3.0-or-later
#include "platform/BootCampWalkWorld.hpp"
#include "platform/BootCampMessages.hpp"
#include "message_presentation_inspection.hpp"
#include "assets/PreparedData.hpp"
#include "assets/MessageColorData.hpp"
#include "render/Renderer.hpp"
#include "render/AlphaAnimationLifecycle.hpp"
#include "render/ObjectAlphaPlacement.hpp"
#include "render/MessageFrame.hpp"
#include "render/GiSpriteDirection.hpp"
#include "render/PreparedRadarAssets.hpp"
#include "render/RadarStorage.hpp"
#include "render/RadarRefresh.hpp"
#include "platform/BootCampRadarActors.hpp"
#include "render/RadarTerrain.hpp"
#include "sim/BuildingDiscovery.hpp"
#include "sim/ScenarioWaypoint.hpp"
#include "sim/MissionScriptState.hpp"
#include "sim/MissionTag.hpp"
#include <type_traits>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
namespace ra2 {
// Observe existing backing/value state without invoking a map/floor service.
// Byte snapshots below detect source mutation only; they are not portable
// serialization, original layouts, or clone-value comparisons across addresses.
struct BootCampWalkWorldInspection {
    static void teamFootExpirationCheck(BootCampWalkWorld& source){
        if(!source.missionWorld_->objectiveTeamIdentity())throw std::runtime_error("Team expiration needs the actual constructed Team");
        const auto sourceFields=source.footExpirations_;
        const auto originalState=source.missionWorld_->state();
        const auto prepare=[&]{
            auto w=source.clone();
            std::vector<int> members;for(auto& [id,a]:w->actors_)if(a.team4c4)members.push_back(id);
            for(int id:members)if(!w->removeFromObjectiveTeam(id))throw std::runtime_error("Expiration fixture must unlink actual members first");
            const auto team=w->missionWorld_->objectiveTeamIdentity();const void* other=&w->actors_.begin()->second;
            for(auto& [id,r]:w->footExpirations_){
                r.headFC=team;r.link108=team;r.link20C=team;r.link23C=team;r.link27C=team;r.link384=team;r.link3F8=team;
                r.links260.fill(team);r.links260[3]=other;
                r.counts={5,5,4};
                r.backing[0]={other,team,other,team,nullptr,other,team,other};
                r.backing[1]={team,other,team,nullptr,other,other,nullptr,team};
                r.backing[2]={team,other,team,nullptr,other,other,nullptr,team};
                r.backing[3]={team,other,team,nullptr,team,other,team,other};
                r.backing[4]={team,other,team,nullptr,team,other,team,other};
                if(w->actors_.contains(id)){auto& a=w->actors_.at(id);a.teamTarget22c=team;a.teamLink498=team;a.field1b0=team;
                    a.radioCountD0=3;a.radioLinksCC={team,other,team};a.resumeCount4ac=5;a.resumePending488=5;
                }else{auto& a=w->passiveFeet_.at(id);a.target22C=team;a.link498=team;a.field1B0=team;
                    a.radioCountD0=3;a.radioCC={team,other,team};a.count4AC=5;a.count488=5;
                    if(a.kind==1)r.derived5AC=team;
                }
            }
            // Noncanonical registry order is retained through cloning, separately
            // from the Foot228 cleanup registry and source map definition order.
            std::reverse(w->teamFootBacking_.begin(),w->teamFootBacking_.end());
            return w;
        };
        for(auto removed:{0u,256u,1u,257u}){
            auto seed=prepare();auto w=seed->clone();seed.reset();
            if(w->teamFootCount_!=8||w->teamFootRecipients_.size()!=8||w->passiveTags_.size()!=3)
                throw std::runtime_error("Team broadcast must retain eight Foot recipients and three authored passive Tags");
            for(std::size_t i=0;i<w->teamFootBacking_.size();++i)
                if(w->teamFootBacking_[i]->identity!=w->footRegistry_.at(7-i))throw std::runtime_error("Team registry clone lost order/actual actor identities");
            std::map<int,MissionTagState*> tags;std::map<int,int> tagCounts;
            for(auto& [id,a]:w->actors_){tags[id]=a.objectTag34;if(a.objectTag34)tagCounts[id]=a.objectTag34->instances;}
            int infantry=0,units=0;for(auto& [id,a]:w->passiveFeet_){tags[id]=a.tag34;tagCounts[id]=a.tag34->instances;
                if(a.kind==15)++infantry;else if(a.kind==1)++units;
                if(!a.tag34||a.tag34==w->missionWorld_->objectiveTeamTag()||!a.mission.hasTag)
                    throw std::runtime_error("Passive actors require their distinct real authored map Tags");
            }
            if(infantry!=1||units!=2)throw std::runtime_error("Cow is Infantry; CMIN/SHAD are both Unit-class recipients");
            for(auto& [id,a]:w->actors_)a.effect25c=w->missionWorld_->objectiveTeamIdentity();
            for(auto& [id,a]:w->passiveFeet_)a.effect25C=w->missionWorld_->objectiveTeamIdentity();
            auto& gi=w->actors_.begin()->second;gi.target494=w->missionWorld_->objectiveTeamIdentity();gi.field490=73;gi.state5ac=29;
            auto& passive=w->passiveFeet_.begin()->second;passive.target494=w->missionWorld_->objectiveTeamIdentity();passive.numeric490=-7;
            const auto state=w->missionWorld_->state();w->composeObjectiveTeamExpiration(removed);
            for(const auto& [id,r]:w->footExpirations_){
                const bool low=std::uint8_t(removed)!=0;
                if(r.link108||r.link20C||r.link23C||r.link27C||r.link384||r.headFC!=(low?nullptr:w->missionWorld_->objectiveTeamIdentity())||
                   r.link3F8!=(low?nullptr:w->missionWorld_->objectiveTeamIdentity())||r.counts!=std::array<std::int32_t,3>{4,4,3})
                    throw std::runtime_error("Actual Foot inherited reference/vector fields are not shared");
                for(int i=0;i<7;++i)if(r.links260[i]!=(i==3?static_cast<const void*>(&w->actors_.begin()->second):nullptr))
                    throw std::runtime_error("Split weapon fields must clear actual owners without mirroring");
                if(r.backing[3][0]!=&w->actors_.begin()->second||r.backing[3][1]!=nullptr||r.backing[3][4]!=w->missionWorld_->objectiveTeamIdentity())
                    throw std::runtime_error("Foot vectors must retain unused original tails");
                auto* tag=tags.at(id);if(tag&&tag->instances!=tagCounts.at(id))throw std::runtime_error("Team expiration must preserve real Tag counts");
                if(w->actors_.contains(id)){const auto& a=w->actors_.at(id);
                    if(a.effect25c||a.field1b0||a.teamTarget22c||a.teamLink498||a.resumeCount4ac!=2||a.resumePending488!=2||a.radioCountD0!=3||a.objectTag34!=tag||
                        a.radioLinksCC[0]!=(low?nullptr:w->missionWorld_->objectiveTeamIdentity())||a.radioLinksCC[2]!=(low?nullptr:w->missionWorld_->objectiveTeamIdentity()))
                        throw std::runtime_error("GI expiration must borrow existing mission/Foot/radio owners");
                }else{const auto& a=w->passiveFeet_.at(id);
                    if(a.effect25C||a.field1B0||a.target22C||a.link498||a.count4AC!=2||a.count488!=2||a.radioCountD0!=3||a.tag34!=tag||r.derived5AC)
                        throw std::runtime_error("Passive expiration must use actual Unit/Infantry fields and retain Tags");
                    const auto type=&w->passiveTypes_.at(lower(w->mission_.actors.at(std::size_t(id)).type));
                    if((a.kind==15?r.passiveType5A8:r.derivedType)!=type)throw std::runtime_error("Passive Type identity must survive clone/expiration");
                }
            }
            if(gi.target494||gi.field490||gi.state5ac!=29||passive.target494||passive.numeric490||
                w->missionWorld_->state().teamMemberCount!=state.teamMemberCount||!w->missionWorld_->state().teamConstructed)
                throw std::runtime_error("Broadcast clears borrowed numeric490/494 but does not pretend to destroy Team");
            // Low-byte-zero retains FC/3F8/radio; a second real removal must
            // clear them with the same persistent backing/count owners.
            if(!std::uint8_t(removed)){w->composeObjectiveTeamExpiration(1);for(const auto& [id,r]:w->footExpirations_)if(r.headFC||r.link3F8)throw std::runtime_error("Repeated actual expiration lost retained fields");}
        }
        auto guarded=prepare();const auto id=guarded->actors_.begin()->first;
        guarded->actors_.at(id).byte170=1;bool refused=false;
        try{guarded->composeObjectiveTeamExpiration();}catch(const std::invalid_argument&){refused=true;}
        if(!refused||guarded->footExpirations_.at(id).link23C||!guarded->footExpirations_.at(id).link27C)
            throw std::runtime_error("Entered unbound CC must refuse after earlier stores and before later clears");
        int foreign=0;guarded->footExpirations_.at(id).link108=&foreign;refused=false;
        try{(void)guarded->clone();}catch(const std::invalid_argument&){refused=true;}
        if(!refused)throw std::runtime_error("Foreign Foot expiration clone pointer must refuse");
        auto split=prepare();const int first=split->teamFootRecipients_.rbegin()->first;
        const auto beforeSplit=split->footExpirations_.at(first);split->teamFootRecipients_.at(first).identity=&foreign;refused=false;
        try{split->composeObjectiveTeamExpiration();}catch(const std::invalid_argument&){refused=true;}
        if(!refused||split->footExpirations_.at(first)!=beforeSplit)throw std::runtime_error("Split recipient identity must refuse before its actor stores");
        if(source.footExpirations_!=sourceFields||source.missionWorld_->state().teamMemberCount!=originalState.teamMemberCount||
            source.missionWorld_->state().teamScriptCursor!=originalState.teamScriptCursor)
            throw std::runtime_error("Discarded Team expiration diagnostics changed source owners");
        std::cout<<"Actual Team expiration: eight Foot owners, authored passive Tags, CMIN/SHAD Unit dispatch, reverse-registry clone/lifetime, low-byte/radio/vector/numeric fields and refusal ordering PASS (explicit unscheduled broadcast; teardown remains guarded)\n";
    }
    static int requestActualViewportCell(BootCampWalkWorld& w,int actor,const CellRedrawView& view){
        auto& membership=w.walking_->membership();
        const int id=membership.cellId(membership.walkMap().coordinate(w.actor(actor).ground.position));
        auto& visibility=*w.visibilityWorld_;auto& cell=visibility.cells_.at(std::size_t(id));
        cell.flags12c|=8u;cell.redraw138=1;
        visibility.withCellRedraw(w.tickOwner(),view,[&]{visibility.redrawCell(id);});
        if(cell.redrawFrame5c!=w.tick())throw std::runtime_error("Actual viewport redraw must stamp actual Cell even when clipped");
        return id;
    }
    static void markRedrawBindingCheck(BootCampWalkWorld& w,int id){
        auto& member=w.walking_->membership();auto& actor=w.actors_.at(id);
        auto& queue=w.visibilityWorld_->redrawQueue_;
        const auto prior=w.missionWorld_->state();const auto count=queue.countE0;
        const auto bound=member.redrawMap;int requests=0;
        member.redrawMap=[&]{
            if(actor.redraw75!=1)throw std::runtime_error("Mark must store actual actor redraw before Tactical request");
            ++requests;bound();
        };
        queue.dirtyD7D=0;actor.redraw75=0;member.mark(id,0);member.mark(id,1);
        if(requests!=1||queue.dirtyD7D!=1||queue.countE0!=count)
            throw std::runtime_error("Mark must dirty shared Tactical without inventing Cell queue entries");
        queue.dirtyD7D=0;actor.redraw75=0x81;member.mark(id,0);member.mark(id,1);
        if(requests!=1||queue.dirtyD7D||actor.redraw75!=0x81)
            throw std::runtime_error("Nonzero raw redraw byte must suppress map request");
        actor.redraw75=0;member.mark(id,0);member.mark(id,1);
        if(requests!=2||queue.dirtyD7D!=1)throw std::runtime_error("Cleared actor redraw must issue another shared request");
        member.redrawMap=bound;
        auto warm=w.clone();queue.dirtyD7D=0;warm->visibilityWorld_->redrawQueue_.dirtyD7D=0;
        warm->actors_.at(id).redraw75=0;warm->walking_->mark(id,0);warm->walking_->mark(id,1);
        if(queue.dirtyD7D||warm->visibilityWorld_->redrawQueue_.dirtyD7D!=1)
            throw std::runtime_error("Warm Mark redraw binding leaked into source Tactical");
        auto survivor=warm->clone();warm.reset();survivor->visibilityWorld_->redrawQueue_.dirtyD7D=0;
        survivor->actors_.at(id).redraw75=0;survivor->walking_->mark(id,0);survivor->walking_->mark(id,1);
        if(survivor->visibilityWorld_->redrawQueue_.dirtyD7D!=1)
            throw std::runtime_error("Mark redraw lost Tactical after source destruction");
        if(w.missionWorld_->state().textRequests!=prior.textRequests||w.missionWorld_->state().triggerDestroyed!=prior.triggerDestroyed)
            throw std::runtime_error("Map redraw must not manufacture Objective1");
        actor.walk.moving34=1;actor.walk.head={};actor.reset5cc=1;bool refused=false;
        try{w.walking_->order(id,nullptr);}catch(const std::invalid_argument& e){refused=std::string(e.what()).find("animation4DC effect unjoined")!=std::string::npos;}
        if(!refused||actor.reset5cc)throw std::runtime_error("Entered unsupported animation must refuse after original reset store");
    }
    static void dirtyBindingCheck(BootCampWalkWorld& w,int actor){
        auto& membership=w.walking_->membership();
        const int cell=membership.cellId(membership.walkMap().coordinate(w.actor(actor).ground.position));
        const auto check=[&](int id){
            auto& attributes=membership.attributes(id);auto& resident=w.cells_.at(std::size_t(id));
            const auto saved=attributes;const auto savedResident=resident;
            attributes.overlay=-1;attributes.overlayData=48;attributes.input.slope=0;attributes.input.flags=0;resident.head=actor;
            if(w.dirtyCell(id)!=CellDirtyEffectExit::Overlay)throw std::runtime_error("Dirty binding lost actual overlay");
            attributes.overlay=126;attributes.overlayData=47;
            if(w.dirtyCell(id)!=CellDirtyEffectExit::OverlayData)throw std::runtime_error("Dirty binding lost actual overlay data");
            attributes.overlayData=48;attributes.input.slope=1;
            if(w.dirtyCell(id)!=CellDirtyEffectExit::Slope)throw std::runtime_error("Dirty binding lost actual slope");
            attributes.input.slope=0;attributes.input.flags=0x20000;
            if(w.dirtyCell(id)!=CellDirtyEffectExit::Flags)throw std::runtime_error("Dirty binding lost actual flags");
            attributes.input.flags=0;resident.head=-1;
            if(w.dirtyCell(id)!=CellDirtyEffectExit::Empty)throw std::runtime_error("Dirty binding lost actual primary resident");
            resident.head=actor;bool refused=false;
            try{w.walking_->dirty(id);}catch(const std::invalid_argument&){refused=true;}
            if(!refused)throw std::runtime_error("Production dirty callback silently accepted unrecovered resident effect");
            attributes=saved;resident=savedResident;
        };
        check(cell);check(int(w.map_->cells.size())); // Shared fallback has its own actual resident record.
        auto warm=w.clone();
        auto& source=membership.attributes(cell);const auto saved=source;
        source.overlay=126;source.overlayData=48;source.input.slope=0;source.input.flags=0;
        warm->walking_->dirty(cell); // Must not consult the now-refusing source Cell.
        source=saved;
        auto survivor=warm->clone();warm.reset();survivor->walking_->dirty(cell);
    }
    static void observeCrossingDirty(BootCampWalkWorld& w,int actor,int& calls){
        const auto bound=w.walking_->dirty;
        w.walking_->dirty=[&w,actor,&calls,bound](int cell){
            auto& membership=w.walking_->membership();
            const auto position=w.actor(actor).ground.position;
            const int expected=membership.cellId(membership.walkMap().coordinate(position));
            if(cell!=expected||w.residentHead({std::int16_t(position.x/256),std::int16_t(position.y/256)})!=actor)
                throw std::runtime_error("Crossing dirty must use current actual Cell after insertion");
            bound(cell);++calls;
        };
    }
    static void saltRecalculationBuffers(BootCampWalkWorld& w,MapInputPosition p){
        auto& m=*w.map_;const int slot=mapAttributeBufferIndex(p,m.width,m.height,int(m.buffer4.size()/4));
        m.buffer4[slot*4]=0xfe;m.buffer4[slot*4+1]=0xfe;m.buffer10[slot*10+8]=0xfe;
    }
    static void membershipDiscoveryCheck(BootCampWalkWorld& w,int id){
        auto& member=w.walking_->membership();auto& services=member.world().services;
        auto& actor=w.actors_.at(id);auto& discovered=actor.object.mission;
        const auto prior=w.missionWorld_->state();const int house=w.missionWorld_->currentHouse();
        if(!services.liveVisibilityGate||!services.liveNotificationArgument||services.liveVisibilityGate()!=w.missionWorld_->discoveryMode()||services.liveNotificationArgument()!=house)
            throw std::runtime_error("Membership must borrow actual mission mode/House");
        services.visibilityGate=-1;services.notificationArgument=-777; // Poison unused diagnostic snapshots.
        const auto notify=services.notify;int calls=0;
        services.notify=[&](int actor,int argument){if(actor!=id||argument!=house)throw std::runtime_error("Membership notification lost actual actor/House");++calls;notify(actor,argument);};
        const auto setVisible=[&](bool value){
            for(std::size_t i=0;i<w.map_->cells.size();++i){auto& c=w.visibilityWorld_->cells_.at(i);c.flags12c=(c.flags12c&~8u)|(value?0:8);auto& flags=w.map_->cells[i].attributes.input.flags;flags=(flags&~2u)|(value?0:2);}
            w.visibilityWorld_->fallback_.flags12c=(w.visibilityWorld_->fallback_.flags12c&~8u)|(value?0:8);
            w.map_->fallback.input.flags=(w.map_->fallback.input.flags&~2u)|(value?0:2);
        };
        discovered.current373=0;setVisible(false);member.mark(id,0);member.mark(id,1);
        auto& owner=w.missionWorld_->house(discovered.owner);
        if(calls!=1||!discovered.current373||!owner.field5668||!owner.field5669||!owner.discovered13c)
            throw std::runtime_error("Actual membership must discover the actual GI and House");
        member.mark(id,0);member.mark(id,1);
        if(calls!=2||!discovered.current373)throw std::runtime_error("Repeated original notify must keep discovery idempotent");
        discovered.current373=0;setVisible(true);member.mark(id,0);member.mark(id,1);
        if(calls!=2||discovered.current373)throw std::runtime_error("Actual session zero and visible Cell must bypass notification despite poisoned snapshots");
        services.notify=notify;
        if(w.missionWorld_->state().textRequests!=prior.textRequests||w.missionWorld_->state().triggerDestroyed!=prior.triggerDestroyed)
            throw std::runtime_error("Null-Tag Infantry discovery must not manufacture Objective1");
    }
    static auto& radarPrepared(BootCampWalkWorld& w){return *w.prepared_;}
    static auto& radarCell(BootCampWalkWorld& w,std::size_t id){return w.map_->cells.at(id).attributes;}
    static auto& threatType(BootCampWalkWorld& w){return w.threat598_;}
    static auto& positionMutable(BootCampWalkWorld& w,int id){return w.positions_.at(id);}
    static auto movementHouse(const BootCampWalkWorld& w,int id){return w.walking_->admission_.gates.houses.at(id);}
    static bool movementAllied(BootCampWalkWorld& w,int house,int actor){return movement_gate_policy::movementGateAllied(house,actor,w.walking_->admission_.gates);}
    static void checkWalkHouseAliases(const BootCampWalkWorld& w){
        for(const auto& [id,b]:w.walking_->actors_){const auto& h=w.missionWorld_->house(b.unit.object.mission.owner);
            if(&b.houseIndex.get()!=&h.indexAlliance.countryIndex||&b.human134.get()!=&h.human134||&b.human135.get()!=&h.control135||
               &b.countrySpeed.get()!=&w.houseInputs_.at(b.unit.object.mission.owner).speed||
               &w.walking_->membership_.actor(id).houseIndex.get()!=&h.indexAlliance.countryIndex)
                throw std::runtime_error("Walk binding split its actual House fields");
        }
    }
    static auto& sightRegistry(BootCampWalkWorld& w){return w.sightRegistry_;}
    static auto& sightTypeADD(BootCampWalkWorld& w){return w.sightTypeADD_;}
    static auto& walkType(BootCampWalkWorld& w){return w.type_;}
    static auto& visibilityCells(BootCampWalkWorld& w){return w.visibilityWorld_->cells_;}
    static auto& visibilityFallback(BootCampWalkWorld& w){return w.visibilityWorld_->fallback_;}
    static auto& actorSight(BootCampWalkWorld& w,int id){return w.sight_.at(id);}
    static auto& actorMutable(BootCampWalkWorld& w,int id){return w.actors_.at(id);}
    static auto& sightHouse(BootCampWalkWorld& w,int id){return w.missionWorld_->house(id).indexAlliance;}
    static auto& allyReveal(BootCampWalkWorld& w){return w.visibilityWorld_->allyReveal_;}
    static std::uint8_t& waypointDisabled(BootCampWalkWorld& w){return w.visibilityWorld_->waypointHouses_.at(w.visibilityWorld_->state_.currentHouse).disabled188;}
    static auto& scenario(BootCampWalkWorld& w){return w.visibilityWorld_->scenario_;}
    static auto& radius(BootCampWalkWorld& w){return w.visibilityWorld_->waypointRules_.range54c;}
    static auto& heightScale(BootCampWalkWorld& w){return w.visibilityWorld_->waypointHeightScale_;}

    static void infantryAccountingBindingCheck(BootCampWalkWorld& source){
        auto warm=source.clone();int gi=-1;
        for(const auto& [id,a]:warm->actors_)if(!warm->player(id)){gi=id;break;}
        if(gi<0)throw std::runtime_error("Accounting needs an actual Other GI");
        auto survivor=warm->clone();warm.reset();auto& actor=survivor->actors_.at(gi);
        const int old=actor.object.mission.owner,player=survivor->missionWorld_->currentHouse();const int index=survivor->type_.accountingIndex;
        auto& oldHouse=survivor->missionWorld_->house(old);auto& nextHouse=survivor->missionWorld_->house(player);
        auto& oc=oldHouse.infantryAccounting;auto& nc=nextHouse.infantryAccounting;
        const auto oldTotal=oc.count234,newTotal=nc.count234,oldActive=oc.active5440.at(index),oldRegistered=oc.registered5480.at(index),nextActive=nc.active5440.at(index),nextRegistered=nc.registered5480.at(index),history=nc.historyA70.at(index);
        int mapRequests=0;HouseInfantryActor a{&actor,actor.accounting324,actor.accounting5c1,
            [&]{return HouseInfantryType{survivor->type_.accounting202,[&]{return survivor->type_.accountingIndex;}};},[&]{return std::uint32_t(actor.object.kind);}};
        withHouseInfantryAccounting(oc,&oldHouse,[&](auto& h){
            removeRegisteredHouseInfantry(h,a,[&]{++mapRequests;});removeActiveHouseInfantry(h,a);
        });
        if(actor.accounting324||oc.count234!=oldTotal-1u||oc.active5440.at(index)!=oldActive-1u||oc.registered5480.at(index)!=oldRegistered-1u||mapRequests!=1)
            throw std::runtime_error("Actual old House accounting order/effects failed");
        withHouseInfantryAccounting(nc,&nextHouse,[&](auto& h){addActiveHouseInfantry(h,a);addRegisteredHouseInfantry(h,a);});
        if(actor.accounting324!=1||nc.count234!=newTotal+1u||nc.active5440.at(index)!=nextActive+1u||nc.registered5480.at(index)!=nextRegistered+1u||nc.historyA70.at(index)!=history+1u)
            throw std::runtime_error("Actual new House accounting effects failed");
        if(actor.object.mission.owner!=old||survivor->missionWorld_->state().createTeamRequests)
            throw std::runtime_error("Accounting must not pretend to transfer ownership or complete Objective1");
        auto later=survivor->clone();survivor.reset();auto& copied=later->missionWorld_->house(player).infantryAccounting;
        if(copied.count234!=newTotal+1u||copied.active5440.at(index)!=nextActive+1u)throw std::runtime_error("Warm House counter clone lost values");
        withHouseInfantryAccounting(copied,&later->missionWorld_->house(player),[&](auto& h){changeHouseInfantryCounter(h.active5440,index,true);});
        if(source.missionWorld_->house(old).infantryAccounting.count234!=oldTotal||source.missionWorld_->house(player).infantryAccounting.count234!=newTotal)
            throw std::runtime_error("House accounting mutated source owners");
        std::cout<<"Actual GI/House Infantry accounting: remove/add, independent clones, source destruction PASS (map child and startup supplied; no ownership transfer)\n";
    }
    static void houseTransferBoundaryCheck(BootCampWalkWorld& source){
        const std::array<std::int32_t,18> tables{}; // Authored alias stencil: native ownership fixture only.
        auto warm=source.clone();int gi=-1;
        for(const auto& [id,a]:warm->actors_)if(!warm->player(id)){gi=id;break;}
        if(gi<0)throw std::runtime_error("Transfer needs actual Other GI");
        auto survivor=warm->clone();warm.reset();auto& a=survivor->actors_.at(gi);
        if(survivor->missionControl_[12].bytes[5]||survivor->missionControl_[12].bytes[7]||
           missionControlIndex(survivor->missionControl_[12])!=12||
           survivor->missionControl_[12].bytes!=source.missionControl_[12].bytes)
            throw std::runtime_error("Actual Return mission-control startup/clone differs");
        auto separate=survivor->clone();separate->missionControl_[12].bytes[5]=255;
        if(survivor->missionControl_[12].bytes[5]||source.missionControl_[12].bytes[5])
            throw std::runtime_error("Mission-control clone shares mutable storage");
        separate.reset();
        const int old=a.object.mission.owner,next=survivor->missionWorld_->currentHouse(),index=survivor->type_.accountingIndex;
        auto& accounting=survivor->missionWorld_->house(old).infantryAccounting;
        const auto registered=accounting.registered5480.at(index),active=accounting.active5440.at(index),total=accounting.count234;
        auto& nextHouse=survivor->missionWorld_->house(next);auto& nextCounts=nextHouse.infantryAccounting;
        const auto nextRegistered=nextCounts.registered5480.at(index),nextActive=nextCounts.active5440.at(index),nextTotal=nextCounts.count234,nextHistory=nextCounts.historyA70.at(index);
        const auto oldIndex=survivor->missionWorld_->house(old).indexAlliance.countryIndex;
        const auto nextCountry=survivor->missionWorld_->countryType(next).countryB8;
        if(nextCountry==next||survivor->missionWorld_->house(next).countryType34==source.missionWorld_->house(next).countryType34)
            throw std::runtime_error("Country Type registration/clone identity confused with House index");
        nextHouse.transferValue5418=0xfffffff0u;nextHouse.transfersFrom5310.at(oldIndex)=0xffffffffu;
        survivor->missionWorld_->house(old).lastCountry53B8=-7;
        const auto originalTeamRequests=survivor->missionWorld_->state().createTeamRequests;
        RadarStorage radar({11,3,0,3,5,2});radar.supplyNotificationMode(2,1);
        {RefreshRect rect{0,0,80,60};const std::int32_t zero=0;radar.initialize(rect,zero,zero,[](auto&,auto&,auto bytes){std::fill(bytes.begin(),bytes.end(),0);},[]{});}
        const auto oldStat=survivor->missionWorld_->house(old).notification5360,sourceStat=source.missionWorld_->house(old).notification5360;
        const auto base=survivor->type_.baseCost550;
        if(base!=200||survivor->infantryCost(&survivor->type_,nullptr)!=200u||
           survivor->infantryCost(&survivor->type_,&survivor->missionWorld_->house(old))!=200u)
            throw std::runtime_error("Actual E1 cost startup differs");
        // Diagnostic mutation on the same persistent owner, not a replacement
        // callback: exercise float32 product/truncation and current-House reads.
        survivor->missionWorld_->countryType(old).costInfantry114=.33333334f;
        survivor->missionWorld_->countryType(next).costInfantry114=2.f;
        if(survivor->infantryCost(&survivor->type_,&survivor->missionWorld_->house(old))!=66u||
           survivor->infantryCost(&survivor->type_,&survivor->missionWorld_->house(next))!=400u)
            throw std::runtime_error("Cost did not borrow distinct actual House fields");
        const auto before=snapshot(*survivor);
        if(survivor->attemptHouseTransferOwned(gi,old,radar,tables)||snapshot(*survivor)!=before)throw std::runtime_error("Same-House transfer must do nothing");
        if(survivor->footCount_!=8||survivor->footRegistry_.size()!=8||survivor->passiveFeet_.size()!=3)
            throw std::runtime_error("Reference cleanup must own all eight actual Foot records");
        const auto teamRefs=[](BootCampWalkWorld& w){
            TechnoReferenceCleanupServices s{w.footCount_,w.missionWorld_->referenceCleanupTeamCount()};
            w.missionWorld_->bindReferenceCleanupTeams(s);return s.teamSlot(0);
        };
        const bool hasTeam=survivor->missionWorld_->referenceCleanupTeamCount()!=0;
        auto* const actualTag=a.objectTag34;
        const auto tagInstances=actualTag?actualTag->instances:0;
        const auto occurred=actualTag?actualTag->first->state.occurred:0;
        if(hasTeam){
            auto t=teamRefs(*survivor);t.target3C=&a;t.target40=&a;
            a.object.mission.current373=0; // Force the actual supported discovery branch on the same owner.
            survivor->missionWorld_->house(old).discovered13c=128;
            survivor->missionWorld_->house(old).field5668=129;
            survivor->missionWorld_->house(old).field5669=130;
        }
        // Diagnostic inputs on the same canonical Houses/grids. The alias stencil
        // subtracts598 nine times at the actual coordinate-projected Cell.
        a.threat400=598;
        for(const auto& [key,h]:survivor->missionWorld_->houses()){
            survivor->missionWorld_->house(key).indexAlliance.allianceMask=0;
            survivor->missionWorld_->houseThreat(key).grid.fill(1000);
        }
        MapFloorHeightWorld threatMap{survivor->map_->table,&survivor->map_->fallback.input,{}};
        const auto& threatCell=mapCoordinateCell(a.ground.position,threatMap,int(survivor->map_->table.size()));
        const auto threatSlot=projectHouseThreatCell({threatCell.position.x,threatCell.position.y});
        a.route[0]=3;a.targetFlag404=255;a.targetFlag57e=128;
        // Seed the same buckets consumed by drawing with two actual identities.
        // Removal followed by new-local insertion must move this GI to the front;
        // a duplicate-only insert would leave the order unchanged.
        int peer=-1;for(const auto& [key,item]:survivor->actors_)if(key!=gi){peer=key;break;}
        if(peer<0)throw std::runtime_error("Transfer radar needs another actual actor");
        a.radarX1a0=2;a.radarY1a4=2;
        auto& peerActor=survivor->actors_.at(peer);peerActor.radarX1a0=2;peerActor.radarY1a4=2;
        BootCampRadarActors::updateMarker(*survivor,radar,&peerActor,RadarActorMarkerOperation::insert);
        BootCampRadarActors::updateMarker(*survivor,radar,&a,RadarActorMarkerOperation::insert);
        const auto bucketIndex=radarMarkerBucket(2,2);
        const auto& bucket=(*radar.markerBucketsOwner())[bucketIndex];
        if(bucket.count!=2||bucket.entries[0].actor!=&peerActor||bucket.entries[1].actor!=&a)
            throw std::runtime_error("Transfer radar initial ordering differs");
        const auto dirtyBefore=radar.dirtyPoints().size();
        bool completed=false;std::string transferBoundary;
        const auto referenceCount=a.references,globalReferences=survivor->globals_.references;
        a.percentage468=.625;
        if(a.object.mission.mission98==12){
            auto gated=survivor->clone();gated->missionControl_[12].bytes[5]=255;
            // A72F40 threshold is distinct from the map floor's850C40 height.
            // Zero makes this grounded marked actor skip the wrapper454 store.
            gated->globals_.levelHeight=0;
            gated->positions_.at(gi).footprintX454=-1234;gated->positions_.at(gi).footprintY456=2345;
            RadarStorage gatedRadar({11,3,0,3,5,2});gatedRadar.supplyNotificationMode(2,1);
            {RefreshRect rect{0,0,80,60};const std::int32_t zero=0;gatedRadar.initialize(rect,zero,zero,[](auto&,auto&,auto bytes){std::fill(bytes.begin(),bytes.end(),0);},[]{});}
            std::string boundary;
            bool success=false;try{success=gated->attemptHouseTransferOwned(gi,next,gatedRadar,tables);}
            catch(const std::invalid_argument& e){boundary=e.what();}
            if(!success||!boundary.empty()||
               survivor->missionControl_[12].bytes[5]||source.missionControl_[12].bytes[5]||
               gated->positions_.at(gi).footprintX454!=-1234||gated->positions_.at(gi).footprintY456!=2345||
               survivor->globals_.levelHeight!=104||gated->map_->levelHeight!=survivor->map_->levelHeight)
                throw std::runtime_error("Resume did not consume the actual independent mission-control table: "+boundary);
            BootCampRadarActors::updateMarker(*gated,gatedRadar,&gated->actors_.at(gi),RadarActorMarkerOperation::remove);
        }
        if(a.object.mission.mission98==12)for(int mode:{1,2}){
            auto changed=survivor->clone();auto& changedActor=changed->actors_.at(gi);
            const auto hadRealTeam=bool(changedActor.team4c4);
            changedActor.veterancy118=mode==1?1.5:0.;
            changed->type_.guardAreaVeteran27c=mode==1?255:0;
            changed->type_.defaultGuardAreaB00=mode==2?255:0;
            RadarStorage changedRadar({11,3,0,3,5,2});changedRadar.supplyNotificationMode(2,1);
            {RefreshRect rect{0,0,80,60};const std::int32_t zero=0;changedRadar.initialize(rect,zero,zero,[](auto&,auto&,auto bytes){std::fill(bytes.begin(),bytes.end(),0);},[]{});}
            std::string boundary;
            bool success=false;try{success=changed->attemptHouseTransferOwned(gi,next,changedRadar,tables);}
            catch(const std::invalid_argument& e){boundary=e.what();}
            if(!success||!boundary.empty()||
               changedActor.object.mission.queuedA0!=(hadRealTeam?5:11)||changedActor.object.mission.queuedA4!=0||
               bool(changedActor.team4c4)!=hadRealTeam||a.veterancy118!=0||
               survivor->type_.guardAreaVeteran27c||survivor->type_.defaultGuardAreaB00)
                throw std::runtime_error("Resume ability/default-area did not borrow actual fields and real Team: "+boundary);
            BootCampRadarActors::updateMarker(*changed,changedRadar,&changedActor,RadarActorMarkerOperation::remove);
        }
        if(a.object.mission.mission98!=5&&a.object.mission.mission98!=12)
            throw std::runtime_error("Transfer fixture entered an unverified startup mission");
        try{completed=survivor->attemptHouseTransferOwned(gi,next,radar,tables);}catch(const std::invalid_argument& e){transferBoundary=e.what();}
        if(a.object.mission.mission98==12&&(a.object.mission.queuedA0!=5||a.object.mission.queuedA4!=0))
            throw std::runtime_error("Actual resume did not queue Guard through the real mission owner");
        if(a.resume59d!=1||source.actors_.at(gi).resume59d!=0)
            throw std::runtime_error("Foot resume59D store lost actual GI or source isolation");
        if(a.percentage468!=0||a.references!=referenceCount||survivor->globals_.references!=globalReferences)
            throw std::runtime_error("Foot resume lost actual percentage or retained Walk reference lifetime");
        if(!completed||!transferBoundary.empty()||survivor->missionWorld_->house(old).notification5360!=oldStat+1u||radar.dirtyFlag()!=1||radar.notificationView().full14D6!=0||a.route[0]!=-1||a.targetFlag404||a.targetFlag57e||a.target494||
           accounting.registered5480.at(index)!=registered-1u||accounting.active5440.at(index)!=active-1u||accounting.count234!=total-1u||
           a.object.mission.owner!=next||a.object.mission.field372!=1||a.accounting324!=1||a.threat400!=std::uint32_t(survivor->threat598_)||!a.ground.marked74||
           nextCounts.active5440.at(index)!=nextActive+1u||nextCounts.count234!=nextTotal+1u||nextCounts.historyA70.at(index)!=nextHistory+1u||
           nextHouse.transferValue5418!=50u||nextHouse.transfersFrom5310.at(oldIndex)!=0||survivor->missionWorld_->house(old).lastCountry53B8!=nextCountry||
           survivor->missionWorld_->house(next).infantryAccounting.registered5480.at(index)!=nextRegistered+1u||survivor->missionWorld_->state().createTeamRequests!=originalTeamRequests)
            throw std::runtime_error("Actual transfer prefix lost order, boundary, source House or refusal scope: "+transferBoundary+" marked="+std::to_string(a.ground.marked74)+" owner="+std::to_string(a.object.mission.owner));
        for(const auto& [key,h]:survivor->missionWorld_->houses()){
            const auto& grid=survivor->missionWorld_->houseThreat(key).grid;
            for(int slot=0;slot<int(grid.size());++slot){
                const int expected=slot!=threatSlot?1000:
                    (h.indexAlliance.countryIndex==oldIndex?1000:0)+(h.indexAlliance.countryIndex==nextHouse.indexAlliance.countryIndex?0:9*survivor->threat598_);
                if(grid[slot]!=expected)throw std::runtime_error("Transfer did not update actual shared House grid");
            }
        }
        const auto actualCell=terrainCellPoint(a.ground.position);
        if(survivor->positions_.at(gi).footprintX454!=actualCell.x||survivor->positions_.at(gi).footprintY456!=actualCell.y)
            throw std::runtime_error("Completed transfer wrapper did not update actual footprint454/456");
        if(a.radarRegistered37b!=1||bucket.count!=2||bucket.entries[0].actor!=&a||
           bucket.entries[1].actor!=&peerActor||radar.dirtyPoints().size()!=dirtyBefore)
            throw std::runtime_error("Transfer did not remove then prepend the actual newly local radar identity, retaining the deduplicated dirty point");
        BootCampRadarActors::updateMarker(*survivor,radar,&a,RadarActorMarkerOperation::remove);
        BootCampRadarActors::updateMarker(*survivor,radar,&peerActor,RadarActorMarkerOperation::remove);
        for(const auto& b:*radar.markerBucketsOwner())if(b.count)
            throw std::runtime_error("Transfer radar retained active identities before clone destruction");
        checkWalkHouseAliases(*survivor);
        if(!survivor->player(gi)||source.player(gi))throw std::runtime_error("Selection retained definition House instead of current owner");
        const auto occurrences=[&](BootCampWalkWorld& w){
            auto& world=w.walking_->membership().world();int count=0;
            for(const auto& cell:w.cells_)for(int head:{cell.head,cell.alternateHead}){
                std::size_t visits=0;
                for(int p=head;p!=-1;p=world.actors.at(p).next){
                    if(++visits>world.actors.size())throw std::runtime_error("Cyclic actual Cell list");
                    if(p==gi)++count;
                }
            }return count;
        };
        if(occurrences(*survivor)!=1)throw std::runtime_error("Transfer Mark3 did not reinsert GI exactly once");
        if(hasTeam){
            auto t=teamRefs(*survivor);if(t.target3C||t.target40)throw std::runtime_error("Reference cleanup did not clear actual Team targets");
            const auto& house=survivor->missionWorld_->house(old);
            if(a.objectTag34!=actualTag||!a.object.mission.hasTag||!a.object.mission.current373||
               house.discovered13c!=1||house.field5668!=1||house.field5669!=1||actualTag->executing||
               actualTag->instances!=tagInstances||actualTag->first->state.occurred!=occurred||actualTag->first->state.destroyed)
                throw std::runtime_error("Actual tagged discovery lost GI/House stores or fired/retired event7");
            const auto beforeRepeat=snapshot(*survivor);
            if(survivor->missionWorld_->discoverInfantry(gi,a.object.mission,a.objectTag34,next)||snapshot(*survivor)!=beforeRepeat)
                throw std::runtime_error("Actual repeated tagged discovery must reject without mutation");
            a.objectTag34=source.missionWorld_->objectiveTeamTag();bool foreignTagRefused=false;
            try{survivor->missionWorld_->discoverInfantry(gi,a.object.mission,a.objectTag34,next);}catch(const std::invalid_argument&){foreignTagRefused=true;}
            a.objectTag34=actualTag;if(!foreignTagRefused||snapshot(*survivor)!=beforeRepeat)throw std::runtime_error("Foreign GI Tag must refuse without mutation");
            a.object.mission.hasTag=false;bool incoherentRefused=false;
            try{survivor->missionWorld_->discoverInfantry(gi,a.object.mission,a.objectTag34,next);}catch(const std::invalid_argument&){incoherentRefused=true;}
            a.object.mission.hasTag=true;if(!incoherentRefused||snapshot(*survivor)!=beforeRepeat)throw std::runtime_error("Incoherent GI Tag must refuse without mutation");
        }
        // Clone/rebind real references before exercising the explicitly guarded
        // matching-Foot child. Passive map actors must participate as well.
        auto references=source.clone();
        for(auto& [id,p]:references->passiveFeet_)p.target228=&references->actors_.at(gi);
        references->positions_.begin()->second.alternate228=&references->actors_.at(gi);
        if(hasTeam){auto t=teamRefs(*references);t.target3C=&references->actors_.at(gi);t.target40=&references->passiveFeet_.begin()->second;}
        auto copied=references->clone();references.reset();
        for(auto& [id,p]:copied->passiveFeet_)if(p.target228!=&copied->actors_.at(gi))throw std::runtime_error("Passive Foot clone lost target identity");
        if(copied->positions_.begin()->second.alternate228!=&copied->actors_.at(gi))throw std::runtime_error("GI reference clone lost identity");
        if(hasTeam){auto t=teamRefs(*copied);if(t.target3C!=&copied->actors_.at(gi)||t.target40!=&copied->passiveFeet_.begin()->second)throw std::runtime_error("Team clone lost actual target identity");}
        for(auto& [id,p]:copied->passiveFeet_)p.target228=nullptr;
        copied->positions_.begin()->second.alternate228=nullptr;
        for(const auto foot:copied->footRegistry_){
            const void** field=nullptr;
            for(auto& [id,a]:copied->actors_)if(foot==&a)field=&copied->positions_.at(id).alternate228;
            for(auto& [id,a]:copied->passiveFeet_)if(foot==&a)field=&a.target228;
            if(!field)throw std::runtime_error("Missing actual Foot field");
            *field=&copied->actors_.at(gi);bool guarded=false;
            try{copied->clearReferencesOwned(&copied->actors_.at(gi));}catch(const std::invalid_argument& e){guarded=std::string(e.what())=="Reference cleanup matching Foot1E0 effects remain unjoined";}
            if(!guarded||*field!=&copied->actors_.at(gi))throw std::runtime_error("Matching Foot child must refuse without clearing");
            *field=nullptr;
        }
        copied->passiveFeet_.begin()->second.target228=&source;bool foreignRefused=false;
        try{copied->clone();}catch(const std::invalid_argument&){foreignRefused=true;}
        if(!foreignRefused)throw std::runtime_error("Foreign passive Foot reference must refuse clone");
        copied->passiveFeet_.begin()->second.target228=nullptr;
        if(hasTeam){auto t=teamRefs(*copied);t.target40=&source;foreignRefused=false;try{copied->clone();}catch(const std::invalid_argument&){foreignRefused=true;}if(!foreignRefused)throw std::runtime_error("Foreign Team target must refuse clone");}
        auto later=survivor->clone();survivor.reset();
        if(!later->actors_.at(gi).ground.marked74||occurrences(*later)!=1)throw std::runtime_error("Completed diagnostic transfer lost Mark3 after clone/source destruction");
        if(later->missionWorld_->house(next).transferValue5418!=50u||later->missionWorld_->house(old).lastCountry53B8!=nextCountry||later->missionWorld_->house(next).infantryAccounting.count234!=nextTotal+1u||later->infantryCost(&later->type_,&later->missionWorld_->house(old))!=66u||later->infantryCost(&later->type_,&later->missionWorld_->house(next))!=400u||later->missionWorld_->house(old).notification5360!=oldStat+1u||later->missionWorld_->house(old).infantryAccounting.registered5480.at(index)!=registered-1u||later->actors_.at(gi).object.mission.owner!=next)
            throw std::runtime_error("Completed diagnostic transfer clone lost state after source destruction");
        checkWalkHouseAliases(*later);
        if(!later->player(gi))throw std::runtime_error("Warm transferred GI lost player association");
        // The same transferred GI becomes selectable and orders use its new
        // House. Use a diagnostic committed head for Process: no route/Team
        // admission or unrecovered sight continuation is bypassed/claimed.
        auto fast=later->clone(),slow=later->clone();
        const Coord motionStart=later->actors_.at(gi).ground.position;
        const auto advance=[&](BootCampWalkWorld& w,float speed){
            w.houseInputs_.at(old).speed=3.f;w.houseInputs_.at(next).speed=speed;
            auto& member=w.actors_.at(gi);member.walk.head={motionStart.x+64,motionStart.y,motionStart.z};
            member.walk.destination=member.walk.head;member.walk.moving34=member.walk.reallyMoving36=1;
            const auto untouched=w.actors_.at(source.actors_.begin()->first).ground.position;
            checkWalkHouseAliases(w);w.walking_->process(gi);
            if(member.ground.position==motionStart)throw std::runtime_error("Transferred GI Process did not move");
            if(source.actors_.begin()->first!=gi&&w.actors_.at(source.actors_.begin()->first).ground.position!=untouched)
                throw std::runtime_error("Transferred GI Process moved independent actor");
            return std::abs(member.ground.position.x-motionStart.x)+std::abs(member.ground.position.y-motionStart.y);
        };
        const int fastDistance=advance(*fast,1.f),slowDistance=advance(*slow,.5f);
        if(slowDistance<=0||slowDistance>=fastDistance||later->actors_.at(gi).ground.position!=motionStart)
            throw std::runtime_error("Transferred Walk retained startup speed or mutated source");
        auto& membership=later->walking_->membership();membership.occupy(gi,motionStart);
        const auto claim=membership.occupation(membership.walkMap().coordinate(motionStart));
        if(claim.groundHouse54!=later->missionWorld_->house(next).indexAlliance.countryIndex)
            throw std::runtime_error("Transferred GI occupation retained old House index");
        // A subsequent call after source destruction must traverse clone-owned
        // registry slots and grids, with no synchronization or transient mirror.
        std::int16_t tx=0,ty=0;
        later->missionWorld_->changeCellThreat({tx,ty},oldIndex,1,tables);
        for(const auto& [key,h]:later->missionWorld_->houses()){
            if(later->missionWorld_->houseThreat(key).grid[131]!=(h.indexAlliance.countryIndex==oldIndex?1000:1009))
                throw std::runtime_error("Warm Cell threat registry retained source Houses");
            if(source.missionWorld_->houseThreat(key).grid[131])throw std::runtime_error("Cell threat mutated source grid");
        }
        auto* ownedCountry=later->missionWorld_->house(old).countryType34;
        later->missionWorld_->house(old).countryType34=source.missionWorld_->house(old).countryType34;
        bool countryRefused=false,costRefused=false;
        try{later->clone();}catch(const std::invalid_argument&){countryRefused=true;}
        try{later->infantryCost(&later->type_,&later->missionWorld_->house(old));}catch(const std::invalid_argument&){costRefused=true;}
        later->missionWorld_->house(old).countryType34=ownedCountry;
        if(!countryRefused||!costRefused)throw std::runtime_error("Foreign country Type must refuse cloning/cost");
        later->actors_.at(gi).walk.piggyback38=&source;bool piggybackRefused=false;
        try{later->clone();}catch(const std::invalid_argument& e){piggybackRefused=std::string(e.what())=="Boot Camp Walk retained locomotor clone remains unjoined";}
        later->actors_.at(gi).walk.piggyback38=nullptr;
        if(!piggybackRefused)throw std::runtime_error("Unowned Walk retained locomotor must refuse cloning");
        later->actors_.at(gi).controller408=&source;bool controllerRefused=false;
        try{later->clone();}catch(const std::invalid_argument&){controllerRefused=true;}
        if(!controllerRefused)throw std::runtime_error("Unowned transfer controller must refuse cloning");
        if(source.missionWorld_->house(next).transferValue5418||source.missionWorld_->house(next).transfersFrom5310.at(oldIndex)||source.missionWorld_->house(old).lastCountry53B8!=-1||source.missionWorld_->house(old).infantryAccounting.count234!=total||source.missionWorld_->house(next).infantryAccounting.count234!=nextTotal||source.missionWorld_->countryType(old).costInfantry114!=1.f||source.missionWorld_->countryType(next).costInfantry114!=1.f||source.missionWorld_->house(old).notification5360!=sourceStat||source.missionWorld_->house(old).infantryAccounting.registered5480.at(index)!=registered||source.missionWorld_->house(next).infantryAccounting.registered5480.at(index)!=nextRegistered)
            throw std::runtime_error("Discarded transfer diagnostic mutated source Houses");
        std::cout<<"Actual GI transfer prefix: notification/cost/ledger/active accounting/reference cleanup/complete Mark3/tagged discovery/map/Cell threat /new owner/new threat/registration/radio/actual Walk query/percentage/late Release/empty refill/mission-control/ability16/actual queued mission/radar removal/new-local prepend/ground query/footprint454 -> complete bounded wrapper, clone/source isolation PASS (unscheduled; country/sidebar/startup supplied)\n";
    }
    static std::string snapshot(const BootCampWalkWorld& w){
        std::string result;
        const auto value=[&]<class T>(const T& v){
            static_assert(std::is_trivially_copyable_v<T>);
            result.append(reinterpret_cast<const char*>(&v),sizeof(v));
        };
        value(w.visibilityWorld_->redrawQueue_);
        value(w.type_);value(w.speeds_);value(w.subcells_);value(w.foundation_);value(w.globals_);value(w.random_);
        value(w.residentSearch_);value(w.positionScratch_);value(w.positionTypeFootprint_);value(w.positionTypeSpecial_);
        value(w.sightType534_);value(w.sightTypeADD_);value(w.sightCount_);
        value(w.sightRegistry_.data());value(w.sightRegistry_.capacity());for(auto p:w.sightRegistry_)value(p);
        value(w.sightSlots_.data());value(w.sightSlots_.size());
        value(w.threat598_);value(w.veteranSight_);value(w.eliteSight_);value(w.sightRange_);value(w.sightHeightDivisor_);value(w.veteranSightMultiplier_);
        for(const auto& [id,a]:w.actors_){value(id);value(&a);value(a);}
        for(const auto& [id,a]:w.houseInputs_){value(id);value(&a);value(a);}
        for(const auto& [id,a]:w.sight_){value(id);value(&a);value(a);}
        for(const auto& [id,a]:w.positions_){value(id);value(&a);value(a);}
        value(w.cells_.data());value(w.cells_.capacity());for(const auto& c:w.cells_)value(c);
        value(w.registry_.data());value(w.registry_.capacity());for(const auto& r:w.registry_)value(r);
        for(const auto& p:w.blocked_){value(p.first);value(p.second);}
        for(const auto& [id,index]:w.definitions_){value(id);value(index);}
        const auto& m=*w.map_;value(&m);value(m.floor);value(m.fallback);
        const auto& r=m.resident;value(r.lat);value(r.directions);value(r.permission);value(r.tubeCount);value(r.cliffMode);value(r.fallback);
        const auto span=[&](const auto& v){value(v.data());value(v.size());for(const auto& x:v)value(x);};
        span(r.tiles);span(r.landMap);span(r.overlays);span(r.resources);span(r.wheelSpeeds);
        value(m.cells.data());value(m.cells.capacity());for(const auto& c:m.cells)value(c);
        value(m.attributes.data());for(auto p:m.attributes)value(p);
        value(m.table.data());for(auto p:m.table)value(p);
        value(m.slots.data());for(auto p:m.slots)value(p);
        value(m.buffer4.data());value(m.buffer4.capacity());for(auto p:m.buffer4)value(p);
        value(m.buffer10.data());value(m.buffer10.capacity());for(auto p:m.buffer10)value(p);
        value(m.width);value(m.height);value(m.levelHeight);
        const auto v=w.visibilityWorld_->state();
        value(v.residentCount);value(v.reveals);value(v.revealAreas);value(v.sightAdds);value(v.sightRemovals);value(v.postSightCalls);
        value(v.waypointReveals);value(v.waypointAreaCalls);
        const auto& visibility=*w.visibilityWorld_;
        value(visibility.revealByHeight_);value(visibility.allyReveal_);
        const auto visibilityCell=[&](const CellVisibilityState& c){
            value(c.point);value(c.primary120);value(c.secondary121);value(c.flags12c);
            value(c.counter130);value(c.maximum134);value(c.count13c);value(c.redraw138);
            value(c.redrawFrame5c);value(c.flags140);value(c.identity);value(c.level11b);value(c.primaryResident);value(c.elevatedResident);
        };
        for(const auto& c:visibility.cells_)visibilityCell(c);visibilityCell(visibility.fallback_);
        for(const auto& [id,h]:w.missionWorld_->houses()){
            value(id);value(&h);value(h.human134);value(h.control135);value(h.discovered13c);value(h.field13d);value(h.field5668);value(h.field5669);
            value(h.buildingType1b4);value(h.building18d);value(h.building144);value(h.indexAlliance);value(h.radarColor55e9);value(h.radarScheme15f40);value(h.notification5360);value(h.countryType34);value(h.transferValue5418);value(h.transfersFrom5310);value(h.lastCountry53B8);
            if(h.countryType34){const auto& type=w.missionWorld_->countryType(id);value(type.indexB4);value(type.countryB8);value(type.costInfantry114);result.append(type.name);result.push_back('\0');}
            const auto& c=h.infantryAccounting;value(c.count234);value(c.activeCapacity);value(c.registeredCapacity);value(c.historyCount1270);value(c.historyA70);
            value(c.active5440.data());value(c.active5440.size());value(c.active5440.capacity());for(auto v:c.active5440)value(v);
            value(c.registered5480.data());value(c.registered5480.size());value(c.registered5480.capacity());for(auto v:c.registered5480)value(v);
        }
        for(const auto& [id,h]:w.missionWorld_->houses()){
            const auto& state=w.missionWorld_->houseThreat(id);
            value(&state);value(state.grid.data());result.append(reinterpret_cast<const char*>(state.grid.data()),sizeof(state.grid));
            value(state.enemy54F0);value(state.count5504);value(state.scores.data());value(state.scores.capacity());
            for(const auto& entry:state.scores){value(entry.house);value(entry.value);}
            value(state.slots.data());value(state.slots.size());
        }
        value(visibility.waypointRules_);value(visibility.waypointHeightScale_);
        value(visibility.scenario_.data());value(visibility.scenario_.capacity());for(auto byte:visibility.scenario_)value(byte);
        for(const auto& [id,defined]:visibility.suppliedWaypoints_){value(id);value(defined);}
        for(const auto& [id,h]:visibility.waypointHouses_){value(id);value(&h);value(h.disabled188);}
        value(v.maskCalls);value(v.mapQueries);value(v.fallbackStores);value(v.redraws);value(v.discoveryParents);value(v.cellNotifications);
        value(v.discoveredResidents);value(v.refreshes);value(v.lastCell);value(v.lastResident);value(v.currentHouse);value(v.fallbackPoint);
        for(int key:{1019675,1019676}){
            value(w.missionWorld().structureExpirationState(key));value(w.missionWorld().structureSightState(key));
            const auto a=w.missionWorld_->structureSight(key);const auto& t=w.missionWorld_->structureSightType(key);value(a.discovery);
            value(t.imageBounds);value(t.ordinaryDraw);value(t.frameSelection);value(t.indexB90);value(t.strengthA0);value(t.countC6C);
            value(t.flag1217);value(t.flag11FE);value(t.flag1206);value(t.sight530);value(t.threat598);
            value(t.veteranSight271);value(t.eliteSight283);value(t.flag534);value(t.flagADD);value(t.radarFootprintC78);
            value(t.radarAA6);value(t.radarAA7);value(t.radarVeteran277);value(t.radarElite289);value(t.radarFlag1ff);
            const auto& i=t.images;value(i.primaryA4);value(i.ownedA8);value(i.demand13e0);value(i.demand13e1);value(i.flag1351);
            value(i.count137c);value(i.startC8c);value(i.countC90);value(i.durationC94);
            value(i.primary13eb.size());result+=i.primary13eb;value(i.secondaryBf4.size());result+=i.secondaryBf4;
            value(t.imageBacking.size());for(const auto& image:t.imageBacking){
                value(image.get());value(image->width);value(image->height);value(image->frames.size());
                for(const auto& f:image->frames){value(f.x);value(f.y);value(f.width);value(f.height);value(f.format);span(f.pixels);}
            }
        }
        value(w.missionWorld_->discoveryMode());value(w.missionWorld_->currentHouse());
        return result+MessagePresentationInspection::snapshot(w.missionWorld().messages());
    }
};
}
using namespace ra2;
namespace {
void require(bool v,const char* message){if(!v)throw std::runtime_error(message);}
// Inspect consumer-owned state without map/floor queries. Refused controls must
// not move, clear queues/targets/references, advance time or warm floor state.
std::string snapshot(const BootCampWalkWorld& world){
    std::ostringstream out;out.precision(17);out<<world.tick()<<' ';
    const auto point=[&](Coord p){out<<p.x<<' '<<p.y<<' '<<p.z<<' ';};
    for(const auto& [id,a]:world.actors()){
        out<<id<<' ';point(a.ground.position);point(a.walk.destination);point(a.walk.head);
        out<<unsigned(a.walk.moving34)<<' '<<unsigned(a.walk.reallyMoving36)<<' '<<a.target494<<' '<<a.references<<' '
           <<a.body.desired<<' '<<a.body.start<<' '<<a.body.timerStart<<' '<<a.body.duration<<' '
           <<a.object.next<<' '<<unsigned(a.object.flags14)<<' '<<a.counter53c<<' '<<a.state5ac<<' '<<a.percentage468<<' ';
        for(int x:a.route)out<<x<<' ';for(int x:a.retry530)out<<x<<' ';for(int x:a.wait558)out<<x<<' ';
    }
    out<<world.positionScratch()<<' ';
    for(const auto& [id,a]:world.actors()){
        const auto& p=world.positionState(id);
        out<<unsigned(a.flag32d)<<' '<<unsigned(a.flag32c)<<' '<<a.team4c4<<' '
            <<a.threat400<<' '<<a.controller408<<' '<<unsigned(a.accounting324)<<' '<<unsigned(a.accounting5c1)<<' '<<a.field1b0<<' '<<a.valueD8<<' '<<a.transport588<<' '<<a.teamNext4c8<<' '<<a.objectTag34<<' '<<a.teamGroup1ac<<' '<<unsigned(a.teamLeader579)<<' '
            <<unsigned(a.recruitable37a)<<' '<<unsigned(a.targetFlag404)<<' '<<unsigned(a.targetFlag57e)<<' '
            <<p.alternate228<<' '<<p.effect208<<' '<<p.target34<<' '<<p.mode1b8<<' '<<p.animation418<<' '
            <<p.footprintX454<<' '<<p.footprintY456<<' '<<unsigned(p.flag77)<<' '<<unsigned(a.object.mission.current373)<<' '
            <<unsigned(p.state59a)<<' '<<unsigned(p.state59c)<<' ';
    }
    const auto& map=world.map();const auto& f=map.floor;
    out<<unsigned(f.flags)<<' '<<f.height<<' '<<f.scale<<' '<<map.fallback.input.position.x<<' '<<map.fallback.input.position.y<<' ';
    for(const auto& p:f.planes)out<<p.x<<' '<<p.y<<' '<<p.offset<<' '<<p.limit<<' '<<p.add<<' ';
    const auto visibility=[&](const CellVisibilityState& c){
        out<<c.point.x<<' '<<c.point.y<<' '<<unsigned(c.primary120)<<' '<<unsigned(c.secondary121)<<' '
           <<c.flags12c<<' '<<c.flags140<<' '<<c.counter130<<' '<<c.maximum134<<' '<<unsigned(c.redraw138)<<' '
           <<c.identity<<' '<<int(c.level11b)<<' '<<c.primaryResident<<' '<<c.elevatedResident<<' ';
    };
    for(const auto& cell:map.cells){const auto& p=cell.attributes.input.position;
        out<<cell.attributes.input.flags<<' ';visibility(world.visibilityWorld().at({p.x,p.y}));
        out<<world.residentHead({p.x,p.y})<<' '<<world.residentHead({p.x,p.y},true)<<' ';}
    out<<map.fallback.input.flags<<' ';visibility(world.visibilityWorld().fallback());
    for(const auto& [id,h]:world.missionWorld().houses())out<<id<<' '<<unsigned(h.human134)<<' '<<unsigned(h.control135)<<' '
        <<unsigned(h.discovered13c)<<' '<<unsigned(h.field13d)<<' '<<unsigned(h.field5668)<<' '<<unsigned(h.field5669)<<' '<<h.buildingType1b4<<' '<<unsigned(h.building18d)<<' '<<unsigned(h.building144)<<' ';
    for(int key:{1019675,1019676}){const auto& a=world.missionWorld().structureResidentState(key);
        point(a.position88);out<<a.next<<' '<<a.width<<' '<<a.height<<' '<<unsigned(a.flags14)<<' '
            <<unsigned(a.alternate79)<<' '<<unsigned(a.eligible5a0)<<' '<<unsigned(a.typeMapFlag205)<<' ';
    }
    return out.str()+BootCampWalkWorldInspection::snapshot(world);
}
// Standalone mission tests deliberately supply a recording leaf; production
// Walk binds the actual cloned visibility owner instead. Never copy callbacks.
void bindInspectionReveal(BootCampMissionWorld& world){world.bindWaypointReveal([](std::int32_t n){if(n!=6)throw std::invalid_argument("Inspection waypoint");return std::uint8_t(1);});}
// Compare every public mission value; timer records deliberately remain plain
// recovered structs without ownership-adapter operators in the simulation core.
bool sameMissionState(const BootCampMissionWorld::State& a,const BootCampMissionWorld::State& b){
    if(std::tie(
           a.tagInstances,a.deferred,a.triggerDestroyed,a.tagFreed,a.triggerFreed,
           a.taggedStructures,a.registryCounts,a.controlledEnabled,a.controlledPadding,a.textRequests,
           a.textKey,a.textPayload,a.textColorSelector,a.textColor,a.textStyle,a.textDuration,
           a.allyCalls,a.allyValue,a.allyFrom,a.allyTo,a.allyAnnounce,
           a.soundRequests,a.speechRequests,a.soundToken,a.speechToken,a.soundIndex,
           a.soundPanning,a.speechIndex,a.speechMode,a.speechParameter,a.soundVolumeBits,
           a.soundController,a.createTeamRequests,a.createTeamId,a.createTeamArgument,a.teamCreationDepth,
           a.createTeamDepthAtCall,a.createTeamFactoryCalls,a.createTeamAllocations,a.teamMemberCount,a.teamThreat,a.teamTaskCounts,a.teamTagInstances,a.teamConstructed,a.teamTypeCount,a.teamTagChildRequests,a.teamScriptChildRequests,a.teamRegistryCounts,a.teamTagConstructed,a.teamTriggerConstructed,a.teamScriptConstructed,a.teamTagTriggerBound,a.teamTriggerEnabled,a.teamScriptCount,a.teamScriptCursor,a.teamFlags,a.teamScriptActionCount,a.teamTriggerControlBound,a.triggerControlCount,a.revealRequests,a.revealCreateTeamRequestsAtCall,a.revealSoundRequestsAtCall,a.revealWaypoint,
           a.revealHouse,a.revealObject,a.revealTrigger,a.revealPackedCell)!=
       std::tie(
           b.tagInstances,b.deferred,b.triggerDestroyed,b.tagFreed,b.triggerFreed,
           b.taggedStructures,b.registryCounts,b.controlledEnabled,b.controlledPadding,b.textRequests,
           b.textKey,b.textPayload,b.textColorSelector,b.textColor,b.textStyle,b.textDuration,
           b.allyCalls,b.allyValue,b.allyFrom,b.allyTo,b.allyAnnounce,
           b.soundRequests,b.speechRequests,b.soundToken,b.speechToken,b.soundIndex,
           b.soundPanning,b.speechIndex,b.speechMode,b.speechParameter,b.soundVolumeBits,
           b.soundController,b.createTeamRequests,b.createTeamId,b.createTeamArgument,b.teamCreationDepth,
           b.createTeamDepthAtCall,b.createTeamFactoryCalls,b.createTeamAllocations,b.teamMemberCount,b.teamThreat,b.teamTaskCounts,b.teamTagInstances,b.teamConstructed,b.teamTypeCount,b.teamTagChildRequests,b.teamScriptChildRequests,b.teamRegistryCounts,b.teamTagConstructed,b.teamTriggerConstructed,b.teamScriptConstructed,b.teamTagTriggerBound,b.teamTriggerEnabled,b.teamScriptCount,b.teamScriptCursor,b.teamFlags,b.teamScriptActionCount,b.teamTriggerControlBound,b.triggerControlCount,b.revealRequests,b.revealCreateTeamRequestsAtCall,b.revealSoundRequestsAtCall,b.revealWaypoint,
           b.revealHouse,b.revealObject,b.revealTrigger,b.revealPackedCell))return false;
    for(std::size_t i=0;i<a.controlledTimers.size();++i)
        if(a.controlledTimers[i].start!=b.controlledTimers[i].start||a.controlledTimers[i].remaining!=b.controlledTimers[i].remaining)return false;
    return true;
}
void missionCloneCheck(const MissionDefinition& mission,const Ini& source,const Ini& rules,std::shared_ptr<const PreparedStringLookup> strings,const MessageColorTable& colors,const GameAssets& assets){
    int sourceFrame=17,cloneFrame=321;
    auto live=[&]{
        const Ini localSource=source,localRules=rules;
        return std::make_unique<BootCampMissionWorld>(mission,localSource,localRules,sourceFrame,strings,colors,makeBootCampMessages(assets));
    }(); // Cloning must not depend on constructor-only Ini argument lifetimes.
    bindInspectionReveal(*live);
    auto resident=live->structureResident(1019675);
    resident.position88={1234,5678,9};resident.next=1019676;resident.width=3;resident.height=2;
    const auto savedResident=live->structureResidentState(1019675);
    auto initial=live->clone(cloneFrame);bindInspectionReveal(*initial);
    require(sameMissionState(initial->state(),live->state()),"Initial mission clone must preserve every public value");
    require(initial->structureResidentState(1019675)==savedResident&&
            initial->structureResident(1019675).identity!=resident.identity,
            "Clone must preserve resident values with independent stable identities");
    for(const auto& [id,h]:live->houses())require(&h!=&initial->house(id),"Clone must own independent Houses");
    const auto liveBefore=live->state();const auto liveMessagesBefore=MessagePresentationInspection::snapshot(live->messages());
    require(initial->discoverStructure(1019675),"Initial clone must execute discovery on its own Tag/action graph");
    const auto queued=initial->state();
    require(initial->messages().list().head&&initial->messages().list().head->flags==0xc046u&&
            initial->messages().list().head->identifier==0&&!live->messages().list().head,
            "Objective callback must insert only into its owned clone list");
    require(initial->messages().config().fillPolicy==MessageFillPolicy::softwareDisplay,"Boot Camp must explicitly select verified software fill");
    std::vector<std::uint16_t> canvas(initial->messages().pixels().size(),0x1234);initial->messages().replacePixels(canvas);
    initial->messages().setMilliseconds(128);initial->messages().draw();
    require(!initial->messages().fills().empty()&&std::any_of(initial->messages().pixels().begin(),initial->messages().pixels().end(),[](auto v){return v!=0;}),
            "Actual objective payload must draw stock-font pixels in the cloned canvas");
    const auto background=initial->messages().fills().front().box;
    require(background.x>=0&&background.y>=0&&background.x<1024&&background.y<720&&
            initial->messages().pixels()[std::size_t(background.y)*1024+background.x]==0&&
            initial->messages().pixels().back()==0x1234,"Recovered objective background must fill the clone canvas and retain unrelated pixels");
    require(queued.textRequests==1&&queued.textPayload==strings->text("MISSION:Objective1")&&queued.textPayload!=queued.textKey&&queued.deferred==2&&queued.taggedStructures==0&&
            queued.controlledTimers[1].start==cloneFrame&&queued.controlledTimers[3].start==cloneFrame,
            "Cloned callbacks must use the clone's frame and mission owners");
    require(sameMissionState(live->state(),liveBefore)&&live->structureResidentState(1019675)==savedResident,
            "Clone discovery must not mutate source mission or residents");
    for(const auto& [id,h]:live->houses())require(!h.discovered13c&&h.buildingType1b4==-1,
            "Clone discovery must not write source Houses");
    require(MessagePresentationInspection::snapshot(live->messages())==liveMessagesBefore,"Cloned objective drawing changed live message owners");
    auto pending=initial->clone(sourceFrame);bindInspectionReveal(*pending);
    require(pending->messages().pixels().data()!=initial->messages().pixels().data()&&
            std::equal(pending->messages().pixels().begin(),pending->messages().pixels().end(),initial->messages().pixels().begin())&&
            pending->messages().list().head!=initial->messages().list().head&&pending->messages().asset()==initial->messages().asset(),
            "Warm mission clone needs independent message nodes/pixels and shared immutable glyphs");
    require(sameMissionState(pending->state(),queued),"Warm clone must retain queued cleanup/action/timer values");
    for(const auto& [id,h]:initial->houses()){
        const auto& other=pending->house(id);
        require(std::tie(h.human134,h.control135,h.discovered13c,h.field13d,h.field5668,h.field5669,h.buildingType1b4,h.building18d,h.building144)==
                std::tie(other.human134,other.control135,other.discovered13c,other.field13d,other.field5668,other.field5669,other.buildingType1b4,other.building18d,other.building144),
                "Warm clone must preserve all discovery House fields");
    }
    initial.reset(); // A stale callback, recipient or deferred pointer now fails under ASan.
    pending->messages().setMilliseconds(256);pending->messages().draw();
    pending->drainDeferred();
    const auto drained=pending->state();
    require(drained.deferred==0&&drained.triggerFreed&&drained.tagFreed&&
            drained.teamTriggerControlBound&&drained.triggerControlCount==5&&drained.registryCounts==std::array<std::int32_t,4>{5,7,6,1},
            "Warm clone cleanup must use remapped deferred/expiration/registry identities");
    require(sameMissionState(live->state(),liveBefore),"Clone cleanup must not drain the source");
    auto cleaned=pending->clone(cloneFrame);pending.reset();
    require(sameMissionState(cleaned->state(),drained),"After-cleanup clone must retain full warm state");
    cleaned->messages().setMilliseconds(100000);require(cleaned->messages().expire()&&!cleaned->messages().list().head,"Cloned objective lifetime must expire on its own explicit clock");
    cleaned->messages().draw();
    cleaned->drainDeferred();
    require(!cleaned->discoverStructure(1019675)&&sameMissionState(cleaned->state(),drained),
            "After-cleanup clone must preserve discovery and avoid duplicate actions");
    // Exercise the second Building and fresh callbacks after destroying source.
    auto survivor=live->clone(cloneFrame);bindInspectionReveal(*survivor);live.reset();
    require(survivor->discoverStructure(1019676),"Clone must survive destruction of source owners");
    survivor->messages().setMilliseconds(256);survivor->messages().draw();
    survivor->drainDeferred();
    require(survivor->state().tagFreed&&survivor->state().revealObject==1019676,
            "Second Building must retain the clone's active identity and cleanup recipients");
    survivor->structureResident(1019675).next=-1;
    require(cleaned->structureResidentState(1019675)==savedResident,"Resident clone mutation must remain isolated");
    std::cout<<"Warm mission clones: initial/queued/drained, independent frame/Houses/residents, source-destruction continuation PASS\n";
}
// Host ownership evidence only; the algorithms have separate original receipts.
void buildingOwnerCheck(const MissionDefinition& mission,const Ini& source,const Ini& rules,
        std::shared_ptr<const PreparedStringLookup> strings,const MessageColorTable& colors,const GameAssets& assets){
    int frame=17,cloneFrame=23;
    const auto make=[&]{auto out=std::make_unique<BootCampMissionWorld>(mission,source,rules,frame,strings,colors,makeBootCampMessages(assets));bindInspectionReveal(*out);return out;};
    auto missing=std::make_unique<BootCampMissionWorld>(mission,source,rules,frame,strings,colors,makeBootCampMessages(assets));
    int sourceCalls=0;missing->bindWaypointReveal([&](std::int32_t){++sourceCalls;return std::uint8_t(1);});
    auto unbound=missing->clone(cloneFrame);bool unboundRefused=false;
    try{unbound->discoverStructure(1019675);}catch(const std::invalid_argument& e){unboundRefused=std::string(e.what()).find("reveal owner is unbound")!=std::string::npos;}
    require(unboundRefused&&!sourceCalls&&missing->state().textRequests==0&&unbound->state().textRequests==1,
            "Mission clones must refuse missing reveal binding after prior actions, never copy source callbacks");
    auto live=make();auto a=live->inspectStructureExpiration(1019675),b=live->inspectStructureExpiration(1019676);
    a.fields.target228=a.tagIdentity;a.fields.pending9C=19;a.actor.queuedA4=7;
    a.fields.byte404=9;a.fields.word310=42;a.fields.link438=a.tagIdentity;
    // Object Next and passenger splice must update the actual resident word.
    live->structureResident(1019675).next=-2;a.expiredNext=nullptr;
    a.fields.headFC=b.identity;live->structureResident(1019676).next=-2;
    a.fields.counts={2,2,2,2,2};
    for(auto& slots:a.fields.backing){slots[0]=a.tagIdentity;slots[1]=b.identity;slots[7]=a.tagIdentity;}
    a.fields.links25C[7]=a.tagIdentity;a.fields.links4C0[2]=a.tagIdentity;
    // Inactive tails, House index0, and type pointers all require clone remapping.
    a.fields.backing[4][6]=&live->house(0);
    const auto saved=a.fields;const auto residentA=live->structureResidentState(1019675);
    auto fork=live->clone(cloneFrame);bindInspectionReveal(*fork);auto c=fork->inspectStructureExpiration(1019675),d=fork->inspectStructureExpiration(1019676);
    require(c.identity!=a.identity&&c.fields.type418!=a.fields.type418&&c.fields.backing[4][6]==&fork->house(0)&&
            c.fields.backing[0][7]==c.tagIdentity&&c.fields.headFC==d.identity&&c.expiredNext==nullptr,
            "Building clone must remap types, House0, Tag, head and inactive tails");
    require(fork->discoverStructure(1019676),"Typed production recipients must execute during discovery");
    require(c.fields.target228==nullptr&&c.fields.pending9C==-1&&c.actor.mission98==19&&c.actor.queuedA4==0&&
            c.fields.byte404==0&&c.fields.word310==0&&c.fields.link438==nullptr&&c.fields.links25C[7]==nullptr&&c.fields.links4C0[2]==nullptr,
            "Actual Building target/pending and inherited typed fields must clear");
    require(fork->structureResidentState(1019675).next==-1&&fork->structureResidentState(1019676).next==-1,
            "Object splice and middle passenger splice must store through shared logical Next");
    require(c.fields.counts==std::array<std::int32_t,5>{2,1,1,1,1}&&c.fields.backing[0][0]==nullptr&&
            c.fields.backing[0][1]==d.identity&&c.fields.backing[0][7]==c.tagIdentity&&
            c.fields.backing[4][0]==d.identity&&c.fields.backing[4][1]==d.identity&&c.fields.backing[4][7]==c.tagIdentity&&
            buildingHasRadioPointerLinks(c.fields.counts[0],std::span<const void* const>(c.fields.backing[0])),
            "Radio clearing and vector erases must share counts/backing and retain unused tails");
    require(a.fields==saved&&live->structureResidentState(1019675)==residentA&&a.actor.queuedA4==7,
            "Typed clone expiration must not mutate source records");
    live.reset();fork->drainDeferred();auto survivor=fork->clone(frame);fork.reset();survivor->drainDeferred();
    require(survivor->state().tagFreed,"Typed warm cleanup must survive source destruction");
    auto foreign=make();int alien=0;auto f=foreign->inspectStructureExpiration(1019675);f.fields.backing[3][7]=&alien;
    const auto bad=f.fields;bool refused=false;try{(void)foreign->clone(cloneFrame);}catch(const std::invalid_argument&){refused=true;}
    require(refused&&f.fields==bad,"Foreign inactive tail must refuse clone and preserve source");
    // These are partial-write refusals, not rollback or recovered child effects.
    for(int mode=0;mode<3;++mode){auto trial=make();auto t=trial->inspectStructureExpiration(1019675);
        t.fields.link438=t.tagIdentity;
        if(mode==0)t.fields.service208=t.identity;
        if(mode==1){t.fields.target228=t.tagIdentity;t.fields.timer150=11;}
        if(mode==2)t.fields.link474=t.tagIdentity;
        bool caught=false;try{trial->discoverStructure(1019675);}catch(const std::invalid_argument&){caught=true;}
        require(caught&&trial->state().taggedStructures==1,"Entered unbound effects must refuse after Object stores");
        if(mode==2)require(t.fields.link438==nullptr,"Animation refusal must retain earlier Building stores");
    }
    std::cout<<"Typed Building owners: target/pending/Next/radio/tails/warm clone/source destruction/refusals PASS\n";
}
void revealOwnerCheck(const GameAssets& assets,const MissionDefinition& mission,const Ini& source,const Ini& rules,const Ini& art){
    const auto make=[&]{return std::make_unique<BootCampWalkWorld>(assets,mission,source,rules,art);};
    {
        auto original=make();
        require(original->visibilityWorld().scenarioFlags()==0x8080u&&
                !source.boolean("SpecialFlags","FogOfWar",1),
                "Actual Day1 SpecialFlags must load map FogOfWar=no into scenario first dword");
        const auto unchanged=snapshot(*original);auto changed=original->clone();
        auto& bytes=BootCampWalkWorldInspection::scenario(*changed);bytes[1]|=0x10;
        require(changed->visibilityWorld().scenarioFlags()==0x9080u&&snapshot(*original)==unchanged,
                "Warm scenario first word must remain independent of source");
        auto survivor=changed->clone();changed.reset();
        const auto before=survivor->visibilityWorld().state().refreshes;
        require(survivor->visibilityWorld().reveal({57,89},survivor->visibilityWorld().currentHouse())&&
                survivor->visibilityWorld().state().refreshes==before+1,
                "Default actual Cell change must read cloned live scenario flags, not fixed zero");
        const auto explicitBefore=survivor->visibilityWorld().state().refreshes;
        (void)survivor->visibilityWorld().reveal({58,89},survivor->visibilityWorld().currentHouse(),0);
        require(survivor->visibilityWorld().state().refreshes==explicitBefore&&snapshot(*original)==unchanged,
                "Explicit diagnostic snapshot must stay separate and preserve source");
        original.reset();auto warm=survivor->clone();survivor.reset();
        const auto warmBefore=warm->visibilityWorld().state().refreshes;
        (void)warm->visibilityWorld().reveal({59,89},warm->visibilityWorld().currentHouse());
        require(warm->visibilityWorld().scenarioFlags()==0x9080u&&
                warm->visibilityWorld().state().refreshes==warmBefore+1,
                "Live scenario binding must survive source destruction and warm cloning");
        std::cout<<"Actual scenario flags: map FogOfWar, live default/explicit snapshot, warm clone/source destruction PASS (refresh child supplied)\n";
    }
    auto live=make();const auto before=snapshot(*live);
    BootCampWalkWorldInspection::infantryAccountingBindingCheck(*live);
    BootCampWalkWorldInspection::houseTransferBoundaryCheck(*live);
    require(snapshot(*live)==before,"Explicit House accounting must preserve source world");
    auto fork=live->clone();
    require(scenarioWaypoint(BootCampWalkWorldInspection::scenario(*fork),6)==TerrainCellPoint{71,95}&&
            BootCampWalkWorldInspection::radius(*fork)==9&&BootCampWalkWorldInspection::heightScale(*fork)==104&&
            BootCampWalkWorldInspection::scenario(*fork).data()!=BootCampWalkWorldInspection::scenario(*live).data(),
            "Waypoint startup must own packed scenario records, radius and separate supplied scale");
    require(fork->missionWorld().discoverStructure(1019675),"Production action17 must reach actual waypoint owner");
    const auto v=fork->visibilityWorld().state();const auto m=fork->missionWorld().state();
    require(v.waypointReveals==1&&v.waypointAreaCalls==2&&v.revealAreas==2&&v.reveals>0&&v.maskCalls==2*v.reveals&&
            !v.sightAdds&&!v.sightRemovals&&v.discoveredResidents>=2&&m.textRequests==1&&m.revealRequests==1&&
            m.revealObject==1019675&&m.revealHouse==6&&m.deferred==2&&m.tagInstances==0&&snapshot(*live)==before,
            "Actual two-pass reveal must nest resident discovery once, retain outer object, and isolate source");
    require((fork->visibilityWorld().at({71,95}).flags140&2u)&&!(live->visibilityWorld().at({71,95}).flags140&2u),
            "Production reveal must mutate actual Cell flags in the cloned map");
    // Diagnostic warm scenario/rule/scale changes must survive cloning; no
    // original startup or gameplay observation is implied by these inputs.
    auto& bytes=BootCampWalkWorldInspection::scenario(*fork);const std::uint32_t packed=57u|(89u<<16);
    for(unsigned i=0;i<4;++i)bytes[0x632+6*4+i]=std::uint8_t(packed>>(i*8));
    BootCampWalkWorldInspection::radius(*fork)=2;BootCampWalkWorldInspection::heightScale(*fork)=0;
    auto survivor=fork->clone();fork.reset();survivor->missionWorld().drainDeferred();
    require(survivor->visibilityWorld().revealWaypoint(6)==1&&survivor->visibilityWorld().state().waypointAreaCalls==4&&
            survivor->missionWorld().state().textRequests==1&&BootCampWalkWorldInspection::radius(*survivor)==2&&
            BootCampWalkWorldInspection::heightScale(*survivor)==0&&(survivor->visibilityWorld().at({57,89}).flags140&2u)&&snapshot(*live)==before,
            "Warm waypoint/mission bindings must survive source destruction without duplicate actions");
    // Disabled House admission must precede undefined waypoint and every map query.
    auto disabled=live->clone();BootCampWalkWorldInspection::waypointDisabled(*disabled)=255;
    const auto d0=disabled->visibilityWorld().state();require(disabled->visibilityWorld().revealWaypoint(-999)==1,"Disabled waypoint must bypass its getter");
    const auto d1=disabled->visibilityWorld().state();
    require(d1.waypointReveals==d0.waypointReveals+1&&d1.waypointAreaCalls==d0.waypointAreaCalls&&d1.mapQueries==d0.mapQueries&&
            d1.reveals==d0.reveals&&disabled->missionWorld().state().textRequests==0&&snapshot(*live)==before,
            "Disabled entry must not touch map/mission owners");
    auto disabledClone=disabled->clone();disabled.reset();
    require(disabledClone->visibilityWorld().revealWaypoint(-999)==1&&BootCampWalkWorldInspection::waypointDisabled(*live)==0,
            "Warm disabled byte must be cloned independently");
    auto undefined=live->clone();const auto u0=undefined->visibilityWorld().state();bool refused=false;
    try{(void)undefined->visibilityWorld().revealWaypoint(701);}catch(const std::invalid_argument&){refused=true;}
    require(refused&&undefined->visibilityWorld().state().mapQueries==u0.mapQueries&&snapshot(*live)==before,
            "Undefined scenario waypoint must refuse without map access or source mutation");
    std::cout<<"Production waypoint owners: two passes/shared map/nested discovery/warm clone/disabled/undefined/source destruction PASS\n";
}
void finish(BootCampWalkWorld& world,int id){
    int ticks=0;while(world.actor(id).walk.moving34&&ticks++<512)world.step();
    require(!world.actor(id).walk.moving34&&!world.actor(id).target494,"Walk must finish and clear target within bound");
}
template<class F>void refused(F action,const char* diagnostic){
    bool caught=false;try{action();}catch(const std::runtime_error& e){caught=std::string(e.what()).find(diagnostic)!=std::string::npos;}
    require(caught,"Expected specific terrain policy refusal");
}
}
int main(int argc,char** argv){try{
    if(argc<2||argc>4)throw std::invalid_argument("Supply owned data directory, optional threat tables (or -), and optional private radar dimensions");
    const bool privateThreat=argc>=3&&std::string(argv[2])!="-";
    RadarShapeDimensions radarWidths{},radarHeights{};
    if(argc==4){
        const auto dimensions=readFile(argv[3]);
        if(dimensions.size!=176||assetSha256(dimensions)!="a6d13a225bbbb52f1178acf67175788d24784bc167317fed350c45ac76d6422e")
            throw std::invalid_argument("Private radar dimension data differs");
        for(unsigned i=0;i<22;++i){radarWidths[i]=dimensions.i32(i*4);radarHeights[i]=dimensions.i32(88+i*4);}
    }
    std::array<std::int32_t,18> threatTables{}; // Authored zero-offset/shift ownership fixture by default.
    if(privateThreat){
        std::ifstream in(argv[2]);std::string sourceHash,extra;in>>sourceHash;
        if(sourceHash!=PatchedEngineSha)throw std::invalid_argument("Private threat table source differs");
        for(auto& v:threatTables)if(!(in>>v))throw std::invalid_argument("Missing private threat stencil");
        if(in>>extra)throw std::invalid_argument("Trailing private threat stencil data");
    }
    GameAssets assets(argv[1],"trn01t.map");prepareStaticScenery(assets);const auto mapText=assets.store.require(assets.mapName).text();
    const Ini source(mapText),rules(assets.store.require("rules.ini").text()),art(assets.store.require("art.ini").text());
    const auto data=readMapRuntimeData(readFile(preparedDataPath(assets.engineDataSource,"map-runtime-data.bin")));
    refused([&]{PreparedTerrainMap p(assets.store,source,data,104,416);},"attached Cell tags");
    refused([&]{PreparedTerrainMap p(assets.store,source,data,104,416,{.deferCellTags=true});},"resource overrides");
    const Ini unsupported(mapText+"\n[Riparius]\nSpread=2\n");
    refused([&]{PreparedTerrainMap p(assets.store,unsupported,data,104,416,{true,true});},"resource overrides");
    const Ini tube(mapText+"\n[Tubes]\n0=unrecovered\n");
    refused([&]{PreparedTerrainMap p(assets.store,tube,data,104,416,{true,true});},"Tubes");
    {
        PreparedTerrainMap p(assets.store,source,data,104,416,{true,true});
        require(p.cellTagsDeferred&&p.resourceTypes.size()==4,"Explicit deferred tags and resource records required");
        require(p.tileImages.size()==p.tiles.size()&&p.tileImages.size()==p.filenames.size(),"Canonical tile sources must share the prepared type indexes");
        unsigned residentImages=0;
        for(std::size_t i=0;i<p.tiles.size();++i){const auto& type=p.tileImages[i];
            require(type.filename==p.filenames[i],"Tile filename provenance changed");
            if(p.tiles[i].image){
                ++residentImages;require(type.image.has_value()&&type.prepared.has_value()&&p.tiles[i].image==&type.prepared->image,
                    "Resident Cell metadata must borrow its retained source type");
                const auto file=assets.store.require(type.filename);
                require(type.image->size==file.size&&std::equal(file.ptr(),file.ptr()+file.size,type.image->ptr()),"Retained TMP bytes differ from source installation");
            }else require(!type.image&&!type.prepared,"Unreferenced primary files must remain absent");
        }
        require(residentImages>1&&p.overlayInputs.size()==p.overlays.size(),"Stock map source ownership incomplete");
        require(p.overlayInputs.at(127).imageName=="TIB01"&&p.overlayInputs.at(127).theater&&p.overlayInputs.at(83).demandLoad&&p.overlayInputs.at(83).theater,
            "Theater fields must use the resolved art image name");
        require(!p.overlayImages.at(83)&&!p.overlayInputs.at(83).image,"Demand image must begin unbound");
        const auto bridgeImage=p.demandOverlayImage(assets.store,83,0);const auto bridgeFile=assets.store.require("LOBRDG10.TEM");
        require(bridgeImage.handle==84&&bridgeImage.data&&bridgeImage.data->storage==p.overlayImages.at(83)->storage&&p.overlayImageOwned.at(83)==1,
            "Actual bridge demand image must use its canonical overlay owner");
        require(bridgeImage.data->size==bridgeFile.size&&std::equal(bridgeFile.ptr(),bridgeFile.ptr()+bridgeFile.size,bridgeImage.data->ptr()),
            "Demand image differs from user-supplied bridge file");
        const auto again=p.demandOverlayImage(assets.store,83,2);require(again.data&&again.data->storage==bridgeImage.data->storage&&again.handle==bridgeImage.handle,
            "Resident image query must retain its cached identity even when supplied theater changes");
        require(!p.demandOverlayImage(assets.store,168,0).data&&!p.overlayImages.at(168),"Nonlazy startup remains unbound");
        p.initializeOverlayImage(assets.store,168,0);const auto rockFile=assets.store.require("SROCK01.TEM");
        require(p.overlayInputs.at(168).image==169&&p.overlayImages.at(168)&&p.overlayImageOwned.at(168)==0,
            "Explicit rock startup must use its canonical non-owned image record");
        const auto& rock=*p.overlayImages.at(168);
        require(rock.size==rockFile.size&&std::equal(rock.ptr(),rock.ptr()+rock.size,rockFile.ptr()),"Rock startup differs from supplied file");
        const int rockMaximum=std::max(8,std::max(int(std::bit_cast<std::int16_t>(rock.u16(2))),int(std::bit_cast<std::int16_t>(rock.u16(4)))));
        require(p.overlayInputs.at(168).imageMaximum==rockMaximum,"Rock startup must derive its signed header maximum");
        const auto rockAgain=p.demandOverlayImage(assets.store,168,2);
        require(rockAgain.data&&rockAgain.data->storage==rock.storage&&p.overlayImageOwned.at(168)==0,"Demand getter must borrow the startup image unchanged");
        p.initializeOverlayImage(assets.store,83,0);
        require(p.overlayInputs.at(83).image==84&&p.overlayImages.at(83)&&p.overlayImageOwned.at(83)==0&&
            p.overlayImages.at(83)->size==bridgeFile.size&&std::equal(bridgeFile.ptr(),bridgeFile.ptr()+bridgeFile.size,p.overlayImages.at(83)->ptr()),
            "Explicit startup must replace the owned demand image on the same bridge type");
        for(std::size_t i=0;i<p.overlays.size();++i)require(p.overlayInputs[i].index==int(i)&&p.overlayInputs[i].tiberium==p.overlays[i].tiberium,
            "Retained overlay registry must preserve actual type/index association");
        require(p.resourceTypes[0].value==50&&p.resourceTypes[1].value==100&&p.resourceTypes[2].value==50&&p.resourceTypes[3].value==50,
                "Day1 Value-only inputs must reach shared resource records");
        CellRadarColorServices radar;int missing=0;
        bindPreparedRadarAssets(radar,p,assets.store,0,[&](int){++missing;});
        // Supplied empty resident query/brightness/clearTile; asset callbacks
        // borrow the existing actual type, Data and resource records.
        radar.resident471760=[](auto,auto){return false;};radar.theaterScale=[] {return 1.0f;};const int clear=0;
        const auto actualCell=[&](int overlay)->const MapCellAttributes&{
            for(const auto& c:p.cells)if(c.attributes.overlay==overlay&&!(c.attributes.input.flags&0x100))return c.attributes;
            throw std::runtime_error("Day1 radar asset Cell missing");
        };
        require(p.resourceTypes.at(2).index==2&&p.resourceTypes.at(2).imageIndex==127&&
                radar.resource5DC0B0(127)==2&&radar.resource5DC0B0(168)==-1&&radar.resource5DC0B0(-1)==-1&&!missing,
                "Actual ore/rock classification must use the retained type/resource registries");
        RadarRGB first{},second{};const auto& oreCell=actualCell(127);
        require(&radar.type(radar.primary(oreCell.input.tile))==&p.tileImages.at(oreCell.input.tile),"Radar must borrow the canonical TMP type");
        cellRadarColors(oreCell,clear,first,second,radar);
        require(first==RadarRGB{170,170,130}&&second==first,"Actual Day1 ore must use recovered resource fallback color");
        cellRadarColors(actualCell(83),clear,first,second,radar);
        require(first==RadarRGB{bridgeFile.u8(44),bridgeFile.u8(45),bridgeFile.u8(46)}&&second==first,
                "Actual bridge Cell must select frame1 from its retained image");
        const auto& rockCell=actualCell(168);cellRadarColors(rockCell,clear,first,second,radar);
        const auto rockFrame=std::size_t(rockCell.overlayData);RadarRGB rockColor{};
        if(rockFrame<std::uint32_t(std::int32_t(std::bit_cast<std::int16_t>(rock.u16(6)))))
            rockColor={rock.u8(20+24*rockFrame),rock.u8(21+24*rockFrame),rock.u8(22+24*rockFrame)};
        require(first==rockColor&&second==first,"Actual rock Cell must use its supplied frame header");
        const auto flag=p.overlayInputs.at(127).tiberium;p.overlayInputs.at(127).tiberium=0;
        require(!radar.overlay279(127)&&radar.resource5DC0B0(127)==-1,"Radar and classifier must read the same live type flag");
        p.overlayInputs.at(127).tiberium=flag;
        auto resources=std::move(p.resourceTypes);p.resourceTypes.clear();
        cellRadarColors(oreCell,clear,first,second,radar);
        require(missing==1&&first==RadarRGB{170,170,130}&&second==first,"Missing resource must log and retain zero-result resource color");
        p.resourceTypes=std::move(resources);
        bool refused=false;const auto animation=p.overlayInputs.at(127).cellAnim;p.overlayInputs.at(127).cellAnim=17;
        try{cellRadarColors(oreCell,clear,first,second,radar);}catch(const std::invalid_argument&){refused=true;}
        p.overlayInputs.at(127).cellAnim=animation;require(refused,"Unbound actual animation owner must refuse");
        std::cout<<"Actual Day1 radar assets: canonical ore/bridge/rock Cells, shared type flags/resource fallback and animation refusal PASS\n";
        // Explicit native integration only: full-map projection geometry,
        // brightness/clear/resident policy and final callback are supplied.
        // Startup must retain both translated inputs and final LAT references.
        // Raw references alone missed the LAT-selected Rmpfx10.tem.
        for(const auto& c:p.cells){const auto tile=c.attributes.input.tile;if(tile==65535)continue;
            const auto& t=p.tileImages.at(tile);
            require(t.image&&t.prepared&&p.tiles.at(tile).image==&t.prepared->image,
                    "Final map references must use canonical resident TMP metadata");
        }
        require(p.tileImages.at(519).filename=="Rmpfx10.tem"&&p.tileImages.at(519).image,
                "Day1 LAT-selected tile519 must retain its actual file bytes");
        RadarStorage storage({11,3,0,3,5,2});TileSweepCursor cursor{};
        const int origin=0,minimum=p.width+1;int visits=0,finished=0;
        RadarTerrainServices terrain;
        terrain.position=[&](int id)->const MapInputPosition&{return p.cells.at(id).attributes.input.position;};
        terrain.colors4712C0=[&](int id,RadarRGB& a,RadarRGB& b){++visits;
            const auto& cell=p.cells.at(id).attributes;
            try{cellRadarColors(cell,clear,a,b,radar);}catch(const std::exception& error){
                throw std::runtime_error("Day1 radar Cell "+std::to_string(id)+" tile "+std::to_string(cell.input.tile)+
                    " sub "+std::to_string(cell.input.subTile)+" overlay "+std::to_string(cell.overlay)+": "+error.what());
            }
        };
        const auto populate=[&](auto& source,auto& region,std::span<std::uint8_t> rgb){
            require(&source==&region,"Actual Day1 startup must preserve source/region alias");
            updateRadarTerrain(source,region,{p.width,origin,minimum,cursor,p.slots,rgb},terrain);
        };
        RefreshRect rectangle{0,0,p.width*2,p.height*2};
        storage.initialize(rectangle,origin,origin,populate,[&]{++finished;});
        require(visits==int(p.cells.size())&&finished==1&&storage.first()!=storage.second()&&
                storage.first()->table!=storage.second()->table&&storage.displayBytes()==2&&
                storage.terrainPixels().size()==std::size_t(rectangle[2]*rectangle[3]*2),
                "Actual Day1 startup must compose every Cell onto owned surfaces with distinct kinds");
        const auto pixels=std::vector<std::uint8_t>(storage.terrainPixels().begin(),storage.terrainPixels().end());
        rectangle={0,0,p.width*2,p.height*2};storage.initialize(rectangle,origin,origin,populate,[&]{++finished;});
        require(finished==2&&visits==2*int(p.cells.size())&&
                std::equal(pixels.begin(),pixels.end(),storage.terrainPixels().begin())&&
                std::all_of(storage.displayPixels().begin(),storage.displayPixels().end(),[](auto b){return b==0;}),
                "Actual Day1 rebuild must retain terrain output while replacing/clearing owned resources");
        std::cout<<"Actual Day1 radar storage: full-map colors/aliased projection/device initializer/rebuild PASS\n";
    }
    const auto strings=std::make_shared<PreparedStringLookup>(assets.store.require("ra2.csf"));
    const auto colors=readMessageColorData(readFile(preparedDataPath(assets.engineDataSource,"message-color-data.bin")),assets.engineDataSource);
    auto invalidColors=readFile(preparedDataPath(assets.engineDataSource,"message-color-data.bin"));
    {auto bytes=*invalidColors.storage;bytes.back()^=1;bool refused=false;try{(void)readMessageColorData(Data(std::move(bytes)),assets.engineDataSource);}catch(const std::runtime_error&){refused=true;}require(refused,"Changed message-color bytes must refuse");}
    const auto mission=readMissionDefinition(source);missionCloneCheck(mission,source,rules,strings,colors,assets);buildingOwnerCheck(mission,source,rules,strings,colors,assets);revealOwnerCheck(assets,mission,source,rules,art);BootCampWalkWorld world(assets,mission,source,rules,art);
    require(world.visibilityWorld().redrawQueue().dirtyD7D==1&&world.visibilityWorld().redrawQueue().countE0==0,
        "Startup GI Mark must dirty actual Tactical without queuing Cells");
    for(const auto& cell:world.map().cells){const auto& input=cell.attributes.input;
        require(&world.visibilityWorld().at({input.position.x,input.position.y}).flags140==&input.flags,
                "Every production visibility Cell must borrow actual terrain flags140");}
    {
        auto& prepared=BootCampWalkWorldInspection::radarPrepared(world);CellRadarColorServices radar;
        // Explicit startup on the unique source before any clone exists. Queries
        // below consume warmed immutable images; discarded previews never load.
        prepared.initializeOverlayImage(assets.store,83,0);
        prepared.initializeOverlayImage(assets.store,168,0);
        bindPreparedRadarAssets(radar,prepared,assets.store,0);
        radar.resident471760=[](auto,auto){return false;};radar.theaterScale=[] {return 1.0f;};const int clear=0;
        std::size_t id=0;while(id<world.map().cells.size()&&world.map().cells[id].attributes.overlay!=127)++id;
        require(id<world.map().cells.size(),"Mutable Day1 resource Cell missing");
        auto& cell=BootCampWalkWorldInspection::radarCell(world,id);
        require(&cell!=&prepared.cells.at(id).attributes&&cell.overlay==prepared.cells.at(id).attributes.overlay,
                "Radar integration must read the application's mutable Cell rather than its initial seed");
        const auto before=snapshot(world);RadarRGB first{},second{};
        cellRadarColors(cell,clear,first,second,radar);
        require(first==RadarRGB{170,170,130}&&second==first,"Mutable Day1 Cell must reach actual resource types");
        const auto overlay=cell.overlay;cell.overlay=-1;
        cellRadarColors(cell,clear,first,second,radar);
        require(first!=RadarRGB{170,170,130}&&second==first&&prepared.cells.at(id).attributes.overlay==127,
                "Radar must observe live Cell overlay changes without reading or mutating the initial seed");
        cell.overlay=overlay;cellRadarColors(cell,clear,first,second,radar);
        require(first==RadarRGB{170,170,130}&&second==first&&snapshot(world)==before,
                "Restored radar query must preserve actual mission/Walk/visibility state");
        std::cout<<"Production mutable radar Cell: shared prepared assets, live overlay removal/restoration and owner isolation PASS\n";
        RadarStorage storage({11,3,0,3,5,2});TileSweepCursor cursor{};
        const auto& map=world.map();const int origin=0,minimum=map.width+1;
        RadarTerrainServices terrain;
        terrain.position=[&](int key)->const MapInputPosition&{return map.cells.at(key).attributes.input.position;};
        terrain.colors4712C0=[&](int key,RadarRGB& a,RadarRGB& b){cellRadarColors(map.cells.at(key).attributes,clear,a,b,radar);};
        const auto rebuild=[&]{
            RefreshRect rectangle{0,0,map.width*2,map.height*2};
            storage.initialize(rectangle,origin,origin,[&](auto& source,auto& region,std::span<std::uint8_t> rgb){
                updateRadarTerrain(source,region,{map.width,origin,minimum,cursor,map.slots,rgb},terrain);
            },[&]{if(argc==4)storage.initializeShapeBuckets(radarWidths,radarHeights);});
        };
        rebuild();const auto originalRGB=std::vector<std::uint8_t>(storage.terrainRGB().begin(),storage.terrainRGB().end());
        const auto originalPixels=std::vector<std::uint8_t>(storage.terrainPixels().begin(),storage.terrainPixels().end());
        const auto rockImage=prepared.overlayInputs.at(168).image,bridgeImage=prepared.overlayInputs.at(83).image;
        cell.overlay=-1;rebuild();
        require(!std::equal(originalRGB.begin(),originalRGB.end(),storage.terrainRGB().begin())&&
                !std::equal(originalPixels.begin(),originalPixels.end(),storage.terrainPixels().begin())&&
                prepared.cells.at(id).attributes.overlay==127,
                "Whole-map radar startup must observe actual mutable Cell edits through to projected pixels");
        cell.overlay=overlay;rebuild();
        require(std::equal(originalRGB.begin(),originalRGB.end(),storage.terrainRGB().begin())&&
                std::equal(originalPixels.begin(),originalPixels.end(),storage.terrainPixels().begin())&&snapshot(world)==before&&
                prepared.overlayInputs.at(168).image==rockImage&&prepared.overlayInputs.at(83).image==bridgeImage,
                "Restored production map must rebuild identical pixels without mission or warmed asset mutation");
        const auto display=storage.displayPixels().data();
        require(storage.setDisplayPixel(1,2,0xdead1234)&&storage.getDisplayPixel(1,2)==0x1234&&
                storage.displayPixels().data()==display&&
                storage.displayPixels()[std::size_t(storage.first()->width)*4+2]==0x34&&
                storage.displayPixels()[std::size_t(storage.first()->width)*4+3]==0x12&&
                !storage.setDisplayPixel(-1,2,0xffff)&&storage.getDisplayPixel(-1,2)==0&&
                std::equal(originalPixels.begin(),originalPixels.end(),storage.terrainPixels().begin())&&
                std::equal(originalRGB.begin(),originalRGB.end(),storage.terrainRGB().begin())&&snapshot(world)==before,
                "Device pixels must use the first backing and retain terrain/mission/Walk/visibility owners");
        require(storage.setDisplayPixel(1,2,0)&&storage.getDisplayPixel(1,2)==0,
                "Device unlock must permit fresh locking and exact restoration");
        std::cout<<"Production mutable radar device pixels: borrowed first backing/read/write/unlock and terrain/world isolation PASS\n";
        RefreshRect sourceRect{},destinationRect{};
        refreshSurfaceRect(*storage.second(),sourceRect);refreshSurfaceRect(*storage.first(),destinationRect);
        storage.first()->table->copy8(*storage.first(),&destinationRect,storage.second(),&sourceRect,0,255);
        require(storage.displayPixels().data()==display&&
                storage.displayPixels().size()==storage.terrainPixels().size()&&
                std::equal(storage.displayPixels().begin(),storage.displayPixels().end(),storage.terrainPixels().begin())&&
                std::equal(originalPixels.begin(),originalPixels.end(),storage.terrainPixels().begin())&&
                std::equal(originalRGB.begin(),originalRGB.end(),storage.terrainRGB().begin())&&snapshot(world)==before,
                "Actual first device copy8 must copy the owned terrain without mutating source/world owners");
        require(storage.getDisplayPixel(1,2)==std::uint32_t(storage.terrainPixels()[std::size_t(storage.first()->width)*4+2])+
                (std::uint32_t(storage.terrainPixels()[std::size_t(storage.first()->width)*4+3])<<8),
                "Copied display must retain actual device readback/unlock behavior");
        std::cout<<"Production mutable radar device copy: actual first table/terrain source/backing/world isolation PASS\n";
        {
            // Surface integration on the actual mutable Day1 terrain storage.
            // House/map/discovery/actor-mark inputs here are explicit diagnostic
            // services, not recovered production associations or scheduling.
            std::int32_t mode=0,zero=0,count=0;std::uint32_t locale=0;
            const void* current=&world;
            SurfaceMarkBuckets bucketStorage{};auto* buckets=&bucketStorage;
            auto* bitmap=&storage.markBitmap();
            std::array<std::uint8_t,2> paletteBytes{0x34,0x12};
            SurfaceMarkPalette palette{2,paletteBytes};SurfaceMarkScheme scheme{&palette,0};
            std::array<const SurfaceMarkScheme*,1> schemeSlots{&scheme};
            std::span<const SurfaceMarkScheme*> registry=schemeSlots;
            RadarColorWorld colors{current,{},{},{}};
            SchemeResolverWorld resolver{registry,count,locale,{},{},{},{}};
            RadarPixelActorWorld actors{colors,zero,resolver,{},{},{},{}};
            RefreshRect dirty{};
            const std::array<std::int32_t,6> shifts{11,3,0,3,5,2};
            RadarPixelServices pixels{current,mode,storage.firstOwner(),storage.secondOwner(),storage.scaleOwner(),
                zero,zero,zero,zero,dirty,buckets,shifts,zero};
            bool hidden=false,dim=false;int floorCalls=0;
            pixels.floor55A280=[&](auto&){++floorCalls;return 0;};
            pixels.discovery568140=[&](auto&){return std::uint8_t(hidden);};
            pixels.discovery568280=[&](auto&){return std::uint8_t(dim);};
            pixels.owner1B4=[&](auto){return current;};pixels.actorC0=[](auto){return std::uint8_t(0);};
            SurfaceMarkServices marks{storage.firstOwner(),buckets,bitmap,registry};
            marks.houseIndex15F40=[](auto){return 0;};
            SurfaceRefreshServices refresh{mode,storage.firstOwner(),storage.secondOwner(),{}, {}};
            SurfaceCopyServices owners{[&](auto& receiver)->CopySurface&{return storage.copyOwner(receiver);}};
            std::array<RefreshSurfaceVirtuals*,2> tables{storage.first()->table,storage.second()->table};
            RadarRefreshSurfacePolicy policy{[&](auto* table){return table==tables[0];}};
            auto& device=storage.copyOwner(*storage.first());const auto lock=device.lock5C;
            int deviceLocks=0;device.lock5C=[&](auto x,auto y){++deviceLocks;return lock(x,y);};
            const auto matchesTerrain=[&]{return std::equal(storage.displayPixels().begin(),storage.displayPixels().end(),storage.terrainPixels().begin());};
            SurfaceRefreshScratch scratch{};
            {
                RadarRefreshBinding binding(refresh,marks,pixels,actors,tables,owners,{},policy);
                require(deviceLocks==0&&floorCalls==0,"Refresh construction queried device/map owners");
                refreshSurfaces(refresh,scratch);
                require(matchesTerrain()&&deviceLocks==1&&floorCalls==0,
                        "Zero refresh must retain the actual device copy and mark bitmap backing");
                // A controlled marker on the actual GI identity must use the
                // same device writer after copying, never a software lock.
                const auto gi=world.actors().begin()->first;
                SurfaceMarkEntry entry{&world.actor(gi),1,2,0};
                bucketStorage[0]={{&entry,1},1};
                refreshSurfaces(refresh,scratch);
                require(deviceLocks==3&&storage.getDisplayPixel(1,2)==0x1234&&bitmap->bytes.data()==storage.bitmap().data(),
                        "Copy then mark must use actual device pixels and startup bitmap");
                bucketStorage[0]={};mode=1;deviceLocks=0;
                refreshSurfaces(refresh,scratch);
                const auto area=storage.first()->width*storage.first()->height;
                require(matchesTerrain()&&deviceLocks==area&&floorCalls==area,
                        "Nonzero refresh must read terrain and write every actual device pixel");
                hidden=true;deviceLocks=0;refreshSurfaces(refresh,scratch);
                require(deviceLocks==area&&std::all_of(storage.displayPixels().begin(),storage.displayPixels().end(),[](auto v){return v==0;}),
                        "Hidden refresh must clear display through actual device locks");
                dim=true;deviceLocks=0;refreshSurfaces(refresh,scratch);
                for(std::size_t i=0;i<storage.terrainPixels().size();i+=2){
                    const auto source=std::uint32_t(storage.terrainPixels()[i])|(std::uint32_t(storage.terrainPixels()[i+1])<<8);
                    const auto actual=std::uint32_t(storage.displayPixels()[i])|(std::uint32_t(storage.displayPixels()[i+1])<<8);
                    require(actual==darkenRadarPixel(source,shifts),"Dim refresh must use actual terrain/device backings");
                }
                require(deviceLocks==area,"Dim refresh bypassed device locks");
                mode=0;refreshSurfaces(refresh,scratch);require(matchesTerrain(),"Repeated zero refresh failed after nonzero branches");
            }
            device.lock5C=lock;
            require(!refresh.pixel632000&&!marks.pixel24&&!storage.second()->table->copy8&&
                    std::equal(originalPixels.begin(),originalPixels.end(),storage.terrainPixels().begin())&&
                    std::equal(originalRGB.begin(),originalRGB.end(),storage.terrainRGB().begin())&&snapshot(world)==before,
                    "Scoped refresh must restore callbacks and preserve terrain/mission/Walk/visibility owners");
            storage.first()->table->copy8(*storage.first(),&destinationRect,storage.second(),&sourceRect,0,1);
            require(matchesTerrain(),"Scoped refresh replaced the native device copy");
            rebuild();refreshSurfaceRect(*storage.first(),destinationRect);refreshSurfaceRect(*storage.second(),sourceRect);
            storage.first()->table->copy8(*storage.first(),&destinationRect,storage.second(),&sourceRect,0,1);
            require(matchesTerrain()&&storage.markBitmap().bytes.data()==storage.bitmap().data()&&
                    &storage.copyOwner(*storage.first()).pixels.width4==&storage.first()->width&&snapshot(world)==before,
                    "Startup after entered refresh must replace borrowed adapters before destroying backing");
            RefreshSurface foreign{tables[0],1,1};bool foreignRefused=false;
            try{(void)storage.copyOwner(foreign);}catch(const std::invalid_argument&){foreignRefused=true;}
            require(foreignRefused,"Radar storage accepted foreign geometry");
            {
                auto actual=world.clone();
                current=actual->visibilityWorld().house(actual->missionWorld().currentHouse());
                const auto setup=[&](BootCampWalkWorld& owner,std::uint32_t flags,int coverage){
                    for(auto& c:BootCampWalkWorldInspection::visibilityCells(owner)){c.flags12c=flags;c.count13c=coverage;}
                    auto& c=BootCampWalkWorldInspection::visibilityFallback(owner);c.flags12c=flags;c.count13c=coverage;
                };
                const auto actorBytes=[](const BootCampWalkWorld& owner){
                    std::string bytes;for(const auto& [id,a]:owner.actors()){
                        bytes.append(reinterpret_cast<const char*>(&a),sizeof(a));
                    }return bytes;
                };
                const auto actorBefore=actorBytes(*actual);
                const auto missionBefore=actual->missionWorld().state();
                const auto diagnosticCalls=floorCalls;mode=1;
                RadarRefreshBinding binding(refresh,marks,pixels,actors,tables,owners,{},policy);
                setup(*actual,8,0);
                actual->visibilityWorld().refreshRadar(refresh,pixels,scratch,binding);
                require(matchesTerrain()&&floorCalls==diagnosticCalls,
                        "Actual map refresh must replace supplied floor/discovery answers");
                setup(*actual,0,0);
                actual->visibilityWorld().refreshRadar(refresh,pixels,scratch,binding);
                require(std::all_of(storage.displayPixels().begin(),storage.displayPixels().end(),[](auto v){return v==0;}),
                        "Actual Cell12C must control radar discovery independently of terrain140");
                setup(*actual,8,1);
                actual->visibilityWorld().refreshRadar(refresh,pixels,scratch,binding);
                for(std::size_t i=0;i<storage.terrainPixels().size();i+=2){
                    const auto source=std::uint32_t(storage.terrainPixels()[i])|(std::uint32_t(storage.terrainPixels()[i+1])<<8);
                    const auto output=std::uint32_t(storage.displayPixels()[i])|(std::uint32_t(storage.displayPixels()[i+1])<<8);
                    require(output==darkenRadarPixel(source,shifts),"Actual Cell13C must select dim terrain");
                }
                const auto& fallback=actual->visibilityWorld().fallback();
                require(fallback.point==actual->visibilityWorld().state().fallbackPoint&&
                        fallback.point.x==actual->map().fallback.input.position.x&&fallback.point.y==actual->map().fallback.input.position.y&&
                        actual->visibilityWorld().state().fallbackStores>0&&
                        actorBytes(*actual)==actorBefore&&actual->missionWorld().state().textRequests==missionBefore.textRequests,
                        "Actual radar map must share fallback and preserve actor/mission state");
                auto warm=actual->clone();
                require(warm->visibilityWorld().at({57,89}).count13c==1&&warm->visibilityWorld().fallback().count13c==1,
                        "Warm visibility clones must preserve independent13C counters");
                current=warm->visibilityWorld().house(warm->missionWorld().currentHouse());actual.reset();
                warm->visibilityWorld().refreshRadar(refresh,pixels,scratch,binding);
                require(warm->visibilityWorld().at({57,89}).count13c==1&&actorBytes(*warm)==actorBefore,
                        "Radar map bindings must survive source destruction on warm owners");
                const auto stateBefore=warm->visibilityWorld().state();
                current=&world;bool rejected=false;
                try{warm->visibilityWorld().refreshRadar(refresh,pixels,scratch,binding);}catch(const std::invalid_argument&){rejected=true;}
                require(rejected&&warm->visibilityWorld().state().mapQueries==stateBefore.mapQueries,
                        "Foreign player House must refuse before map queries");
                require(snapshot(world)==before,"Actual radar refresh on warm owners mutated source world");
                std::cout<<"Actual Boot Camp radar map refresh: shared floor/12C/13C/140/fallback, warm clone/source destruction PASS (empty actor buckets)\n";
            }
            {
                auto actual=world.clone();int gi=-1,enemy=-1;
                for(const auto& [id,a]:actual->actors())if(actual->player(id))gi=id;else enemy=id;
                require(gi>=0&&enemy>=0,"Actual radar marker check needs player/nonplayer GIs");
                const int playerHouse=actual->missionWorld().currentHouse();
                const int enemyHouse=actual->actor(enemy).object.mission.owner;
                auto& playerFields=actual->missionWorld().house(playerHouse);
                auto& enemyFields=actual->missionWorld().house(enemyHouse);
                require(playerHouse!=enemyHouse&&playerFields.indexAlliance.countryIndex>=0&&playerFields.indexAlliance.countryIndex<32,
                        "Actual radar marker check needs distinct bounded House indexes");
                for(const auto& [id,h]:actual->missionWorld().houses()){
                    auto& fields=actual->missionWorld().house(id);fields.radarColor55e9={32,64,248};fields.radarScheme15f40=1;
                }
                playerFields.radarColor55e9={248,128,64};playerFields.radarScheme15f40=0;
                enemyFields.indexAlliance.countryIndex=(playerFields.indexAlliance.countryIndex+1)%32;
                enemyFields.indexAlliance.allianceMask=0;playerFields.indexAlliance.allianceMask=0;
                for(auto& c:BootCampWalkWorldInspection::visibilityCells(*actual)){c.flags12c=8;c.count13c=0;}
                auto& fallback=BootCampWalkWorldInspection::visibilityFallback(*actual);fallback.flags12c=8;fallback.count13c=0;
                std::array<std::uint8_t,4> alternateBytes{0,0,0xef,0xbe};
                SurfaceMarkPalette alternatePalette{2,alternateBytes};SurfaceMarkScheme alternateScheme{&alternatePalette,1};
                std::array<const SurfaceMarkScheme*,2> schemes{&scheme,&alternateScheme};
                std::span<const SurfaceMarkScheme*> actualRegistry=schemes;
                const std::int32_t actualCount=2;
                SchemeResolverWorld actualResolver{actualRegistry,actualCount,locale,
                    [&](auto* p){return p==&alternateScheme?std::string_view("LightGrey"):std::string_view("Other");},
                    [](auto*){return 1;},{},{}};
                SurfaceMarkBuckets actualBuckets{};auto* actualBucketPointer=&actualBuckets;
                std::array<SurfaceMarkEntry,3> entries{};
                const auto render=[&](BootCampWalkWorld& owner){
                    current=owner.visibilityWorld().house(owner.missionWorld().currentHouse());
                    entries={SurfaceMarkEntry{&owner.actor(gi),1,2,0},SurfaceMarkEntry{&owner.actor(enemy),2,2,0},
                        SurfaceMarkEntry{owner.missionWorld().structureResident(1019675).identity,3,2,0}};
                    for(auto& bucket:actualBuckets)bucket={};
                    for(auto& entry:entries)actualBuckets[(std::uint32_t(entry.x)-std::uint32_t(entry.y)*5u)&255u]={{&entry,1},1};
                    RadarPixelServices activePixels{current,mode,storage.firstOwner(),storage.secondOwner(),storage.scaleOwner(),
                        zero,zero,zero,zero,dirty,actualBucketPointer,shifts,owner.tickOwner()};
                    activePixels.flashDivisor90=[] {return 1;}; // Explicit supplied flash-divisor association.
                    SurfaceMarkServices activeMarks{storage.firstOwner(),actualBucketPointer,bitmap,actualRegistry};
                    SurfaceRefreshServices activeRefresh{mode,storage.firstOwner(),storage.secondOwner(),{}, {}};
                    int typeCalls=0;RadarPixelActorProbes probes;probes.type=[&](auto,auto){++typeCalls;};
                    {
                        BootCampRadarActors borrowed(owner,activePixels,activeMarks,actualResolver,probes);
                        require(typeCalls==0,"Actual actor binding queried type during construction");
                        const auto& h=owner.missionWorld().house(playerHouse);
                        require(&borrowed.world().house(current).flag134==&h.human134&&
                                &borrowed.world().house(current).color55E9==&h.radarColor55e9&&
                                &borrowed.world().timer(&owner.actor(gi)).start13C==&owner.actor(gi).radarTimerStart13c&&
                                borrowed.world().type(&owner.actor(gi))==&BootCampWalkWorldInspection::walkType(owner)&&
                                &borrowed.world().timer(entries[2].actor).start13C==&owner.missionWorld().structureSightState(1019675).radarTimerStart13c&&
                                &borrowed.world().colors.actor(entries[2].actor).byte170==&owner.missionWorld().structureExpirationState(1019675).byte170,
                                "Radar fields must borrow the actual House/Infantry/type owners");
                        RadarRefreshBinding shared(activeRefresh,activeMarks,activePixels,borrowed.world(),tables,owners,{},policy);
                        owner.visibilityWorld().refreshRadar(activeRefresh,activePixels,scratch,shared);
                        bool rejected=false;try{(void)activePixels.owner1B4(&world.actor(gi));}catch(const std::invalid_argument&){rejected=true;}
                        require(rejected,"Foreign radar actor must refuse without dereferencing it");
                        rejected=false;try{(void)borrowed.world().typeByte1FF(reinterpret_cast<const void*>(1));}catch(const std::invalid_argument&){rejected=true;}
                        require(rejected,"Foreign radar type must refuse without dereferencing it");
                        rejected=false;try{(void)borrowed.world().house(world.visibilityWorld().house(playerHouse));}catch(const std::invalid_argument&){rejected=true;}
                        require(rejected,"Foreign radar House must refuse without accepting equal field values");
                    }
                    require(!activePixels.actorC0&&!activeMarks.houseIndex15F40&&!activeRefresh.pixel632000,
                            "Actual actor bindings must restore callbacks");
                };
                mode=0;render(*actual);
                require(storage.getDisplayPixel(1,2)==0x1234&&storage.getDisplayPixel(2,2)==0xbeef,
                        "Zero refresh must read actual House scheme indexes and palettes");
                mode=1;render(*actual);
                require(storage.getDisplayPixel(1,2)==0xfc08&&storage.getDisplayPixel(2,2)==0x221f,
                        "Nonzero refresh must pack actual player/nonplayer House colors");
                auto unrelated=actual->missionWorld().inspectStructureExpiration(1019676);
                const auto unrelatedType=unrelated.fields.type418;unrelated.fields.type418=reinterpret_cast<const void*>(1);
                render(*actual);unrelated.fields.type418=unrelatedType;
                require(storage.getDisplayPixel(1,2)==0xfc08,"An unentered Building type must not become a radar dependency");
                auto& playerActor=BootCampWalkWorldInspection::actorMutable(*actual,gi);
                playerActor.object.mission.owner=enemyHouse;render(*actual);
                require(storage.getDisplayPixel(1,2)==0x221f,"Radar Owner must observe the actual live Infantry House field");
                playerActor.byte170=1;playerActor.alternateHouse410=playerHouse;render(*actual);
                require(storage.getDisplayPixel(1,2)==0xfc08,"Infantry CC must select actual alternate House after nonallied test");
                auto& type=BootCampWalkWorldInspection::walkType(*actual);type.radarFlag1ff=1;render(*actual);
                const auto at=std::size_t(storage.first()->width)*4+2;
                const auto terrainPixel=std::uint32_t(storage.terrainPixels()[at])|(std::uint32_t(storage.terrainPixels()[at+1])<<8);
                require(storage.getDisplayPixel(1,2)==terrainPixel,"Actual type1FF must reject a nonallied Owner before alternate color");
                enemyFields.indexAlliance.allianceMask=1u<<unsigned(playerFields.indexAlliance.countryIndex);render(*actual);
                require(storage.getDisplayPixel(1,2)==terrainPixel,"Owner-to-current alliance must not replace the current-to-Owner type filter");
                playerFields.indexAlliance.allianceMask=1u<<unsigned(enemyFields.indexAlliance.countryIndex);render(*actual);
                require(storage.getDisplayPixel(1,2)==0x221f,"Actual alliance mutation must permit the type-filtered actor and select its Owner");
                type.radarFlag1ff=0;playerActor.object.mission.owner=playerHouse;playerActor.byte170=0;
                playerActor.radarTimerStart13c=-1;playerActor.radarTimerRemaining144=2;render(*actual);
                require(storage.getDisplayPixel(1,2)==0x03f7,"Actual timer/current Owner must invert the flashing color");
                playerActor.radarTimerStart13c=actual->tick();render(*actual);
                require(storage.getDisplayPixel(1,2)==0x03f7,"Actual running timer must initially retain its flash phase");
                actual->step();render(*actual);
                require(storage.getDisplayPixel(1,2)==0xfc08,"Actual Walk frame advancement must change the running timer flash phase");
                playerActor.radarTimerStart13c=-1;render(*actual);
                auto building=actual->missionWorld().inspectStructureExpiration(1019675);building.fields.byte170=1;render(*actual);
                require(storage.getDisplayPixel(3,2)==1,"Actual Building CC null must enter the shared LightGrey resolver");
                mode=0;render(*actual);require(storage.getDisplayPixel(3,2)==0xbeef,
                        "Actual Building zero-mode fallback must use resolved palette rather than raw scheme index");
                auto warm=actual->clone();actual.reset();mode=1;render(*warm);
                require(storage.getDisplayPixel(1,2)==0x03f7&&storage.getDisplayPixel(3,2)==1&&
                        warm->actor(gi).radarTimerRemaining144==2&&warm->actor(gi).alternateHouse410==playerHouse&&
                        warm->missionWorld().house(playerHouse).radarColor55e9==std::array<std::uint8_t,3>{248,128,64}&&snapshot(world)==before,
                        "Warm actor/House/type/timer state must survive source destruction without source mutation");
                {
                    // Same storage-owned buckets for production of entries and
                    // both existing drawing branches. Coordinates remain explicit;
                    // no actor footprint or frame/sight scheduler is supplied here.
                    const auto operate=[&](BootCampWalkWorld& owner,const auto& operation){
                        current=owner.visibilityWorld().house(owner.missionWorld().currentHouse());
                        RadarPixelServices activePixels{current,mode,storage.firstOwner(),storage.secondOwner(),storage.scaleOwner(),
                            zero,zero,zero,zero,dirty,storage.markerBucketsOwner(),shifts,owner.tickOwner()};
                        activePixels.flashDivisor90=[] {return 1;};
                        SurfaceMarkServices activeMarks{storage.firstOwner(),storage.markerBucketsOwner(),bitmap,actualRegistry};
                        SurfaceRefreshServices activeRefresh{mode,storage.firstOwner(),storage.secondOwner(),{}, {}};
                        BootCampRadarActors borrowed(owner,activePixels,activeMarks,actualResolver);
                        const auto markerServices=borrowed.markerServices();
                        RadarRefreshBinding shared(activeRefresh,activeMarks,activePixels,borrowed.world(),tables,owners,{},policy);
                        const auto draw=[&]{owner.visibilityWorld().refreshRadar(activeRefresh,activePixels,scratch,shared);};
                        operation(markerServices,borrowed,draw);
                        owner.visibilityWorld().refreshRadar(activeRefresh,activePixels,scratch,shared);
                    };
                    auto& a=BootCampWalkWorldInspection::actorMutable(*warm,gi);a.byte170=0;a.radarTimerRemaining144=0;
                    const auto* playerIdentity=&warm->actor(gi);const auto* enemyIdentity=&warm->actor(enemy);
                    const auto* buildingIdentity=warm->missionWorld().structureResident(1019675).identity;
                    const auto selectedBucket=radarMarkerBucket(4,3);mode=0;
                    operate(*warm,[&](const auto& service,auto&,const auto&){
                        const auto p=service.position(playerIdentity);
                        require(&p.x1A0==&a.radarX1a0&&&p.y1A4==&a.radarY1a4,
                                "Marker position must borrow actual GI fields");
                        storage.insertMarker(enemyIdentity,4,3,current,service);
                        storage.insertMarker(playerIdentity,4,3,current,service);
                        storage.insertMarker(playerIdentity,4,3,current,service);
                        const auto& b=(*storage.markerBucketsOwner())[selectedBucket];
                        require(b.count==2&&b.entries[0].actor==playerIdentity&&b.entries[1].actor==enemyIdentity&&
                                b.entries[0].trailer==reinterpret_cast<std::uintptr_t>(playerIdentity),
                                "Actual player insertion must prepend, duplicate must bypass and trailer must retain actor identity");
                    });
                    require(storage.getDisplayPixel(4,3)==0x1234,"Generated owned buckets must feed actual zero-mode drawing");
                    mode=1;operate(*warm,[](const auto&,auto&,const auto&){});
                    require(storage.getDisplayPixel(4,3)==0xfc08,"Generated owned buckets must feed actual nonzero drawing");
                    mode=0;operate(*warm,[&](const auto& service,auto&,const auto&){
                        storage.removeMarker(playerIdentity,4,3,current,service);
                        const auto& b=(*storage.markerBucketsOwner())[selectedBucket];
                        require(b.count==1&&b.entries[0].actor==enemyIdentity&&b.entries[1].actor==enemyIdentity,
                                "Actual removal must shift resident identity and retain inactive tail");
                    });
                    require(storage.getDisplayPixel(4,3)==0xbeef,"Removing player marker must expose actual nonplayer marker");
                    operate(*warm,[&](const auto& service,auto&,const auto&){
                        storage.removeMarker(enemyIdentity,4,3,current,service);
                        storage.removeMarker(enemyIdentity,4,3,current,service);
                    });
                    const auto location=std::size_t(storage.first()->width*3+4)*2;
                    require(storage.getDisplayPixel(4,3)==std::uint32_t(storage.terrainPixels()[location])+
                            (std::uint32_t(storage.terrainPixels()[location+1])<<8),
                            "Removing final generated marker must restore actual terrain through refresh");
                    operate(*warm,[&](const auto& service,auto&,const auto&){
                        const auto beforeBuilding=warm->missionWorld().structureSightState(1019675);
                        storage.insertMarker(buildingIdentity,-1,2,current,service);
                        storage.insertMarker(playerIdentity,-1,2,current,service);
                        require(a.radarX1a0==0&&a.radarY1a4==2&&
                                warm->missionWorld().structureSightState(1019675)==beforeBuilding&&
                                (*storage.markerBucketsOwner())[radarMarkerBucket(0,2)].count==1,
                                "Actual Building offscreen bypass and GI clamped stores must stay distinct");
                        bool rejected=false;try{storage.insertMarker(&world.actor(gi),-1,2,current,service);}catch(const std::invalid_argument&){rejected=true;}
                        require(rejected,"Foreign marker actor must refuse before clamped writes");
                    });
                    require(storage.getDisplayPixel(0,2)==0x1234,"Clamped actual GI marker must draw from the owned bucket");
                    auto markerWarm=warm->clone();
                    require(markerWarm->actor(gi).radarX1a0==0&&markerWarm->actor(gi).radarY1a4==2,
                            "Warm actual GI clones must retain recovered clamped field values");
                    // Explicitly retire active borrowed identities before their
                    // owner dies, then produce entries for the surviving clone.
                    operate(*warm,[&](const auto& service,auto&,const auto&){storage.removeMarker(playerIdentity,0,2,current,service);});
                    warm.reset();
                    operate(*markerWarm,[&](const auto& service,auto&,const auto&){storage.insertMarker(&markerWarm->actor(gi),4,3,current,service);});
                    require((*storage.markerBucketsOwner())[selectedBucket].entries[0].actor==&markerWarm->actor(gi)&&
                            storage.getDisplayPixel(4,3)==0x1234&&snapshot(world)==before,
                            "Explicit retired/rebound markers must survive old owner destruction without source mutation");
                    operate(*markerWarm,[&](const auto& service,auto&,const auto&){storage.removeMarker(&markerWarm->actor(gi),4,3,current,service);});
                    operate(*markerWarm,[&](const auto&,auto& callers,const auto& draw){
                        auto& fields=BootCampWalkWorldInspection::actorMutable(*markerWarm,gi);
                        fields.radarX1a0=4;fields.radarY1a4=3;
                        callers.updateMarker(storage,&fields,RadarActorMarkerOperation::insert);
                        require(fields.radarRegistered37b==1&&(*storage.markerBucketsOwner())[selectedBucket].count==1,
                                "Complete actual Infantry caller must register after owned insertion");
                    });
                    require(storage.getDisplayPixel(4,3)==0x1234,"Actual Infantry registration caller must feed existing drawing");
                    auto registeredClone=markerWarm->clone();
                    require(registeredClone->actor(gi).radarRegistered37b==1,"Warm clones retain actual registration state");
                    operate(*markerWarm,[&](const auto&,auto& callers,const auto& draw){
                        callers.updateMarker(storage,&markerWarm->actor(gi),RadarActorMarkerOperation::dirty);
                        callers.updateMarker(storage,&markerWarm->actor(gi),RadarActorMarkerOperation::remove);
                        require(markerWarm->actor(gi).radarRegistered37b==0&&(*storage.markerBucketsOwner())[selectedBucket].count==0,
                                "Actual Infantry dirty/removal callers must retire shared markers");
                        if(argc==4){
                            const auto resident=markerWarm->missionWorld().structureResident(1019675).identity;
                            auto& building=markerWarm->missionWorld().structureSight(1019675).fields;
                            building.radarX1a0=4;building.radarY1a4=3;
                            const auto index=markerWarm->missionWorld().structureSightType(1019675).radarFootprintC78;
                            const auto& footprint=radarActorFootprint(storage.shapeBuckets(),index);
                            require(footprint.count>0,"Private-dimension initialized footprint must be nonempty");
                            callers.updateMarker(storage,resident,RadarActorMarkerOperation::insert);
                            require(building.radarRegistered37b==1,"Actual Building caller must set registration after footprint iteration");
                            for(int j=0;j<footprint.count;++j){const auto point=footprint.items[std::size_t(j)];
                                const auto x=fillAdd(4,point.x),y=fillAdd(3,point.y);
                                if(x>=0&&x<storage.first()->width&&y>=0&&y<storage.first()->height)
                                    require(findRadarMarker((*storage.markerBucketsOwner())[radarMarkerBucket(x,y)],resident,x,y)>=0,
                                            "Every entered actual footprint point must reach the shared marker buckets");
                            }
                            callers.updateMarker(storage,resident,RadarActorMarkerOperation::dirty);
                            callers.updateMarker(storage,resident,RadarActorMarkerOperation::remove);
                            require(building.radarRegistered37b==0,"Actual Building removal caller must clear registration");
                            for(const auto& bucket:*storage.markerBucketsOwner())for(int j=0;j<bucket.count;++j)
                                require(bucket.entries[std::size_t(j)].actor!=resident,"Building removal must retire every actual footprint identity");
                        }
                        bool refused=false;try{callers.updateMarker(storage,&world.actor(gi),RadarActorMarkerOperation::insert);}
                        catch(const std::invalid_argument&){refused=true;}
                        require(refused,"Actual caller adapter must refuse foreign identities");
                    });
                    require(snapshot(world)==before,"Actual marker callers must preserve source-world isolation");
                    // Explicit complete parent seam: genuine shared-map visibility,
                    // actual projection/registration/drawing, supplied permission0/1
                    // and status0. No tick, arrival or objective callback adopts it.
                    operate(*markerWarm,[&](const auto&,auto& callers,const auto& draw){
                        auto& actor=BootCampWalkWorldInspection::actorMutable(*markerWarm,gi);
                        const int loading=0,originX=map.width-1,originY=minimum;
                        const auto sourcePoint=actor.ground.position;
                        RadarShapePoint expected{},input{sourcePoint.x,sourcePoint.y};
                        const auto projection=RadarMarkerProjectionFields{storage.scaleOwner(),originX,originY,storage.first()->width,storage.first()->height};
                        projectRadarMarker(expected,input,0,projection);
                        std::uint32_t permit=1;int permissionCalls=0,primaryStores=0,projections=0;
                        RadarActorPlacementServices services;
                        services.permission2F8=[&](auto& status){require(status==0,"Actual placement status must begin at zero");++permissionCalls;return permit;};
                        services.project631BA0=[&](auto point,auto clamp){++projections;RadarShapePoint output{},inputPoint{point.x,point.y};
                            projectRadarMarker(output,inputPoint,clamp,projection);return output;};
                        services.rectangle78=[&]{RefreshRect output{};return *storage.first()->table->rect78(*storage.first(),output);};
                        services.store=[&](auto off,auto,auto){if(off==0x373)++primaryStores;};
                        actor.object.mission.current373=0;actor.radarTimerRemaining144=0;
                        const auto hidden=markerWarm->visibilityWorld().visible(actor.ground.position,false);
                        callers.placeMarker(storage,&actor,1,loading,services);
                        require(primaryStores==1&&actor.object.mission.current373==!hidden&&permissionCalls==1&&projections==1&&
                                actor.radarRegistered37b==1&&actor.radarX1a0==expected.x&&actor.radarY1a4==expected.y&&
                                findRadarMarker((*storage.markerBucketsOwner())[radarMarkerBucket(expected.x,expected.y)],&actor,expected.x,expected.y)>=0,
                                "Complete actual GI placement must join the shared visibility predicate, projection and registered marker owner");
                        draw();
                        require(storage.getDisplayPixel(expected.x,expected.y)==0x1234,
                                "The complete parent-generated actual GI marker must draw through shared refresh");
                        actor.ground.position.x=fillAdd(actor.ground.position.x,256);
                        actor.radarTimerStart13c=-1;actor.radarTimerRemaining144=6;
                        callers.placeMarker(storage,&actor,1,loading,services);
                        require(actor.radarRegistered37b==1&&
                                findRadarMarker((*storage.markerBucketsOwner())[radarMarkerBucket(expected.x,expected.y)],&actor,expected.x,expected.y)==-1,
                                "Actual placement must remove the old GI marker before registering the moved point");
                        permit=0;callers.placeMarker(storage,&actor,1,loading,services);
                        require(actor.radarRegistered37b==0,"Refused actual placement must remove registered GI marker");
                        for(const auto& bucket:*storage.markerBucketsOwner())for(int j=0;j<bucket.count;++j)
                            require(bucket.entries[std::size_t(j)].actor!=&actor,"Placement refusal must retire every active GI identity");
                        actor.ground.position=sourcePoint;
                        if(argc==4){
                            const auto building=markerWarm->missionWorld().structureResident(1019675).identity;
                            auto& fields=markerWarm->missionWorld().structureSight(1019675).fields;
                            fields.radarX1a0=4;fields.radarY1a4=3;fields.radarTimerRemaining144=0;
                            permit=1;const auto projectionCount=projections;
                            callers.placeMarker(storage,building,0,loading,services);
                            require(projections==projectionCount&&fields.radarRegistered37b==1&&fields.radarX1a0==4&&fields.radarY1a4==3,
                                    "Actual Building argument0 must retain existing point and register actual footprint without projection");
                            permit=0;callers.placeMarker(storage,building,256,loading,services);
                            require(projections==projectionCount&&fields.radarRegistered37b==0,
                                    "Building argument256 low byte must retain point while refusal removes the footprint");
                        }
                        bool refused=false;try{callers.placeMarker(storage,&world.actor(gi),0,loading,services);}
                        catch(const std::invalid_argument&){refused=true;}require(refused,"Placement must refuse a foreign actor before field mutation");
                    });
                    require(snapshot(world)==before,"Complete explicit placement must preserve source world");
                    operate(*markerWarm,[&](const auto&,auto& callers,const auto& draw){
                        auto& actor=BootCampWalkWorldInspection::actorMutable(*markerWarm,gi);
                        auto& type=BootCampWalkWorldInspection::walkType(*markerWarm);
                        auto& position=BootCampWalkWorldInspection::positionMutable(*markerWarm,gi);
                        auto& player=markerWarm->missionWorld().house(playerHouse);
                        auto& other=markerWarm->missionWorld().house(enemyHouse);
                        player.human134=1;player.control135=0;player.indexAlliance.countryIndex=0;player.indexAlliance.allianceMask=0;
                        other.human134=0;other.control135=0;other.indexAlliance.countryIndex=1;other.indexAlliance.allianceMask=0;
                        actor.object.mission.owner=playerHouse;actor.object.mission.current373=1;actor.radar325=0;
                        actor.radarTimerRemaining144=0;actor.object.flags14=1;
                        type.radarAA6=type.radarAA7=type.radarVeteran277=type.radarElite289=0;
                        const std::uint32_t session=0;int status=0x12345;
                        require(callers.markerPermission(&actor,status,session)&&status==0x12345,
                                "Actual local GI permission must preserve the supplied status word and need no unentered children");
                        // The actual local player branch must not pull in nonlocal
                        // height/Cell7C/visibility dependencies even in mode2/elite.
                        RadarPermissionServices unentered;
                        unentered.height1B0=[]() -> std::int32_t {throw std::logic_error("Local permission queried height");};
                        unentered.eligible2FC=[]() -> std::uint32_t {throw std::logic_error("Local permission queried Cell7C");};
                        actor.veterancy118=2.;position.mode1b8=2;
                        require(callers.markerPermission(&actor,status,session,unentered)&&status==0x12345,
                                "Actual local GI permission must bypass height/2FC and preserve status even in mode2/elite");
                        actor.veterancy118=0.;position.mode1b8=0;
                        actor.radar325=255;type.radarAA7=255;
                        require(!callers.markerPermission(&actor,status,session),"Actual325 must precede typeAA7 bypass");
                        actor.radar325=0;actor.object.mission.current373=0;
                        require(callers.markerPermission(&actor,status,session),"ActualAA7 must bypass local discovery gating");
                        type.radarAA7=0;require(!callers.markerPermission(&actor,status,session),"Actual local undiscovered GI must refuse");
                        type.radarAA6=255;actor.radar325=128;
                        auto flagsClone=markerWarm->clone();
                        require(BootCampWalkWorldInspection::walkType(*flagsClone).radarAA6==255&&flagsClone->actor(gi).radar325==128,
                                "Warm actual clones must retain type/actor permission fields");
                        type.radarAA6=0;actor.radar325=0;actor.object.mission.current373=1;
                        const int loading=0,originX=map.width-1,originY=minimum;
                        const auto projection=RadarMarkerProjectionFields{storage.scaleOwner(),originX,originY,storage.first()->width,storage.first()->height};
                        RadarActorPlacementServices placement;RadarPermissionServices children;
                        placement.project631BA0=[&](auto p,auto clamp){RadarShapePoint out{},input{p.x,p.y};projectRadarMarker(out,input,clamp,projection);return out;};
                        placement.rectangle78=[&]{RefreshRect out{};return *storage.first()->table->rect78(*storage.first(),out);};
                        std::vector<std::pair<int,std::uint32_t>> visibilityRequests;
                        placement.radarEvent63B5B0=[&](auto mode,auto packed){visibilityRequests.emplace_back(mode,packed);};
                        callers.placeMarkerWithPermission(storage,&actor,1,loading,session,children,placement);
                        require(actor.radarRegistered37b==1&&visibilityRequests.empty(),"Actual local permission must register without inventing status effects");
                        draw();require(storage.getDisplayPixel(actor.radarX1a0,actor.radarY1a4)==0x1234,
                                "Recovered actual local permission must compose through complete placement into drawing");
                        actor.radar325=255;callers.placeMarkerWithPermission(storage,&actor,1,loading,session,children,placement);
                        require(actor.radarRegistered37b==0,"Actual325 refusal must remove the parent-generated marker");
                        actor.radar325=0;actor.object.mission.owner=enemyHouse;actor.object.mission.current373=1;
                        actor.veterancy118=0;position.mode1b8=0;
                        std::uint32_t eligible=1;int heightCalls=0,eligibleCalls=0;std::vector<int> statuses;
                        children.height1B0=[&]{++heightCalls;return -21;};
                        children.eligible2FC=[&]{++eligibleCalls;return eligible;};
                        children.statusStore=[&](auto value){statuses.push_back(value);};
                        status=0;require(callers.markerPermission(&actor,status,session,children)&&status==2&&heightCalls==1&&eligibleCalls==1,
                                "Actual nonlocal GI must produce recovered status2 through explicit height/2FC boundaries");
                        callers.placeMarkerWithPermission(storage,&actor,1,loading,session,children,placement);
                        const auto point=actor.ground.position;
                        const auto packed=std::uint32_t(std::uint16_t(point.x/256))|(std::uint32_t(std::uint16_t(point.y/256))<<16);
                        require(actor.radarRegistered37b==1&&visibilityRequests.size()==1&&visibilityRequests[0]==std::pair<int,std::uint32_t>{5,packed},
                                "Actual recovered GI status must reach the complete parent's supplied visibility-effect boundary");
                        eligible=256;callers.placeMarkerWithPermission(storage,&actor,1,loading,session,children,placement);
                        require(actor.radarRegistered37b==0&&visibilityRequests.size()==1,
                                "2FC low-byte refusal must remove the marker without a new visibility-effect request");
                        if(argc==4){
                            auto building=markerWarm->missionWorld().structureSight(1019675);
                            building.discovery.owner=enemyHouse;building.discovery.current373=1;
                            building.fields.radarMode1b8=2;building.fields.radar5b7=0;building.fields.radar5bd=0;
                            building.fields.radarX1a0=4;building.fields.radarY1a4=3;building.fields.radarTimerRemaining144=0;
                            auto& t=const_cast<BootCampBuildingExpirationType&>(markerWarm->missionWorld().structureSightType(1019675));
                            t.radarAA6=t.radarAA7=0;eligible=1;const auto oldHeightCalls=heightCalls;
                            status=0;require(callers.markerPermission(building.identity,status,session,children)&&status==1&&heightCalls==oldHeightCalls,
                                    "Actual Building must produce status1 from its own dimensions/mode/flags without Infantry height");
                            callers.placeMarkerWithPermission(storage,building.identity,0,loading,session,children,placement);
                            require(building.fields.radarRegistered37b==1&&visibilityRequests.size()==2,
                                    "Actual Building permission must register its shared footprint and forward status effects");
                            eligible=0;callers.placeMarkerWithPermission(storage,building.identity,0,loading,session,children,placement);
                            require(building.fields.radarRegistered37b==0,"Actual Building2FC refusal must retire its footprint");
                        }
                        actor.object.mission.owner=playerHouse;
                        bool refused=false;try{callers.markerPermission(&world.actor(gi),status,session,children);}
                        catch(const std::invalid_argument&){refused=true;}require(refused,"Permission must refuse foreign actor identities");
                    });
                    require(snapshot(world)==before,"Actual recovered permission/placement must preserve source world");
                    std::cout<<"Actual Infantry/Building2F8: local/type/discovery gates, status2/1 -> complete placement/drawing/retirement PASS (height/2FC and visibility effects supplied; unscheduled)\n";
                    std::cout<<"Complete actual actor radar placement -> visibility/projection/registration/removal/dirty owners PASS (supplied permission/status/screen policy; unscheduled)\n";
                    std::cout<<"Actual marker callers: GI registration/dirty/removal and shared Building footprint services PASS (supplied type index/startup; footprints require private dimensions)\n";
                    std::cout<<"Actual GI/Building radar markers: owned insertion/removal -> both refresh branches, clamp/bypass, tails and explicit warm rebinding PASS\n";
                }
                current=&world;
                std::cout<<"Actual Boot Camp radar actors: mixed GI/Building, live Owner/alternate/type/alliance/color/scheme/timer, warm source destruction PASS (controlled marker placement/palettes)\n";
            }
            std::cout<<"Production mutable radar refresh storage: device copy/mark/terrain/hidden/dim branches PASS (diagnostic House/map/mark services)\n";
        }
        {
            // Actual GI coordinates and existing storage, with explicit startup
            // geometry and a controlled clear bitmap. This does not populate
            // actor buckets or invoke a discovery/frame scheduling producer.
            int gi=-1;for(const auto& [actorId,a]:world.actors())if(world.player(actorId))gi=actorId;
            require(gi>=0,"Radar coordinate check needs actual player GI");
            const auto& position=world.actor(gi).ground.position;
            const auto offset=map.width-1;
            RadarShapePoint point{},input{position.x,position.y};
            projectRadarMarker(point,input,0,{storage.scaleOwner(),offset,minimum,storage.first()->width,storage.first()->height});
            require(point.x>=0&&point.y>=0&&point.x<storage.first()->width&&point.y<storage.first()->height,
                    "Actual Day1 GI projection must fall on the owned radar surface");
            const auto originalDisplay=std::vector<std::uint8_t>(storage.displayPixels().begin(),storage.displayPixels().end());
            std::fill(storage.markBitmap().bytes.begin(),storage.markBitmap().bytes.end(),0);
            const auto priorCount=storage.dirtyPoints().size();
            storage.queueDirtyPoint(point);storage.queueDirtyPoint(point);
            require(storage.dirtyPoints().size()==priorCount+1&&storage.dirtyPoints()[priorCount].x==point.x&&
                    storage.dirtyPoints()[priorCount].y==point.y&&storage.dirtyFlag()==1,
                    "Actual radar storage must retain one queue entry for a duplicate GI point");
            const auto bit=std::size_t(point.y*storage.first()->width+point.x);
            require((storage.bitmap()[bit/8]&(1u<<(bit&7)))!=0,
                    "Dirty producer and refresh must borrow the same bitmap bytes");
            for(int x=0;x<12;++x)storage.queueDirtyPoint({x,0});
            require(storage.dirtyPoints().size()==priorCount+13&&storage.dirtyPoints()[priorCount].x==point.x&&
                    storage.dirtyPoints()[priorCount+12].x==11&&storage.dirtyPoints()[priorCount+12].y==0,
                    "Actual dirty queue growth must retain its GI entry and ordered later points");
            storage.queueDirtyPoint({-1,0});storage.queueDirtyPoint({storage.first()->width,0});
            require(storage.dirtyPoints().size()==priorCount+13&&snapshot(world)==before&&
                    std::equal(originalPixels.begin(),originalPixels.end(),storage.terrainPixels().begin())&&
                    std::equal(originalDisplay.begin(),originalDisplay.end(),storage.displayPixels().begin()),
                    "Explicit dirty requests must preserve mission/Walk/visibility and both pixel owners");
            std::cout<<"Actual GI radar coordinates/dirty queue: shared bitmap, duplicates/growth/refusal/owner isolation PASS (explicit unscheduled producer)\n";
        }
        {
            auto notified=world.clone();int gi=-1;
            for(const auto& [id,a]:notified->actors())if(notified->player(id))gi=id;
            require(gi>=0,"Radar notification requires actual player GI");
            const int originX=map.width-1;const auto pixels=std::vector<std::uint8_t>(storage.displayPixels().begin(),storage.displayPixels().end());
            std::fill(storage.markBitmap().bytes.begin(),storage.markBitmap().bytes.end(),0); // Controlled test setup, not startup recovery.
            const auto prior=storage.dirtyPoints().size();
            auto& visibility=notified->visibilityWorld();CellRedrawView view;
            view.viewportX=-10000000;view.viewportWidth=20000000;view.viewportHeight=20000000;view.originB4=-10000000;
            visibility.withRadarNotifications(storage,originX,minimum,[&]{
                visibility.withCellRedraw(notified->tickOwner(),view,[&]{notified->composeArrivalSight(gi);});
            });
            require(visibility.state().cellNotifications>0&&storage.dirtyPoints().size()>prior&&
                    visibility.redrawQueue().countE0>0,"Actual sight/change/discovery must join both Cell redraw and radar dirty owners");
            for(std::size_t n=prior;n<storage.dirtyPoints().size();++n){const auto p=storage.dirtyPoints()[n];
                const auto bit=std::size_t(p.y*storage.first()->width+p.x);
                require(p.x>=0&&p.y>=0&&p.x<storage.first()->width&&p.y<storage.first()->height&&
                        (storage.bitmap()[bit/8]&(1u<<(bit&7))),"Every notification point must use the actual shared bitmap");
            }
            storage.notifyCell({57,89},notified->map().width,originX,minimum);const auto once=storage.dirtyPoints().size();
            storage.notifyCell({57,89},notified->map().width,originX,minimum);
            require(storage.dirtyPoints().size()==once,"Repeated Cell notifications must reuse bitmap duplicate suppression");
            bool nested=false,cloned=false;
            visibility.withRadarNotifications(storage,originX,minimum,[&]{
                try{visibility.withRadarNotifications(storage,originX,minimum,[]{});}catch(const std::invalid_argument&){nested=true;}
                try{auto invalid=notified->clone();}catch(const std::invalid_argument&){cloned=true;}
            });
            require(nested&&cloned,"Active radar notification scopes must not escape through nesting or clone callbacks");
            bool thrown=false;try{visibility.withRadarNotifications(storage,originX,minimum,[]{throw std::runtime_error("probe");});}
            catch(const std::runtime_error&){thrown=true;}
            require(thrown,"Notification exception probe missing");
            auto warm=notified->clone();notified.reset();
            warm->visibilityWorld().withRadarNotifications(storage,originX,minimum,[&]{warm->composeSight(gi);});
            require(snapshot(world)==before&&std::equal(pixels.begin(),pixels.end(),storage.displayPixels().begin()),
                    "Notification scope cleanup/warm rebinding must preserve source world and not pretend to draw pixels");
            std::cout<<"Actual arrival radar notification: shared Cell -> projection/bitmap/dirty queue, redraw composition, duplicates/scope/warm/source-destruction PASS\n";
        }
        if(argc==4){
            std::vector<std::vector<std::pair<int,int>>> expected;
            for(const auto& bucket:storage.shapeBuckets()){
                require(bucket.count>0&&bucket.count<=bucket.capacity&&std::size_t(bucket.count)<=bucket.items.size()&&bucket.valid==1&&bucket.owns==1,
                        "Actual startup must initialize every private-dimension shape on owned backing");
                expected.emplace_back();for(int i=0;i<bucket.count;++i)expected.back().emplace_back(bucket.items[std::size_t(i)].x,bucket.items[std::size_t(i)].y);
            }
            const auto displayBefore=std::vector<std::uint8_t>(storage.displayPixels().begin(),storage.displayPixels().end());
            storage.initializeShapeBuckets(radarWidths,radarHeights);
            for(unsigned i=0;i<22;++i){const auto& bucket=storage.shapeBuckets()[i];
                require(std::size_t(bucket.count)==expected[i].size(),"Repeated actual shape initialization changed count");
                for(int j=0;j<bucket.count;++j)require(expected[i][std::size_t(j)]==std::pair{bucket.items[std::size_t(j)].x,bucket.items[std::size_t(j)].y},"Repeated actual shape initialization changed ordered points");
            }
            require(snapshot(world)==before&&std::equal(displayBefore.begin(),displayBefore.end(),storage.displayPixels().begin())&&
                    std::equal(originalPixels.begin(),originalPixels.end(),storage.terrainPixels().begin())&&
                    std::equal(originalRGB.begin(),originalRGB.end(),storage.terrainRGB().begin()),
                    "Actual shape storage must preserve device/terrain and mission/Walk/visibility state");
            std::cout<<"Production mutable radar shapes: actual startup scale/private dimensions/22 owned vectors/rebuild/world isolation PASS\n";
        }
        std::cout<<"Production mutable radar storage: whole-map Cell edit -> RGB -> pixels -> restore, shared assets/mission/Walk isolation PASS\n";
    }
    require(&world.visibilityWorld().fallback().flags140==&world.map().fallback.input.flags,
            "Fallback visibility flags must borrow the shared fallback Cell");
    {
        BootCampWalkWorld fallback(assets,mission,source,rules,art);
        require(!fallback.map().table.at(0),"Stock Day1 fallback diagnostic requires missing origin");
        const auto initial=fallback.visibilityWorld().state();
        require(fallback.visibilityWorld().visible({0,0,104},false),"Odd-height primary fallback predicate differs");
        const auto after=fallback.visibilityWorld().state();const auto p=fallback.map().fallback.input.position;
        require(after.mapQueries==initial.mapQueries+2&&after.fallbackStores==initial.fallbackStores+2&&
                p.x==0&&p.y==0&&fallback.visibilityWorld().fallback().point==TerrainCellPoint{0,0},
                "Visibility neighbor misses must immediately forward both shared fallback assignments");
    }

    {
        auto sourceWorld=std::make_unique<BootCampWalkWorld>(assets,mission,source,rules,art);
        std::vector<int> infantry;for(const auto& [id,a]:sourceWorld->actors())infantry.push_back(id);
        require(infantry.size()>=2,"Threat binding needs distinct actual GIs");
        const int building=1019675;std::int32_t multiplier=2;
        auto& type=BootCampWalkWorldInspection::threatType(*sourceWorld);type=-37;
        require(sourceWorld->composeActorThreat(infantry[0],multiplier)==-37&&sourceWorld->composeActorThreat(infantry[1],multiplier)==-37,
            "Threat must consume the shared live Infantry type value");
        auto& state=sourceWorld->missionWorld().structureSight(building).fields;state.field564=INT32_MAX;
        require(sourceWorld->composeActorThreat(building,multiplier)==-2,"Building threat must multiply actual owned564 with wrapping");
        multiplier=-1;require(sourceWorld->composeActorThreat(building,multiplier)==-INT32_MAX,"Threat must consume the live supplied rule");
        state.field564=0;
        require(sourceWorld->composeActorThreat(building,multiplier)==sourceWorld->missionWorld().structureSightType(building).threat598,
            "Nonpositive Building564 must consume its actual shared type");
        state.field564=3;const auto before=snapshot(*sourceWorld);auto cloned=sourceWorld->clone();
        require(snapshot(*sourceWorld)==before&&cloned->composeActorThreat(infantry[0],multiplier)==-37&&cloned->composeActorThreat(building,multiplier)==-3,
            "Warm clone must preserve threat fields without source writes");
        BootCampWalkWorldInspection::threatType(*cloned)=19;cloned->missionWorld().structureSight(building).fields.field564=7;
        require(snapshot(*sourceWorld)==before&&sourceWorld->composeActorThreat(infantry[0],multiplier)==-37,
            "Cloned threat fields must remain independent");
        sourceWorld.reset();require(cloned->composeActorThreat(infantry[0],multiplier)==19&&cloned->composeActorThreat(building,multiplier)==-7,
            "Threat bindings must survive source destruction");
        std::cout<<"Owned actor threat: shared GI type, actual Building564/type, wrap, clone/source destruction PASS\n";
    }

    {
        auto live=std::make_unique<BootCampWalkWorld>(assets,mission,source,rules,art);
        const int self=live->missionWorld().currentHouse();int other=-1;
        for(const auto& [id,h]:live->missionWorld().houses())if(id!=self){other=id;break;}
        require(other>=0,"Grid checks need distinct actual House owners");
        const int gi=live->actors().begin()->first,building=1019675;
        for(const auto& [id,a]:live->actors())BootCampWalkWorldInspection::actorMutable(*live,id).flag76=1;
        for(int id:{1019675,1019676})live->missionWorld().structureSight(id).fields.flag76=1;
        auto& a=BootCampWalkWorldInspection::actorMutable(*live,gi);a.flag76=0;a.onMap7d=1;a.object.mission.owner=other;
        auto& point=BootCampWalkWorldInspection::positionMutable(*live,gi);point.footprintX454=128;point.footprintY456=128;
        BootCampWalkWorldInspection::threatType(*live)=19;
        auto& house=live->missionWorld().house(self);house.human134=0;house.control135=0;house.indexAlliance.allianceMask=0;
        auto& state=live->missionWorld().houseThreat(self);const auto unrelated=live->missionWorld().houseThreat(other).grid;
        std::int32_t rule=2;const TerrainCellPoint invalid{-32768,-32768};
        const auto rebuild=[&](BootCampWalkWorld& w){w.composeHouseThreatGrid(self,threatTables,rule,invalid);};
        const auto positive=[](const auto& grid){return std::any_of(grid.begin(),grid.end(),[](auto n){return n>0;});};
        rebuild(*live);const auto stored=state.grid;
        require(positive(stored)&&live->missionWorld().houseThreat(other).grid==unrelated,"Grid must write only the selected actual House");
        a.ground.position.x+=256;rebuild(*live);require(state.grid==stored,"GI grid must use actual454, not copied current coordinates");
        point.footprintX454+=16;rebuild(*live);require(state.grid!=stored,"Grid must borrow live stored Cell words");
        a.object.mission.owner=self;rebuild(*live);require(!positive(state.grid),"Late exact Owner identity must exclude GI");
        a.object.mission.owner=other;house.human134=1;house.indexAlliance.allianceMask=1u<<unsigned(live->missionWorld().house(other).indexAlliance.countryIndex);
        rebuild(*live);require(!positive(state.grid),"Grid filter must borrow the shared House mask");
        house.indexAlliance.allianceMask=0;rebuild(*live);require(positive(state.grid),"Changed shared alliance mask must reach the grid");
        a.flag76=1;auto structure=live->missionWorld().structureSight(building);structure.fields.flag76=0;structure.fields.onMap7d=1;structure.fields.field564=11;
        structure.discovery.owner=self;rebuild(*live);require(positive(state.grid),"Building map branch must bypass exact Owner exclusion");
        const auto buildingGrid=state.grid;structure.position.z+=12345;rebuild(*live);require(state.grid==buildingGrid,"Building Cell lookup must ignore forwarded Z");
        structure.fields.onMap7d=0;rebuild(*live);require(!positive(state.grid),"Grid must borrow actual Building7D");
        structure.fields.onMap7d=1;rule=-1;rebuild(*live);require(!positive(state.grid),"Negative wrapped Building threat must not enter map branch");
        rule=2;rebuild(*live);
        state.enemy54F0=37;state.count5504=1;state.scores={{&live->missionWorld().house(other).indexAlliance,17},{nullptr,-3},{&house.indexAlliance,99}};state.slots=state.scores;
        auto& mutableMap=const_cast<MutableUnitMap&>(live->map());mutableMap.fallback.input.position={7,8};
        const auto before=snapshot(*live);auto cloned=live->clone();
        require(snapshot(*live)==before&&cloned->missionWorld().houseThreat(self).grid==state.grid&&cloned->missionWorld().houseThreat(self).grid.data()!=state.grid.data(),"Warm grid clone must preserve values with independent backing");
        auto& clonedState=cloned->missionWorld().houseThreat(self);
        require(clonedState.enemy54F0==37&&clonedState.count5504==1&&clonedState.scores.size()==3&&clonedState.scores[0].house==&cloned->missionWorld().house(other).indexAlliance&&clonedState.scores[1].house==nullptr&&clonedState.scores[2].house==&cloned->missionWorld().house(self).indexAlliance&&clonedState.scores[2].value==99,"Clone must remap every score identity and retain uncounted tails");
        cloned->missionWorld().structureResident(building).position88={-256,-256,321};
        const auto floorBefore=std::string(reinterpret_cast<const char*>(&cloned->map().floor),sizeof(MapFloorHeightState));
        rebuild(*cloned);
        require(snapshot(*live)==before&&cloned->map().fallback.input.position==MapInputPosition{-1,-1}&&positive(clonedState.grid),"Discarded grid rebuild must use only clone map/fallback/House owners");
        require(std::string(reinterpret_cast<const char*>(&cloned->map().floor),sizeof(MapFloorHeightState))==floorBefore,"Coordinate grid lookup must not warm a floor cache");
        const auto invalidBefore=snapshot(*cloned);bool caught=false;
        try{cloned->composeHouseThreatGrid(-999,threatTables,rule,invalid);}catch(const std::exception&){caught=true;}
        require(caught&&snapshot(*cloned)==invalidBefore,"Foreign House must refuse before clearing or querying");
        const auto pointer=clonedState.scores[0].house;int foreign=0;clonedState.scores[0].house=&foreign;
        const auto foreignBefore=snapshot(*cloned);caught=false;try{auto refusedClone=cloned->clone();}catch(const std::invalid_argument&){caught=true;}
        require(caught&&snapshot(*cloned)==foreignBefore,"Foreign score identity must refuse clone without source changes");
        clonedState.scores[0].house=pointer;live.reset();rebuild(*cloned);
        require(positive(clonedState.grid)&&clonedState.scores[0].house==&cloned->missionWorld().house(other).indexAlliance,"Grid and score owners must survive source destruction");
        std::cout<<"Owned House grid: live actor/House/map fields, score tails, warm isolation/source destruction PASS ("<<(privateThreat?"private original stencil":"authored ownership stencil")<<")\n";
    }

    {
        auto trial=std::make_unique<BootCampWalkWorld>(assets,mission,source,rules,art);
        const int current=trial->visibilityWorld().currentHouse();int other=-1;
        for(const auto& [id,h]:trial->missionWorld().houses())if(id!=current){other=id;break;}
        require(other>=0,"Sight House test needs a distinct owned House");
        auto& h=BootCampWalkWorldInspection::sightHouse(*trial,other);
        h.allianceMask=0;h.countryIndex=other;
        // Negative radius would refuse after House selection if ownership were
        // validated too late. Foreign pointers must refuse before any work.
        RevealAreaHouse foreign{current,current,~0u};
        const auto refusal=snapshot(*trial);
        for(const void* p:{static_cast<const void*>(nullptr),static_cast<const void*>(&foreign)}){
            bool caught=false;try{trial->visibilityWorld().revealSight({{57*256,89*256,0},-1,p});}
            catch(const std::invalid_argument& e){caught=std::string(e.what()).find("owned House")!=std::string::npos;}
            require(caught&&snapshot(*trial)==refusal,"Foreign/null sight House must refuse without warming owners");
        }
        const auto before=trial->visibilityWorld().state();
        const auto counter=trial->visibilityWorld().at({57,89}).counter130;
        trial->visibilityWorld().revealSight({{57*256,89*256,0},1,trial->visibilityWorld().house(other)});
        const auto noAlliance=trial->visibilityWorld().state();
        require(noAlliance.revealAreas==before.revealAreas+1&&noAlliance.sightAdds==before.sightAdds+1&&
                noAlliance.mapQueries==before.mapQueries&&noAlliance.reveals==before.reveals&&
                trial->visibilityWorld().at({57,89}).counter130==counter,
                "Owned nonallied sight must return before Cell queries/effects");
        // Equal country indices pass actual4E5540 even with a zero mask; the
        // reveal parent still requires rules142B on this predicate branch.
        h.countryIndex=BootCampWalkWorldInspection::sightHouse(*trial,current).countryIndex;
        BootCampWalkWorldInspection::allyReveal(*trial)=0;
        trial->visibilityWorld().revealSight({{57*256,89*256,0},1,trial->visibilityWorld().house(other)});
        require(trial->visibilityWorld().state().reveals==before.reveals,
                "Equal-country sight must retain the late rules142B gate");
        BootCampWalkWorldInspection::allyReveal(*trial)=1;
        trial->visibilityWorld().revealSight({{57*256,89*256,0},1,trial->visibilityWorld().house(other)});
        require(trial->visibilityWorld().at({57,89}).counter130==counter-1,
                "Equal-country predicate sight must resolve to the actual current House");
        h.countryIndex=other;h.allianceMask=1u<<unsigned(current&31);
        BootCampWalkWorldInspection::allyReveal(*trial)=0;
        const auto warm=snapshot(*trial);auto fork=trial->clone();
        require(fork->visibilityWorld().house(other)!=trial->visibilityWorld().house(other),
                "Warm clone must own a distinct sight House");
        const auto forkBefore=snapshot(*fork);
        bool caught=false;try{fork->visibilityWorld().revealSight({{57*256,89*256,0},1,trial->visibilityWorld().house(other)});}
        catch(const std::invalid_argument&){caught=true;}
        require(caught&&snapshot(*trial)==warm&&snapshot(*fork)==forkBefore,
                "Cross-world sight House must refuse without source or destination mutation");
        fork->visibilityWorld().revealSight({{57*256,89*256,0},1,fork->visibilityWorld().house(other)});
        require(fork->visibilityWorld().at({57,89}).counter130==counter-2&&snapshot(*trial)==warm&&snapshot(*fork)!=forkBefore,
                "Mask alliance must bypass rules142B using only cloned visibility owners");
        const auto* stale=trial->visibilityWorld().house(other);trial.reset();
        const auto afterDestroy=snapshot(*fork);
        caught=false;try{fork->visibilityWorld().revealSight({{57*256,89*256,0},1,stale});}
        catch(const std::invalid_argument&){caught=true;}
        require(caught&&snapshot(*fork)==afterDestroy,"Destroyed-source House must refuse without dereference or mutation");
        fork->visibilityWorld().revealSight({{57*256,89*256,0},1,fork->visibilityWorld().house(other),0,0,0,1,1});
        require(fork->visibilityWorld().at({57,89}).counter130==counter-1,
                "Cloned allied sight removal must continue after source destruction");
        std::cout<<"Owned sight Houses: mask/predicate/rules/nonallied/foreign/warm clone/source destruction PASS\n";
    }

    {
        auto trial=std::make_unique<BootCampWalkWorld>(assets,mission,source,rules,art);int player=-1,other=-1;
        for(const auto& [id,a]:trial->actors())if(trial->player(id))player=id;
        require(player>=0,"Shared House check needs the actual player");
        const int playerHouse=trial->actor(player).object.mission.owner;
        for(const auto& [id,a]:trial->actors())if(a.object.mission.owner!=playerHouse){other=a.object.mission.owner;break;}
        require(other>=0,"Shared House check needs another actual actor Owner");
        BootCampWalkWorldInspection::checkWalkHouseAliases(*trial);
        for(const auto& [id,h]:trial->missionWorld().houses()){
            const auto movement=BootCampWalkWorldInspection::movementHouse(*trial,id);
            require(&movement.index==&h.indexAlliance.countryIndex&&&movement.allies==&h.indexAlliance.allianceMask&&
                    trial->visibilityWorld().house(id)==&h.indexAlliance,
                    "Movement and sight must borrow one index/alliance owner beside discovery flags");
        }
        auto& h=trial->missionWorld().house(other);h.indexAlliance.countryIndex=other;h.indexAlliance.allianceMask=0;
        require(!BootCampWalkWorldInspection::movementAllied(*trial,other,player),"Zero shared mask must not admit a distinct Owner");
        const auto before=trial->visibilityWorld().state();
        trial->visibilityWorld().revealSight({{57*256,89*256,0},1,&h.indexAlliance});
        require(trial->visibilityWorld().state().mapQueries==before.mapQueries,"Nonallied shared House must not query sight Cells");
        h.indexAlliance.allianceMask=1u<<unsigned(playerHouse&31);
        require(BootCampWalkWorldInspection::movementAllied(*trial,other,player),"Shared mask mutation must reach actual movement alliance");
        trial->visibilityWorld().revealSight({{57*256,89*256,0},1,&h.indexAlliance});
        require(trial->visibilityWorld().state().reveals>before.reveals,"The same mask store must reach actual sight Cells");
        h.indexAlliance.countryIndex=trial->missionWorld().house(playerHouse).indexAlliance.countryIndex;
        h.indexAlliance.allianceMask=0;
        require(BootCampWalkWorldInspection::movementAllied(*trial,other,player),"Shared equal index must reach movement without a mask");
        h.control135=1;const auto warm=snapshot(*trial);auto fork=trial->clone();
        BootCampWalkWorldInspection::checkWalkHouseAliases(*fork);
        auto& cloned=fork->missionWorld().house(other);const auto fields=BootCampWalkWorldInspection::movementHouse(*fork,other);
        require(&cloned!=&h&&&fields.index==&cloned.indexAlliance.countryIndex&&
                &fields.allies==&cloned.indexAlliance.allianceMask&&fork->visibilityWorld().house(other)==&cloned.indexAlliance&&
                cloned.indexAlliance.countryIndex==h.indexAlliance.countryIndex&&cloned.indexAlliance.allianceMask==h.indexAlliance.allianceMask&&
                cloned.control135==h.control135,"Warm clone must retain values and rebind every House consumer");
        cloned.indexAlliance.countryIndex=other;cloned.indexAlliance.allianceMask=0;cloned.control135=0;
        require(!BootCampWalkWorldInspection::movementAllied(*fork,other,player)&&snapshot(*trial)==warm,
                "Cloned House mutation must reach its movement consumer without source writes");
        trial.reset();cloned.indexAlliance.allianceMask=1u<<unsigned(playerHouse&31);
        require(BootCampWalkWorldInspection::movementAllied(*fork,other,player),"Borrowed House fields must survive source destruction");
        fork->visibilityWorld().revealSight({{57*256,89*256,0},1,&cloned.indexAlliance});
        std::cout<<"Shared House owners: exact index/mask/flags aliases, live movement/sight changes, warm clone/source destruction PASS\n";
    }

    {
        auto trial=std::make_unique<BootCampWalkWorld>(assets,mission,source,rules,art);int player=-1;
        for(const auto& [id,a]:trial->actors()){
            if(trial->player(id))player=id;
            else BootCampWalkWorldInspection::actorMutable(*trial,id).flag76=1;
        }
        require(player>=0&&BootCampWalkWorldInspection::sightRegistry(*trial).size()==7,
                "Mixed sight registry must contain five actual GIs and two actual Buildings");
        const int current=trial->visibilityWorld().currentHouse();
        BootCampWalkWorldInspection::actorMutable(*trial,player).object.mission.current373=1;
        for(int key:{1019675,1019676}){
            auto a=trial->missionWorld().structureSight(key);
            require(a.identity==trial->missionWorld().structureResident(key).identity&&
                    &a.position==&trial->missionWorld().structureResident(key).position88&&
                    &a.discovery==&trial->missionWorld().inspectStructureExpiration(key).actor,
                    "Map sight must borrow the actual Building coordinate/discovery owner");
            a.discovery.owner=current;a.discovery.current373=1;
        }
        const auto before=trial->visibilityWorld().state();
        trial->composeHouseMapSight(true);
        require(BootCampWalkWorldInspection::actorSight(*trial,player).active1e4==1&&
                trial->missionWorld().structureSightState(1019675).sight.active1e4==1&&
                trial->missionWorld().structureSightState(1019676).sight.active1e4==1&&
                trial->visibilityWorld().state().postSightCalls==before.postSightCalls+3,
                "Mixed addition must update actual GI/Building sight and post-sight on shared Cells");
        const auto warm=snapshot(*trial);auto fork=trial->clone();
        require(snapshot(*trial)==warm,"Mixed warm clone must not mutate source owners");
        const auto& liveRegistry=BootCampWalkWorldInspection::sightRegistry(*trial);
        const auto& clonedRegistry=BootCampWalkWorldInspection::sightRegistry(*fork);
        require(liveRegistry.size()==clonedRegistry.size(),"Mixed registry clone size differs");
        for(std::size_t i=0;i<liveRegistry.size();++i)require(liveRegistry[i]!=clonedRegistry[i],
                "Every mixed registry actor must remap to its distinct cloned owner");
        fork->composeHouseMapSight(false,1);
        require(BootCampWalkWorldInspection::actorSight(*fork,player).active1e4==0&&
                fork->missionWorld().structureSightState(1019675).sight.active1e4==1&&snapshot(*trial)==warm,
                "Skip-Building removal must leave both Building and source sight owners unchanged");
        fork->composeHouseMapSight(false);
        require(fork->missionWorld().structureSightState(1019675).sight.active1e4==0&&
                fork->missionWorld().structureSightState(1019676).sight.active1e4==0&&
                fork->visibilityWorld().state().postSightCalls==before.postSightCalls+3,
                "Complete removal must not schedule post-sight");
        trial.reset();fork->composeHouseMapSight(true);
        require(fork->missionWorld().structureSightState(1019675).sight.active1e4==1,
                "Mixed sight must continue after source destruction");
        // The actual type is shared with expiration. A supplied forced-sight
        // byte selects explicit current House; an image effect stays refused.
        auto building=fork->missionWorld().structureSight(1019675);
        auto& t=const_cast<BootCampBuildingExpirationType&>(fork->missionWorld().structureSightType(1019675));
        building.discovery.owner=current==0?6:0;
        fork->missionWorld().house(building.discovery.owner).human134=0;
        fork->missionWorld().house(building.discovery.owner).control135=0;
        BootCampWalkWorldInspection::allyReveal(*fork)=0;t.flag534=1;
        const auto forcedBefore=fork->visibilityWorld().state();fork->composeHouseMapSight(true,0,-2147483647-1);
        require(fork->visibilityWorld().state().sightAdds>forcedBefore.sightAdds&&
                fork->visibilityWorld().state().postSightCalls>forcedBefore.postSightCalls,
                "Forced Building sight must reach actual current-House visibility");
        const auto source=snapshot(*fork);auto refused=fork->clone();
        BootCampWalkWorldInspection::sightTypeADD(*refused)=1;bool caught=false;
        try{refused->composeHouseMapSight(false);}catch(const std::invalid_argument& e){caught=std::string(e.what()).find("image effect")!=std::string::npos;}
        require(caught&&snapshot(*fork)==source,"Entered image effect must refuse on clone without source mutation");
        auto inactive=fork->clone();
        inactive->missionWorld().structureSight(1019675).fields.flag76=1;
        auto expiration=inactive->missionWorld().inspectStructureExpiration(1019675);
        int foreignType=0;expiration.fields.type418=&foreignType;
        inactive->composeHouseMapSight(false);
        caught=false;try{(void)inactive->missionWorld().structureSightType(1019675);}
        catch(const std::invalid_argument&){caught=true;}
        require(caught&&snapshot(*fork)==source,"Flag76 skip must not eagerly resolve a Building type");
        auto& registry=BootCampWalkWorldInspection::sightRegistry(*fork);
        const auto* first=registry[0];registry[0]=nullptr;auto nullable=fork->clone();
        require(!BootCampWalkWorldInspection::sightRegistry(*nullable)[0],"Null registry slots must retain their position on clone");
        registry[0]=first;
        int foreign=0;BootCampWalkWorldInspection::sightRegistry(*fork)[0]=&foreign;caught=false;
        try{(void)fork->clone();}catch(const std::invalid_argument&){caught=true;}
        require(caught,"Foreign registry actor must refuse cloning");
        std::cout<<"Mixed House sight: actual GI/Building owners, skip/removal/forced addition, warm clones/refusal/source destruction PASS\n";
    }

    {
        auto missing=mission;missing.triggers.at("043b011c").actions[5].arguments[0]="missing-target";int frame=0;
        BootCampMissionWorld trial(missing,source,rules,frame,strings,colors,makeBootCampMessages(assets));bindInspectionReveal(trial);
        bool refusedTarget=false;try{(void)trial.discoverStructure(1019675);}
        catch(const std::invalid_argument& e){refusedTarget=std::string(e.what()).find("not owned")!=std::string::npos;}
        require(refusedTarget,"Missing Trigger control target must not become no-op success");
        const auto failed=trial.state();bool refusedClone=false;
        try{(void)trial.clone(frame);}catch(const std::invalid_argument& e){
            refusedClone=std::string(e.what()).find("in-progress")!=std::string::npos;
        }
        require(refusedClone&&sameMissionState(trial.state(),failed),
                "Interrupted Tag dispatch must refuse cloning without mutating the source");
    }
    {
        BootCampWalkWorld trial(assets,mission,source,rules,art);const auto initialMission=trial.missionWorld().state();
        require(initialMission.tagInstances==2&&initialMission.taggedStructures==2&&initialMission.deferred==0,
                "First objective mission owners differ");
        require(initialMission.registryCounts==std::array<std::int32_t,4>{5,6,6,1},"First objective shared registries differ");
        require(initialMission.controlledEnabled==std::array<std::uint8_t,4>{0,0,0,0},"Controlled Triggers must begin disabled");
        std::map<int,const UnitDiscoveryHouse*> houseOwners;
        for(const auto& [id,h]:trial.missionWorld().houses())houseOwners[id]=&h;
        auto building=trial.missionWorld().structureResident(1019675);
        const auto originalBuilding=trial.missionWorld().structureResidentState(1019675);
        require(trial.residentHead({71,92})==1019675&&trial.composeKind6ResidentSearch(building.position88).resident==building.identity,
                "Kind6 search must return the same actual Building owner from the movement head");
        require(trial.composeClosestResident(building.position88)==1019675,
                "Visibility must traverse the actual movement head");
        building.flags14=0;require(trial.composeClosestResident(building.position88)==-1,
                "Visibility must read actual Building flag14");building.flags14=originalBuilding.flags14;
        require(trial.missionWorld().structureResidentState(1019675)==originalBuilding,
                "Read-only resident searches must preserve the Building owner");
        const int giId=trial.actors().begin()->first;const auto& gi=trial.actor(giId);
        require(trial.residentHead({std::int16_t(gi.ground.position.x/256),std::int16_t(gi.ground.position.y/256)})==giId&&
                trial.composeClosestResident(gi.ground.position)==giId,
                "Visibility must read the actual GI membership list");
        const auto visibilityInitial=trial.visibilityWorld().state();
        require(visibilityInitial.residentCount==trial.actors().size()+2&&visibilityInitial.reveals==0&&visibilityInitial.mapQueries==0&&
                visibilityInitial.currentHouse==trial.visibilityWorld().currentHouse(),
                "Actual objective structure visibility membership differs");
        bool refusedVisibilityHouse=false;
        try{(void)trial.visibilityWorld().reveal({70,91},trial.visibilityWorld().currentHouse()+1);}
        catch(const std::invalid_argument&){refusedVisibilityHouse=true;}
        const auto visibilityAfterRefusal=trial.visibilityWorld().state();
        require(refusedVisibilityHouse&&visibilityAfterRefusal.reveals==visibilityInitial.reveals&&
                visibilityAfterRefusal.maskCalls==visibilityInitial.maskCalls&&
                visibilityAfterRefusal.mapQueries==visibilityInitial.mapQueries&&
                visibilityAfterRefusal.discoveredResidents==visibilityInitial.discoveredResidents,
                "Unsupported visibility House must refuse before shared state changes");
        require(trial.visibilityWorld().reveal({70,91},trial.visibilityWorld().currentHouse()),
                "Ordinary Cell visibility composition must discover the actual objective structure");
        const auto& sharedVisibility=trial.visibilityWorld().at({70,91});
        require(&sharedVisibility.flags140==&trial.map().table.at(91*512+70)->flags,
                "Sight and movement must share the actual Cell140 word");
        const auto terrainBefore=trial.map().table.at(91*512+70)->flags;
        CellVisibilityState snapshotCell=sharedVisibility;snapshotCell.flags140^=0x80000000u;
        require(&snapshotCell.flags140!=&sharedVisibility.flags140&&trial.map().table.at(91*512+70)->flags==terrainBefore,
                "A copied visibility snapshot must not retain its source flag binding");
        require(!trial.visibilityWorld().visible({70*256+128,91*256+128,0},false)&&
                !trial.visibilityWorld().visible({70*256+128,91*256+128,0},true),
                "Primary/secondary predicates must read revealed shared Cell flags");
        for(const auto& [id,identity]:houseOwners)require(&trial.missionWorld().house(id)==identity,
                "Structure discovery must preserve House addresses borrowed by movement and actions");
        int suppliedBuildingType=-1,buildingOwner=-1;
        for(const auto& [index,name]:rules.section("BuildingTypes"))if(lower(name)=="caarmy04")suppliedBuildingType=std::stoi(index);
        for(const auto& actor:mission.actors)if(actor.key==1019675)
            for(const auto& [id,name]:mission.houses)if(lower(name)==lower(actor.house))buildingOwner=id;
        const auto& buildingHouse=trial.missionWorld().house(buildingOwner);
        require(suppliedBuildingType>=0&&buildingHouse.buildingType1b4==suppliedBuildingType&&
                buildingHouse.building18d==1&&buildingHouse.building144==1,
                "Building override must write the same stable House owner after common discovery");
        const auto visibility=trial.visibilityWorld().state();const auto& visibleCell=trial.visibilityWorld().at({70,91});
        std::cout<<"Shared reveal state: roots="<<visibility.waypointReveals<<" areas="<<visibility.revealAreas<<" Cells="<<visibility.reveals<<" masks="<<visibility.maskCalls<<" redraws="<<visibility.redraws<<" discovery="<<visibility.discoveryParents<<" residents="<<visibility.discoveredResidents<<" last="<<visibility.lastResident<<" fallback="<<visibility.fallbackStores<<" primary="<<int(visibleCell.primary120)<<" secondary="<<int(visibleCell.secondary121)<<" counter="<<visibleCell.counter130<<" flags12c="<<visibleCell.flags12c<<" flags140="<<visibleCell.flags140<<'\n';
        require(visibility.waypointReveals==1&&visibility.waypointAreaCalls==2&&visibility.revealAreas==2&&
                visibility.reveals==507&&visibility.maskCalls==1014&&visibility.redraws==483&&visibility.discoveryParents==483&&
                visibility.discoveredResidents==6&&visibility.lastResident==1019675&&visibility.fallbackStores==0&&
                visibleCell.primary120==255&&visibleCell.secondary121==255&&visibleCell.counter130==-1&&
                (visibleCell.flags12c&0xffu)==0x18u&&(visibleCell.flags140&0xffu)==3u,
                "Shared mask/change/discovery state differs");
        const auto queued=trial.missionWorld().state();
        require(queued.textRequests==1&&queued.textPayload==strings->text("MISSION:Objective1")&&queued.textKey=="MISSION:Objective1"&&queued.textColorSelector==1&&
                queued.textColor==messageColor(1,colors)&&queued.textStyle==0x4046&&queued.textDuration==539,
                "Objective1 text request differs from recovered action11 orchestration");
        require(queued.allyCalls==2&&queued.allyValue==13&&queued.allyFrom==std::array<std::int32_t,2>{6,0}&&
                queued.allyTo==std::array<std::int32_t,2>{0,6}&&queued.allyAnnounce==std::array<std::uint8_t,2>{0,0},
                "Objective1 mutual Make Ally request differs from recovered action37 orchestration");
        require(queued.soundRequests==1&&queued.soundToken=="HealCrate"&&queued.soundIndex==292&&queued.soundPanning==0x2000&&
                queued.soundVolumeBits==0x3f800000u&&!queued.soundController,
                "Objective1 sound request differs from recovered action19 orchestration");
        require(queued.speechRequests==1&&queued.speechToken=="Mis_T1_DrillSearg03"&&queued.speechIndex==247&&
                queued.speechMode==2&&queued.speechParameter==-1,
                "Objective1 speech request differs from recovered action21 orchestration");
        require(queued.createTeamFactoryCalls==1&&queued.createTeamAllocations==1&&queued.createTeamRequests==1&&queued.createTeamId=="0B197B7C"&&queued.createTeamArgument==0&&
                queued.createTeamDepthAtCall==1&&queued.teamCreationDepth==0,
                "Objective1 Create Team request differs from recovered action4 orchestration");
        require(queued.teamConstructed&&queued.teamTypeCount==1&&queued.teamTagChildRequests==1&&queued.teamScriptChildRequests==1&&
                queued.teamRegistryCounts==std::array<std::int32_t,4>{1,3,1,1},
                "Objective1 Team constructor must retain shared owners and supplied child requests");
        require(queued.teamTagConstructed&&queued.teamTriggerConstructed&&queued.teamScriptConstructed&&queued.teamTagTriggerBound&&
                queued.teamTriggerControlBound&&queued.triggerControlCount==6&&queued.teamTriggerEnabled&&queued.teamScriptCount==1&&queued.teamScriptCursor==-1,
                "Objective1 child constructors must produce the actual linked Tag/Trigger and initial Script");
        {
            const auto before=snapshot(trial);int admitted=0,rejected=0;
            for(const auto& [id,actor]:trial.actors()){
                std::int32_t slot=0x12345678;const bool eligible=trial.canAdmitToObjectiveTeam(id,slot);
                if(trial.player(id)){require(!eligible&&slot==0x12345678,"Foreign House admission must preserve output");++rejected;}
                else {require(eligible&&slot==0,"Actual Other2 GI must match the actual Team TaskForce slot");++admitted;}
            }
            require(admitted==4&&rejected==1&&snapshot(trial)==before,
                    "Read-only Team admission must borrow actual GI/Team fields without mutating mission state");
            auto copy=trial.clone();
            for(const auto& [id,actor]:copy->actors()){
                std::int32_t slot=-7;require(copy->canAdmitToObjectiveTeam(id,slot)==!copy->player(id),
                    "Cloned actual Team/House/Type admission must retain independent identities");
            }
        }
        require(queued.revealRequests==1&&queued.revealWaypoint==6&&queued.revealHouse==6&&queued.revealObject==1019675&&
                queued.revealTrigger&&queued.revealPackedCell==0x7fff7fffu&&queued.revealCreateTeamRequestsAtCall==1&&
                queued.revealSoundRequestsAtCall==0,
                "Objective1 Reveal Around Waypoint request differs from recovered action17 orchestration");
        require(queued.triggerDestroyed&&queued.deferred==2&&queued.tagInstances==0&&queued.taggedStructures==0,
                "Discovery must queue destroyed Trigger then detached Tag");
        require(queued.registryCounts==std::array<std::int32_t,4>{6,8,7,2},"Expiration must preserve live controlled Triggers");
        require(queued.controlledEnabled==std::array<std::uint8_t,4>{0,1,0,1},"Objective Trigger controls differ");
        require(queued.controlledTimers[0].start==-1&&queued.controlledTimers[0].remaining==0&&
                queued.controlledTimers[1].start==0&&queued.controlledTimers[1].remaining==1500&&
                queued.controlledTimers[2].start==-1&&queued.controlledTimers[2].remaining==0&&
                queued.controlledTimers[3].start==0&&queued.controlledTimers[3].remaining==570,
                "Enabled Trigger timer resets differ");
        require(queued.controlledPadding==std::array<std::int32_t,4>{0,0,0,0},"Supplied Trigger timer scratch differs");
        {
            const auto unchanged=snapshot(trial);const auto unchangedMission=trial.missionWorld().state();
            auto scheduled=trial.clone();
            for(std::uint32_t tick=0;tick<4;++tick){
                scheduled->tickObjectiveTeamRecruitment();const auto state=scheduled->missionWorld().state();
                require(state.teamMemberCount==tick+1&&state.teamTaskCounts[0]==tick+1&&
                    state.teamFlags[5]==0&&state.teamFlags[4]==0&&state.teamFlags[9]==1&&
                    state.teamScriptCursor==-1,"Original initial Team AI tick must recruit once per underfilled slot and leave refresh pending");
                if(tick==0){
                    auto intermediate=scheduled->clone();auto independent=intermediate->clone();intermediate.reset();
                    independent->tickObjectiveTeamRecruitment();
                    require(independent->missionWorld().state().teamMemberCount==2&&scheduled->missionWorld().state().teamMemberCount==1,
                        "Team AI clone must recruit independently after source destruction");
                }
            }
            for(const auto& [id,a]:scheduled->actors())require(bool(a.team4c4)==!scheduled->player(id),
                "Team AI recruitment must preserve player isolation on actual actors");
            auto child=scheduled->clone();
            require(child->regroupObjectiveTeam(),"Actual existing Team near regroup must complete on shared owners");
            for(const auto& [id,a]:child->actors())if(!child->player(id))require(a.teamLeader579==1&&!a.target494&&a.route[0]==-1&&a.object.mission.queuedA0==5,
                "Actual regroup must promote near members, queue Guard and clear destinations");
            auto activated=scheduled->clone();activated->tickObjectiveTeamRecruitment();
            const auto activeState=activated->missionWorld().state();
            require(activeState.teamFlags[11]==1&&activeState.teamFlags[7]==0&&activeState.teamScriptCursor==-1&&activeState.teamMemberCount==4,
                "Actual fifth tick must activate and finish near regroup through resident admission");
            for(const auto& [id,a]:activated->actors())if(!activated->player(id))require(a.teamLeader579==1&&!a.target494&&a.route[0]==-1&&a.object.mission.queuedA0==5,
                "Activated actual GIs must retain shared members and Guard destinations");
            const auto beforeCommand=snapshot(*scheduled);
            int commandPlayer=-1;for(const auto& [id,a]:scheduled->actors())if(scheduled->player(id))commandPlayer=id;
            require(commandPlayer>=0,"Script ownership fixture needs actual player");
            // A nonnull owned field1B0 exercises the setter, separately from
            // supplied null startup. Clone it through actual member identity.
            for(const auto& [id,a]:activated->actors())if(!activated->player(id)){
                auto& field=const_cast<InfantryWalkState&>(activated->actor(id));field.field1b0=&activated->actor(commandPlayer);field.valueD8=0xdeadbeefu;
            }
            auto command=activated->clone();activated.reset();
            for(const auto& [id,a]:command->actors())if(!command->player(id))require(a.field1b0==&command->actor(commandPlayer),"Script field1B0 must rebind actual cloned identity");
            command->tickObjectiveTeamRecruitment();
            require(command->missionWorld().state().teamScriptCursor==0&&command->missionWorld().state().teamFlags[12]==1,
                "Actual sixth tick must advance and finish original Script50");
            BootCampWalkWorldInspection::houseTransferBoundaryCheck(*command);
            for(const auto& [id,a]:command->actors())require(command->player(id)?a.valueD8==0:(a.valueD8==70&&!a.field1b0&&a.team4c4==command->missionWorld().objectiveTeamIdentity()),
                "Script50 must write raw70 and clear1B0 on actual Team members, preserving player");
            require(snapshot(*scheduled)==beforeCommand,"Executing a clone Script command must preserve recruited source");
            auto survivor=command->clone();command.reset();
            const auto full=snapshot(*survivor);const auto fullMission=survivor->missionWorld().state();bool refused=false;
            try{survivor->tickObjectiveTeamRecruitment();}catch(const std::invalid_argument&){refused=true;}
            require(refused&&snapshot(*survivor)==full&&sameMissionState(survivor->missionWorld().state(),fullMission),
                "Unjoined command20 tick must refuse before mutation after source destruction");
            // Seventh tick remains explicit and uses the existing real radar and
            // transfer owners. The stencil is supplied diagnostic alias data.
            const std::array<std::int32_t,18> transferTables{};
            auto transferred=survivor->clone();
            RadarStorage transferRadar({11,3,0,3,5,2});transferRadar.supplyNotificationMode(2,1);
            {RefreshRect rect{0,0,80,60};const std::int32_t zero=0;
             transferRadar.initialize(rect,zero,zero,[](auto&,auto&,auto bytes){std::fill(bytes.begin(),bytes.end(),0);},[]{});}
            bool badContext=false;try{transferred->tickObjectiveTeamRecruitment(&transferRadar,{});}
            catch(const std::invalid_argument&){badContext=true;}
            require(badContext&&transferred->missionWorld().state().teamScriptCursor==0,
                "Missing transfer inputs must refuse before Script advancement");
            const auto teamIdentity=transferred->missionWorld().objectiveTeamIdentity();
            const auto* teamTag=transferred->missionWorld().objectiveTeamTag();
            const auto teamLinks=transferred->missionWorld().objectiveTeamLinks();
            std::vector<int> changed;int oldHouse=-1;
            for(const auto& [id,a]:transferred->actors())if(a.team4c4==teamIdentity){changed.push_back(id);oldHouse=a.object.mission.owner;}
            require(changed.size()==4,"Script20 needs the four actual recruited members");
            const int playerHouse=transferred->missionWorld().currentHouse();
            const auto oldCounts=transferred->missionWorld().house(oldHouse).infantryAccounting;
            const auto newCounts=transferred->missionWorld().house(playerHouse).infantryAccounting;
            const auto requestCount=transferred->missionWorld().state().createTeamRequests;
            transferred->tickObjectiveTeamRecruitment(&transferRadar,transferTables);
            const auto afterTransfer=transferred->missionWorld().state();
            require(afterTransfer.teamScriptCursor==1&&afterTransfer.teamFlags[12]==1&&afterTransfer.teamMemberCount==4&&
                transferred->missionWorld().objectiveTeamLinks()==teamLinks&&afterTransfer.createTeamRequests==requestCount,
                "Seventh actual tick must complete command20 on the same Team/Script/member chain");
            for(int id:changed){const auto& a=transferred->actor(id);
                require(transferred->player(id)&&a.object.mission.owner==playerHouse&&a.team4c4==teamIdentity&&
                    a.objectTag34==teamTag&&a.valueD8==70&&!a.field1b0&&a.object.mission.queuedA0==5&&a.resume59d==1&&a.accounting324==1,
                    "Command20 must transfer every actual GI, retaining Team/Tag/Script50 and queued Guard");
                BootCampRadarActors::updateMarker(*transferred,transferRadar,&a,RadarActorMarkerOperation::remove);
            }
            for(const auto& bucket:*transferRadar.markerBucketsOwner())require(bucket.count==0,
                "Retire all transfer radar identities before destroying or cloning owners");
            require(transferred->missionWorld().house(oldHouse).infantryAccounting.count234==oldCounts.count234-4u&&
                transferred->missionWorld().house(playerHouse).infantryAccounting.count234==newCounts.count234+4u,
                "Command20 must use actual House accounting for all four GIs");
            BootCampWalkWorldInspection::checkWalkHouseAliases(*transferred);
            require(snapshot(*survivor)==full&&sameMissionState(survivor->missionWorld().state(),fullMission),
                "Explicit Team20 composition must preserve source owners");
            auto afterClone=transferred->clone();transferred.reset();
            BootCampWalkWorldInspection::checkWalkHouseAliases(*afterClone);
            for(int id:changed)require(afterClone->player(id)&&afterClone->actor(id).team4c4==afterClone->missionWorld().objectiveTeamIdentity()&&
                afterClone->actor(id).objectTag34==afterClone->missionWorld().objectiveTeamTag(),
                "Transferred Team/Tag/House identities must survive source destruction");
            BootCampWalkWorldInspection::teamFootExpirationCheck(*afterClone);
            const auto exhausted=snapshot(*afterClone);const auto exhaustedMission=afterClone->missionWorld().state();refused=false;
            try{afterClone->tickObjectiveTeamRecruitment(&transferRadar,transferTables);}catch(const std::invalid_argument&){refused=true;}
            require(refused&&snapshot(*afterClone)==exhausted&&sameMissionState(afterClone->missionWorld().state(),exhaustedMission),
                "Exhausted actual Script must refuse before mutation");
            // Original removal mutates the real chain, slots, threat and mission
            // fields. It is not a substitute for the still-unjoined destructor.
            auto removalSeed=afterClone->clone();
            for(int id:changed){auto& a=BootCampWalkWorldInspection::actorMutable(*removalSeed,id);
                a.mission9c=123;a.teamLink498=&removalSeed->actor(commandPlayer);a.teamTarget22c=&removalSeed->actor(commandPlayer);}
            auto removal=removalSeed->clone();removalSeed.reset();
            const auto beforeRemoval=removal->missionWorld().state();const auto oldTagInstances=beforeRemoval.teamTagInstances;
            const std::array<int,4> removalOrder{changed[1],changed[3],changed[0],changed[2]};
            std::uint32_t countLeft=4,threatLeft=beforeRemoval.teamThreat;
            for(int id:removalOrder){
                require(removal->actor(id).teamLink498==&removal->actor(commandPlayer)&&removal->actor(id).teamTarget22c==&removal->actor(commandPlayer),
                    "Removal's new actual fields must rebind after source destruction");
                require(removal->removeFromObjectiveTeam(id),"Actual Team member removal must succeed");--countLeft;
                threatLeft-=std::uint32_t(BootCampWalkWorldInspection::threatType(*removal));
                const auto& a=removal->actor(id);const auto state=removal->missionWorld().state();
                require(!a.team4c4&&!a.teamNext4c8&&a.teamFlag5a2==1&&a.mission9c==-1&&!a.teamLink498&&!a.teamTarget22c&&
                    a.objectTag34==removal->missionWorld().objectiveTeamTag()&&removal->player(id)&&a.valueD8==70&&a.object.mission.queuedA0==5&&
                    state.teamMemberCount==countLeft&&state.teamTaskCounts[0]==countLeft&&state.teamThreat==threatLeft&&state.teamTagInstances==oldTagInstances,
                    "Actual unlink must preserve player/Tag/Guard and adjust each shared Team count and threat");
            }
            require(!removal->missionWorld().objectiveTeamLinks()[0]&&removal->missionWorld().state().teamConstructed&&
                removal->missionWorld().state().teamScriptCursor==1&&snapshot(*afterClone)==exhausted&&
                sameMissionState(afterClone->missionWorld().state(),exhaustedMission),
                "Explicit member removal must preserve source and not pretend to destroy Team/finish Script");
            auto removedClone=removal->clone();removal.reset();BootCampWalkWorldInspection::checkWalkHouseAliases(*removedClone);
            for(int id:changed)require(!removedClone->actor(id).team4c4&&removedClone->player(id)&&
                removedClone->actor(id).objectTag34==removedClone->missionWorld().objectiveTeamTag(),
                "Removed actual members must clone with retained House/Tag and no stale Team links");
            const int released=changed[1];const auto from=terrainCellPoint(removedClone->actor(released).ground.position);
            std::string releasedStatus;
            if(!removedClone->move(released,from.x+1,from.y,releasedStatus))
                throw std::runtime_error("Released actual GI production order refused at "+std::to_string(from.x)+","+std::to_string(from.y)+": "+releasedStatus);
            finish(*removedClone,released);
            const auto arrived=terrainCellPoint(removedClone->actor(released).ground.position);
            require(arrived.x==from.x+1&&arrived.y==from.y&&!removedClone->actor(released).team4c4&&
                removedClone->actor(released).objectTag34==removedClone->missionWorld().objectiveTeamTag(),
                "Released actual player GI must finish an ordinary production move retaining its Tag");
            std::cout<<"Actual Team RemoveMember: four handed-over GIs, TaskForce/threat/list/mission fields, retained player Tag and lifetime PASS (unscheduled; Team destruction remains guarded)\n";
            std::cout<<"Actual Team seventh tick: country13 lookup, four GI transfers, shared owners and lifetime PASS (explicit unscheduled seam)\n";
            require(snapshot(trial)==unchanged&&sameMissionState(trial.missionWorld().state(),unchangedMission),
                "Diagnostic Team AI must preserve source owner and disabled live objectives");
        }
        {
            const auto untouched=snapshot(trial);auto recruitment=trial.clone();
            auto& mission=recruitment->missionWorld();
            require(mission.state().teamScriptActionCount==2&&!mission.objectiveTeamScriptHasCurrent()&&
                mission.objectiveTeamScriptAction().action==-1&&mission.nextObjectiveTeamScriptAction().action==50&&
                mission.nextObjectiveTeamScriptAction().argument==70,"Actual Script must retain initial cursor and numeric commands");
            require(mission.refreshObjectiveTeamReadiness(),"New empty Team readiness must survive");
            const auto empty=mission.state().teamFlags;
            require(empty[6]==1&&empty[5]==0&&empty[2]==0&&empty[9]==1&&empty[10]==0,
                "Empty Team must retain original readiness gates without clearing pending refresh");
            require(mission.resetObjectiveTeamScript()&&mission.advanceObjectiveTeamScript()&&
                mission.objectiveTeamScriptHasCurrent()&&mission.objectiveTeamScriptAction().action==50&&
                mission.objectiveTeamScriptAction().argument==70,"Actual Script first cursor differs");
            auto intermediate=recruitment->clone();auto scriptClone=intermediate->clone();intermediate.reset();
            auto& copiedScript=scriptClone->missionWorld();
            require(copiedScript.objectiveTeamScriptAction().action==50&&copiedScript.advanceObjectiveTeamScript()&&
                copiedScript.objectiveTeamScriptAction().action==20&&copiedScript.objectiveTeamScriptAction().argument==13&&
                mission.state().teamScriptCursor==0,"Script clone must rebind backing and advance independently after source destruction");
            require(!copiedScript.advanceObjectiveTeamScript()&&!copiedScript.objectiveTeamScriptHasCurrent()&&
                copiedScript.resetObjectiveTeamScript()&&copiedScript.state().teamScriptCursor==-1&&mission.state().teamScriptCursor==0,
                "Exhaustion/reset must preserve independent actual Script owners");
            std::size_t recruited=0;
            while(recruitment->recruitObjectiveTeamSlot(0)){
                require(++recruited<=recruitment->actors().size(),"Original candidate recruitment failed to converge");
                require(recruitment->missionWorld().state().teamMemberCount==recruited,"Selected candidate must join the same actual Team");
                require(mission.refreshObjectiveTeamReadiness(),"Populated actual Team must survive readiness refresh");
                const auto flags=mission.state().teamFlags;
                require(flags[5]==std::uint8_t(recruited==4)&&flags[4]==std::uint8_t(recruited==4)&&
                    flags[6]==std::uint8_t(recruited!=4)&&flags[9]==0&&flags[10]==0&&
                    (recruited!=4||flags[7]==1),"Actual partial/full readiness flags differ");
            }
            require(recruited==4&&recruitment->missionWorld().state().teamTaskCounts[0]==4&&snapshot(trial)==untouched,
                "Original candidate scan must recruit four existing Other2 GIs without source mutation");
            for(const auto& [id,a]:recruitment->actors()){
                if(recruitment->player(id))require(!a.team4c4,"Original House admission must exclude the player GI");
                else require(a.team4c4==recruitment->missionWorld().objectiveTeamIdentity()&&a.route[0]==-1&&!a.targetFlag404&&!a.targetFlag57e,
                    "Recruitment must clear the chosen actual GI target state before membership");
            }
            const auto full=snapshot(*recruitment);require(!recruitment->recruitObjectiveTeamSlot(0)&&snapshot(*recruitment)==full,
                "Full TaskForce must refuse without further target/member mutation");
            auto survivor=recruitment->clone();recruitment.reset();
            require(!survivor->recruitObjectiveTeamSlot(0)&&survivor->missionWorld().state().teamMemberCount==4,
                "Recruited Team must preserve actual identities after source destruction");
        }
        {
            std::vector<int> members;for(const auto& [id,a]:trial.actors())if(!trial.player(id))members.push_back(id);
            for(std::size_t i=0;i<members.size();++i){
                const auto id=members[i];require(trial.addToObjectiveTeam(id),"Actual GI must join the constructed Team");
                const auto& a=trial.actor(id);
                require(a.team4c4==trial.missionWorld().objectiveTeamIdentity()&&a.objectTag34==trial.missionWorld().objectiveTeamTag()&&
                    a.teamGroup1ac==-2&&a.teamLeader579==std::uint8_t(i==0)&&a.recruitable37a==0&&a.object.mission.hasTag,
                    "Actual membership must preserve Team/Tag/group/leader/recruitability effects");
                require(a.teamNext4c8==(i?static_cast<const void*>(&trial.actor(members[i-1])):nullptr),"Actual Team list must prepend members");
            }
            const auto memberState=trial.missionWorld().state();const auto links=trial.missionWorld().objectiveTeamLinks();
            require(memberState.teamMemberCount==4&&memberState.teamTaskCounts[0]==4&&memberState.teamTagInstances==4&&
                links[0]==&trial.actor(members.back())&&links[1]&&links[2]==&trial.actor(members.front()),
                "Actual Team must own four members and the first leader anchor");
            const auto before=snapshot(trial);
            for(const auto& [id,a]:trial.actors())require(!trial.addToObjectiveTeam(id),"Repeated/member or foreign House addition must refuse");
            require(snapshot(trial)==before,"Refused repeated membership must not mutate actual owners");
            auto dying=trial.clone();auto survivor=dying->clone();dying.reset();
            const auto copied=survivor->missionWorld().objectiveTeamLinks();
            require(copied[0]==&survivor->actor(members.back())&&copied[2]==&survivor->actor(members.front()),
                "Team clone must rebind actual member and anchor identities after source destruction");
            const void* expectedAnchor=nullptr;
            for(auto id:members)if(links[1]==&trial.actor(id))expectedAnchor=&survivor->actor(id);
            for(std::size_t i=0;i<trial.map().cells.size();++i)
                if(links[1]==&trial.map().cells[i].attributes.input)expectedAnchor=&survivor->map().cells[i].attributes.input;
            if(links[1]==&trial.map().fallback.input)expectedAnchor=&survivor->map().fallback.input;
            require(expectedAnchor&&copied[1]==expectedAnchor&&copied[1]!=links[1],"Cloned Team anchor must borrow its own member or Cell");
            for(std::size_t i=0;i<members.size();++i){const auto& a=survivor->actor(members[i]);require(a.team4c4==survivor->missionWorld().objectiveTeamIdentity()&&
                a.objectTag34==survivor->missionWorld().objectiveTeamTag()&&
                a.teamNext4c8==(i?static_cast<const void*>(&survivor->actor(members[i-1])):nullptr),
                "Cloned GI membership/Tag/next must borrow cloned owners");}
            survivor->missionWorld().drainDeferred();
            require(survivor->missionWorld().state().teamMemberCount==4&&survivor->missionWorld().state().teamTagInstances==4&&snapshot(trial)==before,
                "Populated Team must survive original Objective1 cleanup independently");
        }
        trial.missionWorld().drainDeferred();const auto drained=trial.missionWorld().state();
        require(drained.deferred==0&&drained.triggerFreed&&drained.tagFreed&&
                drained.teamTriggerControlBound&&drained.triggerControlCount==5&&drained.registryCounts==std::array<std::int32_t,4>{5,7,6,1},"First objective lifetime did not retain controlled owners");
        require(!trial.missionWorld().discoverStructure(1019675),
                "Repeated discovery after objective cleanup must stop at recovered Unit discovery state");
    }
    {
        BootCampWalkWorld trial(assets,mission,source,rules,art);int sightActor=-1;
        for(const auto& [id,a]:trial.actors())if(trial.player(id)){require(sightActor==-1,"Sight composition requires one player GI");sightActor=id;}
        require(sightActor!=-1,"Sight composition player GI missing");
        const auto initial=trial.missionWorld().state();require(initial.textRequests==0,"Sight composition must start before Objective1");
        {
            auto redrawWorld=trial.clone();const auto beforeRedraw=snapshot(trial);
            CellRedrawView view;view.viewportX=-10000000;view.viewportWidth=20000000;
            view.viewportHeight=20000000;view.originB4=-10000000; // Supplied diagnostic geometry.
            auto& visibility=redrawWorld->visibilityWorld();
            visibility.withCellRedraw(redrawWorld->tickOwner(),view,[&]{redrawWorld->composeArrivalSight(sightActor);});
            const auto queue=visibility.redrawQueue();
            require(queue.countE0>0&&queue.countE0<799&&queue.dirtyD7D==1,
                    "Actual arrival sight must queue actual Cells through complete redraw in an explicit viewport scope");
            for(int n=0;n<queue.countE0;++n){const auto id=queue.cells[std::size_t(n)];
                require(id>=0&&BootCampWalkWorldInspection::visibilityCells(*redrawWorld).at(std::size_t(id)).redrawFrame5c==redrawWorld->tick(),
                        "Queued redraw identities must belong to actual shared Cells stamped at the actual frame");
            }
            auto warm=redrawWorld->clone();require(warm->visibilityWorld().redrawQueue().cells==queue.cells&&
                warm->visibilityWorld().redrawQueue().countE0==queue.countE0,"Warm clone must retain redraw queue and capacity tails");
            visibility.withCellRedraw(redrawWorld->tickOwner(),view,[&]{redrawWorld->composePostSight(sightActor);});
            require(visibility.redrawQueue().countE0==queue.countE0,"Same-frame post-sight must not duplicate queued Cells");
            bool nested=false,activeClone=false;
            visibility.withCellRedraw(redrawWorld->tickOwner(),view,[&]{
                try{visibility.withCellRedraw(redrawWorld->tickOwner(),view,[]{});}catch(const std::invalid_argument&){nested=true;}
                try{auto invalid=redrawWorld->clone();}catch(const std::invalid_argument&){activeClone=true;}
            });
            require(nested&&activeClone,"Nested scopes and clones during redraw must refuse without retaining callback aliases");
            redrawWorld.reset();
            warm->visibilityWorld().withCellRedraw(warm->tickOwner(),view,[&]{warm->composePostSight(sightActor);});
            require(snapshot(trial)==beforeRedraw,"Composed redraw and clone continuation must preserve source world");
            std::cout<<"Actual arrival Cell redraw: shared frames/queue, same-frame suppression, warm/source-destruction/scoped refusal PASS\n";
        }
        trial.composeArrivalSight(sightActor);const auto post=trial.visibilityWorld().state();
        require(post.revealAreas==1&&post.sightAdds==1&&post.sightRemovals==0&&
                trial.visibilityWorld().at({57,89}).counter130==-1&&trial.missionWorld().state().textRequests==0,
                "First Techno sight composition differs");
        const auto& commenced=trial.actor(sightActor).object;
        require(commenced.mission.mission98==5&&commenced.mission.queuedA0==-1&&commenced.statusA8==0&&
                commenced.lastAC==0&&commenced.timerStart==0&&commenced.timerPadding==0&&commenced.timerRemaining==0,
                "No-pending Mission Commence changed the actual GI");
        require(post.postSightCalls==1&&post.maskCalls==383&&
                trial.visibilityWorld().at({57,89}).counter130==-1&&
                trial.visibilityWorld().at({63,89}).counter130==0&&
                trial.visibilityWorld().at({63,89}).primary120==254&&
                trial.visibilityWorld().at({63,89}).redraw138==1,
                "Post-sight refresh did not reuse shared visibility Cells");
        trial.composeSight(sightActor);const auto repeated=trial.visibilityWorld().state();
        require(repeated.revealAreas==3&&repeated.sightAdds==2&&repeated.sightRemovals==1&&
                trial.visibilityWorld().at({57,89}).counter130==-1&&trial.missionWorld().state().textRequests==0,
                "Repeated same-position sight did not restore before adding");
        std::string sightStatus;require(trial.move(sightActor,66,92,sightStatus),"Sight composition route to Objective1 differs");
        finish(trial,sightActor);
        require(trial.visibilityWorld().at({57,89}).counter130==-1&&trial.visibilityWorld().at({66,92}).counter130==0&&
                trial.missionWorld().state().textRequests==0,
                "Unscheduled walking must not change sight state");
        trial.composeSight(sightActor);const auto moved=trial.visibilityWorld().state();
        require(moved.revealAreas==7&&moved.sightAdds==3&&moved.sightRemovals==2&&
                trial.visibilityWorld().at({57,89}).counter130==0&&trial.visibilityWorld().at({66,92}).counter130==-1,
                "Moved sight did not restore old-only and decrement new-only Cells");
        std::cout<<"Shared resident sight: text="<<trial.missionWorld().state().textRequests<<" discoveries="<<moved.discoveredResidents<<" initial="<<post.discoveredResidents<<" last="<<moved.lastResident<<'\n';
        require(trial.missionWorld().state().textRequests==1&&moved.discoveredResidents==7&&moved.waypointReveals==1&&moved.waypointAreaCalls==2&&post.discoveredResidents==1&&
                std::count_if(trial.actors().begin(),trial.actors().end(),[](const auto& item){return item.second.object.mission.current373!=0;})==5,
                "Moved Techno sight did not reach actual Objective1 discovery");
    }
    int player=-1,players=0;for(const auto& [id,a]:world.actors())if(world.player(id)){player=id;++players;}
    require(players==1&&world.actors().size()==5,"Expected one player among five GIs");const auto initial=world.actor(player).ground.position;
    require(initial==Coord{57*256+192,89*256+192,assets.cell(57,89)->z*104},"Player start differs from map/subcell/floor inputs");
    require(world.actor(player).flag32d==1,"Supplied active byte must be shared by sight and admission");
    require(world.residentSearchState().enabled==1,"Scenario-loop resident search state must be initialized");
    const auto initialResidents=world.composeKind6ResidentSearch(initial);
    require(!initialResidents.resident&&initialResidents.kindQueries==1&&initialResidents.nextReads==1,
            "Initialized kind-6 search must traverse the actual player GI primary-list record");
    {
        BootCampWalkWorld trial(assets,mission,source,rules,art);std::string previewStatus;
        require(trial.move(player,59,89,previewStatus),"Update-position preview requires an actual Cell order");
        const auto before=snapshot(trial);const auto missionBefore=trial.missionWorld().state();
        const auto visibilityBefore=trial.visibilityWorld().state();
        auto changedBuilding=trial.missionWorld().structureResident(1019675);changedBuilding.flags14=0;
        const auto changedBefore=snapshot(trial);
        require(trial.composeUpdatePositionPreview(player).arrivalProcessCalls==26&&snapshot(trial)==changedBefore,
                "Warm preview must preserve changed Building residents without mutating the source");
        changedBuilding.flags14=1;require(snapshot(trial)==before,"Restored Building diagnostic must retain all source owners");
        const auto preview=trial.composeUpdatePositionPreview(player);
        require(preview.permissionSuccessContinuation&&preview.arrivalNotifications==1&&preview.arrivalKind==2&&
                preview.arrivalProcessCalls==26&&preview.arrivalPosition==Coord{58*256+192,89*256+192,208}&&
                preview.currentCell==reinterpret_cast<std::uintptr_t>(trial.map().table.at(89*512+58))&&
                preview.targetCell==reinterpret_cast<std::uintptr_t>(trial.actor(player).target494)&&preview.currentCell!=preview.targetCell&&
                preview.missionQueries==11&&preview.parentCellQueries==3&&preview.currentCellGetters==3&&
                preview.currentCellMapQueries==6&&preview.cellValueQueries==1&&
                preview.residentSearches==3&&preview.kindQueries==0&&preview.nextReads==0&&
                preview.kind2Queries==2&&preview.kind1Queries==2&&preview.targetKindQueries==1&&preview.targetCoordinateQueries==1&&
                preview.locomotorQueries==1&&preview.sightMissionCalls==1&&preview.sightRemoveCalls==1&&
                preview.sightAddCalls==1&&preview.sightPostCalls==1&&preview.alternateQueries==1&&
                preview.alternateTypeQueries==3&&preview.alternateMissionQueries==0&&preview.alternateResult==0&&
                preview.sightRevealAreas==1&&preview.sightReveals==1&&preview.sightRemovals==0&&
                preview.sightMaskCalls==383&&preview.sightRedraws==282&&preview.sightFinalRange==5&&preview.sightFinalActive==1&&
                preview.discoveryCalls==1&&preview.initialDiscovered==0&&preview.finalDiscovered==1&&
                preview.finalOwner5668==1&&preview.finalOwner5669==1&&preview.finalOwner13c==1&&
                preview.effectCellPointQueries==2&&preview.effectCellQueries==3&&preview.permissionQueries==1&&
                preview.scratchStores==1&&preview.positionChildCalls==1&&preview.mapAssociationCalls==2&&preview.dirtyCalls==1&&preview.tailActiveStore==1&&
                preview.positionCell==preview.currentCell&&preview.positionCloakExit==0&&preview.positionCloakPredicateQueries==0&&
                preview.dirtyCell==preview.currentCell&&preview.dirtyPrefixExit==0,
                "Actual Boot Camp update-position permission-success preview differs");
        require(snapshot(trial)==before,"Discarded update-position preview changed live Walk owners");
        const auto sequence=trial.composeUpdatePositionPreviewSequence(player,2);
        require(sequence.size()==2&&sequence[0].initialState59a==0x5a&&sequence[0].initialState59c==0x5c&&
                sequence[0].initialScratch==0x12345678&&sequence[0].finalState59a==0&&sequence[0].finalState59c==0&&sequence[0].finalScratch==0&&
                sequence[1].initialState59a==0&&sequence[1].initialState59c==0&&sequence[1].initialScratch==0&&
                sequence[1].finalState59a==0&&sequence[1].finalState59c==0&&sequence[1].finalScratch==0&&
                sequence[1].arrivalProcessCalls>sequence[0].arrivalProcessCalls&&sequence[1].sightRemovals==1&&
                sequence[0].discoveryCalls==1&&sequence[0].finalDiscovered==1&&
                sequence[1].initialDiscovered==1&&sequence[1].finalDiscovered==1&&sequence[1].discoveryCalls==0&&
                sequence[1].effectCellQueries==2&&sequence[1].mapAssociationCalls==1&&
                sequence[1].sightReveals==1&&sequence[1].tailActiveStore==trial.actor(player).flag32d,
                "Repeated actual arrivals reset actor fields or failed shared sight/admission state");
        require(snapshot(trial)==before,"Discarded arrival sequence changed persistent source owners");
        std::cout<<"Discarded shared discovery: arrival calls="<<sequence[0].arrivalProcessCalls<<','<<sequence[1].arrivalProcessCalls
                 <<" discovery="<<sequence[0].discoveryCalls<<','<<sequence[1].discoveryCalls
                 <<" Cell queries="<<sequence[0].effectCellQueries<<','<<sequence[1].effectCellQueries<<" source isolation PASS\n";
        const auto missionAfter=trial.missionWorld().state();const auto visibilityAfter=trial.visibilityWorld().state();
        require(missionAfter.textRequests==missionBefore.textRequests&&missionAfter.deferred==missionBefore.deferred&&
                visibilityAfter.revealAreas==visibilityBefore.revealAreas&&visibilityAfter.maskCalls==visibilityBefore.maskCalls,
                "Discarded update-position preview changed mission/visibility owners");
        bool nonplayerRefused=false;for(const auto& [id,actor]:trial.actors())if(id!=player){
            const auto refusalBefore=snapshot(trial);try{(void)trial.composeUpdatePositionPreview(id);}catch(const std::invalid_argument&){nonplayerRefused=true;}
            require(snapshot(trial)==refusalBefore,"Nonplayer update-position refusal changed live owners");break;
        }
        require(nonplayerRefused,"Nonplayer update-position preview must refuse");
        BootCampWalkWorld warmed(assets,mission,source,rules,art);require(warmed.move(player,59,89,previewStatus),"Warm visibility preview needs an order");
        warmed.composeSight(player);for(int n=0;n<7;++n)warmed.step();
        (void)warmed.visibilityWorld().visible({0,0,104},false); // Warm shared fallback too.
        const auto warmBefore=snapshot(warmed);const auto warmMission=warmed.missionWorld().state();
        const auto warm=warmed.composeUpdatePositionPreview(player);
        require(warm.arrivalProcessCalls==19&&warm.initialDiscovered==1&&warm.discoveryCalls==0&&warm.sightRemovals==1&&
                warm.arrivalPosition==preview.arrivalPosition&&snapshot(warmed)==warmBefore&&sameMissionState(warmed.missionWorld().state(),warmMission),
                "Warm moving preview must retain sight/mission/route/frame/fallback values and source owners");
        auto fork=warmed.clone();
        require(fork->actor(player).target494!=warmed.actor(player).target494&&
                fork->actor(player).target494==fork->map().table.at(89*512+59)&&fork->tick()==warmed.tick(),
                "Warm clone must remap the target and retain the frame");
        for(const auto& c:fork->map().cells){const auto& input=c.attributes.input;
            require(&fork->visibilityWorld().at({input.position.x,input.position.y}).flags140==&input.flags,
                    "Cloned visibility flags must borrow cloned terrain Cells");}
        require(&fork->visibilityWorld().fallback().flags140==&fork->map().fallback.input.flags,
                "Cloned fallback visibility must borrow the cloned terrain word");
        require(fork->map().buffer4.data()!=warmed.map().buffer4.data()&&fork->map().buffer10.data()!=warmed.map().buffer10.data()&&
                fork->map().buffer4==warmed.map().buffer4&&fork->map().buffer10==warmed.map().buffer10,
                "Warm clone must own separate map buffers with retained values");
        for(const auto& [id,a]:warmed.actors())require(&a!=&fork->actor(id)&&a.route==fork->actor(id).route&&
                a.ground.position==fork->actor(id).ground.position&&a.walk.head==fork->actor(id).walk.head&&
                a.body.current(warmed.tick())==fork->actor(id).body.current(fork->tick()),
                "All GI records must retain independent warm actor/route/pose ownership");
        finish(*fork,player);require(snapshot(warmed)==warmBefore,"Clone movement must not mutate source memberships or floor caches");
        finish(warmed,player);require(warmed.move(player,61,89,previewStatus),"Moved warm world needs a later order");
        warmed.composeArrivalSight(player);const auto movedBefore=snapshot(warmed);
        const auto moved=warmed.composeUpdatePositionPreviewSequence(player,2);
        require(moved.size()==2&&moved[0].arrivalPosition.x/256==60&&moved[1].arrivalPosition.x/256==61&&snapshot(warmed)==movedBefore,
                "Warm preview must retain moved source position, actual heads and later route");
        const auto failureBefore=snapshot(trial);bool boundRefused=false;
        try{(void)trial.composeUpdatePositionPreviewSequence(player,3);}catch(const std::logic_error& e){
            boundRefused=std::string(e.what()).find("did not reach")!=std::string::npos;
        }
        require(boundRefused&&snapshot(trial)==failureBefore,"Exhausted arrival preview must discard all Process and sight writes");
        int unowned=0;auto& diagnostic=const_cast<InfantryWalkState&>(trial.actor(player));diagnostic.team4c4=&unowned;
        const auto unsupportedBefore=snapshot(trial);bool unsupportedRefused=false;
        try{(void)trial.clone();}catch(const std::invalid_argument& e){unsupportedRefused=std::string(e.what()).find("Team")!=std::string::npos;}
        require(unsupportedRefused&&snapshot(trial)==unsupportedBefore,"Unowned pointer clone refusal must preserve the source");diagnostic.team4c4=nullptr;
        diagnostic.transport588=&unowned;const auto transportBefore=snapshot(trial);bool transportRefused=false;
        try{(void)trial.clone();}catch(const std::invalid_argument&){transportRefused=true;}
        require(transportRefused&&diagnostic.transport588==&unowned&&snapshot(trial)==transportBefore,
                "Unsupported transport clone must preserve original ownership");diagnostic.transport588=nullptr;
        diagnostic.field1b0=&unowned;const auto fieldBefore=snapshot(trial);bool fieldRefused=false;
        try{(void)trial.clone();}catch(const std::invalid_argument& error){fieldRefused=std::string(error.what()).find("field1B0")!=std::string::npos;}
        require(fieldRefused&&snapshot(trial)==fieldBefore,"Unknown1B0 pointer must refuse without source mutation");diagnostic.field1b0=nullptr;
        auto& mapDiagnostic=const_cast<MutableUnitMap&>(trial.map());
        const auto mapSlot=std::size_t(89*512+58);auto* savedCell=mapDiagnostic.table.at(mapSlot);mapDiagnostic.table.at(mapSlot)=nullptr;
        const auto splitBefore=snapshot(trial);bool splitRefused=false;
        try{(void)trial.clone();}catch(const std::invalid_argument& e){splitRefused=std::string(e.what()).find("associations")!=std::string::npos;}
        require(splitRefused&&snapshot(trial)==splitBefore,"Split source map must refuse without silently reconstructing different associations");
        mapDiagnostic.table.at(mapSlot)=savedCell;
        int observerCalls=0;mapDiagnostic.resident.world.query=[&](MapInputPosition){++observerCalls;};
        bool observerRefused=false;try{(void)trial.clone();}catch(const std::invalid_argument& e){observerRefused=std::string(e.what()).find("observers")!=std::string::npos;}
        require(observerRefused&&!observerCalls,"External map observer must refuse without querying the source");mapDiagnostic.resident.world.query={};
        // Exercise warm source destruction with deferred mission cleanup, full
        // movement, resident traversal and another clone after cleanup.
        auto disposable=std::make_unique<BootCampWalkWorld>(assets,mission,source,rules,art);
        require(disposable->move(player,59,89,previewStatus),"Source-destruction clone needs an order");
        disposable->composeSight(player);disposable->step();
        require(disposable->missionWorld().discoverStructure(1019675),"Queued mission clone needs discovery");
        disposable->missionWorld().structureResident(1019675).next=player;
        auto survivor=disposable->clone();disposable.reset();survivor->missionWorld().drainDeferred();
        require(survivor->missionWorld().structureResidentState(1019675).next==player,"Walk clone must rebind external GI identity resolution");
        finish(*survivor,player);survivor->composeArrivalSight(player);
        require(survivor->missionWorld().state().textRequests==1&&survivor->missionWorld().state().tagFreed,
                "Warm world must survive source destruction with remapped cleanup and discovery callbacks");
        auto drained=survivor->clone();survivor.reset();
        require(drained->move(player,61,89,previewStatus),"Drained warm clone needs a later order");
        const auto drainedBefore=snapshot(*drained);(void)drained->composeUpdatePositionPreview(player);
        require(snapshot(*drained)==drainedBefore,"Drained warm clone must retain discarded preview isolation");
        BootCampWalkWorld near(assets,mission,source,rules,art);
        require(near.move(player,66,92,previewStatus),"Objective approach needs a supported route");finish(near,player);
        require(near.move(player,68,92,previewStatus),"Objective preview needs a later supported order");
        auto building=near.missionWorld().inspectStructureExpiration(1019675);
        building.fields.target228=building.tagIdentity;building.fields.pending9C=19;building.actor.queuedA4=7;
        building.fields.byte404=9;building.fields.word310=42;building.fields.backing[4][7]=building.tagIdentity;
        const auto nearBefore=snapshot(near);const auto nearMission=near.missionWorld().state();
        const auto objective=near.composeUpdatePositionPreview(player);
        require(nearMission.textRequests==0&&objective.finalMissionTextRequests==1&&objective.finalMissionMessageLines>0&&objective.finalMissionDeferred==2&&
                objective.finalMissionTagInstances==0&&snapshot(near)==nearBefore&&sameMissionState(near.missionWorld().state(),nearMission),
                "Actual arrival sight must execute and discard cloned discovery/Tag/action/cleanup writes");
        std::cout<<"Discarded warm objective arrival: text requests="<<objective.finalMissionTextRequests<<" deferred="<<objective.finalMissionDeferred<<" source unchanged\n";
        Renderer renderer(assets,320,240,"Gold");renderer.center(trial.actor(player).ground.position);renderer.drawMap();renderer.drawMap();
        const auto pixels=renderer.pixels;const auto* pixelBacking=renderer.pixels.data();const auto camera=renderer.camera;
        const auto rendering=std::tuple{renderer.terrainRejections,renderer.sceneryPixels,renderer.sceneryShadowPixels,renderer.shadowBuilds,renderer.shadowHits,renderer.voxelBuilds,renderer.voxelHits};
        const auto beforeDrawing=snapshot(trial);(void)trial.composeUpdatePositionPreviewSequence(player,2);
        const auto warmObjective=near.composeUpdatePositionPreview(player);
        require(warmObjective.finalMissionTextRequests==1&&snapshot(near)==nearBefore&&snapshot(trial)==beforeDrawing&&renderer.pixels==pixels&&renderer.pixels.data()==pixelBacking&&renderer.camera==camera&&
                rendering==std::tuple{renderer.terrainRejections,renderer.sceneryPixels,renderer.sceneryShadowPixels,renderer.shadowBuilds,renderer.shadowHits,renderer.voxelBuilds,renderer.voxelHits},
                "Discarded preview must preserve warm renderer values and backing");
        renderer.drawMap();require(renderer.pixels==pixels,"Warm renderer redraw after preview must retain the baseline output");
        // Compose objective discovery on an owned full world, warm its actual
        // message canvas, then discard arrival/drawing/expiry in another clone.
        auto messageWorld=trial.clone();messageWorld->missionWorld().discoverStructure(1019675);
        auto& messageOwner=messageWorld->missionWorld().messages();messageOwner.setMilliseconds(128);messageOwner.draw();
        require(messageOwner.list().head&&!messageOwner.fills().empty(),"Full world must own actual objective messages");
        const auto messageBefore=snapshot(*messageWorld);auto messageFork=messageWorld->clone();
        require(messageFork->missionWorld().messages().list().head!=messageOwner.list().head&&
                messageFork->missionWorld().messages().pixels().data()!=messageOwner.pixels().data(),
                "Full world clone must remap warm message ownership");
        std::vector<std::uint32_t> messageFrame(1024*720,0xff123456);
        const auto composed=composeMessageFrame(messageFork->missionWorld().messages(),messageFrame,1024,720,256);
        require(composed.glyphStores&&composed.fillStores&&messageFrame.back()==0xff123456,
                "Full world message composition must forward actual writes and retain unrelated ARGB pixels");
        (void)messageFork->composeUpdatePositionPreviewSequence(player,2);
        messageFork->missionWorld().messages().setMilliseconds(100000);messageFork->missionWorld().messages().expire();
        require(snapshot(*messageWorld)==messageBefore&&renderer.pixels==pixels&&renderer.pixels.data()==pixelBacking&&renderer.camera==camera,
                "Discarded full message/arrival preview changed warm live world or renderer");
        auto messageSurvivor=messageWorld->clone();messageWorld.reset();
        require(composeMessageFrame(messageSurvivor->missionWorld().messages(),messageFrame,1024,720,256).glyphStores,
                "Message frame composition must continue after source world destruction");
        (void)messageSurvivor->composeUpdatePositionPreviewSequence(player,2);messageSurvivor->missionWorld().drainDeferred();
        std::cout<<"Warm full world objective messages: insertion/drawing/expiry/discard/source-destruction PASS\n";
        std::cout<<"Warm Walk/visibility/mission clones: moved/warm/fallback/queued/drained/source-destruction/bounded refusal/renderer isolation PASS\n";

    }
    {
        const auto source=snapshot(world);auto discovery=world.clone();
        BootCampWalkWorldInspection::membershipDiscoveryCheck(*discovery,player);
        require(snapshot(world)==source,"Actual membership discovery clone changed source owners");
        auto survivor=discovery->clone();discovery.reset();
        BootCampWalkWorldInspection::membershipDiscoveryCheck(*survivor,player);
        std::cout<<"Actual GI membership discovery: live mode/House, Cell gates, repeated notify, source isolation/destruction and no synthetic objective PASS\n";
    }
    std::string status;int acceptedRoutes=0;
    {
        const auto before=snapshot(world);
        const auto sourceFields=world.missionWorld().structureSightState(1019675);
        auto trial=world.clone();auto& mission=trial->missionWorld();
        Renderer frameView(assets,1024,720,"Gold");
        auto first=mission.structureSight(1019675),second=mission.structureSight(1019676);
        frameView.center(first.position);const PixelRect bounds{0,0,683,480};
        const auto count=trial->visibilityWorld().redrawQueue().countE0;
        const auto dirty=trial->visibilityWorld().redrawQueue().dirtyD7D;
        require(!frameView.buildingRedrawPending(bounds,mission.buildingFrameRegistry()),
                "Supplied clean actual structures must not request frame redraw");
        first.fields.redraw75=0x80;
        require(frameView.buildingRedrawPending(bounds,mission.buildingFrameRegistry()),
                "Dirty actual objective structure must be found through recovered Building+A8");
        first.fields.marked74=0;
        require(!frameView.buildingRedrawPending(bounds,mission.buildingFrameRegistry()),"Unmarked actual structure must be skipped");
        first.fields.marked74=1;first.fields.onMap7d=0;
        require(!frameView.buildingRedrawPending(bounds,mission.buildingFrameRegistry()),"Off-map actual structure must be skipped");
        second.fields.redraw75=2;frameView.center(second.position);
        require(frameView.buildingRedrawPending(bounds,mission.buildingFrameRegistry()),"Second actual structure must be scanned after refused first");
        frameView.camera.x+=100000;frameView.camera.y+=100000;
        require(!frameView.buildingRedrawPending(bounds,mission.buildingFrameRegistry()),"Actual camera pan must clip pending structure");
        frameView.center(second.position);const auto position=second.position;
        second.position.x+=1000000;
        require(!frameView.buildingRedrawPending(bounds,mission.buildingFrameRegistry()),"Frame query must borrow current actual structure coordinates");
        second.position=position;
        auto warm=trial->clone();trial.reset();
        require(frameView.buildingRedrawPending(bounds,warm->missionWorld().buildingFrameRegistry()),
                "Fresh registry view on a warm clone must survive source destruction");
        require(warm->visibilityWorld().redrawQueue().countE0==count&&warm->visibilityWorld().redrawQueue().dirtyD7D==dirty&&
                snapshot(world)==before&&world.missionWorld().structureSightState(1019675)==sourceFields,
                "Building frame query must not reset queues, trigger objectives or mutate source owners");
        std::cout<<"Actual Building frame predicate: live structure flags/coordinates, camera clipping, warm clone/source destruction, unchanged queues and source isolation PASS (startup/registry supplied; unscheduled)\n";
    }
    {
        const auto before=snapshot(world);const auto sourceFields=world.missionWorld().structureSightState(1019675);
        auto trial=world.clone();Renderer frame(assets,1024,720,"Gold");
        auto first=trial->missionWorld().structureSight(1019675);frame.center(first.position);
        const auto cellCount=trial->visibilityWorld().redrawQueue().countE0;
        const auto cellDirty=trial->visibilityWorld().redrawQueue().dirtyD7D;
        int typeCalls=0;bool supplyType=false;
        auto bind=[&](BootCampWalkWorld& owner){return owner.missionWorld().buildingInvalidationRegistry(
            [&](int key,Coord raw,BuildingRenderBoundsState& cache)->const PixelRect&{
                require(key==1019675||key==1019676,"Foreign actual Building bounds identity");
                std::function<PixelRect()> type;
                if(supplyType)type=[&]{++typeCalls;return PixelRect{-16,-20,32,40};};
                return frame.buildingBounds(raw,cache,type);
            });};
        first.fields.redraw75=0x80;first.fields.onMap7d=0;first.fields.marked74=0;
        const auto initialCache=first.fields.renderBounds;
        bool refused=false;try{frame.invalidateBuildings({0,0,683,480},{},bind(*trial));}catch(const std::invalid_argument&){refused=true;}
        require(refused&&first.fields.redraw75==0x80&&first.fields.renderBounds==initialCache&&frame.frameDirtyRegions().count==0,
                "Missing actual Building Type bounds must refuse a miss without invented bounds/clear");
        supplyType=true;frame.invalidateBuildings({0,0,683,480},{},bind(*trial));
        require(!first.fields.redraw75&&typeCalls==1&&frame.frameDirtyRegions().count==1,
                "Actual invalidation must ignore7D/74, register bounds then clear75");
        const auto cached=first.fields.renderBounds;const auto queued=frame.frameDirtyRegions().slots[0];
        require(queued.flag==0&&queued.bounds.x==cached.bounds50c.x&&queued.bounds.y==cached.bounds50c.y&&
                queued.bounds.width==32&&queued.bounds.height==40&&cached.coordinates51c==buildingRenderCoordinates(first.position),
                "Actual cache and dirty queue must use raw-minus128 coordinates and relative supplied Type bounds");
        first.fields.redraw75=255;supplyType=false;
        frame.invalidateBuildings({0,0,683,480},{5000,5000},bind(*trial));
        require(first.fields.redraw75==255&&typeCalls==1&&first.fields.renderBounds==cached,
                "Translated overlap rejection must retain redraw and reuse cache without Type child");
        auto warm=trial->clone();trial.reset();
        frame.invalidateBuildings({0,0,683,480},{},bind(*warm));
        require(!warm->missionWorld().structureSightState(1019675).redraw75&&frame.frameDirtyRegions().count==1&&typeCalls==1,
                "Warm actual cache must survive source destruction and retained queue containment");
        auto live=warm->missionWorld().structureSight(1019675);live.fields.redraw75=1;frame.camera.x+=10;
        supplyType=true;frame.invalidateBuildings({0,0,683,480},{},bind(*warm));
        require(!live.fields.redraw75&&typeCalls==2&&live.fields.renderBounds.origin528!=cached.origin528,
                "Actual camera change must invalidate the same Building cache key");
        live.position.x+=256;live.fields.redraw75=1;
        frame.invalidateBuildings({0,0,683,480},{},bind(*warm));
        require(!live.fields.redraw75&&typeCalls==3&&live.fields.renderBounds.coordinates51c==buildingRenderCoordinates(live.position),
                "Live actual position must invalidate bounds and update the same owner");
        require(warm->visibilityWorld().redrawQueue().countE0==cellCount&&warm->visibilityWorld().redrawQueue().dirtyD7D==cellDirty&&
                snapshot(world)==before&&world.missionWorld().structureSightState(1019675)==sourceFields,
                "Explicit Building invalidation must retain Cell queues, mission state and source owners");
        std::cout<<"Actual Building invalidation: shared cache/flags, missing Type refusal, camera/position misses, queue containment/retention and warm source destruction PASS (Type bounds/startup supplied; unscheduled)\n";
    }
    {
        const auto before=snapshot(world);auto trial=world.clone();Renderer frame(assets,1024,720,"Gold");
        // Supplied stock Temperate image associations, not recovered theater/
        // demand loading. Metadata is compared with actual original routines by
        // compare_building_type_bounds.py using building-type-assets output.
        std::array<ShpImage,2> images{readShp(assets.store.require("ctarmy04.shp")),readShp(assets.store.require("ctarmy01.shp"))};
        std::array<int,2> imageCalls{};bool supplyImages=true;
        auto bind=[&](BootCampWalkWorld& owner){auto* mission=&owner.missionWorld();
            return mission->buildingInvalidationRegistry([&,mission](int key,Coord raw,BuildingRenderBoundsState& cache)->const PixelRect&{
                const int index=key==1019675?0:key==1019676?1:-1;require(index>=0,"Foreign actual Type image identity");
                return frame.buildingBounds(raw,cache,[&,mission,key,index]{
                    BuildingTypeBoundsServices services;
                    if(supplyImages){services.primary9c=[&,index]{++imageCalls[index];return shpBoundsView(images[index]);};services.secondaryC0=[]{return ShpBoundsView{};};}
                    return mission->structureTypeImageBounds(key,services);
                });
            });};
        auto first=trial->missionWorld().structureSight(1019675),second=trial->missionWorld().structureSight(1019676);
        frame.center(first.position);first.fields.redraw75=1;second.fields.redraw75=128;
        frame.invalidateBuildings({0,0,683,480},{},bind(*trial));
        require(!first.fields.redraw75&&!second.fields.redraw75&&imageCalls==std::array<int,2>{1,1}&&frame.frameDirtyRegions().count>0,
                "Actual original-image Type bounds must compose into existing cache/dirty owners");
        const auto typeFirst=trial->missionWorld().structureSightType(1019675).imageBounds.bounds11ec;
        const auto typeSecond=trial->missionWorld().structureSightType(1019676).imageBounds.bounds11ec;
        require(typeFirst.width>0&&typeFirst.height>0&&typeSecond.width>0&&typeSecond.height>0&&typeFirst.width!=typeSecond.width&&
                first.fields.renderBounds.bounds50c.width==typeFirst.width&&second.fields.renderBounds.bounds50c.width==typeSecond.width,
                "Independent actual Type caches must retain the corresponding original image geometry");
        auto warm=trial->clone();trial.reset();supplyImages=false;frame.camera.x+=10;
        warm->missionWorld().structureSight(1019675).fields.redraw75=255;
        warm->missionWorld().structureSight(1019676).fields.redraw75=255;
        frame.invalidateBuildings({0,0,683,480},{},bind(*warm));
        require(!warm->missionWorld().structureSightState(1019675).redraw75&&!warm->missionWorld().structureSightState(1019676).redraw75&&
                imageCalls==std::array<int,2>{1,1}&&warm->missionWorld().structureSightType(1019675).imageBounds.bounds11ec.width==typeFirst.width,
                "Warm actual Type caches must survive source destruction and body-cache misses without image getters");
        require(snapshot(world)==before&&world.missionWorld().structureSightType(1019675).imageBounds.bounds11ec.width==0&&
                world.missionWorld().structureSightType(1019676).imageBounds.bounds11ec.width==0,
                "Original-image bounds integration must retain source Type/mission owners");
        std::cout<<"Actual Building Type bounds: original SHP metadata -> independent Type/body caches -> persistent dirty queue, warm clone/source destruction PASS (image loading/startup supplied; unscheduled)\n";
    }
    {
        const auto before=snapshot(world);auto trial=world.clone();Renderer frame(assets,1024,720,"Gold");
        const std::int32_t theater=0; // Supplied stock scenario/type startup.
        for(int key:{1019675,1019676}){
            auto& image=trial->missionWorld().structureTypeImageState(key);
            image.primary13eb=key==1019675?"CTARMY04.SHP":"CTARMY01.SHP";
            image.secondaryBf4=key==1019675?"CAARMY04":"CAARMY01";
            image.demand13e0=128;image.demand13e1=255;
        }
        auto& releaseType=const_cast<BootCampBuildingExpirationType&>(trial->missionWorld().structureSightType(1019675));
        releaseType.imageBounds.release13e2=128;
        auto bind=[&](BootCampWalkWorld& owner){auto* mission=&owner.missionWorld();
            return mission->buildingInvalidationRegistry([&,mission](int key,Coord raw,BuildingRenderBoundsState& cache)->const PixelRect&{
                return frame.buildingBounds(raw,cache,[&,mission,key]{
                    return mission->structureTypeImageBoundsFromAssets(key,assets.store,theater,.6);
                });
            });};
        frame.center(trial->missionWorld().structureSight(1019675).position);
        for(int key:{1019675,1019676})trial->missionWorld().structureSight(key).fields.redraw75=128;
        frame.invalidateBuildings({0,0,683,480},{},bind(*trial));
        const auto& first=trial->missionWorld().structureSightType(1019675);
        const auto& second=trial->missionWorld().structureSightType(1019676);
        require(first.images.primaryA4&&second.images.primaryA4&&first.images.primaryA4!=second.images.primaryA4&&
                first.images.ownedA8==1&&second.images.ownedA8==1&&first.imageBacking.size()==1&&second.imageBacking.size()==2&&
                !first.imageBounds.secondaryB98&&!first.imageBounds.flagB9c&&second.imageBounds.secondaryB98&&second.imageBounds.flagB9c==1&&
                first.images.startC8c==0&&first.images.countC90==3&&first.images.durationC94==179&&
                first.imageBounds.bounds11ec.width>0&&second.imageBounds.bounds11ec.width>0&&frame.frameDirtyRegions().count>0,
                "Actual demand getters must load separate primary/theater secondary identities, time animation and release transient secondary");
        const auto* primary=first.images.primaryA4;const auto* secondary=second.imageBounds.secondaryB98;
        auto warm=trial->clone();trial.reset();
        auto& warmType=const_cast<BootCampBuildingExpirationType&>(warm->missionWorld().structureSightType(1019675));
        warmType.imageBounds.bounds11ec={}; // Force Type miss, retain the actual shared loaded backing.
        const auto refreshed=warm->missionWorld().structureTypeImageBoundsFromAssets(1019675,assets.store,theater,.6);
        require(refreshed.width>0&&warmType.images.primaryA4==primary&&warmType.imageBacking.size()==1&&
                warm->missionWorld().structureSightType(1019676).imageBounds.secondaryB98==secondary,
                "Warm cloned Type must keep loaded primary valid after source destruction and release only its own transient secondary");
        frame.camera.x+=10;
        for(int key:{1019675,1019676})warm->missionWorld().structureSight(key).fields.redraw75=255;
        frame.invalidateBuildings({0,0,683,480},{},bind(*warm));
        require(!warm->missionWorld().structureSightState(1019675).redraw75&&warmType.imageBacking.size()==1&&
                warm->missionWorld().structureSightType(1019676).imageBacking.size()==2,
                "Camera/body cache miss must retain warm Type resources");
        auto missing=world.clone();auto& absent=missing->missionWorld().structureTypeImageState(1019675);
        absent.demand13e0=1;absent.primary13eb="zz_missing.shp";
        const auto empty=missing->missionWorld().structureTypeImageBoundsFromAssets(1019675,assets.store,theater,.6);
        require(!empty.width&&!empty.height&&!absent.primaryA4&&
                missing->missionWorld().structureSightType(1019675).imageBacking.empty(),
                "Absent original/generic files must return empty without invented SHP content");
        require(snapshot(world)==before&&!world.missionWorld().structureSightType(1019675).images.primaryA4&&
                world.missionWorld().structureSightType(1019675).imageBacking.empty(),
                "Explicit demand-loading checks must retain source mission/type owners");
        std::cout<<"Actual Building demand getters: original assets -> primary/theater secondary -> animation/type/body cache/dirty queue, transient release and warm clone/source destruction PASS (file services/startup supplied; unscheduled)\n";
    }
    {
        const auto before=snapshot(world);auto trial=world.clone();Renderer frame(assets,1024,720,"Gold");
        const std::int32_t theater=0;
        for(int key:{1019675,1019676}){
            auto& image=trial->missionWorld().structureTypeImageState(key);
            image.primary13eb=key==1019675?"CTARMY04.SHP":"CTARMY01.SHP";image.demand13e0=128;
            auto a=trial->missionWorld().structureSight(key);a.fields.redraw75=128;a.fields.radar5b7=0;
        }
        frame.center(trial->missionWorld().structureSight(1019675).position);
        std::vector<int> calls;bool mutateDraw=false;const PixelRect viewport{0,0,683,480};
        auto bind=[&](BootCampWalkWorld& owner,bool supplyDraw){auto* mission=&owner.missionWorld();
            std::function<void(int,PixelRect,int,int)> draw;
            if(supplyDraw)draw=[&,mission](int key,PixelRect r,int force,int zero){
                require(r.x==viewport.x&&r.y==viewport.y&&r.width==viewport.width&&r.height==viewport.height&&force==256&&zero==0,
                        "Building static must forward copied clip/full force/zero to required child");
                require(mission->structureSightState(key).redraw75==128||mutateDraw,
                        "Static drawing child must see original live redraw before clear");
                calls.push_back(key);if(mutateDraw)mission->structureSight(key).fields.redraw75=255;
            };
            return mission->buildingStaticRegistry([&,mission](int key,Coord raw,BuildingRenderBoundsState& cache)->const PixelRect&{
                return frame.buildingBounds(raw,cache,[&,mission,key]{return mission->structureTypeImageBoundsFromAssets(key,assets.store,theater,.6);});
            },draw);
        };
        const auto cellCount=trial->visibilityWorld().redrawQueue().countE0;
        const auto dirtyCount=frame.frameDirtyRegions().count;
        bool refused=false;try{scanStaticBuildings(viewport,viewport,256,[]{return PixelPoint{};},[]{return std::uint8_t(0);},bind(*trial,false));}
        catch(const std::invalid_argument&){refused=true;}
        require(refused&&trial->missionWorld().structureSightState(1019675).redraw75==128,
                "Missing actual Building drawing service must refuse without clearing actor redraw");
        scanStaticBuildings(viewport,viewport,256,[]{return PixelPoint{};},[]{return std::uint8_t(0);},bind(*trial,true));
        require(calls==std::vector<int>({1019675,1019676})&&!trial->missionWorld().structureSightState(1019675).redraw75&&
                !trial->missionWorld().structureSightState(1019676).redraw75,
                "Static Building pass must use forward actual registry and clear each actor after drawing service");
        calls.clear();mutateDraw=true;
        trial->missionWorld().structureSight(1019675).fields.radar5b7=128;
        scanStaticBuildings(viewport,viewport,256,[]{return PixelPoint{};},[]{return std::uint8_t(0);},bind(*trial,true));
        require(calls==std::vector<int>({1019676})&&!trial->missionWorld().structureSightState(1019676).redraw75,
                "Nonzero hidden byte must skip only that Building, and redraw0 must not suppress later drawing");
        auto warm=trial->clone();trial.reset();calls.clear();
        scanStaticBuildings(viewport,viewport,256,[]{return PixelPoint{};},[]{return std::uint8_t(255);},bind(*warm,true));
        require(calls==std::vector<int>({1019675,1019676})&&!warm->missionWorld().structureSightState(1019675).redraw75&&
                !warm->missionWorld().structureSightState(1019676).redraw75,
                "Raw hidden bypass and post-child clear must retain actual owners on warm clone after source destruction");
        require(warm->visibilityWorld().redrawQueue().countE0==cellCount&&frame.frameDirtyRegions().count==dirtyCount&&snapshot(world)==before,
                "Explicit Building scan must retain Cell/frame queues and source mission owners");
        std::cout<<"Actual Building static scan: shared forward owners, original SHP/type/body bounds, required draw refusal, hidden/bypass/raw force, clear-after-child and warm source destruction PASS (drawing child/startup supplied; unscheduled)\n";
    }
    {
        const auto before=snapshot(world);auto trial=world.clone();Renderer frame(assets,1024,720,"Gold");
        const std::int32_t theater=0;const PixelRect viewport{0,0,683,480};
        for(int key:{1019675,1019676}){
            auto& image=trial->missionWorld().structureTypeImageState(key);
            image.primary13eb=key==1019675?"CTARMY04.SHP":"CTARMY01.SHP";image.demand13e0=128;
            auto a=trial->missionWorld().structureSight(key);a.fields.redraw75=128;a.fields.marked74=1;a.fields.flag76=0;a.fields.radar5b7=0;
        }
        frame.center(trial->missionWorld().structureSight(1019675).position);
        std::vector<int> draws;std::uint8_t bypass=0;
        auto services=[&](BootCampWalkWorld& owner,int key,bool supplyDraw){auto* mission=&owner.missionWorld();BuildingVisibilityServices s;
            s.bypass=[&]{return bypass;};s.contextPresent=[]{return true;};
            s.bounds124=[&,mission,key]{auto a=mission->structureSight(key);return frame.buildingBounds(a.position,a.fields.renderBounds,
                [&,mission,key]{return mission->structureTypeImageBoundsFromAssets(key,assets.store,theater,.6);});};
            s.project6a29d0=[&](Coord p){return frame.projectFrameCoordinates(p);};
            if(supplyDraw)s.ordinary10c=[&,mission,key](PixelPoint& p,PixelRect& r){
                auto a=mission->structureSight(key);const auto expected=frame.projectFrameCoordinates(buildingRenderCoordinates(a.position));
                require(p==expected&&r.x==0&&r.y==0&&r.width==683&&r.height==480&&a.fields.redraw75==0,
                        "Actual parent must use the same raw coordinate/projection, clip and cleared redraw before ordinary child");
                draws.push_back(key);a.fields.redraw75=255;r={21,22,23,24};
            };
            return s;
        };
        auto bind=[&](BootCampWalkWorld& owner){auto* mission=&owner.missionWorld();
            return mission->buildingStaticRegistry([&,mission](int key,Coord raw,BuildingRenderBoundsState& cache)->const PixelRect&{
                return frame.buildingBounds(raw,cache,[&,mission,key]{return mission->structureTypeImageBoundsFromAssets(key,assets.store,theater,.6);});
            },[&,mission](int key,PixelRect clip,int force,int special){
                require(mission->drawStructureIfVisible(key,clip,viewport,force,special,services(owner,key,true)),
                        "Actual static traversal must enter complete Building parent before ordinary drawing request");
            });
        };
        const auto cells=trial->visibilityWorld().redrawQueue().countE0;const auto regions=frame.frameDirtyRegions().count;
        scanStaticBuildings(viewport,viewport,256,[]{return PixelPoint{};},[&]{return bypass;},bind(*trial));
        require(draws==std::vector<int>({1019675,1019676})&&!trial->missionWorld().structureSightState(1019675).redraw75&&
                !trial->missionWorld().structureSightState(1019676).redraw75,
                "Shared static/visibility parents must preserve forward identity and outer clear after child redraw mutation");
        auto& flags=trial->missionWorld().structureSight(1019675).fields;
        PixelRect clip=viewport;const auto gated=snapshot(*trial);
        require(!trial->missionWorld().drawStructureIfVisible(1019675,clip,viewport,256,0,services(*trial,1019675,false))&&snapshot(*trial)==gated,
                "Force256 low byte zero/redraw0 must return before modifying actual owners");
        flags.marked74=0;flags.flag76=128;flags.redraw75=255;
        require(!trial->missionWorld().drawStructureIfVisible(1019675,clip,viewport,1,0,services(*trial,1019675,false))&&flags.redraw75==255,
                "Actual marked/flag gates must retain redraw on early rejection");
        flags.marked74=1;flags.flag76=0;flags.radar5b7=128;
        require(trial->missionWorld().drawStructureIfVisible(1019675,clip,viewport,1,1,services(*trial,1019675,false))&&!flags.redraw75&&draws.size()==2,
                "Special hidden Building must return success without inventing a special drawing request");
        flags.radar5b7=0;flags.redraw75=128;bool refused=false;
        try{trial->missionWorld().drawStructureIfVisible(1019675,clip,viewport,1,0,services(*trial,1019675,false));}
        catch(const std::invalid_argument&){refused=true;}
        require(refused&&!flags.redraw75,"Missing ordinary drawing must refuse after the recovered parent clear");
        auto warm=trial->clone();trial.reset();draws.clear();bypass=255;
        for(int key:{1019675,1019676}){auto a=warm->missionWorld().structureSight(key);a.fields.marked74=0;a.fields.flag76=255;a.fields.redraw75=0;}
        scanStaticBuildings(viewport,viewport,256,[]{return PixelPoint{};},[&]{return bypass;},bind(*warm));
        require(draws==std::vector<int>({1019675,1019676})&&!warm->missionWorld().structureSightState(1019675).redraw75&&
                warm->visibilityWorld().redrawQueue().countE0==cells&&frame.frameDirtyRegions().count==regions&&snapshot(world)==before,
                "Actual bypass/cloned image backing and freshly bound parents must survive source destruction without scheduling queues/objectives");
        std::cout<<"Actual Building visibility parent: static traversal -> shared flags/SHP/type/body bounds -> actual coordinate/projection -> required ordinary child, low-byte gates/special hidden/clear ordering and warm clone PASS (final pixels/startup supplied; unscheduled)\n";
    }
    {
        const auto before=snapshot(world);auto trial=world.clone();double threshold=.5,alternate=.25;
        auto& mission=trial->missionWorld();auto a=mission.structureSight(1019675);
        auto& type=const_cast<BootCampBuildingExpirationType&>(mission.structureSightType(1019675));
        a.fields.frameE0=7;type.images.startC8c=3;type.images.countC90=6;
        a.discovery.mission98=0;
        require(mission.structureAnimationFrame(1019675,threshold,alternate)==7,"Actual frame must borrow E0");
        type.images.flag1351=128;
        require(mission.structureAnimationFrame(1019675,threshold,alternate)==1,"Actual Type reverse sequence must borrow existing image C8C/C90");
        a.discovery.mission98=-1;a.discovery.queuedA0=19;
        require(mission.structureAnimationFrame(1019675,threshold,alternate)==7,"Actual mission fallback19 must reverse the retained frame again");
        a.fields.stage42c=1;a.fields.frame4ec=31;a.fields.frame4f0=37;
        type.frameSelection.flag1359=128;type.frameSelection.flag135a=255;
        require(mission.structureAnimationFrame(1019675,threshold,alternate)==31,"First original frame override must win");
        type.frameSelection.flag1359=0;
        require(mission.structureAnimationFrame(1019675,threshold,alternate)==37,"Second original frame override must borrow actual4F0");
        type.frameSelection.flag135a=0;type.images.flag1351=0;type.frameSelection.flag121e=255;
        type.strengthA0=0; // Actual health/strength path, including original unordered0/0.
        // Set health through its existing lifetime owner; no drawing health mirror.
        auto& expiration=const_cast<BootCampBuildingExpirationState&>(mission.structureExpirationState(1019675));
        expiration.health6C=0;
        require(mission.structureAnimationFrame(1019675,threshold,alternate)==1,"Unordered actual health ratio must enter original alternate branch");
        type.frameSelection.flag121e=0;type.images.flag1351=128;type.images.count137c=INT32_MAX;
        require(mission.structureAnimationFrame(1019675,threshold,alternate)==INT32_MIN,"Actual damaged count+1 must wrap");
        auto warm=trial->clone();trial.reset();
        require(warm->missionWorld().structureAnimationFrame(1019675,threshold,alternate)==INT32_MIN&&snapshot(world)==before,
                "Frame query must rebind cloned Type/health/mission owners after source destruction and leave source isolated");
        std::cout<<"Actual Building frame selector: shared image sequence/Type/mission/health and override priority, unordered damage/wrapping, warm clone PASS (startup supplied; drawing unscheduled)\n";
    }
    {
        // Actual image68 selects and demand-loads on cold existing Type owners.
        {
            auto cold=world.clone();auto& mission=cold->missionWorld();int theater=0;
            for(int key:{1019675,1019676}){
                auto actor=mission.structureSight(key);auto& image=mission.structureTypeImageState(key);
                image.demand13e0=1;image.primary13eb=key==1019675?"ctarmy04.shp":"ctarmy01.shp";
                image.demand13e1=1;image.secondaryBf4=key==1019675?"ctarmy04":"ctarmy01";
                actor.fields.stage42c=0;actor.fields.image5b4=255;
                const auto* secondary=mission.structureImageFromAssets(key,assets.store,theater,.6);
                require(secondary&&!image.primaryA4&&mission.structureSightType(key).imageBacking.size()==1&&image.countC90>0,
                    "Zero stage must short-circuit flag and demand-load only the actual secondary Type image");
                actor.fields.stage42c=-1;actor.fields.image5b4=128;
                const auto* primary=mission.structureImageFromAssets(key,assets.store,theater,.6);
                require(primary&&primary==image.primaryA4&&primary!=secondary&&mission.structureSightType(key).imageBacking.size()==2,
                    "Raw nonzero stage/flag must demand-load the same owner's primary image");
                actor.fields.image5b4=0;
                require(mission.structureImageFromAssets(key,assets.store,theater,.6)==secondary&&mission.structureSightType(key).imageBacking.size()==2,
                    "Zero flag must select the resident secondary without duplicate host allocation");
            }
            auto warm=cold->clone();const auto* retained=mission.structureSightType(1019675).imageBounds.secondaryB98;cold.reset();
            require(warm->missionWorld().structureImageFromAssets(1019675,assets.store,theater,.6)==retained,
                "Selection must rebind clone owners and retain actual immutable backing after source destruction");
            auto& cloned=warm->missionWorld();
            auto& expiration=const_cast<BootCampBuildingExpirationState&>(cloned.structureExpirationState(1019675));
            const auto* savedType=expiration.type418;expiration.type418=cloned.structureExpirationState(1019676).type418;
            require(cloned.structureImageFromAssets(1019675,assets.store,theater,.6)==cloned.structureSightType(1019676).imageBounds.secondaryB98,
                "Selection must resolve the live actor Type association rather than a cached original Type");
            expiration.type418=nullptr;bool refused=false;
            try{(void)cloned.structureImageFromAssets(1019675,assets.store,theater,.6);}catch(const std::invalid_argument&){refused=true;}
            require(refused,"Foreign actual image Type must refuse");expiration.type418=savedType;
            auto missing=world.clone();auto& im=missing->missionWorld().structureTypeImageState(1019675);
            im.demand13e1=1;im.secondaryBf4="ZZNOTPRESENT";
            require(!missing->missionWorld().structureImageFromAssets(1019675,assets.store,theater,.6)&&
                    missing->missionWorld().structureSightType(1019675).imageBacking.empty(),
                "Missing actual first/fallback image must return null without creating backing");
        }
        const auto before=snapshot(world);auto trial=world.clone();Renderer frame(assets,1024,720,"Gold");
        {
            const auto input=assets.store.require("BUILDNGZ.SHP");
            require(assetSha256(input)=="f91653da1f2c4b8e823a7db6ffb5e4c0fc003a9e74eef920adcad2feec739490",
                "Depth image proof requires the exact supplied original asset");
            require(!frame.buildingDepthImage(),"Depth-image startup stays explicitly empty");
            auto first=frame.prepareBuildingDepthImage();
            require(first&&first->width==396&&first->height==477&&first->frames.size()==1&&first->frames[0].format==1,
                "Actual depth image must retain its raw canvas/frame metadata");
            // Hash derives from original458510 memory, not from this native loader.
            const auto expected="c83c79123de049c0fd63de84ba74c0f29965638754b1f46104747fc7376e4397";
            require(assetSha256(Data(first->frames[0].pixels))==expected,"Actual depth payload must match original initializer bytes");
            auto second=frame.prepareBuildingDepthImage();
            require(first!=second&&frame.buildingDepthImage()==second.get()&&
                    assetSha256(Data(second->frames[0].pixels))==expected&&assetSha256(Data(first->frames[0].pixels))==expected,
                "Reinitialization must replace the shared owner while retained immutable views remain valid");
            require(assetSha256(input)=="f91653da1f2c4b8e823a7db6ffb5e4c0fc003a9e74eef920adcad2feec739490",
                "Original archived depth-image bytes must remain unchanged");
        }
        double threshold=.5,alternate=.25;int theater=0;std::vector<int> draws;std::size_t actualBuildingPixels=0,actualDepthPixels=0;
        // Supplied scheme startup on the actual existing House. Recovering the
        // original scenario color loader remains separate from selection.
        const int goldScheme=int(std::distance(assets.playerColors.begin(),assets.playerColors.find("gold")));
        for(const auto& [id,h]:trial->missionWorld().houses())trial->missionWorld().house(id).radarScheme15f40=goldScheme;
        {
            auto& mission=trial->missionWorld();auto actor=mission.structureSight(1019675);
            auto select=[&]{auto s=frame.spriteConverterSelectionServices();s.ownerPredicate3d4=[](const void*){return std::uint8_t(128);};return mission.structureSpriteConverter(1019675,s);};
            require(select()==&frame.unitConverter(),"Actual owner scheme must select existing Gold converter");
            auto& h=mission.house(actor.discovery.owner);h.radarScheme15f40=0;
            auto table=frame.spriteConverterSelectionServices();
            require(select()==table.converter30c(table.schemeAtOffset(table.globalBackingAB6EFC(),0)),"Live House scheme change must select existing renderer slot");
            h.radarScheme15f40=goldScheme;
            auto refuse=[&](auto action){bool refused=false;try{action();}catch(const std::invalid_argument&){refused=true;}require(refused,"Actual converter selection must refuse missing/foreign backing");};
            refuse([&]{mission.structureSpriteConverter(1019675,{});});
            auto competing=frame.spriteConverterSelectionServices();competing.type80=[]{return nullptr;};
            refuse([&]{mission.structureSpriteConverter(1019675,competing);});
            const int owner=actor.discovery.owner;actor.discovery.owner=-1;refuse(select);actor.discovery.owner=owner;
            h.radarScheme15f40=-1;refuse(select);h.radarScheme15f40=goldScheme;
            auto& type=const_cast<BootCampBuildingExpirationType&>(mission.structureSightType(1019675));
            type.spriteSchemeTableB8c=&frame;refuse(select);type.spriteSchemeTableB8c=nullptr;
            require(select()==&frame.unitConverter(),"Selection refusal must preserve actual owner fields after restoration");
        }
        for(int key:{1019675,1019676}){
            auto& mission=trial->missionWorld();auto actor=mission.structureSight(key);auto& im=mission.structureTypeImageState(key);
            im.demand13e0=1;im.primary13eb=key==1019675?"ctarmy04.shp":"ctarmy01.shp";im.demand13e1=1;im.secondaryBf4=key==1019675?"ctarmy04":"ctarmy01";
            (void)mission.structureTypeImageBoundsFromAssets(key,assets.store,theater,.6);
            actor.discovery.mission98=0;actor.fields.frameE0=1;actor.fields.stage42c=0;
        }
        auto services=[&](BootCampWalkWorld& owner,int key){
            auto* mission=&owner.missionWorld();BuildingOrdinaryServices s;
            // Low-level diagnostic image service; Cell lighting borrows the actual map/renderer owners.
            s.image68=[mission,key]{return mission->structureSightType(key).imageBounds.secondaryB98;};
            s.imageCount=[mission,key](const void* p){const auto& t=mission->structureSightType(key);
                for(const auto& image:t.imageBacking)if(image.get()==p)return std::int16_t(image->frames.size());
                throw std::invalid_argument("Foreign actual Building image");};
            s.global85029c=[]{return 123;};s.cellLight548070=[&owner,&frame](std::uint32_t packed){
                return owner.visibilityWorld().buildingAmbient(packed,[&frame](const CellVisibilityState& c){return frame.buildingAmbient(c.identity,c.point);});};
            s.projectHeight6a2970=[](int z){return projectVisibilityHeight(z,.125);};
            s.draw6d1510=[&,mission,key](const BuildingSpriteRequest& r){
                const auto raw=mission->structureResidentState(key).position88;
                const bool auxiliary=r.tail[0]==0;
                const auto packed=buildingDrawCell(raw);const auto& cell=owner.visibilityWorld().at({std::bit_cast<std::int16_t>(std::uint16_t(packed)),std::bit_cast<std::int16_t>(std::uint16_t(packed>>16))});
                const int ambient=frame.buildingAmbient(cell.identity,cell.point);
                require(r.image==mission->structureSightType(key).imageBounds.secondaryB98&&r.frame==1&&
                        r.zero==0&&r.flags==256&&r.adjust==-(auxiliary?1:0)-projectVisibilityHeight(raw.z,.125)&&
                        r.tail[0]==(auxiliary?0:2)&&r.tail[1]==1&&r.tail[2]==ambient&&r.tail[3]==(auxiliary?0:123)&&r.tail[4]==0&&r.tail[7]==0,
                        "Actual ordinary parent must retain loaded-image/frame/height and all pending draw words");
                if(auxiliary)require(r.point.x==71&&r.point.y==72&&r.clip.height==99,
                        "Auxiliary draw must retain the main child's point/clip mutations");
                TechnoSpriteServices sprite;int blits=0;
                sprite.shadow7d88d5=[]{return std::uint8_t(1);};sprite.mode64=[](int a,int b){require(a==0&&b==0,"Actual sprite mode ABI");return 0;};
                sprite.converter1cc=[mission]{return static_cast<const void*>(mission);};
                sprite.currentHouseA35db4=[mission]{return static_cast<const void*>(mission);};
                sprite.ownerPredicate3d4=[](const void*){return std::uint8_t(1);};
                sprite.ownedHousePredicate4f52b0=[]{return std::uint8_t(0);};sprite.predicate32c=[]{return std::uint8_t(0);};
                sprite.project6a2970=[](int z){return projectVisibilityHeight(z,.125);};
                sprite.surface83995c=[&frame]{return static_cast<const void*>(&frame);};
                sprite.draw49eea0=[&](const TechnoSpriteBlit& b){
                    const auto& t=mission->structureSightType(key);const auto& fields=mission->structureSightState(key);
                    const int expectedLight=buildingSpriteBrightness(fields.spriteD8,r.tail[2]);
                    int count=-1;for(const auto& image:t.imageBacking)if(image.get()==r.image)count=int(image->frames.size());
                    require(count>=0,"Actual sprite image must remain owned");
                    require(b.image==r.image&&b.converter==mission&&b.surface==&frame&&&b.point!=&r.point&&&b.clip==&r.clip&&
                            b.zero==0&&b.flags==(blits?0x6e01:0x6e00)&&b.frame==(blits?r.frame+count/2:r.frame)&&
                            b.zAdjust==(blits?-4-projectVisibilityHeight(raw.z,.125):r.adjust-2)&&
                            b.gradient==(blits?0:r.tail[0])&&b.brightness==(blits?1000:expectedLight),
                            "Actual sprite must preserve loaded SHP, saved converter, main/shadow frames and full wrapper arguments");
                    ++blits;
                };
                mission->drawStructureSprite(key,r,sprite);
                require(blits==2,"Actual ordinary Building must compose through the full sprite parent to main/shadow requests");
                // First preserve the null-depth regression, then explicitly bind
                // the actual renderer resource to the original global token.
                auto pixelRequest=r;pixelRequest.tail[3]=0;
                sprite.converter1cc=[&frame,mission,key]{
                    auto selection=frame.spriteConverterSelectionServices();
                    selection.ownerPredicate3d4=[](const void*){return std::uint8_t(1);};
                    return mission->structureSpriteConverter(key,selection);
                };
                std::size_t pixelCalls=0;frame.drawMap();
                sprite.draw49eea0=[&](const TechnoSpriteBlit& b){
                    const ShpImage* image=nullptr;
                    for(const auto& backing:mission->structureSightType(key).imageBacking)if(backing.get()==b.image)image=backing.get();
                    require(image,"Pixel composition must resolve the saved actual SHP owner");
                    const auto* selected=static_cast<const UnitLightConverter*>(b.converter);
                    require(selected,"Actual selector must return a renderer converter");
                    const_cast<UnitLightConverter*>(selected)->field17c=-2147483647;
                    if(b.auxiliaryImage){
                        require(b.auxiliaryImage==frame.buildingDepthImage()&&b.tail[0]==123,
                            "Native auxiliary identity must accompany the unchanged diagnostic word");
                        for(int variant=0;variant<3;++variant){
                            auto bad=b;
                            if(variant==0)bad.auxiliaryImage=&frame;
                            if(variant==1)bad.auxiliaryImage=nullptr;
                            if(variant==2)bad.tail[0]=0;
                            bool refused=false;try{frame.drawBuildingSpritePixels(*image,bad);}catch(const std::invalid_argument&){refused=true;}
                            require(refused,"Foreign/missing/contradictory auxiliary binding must refuse");
                        }
                    }else require(!b.tail[0],"Shadow and null-depth body must retain null binding");
                    const auto visible=frame.drawBuildingSpritePixels(*image,b).visible;
                    actualBuildingPixels+=visible;if(b.auxiliaryImage)actualDepthPixels+=visible;++pixelCalls;
                    require(selected->field17c==b.zero,"Actual selected converter must retain each wrapper fixed-word store");
                };
                mission->drawStructureSprite(key,pixelRequest,sprite);
                require(pixelCalls==2,"Actual Building sprite must reach the shared renderer color/depth planes");
                if(r.tail[3]){
                    pixelRequest.tail[3]=r.tail[3];pixelRequest.auxiliaryImage=frame.buildingDepthImage();
                    frame.drawMap();pixelCalls=0;
                    mission->drawStructureSprite(key,pixelRequest,sprite);
                    require(pixelCalls==2,"Actual depth-bound Building must retain main/shadow traversal");
                }
                draws.push_back(key);r.point={71,72};r.clip.height=99;
            };return s;
        };
        auto bind=[&](BootCampWalkWorld& owner){auto* mission=&owner.missionWorld();BuildingVisibilityServices s;
            s.bypass=[]{return std::uint8_t(1);};

            s.project6a29d0=[&](Coord p){return frame.projectFrameCoordinates(p);};
            return mission->buildingStaticRegistry([&,mission](int key,Coord raw,BuildingRenderBoundsState& cache)->const PixelRect&{
                return frame.buildingBounds(raw,cache,[&,mission,key]{return mission->structureTypeImageBoundsFromAssets(key,assets.store,theater,.6);});},
                [&,mission,s](int key,PixelRect clip,int force,int special)mutable{
                    auto entered=s;entered.bounds124=[&,mission,key]{auto a=mission->structureSight(key);return frame.buildingBounds(a.position,a.fields.renderBounds,
                        [&,mission,key]{return mission->structureTypeImageBoundsFromAssets(key,assets.store,theater,.6);});};entered.ordinary10c=[&,mission,key](PixelPoint& p,PixelRect& r){
                        auto children=services(owner,key);children.image68={};children.imageCount={};
                        mission->drawStructureOrdinaryFromAssets(key,p,r,threshold,alternate,assets.store,theater,.6,std::move(children));};
                    PixelRect viewport{0,0,1024,720};require(mission->drawStructureIfVisible(key,clip,viewport,force,special,entered),"Actual ordinary visibility composition must enter");
                });};
        frame.center(trial->missionWorld().structureSight(1019675).position);
        PixelRect viewport{0,0,1024,720};const auto cellQueue=trial->visibilityWorld().redrawQueue().countE0;
        scanStaticBuildings(viewport,viewport,1,[]{return PixelPoint{};},[]{return std::uint8_t(1);},bind(*trial));
        require(draws==std::vector<int>({1019675,1019676}),"Both actual loaded Building owners must traverse static/visibility/ordinary parents in order");
        PixelPoint p{};PixelRect clip=viewport;
        auto& firstType=const_cast<BootCampBuildingExpirationType&>(trial->missionWorld().structureSightType(1019675));
        firstType.imageBounds.auxiliary11cc=firstType.imageBounds.secondaryB98;
        trial->missionWorld().structureSight(1019675).fields.stage42c=1;draws.clear();
        trial->missionWorld().drawStructureOrdinary(1019675,p,clip,threshold,alternate,services(*trial,1019675));
        require(draws==std::vector<int>({1019675,1019675}),"Shared auxiliary11CC and actual stage must cause the second ordinary layer");
        // Signed ambient remains live on the existing renderer light record.
        const auto raw=trial->missionWorld().structureResidentState(1019675).position88;
        const auto* source=assets.cell(raw.x/256,raw.y/256);require(source,"Actual Building light source Cell must exist");
        auto& light=const_cast<CellLight&>(frame.lightingAt(*source));const auto savedAmbient=light.ambient;
        trial->missionWorld().structureSight(1019675).fields.spriteD8=2;
        light.ambient=-32768;draws.clear();
        trial->missionWorld().drawStructureOrdinary(1019675,p,clip,threshold,alternate,services(*trial,1019675));
        require(draws==std::vector<int>({1019675,1019675}),"Both ordinary layers must read the live signed Cell10A owner");light.ambient=savedAmbient;
        const auto packedFallback=std::uint32_t(0x80008000);
        int fallbackCalls=0;
        require(trial->visibilityWorld().buildingAmbient(packedFallback,[&](const CellVisibilityState& c){
            ++fallbackCalls;require(c.identity==-1&&c.point==TerrainCellPoint{-32768,-32768},"Ambient fallback resolver must receive the actual mutated shared fallback");return std::int16_t(-123);
        })==-123&&fallbackCalls==1,"Explicit fallback ambient must follow the actual548070 fallback store");
        bool fallbackRefused=false;
        try{(void)trial->visibilityWorld().buildingAmbient(packedFallback,[&](const CellVisibilityState& c){return frame.buildingAmbient(c.identity,c.point);});}catch(const std::invalid_argument&){fallbackRefused=true;}
        require(fallbackRefused,"Unowned renderer fallback ambient must refuse instead of inventing a light value");
        const auto beforeMissing=trial->visibilityWorld().state().mapQueries;bool lightRefused=false;
        try{(void)trial->visibilityWorld().buildingAmbient(packedFallback,{});}catch(const std::invalid_argument&){lightRefused=true;}
        require(lightRefused&&trial->visibilityWorld().state().mapQueries==beforeMissing,"Missing ambient owner must refuse before map mutation");
        {
            BuildingSpriteRequest nullRequest{nullptr,0,p,clip};
            trial->missionWorld().drawStructureSprite(1019675,nullRequest,{});
            auto competingSprite=TechnoSpriteServices{};competingSprite.brightness3f8=[](int v){return v;};bool rejected=false;
            try{trial->missionWorld().drawStructureSprite(1019675,nullRequest,competingSprite);}catch(const std::invalid_argument&){rejected=true;}
            require(rejected,"Actual sprite must reject competing brightness ownership even on a null-image request");
            nullRequest.image=trial->missionWorld().structureSightType(1019675).imageBounds.secondaryB98;rejected=false;
            try{trial->missionWorld().drawStructureSprite(1019675,nullRequest,{});}catch(const std::invalid_argument&){rejected=true;}
            require(rejected,"Actual sprite must refuse entered missing services instead of fabricating pixels");
        }
        auto missing=services(*trial,1019675);missing.draw6d1510={};bool refused=false;
        try{trial->missionWorld().drawStructureOrdinary(1019675,p,clip,threshold,alternate,missing);}catch(const std::invalid_argument&){refused=true;}
        require(refused,"Entered missing pixel child must refuse");
        auto assetCompeting=services(*trial,1019675);refused=false;
        try{trial->missionWorld().drawStructureOrdinaryFromAssets(1019675,p,clip,threshold,alternate,assets.store,theater,.6,assetCompeting);}catch(const std::invalid_argument&){refused=true;}
        require(refused,"Actual asset ordinary composition must reject competing image callbacks");
        auto competing=services(*trial,1019675);competing.height1b8=[]{return 123;};refused=false;
        try{trial->missionWorld().drawStructureOrdinary(1019675,p,clip,threshold,alternate,competing);}catch(const std::invalid_argument&){refused=true;}
        require(refused,"Competing ordinary height owner must refuse");
        auto& expiration=const_cast<BootCampBuildingExpirationState&>(trial->missionWorld().structureExpirationState(1019675));
        const auto* originalType=expiration.type418;const auto* replacementType=trial->missionWorld().structureExpirationState(1019676).type418;
        auto changed=services(*trial,1019675);const auto imageGetter=changed.image68;
        changed.image68=[&]{const auto* image=imageGetter();expiration.type418=replacementType;return image;};refused=false;
        try{trial->missionWorld().drawStructureOrdinary(1019675,p,clip,threshold,alternate,changed);}catch(const std::invalid_argument&){refused=true;}
        require(refused,"Unjoined late Type-to-foundation mapping must refuse rather than reuse stale resident dimensions");
        expiration.type418=originalType;
        auto actor=trial->missionWorld().structureSight(1019675);actor.fields.stage42c=0;actor.discovery.mission98=19;refused=false;
        try{trial->missionWorld().drawStructureOrdinary(1019675,p,clip,threshold,alternate,services(*trial,1019675));}catch(const std::invalid_argument&){refused=true;}
        require(refused,"Unjoined actual454 animation association must refuse instead of fabricating animation owners");
        actor.fields.stage42c=1;actor.discovery.mission98=0;
        auto warm=trial->clone();trial.reset();draws.clear();
        scanStaticBuildings(viewport,viewport,1,[]{return PixelPoint{};},[]{return std::uint8_t(1);},bind(*warm));
        require(draws==std::vector<int>({1019675,1019675,1019676})&&warm->visibilityWorld().redrawQueue().countE0==cellQueue&&snapshot(world)==before,
                "Ordinary composition must rebind cloned image/Type/frame/coordinate owners and preserve source/queues after source destruction");
        require(actualBuildingPixels>0&&actualDepthPixels>0,"Actual Building sprite and depth-bound body must write visible pixels, not only empty requests");
        {
            // Queue an actual GI Cell through the already recovered redraw
            // producer, then consume requests against the existing Building
            // registry and renderer. This is explicit and does not drain queues.
            frame.center(warm->actor(player).ground.position);
            (void)BootCampWalkWorldInspection::requestActualViewportCell(*warm,player,frame.cellRedrawView());
            frame.center(warm->missionWorld().structureSight(1019675).position);
            const auto view=frame.cellRedrawView();const PixelRect logical{view.viewportX,view.viewportY,view.viewportWidth,view.viewportHeight};
            for(int key:{1019675,1019676})warm->missionWorld().structureSight(key).fields.redraw75=128;
            auto invalidation=warm->missionWorld().buildingInvalidationRegistry([&](int key,Coord raw,BuildingRenderBoundsState& cache)->const PixelRect&{
                return frame.buildingBounds(raw,cache,[&,key]{return warm->missionWorld().structureTypeImageBoundsFromAssets(key,assets.store,theater,.6);});});
            frame.invalidateBuildings(logical,{},invalidation);
            const auto queued=warm->visibilityWorld().redrawQueue();const auto regions=frame.frameDirtyRegions();
            require(queued.countE0>0&&regions.count>0,"Actual request composition must borrow populated Cell and dirty-region queues");
            const auto pixelsBefore=actualDepthPixels;draws.clear();frame.drawMap();int requests=0,aliases=0;
            frame.requestBuildingDraws(warm->visibilityWorld().redrawQueue(),[&](int id){return warm->visibilityWorld().redrawCellPoint(id);},{},{},1,
                [&](std::uint8_t force,const PixelRect& r,const PixelRect& clip){
                    ++requests;aliases+=&r==&clip;require(force==1,"Actual Building request must force the shared scan");
                    scanStaticBuildings(r,clip,force,[]{return PixelPoint{};},[]{return std::uint8_t(1);},bind(*warm));
                });
            require(requests>=queued.countE0+1&&aliases==1&&actualDepthPixels>pixelsBefore&&!draws.empty(),
                "Actual request producer must reach visible depth-bound Building pixels and retain one aliased full request");
            const auto& retained=warm->visibilityWorld().redrawQueue();
            require(retained.countE0==queued.countE0&&retained.cells==queued.cells&&retained.dirtyD7D==queued.dirtyD7D&&
                    frame.frameDirtyRegions().count==regions.count&&frame.frameDirtyRegions().slots.size()==regions.slots.size()&&snapshot(world)==before,
                "Building request consumption must preserve source owners, Cell queue and dirty-region count/capacity");
            for(std::size_t i=0;i<regions.slots.size();++i){const auto& a=regions.slots[i];const auto& b=frame.frameDirtyRegions().slots[i];
                require(a.bounds.x==b.bounds.x&&a.bounds.y==b.bounds.y&&a.bounds.width==b.bounds.width&&a.bounds.height==b.bounds.height&&a.flag==b.flag,
                    "Building requests must retain every dirty-region slot and unused tail");}
            // A fresh synchronous resolver must borrow the warm clone's Cells.
            auto requestClone=warm->clone();int cellRequests=0;
            frame.requestBuildingDraws(requestClone->visibilityWorld().redrawQueue(),[&](int id){
                ++cellRequests;require(requestClone->visibilityWorld().redrawCellPoint(id)==warm->visibilityWorld().redrawCellPoint(id),"Cloned request Cell values differ");
                return requestClone->visibilityWorld().redrawCellPoint(id);},{},{},256,[](auto,const auto&,const auto&){});
            require(cellRequests==queued.countE0,"Low-byte-zero request must still traverse the actual cloned Cell queue");
            int centers=0,terrainCalls=0;const auto depthRequestsBefore=frame.frameDepthRefreshCalls;
            const auto center=[&](int id){++centers;return warm->visibilityWorld().redrawCellCenter(id);};
            const auto cloneCenter=requestClone->visibilityWorld().redrawCellCenter(requestClone->visibilityWorld().redrawQueue().cells[0]);
            require(cloneCenter==warm->visibilityWorld().redrawCellCenter(queued.cells[0]),"Cloned center query must resolve its own actual Cell/floor owner");
            bool foreignCenter=false;try{(void)warm->visibilityWorld().redrawCellCenter(INT32_MAX);}catch(const std::invalid_argument&){foreignCenter=true;}
            require(foreignCenter,"Frame center must refuse a foreign Cell identity");
            const auto terrain=[&](int id,PixelPoint point,const PixelRect& clip){
                ++terrainCalls;(void)warm->visibilityWorld().redrawCellPoint(id);(void)point;
                require(&clip==&logical,"Frame Cell draw must retain caller clip identity");};
            frame.prepareFrameRegions(warm->visibilityWorld().redrawQueue(),center,1,0,0,logical,[]{return true;},terrain);
            require(centers==0&&terrainCalls==0&&frame.frameDepthRefreshCalls==depthRequestsBefore&&frame.frameDirtyRegions().count==regions.count,
                "Full-byte frame preparation must skip regions and Cells without resetting either queue");
            const auto previousDepth=std::vector<std::uint16_t>(frame.frameDepthPlane().begin(),frame.frameDepthPlane().end());
            frame.prepareFrameRegions(warm->visibilityWorld().redrawQueue(),center,256,0,0,logical,[]{return true;},terrain);
            const auto depthRequests=frame.frameDepthRefreshCalls-depthRequestsBefore;
            std::size_t cleared=0;for(std::size_t i=0;i<previousDepth.size();++i){const auto value=frame.frameDepthPlane()[i];
                if(value!=previousDepth[i]){++cleared;require(value==65535,"Recovered depth refresh must store only all-one words");}}
            require(cleared>0&&frame.frameDepthLockLevel()==0,"Actual prepared regions must clear existing depth pixels and restore the same lock owner");
            require(centers==queued.countE0&&terrainCalls==queued.countE0&&depthRequests>0&&depthRequests==frame.frameDirtyRegions().count,
                "Actual region preparation must clip the same dirty owner and visit actual queued Cells");
            const auto& prepared=frame.frameDirtyRegions();
            for(int i=0;i<prepared.count;++i){const auto r=prepared.slots.at(std::size_t(i)).bounds;
                require(r.x>=0&&r.y>=0&&r.width>0&&r.height>0&&r.x+r.width<=logical.width&&r.y+r.height<=logical.height,
                    "Actual prepared regions must be viewport-local intersections");}
            const auto writesBefore=actualDepthPixels; // Retain the refreshed plane for the actual Building draw.
            frame.requestBuildingDraws(warm->visibilityWorld().redrawQueue(),[&](int id){return warm->visibilityWorld().redrawCellPoint(id);},{},{},0,
                [&](std::uint8_t force,const PixelRect& r,const PixelRect& c){scanStaticBuildings(r,c,force,[]{return PixelPoint{};},[]{return std::uint8_t(1);},bind(*warm));});
            require(actualDepthPixels>writesBefore,"Prepared shared region owner must feed the existing visible Building draw chain");
            // Explicit original6A3EF0 consumes these same retained queues. Only
            // alpha4110B0 is bound to pixels; other draw children record requests.
            // Building invalidation correctly produced flag0. Supply one flag1
            // request through the recovered registration kernel on this owner;
            // its ordinary frame/camera producer remains outside this proof.
            frame.registerFrameDirtyRegion({2,3,8,4},1);
            const auto retainedRegions=frame.frameDirtyRegions();
            const auto retainedColors=std::vector<std::uint16_t>(frame.frameColorPlane().begin(),frame.frameColorPlane().end());
            const auto retainedDepth=std::vector<std::uint16_t>(frame.frameDepthPlane().begin(),frame.frameDepthPlane().end());
            int terrainRequests=0,animationRequests=0,rectangleRequests=0;std::size_t alphaStores=0;
            int flagged=0;for(int i=0;i<retainedRegions.count;++i)flagged+=bool(retainedRegions.slots.at(std::size_t(i)).flag);
            require(flagged>0,"Actual prepared dirty queue must contain a flagged alpha region");
            const auto alphaTrace=[&](auto at,auto n,auto value){++alphaStores;
                require(n==2||n==4,"Alpha refresh must use word/dword stores");
                require(value==(n==2?127u:0x007f007fu),"Alpha refresh must retain the original sentinel");
                require(std::uint64_t(at)+n<=frame.frameAlphaPlane().size()*2,"Alpha store must use retained backing");};
            std::size_t visibilityPixels=0;
            const auto visibilityBefore=warm->visibilityWorld().state();
            const auto terrainDraw=[&](int id,PixelPoint p,const PixelRect& r){
                ++terrainRequests;require(&r==&logical,"Terrain caller clip identity differs");
                warm->visibilityWorld().drawCellVisibility(id,p,r,frame,[&](auto,auto n,auto){
                    require(n==2,"Visibility raster must write alpha words");++visibilityPixels;
                });
            };
            // Nonempty diagnostic AlphaImage association on the actual structure
            // identity and retained Renderer alpha plane. Type+AC asset loading,
            // object startup and mask association remain supplied.
            Bytes animationImage(32+60*30,63);std::fill_n(animationImage.begin(),32,0);
            animationImage[2]=60;animationImage[4]=30;animationImage[6]=1;animationImage[12]=60;animationImage[14]=30;animationImage[28]=32;
            std::array<std::uint8_t,1800> animationMask{};
            for(std::size_t i=0;i<animationMask.size();++i)animationMask[i]=(i%3==0)?0x20:0;
            AlphaAnimationRecord animationRecord;animationRecord.flags14=255;
            std::array<AlphaAnimationRecord*,1> animationSlots{};std::span<AlphaAnimationRecord*> animationBacking=animationSlots;
            std::array<const void*,1> genericSlots{};std::span<const void*> genericBacking=genericSlots;
            int animationCount=0,genericCount=0,animationCapacity=1,genericCapacity=1,animationGrow=0,genericGrow=0,animationFrees=0;
            std::uint8_t animationAllocated=0,genericAllocated=0;
            AlphaAnimationRegistryView<AlphaAnimationRecord*> animationRegistry{{animationCount,animationBacking,&animationCount},animationCapacity,animationAllocated,animationGrow,{}};
            AlphaAnimationRegistryView<const void*> genericRegistry{{genericCount,genericBacking,&genericCount},genericCapacity,genericAllocated,genericGrow,{}};
            AlphaAnimationLifecycleServices lifecycle{animationRegistry,genericRegistry,{},{},{},{},{}};
            lifecycle.freeRecord=[&](auto& record){require(&record==&animationRecord,"Cleanup must delete the constructed record identity");++animationFrees;};
            AlphaAnimationServices animationServices;
            animationServices.count=[&]{return animationCount;};animationServices.backing=[&]{return animationBacking;};
            animationServices.tileMask=animationMask;int imageQueries=0;std::size_t animationPixels=0;
            animationServices.typeImage84=[&](const void* associated){
                require(associated==warm->missionWorld().structureResident(1019675).identity,"Animation must retain actual associated structure identity");
                ++imageQueries;return std::span<const std::uint8_t>(animationImage);};
            lifecycle.typeImage84=animationServices.typeImage84;
            const auto associatedResident=warm->missionWorld().structureResident(1019675);
            std::int32_t alphaLoading=1;int allocations=0;AlphaAnimationRecord* constructed=nullptr;
            ObjectAlphaPlacementServices placement{alphaLoading};
            placement.coordinates48=[&](const void* identity){require(identity==associatedResident.identity,"Alpha producer must borrow actual structure coordinates");return associatedResident.position88;};
            placement.project6a29d0=[&](Coord p){return frame.projectFrameCoordinates(p);};
            placement.tacticalOrigin=[&]{const auto v=frame.cellRedrawView();return PixelPoint{v.originB0,v.originB4};};
            placement.image84=animationServices.typeImage84;
            placement.allocate=[&](std::uint32_t size){require(size==64,"Alpha producer allocation size differs");++allocations;return &animationRecord;};
            placement.construct=[&](auto& record,const void* identity,int x,int y){constructed=frame.constructAlphaAnimation(record,identity,x,y,false,lifecycle);};
            placement.register6a3020=[&](auto,auto){throw std::runtime_error("Loading alpha placement must not enqueue a redraw");};
            placeObjectAlpha(associatedResident.identity,placement);
            const auto projectedAlpha=frame.projectFrameCoordinates(associatedResident.position88);
            const auto alphaOrigin=placement.tacticalOrigin();
            require(allocations==1&&animationRecord.bounds28.x==fillSub(fillAdd(projectedAlpha.x,alphaOrigin.x),30)&&
                animationRecord.bounds28.y==fillSub(fillAdd(projectedAlpha.y,alphaOrigin.y),15),
                "Alpha producer must center the original whole canvas on the actual shared coordinate/projection owners");
            require(constructed==&animationRecord&&animationCount==1&&genericCount==1&&animationSlots[0]==constructed&&genericSlots[0]==constructed&&
                animationRecord.bounds28.width==60&&animationRecord.bounds28.height==30&&animationRecord.flags14==248&&imageQueries==2,
                "Recovered placement/constructor must retain independent image queries and register one shared record before lazy table startup");
            const auto anchorAnimation=[&](PixelPoint p){const auto v=frame.cellRedrawView();
                animationRecord.bounds28={v.originB0+p.x-v.viewportX,v.originB4+p.y-v.viewportY,60,30};};
            const auto animationTrace=[&](auto at,auto n,auto){require(n==2&&std::uint64_t(at)+n<=frame.frameAlphaPlane().size()*2,"Animation must use retained alpha words");++animationPixels;};
            const auto animation=[&](PixelPoint p,const PixelRect& r){
                ++animationRequests;require(&r==&logical,"Animation caller clip identity differs");anchorAnimation(p);
                frame.drawAlphaAnimations(true,p,r,animationServices,animationTrace);
            };
            frame.requestTerrainDraws(warm->visibilityWorld().redrawQueue(),center,{},{},logical,256,[]{return true;},terrainDraw,animation,
                [&](const PixelRect&){++rectangleRequests;},alphaTrace);
            require(terrainRequests==queued.countE0&&animationRequests==queued.countE0&&rectangleRequests==flagged&&alphaStores>0,
                "Actual terrain caller must visit Cells then flagged regions and write its existing alpha plane");
            const auto visibilityAfter=warm->visibilityWorld().state();
            require(visibilityPixels>0&&visibilityAfter.maskCalls==visibilityBefore.maskCalls+2*queued.countE0&&
                visibilityAfter.discoveryParents==visibilityBefore.discoveryParents&&visibilityAfter.discoveredResidents==visibilityBefore.discoveredResidents,
                "Actual queued Cell drawing must borrow both masks and write existing alpha without discovery or objective production");
            bool foreignVisibility=false;try{warm->visibilityWorld().drawCellVisibility(INT32_MAX,{},logical,frame);}catch(const std::invalid_argument&){foreignVisibility=true;}
            require(foreignVisibility,"Cell visibility drawing must refuse foreign identities");
            // Fog is disabled in Day1 startup. Supply that separate flag only
            // on a clone to exercise both actual raster owners synchronously.
            auto fogWorld=warm->clone();const auto warmBeforeFog=snapshot(*warm);
            BootCampWalkWorldInspection::scenario(*fogWorld).at(1)|=0x10;
            std::size_t fogPixels=0;const auto fogState=fogWorld->visibilityWorld().state();
            fogWorld->visibilityWorld().drawCellVisibility(queued.cells[0],{20,20},logical,frame,
                [&](auto,auto,auto){++fogPixels;});
            require(fogPixels>0&&fogWorld->visibilityWorld().state().maskCalls==fogState.maskCalls+2&&snapshot(*warm)==warmBeforeFog,
                "Explicit fog-enabled clone must use its own Cell masks and shared alpha effect without mutating its source owner");
            require(animationPixels>0&&imageQueries==2,"Actual queued point animation must draw its constructed cached registry without another Type query");
            // Rectangle pass independently resolves the supplied Type child and
            // deliberately draws an expired record; point pass did not expire it.
            animationRecord.image38={};animationRecord.expired3c=128;anchorAnimation({2,3});
            const auto previousAnimationPixels=animationPixels;
            terrainRequests=animationRequests=rectangleRequests=0;alphaStores=0;
            std::size_t rectanglePixels=0;int rectangleAnimationRequests=0;
            const auto beforeRectangleMasks=warm->visibilityWorld().state().maskCalls;
            frame.requestTerrainDraws(warm->visibilityWorld().redrawQueue(),center,{},{},logical,1,[]{return true;},terrainDraw,animation,
                [&](const PixelRect& rectangle){
                    ++rectangleRequests;
                    warm->visibilityWorld().drawVisibilityRectangle(frame,rectangle,[]{return true;},
                        [&](const PixelRect& tail){++rectangleAnimationRequests;require(&tail==&rectangle,"Rectangle animation must retain request identity");
                            frame.drawAlphaAnimations(false,{},tail,animationServices,animationTrace);},
                        [&](auto,auto n,auto){require(n==2,"Rectangle drawing must write alpha words");++rectanglePixels;});
                },alphaTrace);
            require(!terrainRequests&&!animationRequests&&rectangleRequests==flagged+1&&alphaStores>0,
                "Full terrain redraw must still refresh flagged dirty regions after its viewport request");
            require(animationPixels>previousAnimationPixels&&imageQueries==3&&!animationRecord.image38.empty(),
                "Actual full/dirty rectangle animation must lazily cache once and draw expired records on retained alpha");
            require(rectanglePixels>0&&rectangleAnimationRequests==rectangleRequests&&
                warm->visibilityWorld().state().maskCalls>beforeRectangleMasks,
                "Full/dirty rectangle traversal must reach actual shared Cell masks and alpha pixels, then request each animation tail");
            expireAlphaAnimation(animationRecord,warm->missionWorld().structureResident(1019675).identity,0);
            require(animationRecord.expired3c==1,"Actual associated expiration must publish the expired byte");
            frame.cleanupAlphaAnimations(lifecycle);
            require(animationCount==0&&genericCount==0&&animationFrees==1&&animationSlots[0]==&animationRecord&&genericSlots[0]==&animationRecord,
                "Recovered cleanup must remove this same drawing record from both physical registries before free, retaining capacity tails");
            require(frame.frameDirtyRegions().count==retainedRegions.count&&frame.frameDirtyRegions().slots.size()==retainedRegions.slots.size()&&
                std::equal(retainedColors.begin(),retainedColors.end(),frame.frameColorPlane().begin())&&
                std::equal(retainedDepth.begin(),retainedDepth.end(),frame.frameDepthPlane().begin())&&frame.terrainAlphaLock()==0,
                "Explicit terrain requests must retain colors/depth, dirty owners and actual alpha lock");
            for(std::size_t i=0;i<retainedRegions.slots.size();++i){const auto& a=retainedRegions.slots[i];const auto& b=frame.frameDirtyRegions().slots[i];
                require(a.bounds.x==b.bounds.x&&a.bounds.y==b.bounds.y&&a.bounds.width==b.bounds.width&&a.bounds.height==b.bounds.height&&a.flag==b.flag,
                    "Terrain caller must preserve every actual dirty slot and capacity tail");}
            const auto tail=frame.frameDirtyRegions().slots.back();
            frame.prepareFrameRegions(warm->visibilityWorld().redrawQueue(),center,0,logical.width+65536,0,logical,[]{return false;},{});
            const auto last=frame.frameDirtyRegions().slots.back();
            require(frame.frameDirtyRegions().count==0&&tail.bounds.x==last.bounds.x&&tail.bounds.y==last.bounds.y&&tail.bounds.width==last.bounds.width&&tail.bounds.height==last.bounds.height&&tail.flag==last.flag&&
                    warm->visibilityWorld().redrawQueue().countE0==queued.countE0&&warm->visibilityWorld().redrawQueue().cells==queued.cells&&snapshot(world)==before,
                "Frame preparation must remove offscreen regions through count/shift policy, retain capacity tails and preserve actual Cells/source");

        }
        std::cout<<"Actual Building requests/region/depth refresh: shared Cell/dirty queues -> static/visibility/ordinary -> Techno -> selected converter/depth pixels, retained queues and warm binding PASS (startup/invocation supplied; unscheduled)\n";
    }
    {
        const auto before=snapshot(world);auto scoped=world.clone();
        Renderer cellFrame(assets,320,240,"Gold");cellFrame.center(scoped->actor(player).ground.position);cellFrame.drawMap();
        const int id=BootCampWalkWorldInspection::requestActualViewportCell(*scoped,player,cellFrame.cellRedrawView());
        const auto savedQueue=scoped->visibilityWorld().redrawQueue();
        const auto colors=std::vector<std::uint16_t>(cellFrame.frameColorPlane().begin(),cellFrame.frameColorPlane().end());
        const auto alpha=std::vector<std::uint16_t>(cellFrame.frameAlphaPlane().begin(),cellFrame.frameAlphaPlane().end());
        const auto depth=std::vector<std::uint16_t>(cellFrame.frameDepthPlane().begin(),cellFrame.frameDepthPlane().end());
        const auto view=cellFrame.cellRedrawView();PixelRect clip{0,0,view.viewportWidth,view.viewportHeight};
        std::size_t stores=0;int calls=0;
        auto terrain=[&](int cell,PixelPoint p,const PixelRect& r){++calls;
            cellFrame.refreshCellTerrainDepth(cell,scoped->visibilityWorld().redrawCellPoint(cell),scoped->visibilityWorld().redrawCellLevel(cell),p,r,
                [&](auto,auto n,auto value){++stores;require(n==2&&value==65535,"Terrain pass must store depth words only");});};
        cellFrame.prepareFrameRegions(scoped->visibilityWorld().redrawQueue(),[&](int cell){return scoped->visibilityWorld().redrawCellCenter(cell);},
            0,0,0,clip,[]{return true;},terrain);
        std::size_t changed=0;for(std::size_t i=0;i<depth.size();++i)if(depth[i]!=cellFrame.frameDepthPlane()[i]){
            ++changed;require(cellFrame.frameDepthPlane()[i]==65535,"Terrain pass modified a depth word incorrectly");}
        require(calls==savedQueue.countE0&&stores==900&&changed>0&&cellFrame.frameDepthRefreshCalls==0,
            "Actual queued GI Cell must reach depth-only diamond without rectangular refresh or drawMap restoration");
        require(std::equal(colors.begin(),colors.end(),cellFrame.frameColorPlane().begin())&&std::equal(alpha.begin(),alpha.end(),cellFrame.frameAlphaPlane().begin())&&
            cellFrame.terrainDepthReferences()==1&&cellFrame.terrainColorLock()==0&&cellFrame.terrainAlphaLock()==0&&cellFrame.frameDepthLockLevel()==0,
            "Terrain depth must preserve color/alpha planes and restore actual retained cache/stock locks");
        const auto beforeScroll=std::vector<std::uint16_t>(cellFrame.frameDepthPlane().begin(),cellFrame.frameDepthPlane().end());
        bool sawAlpha=false;std::array<std::size_t,2> planeStores{};
        const auto planeTrace=[&](bool alpha,std::uint32_t,unsigned n,std::uint32_t value){
            require(alpha||!sawAlpha,"Frame plane operations must keep depth before alpha");sawAlpha|=alpha;++planeStores[alpha];
            require(n==2||n==4,"Frame planes must use word/dword stores");
            require(value==(alpha?(n==2?127u:0x007f007fu):(n==2?65535u:UINT32_MAX)),"Frame plane store color differs");
        };
        cellFrame.scrollFramePlanes({1,1},planeTrace);
        const auto offset=std::uint32_t(2*(view.viewportWidth+1));
        std::size_t scrollChanged=0;for(std::size_t i=0;i<beforeScroll.size();++i)scrollChanged+=beforeScroll[i]!=cellFrame.frameDepthPlane()[i];
        require(planeStores[0]>0&&planeStores[1]>0&&scrollChanged>0&&cellFrame.frameDepthOffset()==offset&&cellFrame.frameAlphaOffset()==offset&&
            cellFrame.frameDepthBase()==32767&&cellFrame.frameAlphaBase()==32767,"Actual scroll must mutate existing planes and both persistent offsets/bases");
        sawAlpha=false;planeStores={};cellFrame.clearFramePlanes(planeTrace);
        require(std::all_of(cellFrame.frameDepthPlane().begin(),cellFrame.frameDepthPlane().end(),[](auto p){return p==65535;})&&
            std::all_of(cellFrame.frameAlphaPlane().begin(),cellFrame.frameAlphaPlane().end(),[](auto p){return p==127;})&&
            cellFrame.frameDepthOffset()==offset&&cellFrame.frameAlphaOffset()==offset&&cellFrame.frameDepthBase()==32767&&cellFrame.frameAlphaBase()==32767,
            "Complete full clear must fill both existing planes while retaining recovered scroll state");
        std::optional<std::uint32_t> refreshed;
        cellFrame.refreshFrameDepth({0,0,2,1},[&](auto p,auto,auto){if(!refreshed)refreshed=p;});
        require(refreshed==offset&&cellFrame.frameDepthLockLevel()==0&&cellFrame.terrainAlphaLock()==0&&
            std::equal(colors.begin(),colors.end(),cellFrame.frameColorPlane().begin()),"Existing refresh must use the same live depth offset and leave color/locks intact");
        std::optional<std::uint32_t> alphaRefreshed;
        cellFrame.refreshFrameAlpha({0,0,2,1},[&](auto at,auto,auto){if(!alphaRefreshed)alphaRefreshed=at;});
        require(alphaRefreshed==offset&&cellFrame.terrainAlphaLock()==0,"Alpha refresh must consume the same retained nonzero scroll offset");
        auto clone=scoped->clone();require(clone->visibilityWorld().redrawCellLevel(id)==scoped->visibilityWorld().redrawCellLevel(id),"Clone terrain must bind its own Cell level");
        bool foreign=false;try{cellFrame.refreshCellTerrainDepth(INT32_MAX,{},0,{},clip);}catch(const std::invalid_argument&){foreign=true;}
        bool wrong=false;try{cellFrame.refreshCellTerrainDepth(id,{0,0},0,{},clip);}catch(const std::invalid_argument&){wrong=true;}
        require(foreign&&wrong&&scoped->visibilityWorld().redrawQueue().countE0==savedQueue.countE0&&
            scoped->visibilityWorld().redrawQueue().cells==savedQueue.cells&&snapshot(world)==before,
            "Terrain depth must refuse foreign Cell bindings and preserve actual queues/source owners");
        std::cout<<"Actual Cell depth pass: queued GI ->4754B0 entered TMP depth diamond, existing planes/cache/locks plus complete clear/scroll state, retained queue/source PASS (startup supplied; unscheduled)\n";
    }
    {
        const auto before=snapshot(world);auto scoped=world.clone();
        {
            Renderer matrixViewport(assets,1024,720,"Gold");
            matrixViewport.camera={317,-923,1};
            const auto& projected=matrixViewport.tacticalViewport();
            // Joined original6A9170 -> 591380 -> FTOL with these supplied
            // planar coefficients gives these six fields. Original matrix
            // initialization is not established by this composition check.
            require(projected.originX==-195&&projected.originY==-1283&&
                    projected.cellX==-48&&projected.cellY==-39&&projected.columns==19&&projected.rows==52,
                    "Actual renderer must compose recovered affine transform below viewport producer");
        }
        Renderer viewport(assets,321,241,"Gold");viewport.center(scoped->actor(player).ground.position);viewport.camera.zoom=1.5;
        const auto view=viewport.cellRedrawView();const auto& state=viewport.tacticalViewport();
        require(view.viewportWidth==214&&view.viewportHeight==161&&state.columns==5&&state.rows==14&&
                view.originB0==int(std::lround(viewport.camera.x))-107&&view.originB4==int(std::lround(viewport.camera.y))-80,
                "Actual renderer must use recovered viewport origin/dimension producer");
        const int id=BootCampWalkWorldInspection::requestActualViewportCell(*scoped,player,view);
        const auto& queue=scoped->visibilityWorld().redrawQueue();
        require(queue.countE0==1&&queue.cells[0]==id,"Actual camera viewport must queue the actual centered GI Cell");
        viewport.camera.x+=100000;viewport.camera.y+=100000;scoped->step();
        (void)BootCampWalkWorldInspection::requestActualViewportCell(*scoped,player,viewport.cellRedrawView());
        require(queue.countE0==1,"Offscreen camera viewport must preserve queue while stamping the Cell");
        viewport.center(scoped->actor(player).ground.position);viewport.camera.zoom=2;scoped->step();
        (void)BootCampWalkWorldInspection::requestActualViewportCell(*scoped,player,viewport.cellRedrawView());
        require(queue.countE0==2&&queue.cells[1]==id&&viewport.cellRedrawView().viewportWidth==161&&snapshot(world)==before,
                "Camera return/zoom must refresh actual viewport and retain prior queue without source mutation");
        std::cout<<"Actual camera viewport -> shared Cell redraw: center/pan/zoom, clipping/frame stamps, retained queue and source isolation PASS (inverse matrix supplied)\n";
    }
    {
        const auto before=snapshot(world);auto redraw=world.clone();
        BootCampWalkWorldInspection::markRedrawBindingCheck(*redraw,player);
        require(snapshot(world)==before,"Actual Mark redraw checks changed source owners");
        std::cout<<"Actual GI Mark redraw: shared Tactical, actor-before-map order, raw gate/repeat, warm/source-destruction isolation and animation refusal PASS\n";
    }
    {
        const auto before=snapshot(world);auto dirty=world.clone();
        BootCampWalkWorldInspection::dirtyBindingCheck(*dirty,player);
        require(snapshot(world)==before,"Actual dirty binding checks changed source owners");
        std::cout<<"Actual crossing dirty: live Cell/fallback fields, resident refusal, clone/source-destruction isolation PASS\n";
    }
    for(int d=0;d<8;++d){const auto [dx,dy]=directionOffset(d);BootCampWalkWorld trial(assets,mission,source,rules,art);
        int dirtyCalls=0;BootCampWalkWorldInspection::observeCrossingDirty(trial,player,dirtyCalls);
        require(trial.move(player,57+dx*2,89+dy*2,status),"Every two-Cell starting direction must be usable");++acceptedRoutes;
        const int targetSlot=(89+dy*2)*512+(57+dx*2);const auto* target=trial.map().table.at(std::size_t(targetSlot));
        require(target&&trial.actor(player).target494==target&&target->position==MapInputPosition{std::int16_t(57+dx*2),std::int16_t(89+dy*2)},
                "Accepted route must retain the selected mutable-map Cell identity");
        require(trial.actor(player).walk.destination.x==(57+dx*2)*256+128&&
                trial.actor(player).walk.destination.y==(89+dy*2)*256+128,
                "Accepted Cell target must supply its center coordinates");
        BootCampWalkWorldInspection::saltRecalculationBuffers(trial,{57,89});
        BootCampWalkWorldInspection::saltRecalculationBuffers(trial,target->position);
        const auto before=snapshot(trial);require(!trial.move(player,57,89,status),"Moving retarget must refuse");
        require(snapshot(trial)==before,"Moving retarget changed live state");
        finish(trial,player);const auto p=trial.actor(player).ground.position;
        require(dirtyCalls>0,"Actual GI journey must invoke recovered dirty callback at Cell crossings");
        // Independent image observation: GI Ready/Walk directions are screen
        // N,NW,W,SW,S,SE,E,NE. Real route1 moves right; route5 moves left.
        constexpr std::array<unsigned,8> spriteDirections{7,6,5,4,3,2,1,0};
        require(giSpriteDirection(trial.actor(player).body.current(trial.tick()))==spriteDirections[std::size_t(d)],
                "Actual GI movement must select the sprite facing along its screen direction");
        require(p.x/256==57+dx*2&&p.y/256==89+dy*2,"Accepted route must arrive in selected Cell");
        for(const auto point:{MapInputPosition{57,89},target->position}){
            const auto& actual=trial.map();const auto* input=actual.table.at(std::size_t(int(point.y)*512+point.x));
            const int slot=mapAttributeBufferIndex(point,actual.width,actual.height,int(actual.buffer4.size()/4));
            const auto* attributes=actual.find(*input);
            require(attributes&&actual.buffer4[slot*4]==attributes->passability&&
                    actual.buffer4[slot*4+1]==std::uint8_t(input->level)&&actual.buffer10[slot*10+8]==std::uint8_t(input->level),
                    "Actual GI Mark removal/arrival must replace salted records in the existing map buffers");
        }

        require(trial.actor(player).ground.marked74&&trial.actor(player).object.next==-1,"Arrived GI must remain in map membership");
        require(trial.residentHead({57,89})!=player&&
                trial.residentHead({std::int16_t(p.x/256),std::int16_t(p.y/256)})==player&&
                trial.composeClosestResident(p)==player,
                "Visibility must follow actual old-head removal and new-head placement after ordinary movement");
        for(const auto& [id,a]:world.actors())if(id!=player)require(trial.actor(id).ground.position==a.ground.position,"Other GI placement changed");
    }
    const auto before=snapshot(world);
    for(const auto [x,y]:{std::pair{INT32_MAX,INT32_MIN},std::pair{57,89},std::pair{56,85},std::pair{100,89},std::pair{0,0}}){
        require(!world.move(player,x,y,status),"Unsupported destination accepted");require(snapshot(world)==before,"Refused destination changed live owners");
    }
    for(const auto& [id,a]:world.actors())if(id!=player){
        require(!world.move(id,70,93,status)&&!world.stop(id,status),"Non-player GI accepted commands");require(snapshot(world)==before,"Non-player command changed live owners");
    }
    require(world.move(player,59,89,status),"Stop test needs accepted route");
    for(int n=0;world.actor(player).walk.head==Coord{}&&n<32;++n)world.step();
    const auto head=world.actor(player).walk.head;require(head!=Coord{},"Stop test needs actual committed head");
    require(world.stop(player,status)&&world.actor(player).walk.head==head,"Stop must retain committed head");finish(world,player);
    require(world.actor(player).ground.position.x/256!=59,"Stop must shorten the route");
    require(world.move(player,59,89,status),"Idle repeated order must succeed");finish(world,player);
    require(world.move(player,57,89,status),"Return route must succeed");finish(world,player);
    require(world.actor(player).ground.position.x/256==57&&world.actor(player).ground.position.y/256==89,"Return route missed starting Cell");
    std::cout<<"Boot Camp actual GI/map/first-objective mission owners: "<<acceptedRoutes<<" starting directions, Stop/repeated orders, refusal isolation and terrain policies PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
