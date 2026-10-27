// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/FootPermissionOverride.hpp"
#include <stdexcept>
namespace ra2 {
bool footPermissionOverride(FootPermissionOverrideActor a,const FootPermissionOverrideServices& s){
    if(!a.active32d)return false;
    if(!s.typeTrainAa0)throw std::invalid_argument("Foot permission override requires type query");
    if(s.typeTrainAa0())return true;
    if(a.flag32c)return true;
    if(!s.mission)throw std::invalid_argument("Foot permission override requires mission query");
    if(s.mission()==4)return true;
    const auto team=a.team4c4;
    if(!team)return false;
    if(!s.teamPredicate)throw std::invalid_argument("Foot permission override Team child requires recovery");
    return s.teamPredicate(team)!=0;
}
}
