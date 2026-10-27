// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cfenv>
#include <stdexcept>
#if defined(__clang__)
#pragma STDC FENV_ACCESS ON
#endif
namespace ra2 {
// Original FTOL leaves x87 control word 0x0e7f active (53-bit, toward zero).
// The portable host must get its own rounding mode back, including on exceptions.
class OriginalRounding {
    int previous_=std::fegetround();
public:
    OriginalRounding() {
        if(previous_==-1||std::fesetround(FE_TOWARDZERO)!=0)
            throw std::runtime_error("Required FP rounding unavailable");
    }
    ~OriginalRounding() { std::fesetround(previous_); }
    OriginalRounding(const OriginalRounding&)=delete;
    OriginalRounding& operator=(const OriginalRounding&)=delete;
};
}
