// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MissionTypedTagExpiration.hpp"
#include <cmath>

namespace ra2 {
struct MissionBuildingTargetType {
    const std::uint8_t& flag1217;
    const std::int32_t& countC6C;
    const std::uint8_t& flag11FE;
    const std::uint8_t& flag1206;
};
struct MissionBuildingTarget {
    const void* identity;
    const std::int32_t& health6C;
    std::int32_t& mission98;
    std::int32_t& pending9C;
    std::uint8_t& queuedA4;
    const std::uint8_t& byte530;
    const std::int32_t& count54C;
    const std::int32_t& word3FC;
    const void* const& type418;
    MissionExpirationOwnerView owner1B4;
    const std::uint8_t& byte59C;
    std::uint8_t& byte404;
    const void*& target228;
    const void* const& service238;
    std::int32_t& word310;
    const void*& attached25C;
    const void* const& target22C;
};
struct MissionBuildingTargetServices {
    // Pure live type registry binding; it must not query or mutate gameplay.
    std::function<MissionBuildingTargetType(const void*)> type;
    //4E8330 and the terminal attached-object/service effects remain named leaves.
    std::function<double(const void*)> housePower4E8330;
    std::function<void(const void*,const void*)> clear68A490;
    std::function<std::int32_t(const void*)> weaponIndex2B8;
    std::function<std::uint8_t(const void*,std::int32_t)> weapon350;
    std::function<void(const void*)> releaseF0;
};
// Complete450360. Preserve signed counts, health!=0, saved initial type and the
// late type reread after a potentially mutating House callback. CF includes NaN.
inline std::uint8_t missionBuildingAvailable(MissionBuildingTarget b,
        const MissionBuildingTargetServices& s) {
    if(!b.byte530&&b.count54C<2)return 0;
    if(b.word3FC>0||!b.health6C)return 0;
    requireMissionExpirationService(s.type);const auto type=s.type(b.type418);
    if(type.flag1217&&type.countC6C>0&&type.flag11FE) {
        requireMissionExpirationService(s.housePower4E8330);
        const auto ratio=s.housePower4E8330(b.owner1B4);
        if(!(ratio>=1.0)&&b.count54C<2)return 0;
    }
    if(s.type(b.type418).flag1206&&!b.byte59C)return 0;
    return 1;
}
// Complete6C5070 orchestration: save both actor identity and the requested target,
// call2B8 first, then350 with its exact signed index. Its leaves remain supplied.
inline std::uint8_t missionBuildingWeaponPermission(const void* target,
        const MissionBuildingTargetServices& s) {
    requireMissionExpirationService(s.weaponIndex2B8);
    const auto index=s.weaponIndex2B8(target);
    requireMissionExpirationService(s.weapon350);return s.weapon350(target,index);
}
//6C9AF0's actual null-target path. Nonnull admission/self/map/Infantry handling
// requires its own recovery and is not silently replaced by a null clear.
inline void clearMissionTechnoTarget(MissionBuildingTarget b,
        const MissionBuildingTargetServices& s,const MissionTagStore& store={}) {
    b.byte404=0;if(store)store(b.identity,0x404,0,nullptr);
    if(!b.target228)return;
    b.target228=nullptr;if(store)store(b.identity,0x228,0,nullptr);
    if(b.service238) {
        requireMissionExpirationService(s.clear68A490);s.clear68A490(b.service238,nullptr);
    }
    if(!b.target228){b.word310=0;if(store)store(b.identity,0x310,0,nullptr);}
    if(b.attached25C&&!missionBuildingWeaponPermission(nullptr,s)) {
        requireMissionExpirationService(s.releaseF0);
        if(!b.attached25C)throw std::invalid_argument("Target-clear release reached a null attachment");
        s.releaseF0(b.attached25C);
        b.attached25C=nullptr;if(store)store(b.identity,0x25c,0,nullptr);
    }
}
// Complete440450 for requested=null, as used by Tag expiration. Even when its
// return cannot change the null argument, the30C availability call must execute.
inline void setMissionBuildingNullTarget(MissionBuildingTarget b,const void* requested,
        const MissionBuildingTargetServices& s,const MissionTagStore& store={}) {
    if(requested)throw std::invalid_argument("Building nonnull target requires recovery");
    if(b.mission98!=19)(void)missionBuildingAvailable(b,s);
    clearMissionTechnoTarget(b,s,store);
}
// Complete594D80. pending9C is distinct from discovery's queuedA0.
inline std::uint8_t restoreMissionBuildingPending(MissionBuildingTarget b,
        const MissionTagStore& store={}) {
    const auto pending=b.pending9C;if(pending==-1)return 0;
    b.mission98=pending;if(store)store(b.identity,0x98,std::uint32_t(pending),nullptr);
    b.pending9C=-1;if(store)store(b.identity,0x9c,0xffffffffu,nullptr);
    b.queuedA4=0;if(store)store(b.identity,0xa4,0,nullptr);
    return 1;
}
//6CD880 continuation in this null-target profile. Read22C only after the mission
// stores. Entered nonnull22C refuses without claiming rollback of those stores.
inline std::uint8_t resumeMissionBuildingNullTarget(MissionBuildingTarget b,
        const MissionBuildingTargetServices& s,const MissionTagStore& store={}) {
    if(!restoreMissionBuildingPending(b,store))return 0;
    setMissionBuildingNullTarget(b,b.target22C,s,store);return 1;
}
inline const void* missionBuildingType84(const void* const& type418){return type418;}
inline std::uint8_t missionTargetPending1E4(const std::int32_t& pending9C){return pending9C!=-1;}
inline std::uint8_t missionTargetDisguisedC0(const std::uint8_t& byte170){return byte170;}
inline const void* missionBuildingQueryCC(std::uint32_t){return nullptr;}
}
