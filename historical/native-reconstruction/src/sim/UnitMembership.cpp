// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MembershipPolicy.hpp"
namespace ra2 {
void UnitMembershipWorld::cellInsert(int id,int cell){membership_policy::cellInsert(id,cell,*this);}
void UnitMembershipWorld::cellRemove(int id,int cell){membership_policy::cellRemove(id,cell,*this);}
void UnitMembershipWorld::mapInsert(int id,TerrainCellPoint p){membership_policy::mapChange(id,p,true,*this);}
void UnitMembershipWorld::mapRemove(int id,TerrainCellPoint p){membership_policy::mapChange(id,p,false,*this);}
}
