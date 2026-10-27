// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/FootDepth.hpp"
#include "render/UnitBaseDepth.hpp"
namespace ra2 {
struct PreparedFootDepthInputs {
    UnitBaseDepthInputs unit;
    FootDepthType type;
    bool drive=true;
    int tileBase=0;
    UnitLightCell invalid{};
};
struct PreparedFootDepthWorld {
    UnitBaseDepthWorld unit;
    // Read-only observations of predicates, type/Drive/base and Cell predicate.
    std::function<void(int)> trace;
    std::function<void(UnitLightCell)> cellPredicate;
};
struct PreparedFootDepthResult {int depth=0,gradient=0;};
// Ordinary nonbridge Unit on shared stable Cells, with an empty tube registry.
// Original initial/type/actor state is supplied. Refuse a missing TMP image when
// dimensions are needed: nested caller scratch initialization is not recovered.
PreparedFootDepthResult preparedFootDepth(const PreparedFootDepthInputs&,const PreparedFootDepthWorld&);
}
