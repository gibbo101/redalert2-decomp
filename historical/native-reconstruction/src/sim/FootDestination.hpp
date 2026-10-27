// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/ActorGroundState.hpp"
#include <bit>
#include <functional>
#include <stdexcept>

namespace ra2 {
using FootDestinationTrace=std::function<void(char,int,int,std::int64_t)>;
struct UnsupportedFootDestination : std::invalid_argument {
    explicit UnsupportedFootDestination(const char* message):std::invalid_argument(message){}
};
struct FootDestinationReferences {
    std::uint32_t& global;
    std::uint32_t& instance;
};
struct FootDestinationTimerView {std::int32_t& start;std::int32_t& padding;std::int32_t& remaining;};
// Actual Foot fields, borrowed independently of the locomotor's representation.
struct FootDestinationView {
    std::int32_t& field490;
    const void*& target494;
    std::uint8_t& suspended598;
    std::uint8_t& reached5a1;
    FootDestinationTimerView retry530,wait558;
    FootDestinationReferences references;
};
struct FootDestinationServices {
    // coordinates dispatches on the late target494 with this Foot as argument.
    std::function<Coord(const void*)> coordinates;
    std::function<void(Coord)> moveTo;
    std::function<void()> stop;
    std::function<int()> kind,tick,delay;
    std::function<int(const void*)> targetId;
    std::function<void(const void*)> targetStore;
    FootDestinationTrace trace;
};
namespace foot_destination_detail {
inline void event(const FootDestinationTrace& trace,char k,int a,int b,std::int64_t value){
    if(trace)trace(k,a,b,value);
}
// Successful ordinary QI/GetClassID profile. Drive and Walk have different
// class IDs; both differ from Foot's timer-special class. Destruction/failure
// and the atomic implementation remain outside this bounded kernel.
class Interface {
    FootDestinationReferences refs_;FootDestinationTrace trace_;
public:
    Interface(FootDestinationReferences refs,FootDestinationTrace trace):refs_(refs),trace_(std::move(trace)){
        if(!refs_.instance||refs_.instance>=0x7fffffffu)
            throw UnsupportedFootDestination("Destination requires a retained ordinary interface");
        ++refs_.global;event(trace_,'C',0,0,refs_.global);
        ++refs_.instance;event(trace_,'I',0,0,refs_.instance);
        event(trace_,'G',0,0,0);
    }
    ~Interface(){--refs_.global;event(trace_,'C',0,0,refs_.global);--refs_.instance;event(trace_,'I',0,0,refs_.instance);}
    Interface(const Interface&)=delete;
};
}
// Complete ordinary Foot4C8030 profile: no attached effect or timer-special
// class, and non-aircraft null handling. Locomotor commands stay in their own
// recovered Walk/Drive kernels. Supplied scratch aliases coordinate output Y.
inline void setOrdinaryFootDestination(FootDestinationView v,const void* target,
    int temporaryPadding,const FootDestinationServices& s){
    const auto store=[&](int off,int n,std::int64_t value){foot_destination_detail::event(s.trace,'a',off,n,value);};
    const auto id=[&](const void* p){if(!p)return 0;if(!s.targetId)throw std::invalid_argument("Missing Foot target identity");return s.targetId(p);};
    v.field490=0;store(0x490,4,0);
    v.target494=target;store(0x494,4,id(target));
    if(s.targetStore)s.targetStore(target);
    int padding=temporaryPadding;
    if(target){
        foot_destination_detail::Interface retained(v.references,s.trace);
        if(v.suspended598){v.suspended598=0;store(0x598,1,0);}
        else {
            if(!s.coordinates||!s.moveTo)throw std::invalid_argument("Missing Foot coordinate/Move_To binding");
            const Coord point=s.coordinates(v.target494);
            padding=point.y;
            s.moveTo(point);
        }
    }else{
        if(!s.kind||!s.stop)throw std::invalid_argument("Missing Foot kind/Stop binding");
        const int kind=s.kind();foot_destination_detail::event(s.trace,'k',0,0,kind);
        if(kind==2)throw UnsupportedFootDestination("Aircraft destination child is unjoined");
        s.stop();v.target494=nullptr;store(0x494,4,0);
    }
    v.reached5a1=0;store(0x5a1,1,0);
    if(!s.tick||!s.delay)throw std::invalid_argument("Missing Foot clock/delay owners");
    const int firstTick=s.tick(),delay=s.delay();
    v.wait558.start=firstTick;store(0x558,4,std::uint32_t(firstTick));
    v.wait558.padding=padding;store(0x55c,4,std::uint32_t(padding));
    v.wait558.remaining=delay;store(0x560,4,std::uint32_t(delay));
    const int secondTick=s.tick();
    v.retry530.start=secondTick;store(0x530,4,std::uint32_t(secondTick));
    v.retry530.padding=padding;store(0x534,4,std::uint32_t(padding));
    v.retry530.remaining=0;store(0x538,4,0);
}
}
