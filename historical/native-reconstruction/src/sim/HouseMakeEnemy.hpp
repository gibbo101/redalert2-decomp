// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/HouseThreat.hpp"
#include "sim/MissionTextAction.hpp"
namespace ra2 {
struct HouseMakeEnemyFields {
    const std::int32_t& index30;
    const void* const& type34;
    const std::uint8_t& flag134;
    const std::uint8_t& flag135;
    std::uint32_t& allies5674;
    std::uint32_t& mask120;
};
struct HouseMakeEnemyWorld {
    const HouseThreatWorld& threat;
    const std::int32_t& unrestricted;
    const void* const& currentHouse;
    std::function<HouseMakeEnemyFields(const void*)> house;
    // Pure type/rules field getters; no query or cached gameplay snapshots.
    std::function<std::uint8_t(const void*)> passive1A6;
    std::function<std::int32_t(const void*)> colorC0;
    std::function<double()> delay1128;
    std::function<void(bool)> mapSight;
    std::function<void(const void*)> rebuildGrid;
    std::function<const void*()> localize;
    std::function<const void*(const void*,const void*,const void*)> format;
    std::function<void(const void*,std::int32_t,std::uint32_t)> display;
    std::function<void()> redraw0;
    std::function<void(std::uint32_t)> speech;
    std::function<void(const void*,int,std::uint32_t)> stored; // Nonmutating observer.
};
template<class F>inline void requireHouseMakeEnemyService(const F& f){
    if(!f)throw std::invalid_argument("House MakeEnemy needs entered service");
}
inline HouseMakeEnemyFields houseMakeEnemyFields(const void* p,const HouseMakeEnemyWorld& w){
    if(!p)throw std::invalid_argument("House MakeEnemy needs owned nonnull House");
    requireHouseMakeEnemyService(w.house);return w.house(p);
}
inline bool houseMakeEnemyAllied(const void* self,const void* other,const HouseMakeEnemyWorld& w){
    if(!other)return false;if(self==other)return true;
    const auto a=houseMakeEnemyFields(self,w),b=houseMakeEnemyFields(other,w);
    return a.index30==b.index30||(b.index30!=-1&&(a.allies5674&(1u<<(std::uint32_t(b.index30)&31u))));
}
// Complete4E5A70, including the out-of-line4E5CD4 tail. Grid/map/UI effects
// remain named services; score/enemy selection uses actual4EEBA0 logic.
inline void makeHouseEnemy(const void* current,const void* target,std::uint8_t announce,const HouseMakeEnemyWorld& w){
    const auto self=houseMakeEnemyFields(current,w);
    if(w.threat.mode){
        requireHouseMakeEnemyService(w.passive1A6);
        if(w.passive1A6(houseMakeEnemyFields(target,w).type34)||w.passive1A6(self.type34))return;
    }
    requireHouseMakeEnemyService(w.mapSight);w.mapSight(false);
    updateHouseThreatScore(current,1,target,w.threat);
    bool reciprocal=false;
    const auto store=[&](const void* p,int offset,std::uint32_t& field,std::uint32_t value){
        field=value;if(w.stored)w.stored(p,offset,value);
    };
    if(houseMakeEnemyAllied(current,target,w)){
        auto other=houseMakeEnemyFields(target,w);
        store(current,0x5674,self.allies5674,self.allies5674&~(1u<<(std::uint32_t(other.index30)&31u)));
        // Actual NEG/SBB/INC on a nonzero shifted bit produces zero, not ~bit.
        if(w.unrestricted)store(current,0x120,self.mask120,0);
        requireHouseMakeEnemyService(w.rebuildGrid);w.rebuildGrid(current);
        if(houseMakeEnemyAllied(target,current,w)){
            reciprocal=true;
            store(target,0x5674,other.allies5674,other.allies5674&~(1u<<(std::uint32_t(self.index30)&31u)));
            // The original destination remains ESI (initiator), not EDI.
            if(w.unrestricted)store(current,0x120,self.mask120,self.mask120&~(1u<<(std::uint32_t(self.index30)&31u)));
            w.rebuildGrid(target);updateHouseThreatScore(target,1,target,w.threat);
        }
        if(w.threat.mode&&!w.unrestricted&&self.flag134){
            requireHouseMakeEnemyService(w.localize);const auto localized=w.localize();
            requireHouseMakeEnemyService(w.format);const auto text=w.format(localized,current,target);
            requireHouseMakeEnemyService(w.delay1128);const auto duration=missionTextDuration(w.delay1128());
            requireHouseMakeEnemyService(w.colorC0);const auto color=w.colorC0(self.type34);
            requireHouseMakeEnemyService(w.display);w.display(text,color,duration);
            requireHouseMakeEnemyService(w.redraw0);w.redraw0();
            if(announce&&reciprocal){
                const bool speak=w.threat.mode?(current==w.currentHouse||target==w.currentHouse):
                    bool(self.flag134||self.flag135||other.flag134||other.flag135);
                if(speak){requireHouseMakeEnemyService(w.speech);w.speech(0x7da338);}
            }
        }
    }
    w.mapSight(true);
}
}
