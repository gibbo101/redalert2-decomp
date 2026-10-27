// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TeamObserverWeight.hpp"
#include <bit>
#include <cfenv>
#include <cmath>
#include <limits>
#include <stdexcept>
#if defined(__clang__)
#pragma STDC FENV_ACCESS ON
#endif
namespace ra2 {
namespace {
// x87 PC=53 rounds each arithmetic result, while retaining a wider exponent.
// This bounded profile avoids exponent edges; do not silently extend it to all
// doubles or replace these ordered operations with algebraic simplification.
double add(double a,double b){volatile double r=a+b;return r;}
double sub(double a,double b){volatile double r=a-b;return r;}
double mul(double a,double b){volatile double r=a*b;return r;}
double div(double a,double b){volatile double r=a/b;return r;}
void finiteProfile(double v){
    if(!std::isfinite(v)||(v!=0&&(std::abs(v)<1e-100||std::abs(v)>1e100)))
        throw std::invalid_argument("Team observer FP input outside verified finite profile");
}
std::int32_t increment(std::int32_t v){return std::bit_cast<std::int32_t>(std::uint32_t(v)+1u);}
}
void updateTeamObserverWeight(TeamObserverWeight o,bool success,const TeamObserverWeightServices& s){
    static_assert(std::numeric_limits<double>::is_iec559&&std::numeric_limits<double>::digits==53);
    if(!s.rules)throw std::invalid_argument("Team observer Rules unbound");
    const int rounding=std::fegetround();
    if(rounding!=FE_TONEAREST&&rounding!=FE_TOWARDZERO)
        throw std::invalid_argument("Team observer rounding outside verified profile");
    finiteProfile(o.weightB8);finiteProfile(o.minimumC0);finiteProfile(o.maximumC8);
    const auto record=[&](std::uint32_t off,std::uint32_t n,std::uint64_t bits){if(s.store)s.store(off,n,bits);};
    const auto splitClamp=[&](const double& bound){
        // The second source word is read after the first destination word store.
        auto bits=std::bit_cast<std::uint64_t>(o.weightB8);
        const auto low=std::uint32_t(std::bit_cast<std::uint64_t>(bound));
        o.weightB8=std::bit_cast<double>((bits&0xffffffff00000000ull)|low);record(0xb8,4,low);
        const auto high=std::uint32_t(std::bit_cast<std::uint64_t>(bound)>>32);
        bits=std::bit_cast<std::uint64_t>(o.weightB8);
        o.weightB8=std::bit_cast<double>((bits&0xffffffffull)|(std::uint64_t(high)<<32));record(0xbc,4,high);
    };
    const auto total=o.trials108; // saved EDX, unlike the late success counter
    double correction=0;
    // 41E070 saves the Rules pointer before the ratio;41DFB0 loads it afterward.
    const auto checkedRules=[&](){auto r=s.rules();finiteProfile(r.successB8);finiteProfile(r.failureC0);finiteProfile(r.failureCoefficientC8);return r;};
    if(success){
        if(total>0){correction=mul(sub(div(double(o.successes104),double(total)),0.5),double(total));if(correction<0)correction=0;}
        const auto r=checkedRules();
        o.weightB8=add(add(r.successB8,o.weightB8),correction);
    }else{
        const auto r=checkedRules();
        if(total>0){correction=mul(mul(sub(div(double(o.successes104),double(total)),0.5),r.failureCoefficientC8),double(total));if(correction>0)correction=0;}
        o.weightB8=add(add(r.failureC0,o.weightB8),correction);
    }
    record(0xb8,8,std::bit_cast<std::uint64_t>(o.weightB8));
    if(o.weightB8<o.minimumC0)splitClamp(o.minimumC0);
    if(o.weightB8>o.maximumC8)splitClamp(o.maximumC8);
    if(success){o.successes104=increment(o.successes104);record(0x104,4,std::uint32_t(o.successes104));}
    o.trials108=increment(total);record(0x108,4,std::uint32_t(o.trials108));
}
}
