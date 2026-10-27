// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/UnitDrawMetadata.hpp"

namespace ra2 {
UnitDrawMetadata updateUnitDrawMetadata(UnitDrawMetadata t,const UnitDrawMetadataServices& s) {
    t.zFudgeCliff=s.integer("ZFudgeCliff",t.zFudgeCliff);
    t.zFudgeColumn=s.integer("ZFudgeColumn",t.zFudgeColumn);
    t.zFudgeTunnel=s.integer("ZFudgeTunnel",t.zFudgeTunnel);
    t.zFudgeBridge=s.integer("ZFudgeBridge",t.zFudgeBridge);
    t.tooBigToFitUnderBridge=s.boolean("TooBigToFitUnderBridge",t.tooBigToFitUnderBridge);
    return t;
}
UnitDrawMetadata readUnitDrawMetadata(const Ini& rules,const std::string& type,UnitDrawMetadata t) {
    UnitDrawMetadataServices s;
    s.integer=[&](std::string_view key,int fallback){return rules.integer(type,std::string(key),fallback);};
    s.boolean=[&](std::string_view key,std::uint8_t fallback){return rules.boolean(type,std::string(key),fallback);};
    return updateUnitDrawMetadata(t,s);
}
}
