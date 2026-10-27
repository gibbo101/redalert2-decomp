// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/InfantrySpeed.hpp"
#include "sim/OriginalMath.hpp"
#include "sim/Facing.hpp"
#include <cmath>
#include <stdexcept>
namespace ra2 {
int infantrySpeed(InfantrySpeedActor a,const InfantrySpeedServices& s){
    if(!s.type||!s.countrySpeed128)throw std::invalid_argument("Infantry speed requires type and country owners");
    OriginalRounding rounding;
    const auto event=[&](char k,int value=0){if(s.trace)s.trace(k,value);};
    const auto type=[&]{event('t');return s.type();};
    const auto integer=[&](double value){
        // Actual77F110 FISTP is signed64, consumed as its low dword. Invalid
        // conversions produce8000000000000000 (low0), not signed32 saturation.
        const auto raw=!std::isfinite(value)||value<-0x1p63||value>=0x1p63?
            std::uint32_t(0):std::uint32_t(std::int64_t(value));
        const int result=signed32(raw);event('c',result);return result;
    };
    (void)type();event('h');const double house=s.countrySpeed128();
    const int base=type().speed5a0;
    int speed=integer((double(base)*house)*a.multiplier470);
    const auto veteran=[&]{event('v');const double n=a.veterancy118;return n>=1.&&n<2.;};
    const auto elite=[&]{event('e');return a.veterancy118>=2.;};
    event('b');bool promoted=false;
    if(veteran()||elite()){
        const auto t=type();
        if(veteran()&&t.veteranSpeed26c)promoted=true;
        else if(elite()&&(t.veteranSpeed26c||t.eliteSpeed27e))promoted=true;
    }
    if(promoted){
        if(!s.veteranSpeed598)throw std::invalid_argument("Infantry promoted speed requires rules owner");
        event('r');speed=integer(double(speed)*s.veteranSpeed598());
    }
    speed=integer(double(speed)*a.percentage468);
    event('k'); // Actual Infantry body kind15 skips the Unit5B4 half-speed path.
    if(a.flag5c3){
        // This last type read is direct actor+5A8, not another virtual+80.
        if(s.type().flagc0b)return signed32(std::uint32_t(speed)-std::uint32_t(speed/3));
        return signed32(std::uint32_t(speed)+std::uint32_t(speed/2));
    }
    return speed;
}
}
