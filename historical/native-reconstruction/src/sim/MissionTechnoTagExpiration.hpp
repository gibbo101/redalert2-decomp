// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MissionTagObjectExpiration.hpp"
#include <array>

namespace ra2 {
// Borrow either a pointer field or a caller's live logical identity field. The
// latter maps handles without a mirrored Owner. Accessors must only read/write
// that field; they must not perform gameplay queries or invoke observers.
using MissionExpirationOwnerView=MissionExpirationPointerView;
struct MissionRadioTagExpiration {
    MissionTagObjectReferences object;
    MissionExpirationVector<const void*>& connections;
};
// Complete636BA0: Tag44 and Team34 subjects share slot cleanup; the base
// Object overload keeps their distinct Tag ownership rules. No compaction.
template<class Subject> inline void expireMissionRadioTag(MissionRadioTagExpiration radio,
        const Subject& subject,std::uint32_t removed,
        const MissionTagStore& store={}) {
    expireMissionTagObjectReferences(radio.object,subject,removed,store);
    for(std::int32_t i=0;i<radio.connections.count;++i) {
        if(missionExpirationSlot(radio.connections,i)==subject.identity&&std::uint8_t(removed)) {
            radio.connections.slots[std::size_t(i)]=nullptr;
            if(store)store(radio.connections.identity,0x100+std::int64_t(i)*4,0,nullptr);
        }
    }
}
struct MissionExpirationChain {
    const void*& head;
    const void* identity;
    // Borrow the actual Abstract+30 links, including the expired record's link.
    std::function<MissionExpirationPointerView(const void*)> next;
    std::size_t traversalLimit;
};
// Complete468A70. Unlink the first matching node; do not clear its own Next.
inline void unlinkMissionExpirationChain(MissionExpirationChain chain,const void* subject,
                                         const MissionTagStore& store={}) {
    if(!subject||!chain.head)return;
    if(!chain.next)throw std::invalid_argument("Expiration chain requires actual links");
    if(chain.head==subject) {
        chain.head=chain.next(subject);if(store)store(chain.identity,4,0,chain.head);return;
    }
    auto* node=chain.head;std::size_t visits=0;
    for(;;) {
        if(++visits>chain.traversalLimit)throw std::invalid_argument("Expiration chain exceeds supplied bound");
        const void* next=chain.next(node);if(!next)return;
        if(next==subject) {
            auto link=chain.next(node);link=static_cast<const void*>(chain.next(subject));
            if(store)store(node,0x30,0,link);return;
        }
        node=next;
    }
}
struct MissionExpirationControl {
    const void*& subject24;
    const void*& subject28;
    const void* identity;
};
// Complete468120. The associated second field clears only on a matching first.
inline std::uint8_t expireMissionControlTag(MissionExpirationControl control,const void* subject,
                                    const MissionTagStore& store={}) {
    if(control.subject24==subject) {
        control.subject24=nullptr;if(store)store(control.identity,0x24,0,nullptr);
        control.subject28=nullptr;if(store)store(control.identity,0x28,0,nullptr);
    }
    return 1;
}
// Borrows contiguous legacy fixtures or an existing first field plus seven
// independently owned trailing fields. No pointer values are copied/synchronized.
class MissionExpirationWeaponFields {
    std::span<const void*> all_,tail_;const void** first_=nullptr;
public:
    MissionExpirationWeaponFields(std::span<const void*> fields):all_(fields){}
    template<std::size_t N>MissionExpirationWeaponFields(std::array<const void*,N>& fields):all_(fields){}
    MissionExpirationWeaponFields(const void*& first,std::span<const void*> tail):tail_(tail),first_(&first){}
    std::size_t size()const{return first_?1+tail_.size():all_.size();}
    const void*& operator[](std::size_t index)const{return first_?(index?tail_[index-1]:*first_):all_[index];}
};
struct MissionTechnoTagExpiration {
    MissionRadioTagExpiration radio;
    MissionExpirationChain passengers;
    const void*& link108;
    const void*& link1B0;
    MissionExpirationOwnerView owner1B4;
    const void*& service208;
    const void*& link20C;
    const void*& target228;
    const void*& target22C;
    const void*& control230;
    const void*& service238;
    const void*& link23C;
    MissionExpirationWeaponFields links25C; // Exactly eight live fields.
    const void*& link27C;
    const void*& link384;
    const void*& link3F8;
    std::int32_t& timer148;
    std::int32_t& timer14C;
    std::int32_t& timer150;
    const std::int32_t& mission98;
    std::int32_t& wordA8;
    std::uint8_t& byte372;
    std::uint8_t& byte5BA;
    MissionExpirationVector<const void*>& values390;
    MissionExpirationVector<const void*>& keys3A8;
    MissionExpirationVector<const void*>& links3C0;
};
struct MissionTechnoTagExpirationServices {
    const std::int32_t& frame;
    const std::int32_t& session;
    const std::int32_t& retryPadding; // Caller local word, not initialized here.
    // These named children retain supplied scope until separately joined.
    std::function<const void*()> subjectOwner;
    std::function<std::int32_t(std::int32_t,std::int32_t)> retryRange;
    std::function<void(const void*)> setTarget370;
    std::function<std::uint8_t()> predicate1E4;
    std::function<void()> action1E0;
    std::function<std::int32_t()> kind2C;
    std::function<std::uint8_t()> predicateC0;
    std::function<const void*(std::int32_t)> queryCC;
    std::function<void()> action400;
    std::function<MissionExpirationControl(const void*)> control;
    std::function<void(const void*,const void*)> service68A560;
    std::function<void(const void*,const void*)> service6E24C0;
};
template<class F> inline void requireMissionExpirationService(const F& f) {
    if(!f)throw std::invalid_argument("Techno expiration requires named service");
}
// Complete6D2D10 for nonnull Tag44 or Team34 subjects; bit0 must be clear.
// Coordinate/discovery admission for Object subjects is a separate dependency.
template<class Subject> inline void expireMissionTechnoTag(MissionTechnoTagExpiration t,
        const Subject& subject,std::uint8_t subjectFlags14,
        std::uint32_t removed,const MissionTechnoTagExpirationServices& s,
        const MissionTagStore& store={}) {
    if(!subject.identity||(subjectFlags14&1)||t.links25C.size()!=8)
        throw std::invalid_argument("Techno Tag expiration subject/fields outside recovered domain");
    expireMissionRadioTag(t.radio,subject,removed,store);
    if(std::uint8_t(removed))unlinkMissionExpirationChain(t.passengers,subject.identity,store);
    const auto id=t.radio.object.identity;
    const auto clear=[&](const void*& link,std::int64_t offset){link=nullptr;if(store)store(id,offset,0,nullptr);};
    if(t.link23C==subject.identity)clear(t.link23C,0x23c);
    if(t.link20C==subject.identity)clear(t.link20C,0x20c);
    if(t.target228==subject.identity) {
        bool clearTarget=true;
        if(!std::uint8_t(removed)) {
            requireMissionExpirationService(s.subjectOwner);
            const auto owner=s.subjectOwner();
            clearTarget=owner!=t.owner1B4;
        }
        if(clearTarget) {
            auto remaining=t.timer150;
            if(t.timer148!=-1) {
                const auto elapsed=missionTagWrapped(s.frame,0u-std::uint32_t(t.timer148));
                remaining=elapsed>=remaining?0:missionTagWrapped(remaining,0u-std::uint32_t(elapsed));
            }
            if(remaining>10&&!s.session) {
                requireMissionExpirationService(s.retryRange);
                const auto value=s.retryRange(4,8);
                t.timer148=s.frame;if(store)store(id,0x148,std::uint32_t(t.timer148),nullptr);
                t.timer14C=s.retryPadding;if(store)store(id,0x14c,std::uint32_t(t.timer14C),nullptr);
                t.timer150=value;if(store)store(id,0x150,std::uint32_t(t.timer150),nullptr);
            }
            requireMissionExpirationService(s.setTarget370);s.setTarget370(nullptr);
            requireMissionExpirationService(s.predicate1E4);
            if(s.predicate1E4()) {
                requireMissionExpirationService(s.action1E0);s.action1E0();
                requireMissionExpirationService(s.kind2C);
                if(s.kind2C()==2&&t.mission98==25) {
                    t.wordA8=0;if(store)store(id,0xa8,0,nullptr);
                    t.byte5BA=0;if(store)store(id,0x5ba,0,nullptr);
                }
            }
        }
    }
    if(t.target22C==subject.identity)clear(t.target22C,0x22c);
    if(t.owner1B4==subject.identity) {
        t.owner1B4=nullptr;if(store)store(id,0x1b4,0,nullptr);
        t.byte372=0;if(store)store(id,0x372,0,nullptr);
    }
    requireMissionExpirationService(s.predicateC0);
    if(s.predicateC0()) {
        requireMissionExpirationService(s.queryCC);
        if(s.queryCC(1)==subject.identity){requireMissionExpirationService(s.action400);s.action400();}
    }
    for(std::size_t i=0;i<8;++i)if(t.links25C[i]==subject.identity)clear(t.links25C[i],0x25c+std::int64_t(i)*4);
    if(t.link27C==subject.identity)clear(t.link27C,0x27c);
    if(std::uint8_t(removed)) {
        if(t.link3F8==subject.identity)clear(t.link3F8,0x3f8);
        if(t.link1B0==subject.identity)clear(t.link1B0,0x1b0);
        if(t.control230){requireMissionExpirationService(s.control);expireMissionControlTag(s.control(t.control230),subject.identity,store);}
    }
    if(t.service238){requireMissionExpirationService(s.service68A560);s.service68A560(t.service238,subject.identity);}
    if(t.service208){requireMissionExpirationService(s.service6E24C0);s.service6E24C0(t.service208,subject.identity);}
    if(t.link384==subject.identity)clear(t.link384,0x384);
    if(t.link108==subject.identity)clear(t.link108,0x108);
    const auto index=findMissionExpiration(t.keys3A8,subject.identity);
    if(index!=-1) {
        eraseMissionExpiration(t.values390,index,store);
        eraseMissionExpiration(t.keys3A8,findMissionExpiration(t.keys3A8,subject.identity),store);
    }
    eraseMissionExpiration(t.links3C0,findMissionExpiration(t.links3C0,subject.identity),store);
}
}
