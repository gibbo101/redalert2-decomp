// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MissionTechnoTagExpiration.hpp"
#include "sim/Drive.hpp"
#include "sim/TerrainOccupation.hpp"
#include "sim/OriginalMath.hpp"

namespace ra2 {
// Registry lookup only borrows fields. It must not perform gameplay queries or
// mutate owners. Different fields of the same logical record retain one owner.
struct MissionExpirationRecord {
    const std::int32_t& health6C;
    const std::uint8_t& flags14;
    const std::uint8_t& byte7D;
    const std::uint8_t& typeByteC08;
    const void* const& next4C8;
    const void* const& recipient588;
};
// This algorithm only writes zero to490. Borrow its actual numeric word or a
// legacy fixture pointer without inventing a pointer interpretation of the word.
class MissionExpirationZeroField {
    std::function<void()> clear_;
public:
    MissionExpirationZeroField(std::int32_t& word):clear_([&word]{word=0;}){}
    MissionExpirationZeroField(const void*& pointer):clear_([&pointer]{pointer=nullptr;}){}
    void operator=(std::nullptr_t){clear_();}
};
struct MissionFootTagExpiration {
    MissionTechnoTagExpiration techno;
    const void*& link4C4;
    const void*& team580;
    const void*& link4C8;
    const void*& link498;
    MissionExpirationZeroField destination490;
    const void*& destination494;
    const void*& destination4BC;
    const void*& cell4B8;
    MissionExpirationPointerView type5A8;
    const std::int32_t& queuedMissionA0;
    MissionExpirationVector<const void*>& links4A0;
    MissionExpirationVector<const void*>& links47C;
};
struct MissionFootTagExpirationServices {
    const std::uint8_t& globalA40D04;
    std::function<MissionExpirationRecord(const void*)> record;
    // Actual virtual+28 nested dispatch and6D6E50 effects remain named children.
    std::function<void(const void*,const void*,std::uint32_t)> nestedExpiration28;
    std::function<void(const void*)> clear1B0;
    std::function<Coord(const void*)> coordinates48;
    std::function<const void*(TerrainCellPoint)> cell548070;
    // Optional non-mutating observation of the actual Mission getter entry.
    // This must not change fields, run gameplay services or bind other owners.
    std::function<void()> missionRead;
};
inline void eraseAllMissionExpiration(MissionExpirationVector<const void*>& v,
        const void* subject,const MissionTagStore& store={}) {
    for(std::int32_t i=0;i<v.count;++i)if(missionExpirationSlot(v,i)==subject) {
        eraseMissionExpiration(v,i,store);--i;
    }
}
// Complete4C8460 for the supported nonnull Tag44/Team34 subject profiles of
// Techno. Object-subject coordinate/discovery admission is outside this entry.
template<class Subject> inline void expireMissionFootTag(MissionFootTagExpiration f,
        const Subject& subject,std::uint8_t subjectFlags14,
        std::uint32_t removed,const MissionTechnoTagExpirationServices& technoServices,
        const MissionFootTagExpirationServices& s,const MissionTagStore& store={}) {
    expireMissionTechnoTag(f.techno,subject,subjectFlags14,removed,technoServices,store);
    const auto actor=f.techno.radio.object.identity;
    const auto clear=[&](auto& link,std::int64_t offset){link=nullptr;if(store)store(actor,offset,0,nullptr);};
    const auto record=[&](const void* p){requireMissionExpirationService(s.record);return s.record(p);};
    if(f.link4C4==subject.identity)clear(f.link4C4,0x4c4);
    if(f.team580==subject.identity) {
        if(!record(f.team580).health6C||!s.globalA40D04)clear(f.team580,0x580);
    }
    if(f.team580&&record(f.team580).health6C>0) {
        const auto recipient=record(f.team580).recipient588;
        requireMissionExpirationService(s.nestedExpiration28);s.nestedExpiration28(recipient,subject.identity,1);
    }
    if(subject.identity==actor)clear(f.team580,0x580);
    if(f.link4C8==subject.identity&&std::uint8_t(removed)) {
        f.link4C8=record(subject.identity).next4C8;if(store)store(actor,0x4c8,0,f.link4C8);
    }
    if(f.techno.link1B0==subject.identity) {requireMissionExpirationService(s.clear1B0);s.clear1B0(nullptr);}
    if(f.link498==subject.identity)clear(f.link498,0x498);
    if(f.destination494==subject.identity) {
        // The constructed Tag profile has flags14 bit0 clear, so the original
        // Object coordinate/Cell-discovery child is not entered even on removed0.
        if(s.missionRead)s.missionRead();
        const auto mission=f.techno.mission98==-1?f.queuedMissionA0:f.techno.mission98;
        bool retain=false;
        if(mission==8) {
            requireMissionExpirationService(technoServices.kind2C);
            if(technoServices.kind2C()==15&&record(f.type5A8).typeByteC08&&f.destination494) {
                const auto target=record(f.destination494);
                retain=(target.flags14&2)&&target.byte7D&&target.health6C>0;
            }
        }
        if(!retain){clear(f.destination490,0x490);clear(f.destination494,0x494);}
    }
    if(f.destination4BC==subject.identity) {
        requireMissionExpirationService(s.coordinates48);const auto point=s.coordinates48(f.destination4BC);
        const TerrainCellPoint cell{std::bit_cast<std::int16_t>(std::uint16_t(point.x/256)),std::bit_cast<std::int16_t>(std::uint16_t(point.y/256))};
        requireMissionExpirationService(s.cell548070);f.cell4B8=s.cell548070(cell);
        if(store)store(actor,0x4b8,0,f.cell4B8);clear(f.destination4BC,0x4bc);
    }
    eraseAllMissionExpiration(f.links4A0,subject.identity,store);
    eraseAllMissionExpiration(f.links47C,subject.identity,store);
}
// Complete501CB0. Type5A8 is read after all inherited callbacks and stores.
template<class Subject> inline void expireMissionInfantryTag(MissionFootTagExpiration f,
        const Subject& subject,std::uint8_t flags14,std::uint32_t removed,
        const MissionTechnoTagExpirationServices& technoServices,
        const MissionFootTagExpirationServices& footServices,const MissionTagStore& store={}) {
    expireMissionFootTag(f,subject,flags14,removed,technoServices,footServices,store);
    if(f.type5A8==subject.identity) {
        f.type5A8=nullptr;if(store)store(f.techno.radio.object.identity,0x5a8,0,nullptr);
    }
}
// Complete707E90/41ADB0. These are distinct derived fields; neither aliases
// Infantry's Type5A8. The saved subject survives all inherited callbacks.
struct MissionUnitTagExpiration {
    MissionFootTagExpiration foot;
    const void*& type5B0;
    const void*& link5AC;
};
struct MissionAircraftTagExpiration {
    MissionFootTagExpiration foot;
    const void*& type5B4;
    const void*& link5AC;
};
template<class Subject> inline void expireMissionUnitTag(MissionUnitTagExpiration unit,
        const Subject& subject,std::uint8_t flags14,std::uint32_t removed,
        const MissionTechnoTagExpirationServices& techno,
        const MissionFootTagExpirationServices& foot,const MissionTagStore& store={}) {
    const auto saved=subject.identity;
    expireMissionFootTag(unit.foot,subject,flags14,removed,techno,foot,store);
    const auto actor=unit.foot.techno.radio.object.identity;
    if(unit.type5B0==saved){unit.type5B0=nullptr;if(store)store(actor,0x5b0,0,nullptr);}
    if(unit.link5AC==saved){unit.link5AC=nullptr;if(store)store(actor,0x5ac,0,nullptr);}
}
template<class Subject> inline void expireMissionAircraftTag(MissionAircraftTagExpiration aircraft,
        const Subject& subject,std::uint8_t flags14,std::uint32_t removed,
        const MissionTechnoTagExpirationServices& techno,
        const MissionFootTagExpirationServices& foot,const MissionTagStore& store={}) {
    const auto saved=subject.identity;
    expireMissionFootTag(aircraft.foot,subject,flags14,removed,techno,foot,store);
    const auto actor=aircraft.foot.techno.radio.object.identity;
    if(aircraft.type5B4==saved){aircraft.type5B4=nullptr;if(store)store(actor,0x5b4,0,nullptr);}
    if(aircraft.link5AC==saved){aircraft.link5AC=nullptr;if(store)store(actor,0x5ac,0,nullptr);}
}
struct MissionBuildingTagExpiration {
    MissionTechnoTagExpiration techno;
    const void*& link438;
    const void*& link440;
    const void*& link41C;
    const void*& link4D4;
    const void*& link4E8;
    const void* const& link474;
    const void*& type418;
    std::span<const void*> links4C0; // Exactly three fixed fields.
    const std::int32_t& health6C;
    MissionExpirationVector<const void*>& links53C;
};
struct MissionBuildingTagExpirationServices {
    const double& threshold1368;
    // Virtual84 returns a type, then its live signed+A0 is read. Return a ref to
    // that owner's strength; don't snapshot actor health after this callback.
    std::function<const std::int32_t&()> strength84;
    std::function<std::uint8_t(const void*,std::int32_t)> animationFirstByte;
    std::function<void(const void*,std::int32_t,std::int32_t)> animation44CA60;
};
inline double missionExpirationHealthRatio(const std::int32_t& health,
        const std::function<const std::int32_t&()>& strength) {
    const auto saved=health;requireMissionExpirationService(strength);
    OriginalRounding rounding;volatile double numerator=saved;volatile double denominator=strength();
    return numerator/denominator;
}
// Complete449E40 for Tag subjects. Original40FFB0 -> actual Tag6B42D0 returns44;
// its kind4 factory-only early returns are unreachable for this typed subject.
inline void expireMissionBuildingTag(MissionBuildingTagExpiration b,
        const MissionTagExpiredAbstract& subject,std::uint8_t flags14,std::uint32_t removed,
        const MissionTechnoTagExpirationServices& technoServices,
        const MissionBuildingTagExpirationServices& s,const MissionTagStore& store={}) {
    if(b.links4C0.size()!=3)throw std::invalid_argument("Building Tag expiration needs three fields");
    expireMissionTechnoTag(b.techno,subject,flags14,removed,technoServices,store);
    const auto actor=b.techno.radio.object.identity;
    const auto clear=[&](const void*& link,std::int64_t offset){link=nullptr;if(store)store(actor,offset,0,nullptr);};
    if(b.link438==subject.identity)clear(b.link438,0x438);
    if(b.link440==subject.identity)clear(b.link440,0x440);
    if(b.link41C==subject.identity)clear(b.link41C,0x41c);
    if(b.link4D4==subject.identity)clear(b.link4D4,0x4d4);
    if(b.link4E8==subject.identity)clear(b.link4E8,0x4e8);
    if(b.link474==subject.identity) {
        const auto ratio=missionExpirationHealthRatio(b.health6C,s.strength84);
        const bool damaged=!(ratio>s.threshold1368); // Equal/unordered choose1.
        const auto offset=damaged?0x1168:0x1158;
        if(!b.type418)throw std::invalid_argument("Building expiration animation type is unbound");
        requireMissionExpirationService(s.animationFirstByte);
        if(s.animationFirstByte(b.type418,offset)) {
            requireMissionExpirationService(s.animation44CA60);s.animation44CA60(b.type418,offset,damaged?1:0);
        }
    }
    if(b.type418==subject.identity)clear(b.type418,0x418);
    for(std::size_t i=0;i<3;++i)if(b.links4C0[i]==subject.identity)clear(b.links4C0[i],0x4c0+std::int64_t(i)*4);
    eraseMissionExpiration(b.links53C,findMissionExpiration(b.links53C,subject.identity),store);
}
// Stable borrowed recipient bindings for the existing generic Tag broadcaster.
// No field is read while binding. Owners, subject and flag storage must outlive
// the binding. Rebind on clones; copying callbacks does not clone their owners.
inline MissionTagExpirationRecipient bindMissionInfantryTagExpiration(
        MissionFootTagExpiration actor,const MissionTagExpiredAbstract& expired,
        const std::uint8_t& flags14,MissionTechnoTagExpirationServices techno,
        MissionFootTagExpirationServices foot,const MissionTagStore& store={}) {
    return {actor.techno.radio.object.identity,
        [actor,&expired,&flags14,techno,foot,store](MissionTagState& subject,std::uint32_t removed) mutable {
            if(&subject!=&expired.tag)throw std::invalid_argument("Infantry expiration Tag association differs");
            expireMissionInfantryTag(actor,expired,flags14,removed,techno,foot,store);
        }};
}
inline MissionTagExpirationRecipient bindMissionBuildingTagExpiration(
        MissionBuildingTagExpiration actor,const MissionTagExpiredAbstract& expired,
        const std::uint8_t& flags14,MissionTechnoTagExpirationServices techno,
        MissionBuildingTagExpirationServices building,const MissionTagStore& store={}) {
    return {actor.techno.radio.object.identity,
        [actor,&expired,&flags14,techno,building,store](MissionTagState& subject,std::uint32_t removed) mutable {
            if(&subject!=&expired.tag)throw std::invalid_argument("Building expiration Tag association differs");
            expireMissionBuildingTag(actor,expired,flags14,removed,techno,building,store);
        }};
}
}
