// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <stdexcept>

namespace ra2 {
template<class F> const F& requireResume(const F& f){
    if(!f)throw std::invalid_argument("Missing Infantry mission-resume child");
    return f;
}
struct InfantryMissionResumeActor {
    const std::int32_t& mission98;
    const void* const& alternate228;
    const void* const& target494;
    const void* const& team4c4;
};
struct InfantryMissionResumeServices {
    std::function<std::uint32_t(const void*,std::uint32_t)> foot4c6f10;
    std::function<std::uint32_t()> special438,mission16c,controlled4f52f0,predicate28c;
    std::function<void()> refill4c8b00;
    // Each invocation performs a new5950D0 query using the live raw mission.
    std::function<std::uint8_t(int)> missionControl;
    std::function<std::int32_t()> house194,rules10a8;
    std::function<std::uint8_t(int)> typeByte;
    std::function<std::uint32_t(int)> ability6d7910;
    std::function<void(int,int)> queue1d0;
};
// Complete4C8B00 early-return profiles. A present494 bypasses the vector;
// otherwise the exact count4AC zero test applies (negative is not empty here).
inline void refillEmptyFootResumeDestination(const void* const& target494,const std::int32_t& count4ac){
    if(target494)return;
    if(count4ac!=0)throw std::invalid_argument("Infantry resume nonempty destination vector remains unjoined");
}
// Complete503C00. Named children are separate evidence boundaries. Preserve
// repeated virtual getters and late actor reads across each child invocation.
inline std::uint8_t resumeInfantryMission(InfantryMissionResumeActor a,
    const void* first,std::uint32_t second,const InfantryMissionResumeServices& s){
    const auto saved=std::uint8_t(requireResume(s.foot4c6f10)(first,second));
    if(std::uint8_t(requireResume(s.special438)()))return saved;
    const auto mission=[&]{return std::int32_t(requireResume(s.mission16c)());};
    if(mission()==28)return saved;
    int chosen;
    if(a.alternate228){
        chosen=1;
        if(const auto m=mission();m==17)chosen=m;
        if(const auto m=mission();m==8)chosen=m;
    }else{
        requireResume(s.refill4c8b00)();
        if(a.target494){
            chosen=2;
            if(const auto m=mission();m==8)chosen=m;
            if(const auto m=mission();m==17)chosen=m;
        }else{
            if(mission()==5)return 0;
            if(mission()==11)return 0;
            if(mission()!=-1){
                if(requireResume(s.missionControl)(5))return 0;
                if(requireResume(s.missionControl)(7))return 0;
            }
            if(!std::uint8_t(requireResume(s.controlled4f52f0)())&&!a.team4c4){
                // The original loads House194 before Rules10A8.
                const auto value=requireResume(s.house194)();
                const auto limit=requireResume(s.rules10a8)();
                if(value<limit&&a.mission98!=11)chosen=5;
                else if(std::uint8_t(requireResume(s.predicate28c)())||
                    requireResume(s.typeByte)(0xc11)||requireResume(s.typeByte)(0xc14))chosen=11;
                else chosen=5;
            }else if(a.mission98==11)chosen=11;
            else if(std::uint8_t(requireResume(s.ability6d7910)(16))||requireResume(s.typeByte)(0xb00))
                chosen=a.team4c4?5:11;
            else chosen=5;
        }
    }
    if(a.mission98!=25&&a.mission98!=11&&chosen!=-1)requireResume(s.queue1d0)(chosen,0);
    return saved;
}
struct TechnoMissionResumeServices {
    std::function<std::uint32_t()> special45c,predicate3c8,controller615360;
};
// Complete6D48F0: arguments are not read by this parent; low bytes gate children.
inline std::uint8_t resumeTechnoMission(const TechnoMissionResumeServices& s){
    if(!std::uint8_t(requireResume(s.special45c)())&&std::uint8_t(requireResume(s.predicate3c8)()))
        (void)requireResume(s.controller615360)();
    return 0;
}
struct FootMissionResumeActor {
    std::uint8_t& entered59d;
    const std::uint8_t& flag577;
    const std::int32_t& pending488;
    const std::int32_t& mission98;
    const std::int32_t& statusA8;
    const std::int32_t& animation418;
    const void* const& field1b0;
};
struct FootMissionResumeServices {
    std::function<void(const void*,std::uint32_t)> techno6d48f0;
    // Query returns a retained logical interface; the parent releases it after
    // its later effects. Null represents the separate E_NOINTERFACE profile.
    std::function<const void*()> queryPiggyback454c70;
    std::function<std::uint32_t(const void*)> predicate14;
    std::function<void(const void*)> release8;
    std::function<void(int,int)> percentage4c8;
    std::function<void(int,int,std::uint32_t)> store;
};
// Complete-to-return4C6F10 for the bounded ordinary E1 domain: no577 effect,
// pending destination vector, entered418 animation or retained1B0; supplied
// query454C70 yields either E_NOINTERFACE/null or a nonnull interface whose
// predicate low byte is false. Positive unstacking remains guarded.
// Refuse at the entered child after preceding original stores, never clear
// real targets/Team/locomotor state to manufacture this supported profile.
inline std::uint8_t resumeOrdinaryFootMission(FootMissionResumeActor a,
    const void* first,std::uint32_t second,const FootMissionResumeServices& s){
    if(a.entered59d)return 0;
    a.entered59d=1;if(s.store)s.store(0x59d,1,1);
    requireResume(s.techno6d48f0)(first,second);
    if(a.flag577)throw std::invalid_argument("Foot resume577 effect remains unjoined");
    requireResume(s.predicate14);requireResume(s.release8);
    const auto local=requireResume(s.queryPiggyback454c70)();
    try{
        if(local&&std::uint8_t(s.predicate14(local)))
            throw std::invalid_argument("Foot resume piggyback end remains unjoined");
        if(a.pending488>0)throw std::invalid_argument("Foot resume488 destination vector remains unjoined");
        if(!(a.mission98==25&&a.statusA8)&&a.animation418!=-1&&std::uint8_t(second))
            throw std::invalid_argument("Foot resume418 animation remains unjoined");
        if(a.field1b0)throw std::invalid_argument("Foot resume retained1B0 destination remains unjoined");
        requireResume(s.percentage4c8)(0,0);
    }catch(...){
        // Native refusal cleanup; not an assertion of original exception behavior.
        if(local)s.release8(local);
        throw;
    }
    if(local)s.release8(local);
    return 0;
}
}
