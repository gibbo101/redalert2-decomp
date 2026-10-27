// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/PreparedFootDepth.hpp"
#include <map>
namespace ra2 {
// Scoped views of shared prepared Cell records. Callbacks returned by world()
// borrow this object; it must outlive the complete draw. Initial actor/type/global
// state is supplied, nonbridge and empty tube registry only. The actual current
// Cell must be flat for the existing Drive shadow consumer; neighbors may be
// ramps. Construction performs a separate preflight query. No final-depth
// substitution: consumers run their actual Foot predicates and Unit base.
class PreparedUnitDepth {
public:
    PreparedUnitDepth(const PreparedFootDepthInputs&,const PreparedFootDepthWorld&);
    PreparedUnitDepth(const PreparedUnitDepth&)=delete;
    PreparedUnitDepth& operator=(const PreparedUnitDepth&)=delete;
    FootDepthWorld world();
    int baseDepth() const;
private:
    const PreparedFootDepthInputs& input_;
    const PreparedFootDepthWorld& services_;
    std::map<const MapCellAttributes*,FootDepthCell> views_;
};
}
