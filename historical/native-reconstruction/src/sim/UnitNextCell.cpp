// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/UnitNextCell.hpp"
namespace ra2 {
void ordinaryUnitNextCell(int mover,const UnitNextCellActor& actor,TerrainCellPoint point,std::uint8_t warning,UnitAdmissionWorld& w){unit_next_cell_policy::ordinaryUnitNextCell(mover,actor,point,warning,w);}
}
