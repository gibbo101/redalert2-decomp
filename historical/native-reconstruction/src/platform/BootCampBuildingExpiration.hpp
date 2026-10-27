// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MissionBuildingTarget.hpp"
#include "sim/UnitDiscovery.hpp"
#include "render/BuildingTypeBounds.hpp"
#include "render/BuildingImage.hpp"
#include "render/BuildingFrame.hpp"
#include "render/BuildingOrdinaryDraw.hpp"
#include <array>
#include <memory>
#include <vector>
namespace ra2 {
// Supplied bounded startup records, not a recovered BuildingType constructor.
struct BootCampBuildingExpirationType {
    BuildingTypeBoundsState imageBounds; // Supplied initial cache/image associations.
    BuildingOrdinaryTypeState ordinaryDraw; // Supplied drawing startup/associations.
    BuildingFrameTypeState frameSelection; // Supplied startup, no schedule/writer claim.
    BuildingImageState images; // Supplied names/demand flags, recovered lazy getters.
    // Host resource ownership, not the original file/heap implementation. Shared
    // immutable backing keeps opaque image identities valid across world clones.
    std::vector<std::shared_ptr<const ShpImage>> imageBacking;
    const void* spriteSchemeTableB8c=nullptr; // Supplied null startup; nonnull owner not yet bound.
    std::int32_t indexB90=-1,strengthA0=0,countC6C=0;
    std::uint8_t flag1217=0,flag11FE=0,flag1206=0;
    std::int32_t sight530=0;
    std::int32_t threat598=0; // Supplied ThreatPosed key association.
    std::uint8_t veteranSight271=0,eliteSight283=0;
    // Meanings and stock initialization not recovered; zero startup supplied.
    std::uint8_t flag534=0,flagADD=0;
    std::int32_t radarFootprintC78=0; // Supplied index; original type loader pending.
    std::uint8_t radarAA6=0,radarAA7=0,radarVeteran277=0,radarElite289=0; // Supplied common type startup.
    std::uint8_t radarFlag1ff=0; // Supplied type startup.
};
// Values only: copying this record does not copy any bound callbacks or views.
struct BootCampBuildingExpirationState {
    const void* headFC=nullptr;const void* link108=nullptr;const void* link1B0=nullptr;
    const void* service208=nullptr;const void* link20C=nullptr;const void* target228=nullptr;
    const void* target22C=nullptr;const void* control230=nullptr;const void* service238=nullptr;
    const void* link23C=nullptr;const void* link27C=nullptr;const void* link384=nullptr;const void* link3F8=nullptr;
    std::array<const void*,8> links25C{};
    const void* type418=nullptr;const void* link41C=nullptr;const void* link438=nullptr;const void* link440=nullptr;
    const void* link4D4=nullptr;const void* link4E8=nullptr;const void* link474=nullptr;
    std::array<const void*,3> links4C0{};
    // Radio,390 values,3A8 keys,3C0 links,53C links. Keep all unused tails.
    std::array<std::int32_t,5> counts{};
    std::array<std::array<const void*,8>,5> backing{};
    std::int32_t health6C=0,pending9C=-1,timer148=-1,timer14C=0,timer150=0,wordA8=0,word3FC=0,word310=0;
    std::uint8_t byte5BA=0,byte530=0,byte59C=0,byte404=0,byte170=0;
    template<class F> void remapPointers(F&& remap){
        for(auto* field:std::array{&headFC,&link108,&link1B0,&service208,&link20C,&target228,&target22C,&control230,&service238,&link23C,&link27C,&link384,&link3F8,&type418,&link41C,&link438,&link440,&link4D4,&link4E8,&link474})*field=remap(*field);
        for(auto& p:links25C)p=remap(p);for(auto& p:links4C0)p=remap(p);
        for(auto& b:backing)for(auto& p:b)p=remap(p);
    }
    bool operator==(const BootCampBuildingExpirationState&)const=default;
};
// Stable backing, counts and spans. Move the owning pointer, never this context.
class BootCampBuildingExpiration {
    std::array<std::span<const void*>,5> slots_;
    std::array<int,5> identities_{};
    std::array<std::unique_ptr<MissionExpirationVector<const void*>>,5> vectors_;
public:
    BootCampBuildingExpirationState state;
    BootCampBuildingExpiration(){for(std::size_t i=0;i<5;++i){slots_[i]=state.backing[i];vectors_[i]=std::make_unique<MissionExpirationVector<const void*>>(MissionExpirationVector<const void*>{state.counts[i],slots_[i],&identities_[i]});}}
    BootCampBuildingExpiration(const BootCampBuildingExpiration&)=delete;
    BootCampBuildingExpiration& operator=(const BootCampBuildingExpiration&)=delete;
    BootCampBuildingExpiration(BootCampBuildingExpiration&&)=delete;
    BootCampBuildingExpiration& operator=(BootCampBuildingExpiration&&)=delete;
    using Type=std::function<const BootCampBuildingExpirationType&(const void*)>;
    MissionTagExpirationRecipient bind(const void* identity,MissionTagState*& tag,MissionExpirationPointerView next,
            UnitDiscoveryActor& actor,MissionExpirationOwnerView owner,const MissionTagExpiredAbstract& expired,
            const std::uint8_t& flags,const std::int32_t& frame,const std::int32_t& session,const std::int32_t& retryPadding,
            std::function<MissionExpirationPointerView(const void*)> chainNext,Type type){
        auto& r=state;
        MissionRadioTagExpiration radio{{tag,next,identity},*vectors_[0]};
        MissionExpirationChain chain{r.headFC,&r.headFC,std::move(chainNext),64};
        MissionTechnoTagExpiration techno{radio,chain,r.link108,r.link1B0,owner,r.service208,r.link20C,r.target228,r.target22C,r.control230,r.service238,r.link23C,r.links25C,r.link27C,r.link384,r.link3F8,r.timer148,r.timer14C,r.timer150,actor.mission98,r.wordA8,actor.field372,r.byte5BA,*vectors_[1],*vectors_[2],*vectors_[3]};
        MissionBuildingTarget target{identity,r.health6C,actor.mission98,r.pending9C,actor.queuedA4,r.byte530,r.counts[4],r.word3FC,r.type418,owner,r.byte59C,r.byte404,r.target228,r.service238,r.word310,r.links25C[0],r.target22C};
        MissionBuildingTargetServices leaves;
        leaves.type=[type](const void* p)->MissionBuildingTargetType{const auto& t=type(p);return {t.flag1217,t.countC6C,t.flag11FE,t.flag1206};};
        // Unrecovered effects stay absent: an entered child refuses explicitly.
        MissionTechnoTagExpirationServices services{frame,session,retryPadding};
        services.setTarget370=[target,leaves](const void* p){setMissionBuildingNullTarget(target,p,leaves);};
        services.predicate1E4=[this]{return missionTargetPending1E4(state.pending9C);};
        services.action1E0=[target,leaves]{(void)resumeMissionBuildingNullTarget(target,leaves);};
        services.kind2C=[]{return 6;}; // Stock453C40, verified separately.
        services.predicateC0=[this]{return missionTargetDisguisedC0(state.byte170);};
        services.queryCC=[](std::int32_t n){return missionBuildingQueryCC(std::uint32_t(n));};
        MissionBuildingTagExpiration building{techno,r.link438,r.link440,r.link41C,r.link4D4,r.link4E8,r.link474,r.type418,r.links4C0,r.health6C,*vectors_[4]};
        // The rules1368 threshold is irrelevant until animation is entered;
        // keep that whole entered branch refused, rather than invent its result.
        // A stable member owns the reference even when no animation is requested.
        MissionBuildingTagExpirationServices effects{threshold_};
        effects.strength84=[this,type]()->const std::int32_t&{return type(missionBuildingType84(state.type418)).strengthA0;};
        return bindMissionBuildingTagExpiration(building,expired,flags,std::move(services),std::move(effects));
    }
private:
    const double threshold_=0.; // Supplied, unusable while animation lookup is unbound.
};
}
