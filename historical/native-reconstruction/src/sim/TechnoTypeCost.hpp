// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
namespace ra2 {
struct TechnoTypeCostServices {
    // Borrowed live Type/House/country fields; construction and INI conversion
    // are supplied. Queries must not be memoized across kind/base-cost reads.
    std::function<std::int32_t(const void*)> kind2C;
    std::function<std::int32_t(const void*)> speedTypeBA0;
    std::function<float(const void*,std::int64_t)> countryFactor;
    std::function<std::int32_t(const void*)> baseCostAC;
    // Read-only observation of logical float store/conversion, not an effect.
    std::function<void(char,std::uint32_t)> trace;
};
// Complete4F5960 including default and kind7 speed-type split. Returns the
// selected float32 country value; original association/constructor stays separate.
float houseTechnoCostMultiplier(const void* type,const void* house,const TechnoTypeCostServices&);
// Complete6DAD30 with actual6DACE0 base550 semantics supplied by baseCostAC.
// Null House bypasses multiplier/conversion. Nonnull preserves the float32
// store,53-bit product,toward-zero signed64 FTOL and its low32-bit result.
std::uint32_t technoTypeCost(const void* type,const void* house,const TechnoTypeCostServices&);
}
