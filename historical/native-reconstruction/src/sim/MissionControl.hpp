// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <array>
#include <bit>
#include <cstdint>
#include <functional>
#include <stdexcept>
#include <string_view>
namespace ra2 {
inline constexpr std::array<std::string_view,30> missionControlNames{
    "Sleep","Attack","Move","QMove","Retreat","Guard","Sticky","Enter","Capture","Eaten",
    "Harvest","Area Guard","Return","Stop","Ambush","Hunt","Unload","Sabotage","Construction",
    "Selling","Repair","Rescue","Missile","Harmless","Open","Patrol","Paradrop Approach",
    "Paradrop Overfly","Wait","Attack Move"};
inline constexpr std::array<std::string_view,6> missionControlKeys{
    "NoThreat","Zombie","Recruitable","Paralyzed","Retaliate","Scatter"};
// Explicit original layout retains untouched padding and split-word writes.
struct MissionControlRecord {std::array<std::uint8_t,32> bytes{};};
using MissionControlTable=std::array<MissionControlRecord,30>;
using MissionControlStore=std::function<void(int,int,std::uint64_t)>;
inline std::uint64_t missionControlBits(const MissionControlRecord& r,int off,int n){
    std::uint64_t out=0;for(int i=0;i<n;++i)out|=std::uint64_t(r.bytes.at(off+i))<<(i*8);return out;
}
inline void storeMissionControl(MissionControlRecord& r,int off,int n,std::uint64_t v,const MissionControlStore& trace={}){
    for(int i=0;i<n;++i)r.bytes.at(off+i)=std::uint8_t(v>>(i*8));
    if(trace)trace(off,n,v);
}
inline std::int32_t missionControlIndex(const MissionControlRecord& r){
    return std::bit_cast<std::int32_t>(std::uint32_t(missionControlBits(r,0,4)));
}
inline std::string_view missionControlName(const MissionControlRecord& r){
    const auto i=missionControlIndex(r);if(i==-1)return "<none>";
    if(i<0||i>=30)throw std::invalid_argument("Mission control name outside recovered table");
    return missionControlNames[i];
}
// Complete594DD0, preserving store order and leaving padding unchanged.
inline void initializeMissionControl(MissionControlRecord& r,const MissionControlStore& trace={}){
    for(int i:{4,5,7})storeMissionControl(r,i,1,0,trace);
    for(int i:{6,8,9})storeMissionControl(r,i,1,1,trace);
    storeMissionControl(r,16,4,0xd2f1a9fc,trace);storeMissionControl(r,24,4,0xd2f1a9fc,trace);
    storeMissionControl(r,0,4,0xffffffff,trace);
    storeMissionControl(r,20,4,0x3f90624d,trace);storeMissionControl(r,28,4,0x3f90624d,trace);
}
struct MissionControlIniServices {
    std::function<std::uint32_t(std::string_view)> hasSection;
    std::function<std::uint32_t(std::string_view,std::string_view,std::uint8_t)> boolean;
    std::function<double(std::string_view,std::string_view,double)> number;
};
// The verified return-value domain includes finite values, infinities and quiet
// NaNs. Signaling NaN exception/quieting semantics remain outside this kernel.
inline std::uint64_t missionControlNumberBits(double value){
    const auto bits=std::bit_cast<std::uint64_t>(value);
    if((bits&0x7ff0000000000000ull)==0x7ff0000000000000ull&&
       (bits&0xfffffffffffffull)&&!(bits&0x8000000000000ull))
        throw std::invalid_argument("Mission control signaling NaN return remains unjoined");
    return bits;
}
// Complete594E30 on supplied binary64 INI-return values. Each section/index and
// default is loaded at its original point; callbacks may mutate the live record.
inline std::uint8_t readMissionControl(MissionControlRecord& r,const MissionControlIniServices& s,
    const MissionControlStore& trace={}){
    if(!s.hasSection)throw std::invalid_argument("Missing mission control section service");
    if(!s.hasSection(missionControlName(r)))return 0;
    if(!s.boolean||!s.number)throw std::invalid_argument("Missing mission control INI services");
    for(int i=0;i<6;++i){
        const auto name=missionControlName(r);const auto fallback=r.bytes[i+4];
        const auto value=std::uint8_t(s.boolean(name,missionControlKeys[i],fallback));
        storeMissionControl(r,i+4,1,value,trace);
    }
    const auto name=missionControlName(r);
    const auto fallback=std::bit_cast<double>(missionControlBits(r,16,8));
    const auto rate=s.number(name,"Rate",fallback);
    // The next section index is loaded before the Rate store.
    const auto aaName=missionControlName(r);
    storeMissionControl(r,16,8,missionControlNumberBits(rate),trace);
    const auto aa=s.number(aaName,"AARate",0.0);
    const auto bits=missionControlNumberBits(aa);
    storeMissionControl(r,24,8,bits,trace);
    // x87 C3 is set for equal AND unordered, so NaN also copies the live Rate.
    const bool nan=(bits&0x7ff0000000000000ull)==0x7ff0000000000000ull&&(bits&0xfffffffffffffull);
    if((bits&0x7fffffffffffffffull)==0||nan){
        const auto lo=missionControlBits(r,16,4),hi=missionControlBits(r,20,4);
        storeMissionControl(r,24,4,lo,trace);storeMissionControl(r,28,4,hi,trace);
    }
    return 1;
}
inline const MissionControlRecord& missionControlRecord(const MissionControlTable& table,int raw){
    // Original5950D0 uses wrapped raw<<5 addressing. Refuse addresses outside
    // this owned table, rather than normalizing an invalid mission to Guard.
    const auto offset=std::uint32_t(raw)<<5;
    if(offset>=table.size()*32)throw std::invalid_argument("Mission control address outside owned table");
    return table[offset/32];
}
inline std::uint8_t missionControlFlag(const MissionControlTable& table,int raw,int off){
    if(off<4||off>9)throw std::invalid_argument("Mission control flag offset outside recovered fields");
    return missionControlRecord(table,raw).bytes[off];
}
inline std::uint8_t missionRecruitable(const MissionControlTable& table,int raw){
    return raw==-1?1:missionControlFlag(table,raw,6);
}
}
