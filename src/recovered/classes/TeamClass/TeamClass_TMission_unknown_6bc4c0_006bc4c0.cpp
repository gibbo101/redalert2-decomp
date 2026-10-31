// void TeamClass::TMission_unknown_6bc4c0(ScriptMissionClass const &mission, bool unknown) (0x006BC4C0)
// Moves the tactical view to the team's target, raised over the map (and over cells flagged 0x100 or 0x400), using Data.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/map_view.hpp"
#include "shared/tactical.hpp"
#include "shared/cell.hpp"
// @ref _unknown_geometry_j=00ac0098
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_006A2CB0@Tactical@@QAEXABUCoordStruct@@H@Z=006a2cb0
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280

void TeamClass::TMission_unknown_6bc4c0(ScriptMissionClass const &mission, bool unknown)
{
    CoordStruct coord = unknown_34->Center_Coord();
    coord.Z = Map.Unknown_0055A280(coord);
    if ((Map[coord].unknown_140 & 0x100) || (Map[coord].unknown_140 & 0x400)) {
        coord.Z += unknown_geometry_j;
    }
    unknown_tactical_83996c->Unknown_006A2CB0(coord, mission.Data);
    StepCompleted = true;
}
